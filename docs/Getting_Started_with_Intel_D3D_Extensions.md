# Getting Started with Intel® Graphics Extensions

Last updated: 9/11/2026 — Graphics Extensions SDK 4.21.12, API version 21

---

## Contents

- [Overview](#overview)
- [What is in the SDK](#what-is-in-the-sdk)
- [Versioning](#versioning)
- [Adding the SDK to your project](#adding-the-sdk-to-your-project)
- [Loading the extensions library](#loading-the-extensions-library)
- [Creating a device extension context](#creating-a-device-extension-context)
- [Querying the device](#querying-the-device)
- [Calling an extension](#calling-an-extension)
- [Shutting down](#shutting-down)
- [Tools support](#tools-support)
- [Shader extensions](#shader-extensions)
- [Common questions](#common-questions)
- [References](#references)

---

## Overview

Intel Graphics Extensions expose features of Intel graphics hardware that the standard
Direct3D 11 and Direct3D 12 APIs do not. They are implemented in the Graphics Extensions
Library (`igdext32.dll` / `igdext64.dll`), which is installed as part of the Intel Graphics
Driver. This SDK is a thin static library plus a header that locates and calls into that
DLL at runtime.

Because the binding happens at runtime, an application that links the SDK still runs
normally on non-Intel hardware and on older Intel drivers: the load or the context creation
fails, and your existing Direct3D path is used instead. Do not copy or replace
`igdext32.dll` / `igdext64.dll` — the SDK finds the one that belongs to the installed
driver.

Every entry point returns an `HRESULT`. Treat a failure as "this extension is not available
here", not as a fatal error.

## What is in the SDK

```
d3dext-sdk
├── sdk
│   ├── include          igdext.h (extensions API), igdext_tools.h (tools API)
│   ├── lib
│   │   ├── Win32/Release/igdext32.lib
│   │   └── x64/Release/igdext64.lib
│   └── docs             generated API reference and changelog
├── docs                 this guide
└── samples
    ├── igdext_common    igdext_impl — reusable init/teardown wrapper
    └── igdext_dx12_helloworld   Direct3D 12 sample that uses it
```

The complete list of extensions, the per-platform support matrix and the API version each
extension was introduced in are generated from the API definition and published in
[../sdk/docs/GraphicsExtensionsAPI.md](../sdk/docs/GraphicsExtensionsAPI.md). Read that
document rather than a copy, so the table matches the SDK you have.

## Versioning

A version is a 3-tuple, `HWFeatureLevel.APIVersion.Revision`:

```cpp
struct INTCExtensionVersion
{
    uint32_t HWFeatureLevel; ///< HW Feature Level, based on the Intel HW Platform
    uint32_t APIVersion;     ///< API Version
    uint32_t Revision;       ///< Revision number
};
```

- **HW Feature Level** — the hardware generation the request targets. Feature levels 1
  through 6 are documented today (Gen9 through Xe3); see the support matrix in the
  [API reference](../sdk/docs/GraphicsExtensionsAPI.md).
- **API Version** — increments whenever the API surface changes. The current version is 21.
- **Revision** — bug fixes with no API change.

Request the *lowest* HW feature level and API version that contain the extensions you
actually use; that keeps your application working on the widest range of GPUs and drivers.
The support matrix in the [API reference](../sdk/docs/GraphicsExtensionsAPI.md) tells you
which combination you need.

## Adding the SDK to your project

1. Add `sdk/include` to your include path.
2. Link `sdk/lib/x64/Release/igdext64.lib` (or the `Win32` / `igdext32.lib` pair). The 64-bit
   library is recommended.
3. Add the OS import libraries the SDK depends on: `ole32.lib` and `kernel32.lib`. The
   library is built `/Zl`, so it names no default libraries of its own and the consuming
   application supplies them. Most projects already link both.
4. Define `INTC_IGDEXT_D3D12`, `INTC_IGDEXT_D3D11`, or both before including `igdext.h`:

   ```cpp
   #define INTC_IGDEXT_D3D12
   #include "igdext.h"
   ```

5. Optionally include `igdext_tools.h` for the tools/callback API.

Built and validated with Visual Studio 2022 and the Windows SDK; nothing from the SDK needs
to be redistributed with your application.

Building the static library from source instead of linking the prebuilt one is described in
[../sdk/BUILDING.md](../sdk/BUILDING.md).

## Loading the extensions library

```cpp
HRESULT INTC_LoadExtensionsLibrary(
    bool   useCurrentProcessDir = false,
    size_t VendorID             = 0,
    size_t DeviceID             = 0 );
```

- `useCurrentProcessDir` — leave `false`. It loads the DLL from the process directory and
  exists for driver development only.
- `VendorID` / `DeviceID` — the adapter you intend to use. Pass them when you load the
  library *before* creating the D3D12 device; otherwise the SDK derives the adapter from the
  device.

There are two workable orderings.

**Load before creating the device.** Required if you want to register application
information with the driver, since `INTC_D3D12_SetApplicationInfo` influences driver
behaviour chosen at device creation time.

```cpp
DXGI_ADAPTER_DESC1 desc;
hardwareAdapter->GetDesc1( &desc );

INTC_LoadExtensionsLibrary( false, desc.VendorId, desc.DeviceId );

INTCExtensionAppInfo1 appInfo = {};
appInfo.pApplicationName = L"Sample App";
appInfo.pEngineName      = L"Unreal Engine";
appInfo.EngineVersion    = { 5, 5, 0 };
INTC_D3D12_SetApplicationInfo( &appInfo );

D3D12CreateDevice( hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS( &device ) );
```

**Load after creating the device.** Simpler when you only need extension entry points.

```cpp
D3D12CreateDevice( ... );
INTC_LoadExtensionsLibrary();
```

## Creating a device extension context

Enumerate the versions the driver supports for this device, then create a context for the
one you need. `INTC_D3D12_GetSupportedVersions` is called twice: once for the count, once to
fill an array you allocate. The returned versions are ordered oldest to newest.

```cpp
uint32_t count = 0;
INTC_D3D12_GetSupportedVersions( pDevice, nullptr, &count );

std::vector<INTCExtensionVersion> supported( count );
INTC_D3D12_GetSupportedVersions( pDevice, supported.data(), &count );

INTCExtensionInfo1 info = {};
info.RequestedExtensionVersion = { 5, 20, 0 }; // HW feature level, API version, revision

INTCExtensionAppInfo1 appInfo = {};
appInfo.pApplicationName    = L"Sample App";
appInfo.ApplicationVersion  = { 0, 0, 0 };
appInfo.pEngineName         = L"Unreal Engine";
appInfo.EngineVersion       = { 5, 5, 0 };

INTCExtensionContext* pContext = nullptr;
if( FAILED( INTC_D3D12_CreateDeviceExtensionContext2( pDevice, &pContext, &info, &appInfo ) ) )
{
    INTC_UnloadExtensionsLibrary();
    return false; // Fall back to the standard Direct3D path.
}
```

`INTC_D3D12_CreateDeviceExtensionContext2` is the current entry point. It takes
`INTCExtensionInfo1`, which reports the extended device information described below.
Checking the requested version against the enumerated list first is recommended, but
creation will fail cleanly if you skip it.

The `igdext_impl` helper in `samples/igdext_common/igdext_impl.cpp` wraps exactly this
sequence — see `igdext_impl::init()` for the load and `igdext_impl::set_device()` for the
context creation. It can be copied into your project as-is.

## Querying the device

On success, `INTCExtensionInfo1` is filled in with the driver description, driver version
string, driver build number, and an `INTCDeviceInfo1`:

```cpp
struct INTCDeviceInfo
{
    uint32_t GPUMaxFreq;             ///< GPU maximum frequency in MHz
    uint32_t GPUMinFreq;             ///< GPU minimum frequency in MHz
    uint32_t GTGeneration;           ///< GPU generation number
    uint32_t EUCount;                ///< Number of execution units
    uint32_t PackageTDP;             ///< Package thermal design power in watts
    uint32_t MaxFillRate;            ///< Maximum fill rate
    wchar_t  GTGenerationName[ 64 ]; ///< GPU generation name (string)
};

struct INTCDeviceInfo1 : INTCDeviceInfo
{
    uint32_t GMDID;        ///< GMD ID (GT, Media, Display - Arch and Release ID)
    uint32_t XeCoresCount; ///< Number of Xe cores (useful for a performance class estimate)
};
```

`GMDID` identifies the architecture and release, and is the reliable way to gate work on a
hardware generation. `igdext.h` provides the accessors and the known identifiers:

```cpp
uint32_t arch    = INTC_GMD_ID_GET_ARCH( info.IntelDeviceInfo.GMDID );
uint32_t release = INTC_GMD_ID_GET_RELEASE( info.IntelDeviceInfo.GMDID );

// e.g. INTC_GMD_ARCH_12 (Xe), INTC_GMD_ARCH_20 (Xe2),
//      INTC_GMD_ARCH_20_RELEASE_XE2_HPG_X2 (BMG-B570 / B580)
```

`igdext_impl::device_architecture()` implements the "at least this architecture/release"
comparison, and `igdext_impl::get_performance_estimate()` maps the known GMD IDs and Xe core
count onto a coarse low/medium/high class you can use to pick default settings.

Do not use these values to decide whether an extension exists — use the version enumeration
for that. Use them to pick quality presets and code paths.

## Calling an extension

Extension entry points take the context as their first argument:

```cpp
UINT64 shaderHeapUsage = 0;
INTC_D3D12_GetCurrentShaderHeapUsage( pContext, &shaderHeapUsage );
```

Refer to [../sdk/docs/GraphicsExtensionsAPI.md](../sdk/docs/GraphicsExtensionsAPI.md) for the
signature, the API version and the platform support of each extension, and to
`samples/igdext_dx12_helloworld/D3D12HelloWindow.cpp` for working calls into
`INTC_D3D12_GetCurrentShaderHeapUsage`, `INTC_D3D12_GetCachedBlob` and
`INTC_D3D12_SetDriverEventMetadata`.

## Shutting down

```cpp
INTC_DestroyDeviceExtensionContext( &pContext );
INTC_UnloadExtensionsLibrary();
```

Free anything you allocated for `INTC_D3D12_GetSupportedVersions`. `igdext_impl::shutdown()`
does both, and the `igdext_impl` destructor calls it.

## Tools support

`igdext_tools.h` lets an application register a callback table so capture and analysis tools
can observe extension API calls. Initialize the table with `INTC_D3D12_API_CALLBACKS_INIT`,
set the callbacks you implement, and check the table version before setting entries added in
a later revision:

```cpp
INTC_D3D12_API_CALLBACKS1 callbacks = { 0 };

// Initialize the compatibility header explicitly. Do not use
// INTC_D3D12_API_CALLBACKS_INIT here - see the note below.
callbacks.header.structVersion = INTC_D3D12_API_CALLBACKS_VERSION_CURRENT;
callbacks.header.structSize    = sizeof( callbacks );

callbacks.INTC_D3D12_SetApplicationInfo               = MySetApplicationInfo;
callbacks.INTC_D3D12_CreateDeviceExtensionContext1    = MyCreateDeviceExtensionContext1;

if( INTC_D3D12_API_CALLBACKS_CHECK_VERSION( callbacks, 2 ) )
{
    callbacks.INTC_D3D12_SetDeviceParams              = MySetDeviceParams;
    callbacks.INTC_D3D12_CreateDeviceExtensionContext2 = MyCreateDeviceExtensionContext2;
}

INTC_D3D12_RegisterApplicationCallbacks1( &callbacks );
```

Register the callbacks before creating the device extension context. The sample shows the
full table.

> **Note**
> `INTC_D3D12_API_CALLBACKS_INIT` sets `header.structSize` from
> `INTC_D3D12_API_CALLBACKS_SIZE_CURRENT`, which is defined as
> `sizeof( INTC_D3D12_API_CALLBACKS )` — the deprecated version 0 structure, which has
> neither the compatibility header nor the version 2 function pointers. It sets
> `header.structVersion` to 2 at the same time, so the reported size is inconsistent with
> the reported version and a consumer using `INTC_D3D12_API_CALLBACKS_CHECK_SIZE` will treat
> the version 2 entries as absent. Set `header.structSize` to `sizeof( callbacks )` yourself
> until the macro is corrected.

## Shader extensions

Some extensions add HLSL intrinsics rather than host API calls. Those require three
additional things:

1. A UAV descriptor in a reserved slot — register `u63` by default. Nothing needs to be
   written into it, but the range must be present in the root signature.
   Override the slot with `#define INTEL_SHADER_EXT_UAV_SLOT u7` (for example) before
   including the Intel HLSL header.
2. The Intel HLSL header included at the top of the shader, and a call to `IntelExt_Init()`
   before any Intel intrinsic. Intrinsics are prefixed `IntelExt_`.
3. Optimizations disabled for that HLSL file (`/Od`).

Host side:

```cpp
D3DX12_DESCRIPTOR_RANGE1 rootRangeIntelExt[1];
rootRangeIntelExt[0].Init( D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 63, 0,
                           D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC );

CD3DX12_ROOT_PARAMETER1 rootParameterIntelExt;
rootParameterIntelExt.InitAsDescriptorTable( 1, &rootRangeIntelExt[0],
                                             D3D12_SHADER_VISIBILITY_PIXEL );

rootParameters[ RootParameterIndexSRVCBVUAV + 1 ] = rootParameterIntelExt;

m_commandList->SetGraphicsRootDescriptorTable(
    RootParameterIndexSRVCBVUAV + 1,
    gpuHeapSRVCBVUAV->ComputeGPUHandle( nullUAVGPUDescIndex ) );
```

Shader side:

```hlsl
#include "IntelExtensions12.hlsl"

float4 PSMain() : SV_Target
{
    IntelExt_Init();
    float4 finalColor = /* ... */;
    return finalColor;
}
```

> **Note**
> The HLSL helper headers (`IntelExtensions.hlsl` for D3D11, `IntelExtensions12.hlsl` for
> D3D12) are not part of this repository snapshot. Open an issue if you need them for the
> extension you are targeting.

## Common questions

**Is the extension I want available on this GPU and driver?**
Call `INTC_D3D12_GetSupportedVersions` and look for a version at or above the one the
extension requires. The requirement per extension is in the
[API reference](../sdk/docs/GraphicsExtensionsAPI.md). If the version you need is missing,
the driver is older than the extension; the current driver is at
[Intel Driver and Software Downloads](https://www.intel.com/content/www/us/en/download-center/home.html).

**Are extensions backward compatible?**
An extension introduced for a newer hardware generation is not guaranteed to run on older
hardware, but where the hardware can support it we make it available.

**Are extensions forward compatible?**
Yes. Once an extension ships as a supported extension it is validated against subsequent
driver releases and is intended to keep working on newer hardware.

**What if an extension is not available?**
Always have a fallback. Context creation failing, or a version not being enumerated, is a
normal outcome on non-Intel hardware or an older driver.

**Can I create more than one context in the same application?**
This is strongly discouraged. It has been tested only in a narrow case that needed two
different context versions.

**Using RenderDoc**
Select *Ref All Resources* in the Capture Options.

**Using Intel Graphics Performance Analyzer**
Use stream mode rather than frame mode; select it in Graphics Monitor before launching the
application.

**I have feedback on the interface**
Open an issue. Input on both the API shape and on extensions you would like to see is
welcome.

## References

1. [Graphics Extensions API reference](../sdk/docs/GraphicsExtensionsAPI.md)
2. [Changelog](../sdk/docs/CHANGELOG.md)
3. [Microsoft DirectX-Graphics-Samples](https://github.com/microsoft/DirectX-Graphics-Samples)
   — the Direct3D 12 sample in this repository is derived from D3D12HelloWorld
