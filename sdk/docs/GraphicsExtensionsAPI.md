
# Intel(R) Graphics Extensions SDK API Documentation

**Version: 6.20.***

This document contains the API documentation for the Intel Graphics Extensions SDK. This document is auto-generated.


# Intel(R) Graphics Extensions version compatibility table

Supported HW Feature Levels (Platforms):
HW Feature Level | Platform ID | Platform Description |
------------ | ------------ | ------------ |
1 | Gen9 | None |
2 | Gen11 | None |
3 | Gen12LP | None |
4 | Xe Architecture |  |
5 | Xe2 Architecture |  |
6 | Xe3 Architecture | None |

API Version | Revision | Gen9 *(1)* | Gen11 *(2)* | Gen12LP *(3)* | Xe Architecture *(4)* | Xe2 Architecture *(5)* | Xe3 Architecture *(6)* | 
------------ | --------- | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | 
0 |  |X |X |X |X | | 
1 |  |X |X |X |X | | 
2 |  |X |X |X |X | | 
4 |  |X |X |X |X | | 
5 |  | |  |  | X | | 
6 |  | |  |  | X |X |
7 |  | |  |  | X |X |
8 |  | |  |  | X |X |
9 |  |X |X |X |X |X |
10 |  | |  | X |X |X |
11 |  | |  |  | X |X |
12 |  | |  | X |X |X |
13 |  | |  |  | X |X |
14 |  | |  | X |X |X |
15 |  | |  |  | X |X |
16 |  | |  |  | X |X |
18 |  | |  |  |  | X |
19 |  |X |X |X |X |X |
20 |  | |  |  | X |X |

# Intel(R) Graphics Extensions feature list

Feature name | Platform supported | API Version | Version introduced |
------------ | ------------ | ------------ | ------------ |
[Multi Draw Indirect](#multi-draw-indirect) | Gen9 | 0 | 1.0 |
[Command Throttle Policy](#command-throttle-policy) | Gen9 | 0 | 1.0 |
[XeSS](#xess) | Gen9 | 0 | 1.0 |
[CPU Visible VRAM](#cpu-visible-vram) | Gen9 | 0 | 1.0 |
[UAV Overlap](#uav-overlap) | Gen9 | 1 | 1.1 |
[Depth Bounds Test](#depth-bounds-test) | Gen12LP | 2 | 3.2 |
[BVH CPU Build](#bvh-cpu-build) | Xe Architecture | 2 | 4.2 |
[Emulated Typed 64bit Atomics](#emulated-typed-64bit-atomics) | Gen12LP | 4 | 3.4 |
[Driver Metadata](#driver-metadata) | Gen9 | 4 | 1.4 |
[XeSS](#xess) | Gen12LP | 8 | 3.8 |
[Offline Compiler](#offline-compiler) | Xe Architecture | 9 | 4.9 |
[Application Discovery](#application-discovery) | Xe Architecture | 9 | 4.9 |
[Breadcrumbs](#breadcrumbs) | Xe Architecture | 14 | 4.14 |
[Retrieve Resource Driver Handle](#retrieve-resource-driver-handle) | Xe Architecture | 16 | 4.16 |
[GetCurrentShaderHeapUsage](#getcurrentshaderheapusage) | Xe Architecture | 18 | 4.18 |
[Tools Support](#tools-support) | Gen9 | 19 | 1.19 |
[Get Cached Blob](#get-cached-blob) | Xe Architecture | 20 | 4.20 |

# Intel(R) Graphics Extensions API list

List of all extensions (features) supported by the Intel Graphics Driver. The list contains the name of the extension and the list of all API entry points that are part of the extension implementation.

**<a id='multi-draw-indirect'>Multi Draw Indirect</a>**:
- [`INTC_D3D11_MultiDrawInstancedIndirect`](#intc_d3d11_multidrawinstancedindirect) - MultiDrawInstancedIndirect function submits multiple DrawInstancedIndirect in one call.

- [`INTC_D3D11_MultiDrawIndexedInstancedIndirect`](#intc_d3d11_multidrawindexedinstancedindirect) - MultiDrawIndexedInstancedIndirect function submits multiple DrawIndexedInstancedIndirect in one call.

- [`INTC_D3D11_MultiDrawInstancedIndirectCountIndirect`](#intc_d3d11_multidrawinstancedindirectcountindirect) - MultiDrawInstancedIndirect function submits multiple DrawInstancedIndirect in one call. The number of draws are passed using Draw Count Buffer. It must be less or equal the Max Count argument.

- [`INTC_D3D11_MultiDrawIndexedInstancedIndirectCountIndirect`](#intc_d3d11_multidrawindexedinstancedindirectcountindirect) - MultiDrawIndexedInstancedIndirect function submits multiple DrawInstancedIndirect in one call. The number of draws are passed using Draw Count Buffer. It must be less or equal the Max Count argument.


**<a id='command-throttle-policy'>Command Throttle Policy</a>**:
- [`INTC_D3D12_CreateCommandQueue`](#intc_d3d12_createcommandqueue) - Creates a command queue.


**<a id='xess'>XeSS</a>**:
- [`INTC_D3D12_CreateComputePipelineState`](#intc_d3d12_createcomputepipelinestate) - Creates a compute pipeline state object.


**<a id='cpu-visible-vram'>CPU Visible VRAM</a>**:
- [`INTC_D3D12_CreateReservedResource`](#intc_d3d12_createreservedresource) - Creates a resource that is reserved, which is not yet mapped to any pages in a heap.

- [`INTC_D3D12_CreateCommittedResource`](#intc_d3d12_createcommittedresource) - Creates both a resource and an implicit heap, such that the heap is big enough to contain the entire resource and the resource is mapped to the heap.

- [`INTC_D3D12_CreateCommittedResource1`](#intc_d3d12_createcommittedresource1) - Creates both a resource and an implicit heap, such that the heap is big enough to contain the entire resource and the resource is mapped to the heap.

- [`INTC_D3D12_CreateHeap`](#intc_d3d12_createheap) - Creates a heap.

- [`INTC_D3D12_CreatePlacedResource`](#intc_d3d12_createplacedresource) - Creates a resource that is placed in a specific heap.

- [`INTC_D3D12_QueryCpuVisibleVidmem`](#intc_d3d12_querycpuvisiblevidmem) - Queries total number of bytes and number of free bytes in CPU visible local memory.


**<a id='uav-overlap'>UAV Overlap</a>**:
- [`INTC_D3D11_BeginUAVOverlap`](#intc_d3d11_beginuavoverlap) - BeginUAVOverlap marks the beginning point for disabling GPU synchronization between consecutive draws and dispatches that share UAV resources.

- [`INTC_D3D11_EndUAVOverlap`](#intc_d3d11_enduavoverlap) - EndUAVOverlap marks the end point for disabling GPU synchronization between consecutive draws and dispatches that share UAV resources.


**<a id='depth-bounds-test'>Depth Bounds Test</a>**:
- [`INTC_D3D11_SetDepthBounds`](#intc_d3d11_setdepthbounds) - SetDepthBounds method enables you to change the depth bounds dynamically.


**<a id='bvh-cpu-build'>BVH CPU Build</a>**:
- [`INTC_D3D12_CreateHostRTASResource`](#intc_d3d12_createhostrtasresource) - Constructs a buffer resource suitable for storing raytracing acceleration structures build on the host.

- [`INTC_D3D12_BuildRaytracingAccelerationStructure_Host`](#intc_d3d12_buildraytracingaccelerationstructure_host) - Builds an acceleration structure on the host timeline.

- [`INTC_D3D12_CopyRaytracingAccelerationStructure_Host`](#intc_d3d12_copyraytracingaccelerationstructure_host) - Copies an acceleration structure on the host timeline.

- [`INTC_D3D12_EmitRaytracingAccelerationStructurePostbuildInfo_Host`](#intc_d3d12_emitraytracingaccelerationstructurepostbuildinfo_host) - Retrieves post-build info for a host-built AS on the host timeline.

- [`INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo_Host`](#intc_d3d12_getraytracingaccelerationstructureprebuildinfo_host) - Retrieves pre-build info for a host-built AS.

- [`INTC_D3D12_TransferHostRTAS`](#intc_d3d12_transferhostrtas) - Copy host-built acceleration structures to/from device memory on the GPU timeline.

- [`INTC_D3D12_CreateStateObject`](#intc_d3d12_createstateobject) - Creates an ID3D12StateObject.

- [`INTC_D3D12_BuildRaytracingAccelerationStructure`](#intc_d3d12_buildraytracingaccelerationstructure) - Performs a raytracing acceleration structure build on the GPU.

- [`INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo`](#intc_d3d12_getraytracingaccelerationstructureprebuildinfo) - Query the driver for resource requirements to build an acceleration structure.


**<a id='emulated-typed-64bit-atomics'>Emulated Typed 64bit Atomics</a>**:
- [`INTC_D3D11_CreateTexture2D`](#intc_d3d11_createtexture2d) - Create an array of 2D textures. Supported extensions: Emulated64bitTypedAtomics - Enable usage of 64bit Typed Atomics on a texture created.

- [`INTC_D3D12_CreateReservedResource`](#intc_d3d12_createreservedresource) - Creates a resource that is reserved, which is not yet mapped to any pages in a heap.

- [`INTC_D3D12_CreateCommittedResource`](#intc_d3d12_createcommittedresource) - Creates both a resource and an implicit heap, such that the heap is big enough to contain the entire resource and the resource is mapped to the heap.

- [`INTC_D3D12_CreateCommittedResource1`](#intc_d3d12_createcommittedresource1) - Creates both a resource and an implicit heap, such that the heap is big enough to contain the entire resource and the resource is mapped to the heap.

- [`INTC_D3D12_CreatePlacedResource`](#intc_d3d12_createplacedresource) - Creates a resource that is placed in a specific heap.

- [`INTC_D3D12_SetFeatureSupport`](#intc_d3d12_setfeaturesupport) - Sets feature support.

- [`INTC_D3D12_CheckFeatureSupport`](#intc_d3d12_checkfeaturesupport) - Gets information about the features that are supported by the current graphics driver.


**<a id='driver-metadata'>Driver Metadata</a>**:
- [`INTC_D3D12_SetDriverEventMetadata`](#intc_d3d12_setdrivereventmetadata) - Set Metadata associated with the CommandList.


**<a id='xess'>XeSS</a>**:
- [`INTC_D3D12_CheckFeatureSupport`](#intc_d3d12_checkfeaturesupport) - Gets information about the features that are supported by the current graphics driver.


**<a id='offline-compiler'>Offline Compiler</a>**:
- [`INTC_D3D12_AddShaderBinariesPath`](#intc_d3d12_addshaderbinariespath) - Sets a custom shader binary file path.

- [`INTC_D3D12_RemoveShaderBinariesPath`](#intc_d3d12_removeshaderbinariespath) - Removes a custom shader binary file path.


**<a id='application-discovery'>Application Discovery</a>**:
- [`INTC_D3D12_SetApplicationInfo`](#intc_d3d12_setapplicationinfo) - Register Application Info in the graphics driver.


**<a id='breadcrumbs'>Breadcrumbs</a>**:
- [`INTC_D3D12_GetCommandListHandle`](#intc_d3d12_getcommandlisthandle) - Obtains an Graphics Extensions CommandListHandle associated with the D3D12 CommandList Object.

- [`INTC_D3D12_SetEventMarker`](#intc_d3d12_seteventmarker) - Places a marker in the Command List. Markers (breadcrumbs) are then decoded in the GPU crash dump.

- [`INTC_EnableGpuCrashDumps`](#intc_enablegpucrashdumps) - Enables Intel Breadcrumbs GPU crash dumps - should be called *before* device creation.

- [`INTC_IsGpuCrashDumpsEnabled`](#intc_isgpucrashdumpsenabled) - Used to determine if application GPU crash dumps are enabled.

- [`INTC_DisableGpuCrashDumps`](#intc_disablegpucrashdumps) - Disables Intel Breadcrumbs GPU crash dumps.

- [`INTC_GetGpuCrashDump`](#intc_getgpucrashdump) - Checks the status of the GPU Crash Dump.

- [`INTC_DecodeGpuCrashDump`](#intc_decodegpucrashdump) - Decodes the GPU Crash Dump and generates a text with the crash dump information.

- [`INTC_RetrieveGpuCrashDump`](#intc_retrievegpucrashdump) - Retrieves the GPU Crash Dump information in a structured format for further processing.

- [`INTC_LoadGpuCrashDump`](#intc_loadgpucrashdump) - Loads the binary GPU Crash Dump data.


**<a id='retrieve-resource-driver-handle'>Retrieve Resource Driver Handle</a>**:
- [`INTC_D3D11_Begin_Retrieve_Resource_Handle`](#intc_d3d11_begin_retrieve_resource_handle) - Begin_Retrieve_Resource_Handle marks the beginning point for retrieving the resource driver handle, it turns on the handle retrieval flag. flag off means no subsequent resource handle retrieval, thus no performance impact for normal resource creation flow.

- [`INTC_D3D11_End_Retrieve_Resource_Handle`](#intc_d3d11_end_retrieve_resource_handle) - End_Retrieve_Resource_Handle marks the end point for retrieving the resource driver handle, it writes the resource handle to the destination memory where the application provides.


**<a id='getcurrentshaderheapusage'>GetCurrentShaderHeapUsage</a>**:
- [`INTC_D3D12_GetCurrentShaderHeapUsage`](#intc_d3d12_getcurrentshaderheapusage) - Returns the current shader heap usage.


**<a id='tools-support'>Tools Support</a>**:
- [`INTC_D3D12_SetDeviceParams`](#intc_d3d12_setdeviceparams) - Sets additional device information for the next/current D3D12 device.


**<a id='get-cached-blob'>Get Cached Blob</a>**:
- [`INTC_D3D12_GetCachedBlob`](#intc_d3d12_getcachedblob) - Gets the cached blob representing the pipeline state.



# Intel(R) Graphics Extensions API Reference

**API Version 0**:  
- `INTC_D3D11_MultiDrawInstancedIndirect`
- `INTC_D3D11_MultiDrawIndexedInstancedIndirect`
- `INTC_D3D11_MultiDrawInstancedIndirectCountIndirect`
- `INTC_D3D11_MultiDrawIndexedInstancedIndirectCountIndirect`
- `INTC_D3D12_CreateCommandQueue`
- `INTC_D3D12_CreateComputePipelineState`
- `INTC_D3D12_CreateReservedResource`

**API Version 1**:  
- `INTC_D3D11_BeginUAVOverlap`
- `INTC_D3D11_EndUAVOverlap`

**API Version 2**:  
- `INTC_D3D11_SetDepthBounds`
- `INTC_D3D12_CreateHostRTASResource`
- `INTC_D3D12_BuildRaytracingAccelerationStructure_Host`
- `INTC_D3D12_CopyRaytracingAccelerationStructure_Host`
- `INTC_D3D12_EmitRaytracingAccelerationStructurePostbuildInfo_Host`
- `INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo_Host`
- `INTC_D3D12_TransferHostRTAS`

**API Version 4**:  
- `INTC_D3D11_CreateTexture2D`
- `INTC_D3D12_CreateCommittedResource`
- `INTC_D3D12_CreatePlacedResource`
- `INTC_D3D12_SetDriverEventMetadata`

**API Version 5**:  
- `INTC_D3D12_CreateCommittedResource1`
- `INTC_D3D12_CreateHeap`
- `INTC_D3D12_QueryCpuVisibleVidmem`

**API Version 6**:  
- `INTC_D3D12_CreateStateObject`
- `INTC_D3D12_BuildRaytracingAccelerationStructure`
- `INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo`

**API Version 7**:  
- `INTC_D3D12_SetFeatureSupport`
- `INTC_D3D12_GetResourceAllocationInfo`

**API Version 8**:  
- `INTC_D3D12_CheckFeatureSupport`

**API Version 9**:  
- `INTC_D3D12_AddShaderBinariesPath`
- `INTC_D3D12_RemoveShaderBinariesPath`
- `INTC_D3D12_SetApplicationInfo`

**API Version 10**:  

**API Version 11**:  

**API Version 12**:  
- `INTC_D3D12_SetEventMarker`
- `INTC_IsGpuCrashDumpsEnabled`
- `INTC_DisableGpuCrashDumps`
- `INTC_GetGpuCrashDump`
- `INTC_DecodeGpuCrashDump`
- `INTC_RetrieveGpuCrashDump`
- `INTC_LoadGpuCrashDump`

**API Version 13**:  

**API Version 14**:  
- `INTC_D3D12_GetCommandListHandle`
- `INTC_EnableGpuCrashDumps`

**API Version 15**:  
- `INTC_D3D11_RegisterApplicationCallbacks`
- `INTC_D3D12_RegisterApplicationCallbacks`

**API Version 16**:  
- `INTC_D3D11_Begin_Retrieve_Resource_Handle`
- `INTC_D3D11_End_Retrieve_Resource_Handle`

**API Version 18**:  
- `INTC_D3D12_GetCurrentShaderHeapUsage`

**API Version 19**:  
- `INTC_D3D12_SetDeviceParams`
- `INTC_D3D12_RegisterApplicationCallbacks1`

**API Version 20**:  
- `INTC_D3D12_GetCachedBlob`


# API Documentation

This section contains the documentation for the Graphics Extensions SDK entry points supported by the Intel Graphics Driver. Every entry point has a Doxygen style documentation that describes the purpose of the entry point, the parameters, and the return value. This documentation is auto-generated.



# Enumerations

### INTC_GPU_CRASH_FLAGS:
GPU Crash Flags
- **INTC_GPU_CRASH_FLAG_MARKERS** = 1 - Markers
- **INTC_GPU_CRASH_FLAG_RESOURCE_TRACKING** = 2 - Resource Tracking
- **INTC_GPU_CRASH_FLAG_SHADER_DEBUG_INFO** = 4 - Shader Debug Info
- **INTC_GPU_CRASH_FLAG_CALL_STACK** = 8 - Call Stack
### INTC_CRASHDUMP_STATUS:
Crashdump Status
- **INTC_CRASHDUMP_STATUS_NOT_READY** = 0 - Not Ready
- **INTC_CRASHDUMP_STATUS_READY** = 1 - Ready
### INTC_CRASHDUMP_SECTION_TYPE:
Crashdump Section Type
- **INTC_CRASHDUMP_SECTION_TYPE_BLOB** = 1 - Crash Dump Blob
- **INTC_CRASHDUMP_SECTION_TYPE_MARKERS** = 2 - Markers
- **INTC_CRASHDUMP_SECTION_TYPE_PAGEFAULT** = 3 - Pagefault
- **INTC_CRASHDUMP_SECTION_TYPE_SHADER_DEBUG_INFO** = 4 - Shader Debug Info
- **INTC_CRASHDUMP_SECTION_TYPE_CALL_STACK** = 5 - Call Stack
### INTC_EVENT_MARKER_EVENT:
Event Marker Event
- **INTC_EVENT_MARKER** = 1 - Event Marker
- **INTC_EVENT_MARKER_BEGIN** = 2 - Event Marker Begin
- **INTC_EVENT_MARKER_END** = 4 - Event Marker End
- **INTC_EVENT_MARKER_BUFFER** = 8 - Event Marker Buffer
- **INTC_EVENT_MARKER_STRING** = 16 - Event Marker String
- **INTC_EVENT_MARKER_WSTRING** = 32 - Event Marker WString
- **INTC_EVENT_MARKER_PTR** = 64 - Event Marker Pointer
### INTC_D3D12_COMMAND_QUEUE_THROTTLE_POLICY:
Command Queue Throttle Policy
- **INTC_D3D12_COMMAND_QUEUE_THROTTLE_DYNAMIC** = 0 - Dynamic
- **INTC_D3D12_COMMAND_QUEUE_THROTTLE_MAX_PERFORMANCE** = 255 - Max Performance
### INTC_D3D12_SHADER_INPUT_TYPE:
Shader Input Type
- **NONE** = 0 - None
- **CM** = 1 - CM
- **CM_SPIRV** = 2 - CM SPIRV
- **OpenCL** = 3 - OpenCL
- **SPIRV** = 4 - SPIRV
- **HLSL** = 5 - HLSL
- **CL_BIN** = 6 - CL BIN
- **ESIMD_SPIRV** = 7 - ESIMD SPIRV
- **ZEBIN_ELF** = 8 - ZEBIN ELF
### INTC_D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC_TYPE:
Build Raytracing Acceleration Structure Descriptor Type
- **D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC_EXT_INSTANCE_COMPARISON** = 0 - Instance Comparison
### INTC_D3D12_FEATURES:
Intel D3D12 Features
- **INTC_D3D12_FEATURE_D3D12_OPTIONS1** = 0 - D3D12 Options 1
- **INTC_D3D12_FEATURE_D3D12_OPTIONS2** = 1 - D3D12 Options 2
- **INTC_D3D12_FEATURE_D3D12_OPTIONS3** = 2 - D3D12 Options 3
### INTC_D3D12_CACHED_BLOB_FLAGS:
Cached Blob Flags
- **INTC_D3D12_CACHED_BLOB_FLAG_NONE** = 0 - Regular shader blob retrieval
- **INTC_D3D12_CACHED_BLOB_FLAG_STAGE_2** = 1 - Stage-2 shader blob retrieval
- **INTC_D3D12_CACHED_BLOB_FLAG_WAIT_FOR_READY** = 2 - Return only when the shader blob is ready

# Functions declarations

GPU Crash Dump Callback
```cpp
typedef void (*PFNINTC_GPUCRASHDUMPCB)(
    const void* pBuffer,
    const uint32_t bufferSize,
    void* pPrivateData
);
```
- `pBuffer` - Pointer to the buffer containing the crash dump data.
- `bufferSize` - Size of the buffer.
- `pPrivateData` - Pointer to private data.

Shader Debug Callback
```cpp
typedef void (*PFNINTC_SHADERDEBUGCB)(
    const void* pBuffer,
    uint32_t bufferSize,
    void* pPrivateData
);
```
- `pBuffer` - Pointer to the buffer containing the shader debug data.
- `bufferSize` - Size of the buffer.
- `pPrivateData` - Pointer to private data.

Resolve Marker Callback
```cpp
typedef void (*PFNINTC_RESOLVEMARKERCB)(
    const void* pBuffer,
    uint32_t bufferSize,
    void* pPrivateData,
    void** ppResolvedBuffer,
    uint32_t* pResolvedBufferSize
);
```
- `pBuffer` - Pointer to the buffer containing the marker data.
- `bufferSize` - Size of the buffer.
- `pPrivateData` - Pointer to private data.
- `ppResolvedBuffer` - Pointer to the resolved buffer.
- `pResolvedBufferSize` - Pointer to the size of the resolved buffer.



# Structures

**`INTC_CALLBACKS`**:  
GPU Crash Dump callback functions  
- `GPUCrashDumpCb` - GPU Crash Dump callback
- `ShaderDebugCb` - Shader Debug callback
- `ResolveMarkerCb` - Resolve Marker callback

**`INTC_CRASHDUMP_BREADCRUMB_DATA`**:  
Crashdump Breadcrumb Data  
- `eventType` - Event type
- `buffer` - Pointer to the buffer
- `bufferSize` - Buffer size
- `pMarkerName` - Marker name
- `completed` - Flag indicating if the event is completed

**`INTC_CRASHDUMP_SECTION`**:  
Crashdump Section  
- `sectionType` - Section type
- `pSectionInfo` - Section information
- `dataEntryCount` - Section size
- `pDataEntry` - Pointer to the section data

**`INTC_CRASHDUMP_INFO`**:  
Crashdump Information  
- `status` - Crashdump status
- `crashDumpSectionCount` - Crashdump section count
- `pCrashDumpSections` - Pointer to the crashdump sections

**`INTC_D3D11_TEXTURE2D_DESC`**:  
Texture2D Descriptor for D3D11  
- `None` - None
- `EmulatedTyped64bitAtomics` - Emulated Typed 64bit Atomics

**`INTC_D3D12_COMMAND_QUEUE_DESC_0001`**:  
Command Queue Descriptor  
- `None` - None
- `CommandThrottlePolicy` - Command Queue Throttle Policy

**`INTC_D3D12_COMMAND_QUEUE_DESC`**:  
Command Queue Descriptor  

**`INTC_D3D12_COMPUTE_PIPELINE_STATE_DESC`**:  
Compute Pipeline State Descriptor  
- `None` - None
- `CS` - Compute Shader Bytecode
- `ShaderInputType` - Input Shader Type
- `CompileOptions` - Compilation Options
- `InternalOptions` - Internal CrossCompile Options

**`INTC_D3D12_RESOURCE_DESC`**:  
Resource Descriptor  
- `None` - None
- `Texture2DArrayMipPack` - Reserved Resources Texture2D Array with Mip Packing

**`INTC_D3D12_RESOURCE_DESC_0001`**:  
Resource Descriptor with Emulated Typed 64bit Atomics  
- `EmulatedTyped64bitAtomics` - Emulated Typed 64bit Atomics

**`INTC_D3D12_RESOURCE_DESC_0002`**:  
Resource Descriptor with Cpu Visible Video Memory  
- `ResourceFlagCpuVisibleVideoMemory` - Cpu Visible Video Memory

**`INTC_D3D12_HEAP_DESC`**:  
Heap Descriptor  
- `None` - None
- `HeapFlagCpuVisibleVideoMemory` - Cpu Visible Video Memory

**`INTC_D3D12_STATE_OBJECT_DESC`**:  
Raytracing Pipeline State Object Descriptor  
- `None` - None
- `DXILLibrary` - Raytracing Shader Byte code
- `numLibraries` - Number of libraries

**`INTC_D3D12_INSTANCE_COMPARISON_DATA`**:  
Instance Comparison Data  
- `InstanceValue:8` - Instance Value
- `InstanceComparisonOperator:8` - Instance Comparison Operator

**`INTC_D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC_INSTANCE_COMPARISON_DATA`**:  
Build Raytracing Acceleration Structure Descriptor Instance Comparison Data  
- `pNext` - Pointer to next extension or 0
- `ExtType` - Type of the extension
- `InstanceComparisonData` - GPU virtual address of a buffer that contains an array of INTC_D3D12_INSTANCE_COMPARISON_DATA

**`INTC_D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC`**:  
Build Raytracing Acceleration Structure Descriptor  
- `None` - None
- `pCompDataDesc` - Pointer to the comparison data descriptor

**`INTC_D3D12_GET_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILDINFO_DESC`**:  
Get Raytracing Acceleration Structure Prebuild Info Descriptor  
- `None` - None
- `pCompDataDesc` - Pointer to the comparison data descriptor

**`INTC_D3D12_FEATURE`**:  
Feature  
- `EmulatedTyped64bitAtomics` - Emulated Typed 64bit Atomics

**`INTC_D3D12_FEATURE_DATA_D3D12_OPTIONS1`**:  
Feature Data D3D12 Options 1  
- `XMXEnabled` - XMX Enabled
- `DLBoostEnabled` - DL Boost Enabled
- `EmulatedTyped64bitAtomics` - Emulated Typed 64bit Atomics

**`INTC_D3D12_FEATURE_DATA_D3D12_OPTIONS2`**:  
Feature Data D3D12 Options 2  
- `SIMD16Required` - SIMD16 Required
- `LSCSupported` - LSC Supported
- `LegacyTranslationRequired` - Legacy Translation Required

**`INTC_D3D12_FEATURE_DATA_D3D12_OPTIONS3`**:  
Feature Data D3D12 Options 3  
- `AsyncCompute` - Async Compute Supported (Efficient Async Compute)


# API Entry Points

<a id='intc_d3d11_beginuavoverlap'>**`INTC_D3D11_BeginUAVOverlap`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D11_BeginUAVOverlap(
    INTCExtensionContext* pExtensionContext )
```
**Description:**  
BeginUAVOverlap marks the beginning point for disabling GPU synchronization between consecutive draws and dispatches that share UAV resources.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d11_enduavoverlap'>**`INTC_D3D11_EndUAVOverlap`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D11_EndUAVOverlap(
    INTCExtensionContext* pExtensionContext )
```
**Description:**  
EndUAVOverlap marks the end point for disabling GPU synchronization between consecutive draws and dispatches that share UAV resources.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d11_begin_retrieve_resource_handle'>**`INTC_D3D11_Begin_Retrieve_Resource_Handle`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D11_Begin_Retrieve_Resource_Handle(
    INTCExtensionContext* pExtensionContext )
```
**Description:**  
Begin_Retrieve_Resource_Handle marks the beginning point for retrieving the resource driver handle, it turns on the handle retrieval flag. flag off means no subsequent resource handle retrieval, thus no performance impact for normal resource creation flow.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d11_end_retrieve_resource_handle'>**`INTC_D3D11_End_Retrieve_Resource_Handle`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D11_End_Retrieve_Resource_Handle(
    INTCExtensionContext* pExtensionContext )
```
**Description:**  
End_Retrieve_Resource_Handle marks the end point for retrieving the resource driver handle, it writes the resource handle to the destination memory where the application provides.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d11_multidrawinstancedindirect'>**`INTC_D3D11_MultiDrawInstancedIndirect`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D11_MultiDrawInstancedIndirect(
    INTCExtensionContext* pExtensionContext,
    ID3D11DeviceContext* pDeviceContext,
    UINT drawCount,
    ID3D11Buffer* pBufferForArgs,
    UINT alignedByteOffsetForArgs,
    UINT byteStrideForArgs )
```
**Description:**  
MultiDrawInstancedIndirect function submits multiple DrawInstancedIndirect in one call.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDeviceContext` - A pointer to the device context that will be used to generate rendering commands.
- `drawCount` - The number of draws.
- `pBufferForArgs` - Pointer to the Arguments Buffer.
- `alignedByteOffsetForArgs` - Offset into the Arguments Buffer.
- `byteStrideForArgs` - The stride between elements in the Argument Buffer.

**Return:**  
- `void` - None


<a id='intc_d3d11_multidrawindexedinstancedindirect'>**`INTC_D3D11_MultiDrawIndexedInstancedIndirect`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D11_MultiDrawIndexedInstancedIndirect(
    INTCExtensionContext* pExtensionContext,
    ID3D11DeviceContext* pDeviceContext,
    UINT drawCount,
    ID3D11Buffer* pBufferForArgs,
    UINT alignedByteOffsetForArgs,
    UINT byteStrideForArgs )
```
**Description:**  
MultiDrawIndexedInstancedIndirect function submits multiple DrawIndexedInstancedIndirect in one call.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDeviceContext` - A pointer to the device context that will be used to generate rendering commands.
- `drawCount` - The number of draws.
- `pBufferForArgs` - Pointer to the Arguments Buffer.
- `alignedByteOffsetForArgs` - Offset into the Arguments Buffer.
- `byteStrideForArgs` - The stride between elements in the Argument Buffer.

**Return:**  
- `void` - None


<a id='intc_d3d11_multidrawinstancedindirectcountindirect'>**`INTC_D3D11_MultiDrawInstancedIndirectCountIndirect`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D11_MultiDrawInstancedIndirectCountIndirect(
    INTCExtensionContext* pExtensionContext,
    ID3D11DeviceContext* pDeviceContext,
    ID3D11Buffer* pBufferForDrawCount,
    UINT alignedByteOffsetForDrawCount,
    UINT maxCount,
    ID3D11Buffer* pBufferForArgs,
    UINT alignedByteOffsetForArgs,
    UINT byteStrideForArgs )
```
**Description:**  
MultiDrawInstancedIndirect function submits multiple DrawInstancedIndirect in one call. The number of draws are passed using Draw Count Buffer. It must be less or equal the Max Count argument.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDeviceContext` - A pointer to the device context that will be used to generate rendering commands.
- `pBufferForDrawCount` - Buffer that contains the number of draws.
- `alignedByteOffsetForDrawCount` - Offset into the Draw Count Buffer.
- `maxCount` - Maximum count of draws generated by this call.
- `pBufferForArgs` - Pointer to the Arguments Buffer.
- `alignedByteOffsetForArgs` - Offset into the Arguments Buffer.
- `byteStrideForArgs` - The stride between elements in the Argument Buffer.

**Return:**  
- `void` - None


<a id='intc_d3d11_multidrawindexedinstancedindirectcountindirect'>**`INTC_D3D11_MultiDrawIndexedInstancedIndirectCountIndirect`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D11_MultiDrawIndexedInstancedIndirectCountIndirect(
    INTCExtensionContext* pExtensionContext,
    ID3D11DeviceContext* pDeviceContext,
    ID3D11Buffer* pBufferForDrawCount,
    UINT alignedByteOffsetForDrawCount,
    UINT maxCount,
    ID3D11Buffer* pBufferForArgs,
    UINT alignedByteOffsetForArgs,
    UINT byteStrideForArgs )
```
**Description:**  
MultiDrawIndexedInstancedIndirect function submits multiple DrawInstancedIndirect in one call. The number of draws are passed using Draw Count Buffer. It must be less or equal the Max Count argument.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDeviceContext` - A pointer to the device context that will be used to generate rendering commands.
- `pBufferForDrawCount` - Buffer that contains the number of draws.
- `alignedByteOffsetForDrawCount` - Offset into the Draw Count Buffer.
- `maxCount` - Maximum count of draws generated by this call.
- `pBufferForArgs` - Pointer to the Arguments Buffer.
- `alignedByteOffsetForArgs` - Offset into the Arguments Buffer.
- `byteStrideForArgs` - The stride between elements in the Argument Buffer.

**Return:**  
- `void` - None


<a id='intc_d3d11_setdepthbounds'>**`INTC_D3D11_SetDepthBounds`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D11_SetDepthBounds(
    INTCExtensionContext* pExtensionContext,
    BOOL bEnable,
    FLOAT Min,
    FLOAT Max )
```
**Description:**  
SetDepthBounds method enables you to change the depth bounds dynamically.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `bEnable` - Enable or disable depth bounds test.
- `Min` - Specifies the minimum depth bounds. The default value is 0. NaN values silently convert to 0.
- `Max` - Specifies the maximum depth bounds. The default value is 1. NaN values silently convert to 0.

**Return:**  
- `void` - None


<a id='intc_d3d11_createtexture2d'>**`INTC_D3D11_CreateTexture2D`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D11_CreateTexture2D(
    INTCExtensionContext* pExtensionContext,
    const INTC_D3D11_TEXTURE2D_DESC* pDesc,
    const D3D11_SUBRESOURCE_DATA* pInitialData,
    ID3D11Texture2D** ppTexture2D )
```
**Description:**  
Create an array of 2D textures. Supported extensions: Emulated64bitTypedAtomics - Enable usage of 64bit Typed Atomics on a texture created.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDesc` - A pointer to a INTC_D3D11_TEXTURE2D_DESC structure that describes a 2D texture resource.
- `pInitialData` - A pointer to an array of D3D11_SUBRESOURCE_DATA structures that describe subresources for the 2D texture resource.
- `ppTexture2D` - A pointer to a buffer that receives a pointer to a ID3D11Texture2D interface for the created texture.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_createcommandqueue'>**`INTC_D3D12_CreateCommandQueue`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_CreateCommandQueue(
    INTCExtensionContext* pExtensionContext,
    const INTC_D3D12_COMMAND_QUEUE_DESC* pDesc,
    REFIID riid,
    void** ppCommandQueue )
```
**Description:**  
Creates a command queue.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDesc` - A pointer to a D3D12_COMPUTE_PIPELINE_STATE_DESC structure that describes compute pipeline state.
- `riid` - The globally unique identifier (GUID) for the command queue interface.
- `ppCommandQueue` - A pointer to a memory block that receives a pointer to the ID3D12CommandQueue interface for the command queue.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_createcomputepipelinestate'>**`INTC_D3D12_CreateComputePipelineState`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_CreateComputePipelineState(
    INTCExtensionContext* pExtensionContext,
    const INTC_D3D12_COMPUTE_PIPELINE_STATE_DESC* pDesc,
    REFIID riid,
    void** ppPipelineState )
```
**Description:**  
Creates a compute pipeline state object.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDesc` - A pointer to a D3D12_COMPUTE_PIPELINE_STATE_DESC structure that describes compute pipeline state.
- `riid` - The globally unique identifier (GUID) for the pipeline state interface.
- `ppPipelineState` - A pointer to a memory block that receives a pointer to the ID3D12PipelineState interface for the pipeline state object.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_createreservedresource'>**`INTC_D3D12_CreateReservedResource`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_CreateReservedResource(
    INTCExtensionContext* pExtensionContext,
    const INTC_D3D12_RESOURCE_DESC* pDesc,
    D3D12_RESOURCE_STATES InitialState,
    const D3D12_CLEAR_VALUE* pOptimizedClearValue,
    REFIID riid,
    void** ppvResource )
```
**Description:**  
Creates a resource that is reserved, which is not yet mapped to any pages in a heap.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDesc` - A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
- `InitialState` - The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
- `pOptimizedClearValue` - Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
- `riid` - The globally unique identifier (GUID) for the resource interface.
- `ppvResource` - A pointer to a memory block that receives a pointer to the resource.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_createcommittedresource'>**`INTC_D3D12_CreateCommittedResource`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_CreateCommittedResource(
    INTCExtensionContext* pExtensionContext,
    const D3D12_HEAP_PROPERTIES* pHeapProperties,
    D3D12_HEAP_FLAGS HeapFlags,
    const INTC_D3D12_RESOURCE_DESC_0001* pDesc,
    D3D12_RESOURCE_STATES InitialResourceState,
    const D3D12_CLEAR_VALUE* pOptimizedClearValue,
    REFIID riidResource,
    void** ppvResource )
```
**Description:**  
Creates both a resource and an implicit heap, such that the heap is big enough to contain the entire resource and the resource is mapped to the heap.  

**Arguments:**  
- `pExtensionContext` - A pointer to a D3D12_HEAP_PROPERTIES structure that provides properties for the resource's heap.
- `pHeapProperties` - A pointer to the ID3D12Heap interface that represents the heap in which the resource is placed.
- `HeapFlags` - The offset, in bytes, to the resource.
- `pDesc` - A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
- `InitialResourceState` - The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
- `pOptimizedClearValue` - Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
- `riidResource` - The globally unique identifier (GUID) for the resource interface.
- `ppvResource` - A pointer to memory that receives the requested interface pointer to the created resource object.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_createcommittedresource1'>**`INTC_D3D12_CreateCommittedResource1`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_CreateCommittedResource1(
    INTCExtensionContext* pExtensionContext,
    const D3D12_HEAP_PROPERTIES* pHeapProperties,
    D3D12_HEAP_FLAGS HeapFlags,
    const INTC_D3D12_RESOURCE_DESC_0002* pDesc,
    D3D12_RESOURCE_STATES InitialResourceState,
    const D3D12_CLEAR_VALUE* pOptimizedClearValue,
    REFIID riidResource,
    void** ppvResource )
```
**Description:**  
Creates both a resource and an implicit heap, such that the heap is big enough to contain the entire resource and the resource is mapped to the heap.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pHeapProperties` - A pointer to the ID3D12Heap interface that represents the heap in which the resource is placed.
- `HeapFlags` - The offset, in bytes, to the resource.
- `pDesc` - A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
- `InitialResourceState` - The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
- `pOptimizedClearValue` - Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
- `riidResource` - The globally unique identifier (GUID) for the resource interface.
- `ppvResource` - A pointer to memory that receives the requested interface pointer to the created resource object.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_createheap'>**`INTC_D3D12_CreateHeap`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_CreateHeap(
    INTCExtensionContext* pExtensionContext,
    const INTC_D3D12_HEAP_DESC* pDesc,
    REFIID riid,
    void** ppvHeap )
```
**Description:**  
Creates a heap.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDesc` - A pointer to a overridden D3D12_HEAP_DESC structure that describes the heap.
- `riid` - The globally unique identifier (GUID) for the heap interface.
- `ppvHeap` - A pointer to a memory block that receives a pointer to the heap.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_createplacedresource'>**`INTC_D3D12_CreatePlacedResource`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_CreatePlacedResource(
    INTCExtensionContext* pExtensionContext,
    ID3D12Heap* pHeap,
    UINT64 HeapOffset,
    const INTC_D3D12_RESOURCE_DESC_0001* pDesc,
    D3D12_RESOURCE_STATES InitialState,
    const D3D12_CLEAR_VALUE* pOptimizedClearValue,
    REFIID riid,
    void** ppvResource )
```
**Description:**  
Creates a resource that is placed in a specific heap.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pHeap` - A pointer to the ID3D12Heap interface that represents the heap in which the resource is placed.
- `HeapOffset` - The offset, in bytes, to the resource.
- `pDesc` - A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
- `InitialState` - The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
- `pOptimizedClearValue` - Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
- `riid` - The globally unique identifier (GUID) for the resource interface.
- `ppvResource` - A pointer to a memory block that receives a pointer to the resource.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_createhostrtasresource'>**`INTC_D3D12_CreateHostRTASResource`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_CreateHostRTASResource(
    INTCExtensionContext* pExtensionContext,
    size_t SizeInBytes,
    DWORD Flags,
    REFIID riidResource,
    void** ppvResource )
```
**Description:**  
Constructs a buffer resource suitable for storing raytracing acceleration structures build on the host.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `SizeInBytes` - Size of the resource, in bytes.
- `Flags` - Reserved, must be zero.
- `riidResource` - Interface id for the returned resource.
- `ppvResource` - Pointer to a pointer which is set to the output resource.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_buildraytracingaccelerationstructure_host'>**`INTC_D3D12_BuildRaytracingAccelerationStructure_Host`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D12_BuildRaytracingAccelerationStructure_Host(
    INTCExtensionContext* pExtensionContext,
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC* pDesc,
    const D3D12_GPU_VIRTUAL_ADDRESS* pInstanceGPUVAs,
    UINT NumInstances )
```
**Description:**  
Builds an acceleration structure on the host timeline.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDesc` - An acceleration structure description. All GPUVA fields contained in the description are interpreted as host pointers cast to uintptr_t.
- `pInstanceGPUVAs` - For a top-level AS, this contains the GPUVA of the bottom-level AS for each instance which will be used for ray traversal.
- `NumInstances` - Number of addresses in 'pInstanceGPUVAs'.

**Return:**  
- `void` - None


<a id='intc_d3d12_copyraytracingaccelerationstructure_host'>**`INTC_D3D12_CopyRaytracingAccelerationStructure_Host`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D12_CopyRaytracingAccelerationStructure_Host(
    INTCExtensionContext* pExtensionContext,
    void* DestAccelerationStructureData,
    const void* SourceAccelerationStructureData,
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode )
```
**Description:**  
Copies an acceleration structure on the host timeline.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `DestAccelerationStructureData` - Pointer to destination AS. Must point into a mapped Host RTAS resource.
- `SourceAccelerationStructureData` - Pointer to source AS. Must point into a mapped Host RTAS resource.
- `Mode` - See DXR spec.

**Return:**  
- `void` - None


<a id='intc_d3d12_emitraytracingaccelerationstructurepostbuildinfo_host'>**`INTC_D3D12_EmitRaytracingAccelerationStructurePostbuildInfo_Host`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D12_EmitRaytracingAccelerationStructurePostbuildInfo_Host(
    INTCExtensionContext* pExtensionContext,
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE InfoType,
    void* DestBuffer,
    const void* SourceRTAS )
```
**Description:**  
Retrieves post-build info for a host-built AS on the host timeline.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `InfoType` - See DXR spec.
- `DestBuffer` - Pointer to output structure (see DXR spec).
- `SourceRTAS` - Pointer to source RTAS. Must lie within a Host rtas resource.

**Return:**  
- `void` - None


<a id='intc_d3d12_getraytracingaccelerationstructureprebuildinfo_host'>**`INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo_Host`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo_Host(
    INTCExtensionContext* pExtensionContext,
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS* pDesc,
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO* pInfo )
```
**Description:**  
Retrieves pre-build info for a host-built AS.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDesc` - See DXR spec.
- `pInfo` - See DXR spec. This function gives the AS and scratch sizes for a host-built AS, which might not match the device-built equivalents.

**Return:**  
- `void` - None


<a id='intc_d3d12_transferhostrtas'>**`INTC_D3D12_TransferHostRTAS`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D12_TransferHostRTAS(
    INTCExtensionContext* pExtensionContext,
    ID3D12GraphicsCommandList* pCommandList,
    D3D12_GPU_VIRTUAL_ADDRESS DestAccelerationStructureData,
    D3D12_GPU_VIRTUAL_ADDRESS SrcAccelerationStructureData,
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode )
```
**Description:**  
Copy host-built acceleration structures to/from device memory on the GPU timeline.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pCommandList` - A command list to receive copy commands.
- `DestAccelerationStructureData` - GPU address of destination.
- `SrcAccelerationStructureData` - GPU address of source.
- `Mode` - See DXR spec. At least one of Dest and Src must be a Host RTAS resource. The other must be a conventional DXR acceleration structure buffer.

**Return:**  
- `void` - None


<a id='intc_d3d12_setdrivereventmetadata'>**`INTC_D3D12_SetDriverEventMetadata`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D12_SetDriverEventMetadata(
    INTCExtensionContext* pExtensionContext,
    ID3D12GraphicsCommandList* pCommandList,
    UINT64 Metadata )
```
**Description:**  
Set Metadata associated with the CommandList.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pCommandList` - A command list to set metadata.
- `Metadata` - Metadata.

**Return:**  
- `void` - None


<a id='intc_d3d12_querycpuvisiblevidmem'>**`INTC_D3D12_QueryCpuVisibleVidmem`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D12_QueryCpuVisibleVidmem(
    INTCExtensionContext* pExtensionContext,
    UINT64* pTotalBytes,
    UINT64* pFreeBytes )
```
**Description:**  
Queries total number of bytes and number of free bytes in CPU visible local memory.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pTotalBytes` - A pointer to total number of bytes in CPU visible vidmem.
- `pFreeBytes` - A pointer to number of free bytes in CPU visible vidmem.

**Return:**  
- `void` - None


<a id='intc_d3d12_createstateobject'>**`INTC_D3D12_CreateStateObject`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_CreateStateObject(
    INTCExtensionContext* pExtensionContext,
    const INTC_D3D12_STATE_OBJECT_DESC* pDesc,
    REFIID riid,
    void** ppPipelineState )
```
**Description:**  
Creates an ID3D12StateObject.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDesc` - The description of the state object to create.
- `riid` - The GUID of the interface to create.
- `ppPipelineState` - The returned Raytracing pipeline state object.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_buildraytracingaccelerationstructure'>**`INTC_D3D12_BuildRaytracingAccelerationStructure`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D12_BuildRaytracingAccelerationStructure(
    INTCExtensionContext* pExtensionContext,
    ID3D12GraphicsCommandList* pCommandList,
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC* pDesc,
    UINT NumPostbuildInfoDescs,
    const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC* pPostbuildInfoDescs,
    const INTC_D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC_INSTANCE_COMPARISON_DATA* pComparisonDataDesc )
```
**Description:**  
Performs a raytracing acceleration structure build on the GPU.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pCommandList` - A command list to build acceleration structure.
- `pDesc` - Description of the acceleration structure to build.
- `NumPostbuildInfoDescs` - Size of the pPostbuildInfoDescs array.
- `pPostbuildInfoDescs` - Optional array of descriptions for post-build info to generate describing properties of the acceleration structure that was built.
- `pComparisonDataDesc` - Description of the comparison data.

**Return:**  
- `void` - None


<a id='intc_d3d12_getraytracingaccelerationstructureprebuildinfo'>**`INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo(
    INTCExtensionContext* pExtensionContext,
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS* pDesc,
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO* pInfo,
    const INTC_D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC_INSTANCE_COMPARISON_DATA* pComparisonDataDesc )
```
**Description:**  
Query the driver for resource requirements to build an acceleration structure.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pDesc` - Description of the acceleration structure build.
- `pInfo` - The result of the query.
- `pComparisonDataDesc` - Description of the comparison data.

**Return:**  
- `void` - None


<a id='intc_d3d12_setfeaturesupport'>**`INTC_D3D12_SetFeatureSupport`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_SetFeatureSupport(
    INTCExtensionContext* pExtensionContext,
    INTC_D3D12_FEATURE* pFeature )
```
**Description:**  
Sets feature support.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pFeature` - Pointer to the feature to be set.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_getresourceallocationinfo'>**`INTC_D3D12_GetResourceAllocationInfo`**</a>  

**Function declaration:**  
```cpp
D3D12_RESOURCE_ALLOCATION_INFO INTC_D3D12_GetResourceAllocationInfo(
    INTCExtensionContext* pExtensionContext,
    UINT visibleMask,
    UINT numResourceDescs,
    const INTC_D3D12_RESOURCE_DESC_0001* pResourceDescs )
```
**Description:**  
Gets the size and alignment of memory required for a collection of resources on this adapter.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `visibleMask` - For single-GPU operation, set this to zero. If there are multiple GPU nodes, set bits to identify the nodes (the device's physical adapters). Each bit in the mask corresponds to a single node.
- `numResourceDescs` - The number of resource descriptors in the pResourceDescs array.
- `pResourceDescs` - A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.

**Return:**  
- `D3D12_RESOURCE_ALLOCATION_INFO` - None


<a id='intc_d3d12_checkfeaturesupport'>**`INTC_D3D12_CheckFeatureSupport`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_CheckFeatureSupport(
    INTCExtensionContext* pExtensionContext,
    INTC_D3D12_FEATURES Feature,
    void* pFeatureSupportData,
    UINT FeatureSupportDataSize )
```
**Description:**  
Gets information about the features that are supported by the current graphics driver.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `Feature` - A constant from the D3D12_FEATURES enumeration describing the feature(s) that you want to query for support.
- `pFeatureSupportData` - A pointer to a data structure that corresponds to the value of the Feature parameter. To determine the corresponding data structure for each constant, see INTC_D3D12_FEATURES.
- `FeatureSupportDataSize` - The size of the structure pointed to by the pFeatureSupportData parameter.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_addshaderbinariespath'>**`INTC_D3D12_AddShaderBinariesPath`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_AddShaderBinariesPath(
    INTCExtensionContext* pExtensionContext,
    const wchar_t* filePath )
```
**Description:**  
Sets a custom shader binary file path.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `filePath` - Path to a pre-built shader binary file.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_removeshaderbinariespath'>**`INTC_D3D12_RemoveShaderBinariesPath`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_RemoveShaderBinariesPath(
    INTCExtensionContext* pExtensionContext,
    const wchar_t* filePath )
```
**Description:**  
Removes a custom shader binary file path.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `filePath` - Path to a pre-built shader binary file.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_setapplicationinfo'>**`INTC_D3D12_SetApplicationInfo`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_SetApplicationInfo(
    INTCExtensionAppInfo1* pExtensionAppInfo )
```
**Description:**  
Register Application Info in the graphics driver.  

**Arguments:**  
- `pExtensionAppInfo` - Application Info to be passed to the driver.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_getcommandlisthandle'>**`INTC_D3D12_GetCommandListHandle`**</a>  

**Function declaration:**  
```cpp
uint64_t INTC_D3D12_GetCommandListHandle(
    INTCExtensionContext* pExtensionContext,
    void* pCommandList )
```
**Description:**  
Obtains an Graphics Extensions CommandListHandle associated with the D3D12 CommandList Object.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pCommandList` - Pointer to the D3D12 CommandList Object.

**Return:**  
- `uint64_t` - None


<a id='intc_d3d12_seteventmarker'>**`INTC_D3D12_SetEventMarker`**</a>  

**Function declaration:**  
```cpp
void INTC_D3D12_SetEventMarker(
    INTCExtensionContext* pExtensionContext,
    ID3D12GraphicsCommandList* pCommandList,
    uint32_t eventType,
    const void* marker,
    uint32_t markerSize )
```
**Description:**  
Places a marker in the Command List. Markers (breadcrumbs) are then decoded in the GPU crash dump.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pCommandList` - A command list to set the event marker.
- `eventType` - The type of the event marker.
- `marker` - The marker data.
- `markerSize` - The size of the marker data.

**Return:**  
- `void` - None


<a id='intc_d3d12_getcurrentshaderheapusage'>**`INTC_D3D12_GetCurrentShaderHeapUsage`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_GetCurrentShaderHeapUsage(
    INTCExtensionContext* pExtensionContext,
    UINT64* pShaderHeapUsage )
```
**Description:**  
Returns the current shader heap usage.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pShaderHeapUsage` - A pointer to a variable that receives the current shader heap usage in bytes.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_d3d12_setdeviceparams'>**`INTC_D3D12_SetDeviceParams`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_SetDeviceParams(
    INTCDeviceParams* pDeviceParams )
```
**Description:**  
Sets additional device information for the next/current D3D12 device.  

**Arguments:**  
- `pDeviceParams` - A pointer to a structure containing device params to be set.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful. If setting any of the parameters fails, it returns E_INVALIDARG.


<a id='intc_d3d12_getcachedblob'>**`INTC_D3D12_GetCachedBlob`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_D3D12_GetCachedBlob(
    INTCExtensionContext* pExtensionContext,
    ID3D12PipelineState* pPipelineState,
    ID3DBlob** ppBlob,
    INTC_D3D12_CACHED_BLOB_FLAGS flags )
```
**Description:**  
Gets the cached blob representing the pipeline state.  

**Arguments:**  
- `pExtensionContext` - A pointer to the extension context associated with the current Device.
- `pPipelineState` - A pipeline state object.
- `ppBlob` - After this method returns, points to the cached blob representing the pipeline state.
- `flags` - Flags to specify the behavior of the method.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_enablegpucrashdumps'>**`INTC_EnableGpuCrashDumps`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_EnableGpuCrashDumps(
    INTC_GPU_CRASH_FLAGS flags,
    const INTC_CALLBACKS& callbacks,
    void* pPrivateData )
```
**Description:**  
Enables Intel Breadcrumbs GPU crash dumps - should be called *before* device creation.  

**Arguments:**  
- `flags` - Flags to enable the crash dump.
- `callbacks` - Callbacks to be used for the crash dump.
- `pPrivateData` - Private data that can be associated with the crash dump.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_isgpucrashdumpsenabled'>**`INTC_IsGpuCrashDumpsEnabled`**</a>  

**Function declaration:**  
BOOL INTC_IsGpuCrashDumpsEnabled()
```
**Description:**  
Used to determine if application GPU crash dumps are enabled.  

**Arguments:**  

**Return:**  
- `BOOL` - Returns TRUE if app wants to collect crash dumps, else FALSE.


<a id='intc_disablegpucrashdumps'>**`INTC_DisableGpuCrashDumps`**</a>  

**Function declaration:**  
void INTC_DisableGpuCrashDumps()
```
**Description:**  
Disables Intel Breadcrumbs GPU crash dumps.  

**Arguments:**  

**Return:**  
- `void` - None


<a id='intc_getgpucrashdump'>**`INTC_GetGpuCrashDump`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_GetGpuCrashDump(
    INTC_CRASHDUMP_STATUS& Status )
```
**Description:**  
Checks the status of the GPU Crash Dump.  

**Arguments:**  
- `Status` - The status of the GPU Crash Dump.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_decodegpucrashdump'>**`INTC_DecodeGpuCrashDump`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_DecodeGpuCrashDump(
    wchar_t* crashDump,
    uint32_t& crashDumpSize )
```
**Description:**  
Decodes the GPU Crash Dump and generates a text with the crash dump information.  

**Arguments:**  
- `crashDump` - The string buffer that receives GPU Crash Dump decoded text.
- `crashDumpSize` - The size of the crash dump. If crashDump is NULL, this will return the size of the crash dump string required.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_retrievegpucrashdump'>**`INTC_RetrieveGpuCrashDump`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_RetrieveGpuCrashDump(
    INTC_CRASHDUMP_INFO*& pCrashDumpInfo )
```
**Description:**  
Retrieves the GPU Crash Dump information in a structured format for further processing.  

**Arguments:**  
- `pCrashDumpInfo` - Pointer to the INTC_CRASHDUMP_INFO structure to be filled with the crash dump information.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.


<a id='intc_loadgpucrashdump'>**`INTC_LoadGpuCrashDump`**</a>  

**Function declaration:**  
```cpp
HRESULT INTC_LoadGpuCrashDump(
    uint8_t* crashDump,
    uint32_t crashDumpSize )
```
**Description:**  
Loads the binary GPU Crash Dump data.  

**Arguments:**  
- `crashDump` - The raw buffer that receives GPU Crash Dump data.
- `crashDumpSize` - The size of the crash dump. If crashDump is NULL, this will return the size of the crash dump buffer required.

**Return:**  
- `HRESULT` - Returns S_OK if it was successful.



# Intel(R) Graphics Extensions SDK Changelog


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
