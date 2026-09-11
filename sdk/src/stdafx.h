/*
 *
 * Copyright (C) 2016-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 *
 * File Name:  stdafx.h
 *
 * Abstract:   Precompiled header
 *
 * Notes:
 */
#pragma once

#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <stdint.h>
#include <stdio.h>
#include <io.h>

// Include both parts of the common D3D11/D3D12 header file
#define INTC_IGDEXT_D3D11
#define INTC_IGDEXT_D3D12

// Graphics Extensions API header files
#include "igdext.h"

#include "igdext_api_dll.h"
#include "igdext_tools.h"

// Graphics Extensions Internal API header files. Not generated in a public-only build.
#ifndef D3DEXT_PUBLIC_ONLY
#include "igdext_int.h"
#include "igdext_api_dll_int.h"
#endif

// Graphics Extensions Helpers
#include "igdext_helper.h"

// Graphics Extensions Infrastructure header files
#include "igdext_api.h"


