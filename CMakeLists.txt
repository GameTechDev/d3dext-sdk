# Copyright (C) 2025 Intel Corporation
# SPDX-License-Identifier: MIT
#
# Builds the Graphics Extensions static library (igdext64.lib / igdext32.lib) from source,
# as an alternative to linking the prebuilt library in sdk/lib.
#
# Point D3DEXT_SDK_SOURCE_DIR at a directory holding the SDK sources. See sdk/BUILDING.md
# for the required file list.
#
#   cmake -S . -B build -G "Visual Studio 17 2022" -A x64 ^
#         -DD3DEXT_SDK_SOURCE_DIR=<path-to-generated-sources>
#   cmake --build build --config Release

cmake_minimum_required(VERSION 3.20)

project(igdext-sdk LANGUAGES CXX)

if(NOT MSVC)
    message(FATAL_ERROR "The Graphics Extensions static library is a Windows/MSVC target.")
endif()

set(D3DEXT_SDK_SOURCE_DIR "" CACHE PATH
    "Directory containing the SDK sources (see sdk/BUILDING.md)")

# The loader sources live in sdk/src, so the build works out of a plain clone. The variable
# remains supported for building against a different snapshot of the sources.
if(NOT D3DEXT_SDK_SOURCE_DIR AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/sdk/src/igdext_api.cpp")
    set(D3DEXT_SDK_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sdk/src")
    message(STATUS "igdext: using the in-repository sources in sdk/src")
endif()

if(NOT D3DEXT_SDK_SOURCE_DIR)
    message(FATAL_ERROR
        "D3DEXT_SDK_SOURCE_DIR is not set and sdk/src is not present. See sdk/BUILDING.md.")
endif()

# igdext.h and igdext_tools.h are the public headers and are kept only in sdk/include, so
# that the copy applications compile against is the same one the library is built from.
set(D3DEXT_SDK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sdk/include" CACHE PATH
    "Directory containing the SDK public headers")

if("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "x64")
    set(ARCH "64")
elseif("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "Win32")
    set(ARCH "32")
else()
    message(FATAL_ERROR "Unsupported platform '${CMAKE_GENERATOR_PLATFORM}'; use -A x64 or -A Win32.")
endif()

# Fail during configure with a precise name rather than mid-compile on a missing include.
set(D3DEXT_REQUIRED_SOURCES
    stdafx.h
    stdafx.cpp
    igdext_helper.h
    igdext_api.h
    igdext_api.cpp
    igdext_api_dll.h
)

set(D3DEXT_SOURCES "")
set(D3DEXT_MISSING "")
foreach(f IN LISTS D3DEXT_REQUIRED_SOURCES)
    if(EXISTS "${D3DEXT_SDK_SOURCE_DIR}/${f}")
        list(APPEND D3DEXT_SOURCES "${D3DEXT_SDK_SOURCE_DIR}/${f}")
    else()
        list(APPEND D3DEXT_MISSING "${f}")
    endif()
endforeach()

if(D3DEXT_MISSING)
    string(REPLACE ";" "\n  " D3DEXT_MISSING_TEXT "${D3DEXT_MISSING}")
    message(FATAL_ERROR
        "Missing from D3DEXT_SDK_SOURCE_DIR (${D3DEXT_SDK_SOURCE_DIR}):\n  ${D3DEXT_MISSING_TEXT}\n"
        "See sdk/BUILDING.md.")
endif()

foreach(f IN ITEMS igdext.h igdext_tools.h)
    if(NOT EXISTS "${D3DEXT_SDK_INCLUDE_DIR}/${f}")
        message(FATAL_ERROR "Missing from D3DEXT_SDK_INCLUDE_DIR (${D3DEXT_SDK_INCLUDE_DIR}): ${f}")
    endif()
endforeach()

add_library(igdext STATIC ${D3DEXT_SOURCES})

target_include_directories(igdext PUBLIC
    "${D3DEXT_SDK_SOURCE_DIR}"
    "${D3DEXT_SDK_INCLUDE_DIR}")

# Precompiled header, matching how the sources are written: every translation unit
# includes stdafx.h first.
target_precompile_headers(igdext PRIVATE "${D3DEXT_SDK_SOURCE_DIR}/stdafx.h")

target_compile_definitions(igdext PRIVATE
    D3DEXT_PUBLIC_ONLY
    EXPORT_INTC_EXT_API
    _USRDLL
    IGFX_D3D12_MONZA_EXT_EXPORTS
    USERMODE_DRIVER
    D3D12_UMD
    D3D12_GMM
    REGISTRY_ENABLE
    $<$<CONFIG:Release>:_RELEASE>
    $<$<CONFIG:Debug>:_DEBUG>
)

target_compile_options(igdext PRIVATE
    /W3
    /EHsc
    /Zm400
    /MP
    /sdl
    /GS
    /Gy
    /guard:cf
    /Zi
    # /Zl - omit the default library name, so the consuming application chooses its own
    # CRT. The shipped library is built this way.
    $<$<CONFIG:Release>:/Ox /Ob2 /Oi /Ot /Oy- /GF /Zl /MT>
    $<$<CONFIG:Debug>:/Od /MTd>
)

# Propagated to consumers of the target. The library is built /Zl, so it embeds no
# default library directives and the linker resolves these through the interface.
# ole32 provides StringFromGUID2; dxgi matches how the shipped library is built.
target_link_libraries(igdext PUBLIC dxgi.lib ole32.lib)

set_target_properties(igdext PROPERTIES
    OUTPUT_NAME "igdext${ARCH}"
    COMPILE_PDB_NAME "igdext${ARCH}"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

message(STATUS "igdext: building igdext${ARCH}.lib from ${D3DEXT_SDK_SOURCE_DIR}")
