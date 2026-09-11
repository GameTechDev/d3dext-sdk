/*
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 *
 * File Name:  igdext_api.cpp
 *
 * Abstract:   Graphics Extensions SDK API Source File
 *
 * Notes:      This file is auto-generated.
 */

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////
/// @brief Extension Context structure to pass to all extension calls
//////////////////////////////////////////////////////////////////////////

struct INTCInternalExtensionContext;
INTCInternalExtensionContext* pExtInternalContext = INTCInternalExtensionContext::Get();
INTC_LIB_OPTIONS              g_Options           = { 0 };

static size_t libraryLoadRefCount = 0;

//////////////////////////////////////////////////////////////////////////
/// @brief Graphics Extensions Framework infrastructure function prototypes
//////////////////////////////////////////////////////////////////////////

HRESULT INTC_LoadExtensionsLibrary(
    bool   useCurrentProcessDir,
    size_t VendorID,
    size_t DeviceID )
{
    if( !pExtInternalContext )
    {
        return E_FAIL;
    }

    // Always call the OS LoadLibrary function to ensure proper DLL ref counting.
    HMODULE loadHandle = LoadIntelExtensionsLibrary( useCurrentProcessDir, VendorID, DeviceID );
    if( NULL == loadHandle )
    {
        // DLL load failed, bail out.
        return E_FAIL;
    }
    else if( NULL == pExtInternalContext->m_hExtLib )
    {
        pExtInternalContext->m_hExtLib = loadHandle;
    }
    ++libraryLoadRefCount;

    // if( 1 == libraryLoadRefCount )
    {
        // Infrastructure function exports
        pExtInternalContext->INTC_D3D11_GetSupportedVersions = (PFNINTCDX11EXT_GETSUPPORTEDVERSIONS)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_GetSupportedVersions" );
        if( !pExtInternalContext->INTC_D3D11_GetSupportedVersions )
            pExtInternalContext->INTC_D3D11_GetSupportedVersions = (PFNINTCDX11EXT_GETSUPPORTEDVERSIONS)GetProcAddress( pExtInternalContext->m_hExtLib, "D3D11GetSupportedVersions2" );
        pExtInternalContext->INTC_D3D11_CreateDeviceExtensionContext  = (PFNINTCDX11EXT_CREATEDEVICEEXTENSIONCONTEXT)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_CreateDeviceExtensionContext" );
        pExtInternalContext->INTC_D3D11_CreateDeviceExtensionContext1 = (PFNINTCDX11EXT_CREATEDEVICEEXTENSIONCONTEXT1)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_CreateDeviceExtensionContext1" );
        pExtInternalContext->INTC_D3D11_RegisterApplicationCallbacks  = (PFNINTCDX11EXT_REGISTERAPPLICATIONCALLBACKS)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_RegisterApplicationCallbacks" );

        pExtInternalContext->INTC_D3D12_GetSupportedVersions = (PFNINTCDX12EXT_GETSUPPORTEDVERSIONS)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_GetSupportedVersions" );
        if( !pExtInternalContext->INTC_D3D12_GetSupportedVersions )
            pExtInternalContext->INTC_D3D12_GetSupportedVersions = (PFNINTCDX12EXT_GETSUPPORTEDVERSIONS)GetProcAddress( pExtInternalContext->m_hExtLib, "D3D12GetSupportedVersions2" );
        pExtInternalContext->INTC_D3D12_CreateDeviceExtensionContext  = (PFNINTCDX12EXT_CREATEDEVICEEXTENSIONCONTEXT)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreateDeviceExtensionContext" );
        pExtInternalContext->INTC_D3D12_CreateDeviceExtensionContext1 = (PFNINTCDX12EXT_CREATEDEVICEEXTENSIONCONTEXT1)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreateDeviceExtensionContext1" );
        pExtInternalContext->INTC_D3D12_CreateDeviceExtensionContext2 = (PFNINTCDX12EXT_CREATEDEVICEEXTENSIONCONTEXT2)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreateDeviceExtensionContext2" );
        pExtInternalContext->INTC_D3D12_RegisterApplicationCallbacks  = (PFNINTCDX12EXT_REGISTERAPPLICATIONCALLBACKS)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_RegisterApplicationCallbacks" );
        pExtInternalContext->INTC_D3D12_RegisterApplicationCallbacks1 = (PFNINTCDX12EXT_REGISTERAPPLICATIONCALLBACKS1)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_RegisterApplicationCallbacks1" );

        pExtInternalContext->INTC_CreateDeviceExtensionContext  = (PFNINTCDX11DX12EXT_CREATEDEVICEEXTENSIONCONTEXT)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_CreateDeviceExtensionContext" );
        pExtInternalContext->INTC_CreateDeviceExtensionContext1 = (PFNINTCDX11DX12EXT_CREATEDEVICEEXTENSIONCONTEXT1)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_CreateDeviceExtensionContext1" );

        pExtInternalContext->INTC_DestroyDeviceExtensionContext = (PFNINTCEXT_DESTROYDEVICEEXTENSIONCONTEXT)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_DestroyDeviceExtensionContext" );
        if( !pExtInternalContext->INTC_DestroyDeviceExtensionContext )
            pExtInternalContext->INTC_DestroyDeviceExtensionContext = (PFNINTCEXT_DESTROYDEVICEEXTENSIONCONTEXT)GetProcAddress( pExtInternalContext->m_hExtLib, "D3D11D3D12DestroyDeviceExtensionContext2" );

        // API function exports
        pExtInternalContext->INTC_D3D11_BeginUAVOverlap                                = (PFNINTCDX11EXT_BEGINUAVOVERLAP)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_BeginUAVOverlap" );
        pExtInternalContext->INTC_D3D11_EndUAVOverlap                                  = (PFNINTCDX11EXT_ENDUAVOVERLAP)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_EndUAVOverlap" );
        pExtInternalContext->INTC_D3D11_Begin_Retrieve_Resource_Handle                 = (PFNINTCDX11EXT_BEGIN_RETRIEVE_RESOURCE_HANDLE)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_Begin_Retrieve_Resource_Handle" );
        pExtInternalContext->INTC_D3D11_End_Retrieve_Resource_Handle                   = (PFNINTCDX11EXT_END_RETRIEVE_RESOURCE_HANDLE)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_End_Retrieve_Resource_Handle" );
        pExtInternalContext->INTC_D3D11_MultiDrawInstancedIndirect                     = (PFNINTCDX11EXT_MULTIDRAWINSTANCEDINDIRECT)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_MultiDrawInstancedIndirect" );
        pExtInternalContext->INTC_D3D11_MultiDrawIndexedInstancedIndirect              = (PFNINTCDX11EXT_MULTIDRAWINDEXEDINSTANCEDINDIRECT)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_MultiDrawIndexedInstancedIndirect" );
        pExtInternalContext->INTC_D3D11_MultiDrawInstancedIndirectCountIndirect        = (PFNINTCDX11EXT_MULTIDRAWINSTANCEDINDIRECTCOUNTINDIRECT)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_MultiDrawInstancedIndirectCountIndirect" );
        pExtInternalContext->INTC_D3D11_MultiDrawIndexedInstancedIndirectCountIndirect = (PFNINTCDX11EXT_MULTIDRAWINDEXEDINSTANCEDINDIRECTCOUNTINDIRECT)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_MultiDrawIndexedInstancedIndirectCountIndirect" );
        pExtInternalContext->INTC_D3D11_SetDepthBounds                                 = (PFNINTCDX11EXT_SETDEPTHBOUNDS)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_SetDepthBounds" );
        pExtInternalContext->INTC_D3D11_CreateTexture2D                                = (PFNINTCDX11EXT_CREATETEXTURE2D)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D11_CreateTexture2D" );

        pExtInternalContext->INTC_D3D12_CreateCommandQueue                                    = (PFNINTCDX12EXT_CREATECOMMANDQUEUE)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreateCommandQueue" );
        pExtInternalContext->INTC_D3D12_CreateComputePipelineState                            = (PFNINTCDX12EXT_CREATECOMPUTEPIPELINESTATE)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreateComputePipelineState" );
        pExtInternalContext->INTC_D3D12_CreateReservedResource                                = (PFNINTCDX12EXT_CREATERESERVEDRESOURCE)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreateReservedResource" );
        pExtInternalContext->INTC_D3D12_CreateCommittedResource                               = (PFNINTCDX12EXT_CREATECOMMITTEDRESOURCE)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreateCommittedResource" );
        pExtInternalContext->INTC_D3D12_CreateCommittedResource1                              = (PFNINTCDX12EXT_CREATECOMMITTEDRESOURCE1)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreateCommittedResource1" );
        pExtInternalContext->INTC_D3D12_CreateHeap                                            = (PFNINTCDX12EXT_CREATEHEAP)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreateHeap" );
        pExtInternalContext->INTC_D3D12_CreatePlacedResource                                  = (PFNINTCDX12EXT_CREATEPLACEDRESOURCE)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreatePlacedResource" );
        pExtInternalContext->INTC_D3D12_CreateHostRTASResource                                = (PFNINTCDX12EXT_CREATEHOSTRTASRESOURCE)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreateHostRTASResource" );
        pExtInternalContext->INTC_D3D12_BuildRaytracingAccelerationStructure_Host             = (PFNINTCDX12EXT_BUILDRAYTRACINGACCELERATIONSTRUCTURE_HOST)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_BuildRaytracingAccelerationStructure_Host" );
        pExtInternalContext->INTC_D3D12_CopyRaytracingAccelerationStructure_Host              = (PFNINTCDX12EXT_COPYRAYTRACINGACCELERATIONSTRUCTURE_HOST)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CopyRaytracingAccelerationStructure_Host" );
        pExtInternalContext->INTC_D3D12_EmitRaytracingAccelerationStructurePostbuildInfo_Host = (PFNINTCDX12EXT_EMITRAYTRACINGACCELERATIONSTRUCTUREPOSTBUILDINFO_HOST)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_EmitRaytracingAccelerationStructurePostbuildInfo_Host" );
        pExtInternalContext->INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo_Host   = (PFNINTCDX12EXT_GETRAYTRACINGACCELERATIONSTRUCTUREPREBUILDINFO_HOST)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo_Host" );
        pExtInternalContext->INTC_D3D12_TransferHostRTAS                                      = (PFNINTCDX12EXT_TRANSFERHOSTRTAS)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_TransferHostRTAS" );
        pExtInternalContext->INTC_D3D12_SetDriverEventMetadata                                = (PFNINTCDX12EXT_SETDRIVEREVENTMETADATA)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_SetDriverEventMetadata" );
        pExtInternalContext->INTC_D3D12_QueryCpuVisibleVidmem                                 = (PFNINTCDX12EXT_QUERYCPUVISIBLEVIDMEM)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_QueryCpuVisibleVidmem" );
        pExtInternalContext->INTC_D3D12_CreateStateObject                                     = (PFNINTCDX12EXT_CREATESTATEOBJECT)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CreateStateObject" );
        pExtInternalContext->INTC_D3D12_BuildRaytracingAccelerationStructure                  = (PFNINTCDX12EXT_BUILDRAYTRACINGACCELERATIONSTRUCTURE)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_BuildRaytracingAccelerationStructure" );
        pExtInternalContext->INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo        = (PFNINTCDX12EXT_GETRAYTRACINGACCELERATIONSTRUCTUREPREBUILDINFO)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo" );
        pExtInternalContext->INTC_D3D12_SetFeatureSupport                                     = (PFNINTCDX12EXT_SETFEATURESUPPORT)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_SetFeatureSupport" );
        pExtInternalContext->INTC_D3D12_GetResourceAllocationInfo                             = (PFNINTCDX12EXT_GETRESOURCEALLOCATIONINFO)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_GetResourceAllocationInfo" );
        pExtInternalContext->INTC_D3D12_CheckFeatureSupport                                   = (PFNINTCDX12EXT_CHECKFEATURESUPPORT)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_CheckFeatureSupport" );
        pExtInternalContext->INTC_D3D12_AddShaderBinariesPath                                 = (PFNINTCDX12EXT_ADDSHADERBINARIESPATH)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_AddShaderBinariesPath" );
        pExtInternalContext->INTC_D3D12_RemoveShaderBinariesPath                              = (PFNINTCDX12EXT_REMOVESHADERBINARIESPATH)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_RemoveShaderBinariesPath" );
        pExtInternalContext->INTC_D3D12_SetApplicationInfo                                    = (PFNINTCDX12EXT_SETAPPLICATIONINFO)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_SetApplicationInfo" );
        pExtInternalContext->INTC_D3D12_GetCommandListHandle                                  = (PFNINTCDX12EXT_GETCOMMANDLISTHANDLE)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_GetCommandListHandle" );
        pExtInternalContext->INTC_D3D12_SetEventMarker                                        = (PFNINTCDX12EXT_SETEVENTMARKER)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_SetEventMarker" );
        pExtInternalContext->INTC_D3D12_GetCurrentShaderHeapUsage                             = (PFNINTCDX12EXT_GETCURRENTSHADERHEAPUSAGE)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_GetCurrentShaderHeapUsage" );
        pExtInternalContext->INTC_D3D12_SetDeviceParams                                       = (PFNINTCDX12EXT_SETDEVICEPARAMS)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_SetDeviceParams" );
        pExtInternalContext->INTC_D3D12_GetCachedBlob                                         = (PFNINTCDX12EXT_GETCACHEDBLOB)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_D3D12_GetCachedBlob" );

        pExtInternalContext->INTC_EnableGpuCrashDumps    = (PFNINTCEXT_ENABLEGPUCRASHDUMPS)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_EnableGpuCrashDumps" );
        pExtInternalContext->INTC_IsGpuCrashDumpsEnabled = (PFNINTCEXT_ISGPUCRASHDUMPSENABLED)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_IsGpuCrashDumpsEnabled" );
        pExtInternalContext->INTC_DisableGpuCrashDumps   = (PFNINTCEXT_DISABLEGPUCRASHDUMPS)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_DisableGpuCrashDumps" );
        pExtInternalContext->INTC_GetGpuCrashDump        = (PFNINTCEXT_GETGPUCRASHDUMP)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_GetGpuCrashDump" );
        pExtInternalContext->INTC_DecodeGpuCrashDump     = (PFNINTCEXT_DECODEGPUCRASHDUMP)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_DecodeGpuCrashDump" );
        pExtInternalContext->INTC_RetrieveGpuCrashDump   = (PFNINTCEXT_RETRIEVEGPUCRASHDUMP)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_RetrieveGpuCrashDump" );
        pExtInternalContext->INTC_LoadGpuCrashDump       = (PFNINTCEXT_LOADGPUCRASHDUMP)GetProcAddress( pExtInternalContext->m_hExtLib, "_INTC_LoadGpuCrashDump" );

        // Internal Graphics Extensions

        // Infrastructure function exports

        // API function exports
    }

    return S_OK;
}

void INTC_UnloadExtensionsLibrary()
{
    // Validate input parameters
    if( pExtInternalContext == nullptr )
    {
        return;
    }

    // Wait until all of the LoadLibrary references are removed before
    // deleting the internal context data.
    if( libraryLoadRefCount )
    {
        --libraryLoadRefCount;
        if( libraryLoadRefCount != 0 )
        {
            // Always call FreeLibrary to ensure proper OS dll ref counting
            // Keep using the same handle, it should be the same value returned
            // for all calls to LoadLibrary...
            if( pExtInternalContext->m_hExtLib != NULL )
            {
                FreeLibrary( pExtInternalContext->m_hExtLib );
            }

            return;
        }
    }

    // Delete internal context
    if( pExtInternalContext->m_D3D11InternalExtensions )
    {
        free( pExtInternalContext->m_D3D11InternalExtensions );
        pExtInternalContext->m_D3D11InternalExtensions = nullptr;
    }
    if( pExtInternalContext->m_D3D12InternalExtensions )
    {
        free( pExtInternalContext->m_D3D12InternalExtensions );
        pExtInternalContext->m_D3D12InternalExtensions = nullptr;
    }

    // Store off the module handle, the internal context is about to be freed.
    HMODULE hMod = pExtInternalContext->m_hExtLib;

    // One final call to FreeLibrary.  This one should actually
    // release the final OS ref count on the dll.
    if( hMod != NULL )
    {
        FreeLibrary( hMod );
    }
}

//////////////////////////////////////////////////////////////////////////
/// @brief Returns all Graphics Extensions interface versions supported on a current platform/driver/header file combination using D3D11 Device.
/// @param pDevice A pointer to the current D3D11 Device.
/// @param pSupportedExtVersions A pointer to the table of supported versions.
/// @param pSupportedExtVersionsCount A pointer to the variable that will hold the number of supported versions. Pointer is null if Init fails.
HRESULT INTC_D3D11_GetSupportedVersions(
    const ID3D11Device*   pDevice,               ///< A pointer to the current D3D11 Device.
    INTCExtensionVersion* pSupportedExtVersions, ///< A pointer to the table of supported versions.
    uint32_t*             pSupportedExtVersionsCount )       ///< A pointer to the variable that will hold the number of supported versions. Pointer is null if Init fails.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_GetSupportedVersions == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_GetSupportedVersions(
        pDevice,
        pSupportedExtVersions,
        pSupportedExtVersionsCount );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates D3D11 Graphics Extensions Device Context and returns ppfnExtensionContext Extension Context object and ppfnExtensionFuncs extension function pointers table. This function must be called prior to using extensions.
/// @param pDevice A pointer to the current Device.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
/// @param pExtensionInfo A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
/// @param pExtensionAppInfo A pointer to the ExtensionAppInfo structure that can be optionally passed to the driver identifying application and engine.
HRESULT INTC_D3D11_CreateDeviceExtensionContext(
    const ID3D11Device*    pDevice,            ///< A pointer to the current Device.
    INTCExtensionContext** ppExtensionContext, ///< A pointer to a pointer to the extension context associated with the current Device.
    INTCExtensionInfo*     pExtensionInfo,     ///< A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
    INTCExtensionAppInfo*  pExtensionAppInfo )  ///< A pointer to the ExtensionAppInfo structure that can be optionally passed to the driver identifying application and engine.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_CreateDeviceExtensionContext == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_CreateDeviceExtensionContext(
        pDevice,
        ppExtensionContext,
        pExtensionInfo,
        pExtensionAppInfo );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a device extension context for Direct3D 11.
/// @param pDevice A pointer to the Direct3D 11 device.
/// @param ppExtensionContext A pointer to a memory block that receives a pointer to the extension context.
/// @param pExtensionInfo A pointer to the extension information.
/// @param pExtensionAppInfo A pointer to the application-specific extension information.
HRESULT INTC_D3D11_CreateDeviceExtensionContext1(
    const ID3D11Device*    pDevice,            ///< A pointer to the Direct3D 11 device.
    INTCExtensionContext** ppExtensionContext, ///< A pointer to a memory block that receives a pointer to the extension context.
    INTCExtensionInfo*     pExtensionInfo,     ///< A pointer to the extension information.
    INTCExtensionAppInfo1* pExtensionAppInfo ) ///< A pointer to the application-specific extension information.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_CreateDeviceExtensionContext1 == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_CreateDeviceExtensionContext1(
        pDevice,
        ppExtensionContext,
        pExtensionInfo,
        pExtensionAppInfo );
}

//////////////////////////////////////////////////////////////////////////
/// @brief INTC_D3D11_RegisterApplicationCallbacks function sets the callback table for D3D11 API handlers. All registered callbacks will be called when the corresponding original API is called.
/// @param pCallbacks A pointer to a INTC_D3D12_API_CALLBACKS structure that registers the callbacks to D3D12 API handlers.
HRESULT INTC_D3D11_RegisterApplicationCallbacks(
    const INTC_D3D11_API_CALLBACKS* pCallbacks ) ///< A pointer to a INTC_D3D12_API_CALLBACKS structure that registers the callbacks to D3D12 API handlers.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_RegisterApplicationCallbacks == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_RegisterApplicationCallbacks(
        pCallbacks );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Returns all Graphics Extensions interface versions supported on a current platform/driver/header file combination using D3D12 Device.
/// @param pDevice A pointer to the current D3D11 Device.
/// @param pSupportedExtVersions A pointer to the table of supported versions.
/// @param pSupportedExtVersionsCount A pointer to the variable that will hold the number of supported versions. Pointer is null if Init fails.
HRESULT INTC_D3D12_GetSupportedVersions(
    const ID3D12Device*   pDevice,               ///< A pointer to the current D3D11 Device.
    INTCExtensionVersion* pSupportedExtVersions, ///< A pointer to the table of supported versions.
    uint32_t*             pSupportedExtVersionsCount )       ///< A pointer to the variable that will hold the number of supported versions. Pointer is null if Init fails.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_GetSupportedVersions == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_GetSupportedVersions(
        pDevice,
        pSupportedExtVersions,
        pSupportedExtVersionsCount );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates D3D12 Graphics Extensions Device Context and returns ppfnExtensionContext Extension Context object and ppfnExtensionFuncs extension function pointers table. This function must be called prior to using extensions.
/// @param pDevice A pointer to the current Device.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
/// @param pExtensionInfo A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
/// @param pExtensionAppInfo A pointer to the ExtensionAppInfo structure that can be optionally passed to the driver identifying application and engine.
HRESULT INTC_D3D12_CreateDeviceExtensionContext(
    const ID3D12Device*    pDevice,            ///< A pointer to the current Device.
    INTCExtensionContext** ppExtensionContext, ///< A pointer to a pointer to the extension context associated with the current Device.
    INTCExtensionInfo*     pExtensionInfo,     ///< A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
    INTCExtensionAppInfo*  pExtensionAppInfo )  ///< A pointer to the ExtensionAppInfo structure that can be optionally passed to the driver identifying application and engine.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreateDeviceExtensionContext == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreateDeviceExtensionContext(
        pDevice,
        ppExtensionContext,
        pExtensionInfo,
        pExtensionAppInfo );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates D3D12 Graphics Extensions Device Context and returns ppfnExtensionContext Extension Context object and ppfnExtensionFuncs extension function pointers table. This function must be called prior to using extensions.
/// @param pDevice A pointer to the current Device.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
/// @param pExtensionInfo A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
/// @param pExtensionAppInfo A pointer to the ExtensionAppInfo1 structure that can optionally be used in the driver to identify workload.
HRESULT INTC_D3D12_CreateDeviceExtensionContext1(
    const ID3D12Device*    pDevice,            ///< A pointer to the current Device.
    INTCExtensionContext** ppExtensionContext, ///< A pointer to a pointer to the extension context associated with the current Device.
    INTCExtensionInfo*     pExtensionInfo,     ///< A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
    INTCExtensionAppInfo1* pExtensionAppInfo ) ///< A pointer to the ExtensionAppInfo1 structure that can optionally be used in the driver to identify workload.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreateDeviceExtensionContext1 == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreateDeviceExtensionContext1(
        pDevice,
        ppExtensionContext,
        pExtensionInfo,
        pExtensionAppInfo );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates D3D12 Graphics Extensions Device Context and returns ppfnExtensionContext Extension Context object and ppfnExtensionFuncs extension function pointers table. This function must be called prior to using extensions.
/// @param pDevice A pointer to the current Device.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
/// @param pExtensionInfo A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
/// @param pExtensionAppInfo A pointer to the ExtensionAppInfo1 structure that can optionally be used in the driver to identify workload.
HRESULT INTC_D3D12_CreateDeviceExtensionContext2(
    const ID3D12Device*    pDevice,            ///< A pointer to the current Device.
    INTCExtensionContext** ppExtensionContext, ///< A pointer to a pointer to the extension context associated with the current Device.
    INTCExtensionInfo1*    pExtensionInfo,     ///< A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
    INTCExtensionAppInfo1* pExtensionAppInfo ) ///< A pointer to the ExtensionAppInfo1 structure that can optionally be used in the driver to identify workload.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreateDeviceExtensionContext2 == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreateDeviceExtensionContext2(
        pDevice,
        ppExtensionContext,
        pExtensionInfo,
        pExtensionAppInfo );
}

//////////////////////////////////////////////////////////////////////////
/// @brief INTC_D3D12_RegisterApplicationCallbacks function sets the callback table for D3D12 API handlers. All registered callbacks will be called when the corresponding original API is called.
/// @param pCallbacks A pointer to a INTC_D3D12_API_CALLBACKS structure that registers the callbacks to D3D12 API handlers.
HRESULT INTC_D3D12_RegisterApplicationCallbacks(
    const INTC_D3D12_API_CALLBACKS* pCallbacks ) ///< A pointer to a INTC_D3D12_API_CALLBACKS structure that registers the callbacks to D3D12 API handlers.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_RegisterApplicationCallbacks == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_RegisterApplicationCallbacks(
        pCallbacks );
}

//////////////////////////////////////////////////////////////////////////
/// @brief INTC_D3D12_RegisterApplicationCallbacks1 function sets the callback table for D3D12 API handlers. All registered callbacks will be called when the corresponding original API is called.
/// @param pCallbacks A pointer to a INTC_D3D12_API_CALLBACKS1 structure that registers the callbacks to D3D12 API handlers.
HRESULT INTC_D3D12_RegisterApplicationCallbacks1(
    const INTC_D3D12_API_CALLBACKS1* pCallbacks ) ///< A pointer to a INTC_D3D12_API_CALLBACKS1 structure that registers the callbacks to D3D12 API handlers.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_RegisterApplicationCallbacks1 == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_RegisterApplicationCallbacks1(
        pCallbacks );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a D3D Graphics Extensions Device Context and returns ppExtensionContext Extension Context object. This function must be called prior to using extensions when creating an extension context with a D3D11 and D3D12 device.
/// @param pD3D11Device A pointer to the current D3D11 device.
/// @param pD3D12Device A pointer to the current D3D12 device.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
/// @param pExtensionInfo A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
/// @param pExtensionAppInfo A pointer to the ExtensionAppInfo structure that can be optionally passed to the driver identifying application and engine.
HRESULT INTC_CreateDeviceExtensionContext(
    const ID3D11Device*    pD3D11Device,       ///< A pointer to the current D3D11 device.
    const ID3D12Device*    pD3D12Device,       ///< A pointer to the current D3D12 device.
    INTCExtensionContext** ppExtensionContext, ///< A pointer to a pointer to the extension context associated with the current Device.
    INTCExtensionInfo*     pExtensionInfo,     ///< A pointer to the ExtensionInfo structure. The requestedExtensionVersion member must be set prior to calling this function. The remaining members are filled in with device info about the Intel GPU and info about the graphics driver version.
    INTCExtensionAppInfo*  pExtensionAppInfo )  ///< A pointer to the ExtensionAppInfo structure that can be optionally passed to the driver identifying application and engine.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_CreateDeviceExtensionContext == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_CreateDeviceExtensionContext(
        pD3D11Device,
        pD3D12Device,
        ppExtensionContext,
        pExtensionInfo,
        pExtensionAppInfo );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a device extension context for DX12.
/// @param pD3D11Device Pointer to the D3D11 device.
/// @param pD3D12Device Pointer to the D3D12 device.
/// @param ppExtensionContext Pointer to the extension context.
/// @param pExtensionInfo Pointer to the extension information.
/// @param pExtensionAppInfo Pointer to the extension application information.
HRESULT INTC_CreateDeviceExtensionContext1(
    ID3D11Device*          pD3D11Device,       ///< Pointer to the D3D11 device.
    ID3D12Device*          pD3D12Device,       ///< Pointer to the D3D12 device.
    INTCExtensionContext** ppExtensionContext, ///< Pointer to the extension context.
    INTCExtensionInfo*     pExtensionInfo,     ///< Pointer to the extension information.
    INTCExtensionAppInfo1* pExtensionAppInfo ) ///< Pointer to the extension application information.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_CreateDeviceExtensionContext1 == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_CreateDeviceExtensionContext1(
        pD3D11Device,
        pD3D12Device,
        ppExtensionContext,
        pExtensionInfo,
        pExtensionAppInfo );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Destroys D3D12 Graphics Extensions Device Context and provides cleanup for the Graphics Extensions Framework. No D3D12 extensions can be used after calling this function.
/// @param ppExtensionContext A pointer to a pointer to the extension context associated with the current Device.
HRESULT INTC_DestroyDeviceExtensionContext(
    INTCExtensionContext** ppExtensionContext ) ///< A pointer to a pointer to the extension context associated with the current Device.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_DestroyDeviceExtensionContext == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_DestroyDeviceExtensionContext(
        ppExtensionContext );
}

//////////////////////////////////////////////////////////////////////////
/// @brief BeginUAVOverlap marks the beginning point for disabling GPU synchronization between consecutive draws and dispatches that share UAV resources.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
HRESULT INTC_D3D11_BeginUAVOverlap(
    INTCExtensionContext* pExtensionContext ) ///< A pointer to the extension context associated with the current Device.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_BeginUAVOverlap == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_BeginUAVOverlap(
        pExtensionContext );
}

//////////////////////////////////////////////////////////////////////////
/// @brief EndUAVOverlap marks the end point for disabling GPU synchronization between consecutive draws and dispatches that share UAV resources.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
HRESULT INTC_D3D11_EndUAVOverlap(
    INTCExtensionContext* pExtensionContext ) ///< A pointer to the extension context associated with the current Device.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_EndUAVOverlap == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_EndUAVOverlap(
        pExtensionContext );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Begin_Retrieve_Resource_Handle marks the beginning point for retrieving the resource driver handle, it turns on the handle retrieval flag. flag off means no subsequent resource handle retrieval, thus no performance impact for normal resource creation flow.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
HRESULT INTC_D3D11_Begin_Retrieve_Resource_Handle(
    INTCExtensionContext* pExtensionContext ) ///< A pointer to the extension context associated with the current Device.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_Begin_Retrieve_Resource_Handle == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_Begin_Retrieve_Resource_Handle(
        pExtensionContext );
}

//////////////////////////////////////////////////////////////////////////
/// @brief End_Retrieve_Resource_Handle marks the end point for retrieving the resource driver handle, it writes the resource handle to the destination memory where the application provides.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
HRESULT INTC_D3D11_End_Retrieve_Resource_Handle(
    INTCExtensionContext* pExtensionContext ) ///< A pointer to the extension context associated with the current Device.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_End_Retrieve_Resource_Handle == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_End_Retrieve_Resource_Handle(
        pExtensionContext );
}

//////////////////////////////////////////////////////////////////////////
/// @brief MultiDrawInstancedIndirect function submits multiple DrawInstancedIndirect in one call.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDeviceContext A pointer to the device context that will be used to generate rendering commands.
/// @param drawCount The number of draws.
/// @param pBufferForArgs Pointer to the Arguments Buffer.
/// @param alignedByteOffsetForArgs Offset into the Arguments Buffer.
/// @param byteStrideForArgs The stride between elements in the Argument Buffer.
void INTC_D3D11_MultiDrawInstancedIndirect(
    INTCExtensionContext* pExtensionContext,        ///< A pointer to the extension context associated with the current Device.
    ID3D11DeviceContext*  pDeviceContext,           ///< A pointer to the device context that will be used to generate rendering commands.
    UINT                  drawCount,                ///< The number of draws.
    ID3D11Buffer*         pBufferForArgs,           ///< Pointer to the Arguments Buffer.
    UINT                  alignedByteOffsetForArgs, ///< Offset into the Arguments Buffer.
    UINT                  byteStrideForArgs )                        ///< The stride between elements in the Argument Buffer.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_MultiDrawInstancedIndirect == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_MultiDrawInstancedIndirect(
        pExtensionContext,
        pDeviceContext,
        drawCount,
        pBufferForArgs,
        alignedByteOffsetForArgs,
        byteStrideForArgs );
}

//////////////////////////////////////////////////////////////////////////
/// @brief MultiDrawIndexedInstancedIndirect function submits multiple DrawIndexedInstancedIndirect in one call.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDeviceContext A pointer to the device context that will be used to generate rendering commands.
/// @param drawCount The number of draws.
/// @param pBufferForArgs Pointer to the Arguments Buffer.
/// @param alignedByteOffsetForArgs Offset into the Arguments Buffer.
/// @param byteStrideForArgs The stride between elements in the Argument Buffer.
void INTC_D3D11_MultiDrawIndexedInstancedIndirect(
    INTCExtensionContext* pExtensionContext,        ///< A pointer to the extension context associated with the current Device.
    ID3D11DeviceContext*  pDeviceContext,           ///< A pointer to the device context that will be used to generate rendering commands.
    UINT                  drawCount,                ///< The number of draws.
    ID3D11Buffer*         pBufferForArgs,           ///< Pointer to the Arguments Buffer.
    UINT                  alignedByteOffsetForArgs, ///< Offset into the Arguments Buffer.
    UINT                  byteStrideForArgs )                        ///< The stride between elements in the Argument Buffer.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_MultiDrawIndexedInstancedIndirect == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_MultiDrawIndexedInstancedIndirect(
        pExtensionContext,
        pDeviceContext,
        drawCount,
        pBufferForArgs,
        alignedByteOffsetForArgs,
        byteStrideForArgs );
}

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
void INTC_D3D11_MultiDrawInstancedIndirectCountIndirect(
    INTCExtensionContext* pExtensionContext,             ///< A pointer to the extension context associated with the current Device.
    ID3D11DeviceContext*  pDeviceContext,                ///< A pointer to the device context that will be used to generate rendering commands.
    ID3D11Buffer*         pBufferForDrawCount,           ///< Buffer that contains the number of draws.
    UINT                  alignedByteOffsetForDrawCount, ///< Offset into the Draw Count Buffer.
    UINT                  maxCount,                      ///< Maximum count of draws generated by this call.
    ID3D11Buffer*         pBufferForArgs,                ///< Pointer to the Arguments Buffer.
    UINT                  alignedByteOffsetForArgs,      ///< Offset into the Arguments Buffer.
    UINT                  byteStrideForArgs )                             ///< The stride between elements in the Argument Buffer.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_MultiDrawInstancedIndirectCountIndirect == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_MultiDrawInstancedIndirectCountIndirect(
        pExtensionContext,
        pDeviceContext,
        pBufferForDrawCount,
        alignedByteOffsetForDrawCount,
        maxCount,
        pBufferForArgs,
        alignedByteOffsetForArgs,
        byteStrideForArgs );
}

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
void INTC_D3D11_MultiDrawIndexedInstancedIndirectCountIndirect(
    INTCExtensionContext* pExtensionContext,             ///< A pointer to the extension context associated with the current Device.
    ID3D11DeviceContext*  pDeviceContext,                ///< A pointer to the device context that will be used to generate rendering commands.
    ID3D11Buffer*         pBufferForDrawCount,           ///< Buffer that contains the number of draws.
    UINT                  alignedByteOffsetForDrawCount, ///< Offset into the Draw Count Buffer.
    UINT                  maxCount,                      ///< Maximum count of draws generated by this call.
    ID3D11Buffer*         pBufferForArgs,                ///< Pointer to the Arguments Buffer.
    UINT                  alignedByteOffsetForArgs,      ///< Offset into the Arguments Buffer.
    UINT                  byteStrideForArgs )                             ///< The stride between elements in the Argument Buffer.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_MultiDrawIndexedInstancedIndirectCountIndirect == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_MultiDrawIndexedInstancedIndirectCountIndirect(
        pExtensionContext,
        pDeviceContext,
        pBufferForDrawCount,
        alignedByteOffsetForDrawCount,
        maxCount,
        pBufferForArgs,
        alignedByteOffsetForArgs,
        byteStrideForArgs );
}

//////////////////////////////////////////////////////////////////////////
/// @brief SetDepthBounds method enables you to change the depth bounds dynamically.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param bEnable Enable or disable depth bounds test.
/// @param Min Specifies the minimum depth bounds. The default value is 0. NaN values silently convert to 0.
/// @param Max Specifies the maximum depth bounds. The default value is 1. NaN values silently convert to 0.
void INTC_D3D11_SetDepthBounds(
    INTCExtensionContext* pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    BOOL                  bEnable,           ///< Enable or disable depth bounds test.
    FLOAT                 Min,               ///< Specifies the minimum depth bounds. The default value is 0. NaN values silently convert to 0.
    FLOAT                 Max )                              ///< Specifies the maximum depth bounds. The default value is 1. NaN values silently convert to 0.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_SetDepthBounds == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_SetDepthBounds(
        pExtensionContext,
        bEnable,
        Min,
        Max );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Create an array of 2D textures. Supported extensions: Emulated64bitTypedAtomics - Enable usage of 64bit Typed Atomics on a texture created.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc A pointer to a INTC_D3D11_TEXTURE2D_DESC structure that describes a 2D texture resource.
/// @param pInitialData A pointer to an array of D3D11_SUBRESOURCE_DATA structures that describe subresources for the 2D texture resource.
/// @param ppTexture2D A pointer to a buffer that receives a pointer to a ID3D11Texture2D interface for the created texture.
HRESULT INTC_D3D11_CreateTexture2D(
    INTCExtensionContext*            pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    const INTC_D3D11_TEXTURE2D_DESC* pDesc,             ///< A pointer to a INTC_D3D11_TEXTURE2D_DESC structure that describes a 2D texture resource.
    const D3D11_SUBRESOURCE_DATA*    pInitialData,      ///< A pointer to an array of D3D11_SUBRESOURCE_DATA structures that describe subresources for the 2D texture resource.
    ID3D11Texture2D**                ppTexture2D )                     ///< A pointer to a buffer that receives a pointer to a ID3D11Texture2D interface for the created texture.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D11_CreateTexture2D == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D11_CreateTexture2D(
        pExtensionContext,
        pDesc,
        pInitialData,
        ppTexture2D );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc A pointer to a D3D12_COMPUTE_PIPELINE_STATE_DESC structure that describes compute pipeline state.
/// @param riid The globally unique identifier (GUID) for the command queue interface.
/// @param ppCommandQueue A pointer to a memory block that receives a pointer to the ID3D12CommandQueue interface for the command queue.
HRESULT INTC_D3D12_CreateCommandQueue(
    INTCExtensionContext*                pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    const INTC_D3D12_COMMAND_QUEUE_DESC* pDesc,             ///< A pointer to a D3D12_COMPUTE_PIPELINE_STATE_DESC structure that describes compute pipeline state.
    REFIID                               riid,              ///< The globally unique identifier (GUID) for the command queue interface.
    void**                               ppCommandQueue )                                 ///< A pointer to a memory block that receives a pointer to the ID3D12CommandQueue interface for the command queue.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreateCommandQueue == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreateCommandQueue(
        pExtensionContext,
        pDesc,
        riid,
        ppCommandQueue );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a compute pipeline state object.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc A pointer to a D3D12_COMPUTE_PIPELINE_STATE_DESC structure that describes compute pipeline state.
/// @param riid The globally unique identifier (GUID) for the pipeline state interface.
/// @param ppPipelineState A pointer to a memory block that receives a pointer to the ID3D12PipelineState interface for the pipeline state object.
HRESULT INTC_D3D12_CreateComputePipelineState(
    INTCExtensionContext*                         pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    const INTC_D3D12_COMPUTE_PIPELINE_STATE_DESC* pDesc,             ///< A pointer to a D3D12_COMPUTE_PIPELINE_STATE_DESC structure that describes compute pipeline state.
    REFIID                                        riid,              ///< The globally unique identifier (GUID) for the pipeline state interface.
    void**                                        ppPipelineState )                                         ///< A pointer to a memory block that receives a pointer to the ID3D12PipelineState interface for the pipeline state object.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreateComputePipelineState == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreateComputePipelineState(
        pExtensionContext,
        pDesc,
        riid,
        ppPipelineState );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a resource that is reserved, which is not yet mapped to any pages in a heap.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
/// @param InitialState The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
/// @param pOptimizedClearValue Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
/// @param riid The globally unique identifier (GUID) for the resource interface.
/// @param ppvResource A pointer to a memory block that receives a pointer to the resource.
HRESULT INTC_D3D12_CreateReservedResource(
    INTCExtensionContext*           pExtensionContext,    ///< A pointer to the extension context associated with the current Device.
    const INTC_D3D12_RESOURCE_DESC* pDesc,                ///< A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
    D3D12_RESOURCE_STATES           InitialState,         ///< The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
    const D3D12_CLEAR_VALUE*        pOptimizedClearValue, ///< Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
    REFIID                          riid,                 ///< The globally unique identifier (GUID) for the resource interface.
    void**                          ppvResource )                                  ///< A pointer to a memory block that receives a pointer to the resource.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreateReservedResource == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreateReservedResource(
        pExtensionContext,
        pDesc,
        InitialState,
        pOptimizedClearValue,
        riid,
        ppvResource );
}

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
HRESULT INTC_D3D12_CreateCommittedResource(
    INTCExtensionContext*                pExtensionContext,    ///< A pointer to a D3D12_HEAP_PROPERTIES structure that provides properties for the resource's heap.
    const D3D12_HEAP_PROPERTIES*         pHeapProperties,      ///< A pointer to the ID3D12Heap interface that represents the heap in which the resource is placed.
    D3D12_HEAP_FLAGS                     HeapFlags,            ///< The offset, in bytes, to the resource.
    const INTC_D3D12_RESOURCE_DESC_0001* pDesc,                ///< A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
    D3D12_RESOURCE_STATES                InitialResourceState, ///< The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
    const D3D12_CLEAR_VALUE*             pOptimizedClearValue, ///< Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
    REFIID                               riidResource,         ///< The globally unique identifier (GUID) for the resource interface.
    void**                               ppvResource )                                       ///< A pointer to memory that receives the requested interface pointer to the created resource object.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreateCommittedResource == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreateCommittedResource(
        pExtensionContext,
        pHeapProperties,
        HeapFlags,
        pDesc,
        InitialResourceState,
        pOptimizedClearValue,
        riidResource,
        ppvResource );
}

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
HRESULT INTC_D3D12_CreateCommittedResource1(
    INTCExtensionContext*                pExtensionContext,    ///< A pointer to the extension context associated with the current Device.
    const D3D12_HEAP_PROPERTIES*         pHeapProperties,      ///< A pointer to the ID3D12Heap interface that represents the heap in which the resource is placed.
    D3D12_HEAP_FLAGS                     HeapFlags,            ///< The offset, in bytes, to the resource.
    const INTC_D3D12_RESOURCE_DESC_0002* pDesc,                ///< A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
    D3D12_RESOURCE_STATES                InitialResourceState, ///< The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
    const D3D12_CLEAR_VALUE*             pOptimizedClearValue, ///< Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
    REFIID                               riidResource,         ///< The globally unique identifier (GUID) for the resource interface.
    void**                               ppvResource )                                       ///< A pointer to memory that receives the requested interface pointer to the created resource object.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreateCommittedResource1 == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreateCommittedResource1(
        pExtensionContext,
        pHeapProperties,
        HeapFlags,
        pDesc,
        InitialResourceState,
        pOptimizedClearValue,
        riidResource,
        ppvResource );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates a heap.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc A pointer to a overridden D3D12_HEAP_DESC structure that describes the heap.
/// @param riid The globally unique identifier (GUID) for the heap interface.
/// @param ppvHeap A pointer to a memory block that receives a pointer to the heap.
HRESULT INTC_D3D12_CreateHeap(
    INTCExtensionContext*       pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    const INTC_D3D12_HEAP_DESC* pDesc,             ///< A pointer to a overridden D3D12_HEAP_DESC structure that describes the heap.
    REFIID                      riid,              ///< The globally unique identifier (GUID) for the heap interface.
    void**                      ppvHeap )                               ///< A pointer to a memory block that receives a pointer to the heap.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreateHeap == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreateHeap(
        pExtensionContext,
        pDesc,
        riid,
        ppvHeap );
}

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
HRESULT INTC_D3D12_CreatePlacedResource(
    INTCExtensionContext*                pExtensionContext,    ///< A pointer to the extension context associated with the current Device.
    ID3D12Heap*                          pHeap,                ///< A pointer to the ID3D12Heap interface that represents the heap in which the resource is placed.
    UINT64                               HeapOffset,           ///< The offset, in bytes, to the resource.
    const INTC_D3D12_RESOURCE_DESC_0001* pDesc,                ///< A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
    D3D12_RESOURCE_STATES                InitialState,         ///< The initial state of the resource, as a bitwise-OR'd combination of D3D12_RESOURCE_STATES enumeration constants.
    const D3D12_CLEAR_VALUE*             pOptimizedClearValue, ///< Specifies a D3D12_CLEAR_VALUE that describes the default value for a clear color.
    REFIID                               riid,                 ///< The globally unique identifier (GUID) for the resource interface.
    void**                               ppvResource )                                       ///< A pointer to a memory block that receives a pointer to the resource.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreatePlacedResource == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreatePlacedResource(
        pExtensionContext,
        pHeap,
        HeapOffset,
        pDesc,
        InitialState,
        pOptimizedClearValue,
        riid,
        ppvResource );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Constructs a buffer resource suitable for storing raytracing acceleration structures build on the host.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param SizeInBytes Size of the resource, in bytes.
/// @param Flags Reserved, must be zero.
/// @param riidResource Interface id for the returned resource.
/// @param ppvResource Pointer to a pointer which is set to the output resource.
HRESULT INTC_D3D12_CreateHostRTASResource(
    INTCExtensionContext* pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    size_t                SizeInBytes,       ///< Size of the resource, in bytes.
    DWORD                 Flags,             ///< Reserved, must be zero.
    REFIID                riidResource,      ///< Interface id for the returned resource.
    void**                ppvResource )                     ///< Pointer to a pointer which is set to the output resource.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreateHostRTASResource == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreateHostRTASResource(
        pExtensionContext,
        SizeInBytes,
        Flags,
        riidResource,
        ppvResource );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Builds an acceleration structure on the host timeline.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc An acceleration structure description. All GPUVA fields contained in the description are interpreted as host pointers cast to uintptr_t.
/// @param pInstanceGPUVAs For a top-level AS, this contains the GPUVA of the bottom-level AS for each instance which will be used for ray traversal.
/// @param NumInstances Number of addresses in 'pInstanceGPUVAs'.
void INTC_D3D12_BuildRaytracingAccelerationStructure_Host(
    INTCExtensionContext*                                     pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC* pDesc,             ///< An acceleration structure description. All GPUVA fields contained in the description are interpreted as host pointers cast to uintptr_t.
    const D3D12_GPU_VIRTUAL_ADDRESS*                          pInstanceGPUVAs,   ///< For a top-level AS, this contains the GPUVA of the bottom-level AS for each instance which will be used for ray traversal.
    UINT                                                      NumInstances )                                                          ///< Number of addresses in 'pInstanceGPUVAs'.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_BuildRaytracingAccelerationStructure_Host == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_BuildRaytracingAccelerationStructure_Host(
        pExtensionContext,
        pDesc,
        pInstanceGPUVAs,
        NumInstances );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Copies an acceleration structure on the host timeline.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param DestAccelerationStructureData Pointer to destination AS. Must point into a mapped Host RTAS resource.
/// @param SourceAccelerationStructureData Pointer to source AS. Must point into a mapped Host RTAS resource.
/// @param Mode See DXR spec.
void INTC_D3D12_CopyRaytracingAccelerationStructure_Host(
    INTCExtensionContext*                             pExtensionContext,               ///< A pointer to the extension context associated with the current Device.
    void*                                             DestAccelerationStructureData,   ///< Pointer to destination AS. Must point into a mapped Host RTAS resource.
    const void*                                       SourceAccelerationStructureData, ///< Pointer to source AS. Must point into a mapped Host RTAS resource.
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode )                           ///< See DXR spec.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CopyRaytracingAccelerationStructure_Host == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CopyRaytracingAccelerationStructure_Host(
        pExtensionContext,
        DestAccelerationStructureData,
        SourceAccelerationStructureData,
        Mode );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Retrieves post-build info for a host-built AS on the host timeline.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param InfoType See DXR spec.
/// @param DestBuffer Pointer to output structure (see DXR spec).
/// @param SourceRTAS Pointer to source RTAS. Must lie within a Host rtas resource.
void INTC_D3D12_EmitRaytracingAccelerationStructurePostbuildInfo_Host(
    INTCExtensionContext*                                       pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE InfoType,          ///< See DXR spec.
    void*                                                       DestBuffer,        ///< Pointer to output structure (see DXR spec).
    const void*                                                 SourceRTAS )                                                       ///< Pointer to source RTAS. Must lie within a Host rtas resource.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_EmitRaytracingAccelerationStructurePostbuildInfo_Host == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_EmitRaytracingAccelerationStructurePostbuildInfo_Host(
        pExtensionContext,
        InfoType,
        DestBuffer,
        SourceRTAS );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Retrieves pre-build info for a host-built AS.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc See DXR spec.
/// @param pInfo See DXR spec. This function gives the AS and scratch sizes for a host-built AS, which might not match the device-built equivalents.
void INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo_Host(
    INTCExtensionContext*                                       pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS* pDesc,             ///< See DXR spec.
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO*      pInfo )                 ///< See DXR spec. This function gives the AS and scratch sizes for a host-built AS, which might not match the device-built equivalents.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo_Host == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo_Host(
        pExtensionContext,
        pDesc,
        pInfo );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Copy host-built acceleration structures to/from device memory on the GPU timeline.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pCommandList A command list to receive copy commands.
/// @param DestAccelerationStructureData GPU address of destination.
/// @param SrcAccelerationStructureData GPU address of source.
/// @param Mode See DXR spec. At least one of Dest and Src must be a Host RTAS resource. The other must be a conventional DXR acceleration structure buffer.
void INTC_D3D12_TransferHostRTAS(
    INTCExtensionContext*                             pExtensionContext,             ///< A pointer to the extension context associated with the current Device.
    ID3D12GraphicsCommandList*                        pCommandList,                  ///< A command list to receive copy commands.
    D3D12_GPU_VIRTUAL_ADDRESS                         DestAccelerationStructureData, ///< GPU address of destination.
    D3D12_GPU_VIRTUAL_ADDRESS                         SrcAccelerationStructureData,  ///< GPU address of source.
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode )                         ///< See DXR spec. At least one of Dest and Src must be a Host RTAS resource. The other must be a conventional DXR acceleration structure buffer.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_TransferHostRTAS == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_TransferHostRTAS(
        pExtensionContext,
        pCommandList,
        DestAccelerationStructureData,
        SrcAccelerationStructureData,
        Mode );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Set Metadata associated with the CommandList.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pCommandList A command list to set metadata.
/// @param Metadata Metadata.
void INTC_D3D12_SetDriverEventMetadata(
    INTCExtensionContext*      pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    ID3D12GraphicsCommandList* pCommandList,      ///< A command list to set metadata.
    UINT64                     Metadata )                             ///< Metadata.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_SetDriverEventMetadata == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_SetDriverEventMetadata(
        pExtensionContext,
        pCommandList,
        Metadata );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Queries total number of bytes and number of free bytes in CPU visible local memory.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pTotalBytes A pointer to total number of bytes in CPU visible vidmem.
/// @param pFreeBytes A pointer to number of free bytes in CPU visible vidmem.
void INTC_D3D12_QueryCpuVisibleVidmem(
    INTCExtensionContext* pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    UINT64*               pTotalBytes,       ///< A pointer to total number of bytes in CPU visible vidmem.
    UINT64*               pFreeBytes )                     ///< A pointer to number of free bytes in CPU visible vidmem.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_QueryCpuVisibleVidmem == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_QueryCpuVisibleVidmem(
        pExtensionContext,
        pTotalBytes,
        pFreeBytes );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Creates an ID3D12StateObject.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc The description of the state object to create.
/// @param riid The GUID of the interface to create.
/// @param ppPipelineState The returned Raytracing pipeline state object.
HRESULT INTC_D3D12_CreateStateObject(
    INTCExtensionContext*               pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    const INTC_D3D12_STATE_OBJECT_DESC* pDesc,             ///< The description of the state object to create.
    REFIID                              riid,              ///< The GUID of the interface to create.
    void**                              ppPipelineState )                               ///< The returned Raytracing pipeline state object.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CreateStateObject == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CreateStateObject(
        pExtensionContext,
        pDesc,
        riid,
        ppPipelineState );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Performs a raytracing acceleration structure build on the GPU.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pCommandList A command list to build acceleration structure.
/// @param pDesc Description of the acceleration structure to build.
/// @param NumPostbuildInfoDescs Size of the pPostbuildInfoDescs array.
/// @param pPostbuildInfoDescs Optional array of descriptions for post-build info to generate describing properties of the acceleration structure that was built.
/// @param pComparisonDataDesc Description of the comparison data.
void INTC_D3D12_BuildRaytracingAccelerationStructure(
    INTCExtensionContext*                                                                   pExtensionContext,     ///< A pointer to the extension context associated with the current Device.
    ID3D12GraphicsCommandList*                                                              pCommandList,          ///< A command list to build acceleration structure.
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC*                               pDesc,                 ///< Description of the acceleration structure to build.
    UINT                                                                                    NumPostbuildInfoDescs, ///< Size of the pPostbuildInfoDescs array.
    const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC*                      pPostbuildInfoDescs,   ///< Optional array of descriptions for post-build info to generate describing properties of the acceleration structure that was built.
    const INTC_D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC_INSTANCE_COMPARISON_DATA* pComparisonDataDesc )  ///< Description of the comparison data.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_BuildRaytracingAccelerationStructure == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_BuildRaytracingAccelerationStructure(
        pExtensionContext,
        pCommandList,
        pDesc,
        NumPostbuildInfoDescs,
        pPostbuildInfoDescs,
        pComparisonDataDesc );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Query the driver for resource requirements to build an acceleration structure.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pDesc Description of the acceleration structure build.
/// @param pInfo The result of the query.
/// @param pComparisonDataDesc Description of the comparison data.
void INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo(
    INTCExtensionContext*                                                                   pExtensionContext,    ///< A pointer to the extension context associated with the current Device.
    const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS*                             pDesc,                ///< Description of the acceleration structure build.
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO*                                  pInfo,                ///< The result of the query.
    const INTC_D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC_INSTANCE_COMPARISON_DATA* pComparisonDataDesc ) ///< Description of the comparison data.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo(
        pExtensionContext,
        pDesc,
        pInfo,
        pComparisonDataDesc );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Sets feature support.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pFeature Pointer to the feature to be set.
HRESULT INTC_D3D12_SetFeatureSupport(
    INTCExtensionContext* pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    INTC_D3D12_FEATURE*   pFeature )           ///< Pointer to the feature to be set.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_SetFeatureSupport == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_SetFeatureSupport(
        pExtensionContext,
        pFeature );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Gets the size and alignment of memory required for a collection of resources on this adapter.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param visibleMask For single-GPU operation, set this to zero. If there are multiple GPU nodes, set bits to identify the nodes (the device's physical adapters). Each bit in the mask corresponds to a single node.
/// @param numResourceDescs The number of resource descriptors in the pResourceDescs array.
/// @param pResourceDescs A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
D3D12_RESOURCE_ALLOCATION_INFO INTC_D3D12_GetResourceAllocationInfo(
    INTCExtensionContext*                pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    UINT                                 visibleMask,       ///< For single-GPU operation, set this to zero. If there are multiple GPU nodes, set bits to identify the nodes (the device's physical adapters). Each bit in the mask corresponds to a single node.
    UINT                                 numResourceDescs,  ///< The number of resource descriptors in the pResourceDescs array.
    const INTC_D3D12_RESOURCE_DESC_0001* pResourceDescs )   ///< A pointer to a overridden D3D12_RESOURCE_DESC structure that describes the resource.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_GetResourceAllocationInfo == nullptr ) )
    {
        return { UINT64_MAX };
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_GetResourceAllocationInfo(
        pExtensionContext,
        visibleMask,
        numResourceDescs,
        pResourceDescs );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Gets information about the features that are supported by the current graphics driver.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param Feature A constant from the D3D12_FEATURES enumeration describing the feature(s) that you want to query for support.
/// @param pFeatureSupportData A pointer to a data structure that corresponds to the value of the Feature parameter. To determine the corresponding data structure for each constant, see INTC_D3D12_FEATURES.
/// @param FeatureSupportDataSize The size of the structure pointed to by the pFeatureSupportData parameter.
HRESULT INTC_D3D12_CheckFeatureSupport(
    INTCExtensionContext* pExtensionContext,   ///< A pointer to the extension context associated with the current Device.
    INTC_D3D12_FEATURES   Feature,             ///< A constant from the D3D12_FEATURES enumeration describing the feature(s) that you want to query for support.
    void*                 pFeatureSupportData, ///< A pointer to a data structure that corresponds to the value of the Feature parameter. To determine the corresponding data structure for each constant, see INTC_D3D12_FEATURES.
    UINT                  FeatureSupportDataSize )              ///< The size of the structure pointed to by the pFeatureSupportData parameter.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_CheckFeatureSupport == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_CheckFeatureSupport(
        pExtensionContext,
        Feature,
        pFeatureSupportData,
        FeatureSupportDataSize );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Sets a custom shader binary file path.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param filePath Path to a pre-built shader binary file.
HRESULT INTC_D3D12_AddShaderBinariesPath(
    INTCExtensionContext* pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    const wchar_t*        filePath )                ///< Path to a pre-built shader binary file.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_AddShaderBinariesPath == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_AddShaderBinariesPath(
        pExtensionContext,
        filePath );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Removes a custom shader binary file path.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param filePath Path to a pre-built shader binary file.
HRESULT INTC_D3D12_RemoveShaderBinariesPath(
    INTCExtensionContext* pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    const wchar_t*        filePath )                ///< Path to a pre-built shader binary file.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_RemoveShaderBinariesPath == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_RemoveShaderBinariesPath(
        pExtensionContext,
        filePath );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Register Application Info in the graphics driver.
/// @param pExtensionAppInfo Application Info to be passed to the driver.
HRESULT INTC_D3D12_SetApplicationInfo(
    INTCExtensionAppInfo1* pExtensionAppInfo ) ///< Application Info to be passed to the driver.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_SetApplicationInfo == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_SetApplicationInfo(
        pExtensionAppInfo );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Obtains an Graphics Extensions CommandListHandle associated with the D3D12 CommandList Object.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pCommandList Pointer to the D3D12 CommandList Object.
uint64_t INTC_D3D12_GetCommandListHandle(
    INTCExtensionContext* pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    void*                 pCommandList )                     ///< Pointer to the D3D12 CommandList Object.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_GetCommandListHandle == nullptr ) )
    {
        return 0;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_GetCommandListHandle(
        pExtensionContext,
        pCommandList );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Places a marker in the Command List. Markers (breadcrumbs) are then decoded in the GPU crash dump.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pCommandList A command list to set the event marker.
/// @param eventType The type of the event marker.
/// @param marker The marker data.
/// @param markerSize The size of the marker data.
void INTC_D3D12_SetEventMarker(
    INTCExtensionContext*      pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    ID3D12GraphicsCommandList* pCommandList,      ///< A command list to set the event marker.
    uint32_t                   eventType,         ///< The type of the event marker.
    const void*                marker,            ///< The marker data.
    uint32_t                   markerSize )                         ///< The size of the marker data.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_SetEventMarker == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_SetEventMarker(
        pExtensionContext,
        pCommandList,
        eventType,
        marker,
        markerSize );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Returns the current shader heap usage.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pShaderHeapUsage A pointer to a variable that receives the current shader heap usage in bytes.
HRESULT INTC_D3D12_GetCurrentShaderHeapUsage(
    INTCExtensionContext* pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    UINT64*               pShaderHeapUsage )               ///< A pointer to a variable that receives the current shader heap usage in bytes.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_GetCurrentShaderHeapUsage == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_GetCurrentShaderHeapUsage(
        pExtensionContext,
        pShaderHeapUsage );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Sets additional device information for the next/current D3D12 device.
/// @param pDeviceParams A pointer to a structure containing device params to be set.
HRESULT INTC_D3D12_SetDeviceParams(
    INTCDeviceParams* pDeviceParams ) ///< A pointer to a structure containing device params to be set.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_SetDeviceParams == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_SetDeviceParams(
        pDeviceParams );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Gets the cached blob representing the pipeline state.
/// @param pExtensionContext A pointer to the extension context associated with the current Device.
/// @param pPipelineState A pipeline state object.
/// @param ppBlob After this method returns, points to the cached blob representing the pipeline state.
/// @param flags Flags to specify the behavior of the method.
HRESULT INTC_D3D12_GetCachedBlob(
    INTCExtensionContext*        pExtensionContext, ///< A pointer to the extension context associated with the current Device.
    ID3D12PipelineState*         pPipelineState,    ///< A pipeline state object.
    ID3DBlob**                   ppBlob,            ///< After this method returns, points to the cached blob representing the pipeline state.
    INTC_D3D12_CACHED_BLOB_FLAGS flags )            ///< Flags to specify the behavior of the method.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_D3D12_GetCachedBlob == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_D3D12_GetCachedBlob(
        pExtensionContext,
        pPipelineState,
        ppBlob,
        flags );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Enables Intel Breadcrumbs GPU crash dumps - should be called *before* device creation.
/// @param flags Flags to enable the crash dump.
/// @param callbacks Callbacks to be used for the crash dump.
/// @param pPrivateData Private data that can be associated with the crash dump.
HRESULT INTC_EnableGpuCrashDumps(
    INTC_GPU_CRASH_FLAGS  flags,     ///< Flags to enable the crash dump.
    const INTC_CALLBACKS& callbacks, ///< Callbacks to be used for the crash dump.
    void*                 pPrivateData )             ///< Private data that can be associated with the crash dump.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_EnableGpuCrashDumps == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_EnableGpuCrashDumps(
        flags,
        callbacks,
        pPrivateData );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Used to determine if application GPU crash dumps are enabled.
BOOL INTC_IsGpuCrashDumpsEnabled()
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_IsGpuCrashDumpsEnabled == nullptr ) )
    {
        return FALSE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_IsGpuCrashDumpsEnabled();
}

//////////////////////////////////////////////////////////////////////////
/// @brief Disables Intel Breadcrumbs GPU crash dumps.
void INTC_DisableGpuCrashDumps()
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_DisableGpuCrashDumps == nullptr ) )
    {
        return;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_DisableGpuCrashDumps();
}

//////////////////////////////////////////////////////////////////////////
/// @brief Checks the status of the GPU Crash Dump.
/// @param Status The status of the GPU Crash Dump.
HRESULT INTC_GetGpuCrashDump(
    INTC_CRASHDUMP_STATUS& Status ) ///< The status of the GPU Crash Dump.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_GetGpuCrashDump == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_GetGpuCrashDump(
        Status );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Decodes the GPU Crash Dump and generates a text with the crash dump information.
/// @param crashDump The string buffer that receives GPU Crash Dump decoded text.
/// @param crashDumpSize The size of the crash dump. If crashDump is NULL, this will return the size of the crash dump string required.
HRESULT INTC_DecodeGpuCrashDump(
    wchar_t*  crashDump,      ///< The string buffer that receives GPU Crash Dump decoded text.
    uint32_t& crashDumpSize ) ///< The size of the crash dump. If crashDump is NULL, this will return the size of the crash dump string required.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_DecodeGpuCrashDump == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_DecodeGpuCrashDump(
        crashDump,
        crashDumpSize );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the GPU Crash Dump information in a structured format for further processing.
/// @param pCrashDumpInfo Pointer to the INTC_CRASHDUMP_INFO structure to be filled with the crash dump information.
HRESULT INTC_RetrieveGpuCrashDump(
    INTC_CRASHDUMP_INFO*& pCrashDumpInfo ) ///< Pointer to the INTC_CRASHDUMP_INFO structure to be filled with the crash dump information.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_RetrieveGpuCrashDump == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_RetrieveGpuCrashDump(
        pCrashDumpInfo );
}

//////////////////////////////////////////////////////////////////////////
/// @brief Loads the binary GPU Crash Dump data.
/// @param crashDump The raw buffer that receives GPU Crash Dump data.
/// @param crashDumpSize The size of the crash dump. If crashDump is NULL, this will return the size of the crash dump buffer required.
HRESULT INTC_LoadGpuCrashDump(
    uint8_t* crashDump,      ///< The raw buffer that receives GPU Crash Dump data.
    uint32_t crashDumpSize ) ///< The size of the crash dump. If crashDump is NULL, this will return the size of the crash dump buffer required.
{
    // Validate Graphics Extensions context
    if( pExtInternalContext == nullptr || ( pExtInternalContext &&
                                            pExtInternalContext->INTC_LoadGpuCrashDump == nullptr ) )
    {
        return E_NOINTERFACE;
    }

    // Forward the call to the appropriate
    return pExtInternalContext->INTC_LoadGpuCrashDump(
        crashDump,
        crashDumpSize );
}
