# Intel® Graphics Extensions SDK

The Intel Graphics Extensions SDK gives Direct3D 11 and Direct3D 12 applications access to
features of Intel graphics hardware that are not exposed by the standard Direct3D APIs —
multi-draw indirect, UAV overlap, depth bounds test, 64-bit typed atomics, CPU-visible VRAM,
host-side BVH builds, GPU crash breadcrumbs and more.

The SDK is a thin static library plus a header. It talks to the Intel Graphics Driver at
runtime, so an application that links it still runs normally on non-Intel hardware and on
older Intel drivers — extensions simply report as unavailable and your existing code path is
used instead.

Licensed under the [MIT License](LICENSE).

## Features

### Direct3D 12

| Feature | What it does |
| ------- | ------------ |
| [CPU Visible VRAM](sdk/docs/GraphicsExtensionsAPI.md#cpu-visible-vram) | Create committed, placed, reserved resources and heaps in CPU-visible device memory, and query how much is free. |
| [Emulated Typed 64-bit Atomics](sdk/docs/GraphicsExtensionsAPI.md#emulated-typed-64bit-atomics) | 64-bit typed atomic operations on Texture2D resources. |
| [BVH CPU Build](sdk/docs/GraphicsExtensionsAPI.md#bvh-cpu-build) | Build, copy and query raytracing acceleration structures on the host timeline, then transfer them to device memory. |
| [Breadcrumbs](sdk/docs/GraphicsExtensionsAPI.md#breadcrumbs) | Place event markers in command lists and capture, decode and inspect GPU crash dumps to find the work that was in flight. |
| [Get Cached Blob](sdk/docs/GraphicsExtensionsAPI.md#get-cached-blob) | Retrieve the cached blob for a pipeline state. |
| [Offline Compiler](sdk/docs/GraphicsExtensionsAPI.md#offline-compiler) | Point the driver at precompiled shader binaries on disk. |
| [Command Throttle Policy](sdk/docs/GraphicsExtensionsAPI.md#command-throttle-policy) | Create a command queue with a throttle policy that biases shared CPU/GPU power toward the GPU. |
| [Driver Metadata](sdk/docs/GraphicsExtensionsAPI.md#driver-metadata) | Attach metadata to a command list for driver-side tooling. |
| [Application Discovery](sdk/docs/GraphicsExtensionsAPI.md#application-discovery) | Register your application name, version and engine with the driver. |
| [GetCurrentShaderHeapUsage](sdk/docs/GraphicsExtensionsAPI.md#getcurrentshaderheapusage) | Query current shader heap usage. |
| [XeSS](sdk/docs/GraphicsExtensionsAPI.md#xess) | Driver support queries backing Intel Xe Super Sampling. |

### Direct3D 11

| Feature | What it does |
| ------- | ------------ |
| [Multi Draw Indirect](sdk/docs/GraphicsExtensionsAPI.md#multi-draw-indirect) | Submit many indirect draws in one call, optionally with a GPU-side draw count, instead of one call per draw. |
| [UAV Overlap](sdk/docs/GraphicsExtensionsAPI.md#uav-overlap) | Disable GPU synchronization between consecutive draws and dispatches that share a UAV when you know they do not conflict. |
| [Depth Bounds Test](sdk/docs/GraphicsExtensionsAPI.md#depth-bounds-test) | Set the depth bounds range dynamically. |
| [Emulated Typed 64-bit Atomics](sdk/docs/GraphicsExtensionsAPI.md#emulated-typed-64bit-atomics) | 64-bit typed atomics on textures created through the extension. |
| [Retrieve Resource Driver Handle](sdk/docs/GraphicsExtensionsAPI.md#retrieve-resource-driver-handle) | Obtain the driver-side handle for a resource, with the retrieval path off by default so normal resource creation is unaffected. |

Availability depends on both the GPU and the installed driver. The per-platform support
matrix and the complete API reference are in
[sdk/docs/GraphicsExtensionsAPI.md](sdk/docs/GraphicsExtensionsAPI.md).

## Requirements

- Windows, x64 or Win32
- An Intel GPU and an installed Intel Graphics Driver. The extensions are reached through
  `igdext64.dll` / `igdext32.dll`, which ships with the driver. Do not copy that DLL next to
  your application or replace it — the SDK locates the installed one.
- Visual Studio 2022 to build the samples

## Getting started

Add `sdk/include` to your include path and link the static library for your architecture:
`sdk/lib/x64/Release/igdext64.lib` or `sdk/lib/Win32/Release/igdext32.lib`. There is nothing
to redistribute.

The library is a thin wrapper: it finds the extensions DLL that ships with the installed
driver, resolves the entry points and forwards calls. Its sources are in `sdk/src`, so you
can read exactly what it does and rebuild it yourself — see [sdk/BUILDING.md](sdk/BUILDING.md).

```cpp
#define INTC_IGDEXT_D3D12
#include "igdext.h"

// 1. Load the extensions library that shipped with the installed driver.
//    Fails cleanly when there is no Intel GPU or the driver is too old.
if( FAILED( INTC_LoadExtensionsLibrary() ) )
    return false;

// 2. Ask the device which extension versions it supports.
uint32_t count = 0;
INTC_D3D12_GetSupportedVersions( pDevice, nullptr, &count );

std::vector<INTCExtensionVersion> supported( count );
INTC_D3D12_GetSupportedVersions( pDevice, supported.data(), &count );

// 3. Create a context for the version you need. Check it against the list
//    above before requesting it.
INTCExtensionInfo1 info = {};
info.RequestedExtensionVersion = { 4, 21, 0 }; // HW feature level, API version, revision

INTCExtensionAppInfo1 appInfo = {};
appInfo.pApplicationName = L"My Application";
appInfo.pEngineName      = L"My Engine";

INTCExtensionContext* pContext = nullptr;
if( FAILED( INTC_D3D12_CreateDeviceExtensionContext2( pDevice, &pContext, &info, &appInfo ) ) )
{
    INTC_UnloadExtensionsLibrary();
    return false; // Fall back to your standard Direct3D path.
}

// ... call extension entry points with pContext ...

INTC_DestroyDeviceExtensionContext( &pContext );
INTC_UnloadExtensionsLibrary();
```

Every extension entry point returns an `HRESULT`. Treat a failure as "this extension is not
available here" and fall back, rather than as a fatal error.

## Samples

[`samples/igdext_dx12_helloworld`](samples/igdext_dx12_helloworld) is a Direct3D 12
application that performs the full sequence above. Open
`igdext_dx12_helloworld.sln` in Visual Studio 2022 and build the x64 configuration. The
project restores the `Microsoft.Direct3D.D3D12` Agility SDK NuGet package at build time.

[`samples/igdext_common`](samples/igdext_common) holds a small reusable wrapper
(`igdext_impl`) around initialization, version selection and teardown that the sample builds
on and that you can lift into your own project.

## Documentation

- [Getting Started guide](docs/Getting_Started_with_Intel_D3D_Extensions.md) — the longer
  walkthrough: versioning scheme, loading the library, the extension structures, compiler
  extensions and answers to common questions
- [API reference](sdk/docs/GraphicsExtensionsAPI.md) — every entry point, structure and
  enumeration, plus the platform and version support matrix
- [Changelog](sdk/docs/CHANGELOG.md) — what changed in each API version
- [Building the static library from source](sdk/BUILDING.md) — optional; the prebuilt
  libraries in `sdk/lib` are the usual path

## Repository layout

| Path | Contents |
| ---- | -------- |
| `sdk/include` | `igdext.h` (extensions API), `igdext_tools.h` (tools API) |
| `sdk/src` | Sources of the wrapper and loader library, and [how to build them](sdk/BUILDING.md) |
| `sdk/lib` | Prebuilt static libraries for x64 and Win32 |
| `sdk/docs` | API reference and changelog |
| `docs` | Getting Started guide |
| `samples` | Direct3D 12 sample and shared helper code |
| `CMakeLists.txt` | Optional target to build the static library from source |

The SDK content corresponds to the Graphics Extensions SDK 4.21.12 release.

## License

MIT. See [LICENSE](LICENSE).

The license covers the headers, the prebuilt static libraries in `sdk/lib`, the documentation
and the samples. Parts of the samples are derived from Microsoft's DirectX-Graphics-Samples
and carry Microsoft's copyright under the same MIT terms; the Agility SDK NuGet package the
sample restores at build time is governed by Microsoft's own license and is not redistributed
here. See [THIRD-PARTY-NOTICES.md](THIRD-PARTY-NOTICES.md).

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). Security issues go through
[SECURITY.md](SECURITY.md), not GitHub Issues.
