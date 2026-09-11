/*
 *
 * Copyright (C) 2016-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 *
 * @file igdext_helper.h
 *
 * @brief Functions that help finding and loading igdext64.dll and igdext32.dll
 *        libraries.
 */

#pragma once

#ifdef _WIN32
#include <devguid.h>    // for GUID_DEVCLASS_DISPLAY
#include <initguid.h>   // for DEVPKEY_*
#include <Devpkey.h>    // for DEVPKEY_*
#include <cfgmgr32.h>   // for DEVINST
#include <SetupAPI.h>
#include <Shlwapi.h>
#include <psapi.h>      // PS API needed only for EnumProcessModules in LoadIntelExtensionsLibrary
#endif

#ifdef _WIN64
#define D3D_EXT_DLL     L"igdext64.dll"
#else 
#define D3D_EXT_DLL     L"igdext32.dll"
#endif

#define INTC_INTEL_VENDOR_ID    0x8086 

typedef decltype( &PathRemoveFileSpecW )                PathRemoveFileSpecWT;
typedef decltype( &SetupGetInfDriverStoreLocationW )    SetupGetInfDriverStoreLocationWT;
typedef decltype( &CM_Get_Device_ID_ListW )             CM_Get_Device_ID_ListWT;
typedef decltype( &CM_Get_Device_ID_List_SizeW )        CM_Get_Device_ID_List_SizeWT;
typedef decltype( &CM_Get_DevNode_PropertyW )           CM_Get_DevNode_PropertyWT;
typedef decltype( &CM_Locate_DevNodeW )                 CM_Locate_DevNodeWT;
typedef decltype( &CM_MapCrToWin32Err )                 CM_MapCrToWin32ErrT;

struct DependecyFunctions
{
    HMODULE                             module_shlwapi;
    HMODULE                             module_setupapi;
    HMODULE                             module_cfgmgr32;

    PathRemoveFileSpecWT                PathRemoveFileSpecW;
    SetupGetInfDriverStoreLocationWT    SetupGetInfDriverStoreLocationW;
    CM_Get_Device_ID_ListWT             CM_Get_Device_ID_ListW;
    CM_Get_Device_ID_List_SizeWT        CM_Get_Device_ID_List_SizeW;
    CM_Get_DevNode_PropertyWT           CM_Get_DevNode_PropertyW;
    CM_Locate_DevNodeWT                 CM_Locate_DevNodeW;
    CM_MapCrToWin32ErrT                 CM_MapCrToWin32Err;
};

static DependecyFunctions dep = { 0 };

struct DeviceInfo
{
    wchar_t     driverPath[ MAX_PATH ];
    wchar_t     deviceIDString[ MAX_DEVICE_ID_LEN ];
    DEVINST     deviceInstance;

    uint32_t    DeviceID;
    uint32_t    VendorID;

    DeviceInfo* next;
};

enum LOG_LEVEL
{
    LOG_OFF     = 0,
    LOG_ERROR   = 1,
    LOG_INFO    = 2,
    LOG_DEBUG   = 3,
};

struct INTC_LIB_OPTIONS
{
    wchar_t*    INTC_ALT_DRIVER_EXTENSIONS_PATH;
    int         INTC_IGDEXT_DEBUG_LOG_LEVEL;
    int         INTC_IGDEXT_DEVICE_INDEX_PREFERENCE;            // Index (1 based!)
};

extern INTC_LIB_OPTIONS                g_Options;

__inline void LogOut( int log_level, const char* format, ... )
{
    // Filter log level
    if( log_level > g_Options.INTC_IGDEXT_DEBUG_LOG_LEVEL )
        return;

    char        buf[ 1024 ] = { 0 };
    va_list     args;

    // Add log level prefix
    switch( log_level )
    {
    case LOG_ERROR:
        strcpy_s( buf, sizeof( buf ), "[INTC_D3D12][ERROR] " );
        break;
    case LOG_INFO:
        strcpy_s( buf, sizeof( buf ), "[INTC_D3D12][INFO] " );
        break;
    case LOG_DEBUG:
        strcpy_s( buf, sizeof( buf ), "[INTC_D3D12][DEBUG] " );
        break;
    }

    va_start( args, format );
    vsprintf_s( &buf[ strlen( buf ) ], sizeof( buf ) - strlen( buf ), format, args );
    va_end( args );

    strcat_s( buf, sizeof( buf ), "\n" );

    // Print to the Debug Output
    OutputDebugString( buf );

    return;
}


////////////////////////////////////////////////////////////////////////////////////////
/// @brief This function can be used to request a value of any device property.                     
/// There are many types of properties values. Refer to devpkey.h for more details.          
/// Function SetupDiGetDeviceProperty() inside GetPropertyFromDevice() fills a property value
/// in a correct format, but always returns the value as a pointer to a string of bytes.     
/// The string of bytes must be casted outside of the function GetPropertyFromDevice()       
/// to get a value in a format suitable for the given type of property.                      
////////////////////////////////////////////////////////////////////////////////////////
static bool GetPropertyFromDevice(
    DEVINST             devInst,
    const DEVPROPKEY&   PropertyKey,
    BYTE*&              PropertyData )
{
    unsigned long   propertySize = 0;
    DEVPROPTYPE     propertyType;

    // Request a size, in bytes, required for a buffer in which property value will be stored.
    // CM_Get_DevNode_PropertyW() returns false and ERROR_INSUFFICIENT_BUFFER for the call
    CONFIGRET       status = dep.CM_Get_DevNode_PropertyW( devInst, &PropertyKey, &propertyType, NULL, &propertySize, 0 );
    if( status != CR_BUFFER_SMALL )
    {
        return false;
    }

    // Allocate memory for the buffer
    PropertyData = (BYTE*)malloc( propertySize );

    // Fill in the buffer with property value
    status = dep.CM_Get_DevNode_PropertyW( devInst, &PropertyKey, &propertyType, &PropertyData[ 0 ], &propertySize, 0 );
    if( status != CR_SUCCESS )
    {
        free( PropertyData );
        PropertyData = nullptr;

        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the driver installation path for the given device. 
////////////////////////////////////////////////////////////////////////////////////////
static bool Device_GetDriverPath( DeviceInfo* Device )
{
    BYTE* propertyData = nullptr;

    // Get the oem INF name
    if( !GetPropertyFromDevice( Device->deviceInstance, DEVPKEY_Device_DriverInfPath, propertyData ) )
    {
        return false;
    }
    const wchar_t* propertyInfName = reinterpret_cast<const wchar_t*>( &propertyData[ 0 ] );

    // Get the fully qualified name of the inf file in the driver store (directory path and file name)
    if( !dep.SetupGetInfDriverStoreLocationW( &propertyInfName[ 0 ], NULL, NULL, &Device->driverPath[ 0 ], MAX_PATH, NULL ) )
    {
        free( propertyData );
        propertyData = nullptr;
        return false;
    }

    free( propertyData );
    propertyData = nullptr;

    // Remove backslash and file name from the fully qualified name to get the directory
    dep.PathRemoveFileSpecW( &Device->driverPath[ 0 ] );
    if( 0 == wcslen( Device->driverPath ) )
    {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Checks whether the Vendor ID and Device ID match with the information in Device ID string.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool Device_GetVendorAndDeviceID( DeviceInfo* Device )
{
    if( !Device || !Device->deviceIDString[0] )
    {
        return false;
    }

    wchar_t* isVendorIDBegin = wcsstr( Device->deviceIDString, L"VEN_" );
    if( isVendorIDBegin )
    {
        // The Vendor ID hex string starts at the end of "VEN_".
        isVendorIDBegin = isVendorIDBegin + 4;

        // Convert hex string to integer
        if( isVendorIDBegin )
        {
            wchar_t* End;
            Device->VendorID = wcstol( isVendorIDBegin, &End, 16 );
        }
    }

    wchar_t* isDeviceIDBegin = wcsstr( Device->deviceIDString, L"DEV_" );
    if( isDeviceIDBegin )
    {
        // The Device ID hex string starts at the end of "DEV_".
        isDeviceIDBegin = isDeviceIDBegin + 4;

        // Convert hex string to integer
        if( isDeviceIDBegin )
        {
            wchar_t* End;
            Device->DeviceID = wcstol( isDeviceIDBegin, &End, 16 );
        }
    }

    if( Device->VendorID && Device->DeviceID )
    {
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Checks whether the Vendor ID and Device ID match with the information in Device ID string.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool Device_IsVendorAndDeviceIDMatch( DeviceInfo* Device, size_t InputVendorID, size_t InputDeviceID )
{
    if( ( Device->VendorID == InputVendorID || Device->VendorID == 0x1002 ) &&  // Allow AMD VendorID for some workloads where MSFT uses AMD vendor ID with Intel device ID
        Device->DeviceID == InputDeviceID )
    {
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////
/// @brief Matches enumerated Graphics Device Driver path with one of the modules 
///        enumerated in current process and makes sure it is located in DriverStore.
////////////////////////////////////////////////////////////////////////////////////////
static bool Device_MatchDevicePath( DeviceInfo*& Devices, wchar_t* Path )
{
    DeviceInfo* CurrentDevice = Devices;
    while ( CurrentDevice )
    {
        // We do not check VendorID, because of the AMD VendorID usage in some workloads where MSFT uses AMD vendor ID with Intel device ID
        if( wcsstr( Path, CurrentDevice->driverPath ) &&            // Path(module) matches device path
            wcsstr( Path, L"DriverStore\\FileRepository" ) )        // Path(module) is part of the DriverStore location
        {
            return true;
        }

        CurrentDevice = CurrentDevice->next;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////
/// @brief Destroys Devices list
////////////////////////////////////////////////////////////////////////////////////////
static void DestroyDevicesList( DeviceInfo*& Devices )
{
    DeviceInfo* CurrentDevice = Devices;
    while ( CurrentDevice )
    {
        DeviceInfo* nextDevice = CurrentDevice->next;

        free( CurrentDevice );

        CurrentDevice = nextDevice;
    }
    Devices = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////
/// @brief Builds Devices list based on the DeviceID list string
////////////////////////////////////////////////////////////////////////////////////////
static void ParseDeviceIDString( DeviceInfo*& Devices, wchar_t* DeviceIDList, size_t DeviceIDListSize )
{
    // Remove terminating null character to avoid adding empty string at the end
    // NextDeviceSlot always points to the next-pointer slot in the list where the next node should be stored.
    // Starting at &Devices means the first store is directly into the caller-visible output parameter,
    // which lets Coverity's escape analysis see that allocated nodes outlive this function.
    DeviceInfo** NextDeviceSlot = &Devices;
    uint32_t     DeviceIndex = 0;

    LogOut( LOG_DEBUG, "Enumerating device drivers...");
    wchar_t* DeviceIDString = DeviceIDList;
    do
    {
        if (DeviceIDString == nullptr)
        {
            LogOut( LOG_DEBUG, "Invalid pointer...");
            return;
        }

        if( wcslen( DeviceIDString ) )
        {
            DEVINST devInst;
            bool preferredDevice = ( g_Options.INTC_IGDEXT_DEVICE_INDEX_PREFERENCE > 0 && g_Options.INTC_IGDEXT_DEVICE_INDEX_PREFERENCE == DeviceIndex + 1 );

            // Locate the node
            CONFIGRET crLocateDevNode = dep.CM_Locate_DevNodeW(
                &devInst,
                DeviceIDString,
                CM_LOCATE_DEVNODE_NORMAL );

            if( crLocateDevNode == CR_SUCCESS )
            {
                // There can be many drivers on the system from past installs.
                // CR_NO_SUCH_DEVNODE is returned for drivers that don't match any devices.
                // It's ok to skip these.

                // Create new DeviceInfo
                DeviceInfo* NewDevice = (DeviceInfo*)malloc( sizeof( DeviceInfo ) );
                if (NewDevice == nullptr)
                {
                    LogOut( LOG_DEBUG, "Failed to allocate memory...");
                    DestroyDevicesList(Devices);
                    return;
                }
                NewDevice->VendorID = 0;
                NewDevice->DeviceID = 0;
                NewDevice->driverPath[ 0 ] = 0;
                NewDevice->deviceInstance = devInst;
                NewDevice->deviceIDString[ 0 ] = 0;
                wcscpy_s( &NewDevice->deviceIDString[ 0 ], MAX_DEVICE_ID_LEN, DeviceIDString );
                NewDevice->next = nullptr;

                // Append to list and advance NextDeviceSlot to the new node's next slot
                *NextDeviceSlot = NewDevice;
                NextDeviceSlot  = &NewDevice->next;

                // Get driver details
                Device_GetDriverPath( NewDevice );
                Device_GetVendorAndDeviceID( NewDevice );

                // Display debug entry
                LogOut( LOG_DEBUG, "Device[%d%s] | DeviceIDString: %S | VendorID[0x%04x] DeviceID[0x%04x] DriverPath[%S]", DeviceIndex, preferredDevice ? "*" : "", reinterpret_cast<wchar_t*>( DeviceIDString ), NewDevice->VendorID, NewDevice->DeviceID, &NewDevice->driverPath[ 0 ] );
            }
            else if (crLocateDevNode == CR_NO_SUCH_DEVNODE )
            {
                LogOut( LOG_DEBUG, "Device[%d%s] | DeviceIDString: %S | skipped [NO_DEVICE]", DeviceIndex, preferredDevice ? "*" : "", reinterpret_cast<wchar_t*>( DeviceIDString ) );
            }
            else
            {
                LogOut( LOG_DEBUG, "Device[%d%s] | DeviceIDString: %S | skipped [OTHER: 0x%08x]", DeviceIndex, preferredDevice ? "*" : "", reinterpret_cast<wchar_t*>( DeviceIDString ), crLocateDevNode );
            }
        }

        // Find next DeviceID substring
        DeviceIDString = wcschr( DeviceIDString, L'\0' ) + 1;
        DeviceIndex++;
    } while( DeviceIDString < DeviceIDList + DeviceIDListSize );
    LogOut( LOG_DEBUG, "Enumerating device drivers finished!" );
}

////////////////////////////////////////////////////////////////////////////////////////
/// @brief Builds a device list based on the DeviceID list string
////////////////////////////////////////////////////////////////////////////////////////
static HRESULT BuildDevicesList( DeviceInfo*& Devices )
{
    CONFIGRET   cr = CR_SUCCESS;
    wchar_t     DisplayDevClassGUID[ 40 ];
    ULONG       DeviceIDListSize = 0;
    wchar_t*    DeviceIDList = nullptr;

    if (!StringFromGUID2( GUID_DEVCLASS_DISPLAY, DisplayDevClassGUID, _countof( DisplayDevClassGUID )))
    {
        LogOut( LOG_DEBUG, "Failed to build device list...");
        return E_FAIL;
    }

    cr = dep.CM_Get_Device_ID_List_SizeW(
        &DeviceIDListSize,
        DisplayDevClassGUID,
        CM_GETIDLIST_FILTER_CLASS ); // we don't want to use CM_GETIDLIST_FILTER_PRESENT in order to support safe mode.
    if( cr != CR_SUCCESS )
    {
        return E_FAIL;
    }

    DeviceIDList = (wchar_t*)malloc( DeviceIDListSize * sizeof( wchar_t ) );
    
    if (DeviceIDList == nullptr)
    {
        LogOut( LOG_DEBUG, "Failed to allocate memory...");
        return E_FAIL;
    }

    // Get the list of device IDs in a string format
    cr = dep.CM_Get_Device_ID_ListW(
        DisplayDevClassGUID,
        DeviceIDList,
        DeviceIDListSize,
        CM_GETIDLIST_FILTER_CLASS );

    if( cr != CR_SUCCESS )
    {
        if( DeviceIDList )
        {
            free( DeviceIDList );
            DeviceIDList = nullptr;
        }
        return E_FAIL;
    }

    // Parse the DeviceID string and build the list of devices
    ParseDeviceIDString( Devices, DeviceIDList, DeviceIDListSize );

    if( DeviceIDList )
    {
        free( DeviceIDList );
        DeviceIDList = nullptr;
    }

    return S_OK;
}

__inline void ClearDependencies()
{
    if( dep.module_shlwapi )
    {
        FreeLibrary( dep.module_shlwapi );
        dep.module_shlwapi = nullptr;
    }
    if( dep.module_setupapi )
    {
        FreeLibrary( dep.module_setupapi );
        dep.module_setupapi = nullptr;
    }
    if( dep.module_cfgmgr32 )
    {
        FreeLibrary( dep.module_cfgmgr32 );
        dep.module_cfgmgr32 = nullptr;
    }
}

__inline bool LoadDependecies()
{
    wchar_t systemDir[MAX_PATH];
    wchar_t fullPath[MAX_PATH];
    
    // Get the system directory path
    if (GetSystemDirectoryW(systemDir, MAX_PATH) == 0)
    {
        return false;
    }
    
    // Load shlwapi.dll from system directory
    if (swprintf_s(fullPath, MAX_PATH, L"%s\\shlwapi.dll", systemDir) < 0)
    {
        return false;
    }
    if( (dep.module_shlwapi = LoadLibraryW( fullPath )) )
    {
        if( !( dep.PathRemoveFileSpecW = (PathRemoveFileSpecWT)GetProcAddress( dep.module_shlwapi, "PathRemoveFileSpecW" ) ) )
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    
    // Load setupapi.dll from system directory
    if (swprintf_s(fullPath, MAX_PATH, L"%s\\setupapi.dll", systemDir) < 0)
    {
        return false;
    }
    if( ( dep.module_setupapi = LoadLibraryW( fullPath ) ) )
    {
        if( !( dep.SetupGetInfDriverStoreLocationW = (SetupGetInfDriverStoreLocationWT)GetProcAddress( dep.module_setupapi, "SetupGetInfDriverStoreLocationW" ) ) )
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    
    // Load cfgmgr32.dll from system directory
    if (swprintf_s(fullPath, MAX_PATH, L"%s\\cfgmgr32.dll", systemDir) < 0)
    {
        return false;
    }
    if( ( dep.module_cfgmgr32 = LoadLibraryW( fullPath ) ) )
    {
        if( !( dep.CM_Get_Device_ID_ListW = (CM_Get_Device_ID_ListWT)GetProcAddress( dep.module_cfgmgr32, "CM_Get_Device_ID_ListW" ) ) )
        {
            return false;
        }
        if( !( dep.CM_Get_Device_ID_List_SizeW = (CM_Get_Device_ID_List_SizeWT)GetProcAddress( dep.module_cfgmgr32, "CM_Get_Device_ID_List_SizeW" ) ) )
        {
            return false;
        }
        if( !( dep.CM_Get_DevNode_PropertyW = (CM_Get_DevNode_PropertyWT)GetProcAddress( dep.module_cfgmgr32, "CM_Get_DevNode_PropertyW" ) ) )
        {
            return false;
        }
        if( !( dep.CM_Locate_DevNodeW = (CM_Locate_DevNodeWT)GetProcAddress( dep.module_cfgmgr32, "CM_Locate_DevNodeW" ) ) )
        {
            return false;
        }
        if( !( dep.CM_MapCrToWin32Err = (CM_MapCrToWin32ErrT)GetProcAddress( dep.module_cfgmgr32, "CM_MapCrToWin32Err" ) ) )
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

__inline wchar_t* LoadEnvVar( const wchar_t* var )
{
    size_t   requiredSize = 0;
    wchar_t* buffer = nullptr;

    _wgetenv_s( &requiredSize, NULL, 0, var );
    if( requiredSize > 0 )
    {
        buffer = (wchar_t*)malloc( requiredSize * sizeof(wchar_t) );
        _wgetenv_s( &requiredSize, buffer, requiredSize, var );
    }

    return buffer;
}

__inline void LoadOptions( INTC_LIB_OPTIONS* options )
{
    wchar_t* var = nullptr;

    if( ( var = LoadEnvVar( L"INTC_ALT_DRIVER_EXTENSIONS_PATH" ) ) != nullptr )
    {
        options->INTC_ALT_DRIVER_EXTENSIONS_PATH = var;
    }
    if( ( var = LoadEnvVar( L"INTC_IGDEXT_DEBUG_LOG_LEVEL" ) ) != nullptr )
    {
        wchar_t* end;
        options->INTC_IGDEXT_DEBUG_LOG_LEVEL = wcstol( var, &end, 10 );
        free( var );
    }
    if( ( var = LoadEnvVar( L"INTC_IGDEXT_DEVICE_INDEX_PREFERENCE" ) ) != nullptr )
    {
        wchar_t* end;
        options->INTC_IGDEXT_DEVICE_INDEX_PREFERENCE = wcstol( var, &end, 10 ) + 1;         // 1 based internally (so we know if it was set, and zero index is valid)
        free( var );
    }
}

__inline void DestroyOptions( INTC_LIB_OPTIONS* options )
{
    if( options->INTC_ALT_DRIVER_EXTENSIONS_PATH != nullptr )
    {
        free( options->INTC_ALT_DRIVER_EXTENSIONS_PATH );
        options->INTC_ALT_DRIVER_EXTENSIONS_PATH = nullptr;
    }
}

// Log out last Win32 error
__inline void LogOutGetLastError()
{
    DWORD errorMessageID = ::GetLastError();    // Get the error message, if any.
    if( errorMessageID == 0 )
        return;                                 // No error message have been recorded

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), (LPSTR)&messageBuffer, 0, NULL );

    char    buf[ 1024 ];
    strcpy_s( buf, sizeof(buf), messageBuffer );

    LogOut( LOG_ERROR, "GetLastError reason: %s", buf );

    LocalFree( messageBuffer );
}

////////////////////////////////////////////////////////////////////////////////////////
/// @brief Extension library loading helper function.
/// @details 
///     Function helps load D3D11 Extensions Framework and return hLibModule handle. 
///     If useCurrentProcessDir is set, the function tries to load the library from the current
///     process directory first. If that was unsuccessful or useCurrentProcessDir was not set, 
///     it tries to find the full path to the Intel DX11 UMD Driver module that must be loaded
///     by the current process. Library is loaded from the same path (whether it is DriverStore
///     location or system32 folder).
/// @param useCurrentProcessDir If set, the function tries to load the library from the current
///        process directory first.
////////////////////////////////////////////////////////////////////////////////////////
__inline HMODULE LoadIntelExtensionsLibrary(
    BOOL                    useCurrentProcessDir = false,
    size_t                  VendorID = 0,
    size_t                  DeviceID = 0 )
{
#ifdef _WIN32
    HMODULE             hLibModule = NULL;
    HANDLE              hProc = GetCurrentProcess();
    HMODULE             hMods[ 1024 ];
    DWORD               cbNeeded;
    wchar_t             szModFullPath[ MAX_PATH ];
    wchar_t             szPath[ MAX_PATH ] = { 0 };
    size_t              szExtDllNameLength = wcslen( D3D_EXT_DLL );
    size_t              requiredSize = 0;
    bool                loadLibrary = false;
    DeviceInfo*         Devices = nullptr;
    HRESULT             hr = S_OK;

    // Load environment variable options for static library
    LoadOptions( &g_Options );

    // This helper function will try to load the library in the specific order:
    // 1. OS environment variable INTC_ALT_DRIVER_EXTENSIONS_PATH=path\to\dll is set.
    // 2. Current directory, if not loaded with 1.
    // 3. Current display driver module path - DEFAULT location!

    // Try to load the library from an OS environment path location
    if( g_Options.INTC_ALT_DRIVER_EXTENSIONS_PATH &&
        wcslen( g_Options.INTC_ALT_DRIVER_EXTENSIONS_PATH ) + szExtDllNameLength <= MAX_PATH )
    {
        wcscpy_s( szPath, MAX_PATH, g_Options.INTC_ALT_DRIVER_EXTENSIONS_PATH );

        size_t index = wcslen( szPath ) - 1;
        wchar_t* pFileName = &szPath[ index + 1 ];      // Pointer to the library filename location

        // Add backslash if missing
        if( szPath[ index ] != '\\' )
        {
            szPath[ index + 1 ] = '\\';
            szPath[ index + 2 ] = 0;
            pFileName = &szPath[ index + 2 ];
        }


        // Copy library filename
        memcpy_s( pFileName, MAX_PATH, D3D_EXT_DLL, ( szExtDllNameLength + 1 ) * sizeof( wchar_t ) );

        LogOut( LOG_DEBUG, "Loading Graphics Extensions library from env var: \"%S\"... ", szPath );

        // Make sure the file exists - if not, we can still try default path
        if( _waccess( szPath, 0 ) == 0 )
        {
            loadLibrary = true;
        }
        else
        {
            LogOut( LOG_ERROR, "Cannot load Graphics Extensions library from: \"%S\"! Cannot access the path specified. Trying default method...", szPath );
        }
    }

    DestroyOptions( &g_Options );

    // Try to load library from the current process directory
    if( useCurrentProcessDir && !loadLibrary)
    {
        if( GetModuleFileNameW( NULL, szModFullPath, sizeof( szModFullPath ) / sizeof( wchar_t ) ) )
        {
            wcscpy_s( szPath, MAX_PATH, szModFullPath );

            // Build full path to the module
            wchar_t* pFileName = wcsrchr(szPath, '\\' );
            if( pFileName != nullptr )
            {
                size_t  modNameLength = wcslen( pFileName );
                size_t  szPathLength = wcslen( szPath );

                if( modNameLength > 0 )
                {
                    pFileName++;        // Skip slash '\'
                }

                if( szPathLength + 1 - modNameLength + szExtDllNameLength <= MAX_PATH )
                {
                    memcpy_s( pFileName, MAX_PATH, D3D_EXT_DLL, ( szExtDllNameLength + 1 ) * sizeof( wchar_t ) );
                }
                else
                {
                    // Something is wrong with the current process path, try using library name only
                    wcscpy_s( szPath, szExtDllNameLength, D3D_EXT_DLL );
                }
            }
            else
            {
                // Something is wrong with the current process path, try using library name only
                wcscpy_s( szPath, szExtDllNameLength, D3D_EXT_DLL);
            }

            LogOut( LOG_DEBUG, "Loading Graphics Extensions library from the current folder: \"%S\"... ", szPath );

            // Make sure the file exists - if not, we can still try default path
            if( _waccess( szPath, 0 ) == 0 )
            {
                loadLibrary = true;
            }
            else
            {
                LogOut( LOG_ERROR, "Cannot load Graphics Extensions library from: \"%S\"! Cannot access the path specified. Trying default method...", szPath );
            }
        }
        else
        {
            return NULL;
        }
    }

    // Build the list of devices and paths to its drivers
    if( !loadLibrary )
    {
        // Load dynamic dependencies
        if( !LoadDependecies() )
        {
            ClearDependencies();
            return NULL;
        }

        // Try to load library from the Intel Graphics Driver location (most likely DriverStore or system32)
        if( FAILED( hr = BuildDevicesList( Devices ) ) )
        {
            // Remove Graphics Devices list
            DestroyDevicesList( Devices );

            // Failed to find any graphics device instances
            return NULL;
        }

        // Iterate through the list of Graphics Devices and obtain a driver path location
        DeviceInfo* CurrentDevice = Devices;
        uint32_t    DeviceIndex = 0;
        bool        preferredDeviceRequested = ( g_Options.INTC_IGDEXT_DEVICE_INDEX_PREFERENCE > 0 ) ? true : false;
        int         preferredDeviceIndex = preferredDeviceRequested ? g_Options.INTC_IGDEXT_DEVICE_INDEX_PREFERENCE - 1 : 0;

        while( CurrentDevice )
        {

            // Check direct VendorID and DeviceID match
            if( (!preferredDeviceRequested && VendorID && DeviceID && Device_IsVendorAndDeviceIDMatch( CurrentDevice, VendorID, DeviceID ) ) ||
                ( preferredDeviceRequested && preferredDeviceIndex == DeviceIndex ) )
            {
                wcscpy_s( szPath, MAX_PATH, &CurrentDevice->driverPath[ 0 ] );

                size_t index = wcslen( szPath );

                // Add backslash if missing
                if( szPath[ index ] != '\\' )
                {
                    szPath[ index ] = '\\';
                    szPath[ index + 1 ] = 0;
                }

                wchar_t* pFileName = &szPath[ index + 1 ];      // Pointer to the library filename location
                size_t      szPathLength = wcslen( szPath );

                // Copy library filename
                memcpy_s( pFileName, MAX_PATH, D3D_EXT_DLL, ( szExtDllNameLength + 1 ) * sizeof( wchar_t ) );

                LogOut( LOG_DEBUG, "Loading Graphics Extensions library using: Device[%d%s] | VendorID=0x%04x DeviceID=0x%04x | Path: \"%S\"... ", DeviceIndex, preferredDeviceRequested ? "*" : "", CurrentDevice->VendorID, CurrentDevice->DeviceID, szPath );

                loadLibrary = true;
                break;
            }

            // Next node
            CurrentDevice = CurrentDevice->next;
            DeviceIndex++;
        }

        // We don't need more of these dependencies
        ClearDependencies();
    }

    // Default method of loading the DLL
    if( !loadLibrary && EnumProcessModules( hProc, hMods, sizeof( hMods ), &cbNeeded ) )
    {
        // Go through all the enumerated processes and find the driver module
        for( unsigned int i = 0; i < ( cbNeeded / sizeof( HMODULE ) ); i++ )
        {
            // Get the full path to the module
            if( GetModuleFileNameExW( hProc, hMods[ i ], szModFullPath, sizeof( szModFullPath ) / sizeof( wchar_t ) ) )
            {
                // Match enumerated Graphics Device Driver path with one of the module names enumerated from current process and
                // make sure it is located in DriverStore
                if( !Device_MatchDevicePath( Devices, szModFullPath ) )
                {
                    continue;
                }

                wcscpy_s( szPath, MAX_PATH, szModFullPath );

                // Build full path to the module
                wchar_t* pFileName = wcsrchr( szPath, '\\' );
                if( pFileName != nullptr )
                {
                    size_t  modNameLength = wcslen( pFileName );
                    size_t  szPathLength = wcslen( szPath );

                    if( modNameLength > 0 )
                    {
                        pFileName++;        // Skip slash '\'
                    }

                    if( szPathLength + 1 - modNameLength + szExtDllNameLength <= MAX_PATH )
                    {
                        memcpy_s( pFileName, MAX_PATH, D3D_EXT_DLL, ( szExtDllNameLength + 1 ) * sizeof( wchar_t ) );
                    }
                    else
                    {
                        // Something is wrong with the current process path, try using library name only
                        wcscpy_s( szPath, szExtDllNameLength, D3D_EXT_DLL );
                    }
                }
                else
                {
                    // Something is wrong with the current process path, try using library name only
                    wcscpy_s( szPath, szExtDllNameLength, D3D_EXT_DLL );
                }

                LogOut( LOG_DEBUG, "Loading Graphics Extensions library from the driver folder: \"%S\"... ", szPath );

                loadLibrary = true;

                break;
            }
        }
    }

    // Remove Graphics Devices list
    DestroyDevicesList( Devices );

    // Try to load the library
    if( loadLibrary )
    {
        hLibModule = LoadLibraryExW( szPath, NULL, 0 );
        if( hLibModule )
        {
            LogOut( LOG_INFO, "Graphics Extensions library loaded: \"%S\"!", szPath );

             return hLibModule;
        }
        
        LogOut( LOG_ERROR, "Cannot load Graphics Extensions library from: \"%S\"!", szPath );
        LogOutGetLastError();
    }
#endif

    return NULL;
}
