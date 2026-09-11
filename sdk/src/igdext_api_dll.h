/*
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 *
 * File Name:  igdext_api_dll.h
 *
 * Abstract:   Graphics Extensions DLL Header File
 *
 * Notes:      This file is auto-generated.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define INTC_EXT_API __declspec( dllexport )

struct INTCExtensionVersion;
struct INTCExtensionInfo;
struct INTCExtensionAppInfo;
struct INTCExtensionAppInfo1;
struct INTCExtensionContext;

class ExtensionAppInfo
{
public:
    static ExtensionAppInfo& get();

    void OnDestroy();

    INTCExtensionAppInfo1 GetApplicationInfo();

    HRESULT SetApplicationInfo( INTCExtensionAppInfo1* pExtensionAppInfo );

private:
    ExtensionAppInfo()                                     = default;
    ExtensionAppInfo( const ExtensionAppInfo& )            = delete;
    ExtensionAppInfo& operator=( const ExtensionAppInfo& ) = delete;
    ~ExtensionAppInfo();

    void Cleanup();

    void StoreConstString( const wchar_t*& destString, const wchar_t* srcString );

    INTCAppInfoVersion    appInfoVersion   = { 0, 0, 0, 0 };
    INTCExtensionAppInfo1 extensionAppInfo = { 0 };
};

class ExtensionDeviceParams
{
public:
    static ExtensionDeviceParams& get();

    void OnDestroy();

    INTCDeviceParams* GetDeviceParams();

    HRESULT SetDeviceParams( INTCDeviceParams* pDeviceParams );

private:
    ExtensionDeviceParams() = default;
    ~ExtensionDeviceParams();

    void Cleanup();

    INTCDeviceParams deviceParams = { 0 };
};

class OfflineCompilationDeviceInfo
{
public:
    static OfflineCompilationDeviceInfo& get();

    void OnDestroy();

    wchar_t*& GetOfflineCompilationDevice();

    HRESULT SetOfflineCompilationDevice( const wchar_t* pOfflineCompilationDevice );

private:
    OfflineCompilationDeviceInfo()                                                 = default;
    OfflineCompilationDeviceInfo( const OfflineCompilationDeviceInfo& )            = delete;
    OfflineCompilationDeviceInfo& operator=( const OfflineCompilationDeviceInfo& ) = delete;
    ~OfflineCompilationDeviceInfo();

    void Cleanup();

    void StoreConstString( wchar_t*& destString, const wchar_t* srcString );

    wchar_t* pOfflineCompilationDeviceInfo = nullptr;
};

//////////////////////////////////////////////////////////////////////////
/// @brief D3D11 Graphics Extensions data structure definitions
//////////////////////////////////////////////////////////////////////////

#ifdef INTC_IGDEXT_D3D11

#endif // INTC_IGDEXT_D3D11

//////////////////////////////////////////////////////////////////////////
/// @brief D3D12 Graphics Extensions data structure definitions
//////////////////////////////////////////////////////////////////////////

#ifdef INTC_IGDEXT_D3D12

#endif // INTC_IGDEXT_D3D12

//////////////////////////////////////////////////////////////////////////
/// @brief Graphics Extensions data structure definitions
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// @brief D3D11 Graphics Extensions API function prototypes
//////////////////////////////////////////////////////////////////////////

#ifdef INTC_IGDEXT_D3D11

//////////////////////////////////////////////////////////////////////////
/// @brief BeginUAVOverlap marks the beginning point for disabling GPU synchronization between consecutive draws and dispatches that share UAV resources.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
typedef HRESULT ( *PFNINTCDX11EXT_BEGINUAVOVERLAP )(
    INTCExtensionContext* pExtensionContext );

//////////////////////////////////////////////////////////////////////////
/// @brief EndUAVOverlap marks the end point for disabling GPU synchronization between consecutive draws and dispatches that share UAV resources.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
typedef HRESULT ( *PFNINTCDX11EXT_ENDUAVOVERLAP )(
    INTCExtensionContext* pExtensionContext );

//////////////////////////////////////////////////////////////////////////
/// @brief Begin_Retrieve_Resource_Handle marks the beginning point for retrieving the resource driver handle, it turns on the handle retrieval flag. flag off means no subsequent resource handle retrieval, thus no performance impact for normal resource creation flow.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
typedef HRESULT ( *PFNINTCDX11EXT_BEGIN_RETRIEVE_RESOURCE_HANDLE )(
    INTCExtensionContext* pExtensionContext );

//////////////////////////////////////////////////////////////////////////
/// @brief End_Retrieve_Resource_Handle marks the end point for retrieving the resource driver handle, it writes the resource handle to the destination memory where the application provides.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
typedef HRESULT ( *PFNINTCDX11EXT_END_RETRIEVE_RESOURCE_HANDLE )(
    INTCExtensionContext* pExtensionContext );

//////////////////////////////////////////////////////////////////////////
/// @brief MultiDrawInstancedIndirect function submits multiple DrawInstancedIndirect in one call.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDeviceContext A pointer to the device context that will be used to generate rendering commands.
/// @param drawCount The number of draws.
/// @param pBufferForArgs Pointer to the Arguments Buffer.
/// @param alignedByteOffsetForArgs Offset into the Arguments Buffer.
/// @param byteStrideForArgs The stride between elements in the Argument Buffer.
typedef void ( *PFNINTCDX11EXT_MULTIDRAWINSTANCEDINDIRECT )(
    INTCExtensionContext* pExtensionContext,
    ID3D11DeviceContext*  pDeviceContext,
    UINT                  drawCount,
    ID3D11Buffer*         pBufferForArgs,
    UINT                  alignedByteOffsetForArgs,
    UINT                  byteStrideForArgs );

//////////////////////////////////////////////////////////////////////////
/// @brief MultiDrawIndexedInstancedIndirect function submits multiple DrawIndexedInstancedIndirect in one call.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDeviceContext A pointer to the device context that will be used to generate rendering commands.
/// @param drawCount The number of draws.
/// @param pBufferForArgs Pointer to the Arguments Buffer.
/// @param alignedByteOffsetForArgs Offset into the Arguments Buffer.
/// @param byteStrideForArgs The stride between elements in the Argument Buffer.
typedef void ( *PFNINTCDX11EXT_MULTIDRAWINDEXEDINSTANCEDINDIRECT )(
    INTCExtensionContext* pExtensionContext,
    ID3D11DeviceContext*  pDeviceContext,
    UINT                  drawCount,
    ID3D11Buffer*         pBufferForArgs,
    UINT                  alignedByteOffsetForArgs,
    UINT                  byteStrideForArgs );

//////////////////////////////////////////////////////////////////////////
/// @brief MultiDrawInstancedIndirect function submits multiple DrawInstancedIndirect in one call. The number of draws are passed using Draw Count Buffer. It must be less or equal the Max Count argument.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDeviceContext A pointer to the device context that will be used to generate rendering commands.
/// @param pBufferForDrawCount Buffer that contains the number of draws.
/// @param alignedByteOffsetForDrawCount Offset into the Draw Count Buffer.
/// @param maxCount Maximum count of draws generated by this call.
/// @param pBufferForArgs Pointer to the Arguments Buffer.
/// @param alignedByteOffsetForArgs Offset into the Arguments Buffer.
/// @param byteStrideForArgs The stride between elements in the Argument Buffer.
typedef void ( *PFNINTCDX11EXT_MULTIDRAWINSTANCEDINDIRECTCOUNTINDIRECT )(
    INTCExtensionContext* pExtensionContext,
    ID3D11DeviceContext*  pDeviceContext,
    ID3D11Buffer*         pBufferForDrawCount,
    UINT                  alignedByteOffsetForDrawCount,
    UINT                  maxCount,
    ID3D11Buffer*         pBufferForArgs,
    UINT                  alignedByteOffsetForArgs,
    UINT                  byteStrideForArgs );

//////////////////////////////////////////////////////////////////////////
/// @brief MultiDrawIndexedInstancedIndirect function submits multiple DrawInstancedIndirect in one call. The number of draws are passed using Draw Count Buffer. It must be less or equal the Max Count argument.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDeviceContext A pointer to the device context that will be used to generate rendering commands.
/// @param pBufferForDrawCount Buffer that contains the number of draws.
/// @param alignedByteOffsetForDrawCount Offset into the Draw Count Buffer.
/// @param maxCount Maximum count of draws generated by this call.
/// @param pBufferForArgs Pointer to the Arguments Buffer.
/// @param alignedByteOffsetForArgs Offset into the Arguments Buffer.
/// @param byteStrideForArgs The stride between elements in the Argument Buffer.
typedef void ( *PFNINTCDX11EXT_MULTIDRAWINDEXEDINSTANCEDINDIRECTCOUNTINDIRECT )(
    INTCExtensionContext* pExtensionContext,
    ID3D11DeviceContext*  pDeviceContext,
    ID3D11Buffer*         pBufferForDrawCount,
    UINT                  alignedByteOffsetForDrawCount,
    UINT                  maxCount,
    ID3D11Buffer*         pBufferForArgs,
    UINT                  alignedByteOffsetForArgs,
    UINT                  byteStrideForArgs );

//////////////////////////////////////////////////////////////////////////
/// @brief SetDepthBounds method enables you to change the depth bounds dynamically.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param bEnable Enable or disable depth bounds test.
/// @param Min Specifies the minimum depth bounds. The default value is 0. NaN values silently convert to 0.
/// @param Max Specifies the maximum depth bounds. The default value is 1. NaN values silently convert to 0.
typedef void ( *PFNINTCDX11EXT_SETDEPTHBOUNDS )(
    INTCExtensionContext* pExtensionContext,
    BOOL                  bEnable,
    FLOAT                 Min,
    FLOAT                 Max );

//////////////////////////////////////////////////////////////////////////
/// @brief Create an array of 2D textures. Supported extensions: Emulated64bitTypedAtomics - Enable usage of 64bit Typed Atomics on a texture created.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc A pointer to a INTC_D3D11_TEXTURE2D_DESC structure that describes a 2D texture resource.
/// @param pInitialData A pointer to an array of D3D11_SUBRESOURCE_DATA structures that describe subresources for the 2D texture resource.
/// @param ppTexture2D A pointer to a buffer that receives a pointer to a ID3D11Texture2D interface for the created texture.
typedef HRESULT ( *PFNINTCDX11EXT_CREATETEXTURE2D )(
    INTCExtensionContext*            pExtensionContext,
    const INTC_D3D11_TEXTURE2D_DESC* pDesc,
    const D3D11_SUBRESOURCE_DATA*    pInitialData,
    ID3D11Texture2D**                ppTexture2D );

#endif // INTC_IGDEXT_D3D11

//////////////////////////////////////////////////////////////////////////
/// @brief D3D12 Graphics Extensions API function prototypes
//////////////////////////////////////////////////////////////////////////

#ifdef INTC_IGDEXT_D3D12

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc A pointer to a D3D12_COMPUTE_PIPELINE_STATE_DESC structure that describes compute pipeline state.
/// @param riid The globally unique identifier (GUID) for the command queue interface.
/// @param ppCommandQueue A pointer to a memory block that receives a pointer to the ID3D12CommandQueue interface for the command queue.
typedef HRESULT ( *PFNINTCDX12EXT_CREATECOMMANDQUEUE )(
    INTCExtensionContext*                pExtensionContext,
    const INTC_D3D12_COMMAND_QUEUE_DESC* pDesc,
    REFIID                               riid,
    void**                               ppCommandQueue );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a compute pipeline state object.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc A pointer to a D3D12_COMPUTE_PIPELINE_STATE_DESC structure that describes compute pipeline state.
/// @param riid The globally unique identifier (GUID) for the pipeline state interface.
/// @param ppPipelineState A pointer to a memory block that receives a pointer to the ID3D12PipelineState interface for the pipeline state object.
typedef HRESULT ( *PFNINTCDX12EXT_CREATECOMPUTEPIPELINESTATE )(
    INTCExtensionContext*                         pExtensionContext,
    const INTC_D3D12_COMPUTE_PIPELINE_STATE_DESC* pDesc,
    REFIID                                        riid,
    void**                                        ppPipelineState );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a resource that is reserved, which is not yet mapped to any pages in a heap.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
/// @param InitialState The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
/// @param pOptimizedClearValue Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
/// @param riid The globally unique identifier (GUID) for the resource interface.
/// @param ppvResource A pointer to a memory block that receives a pointer to the resource.
typedef HRESULT ( *PFNINTCDX12EXT_CREATERESERVEDRESOURCE )(
    INTCExtensionContext*           pExtensionContext,
    const INTC_D3D12_RESOURCE_DESC* pDesc,
    D3D12_RESOURCE_STATES           InitialState,
    const D3D12_CLEAR_VALUE*        pOptimizedClearValue,
    REFIID                          riid,
    void**                          ppvResource );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates both a resource and an implicit heap, such that the heap is big enough to contain the entire resource and the resource is mapped to the heap.
/// @param pExtensionContext A pointer to a D3D12_HEAP_PROPERTIES structure that provides properties for the resource's heap.
/// @param pHeapProperties A pointer to the ID3D12Heap interface that represents the heap in which the resource is placed.
/// @param HeapFlags The offset, in bytes, to the resource.
/// @param pDesc A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
/// @param InitialResourceState The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
/// @param pOptimizedClearValue Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
/// @param riidResource The globally unique identifier (GUID) for the resource interface.
/// @param ppvResource A pointer to memory that receives the requested interface pointer to the created resource object.
typedef HRESULT ( *PFNINTCDX12EXT_CREATECOMMITTEDRESOURCE )(
    INTCExtensionContext*                pExtensionContext,
    const D3D12_HEAP_PROPERTIES*         pHeapProperties,
    D3D12_HEAP_FLAGS                     HeapFlags,
    const INTC_D3D12_RESOURCE_DESC_0001* pDesc,
    D3D12_RESOURCE_STATES                InitialResourceState,
    const D3D12_CLEAR_VALUE*             pOptimizedClearValue,
    REFIID                               riidResource,
    void**                               ppvResource );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates both a resource and an implicit heap, such that the heap is big enough to contain the entire resource and the resource is mapped to the heap.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pHeapProperties A pointer to the ID3D12Heap interface that represents the heap in which the resource is placed.
/// @param HeapFlags The offset, in bytes, to the resource.
/// @param pDesc A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
/// @param InitialResourceState The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
/// @param pOptimizedClearValue Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
/// @param riidResource The globally unique identifier (GUID) for the resource interface.
/// @param ppvResource A pointer to memory that receives the requested interface pointer to the created resource object.
typedef HRESULT ( *PFNINTCDX12EXT_CREATECOMMITTEDRESOURCE1 )(
    INTCExtensionContext*                pExtensionContext,
    const D3D12_HEAP_PROPERTIES*         pHeapProperties,
    D3D12_HEAP_FLAGS                     HeapFlags,
    const INTC_D3D12_RESOURCE_DESC_0002* pDesc,
    D3D12_RESOURCE_STATES                InitialResourceState,
    const D3D12_CLEAR_VALUE*             pOptimizedClearValue,
    REFIID                               riidResource,
    void**                               ppvResource );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a heap.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc A pointer to a overridden D3D12_HEAP_DESC structure that describes the heap.
/// @param riid The globally unique identifier (GUID) for the heap interface.
/// @param ppvHeap A pointer to a memory block that receives a pointer to the heap.
typedef HRESULT ( *PFNINTCDX12EXT_CREATEHEAP )(
    INTCExtensionContext*       pExtensionContext,
    const INTC_D3D12_HEAP_DESC* pDesc,
    REFIID                      riid,
    void**                      ppvHeap );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a resource that is placed in a specific heap.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pHeap A pointer to the ID3D12Heap interface that represents the heap in which the resource is placed.
/// @param HeapOffset The offset, in bytes, to the resource.
/// @param pDesc A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
/// @param InitialState The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
/// @param pOptimizedClearValue Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
/// @param riid The globally unique identifier (GUID) for the resource interface.
/// @param ppvResource A pointer to a memory block that receives a pointer to the resource.
typedef HRESULT ( *PFNINTCDX12EXT_CREATEPLACEDRESOURCE )(
    INTCExtensionContext*                pExtensionContext,
    ID3D12Heap*                          pHeap,
    UINT64                               HeapOffset,
    const INTC_D3D12_RESOURCE_DESC_0001* pDesc,
    D3D12_RESOURCE_STATES                InitialState,
    const D3D12_CLEAR_VALUE*             pOptimizedClearValue,
    REFIID                               riid,
    void**                               ppvResource );

//////////////////////////////////////////////////////////////////////////
/// @brief Constructs a buffer resource suitable for storing raytracing acceleration structures build on the host.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param SizeInBytes Size of the resource, in bytes.
/// @param Flags Reserved, must be zero.
/// @param riidResource Interface id for the returned resource.
/// @param ppvResource Pointer to a pointer which is set to the output resource.
typedef HRESULT ( *PFNINTCDX12EXT_CREATEHOSTRTASRESOURCE )(
    INTCExtensionContext* pExtensionContext,
    size_t                SizeInBytes,
    DWORD                 Flags,
    REFIID                riidResource,
    void**                ppvResource );

//////////////////////////////////////////////////////////////////////////
/// @brief Builds an acceleration structure on the host timeline.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc An acceleration structure description. All GPUVA fields contained in the description are interpreted as host pointers cast to uintptr_t.
/// @param pInstanceGPUVAs For a top-level AS, this contains the GPUVA of the bottom-level AS for each instance which will be used for ray traversal.
/// @param NumInstances Number of addresses in 'pInstanceGPUVAs'.
typedef void ( *PFNINTCDX12EXT_BUILDRAYTRACINGACCELERATIONSTRUCTURE_HOST )(
    INTCExtensionContext*                                     pExtensionContext,
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC* pDesc,
    const D3D12_GPU_VIRTUAL_ADDRESS*                          pInstanceGPUVAs,
    UINT                                                      NumInstances );

//////////////////////////////////////////////////////////////////////////
/// @brief Copies an acceleration structure on the host timeline.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param DestAccelerationStructureData Pointer to destination AS. Must point into a mapped Host RTAS resource.
/// @param SourceAccelerationStructureData Pointer to source AS. Must point into a mapped Host RTAS resource.
/// @param Mode See DXR spec.
typedef void ( *PFNINTCDX12EXT_COPYRAYTRACINGACCELERATIONSTRUCTURE_HOST )(
    INTCExtensionContext*                             pExtensionContext,
    void*                                             DestAccelerationStructureData,
    const void*                                       SourceAccelerationStructureData,
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode );

//////////////////////////////////////////////////////////////////////////
/// @brief Retrieves post-build info for a host-built AS on the host timeline.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param InfoType See DXR spec.
/// @param DestBuffer Pointer to output structure (see DXR spec).
/// @param SourceRTAS Pointer to source RTAS. Must lie within a Host rtas resource.
typedef void ( *PFNINTCDX12EXT_EMITRAYTRACINGACCELERATIONSTRUCTUREPOSTBUILDINFO_HOST )(
    INTCExtensionContext*                                       pExtensionContext,
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE InfoType,
    void*                                                       DestBuffer,
    const void*                                                 SourceRTAS );

//////////////////////////////////////////////////////////////////////////
/// @brief Retrieves pre-build info for a host-built AS.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc See DXR spec.
/// @param pInfo See DXR spec. This function gives the AS and scratch sizes for a host-built AS, which might not match the device-built equivalents.
typedef void ( *PFNINTCDX12EXT_GETRAYTRACINGACCELERATIONSTRUCTUREPREBUILDINFO_HOST )(
    INTCExtensionContext*                                       pExtensionContext,
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS* pDesc,
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO*      pInfo );

//////////////////////////////////////////////////////////////////////////
/// @brief Copy host-built acceleration structures to/from device memory on the GPU timeline.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pCommandList A command list to receive copy commands.
/// @param DestAccelerationStructureData GPU address of destination.
/// @param SrcAccelerationStructureData GPU address of source.
/// @param Mode See DXR spec. At least one of Dest and Src must be a Host RTAS resource. The other must be a conventional DXR acceleration structure buffer.
typedef void ( *PFNINTCDX12EXT_TRANSFERHOSTRTAS )(
    INTCExtensionContext*                             pExtensionContext,
    ID3D12GraphicsCommandList*                        pCommandList,
    D3D12_GPU_VIRTUAL_ADDRESS                         DestAccelerationStructureData,
    D3D12_GPU_VIRTUAL_ADDRESS                         SrcAccelerationStructureData,
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode );

//////////////////////////////////////////////////////////////////////////
/// @brief Set Metadata associated with the CommandList.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pCommandList A command list to set metadata.
/// @param Metadata Metadata.
typedef void ( *PFNINTCDX12EXT_SETDRIVEREVENTMETADATA )(
    INTCExtensionContext*      pExtensionContext,
    ID3D12GraphicsCommandList* pCommandList,
    UINT64                     Metadata );

//////////////////////////////////////////////////////////////////////////
/// @brief Queries total number of bytes and number of free bytes in CPU visible local memory.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pTotalBytes A pointer to total number of bytes in CPU visible vidmem.
/// @param pFreeBytes A pointer to number of free bytes in CPU visible vidmem.
typedef void ( *PFNINTCDX12EXT_QUERYCPUVISIBLEVIDMEM )(
    INTCExtensionContext* pExtensionContext,
    UINT64*               pTotalBytes,
    UINT64*               pFreeBytes );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates an ID3D12StateObject.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc The description of the state object to create.
/// @param riid The GUID of the interface to create.
/// @param ppPipelineState The returned Raytracing pipeline state object.
typedef HRESULT ( *PFNINTCDX12EXT_CREATESTATEOBJECT )(
    INTCExtensionContext*               pExtensionContext,
    const INTC_D3D12_STATE_OBJECT_DESC* pDesc,
    REFIID                              riid,
    void**                              ppPipelineState );

//////////////////////////////////////////////////////////////////////////
/// @brief Performs a raytracing acceleration structure build on the GPU.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pCommandList A command list to build acceleration structure.
/// @param pDesc Description of the acceleration structure to build.
/// @param NumPostbuildInfoDescs Size of the pPostbuildInfoDescs array.
/// @param pPostbuildInfoDescs Optional array of descriptions for post-build info to generate describing properties of the acceleration structure that was built.
/// @param pComparisonDataDesc Description of the comparison data.
typedef void ( *PFNINTCDX12EXT_BUILDRAYTRACINGACCELERATIONSTRUCTURE )(
    INTCExtensionContext*                                                                   pExtensionContext,
    ID3D12GraphicsCommandList*                                                              pCommandList,
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC*                               pDesc,
    UINT                                                                                    NumPostbuildInfoDescs,
    const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC*                      pPostbuildInfoDescs,
    const INTC_D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC_INSTANCE_COMPARISON_DATA* pComparisonDataDesc );

//////////////////////////////////////////////////////////////////////////
/// @brief Query the driver for resource requirements to build an acceleration structure.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc Description of the acceleration structure build.
/// @param pInfo The result of the query.
/// @param pComparisonDataDesc Description of the comparison data.
typedef void ( *PFNINTCDX12EXT_GETRAYTRACINGACCELERATIONSTRUCTUREPREBUILDINFO )(
    INTCExtensionContext*                                                                   pExtensionContext,
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS*                             pDesc,
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO*                                  pInfo,
    const INTC_D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC_INSTANCE_COMPARISON_DATA* pComparisonDataDesc );

//////////////////////////////////////////////////////////////////////////
/// @brief Sets feature support.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pFeature Pointer to the feature to be set.
typedef HRESULT ( *PFNINTCDX12EXT_SETFEATURESUPPORT )(
    INTCExtensionContext* pExtensionContext,
    INTC_D3D12_FEATURE*   pFeature );

//////////////////////////////////////////////////////////////////////////
/// @brief Gets the size and alignment of memory required for a collection of resources on this adapter.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param visibleMask For single-GPU operation, set this to zero. If there are multiple GPU nodes, set bits to identify the nodes (the device's physical adapters). Each bit in the mask corresponds to a single node.
/// @param numResourceDescs The number of resource descriptors in the pResourceDescs array.
/// @param pResourceDescs A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
typedef D3D12_RESOURCE_ALLOCATION_INFO ( *PFNINTCDX12EXT_GETRESOURCEALLOCATIONINFO )(
    INTCExtensionContext*                pExtensionContext,
    UINT                                 visibleMask,
    UINT                                 numResourceDescs,
    const INTC_D3D12_RESOURCE_DESC_0001* pResourceDescs );

//////////////////////////////////////////////////////////////////////////
/// @brief Gets information about the features that are supported by the current graphics driver.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param Feature A constant from the D3D12_FEATURES enumeration describing the feature(s) that you want to query for support.
/// @param pFeatureSupportData A pointer to a data structure that corresponds to the value of the Feature parameter. To determine the corresponding data structure for each constant, see INTC_D3D12_FEATURES.
/// @param FeatureSupportDataSize The size of the structure pointed to by the pFeatureSupportData parameter.
typedef HRESULT ( *PFNINTCDX12EXT_CHECKFEATURESUPPORT )(
    INTCExtensionContext* pExtensionContext,
    INTC_D3D12_FEATURES   Feature,
    void*                 pFeatureSupportData,
    UINT                  FeatureSupportDataSize );

//////////////////////////////////////////////////////////////////////////
/// @brief Sets a custom shader binary file path.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param filePath Path to a pre-built shader binary file.
typedef HRESULT ( *PFNINTCDX12EXT_ADDSHADERBINARIESPATH )(
    INTCExtensionContext* pExtensionContext,
    const wchar_t*        filePath );

//////////////////////////////////////////////////////////////////////////
/// @brief Removes a custom shader binary file path.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param filePath Path to a pre-built shader binary file.
typedef HRESULT ( *PFNINTCDX12EXT_REMOVESHADERBINARIESPATH )(
    INTCExtensionContext* pExtensionContext,
    const wchar_t*        filePath );

//////////////////////////////////////////////////////////////////////////
/// @brief Register Application Info in the graphics driver.
/// @param pExtensionAppInfo Application Info to be passed to the driver.
typedef HRESULT ( *PFNINTCDX12EXT_SETAPPLICATIONINFO )(
    INTCExtensionAppInfo1* pExtensionAppInfo );

//////////////////////////////////////////////////////////////////////////
/// @brief Obtains an Graphics Extensions CommandListHandle associated with the D3D12 CommandList Object.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pCommandList Pointer to the D3D12 CommandList Object.
typedef uint64_t ( *PFNINTCDX12EXT_GETCOMMANDLISTHANDLE )(
    INTCExtensionContext* pExtensionContext,
    void*                 pCommandList );

//////////////////////////////////////////////////////////////////////////
/// @brief Places a marker in the Command List. Markers (breadcrumbs) are then decoded in the GPU crash dump.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pCommandList A command list to set the event marker.
/// @param eventType The type of the event marker.
/// @param marker The marker data.
/// @param markerSize The size of the marker data.
typedef void ( *PFNINTCDX12EXT_SETEVENTMARKER )(
    INTCExtensionContext*      pExtensionContext,
    ID3D12GraphicsCommandList* pCommandList,
    uint32_t                   eventType,
    const void*                marker,
    uint32_t                   markerSize );

//////////////////////////////////////////////////////////////////////////
/// @brief Returns the current shader heap usage.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pShaderHeapUsage A pointer to a variable that receives the current shader heap usage in bytes.
typedef HRESULT ( *PFNINTCDX12EXT_GETCURRENTSHADERHEAPUSAGE )(
    INTCExtensionContext* pExtensionContext,
    UINT64*               pShaderHeapUsage );

//////////////////////////////////////////////////////////////////////////
/// @brief Sets additional device information for the next/current D3D12 device.
/// @param pDeviceParams A pointer to a structure containing device params to be set.
typedef HRESULT ( *PFNINTCDX12EXT_SETDEVICEPARAMS )(
    INTCDeviceParams* pDeviceParams );

//////////////////////////////////////////////////////////////////////////
/// @brief Gets the cached blob representing the pipeline state.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pPipelineState A pipeline state object.
/// @param ppBlob After this method returns, points to the cached blob representing the pipeline state.
/// @param flags Flags to specify the behavior of the method.
typedef HRESULT ( *PFNINTCDX12EXT_GETCACHEDBLOB )(
    INTCExtensionContext*        pExtensionContext,
    ID3D12PipelineState*         pPipelineState,
    ID3DBlob**                   ppBlob,
    INTC_D3D12_CACHED_BLOB_FLAGS flags );

#endif // INTC_IGDEXT_D3D12

//////////////////////////////////////////////////////////////////////////
/// @brief Enables Intel Breadcrumbs GPU crash dumps - should be called *before* device creation.
/// @param flags Flags to enable the crash dump.
/// @param callbacks Callbacks to be used for the crash dump.
/// @param pPrivateData Private data that can be associated with the crash dump.
typedef HRESULT ( *PFNINTCEXT_ENABLEGPUCRASHDUMPS )(
    INTC_GPU_CRASH_FLAGS  flags,
    const INTC_CALLBACKS& callbacks,
    void*                 pPrivateData );

//////////////////////////////////////////////////////////////////////////
/// @brief Used to determine if application GPU crash dumps are enabled.
typedef BOOL ( *PFNINTCEXT_ISGPUCRASHDUMPSENABLED )();

//////////////////////////////////////////////////////////////////////////
/// @brief Disables Intel Breadcrumbs GPU crash dumps.
typedef void ( *PFNINTCEXT_DISABLEGPUCRASHDUMPS )();

//////////////////////////////////////////////////////////////////////////
/// @brief Checks the status of the GPU Crash Dump.
/// @param Status The status of the GPU Crash Dump.
typedef HRESULT ( *PFNINTCEXT_GETGPUCRASHDUMP )(
    INTC_CRASHDUMP_STATUS& Status );

//////////////////////////////////////////////////////////////////////////
/// @brief Decodes the GPU Crash Dump and generates a text with the crash dump information.
/// @param crashDump The string buffer that receives GPU Crash Dump decoded text.
/// @param crashDumpSize The size of the crash dump. If crashDump is NULL, this will return the size of the crash dump string required.
typedef HRESULT ( *PFNINTCEXT_DECODEGPUCRASHDUMP )(
    wchar_t*  crashDump,
    uint32_t& crashDumpSize );

//////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the GPU Crash Dump information in a structured format for further processing.
/// @param pCrashDumpInfo Pointer to the INTC_CRASHDUMP_INFO structure to be filled with the crash dump information.
typedef HRESULT ( *PFNINTCEXT_RETRIEVEGPUCRASHDUMP )(
    INTC_CRASHDUMP_INFO*& pCrashDumpInfo );

//////////////////////////////////////////////////////////////////////////
/// @brief Loads the binary GPU Crash Dump data.
/// @param crashDump The raw buffer that receives GPU Crash Dump data.
/// @param crashDumpSize The size of the crash dump. If crashDump is NULL, this will return the size of the crash dump buffer required.
typedef HRESULT ( *PFNINTCEXT_LOADGPUCRASHDUMP )(
    uint8_t* crashDump,
    uint32_t crashDumpSize );

//////////////////////////////////////////////////////////////////////////
/// @brief D3D11 Graphics Extensions Framework extension function prototypes
//////////////////////////////////////////////////////////////////////////

#ifdef INTC_IGDEXT_D3D11

//////////////////////////////////////////////////////////////////////////
/// @brief Returns all Graphics Extensions interface versions supported on a current platform/driver/header file combination using D3D11 Device.
/// @param pDevice A pointer to the current D3D11 Device.
/// @param pSupportedExtVersions A pointer to the table of supported versions.
/// @param pSupportedExtVersionsCount A pointer to the variable that will hold the number of supported versions. Pointer is null if Init fails.
typedef HRESULT ( *PFNINTCDX11EXT_GETSUPPORTEDVERSIONS )(
    const ID3D11Device*   pDevice,
    INTCExtensionVersion* pSupportedExtVersions,
    uint32_t*             pSupportedExtVersionsCount );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates D3D11 Graphics Extensions Device Context and returns ppfnExtensionContext Extension Context object and ppfnExtensionFuncs extension function pointers table. This function must be called prior to using extensions.
/// @param pDevice A pointer to the current Device.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
/// @param pExtensionInfo A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
/// @param pExtensionAppInfo A pointer to the ExtensionAppInfo structure that can be optionally passed to the driver identifying application and engine.
typedef HRESULT ( *PFNINTCDX11EXT_CREATEDEVICEEXTENSIONCONTEXT )(
    const ID3D11Device*    pDevice,
    INTCExtensionContext** ppExtensionContext,
    INTCExtensionInfo*     pExtensionInfo,
    INTCExtensionAppInfo*  pExtensionAppInfo );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a device extension context for Direct3D 11.
/// @param pDevice A pointer to the Direct3D 11 device.
/// @param ppExtensionContext A pointer to a memory block that receives a pointer to the extension context.
/// @param pExtensionInfo A pointer to the extension information.
/// @param pExtensionAppInfo A pointer to the application-specific extension information.
typedef HRESULT ( *PFNINTCDX11EXT_CREATEDEVICEEXTENSIONCONTEXT1 )(
    const ID3D11Device*    pDevice,
    INTCExtensionContext** ppExtensionContext,
    INTCExtensionInfo*     pExtensionInfo,
    INTCExtensionAppInfo1* pExtensionAppInfo );

//////////////////////////////////////////////////////////////////////////
/// @brief INTC_D3D11_RegisterApplicationCallbacks function sets the callback table for D3D11 API handlers. All registered callbacks will be called when the corresponding original API is called.
/// @param pCallbacks A pointer to a INTC_D3D12_API_CALLBACKS structure that registers the callbacks to D3D12 API handlers.
typedef HRESULT ( *PFNINTCDX11EXT_REGISTERAPPLICATIONCALLBACKS )(
    const INTC_D3D11_API_CALLBACKS* pCallbacks );

#endif // INTC_IGDEXT_D3D11

//////////////////////////////////////////////////////////////////////////
/// @brief D3D12 Graphics Extensions Framework extension function prototypes
//////////////////////////////////////////////////////////////////////////

#ifdef INTC_IGDEXT_D3D12

//////////////////////////////////////////////////////////////////////////
/// @brief Returns all Graphics Extensions interface versions supported on a current platform/driver/header file combination using D3D12 Device.
/// @param pDevice A pointer to the current D3D11 Device.
/// @param pSupportedExtVersions A pointer to the table of supported versions.
/// @param pSupportedExtVersionsCount A pointer to the variable that will hold the number of supported versions. Pointer is null if Init fails.
typedef HRESULT ( *PFNINTCDX12EXT_GETSUPPORTEDVERSIONS )(
    const ID3D12Device*   pDevice,
    INTCExtensionVersion* pSupportedExtVersions,
    uint32_t*             pSupportedExtVersionsCount );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates D3D12 Graphics Extensions Device Context and returns ppfnExtensionContext Extension Context object and ppfnExtensionFuncs extension function pointers table. This function must be called prior to using extensions.
/// @param pDevice A pointer to the current Device.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
/// @param pExtensionInfo A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
/// @param pExtensionAppInfo A pointer to the ExtensionAppInfo structure that can be optionally passed to the driver identifying application and engine.
typedef HRESULT ( *PFNINTCDX12EXT_CREATEDEVICEEXTENSIONCONTEXT )(
    const ID3D12Device*    pDevice,
    INTCExtensionContext** ppExtensionContext,
    INTCExtensionInfo*     pExtensionInfo,
    INTCExtensionAppInfo*  pExtensionAppInfo );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates D3D12 Graphics Extensions Device Context and returns ppfnExtensionContext Extension Context object and ppfnExtensionFuncs extension function pointers table. This function must be called prior to using extensions.
/// @param pDevice A pointer to the current Device.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
/// @param pExtensionInfo A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
/// @param pExtensionAppInfo A pointer to the ExtensionAppInfo1 structure that can optionally be used in the driver to identify workload.
typedef HRESULT ( *PFNINTCDX12EXT_CREATEDEVICEEXTENSIONCONTEXT1 )(
    const ID3D12Device*    pDevice,
    INTCExtensionContext** ppExtensionContext,
    INTCExtensionInfo*     pExtensionInfo,
    INTCExtensionAppInfo1* pExtensionAppInfo );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates D3D12 Graphics Extensions Device Context and returns ppfnExtensionContext Extension Context object and ppfnExtensionFuncs extension function pointers table. This function must be called prior to using extensions.
/// @param pDevice A pointer to the current Device.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
/// @param pExtensionInfo A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
/// @param pExtensionAppInfo A pointer to the ExtensionAppInfo1 structure that can optionally be used in the driver to identify workload.
typedef HRESULT ( *PFNINTCDX12EXT_CREATEDEVICEEXTENSIONCONTEXT2 )(
    const ID3D12Device*    pDevice,
    INTCExtensionContext** ppExtensionContext,
    INTCExtensionInfo1*    pExtensionInfo,
    INTCExtensionAppInfo1* pExtensionAppInfo );

//////////////////////////////////////////////////////////////////////////
/// @brief INTC_D3D12_RegisterApplicationCallbacks function sets the callback table for D3D12 API handlers. All registered callbacks will be called when the corresponding original API is called.
/// @param pCallbacks A pointer to a INTC_D3D12_API_CALLBACKS structure that registers the callbacks to D3D12 API handlers.
typedef HRESULT ( *PFNINTCDX12EXT_REGISTERAPPLICATIONCALLBACKS )(
    const INTC_D3D12_API_CALLBACKS* pCallbacks );

//////////////////////////////////////////////////////////////////////////
/// @brief INTC_D3D12_RegisterApplicationCallbacks1 function sets the callback table for D3D12 API handlers. All registered callbacks will be called when the corresponding original API is called.
/// @param pCallbacks A pointer to a INTC_D3D12_API_CALLBACKS1 structure that registers the callbacks to D3D12 API handlers.
typedef HRESULT ( *PFNINTCDX12EXT_REGISTERAPPLICATIONCALLBACKS1 )(
    const INTC_D3D12_API_CALLBACKS1* pCallbacks );

#endif // INTC_IGDEXT_D3D12

//////////////////////////////////////////////////////////////////////////
/// @brief Graphics Extensions Framework extension function prototypes
//////////////////////////////////////////////////////////////////////////

#if defined( INTC_IGDEXT_D3D11 ) && defined( INTC_IGDEXT_D3D12 )

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a D3D Graphics Extensions Device Context and returns ppExtensionContext Extension Context object. This function must be called prior to using extensions when creating an extension context with a D3D11 and D3D12 device.
/// @param pD3D11Device A pointer to the current D3D11 device.
/// @param pD3D12Device A pointer to the current D3D12 device.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
/// @param pExtensionInfo A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
/// @param pExtensionAppInfo A pointer to the ExtensionAppInfo structure that can be optionally passed to the driver identifying application and engine.
typedef HRESULT ( *PFNINTCDX11DX12EXT_CREATEDEVICEEXTENSIONCONTEXT )(
    const ID3D11Device*    pD3D11Device,
    const ID3D12Device*    pD3D12Device,
    INTCExtensionContext** ppExtensionContext,
    INTCExtensionInfo*     pExtensionInfo,
    INTCExtensionAppInfo*  pExtensionAppInfo );

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a device extension context for DX12.
/// @param pD3D11Device Pointer to the D3D11 device.
/// @param pD3D12Device Pointer to the D3D12 device.
/// @param ppExtensionContext Pointer to the extension context.
/// @param pExtensionInfo Pointer to the extension information.
/// @param pExtensionAppInfo Pointer to the extension application information.
typedef HRESULT ( *PFNINTCDX11DX12EXT_CREATEDEVICEEXTENSIONCONTEXT1 )(
    ID3D11Device*          pD3D11Device,
    ID3D12Device*          pD3D12Device,
    INTCExtensionContext** ppExtensionContext,
    INTCExtensionInfo*     pExtensionInfo,
    INTCExtensionAppInfo1* pExtensionAppInfo );

#endif // INTC_IGDEXT_D3D11 & INTC_IGDEXT_D3D12

//////////////////////////////////////////////////////////////////////////
/// @brief Destroys D3D12 Graphics Extensions Device Context and provides cleanup for the Graphics Extensions Framework. No D3D12 extensions can be used after calling this function.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
typedef HRESULT ( *PFNINTCEXT_DESTROYDEVICEEXTENSIONCONTEXT )(
    INTCExtensionContext** ppExtensionContext );

#ifdef __cplusplus
} // extern "C"
#endif
