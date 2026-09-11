/*
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 *
 * File Name:  igdext_api.h
 *
 * Abstract:   Graphics Extensions SDK API Header file
 *
 * Notes:      This file is auto-generated.
 */

#pragma once

// Pointers only below, so a forward declaration is enough. Keeps the layout identical
// between builds while the definition stays in igdext_int.h, which public builds omit.
struct INTCInternalExtension;

struct INTCInternalExtensionContext
{
    static INTCInternalExtensionContext* Get()
    {
        static INTCInternalExtensionContext instance;

        return &instance;
    }

    HMODULE m_hExtLib; // [out] Graphics Extensions dynamic library handle

    // Function pointers to the Graphics Extensions Framework functions
    PFNINTCDX11EXT_GETSUPPORTEDVERSIONS          INTC_D3D11_GetSupportedVersions;
    PFNINTCDX11EXT_CREATEDEVICEEXTENSIONCONTEXT  INTC_D3D11_CreateDeviceExtensionContext;
    PFNINTCDX11EXT_CREATEDEVICEEXTENSIONCONTEXT1 INTC_D3D11_CreateDeviceExtensionContext1;
    PFNINTCDX11EXT_REGISTERAPPLICATIONCALLBACKS  INTC_D3D11_RegisterApplicationCallbacks;

    PFNINTCDX12EXT_GETSUPPORTEDVERSIONS          INTC_D3D12_GetSupportedVersions;
    PFNINTCDX12EXT_CREATEDEVICEEXTENSIONCONTEXT  INTC_D3D12_CreateDeviceExtensionContext;
    PFNINTCDX12EXT_CREATEDEVICEEXTENSIONCONTEXT1 INTC_D3D12_CreateDeviceExtensionContext1;
    PFNINTCDX12EXT_CREATEDEVICEEXTENSIONCONTEXT2 INTC_D3D12_CreateDeviceExtensionContext2;
    PFNINTCDX12EXT_REGISTERAPPLICATIONCALLBACKS  INTC_D3D12_RegisterApplicationCallbacks;
    PFNINTCDX12EXT_REGISTERAPPLICATIONCALLBACKS1 INTC_D3D12_RegisterApplicationCallbacks1;

    PFNINTCDX11DX12EXT_CREATEDEVICEEXTENSIONCONTEXT  INTC_CreateDeviceExtensionContext;
    PFNINTCDX11DX12EXT_CREATEDEVICEEXTENSIONCONTEXT1 INTC_CreateDeviceExtensionContext1;

    PFNINTCEXT_DESTROYDEVICEEXTENSIONCONTEXT INTC_DestroyDeviceExtensionContext;

    // Function pointers to the Graphics Extensions SDK API functions
    PFNINTCDX11EXT_BEGINUAVOVERLAP                                INTC_D3D11_BeginUAVOverlap;
    PFNINTCDX11EXT_ENDUAVOVERLAP                                  INTC_D3D11_EndUAVOverlap;
    PFNINTCDX11EXT_BEGIN_RETRIEVE_RESOURCE_HANDLE                 INTC_D3D11_Begin_Retrieve_Resource_Handle;
    PFNINTCDX11EXT_END_RETRIEVE_RESOURCE_HANDLE                   INTC_D3D11_End_Retrieve_Resource_Handle;
    PFNINTCDX11EXT_MULTIDRAWINSTANCEDINDIRECT                     INTC_D3D11_MultiDrawInstancedIndirect;
    PFNINTCDX11EXT_MULTIDRAWINDEXEDINSTANCEDINDIRECT              INTC_D3D11_MultiDrawIndexedInstancedIndirect;
    PFNINTCDX11EXT_MULTIDRAWINSTANCEDINDIRECTCOUNTINDIRECT        INTC_D3D11_MultiDrawInstancedIndirectCountIndirect;
    PFNINTCDX11EXT_MULTIDRAWINDEXEDINSTANCEDINDIRECTCOUNTINDIRECT INTC_D3D11_MultiDrawIndexedInstancedIndirectCountIndirect;
    PFNINTCDX11EXT_SETDEPTHBOUNDS                                 INTC_D3D11_SetDepthBounds;
    PFNINTCDX11EXT_CREATETEXTURE2D                                INTC_D3D11_CreateTexture2D;

    PFNINTCDX12EXT_CREATECOMMANDQUEUE                                    INTC_D3D12_CreateCommandQueue;
    PFNINTCDX12EXT_CREATECOMPUTEPIPELINESTATE                            INTC_D3D12_CreateComputePipelineState;
    PFNINTCDX12EXT_CREATERESERVEDRESOURCE                                INTC_D3D12_CreateReservedResource;
    PFNINTCDX12EXT_CREATECOMMITTEDRESOURCE                               INTC_D3D12_CreateCommittedResource;
    PFNINTCDX12EXT_CREATECOMMITTEDRESOURCE1                              INTC_D3D12_CreateCommittedResource1;
    PFNINTCDX12EXT_CREATEHEAP                                            INTC_D3D12_CreateHeap;
    PFNINTCDX12EXT_CREATEPLACEDRESOURCE                                  INTC_D3D12_CreatePlacedResource;
    PFNINTCDX12EXT_CREATEHOSTRTASRESOURCE                                INTC_D3D12_CreateHostRTASResource;
    PFNINTCDX12EXT_BUILDRAYTRACINGACCELERATIONSTRUCTURE_HOST             INTC_D3D12_BuildRaytracingAccelerationStructure_Host;
    PFNINTCDX12EXT_COPYRAYTRACINGACCELERATIONSTRUCTURE_HOST              INTC_D3D12_CopyRaytracingAccelerationStructure_Host;
    PFNINTCDX12EXT_EMITRAYTRACINGACCELERATIONSTRUCTUREPOSTBUILDINFO_HOST INTC_D3D12_EmitRaytracingAccelerationStructurePostbuildInfo_Host;
    PFNINTCDX12EXT_GETRAYTRACINGACCELERATIONSTRUCTUREPREBUILDINFO_HOST   INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo_Host;
    PFNINTCDX12EXT_TRANSFERHOSTRTAS                                      INTC_D3D12_TransferHostRTAS;
    PFNINTCDX12EXT_SETDRIVEREVENTMETADATA                                INTC_D3D12_SetDriverEventMetadata;
    PFNINTCDX12EXT_QUERYCPUVISIBLEVIDMEM                                 INTC_D3D12_QueryCpuVisibleVidmem;
    PFNINTCDX12EXT_CREATESTATEOBJECT                                     INTC_D3D12_CreateStateObject;
    PFNINTCDX12EXT_BUILDRAYTRACINGACCELERATIONSTRUCTURE                  INTC_D3D12_BuildRaytracingAccelerationStructure;
    PFNINTCDX12EXT_GETRAYTRACINGACCELERATIONSTRUCTUREPREBUILDINFO        INTC_D3D12_GetRaytracingAccelerationStructurePrebuildInfo;
    PFNINTCDX12EXT_SETFEATURESUPPORT                                     INTC_D3D12_SetFeatureSupport;
    PFNINTCDX12EXT_GETRESOURCEALLOCATIONINFO                             INTC_D3D12_GetResourceAllocationInfo;
    PFNINTCDX12EXT_CHECKFEATURESUPPORT                                   INTC_D3D12_CheckFeatureSupport;
    PFNINTCDX12EXT_ADDSHADERBINARIESPATH                                 INTC_D3D12_AddShaderBinariesPath;
    PFNINTCDX12EXT_REMOVESHADERBINARIESPATH                              INTC_D3D12_RemoveShaderBinariesPath;
    PFNINTCDX12EXT_SETAPPLICATIONINFO                                    INTC_D3D12_SetApplicationInfo;
    PFNINTCDX12EXT_GETCOMMANDLISTHANDLE                                  INTC_D3D12_GetCommandListHandle;
    PFNINTCDX12EXT_SETEVENTMARKER                                        INTC_D3D12_SetEventMarker;
    PFNINTCDX12EXT_GETCURRENTSHADERHEAPUSAGE                             INTC_D3D12_GetCurrentShaderHeapUsage;
    PFNINTCDX12EXT_SETDEVICEPARAMS                                       INTC_D3D12_SetDeviceParams;
    PFNINTCDX12EXT_GETCACHEDBLOB                                         INTC_D3D12_GetCachedBlob;

    PFNINTCEXT_ENABLEGPUCRASHDUMPS    INTC_EnableGpuCrashDumps;
    PFNINTCEXT_ISGPUCRASHDUMPSENABLED INTC_IsGpuCrashDumpsEnabled;
    PFNINTCEXT_DISABLEGPUCRASHDUMPS   INTC_DisableGpuCrashDumps;
    PFNINTCEXT_GETGPUCRASHDUMP        INTC_GetGpuCrashDump;
    PFNINTCEXT_DECODEGPUCRASHDUMP     INTC_DecodeGpuCrashDump;
    PFNINTCEXT_RETRIEVEGPUCRASHDUMP   INTC_RetrieveGpuCrashDump;
    PFNINTCEXT_LOADGPUCRASHDUMP       INTC_LoadGpuCrashDump;

    // Internal extensions

    // Function pointers to the Graphics Extensions SDK API functions

    INTCInternalExtension* m_D3D11InternalExtensions;      // [out] Enumerated list of D3D11 Internal Graphics Extensions
    uint32_t               m_D3D11InternalExtensionsCount; // [out] D3D11 Internal Graphics Extensions count
    INTCInternalExtension* m_D3D12InternalExtensions;      // [out] Enumerated list of D3D11 Internal Graphics Extensions
    uint32_t               m_D3D12InternalExtensionsCount; // [out] D3D12 Internal Graphics Extensions count
};