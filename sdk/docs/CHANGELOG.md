
# Graphics Extensions SDK API Changelog

<!-- This file is auto-generated. -->


**[1]** - 2019-09-01
- **Changes:**  
    - Initial version of the Graphics Extensions API.

**[2]** - 2024-08-21
- **Description:**  Enabled auto-generation of the Graphics Extensions SDK API project.
- **API Version:**  14  
- **Changes:**  
    - Added INTC_EXTENSION_GETCOMMANDLISTHANDLE extension type.
    - Added INTC_EVENT_MARKER_EVENT enumeration.
    - Enable auto-generation of the Graphics Extensions SDK API project.

**[3]** - 2024-08-21
- **Description:**  Add XeSS D3D11 API.
- **API Version:**  14  
- **Changes:**  
    - Added XeSS D3D11 API.

**[4]** - 2024-09-09
- **Description:**  Changes in INTC_D3D12_SetEventMarker API argument.
- **API Version:**  14  
- **Changes:**  
    - Changed type for argument pCommandList from ID3D12GraphicsCommandList* to ID3D12CommancList*.

**[6]** - 2024-11-25
- **Description:**  Added Tools Support for Graphics Extensions Framework. It allows an app to register callback table that will be called by Graphics Extensions library to notify about the API calls (API record scenario).
- **API Version:**  15  
- **Changes:**  
    - Tools Support for Intel(R) Graphics Extensions Framework added.
    - Minor changes in the input file and generated code.

**[9]** - 2024-12-17
- **Description:**  Tools Support API update.
- **API Version:**  15  
- **Changes:**  
    - Tools Support API update - added GetSupportedVersions callbacks.
    - Developer Guide updates. Still in progress.
    - Include igdext_tools.h in the release package.

**[10]** - 2025-01-31
- **Description:**  Names cleanup.
- **API Version:**  15  
- **Changes:**  
    - Cleaned up names in the input file.

**[11]** - 2025-04-08
- **Description:**  Add extension support to retrieve resource driver handle.
- **API Version:**  16  
- **Changes:**  
    - Add paired Begin and End intel internal extension type to retrieve resource handle.

**[14]** - 2025-05-01
- **Description:**  Fixes
- **API Version:**  16  
- **Changes:**  
    - Fix DLL modifying original variables.
    - Fix some missing Tools Callbacks (e.g. INTC_D3D12_SetApplicationInfo).

**[15]** - 2025-05-13
- **Description:**  Move retrieve resource driver handle extension type to the end of enumeration.
- **API Version:**  16  
- **Changes:**  
    - To void compatability issues, newly decleared types should be locate at the end.

**[15]** - 2025-05-23
- **Description:**  New extensions for offline compiler.
- **API Version:**  17  
- **Changes:**  
    - Add extensions support for setting and retrieving offline compilation device.

**[16]** - 2025-06-10
- **Description:**  Add new extensions GetCurrentShaderHeapUsage() 
- **API Version:**  18  
- **Changes:**  
    - Add INTC_EXTENSION_GETCURRENTSHADERHEAPUSAGE extension type.
    - Extension returns current shader heap usage in bytes.

**[17]** - 2025-06-18
- **Description:**  Add new extensions for D3D12 device.
- **API Version:**  19  
- **Changes:**  
    - Add INTCDeviceParams and INTCParamValue structures for SetDeviceParams extensions call
    - Add INTC_D3D12_SetDeviceParams extension
    - New device detection logic (GMDID, XeCoresCount)

**[18]** - 2025-10-07
- **Description:**  Get Cached Blob extension.
- **API Version:**  20  
- **Changes:**  
    - Add GetCachedBlob extension

**[19]** - 2025-10-28
- **Description:**  Fix API 20 version reported properly on Gen12HP platforms.
- **API Version:**  20  
- **Changes:**  
    - Add API 20 to supported versions for Gen12HP platforms.

**[20]** - 2025-11-25
- **Description:**  Add INTC_D3D12_GetDeviceParams extension.
- **API Version:**  20  
- **Changes:**  
    - Add INTC_D3D12_GetDeviceParams extension. This is only DLL visible extension for driver to use.
    - Modify INTC_D3D12_GetCachedBlob extension definition

**[21]** - 2026-03-31
- **Description:**  New options INTC_D3D12_FEATURE_DATA_D3D12_OPTIONS3 added.
- **API Version:**  21  
- **Changes:**  
    - New flag AsyncCompute added to INTC_D3D12_FEATURE_DATA_D3D12_OPTIONS3 structure.

