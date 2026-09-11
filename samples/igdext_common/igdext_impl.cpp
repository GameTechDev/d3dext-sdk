/*
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#define INTC_IGDEXT_D3D12

#include "igdext_impl.h"
#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>

// Instantiation of the static members
INTCExtensionContext* igdext_impl::m_pDeviceExtensionContext = nullptr;
const ID3D12Device* igdext_impl::m_pDevice = nullptr;

igdext_impl::~igdext_impl()
{
    shutdown();
}

bool igdext_impl::get_supported_versions()
{
    std::vector<INTCExtensionVersion>   supportedExtVersions;
    uint32_t                            supportedExtVersionsCount = 0;

    if( !m_pDevice )
    {
        // No device set, need to call set_device() first
        return false;
    }

    if( FAILED( INTC_D3D12_GetSupportedVersions( m_pDevice, nullptr, &supportedExtVersionsCount ) ) )
    {
        return false;
    }

    // If no supported versions were returned, no need to proceed
    if( supportedExtVersionsCount == 0 )
    {
        INTC_UnloadExtensionsLibrary();
        return false;
    }

    supportedExtVersions.resize( supportedExtVersionsCount );
    if( FAILED( INTC_D3D12_GetSupportedVersions( m_pDevice, supportedExtVersions.data(), &supportedExtVersionsCount ) ) )
    {
        return false;
    }

    // Cache the supported versions
    m_SupportedExtVersions = supportedExtVersions;

    return true;
}

bool igdext_impl::init( const INTCExtensionAppInfo1& extensionAppInfo, const INTCExtensionVersion& extensionVersion, uint32_t vendorID, uint32_t deviceID  )
{
    HRESULT result = E_FAIL;

    // Set the application info structure
    if( !set_extension_app_info( extensionAppInfo ) )
    {
        // Cannot set the application info
        return false;
    }

    // Set the requested extension version
    m_ExtensionInfo.RequestedExtensionVersion = extensionVersion;

    // Load the library and list all available versions
    if( FAILED( result = INTC_LoadExtensionsLibrary( m_LoadFromLocalDirectory, vendorID, deviceID ) ) )
    {
        switch( result )
        {
        case E_FAIL:            // Failure loading the library
            break;
        case E_NOINTERFACE:     // No current Graphics Extensions Framework API found
            break;
        }
        return false;
    }

    return true;
}

bool igdext_impl::set_device( const ID3D12Device* pDevice )
{
    HRESULT result = E_FAIL;

    // Empty D3D12 Device causes shutdown
    if( !pDevice )
    {
        shutdown( false );
        return true;
    }

    // Cache the D3D12 Device
    m_pDevice = pDevice;

    // Get supported versions for the device
    get_supported_versions();

    // Create Device Extension Context
    if( FAILED( INTC_D3D12_CreateDeviceExtensionContext2( m_pDevice, &m_pDeviceExtensionContext, &m_ExtensionInfo, &m_ExtensionAppInfo ) ) )
    {
        INTC_UnloadExtensionsLibrary();

        return false;
    }

    return true;
}

void igdext_impl::shutdown( bool unloadLibrary )
{
    if( m_pDeviceExtensionContext )
    {
        INTC_DestroyDeviceExtensionContext( &m_pDeviceExtensionContext );
    }

    INTC_UnloadExtensionsLibrary();
}

bool igdext_impl::enable_app_detection()
{
    if( m_pDevice )
    {
        // This feature is only available before the device is created
        return false;
    }

    if( FAILED( INTC_D3D12_SetApplicationInfo( &m_ExtensionAppInfo ) ) )
    {
        return false;
    }

    m_AppDetectionEnabled = true;

    return true;
}

bool igdext_impl::enable_gpu_crash_dumps( bool enable )
{
    if( enable )
    {
        // Enable GPU crash dumps
        INTC_GPU_CRASH_FLAGS flags = INTC_GPU_CRASH_FLAGS( INTC_GPU_CRASH_FLAG_MARKERS | INTC_GPU_CRASH_FLAG_SHADER_DEBUG_INFO );
        INTC_CALLBACKS callbacks = { nullptr };

        if( SUCCEEDED( INTC_EnableGpuCrashDumps( flags, callbacks, nullptr ) ) )
        {
            return true;
        }
    }
    else
    {
        // Disable GPU crash dumps
        INTC_DisableGpuCrashDumps();
        return true;
    }
    
    return false;
}

// Check if the device is at least the specified architecture/release
bool igdext_impl::device_architecture( uint32_t gmd_id )
{
    return device_architecture( INTC_GMD_ID_GET_ARCH( gmd_id ), INTC_GMD_ID_GET_RELEASE( gmd_id ) );
}

bool igdext_impl::device_architecture( uint32_t gmd_arch, uint32_t gmd_release )
{
    if( INTC_GMD_ID_GET_ARCH( m_ExtensionInfo.IntelDeviceInfo.GMDID ) >= gmd_arch &&
        INTC_GMD_ID_GET_RELEASE( m_ExtensionInfo.IntelDeviceInfo.GMDID ) >= gmd_release )
    {
        return true;
    }

    return false;
}

// Get the current performance estimate for the device
igdext_impl::INTC_PERFORMANCE igdext_impl::get_performance_estimate()
{
    switch( INTC_GMD_ID_GET_ARCH( m_ExtensionInfo.IntelDeviceInfo.GMDID ) )
    {
    case INTC_GMD_ARCH_12: // Xe Architecture
        switch( INTC_GMD_ID_GET_RELEASE( m_ExtensionInfo.IntelDeviceInfo.GMDID ) )
        {
        case INTC_GMD_ARCH_12_RELEASE_DG2_512: // Xe DG2 512 EU
        case INTC_GMD_ARCH_12_RELEASE_DG2_256: // Xe DG2 256 EU
        case INTC_GMD_ARCH_12_RELEASE_DG2_128: // Xe DG2 128 EU
            if( m_ExtensionInfo.IntelDeviceInfo.EUCount > 256 )
            {
                return INTC_PERFORMANCE_HIGH; // High performance mode for Xe DG2 512 EU
            }
            else if( m_ExtensionInfo.IntelDeviceInfo.EUCount > 128 )
            {
                return INTC_PERFORMANCE_MEDIUM;
            }
            else // Xe DG2 128 EU or lower
            {
                return INTC_PERFORMANCE_LOW;
            }
            break;

        case INTC_GMD_ARCH_12_RELEASE_XE_LP_MD: // Xe LP Medium (MTL-U282, MTL-U281, MTL-S, ARL-U, ARL-S)
        case INTC_GMD_ARCH_12_RELEASE_XE_LP_LG: // Xe LP Large (MTL-H682)
        case INTC_GMD_ARCH_12_RELEASE_XE_LPG_PLUS_LG: // Xe LPG+ Large (MTL-U282, MTL-U281, MTL-S, ARL-U, ARL-S)
            if( m_ExtensionInfo.IntelDeviceInfo.EUCount > 128 )
                return INTC_PERFORMANCE_MEDIUM;
            else
                return INTC_PERFORMANCE_LOW;
            break;
        default:
            return INTC_PERFORMANCE_UNKNOWN; // Unknown performance mode for other Xe architectures
        }
        break;

    case INTC_GMD_ARCH_20: // Xe2 Architecture
        if( m_ExtensionInfo.IntelDeviceInfo.XeCoresCount >= 28 )
        {
            return INTC_PERFORMANCE_HIGH;
        }
        else if( m_ExtensionInfo.IntelDeviceInfo.XeCoresCount >= 18 )
        {
            return INTC_PERFORMANCE_MEDIUM; // Balanced performance mode for Xe2 with 9-16 Xe cores
        }
        else 
        {
            return INTC_PERFORMANCE_LOW; // Low performance mode for Xe2 with 5-8 Xe cores
        }
        break;

    default:
        return INTC_PERFORMANCE_UNKNOWN; // Unknown performance mode for other architectures
    }
}

bool igdext_impl::enable_capture_mode()
{
    // Example of creating a device with parameters:
    INTCParamValue params[ 1 ] = {};
    params[ 0 ].Set( INTC_DEVICE_PARAM_CAPTURE_MODE, TRUE );

    INTCDeviceParams deviceParams = {};
    deviceParams.NumParamValues = sizeof( params ) / sizeof( INTCParamValue );
    deviceParams.pParamValues = params;

    if( FAILED( INTC_D3D12_SetDeviceParams( &deviceParams ) ) )
    {
        return false;
    }
    return true;
}

bool igdext_impl::get_current_shader_heap_usage( UINT64* pShaderHeapUsage )
{
    if( !m_pDeviceExtensionContext || !pShaderHeapUsage )
    {
        // Requires Device Extension Context and valid output pointer
        return false;
    }
    HRESULT hr = INTC_D3D12_GetCurrentShaderHeapUsage( m_pDeviceExtensionContext, pShaderHeapUsage );
    if( FAILED( hr ) )
    {
        return false;
    }
    return true;
}

bool igdext_impl::get_cached_blob( ID3D12PipelineState* pPipelineState, ID3DBlob** ppBlob, INTC_D3D12_CACHED_BLOB_FLAGS flags )
{
    if( !m_pDeviceExtensionContext || !pPipelineState || !ppBlob )
    {
        // Requires Device Extension Context, valid command list, pipeline state and output pointer
        return false;
    }
    HRESULT hr = INTC_D3D12_GetCachedBlob( m_pDeviceExtensionContext, pPipelineState, ppBlob, flags );
    if( FAILED( hr ) )
    {
        return false;
    }
    return true;
}

bool igdext_impl::check_feature_support( INTC_D3D12_FEATURES feature, void* pFeatureStruct, uint32_t featureStructSize )
{
    if( !m_pDeviceExtensionContext )
    {
        // Requires Device Extension Context
        return false;
    }

    return SUCCEEDED( INTC_D3D12_CheckFeatureSupport( m_pDeviceExtensionContext, feature, pFeatureStruct, featureStructSize ) );
}

INTCExtensionVersion igdext_impl::make_extension_version( uint32_t hw_feature_level, uint32_t api_version, uint32_t revision )
{
    return { hw_feature_level, api_version, revision };
}

INTCAppInfoVersion igdext_impl::make_appinfo_version( uint32_t major, uint32_t minor, uint32_t revision )
{
    return { major, minor, revision, 0 };
}

std::unique_ptr<INTCExtensionAppInfo1> igdext_impl::make_extension_app_info( const wchar_t* pApplicationName, const INTCAppInfoVersion& applicationVersion, const wchar_t* pEngineName, const INTCAppInfoVersion& engineVersion )
{
    std::unique_ptr<INTCExtensionAppInfo1> appInfo = std::make_unique<INTCExtensionAppInfo1>();

    if( pApplicationName && wcslen( pApplicationName ) > 0 )
    {
        uint32_t bufferLength = (uint32_t)wcslen( pApplicationName ) + 1;

        appInfo->pApplicationName = new wchar_t[ bufferLength ];
        wcscpy_s( const_cast<wchar_t*>( appInfo->pApplicationName ), bufferLength, pApplicationName );
        memcpy( &appInfo->ApplicationVersion, &applicationVersion, sizeof( INTCExtensionVersion ) );
    }
    else
    {
        // Incorrect structure
        return std::unique_ptr<INTCExtensionAppInfo1>( nullptr );
    }

    if( pEngineName && wcslen( pEngineName ) > 0 )
    {
        uint32_t bufferLength = (uint32_t)wcslen( pEngineName ) + 1;

        appInfo->pEngineName = new wchar_t[ bufferLength ];
        wcscpy_s( const_cast<wchar_t*>( appInfo->pEngineName ), bufferLength, pEngineName );
        memcpy( &appInfo->EngineVersion, &engineVersion, sizeof( INTCExtensionVersion ) );
    }

    return appInfo;
}

void igdext_impl::clear_extension_app_info()
{
    if( m_ExtensionAppInfo.pApplicationName )
    {
        delete[] const_cast<wchar_t*>( m_ExtensionAppInfo.pApplicationName );
    }
    if( m_ExtensionAppInfo.pEngineName )
    {
        delete[] const_cast<wchar_t*>( m_ExtensionAppInfo.pEngineName );
    }
    memset( &m_ExtensionAppInfo, 0, sizeof( INTCExtensionAppInfo1 ) );
}

bool igdext_impl::set_extension_app_info( const INTCExtensionAppInfo1& extensionAppInfo )
{
    // Delete the existing application info
    clear_extension_app_info();

    // Copy the structure contents
    if( extensionAppInfo.pApplicationName && wcslen( extensionAppInfo.pApplicationName ) > 0 )
    {
        uint32_t bufferLength = (uint32_t)wcslen( extensionAppInfo.pApplicationName ) + 1;

        m_ExtensionAppInfo.pApplicationName = new wchar_t[ bufferLength ];
        wcscpy_s( const_cast<wchar_t*>( m_ExtensionAppInfo.pApplicationName ), bufferLength, extensionAppInfo.pApplicationName );
        memcpy( &m_ExtensionAppInfo.ApplicationVersion, &extensionAppInfo.ApplicationVersion, sizeof( INTCExtensionVersion ) );
    }
    else
    {
        // Incorrect structure
        return false;
    }

    if( extensionAppInfo.pEngineName && wcslen( extensionAppInfo.pEngineName ) > 0 )
    {
        uint32_t bufferLength = (uint32_t)wcslen( extensionAppInfo.pEngineName ) + 1;

        m_ExtensionAppInfo.pEngineName = new wchar_t[ bufferLength ];
        wcscpy_s( const_cast<wchar_t*>( m_ExtensionAppInfo.pEngineName ), bufferLength, extensionAppInfo.pEngineName );
        memcpy( &m_ExtensionAppInfo.EngineVersion, &extensionAppInfo.EngineVersion, sizeof( INTCExtensionVersion ) );
    }

    return true;
}

// Tools Support
#ifdef IGDEXT_OPTIONS_TOOLS_SUPPORT
bool igdext_impl::register_api_callbacks( INTC_D3D12_API_CALLBACKS* pCallbacks )
{
    return ( INTC_D3D12_RegisterApplicationCallbacks( pCallbacks ) == S_OK );
}
bool igdext_impl::register_api_callbacks( INTC_D3D12_API_CALLBACKS1* pCallbacks )
{
    return ( INTC_D3D12_RegisterApplicationCallbacks1( pCallbacks ) == S_OK );
}

bool unregister_api_callbacks()
{
    INTC_D3D12_API_CALLBACKS callbacks = { 0 };

    return (INTC_D3D12_RegisterApplicationCallbacks( &callbacks ) == S_OK);
}
#endif // IGDEXT_OPTIONS_TOOLS_SUPPORT

void igdext_impl::print_status()
{
    if( m_LogEnabled )
    {
        std::wstring logMessage = L"Intel(R) Graphics Extensions for D3D12: \n";

        logMessage += L"    Intel App Detection:      ";
        if (m_AppDetectionEnabled)
            logMessage += L"[Enabled]\n";
        else
            logMessage += L"[Disabled]\n";

        logMessage += L"    Device Extension Context: ";
        if( m_pDeviceExtensionContext )
        {
            logMessage += L"[Enabled]\n";
            logMessage += L"        Version:              [";
            logMessage += std::to_wstring( m_ExtensionInfo.RequestedExtensionVersion.HWFeatureLevel );
            logMessage += L".";
            logMessage += std::to_wstring( m_ExtensionInfo.RequestedExtensionVersion.APIVersion );
            logMessage += L".";
            logMessage += std::to_wstring( m_ExtensionInfo.RequestedExtensionVersion.Revision );
            logMessage += L"]\n";

            // Extension Info - information about Intel (R) Graphics Extensions based on a D3D12 Device
            logMessage += L"        Device Info:          [";
            logMessage += m_ExtensionInfo.IntelDeviceInfo.GTGenerationName;
            logMessage += L"] [EU:";
            logMessage += std::to_wstring( m_ExtensionInfo.IntelDeviceInfo.EUCount );
            logMessage += L"] [Freq:";
            logMessage += std::to_wstring( m_ExtensionInfo.IntelDeviceInfo.GPUMaxFreq );
            logMessage += L"Mhz]";
            // Performance estimate
            logMessage += L" [Performance: ";
            switch( get_performance_estimate() )
            {
            case INTC_PERFORMANCE_LOW:
                logMessage += L"Low]\n";
                break;
            case INTC_PERFORMANCE_MEDIUM:
                logMessage += L"Medium]\n";
                break;
            case INTC_PERFORMANCE_HIGH:
                logMessage += L"High]\n";
                break;
            case INTC_PERFORMANCE_UNKNOWN:
                logMessage += L"Unknown]\n";
                break;
            }

            logMessage += L"        Device ID:            [";
            
            // Format GMDID as hex
            std::wstringstream ss;
            ss << L"0x" << std::hex << std::uppercase << std::setfill(L'0') << std::setw(8) << m_ExtensionInfo.IntelDeviceInfo.GMDID;
            logMessage += ss.str();
            
            // Format Arch as decimal (no trailing zeros)
            logMessage += L"] [Arch: ";
            logMessage += std::to_wstring( INTC_GMD_ID_GET_ARCH( m_ExtensionInfo.IntelDeviceInfo.GMDID ) );
            
            // Format Release as decimal (no trailing zeros)
            logMessage += L"] [Release: ";
            logMessage += std::to_wstring( INTC_GMD_ID_GET_RELEASE( m_ExtensionInfo.IntelDeviceInfo.GMDID ) );

            logMessage += L"]\n        Driver Name:          [";
            logMessage += m_ExtensionInfo.pDeviceDriverDesc ? m_ExtensionInfo.pDeviceDriverDesc : L"";
            logMessage += L"]\n";
            logMessage += L"        Driver Version:       [";
            logMessage += m_ExtensionInfo.pDeviceDriverVersion ? m_ExtensionInfo.pDeviceDriverVersion : L"";
            logMessage += L"]\n";
            logMessage += L"        Driver BuildNumber:   [";
            logMessage += std::to_wstring( m_ExtensionInfo.DeviceDriverBuildNumber );
            logMessage += L"]\n";
        }
        else
            logMessage += L"[Disabled]\n";

        logMessage += L"    Supported Versions:       ";
        if( m_SupportedExtVersions.size() > 0 )
        {
            // Maximum version
            logMessage += L"[";
            logMessage += std::to_wstring( m_SupportedExtVersions[ m_SupportedExtVersions.size() - 1 ].HWFeatureLevel );
            logMessage += L".";
            logMessage += std::to_wstring( m_SupportedExtVersions[ m_SupportedExtVersions.size() - 1 ].APIVersion );
            logMessage += L".";
            logMessage += std::to_wstring( m_SupportedExtVersions[ m_SupportedExtVersions.size() - 1 ].Revision );
            logMessage += L"] [Versions count: ";
            logMessage += std::to_wstring( m_SupportedExtVersions.size() );
            logMessage += L"]\n";
        }
        else
            logMessage += L"[Not Available]\n";

        OutputDebugString( logMessage.c_str() );
    }
}
