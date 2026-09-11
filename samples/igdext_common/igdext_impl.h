/*
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#define IGDEXT_OPTIONS_LOAD_FROM_LOCAL_DIRECTORY    1
#define IGDEXT_OPTIONS_TOOLS_SUPPORT                1
#define IGDEXT_OPTIONS_LOGS                         1

// Required includes
#ifdef INTC_IGDEXT_D3D12
    #include <d3d12.h>
    #include <dxgi1_6.h>
#endif // INTC_IGDEXT_D3D12

#include <vector>
#include <memory>
#include <string>

// Graphics Extensions Public Header
#include "igdext.h"

// Optional: Tools Support
#ifdef IGDEXT_OPTIONS_TOOLS_SUPPORT
    #include "igdext_tools.h"
#endif // IGDEXT_OPTIONS_TOOLS_SUPPORT

struct ID3D12Device;

class igdext_impl
{
public:
    igdext_impl() :
        m_ExtensionAppInfo( {} ),
        m_ExtensionInfo( { 0 } )
    {
        m_pDeviceExtensionContext = nullptr;
        m_pDevice = nullptr;
    }
    ~igdext_impl();

    // Initialize Graphics Extensions for D3D12 - load the Graphics Extensions library and enables API access
    bool init( const INTCExtensionAppInfo1& extensionAppInfo, const INTCExtensionVersion& extensionVersion, uint32_t vendorID = 0, uint32_t deviceID = 0);
    // Set the D3D12 Device and initialize Device Extension Context for Graphics Extensions API functions
    bool set_device( const ID3D12Device* pDevice );
    // Shutdown Graphics Extensions for D3D12 - unload the Graphics Extensions library
    void shutdown( bool unloadLibrary = true );


    // Get the list of supported versions for the D3D12 Device
    bool get_supported_versions();
    // Enable Intel App Detection - allows applications to register with Graphics Extensions for better workload tuning
    // This function should be called before creating D3D12 Device (does not require Device Extension Context)
    bool enable_app_detection();

    // Check if the device is at least the specified architecture/release
    bool device_architecture( uint32_t gmd_id );
    bool device_architecture( uint32_t gmd_arch, uint32_t gmd_release );

    enum INTC_PERFORMANCE
    {
        INTC_PERFORMANCE_LOW = 0,       // Low performance mode
        INTC_PERFORMANCE_MEDIUM,        // Medium performance mode
        INTC_PERFORMANCE_HIGH,          // High performance mode (enthusiast)
        
        INTC_PERFORMANCE_UNKNOWN,       // Unknown performance mode
    };

    // Get the current performance estimate for the device
    INTC_PERFORMANCE get_performance_estimate();

    // Enable Capture Mode - informs Graphics Driver that the application is running in capture mode
    bool enable_capture_mode();

    bool enable_gpu_crash_dumps( bool enable = true );

    bool get_current_shader_heap_usage( UINT64* pShaderHeapUsage );

    bool get_cached_blob( ID3D12PipelineState* pPipelineState, ID3DBlob** ppBlob, INTC_D3D12_CACHED_BLOB_FLAGS flags );
        
    bool check_feature_support( INTC_D3D12_FEATURES feature, void* pFeatureStruct, uint32_t featureStructSize );

    // Format the Graphics Extensions Version structure
    INTCExtensionVersion make_extension_version( uint32_t hw_feature_level, uint32_t api_version, uint32_t revision = 0 );
    // Format the Graphics Extensions App Info Version structure
    INTCAppInfoVersion make_appinfo_version( uint32_t major, uint32_t minor, uint32_t revision = 0 );
    // Prepare the Application Info structure for Graphics Extensions
    std::unique_ptr<INTCExtensionAppInfo1> make_extension_app_info( const wchar_t* pApplicationName, const INTCAppInfoVersion& applicationVersion, const wchar_t* pEngineName = nullptr, const INTCAppInfoVersion& engineVersion = {  } );


    // Return the Device used by Graphics Extensions
    const ID3D12Device* get_device() const { return m_pDevice; }
    // Return the Device Extension Context
    INTCExtensionContext* get_device_extension_context() const { return m_pDeviceExtensionContext; }

    // Tools Support
#ifdef IGDEXT_OPTIONS_TOOLS_SUPPORT
    bool register_api_callbacks( INTC_D3D12_API_CALLBACKS* pCallbacks );
    bool register_api_callbacks( INTC_D3D12_API_CALLBACKS1* pCallbacks );
    bool unregister_api_callbacks();
#endif // IGDEXT_OPTIONS_TOOLS_SUPPORT

    // Log the message to the console
    void print_status();

private:
    bool                                m_LoadFromLocalDirectory = IGDEXT_OPTIONS_LOAD_FROM_LOCAL_DIRECTORY ? true : false;
    bool                                m_LogEnabled = IGDEXT_OPTIONS_LOGS ? true : false;

    // Context
    static INTCExtensionContext*        m_pDeviceExtensionContext;      // Graphics Extensions Device Context - used by Graphics Extensions API functions to identify the device
    static const ID3D12Device*          m_pDevice;                      // D3D12 Device - used by Graphics Extensions API functions to identify the device

    INTCExtensionAppInfo1               m_ExtensionAppInfo = {  };      // Application Info structure
    INTCExtensionInfo1                  m_ExtensionInfo = { 0 };        // Extension Info structure - information about Graphics Extensions

    std::vector<INTCExtensionVersion>   m_SupportedExtVersions;         // List of supported versions for the D3D12 Device

    // Status
    bool                                m_AppDetectionEnabled = false;  // App Detection enabled

    // Clear the application info for Graphics Extensions
    void clear_extension_app_info();
    // Set the application info for Graphics Extensions
    bool set_extension_app_info( const INTCExtensionAppInfo1& extensionAppInfo );
};