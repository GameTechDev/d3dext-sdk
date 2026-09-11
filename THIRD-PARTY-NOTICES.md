# Third-party notices

This repository is licensed under the MIT License (see LICENSE), covering its contents
including the headers, the loader sources under `sdk/src/`, the prebuilt static libraries
under `sdk/lib/`, the documentation and the samples. The components below are the
copyright of other authors and are provided under their own terms.

## Microsoft DirectX-Graphics-Samples

The sample sources listed below are derived from Microsoft's
DirectX-Graphics-Samples and retain Microsoft's copyright notice in their file
headers. Some have been modified by Intel to demonstrate the Graphics Extensions
API; both the original and the modifications are MIT-licensed.

    samples/igdext_dx12_helloworld/D3D12HelloWindow.cpp
    samples/igdext_dx12_helloworld/D3D12HelloWindow.h
    samples/igdext_dx12_helloworld/DXSample.cpp
    samples/igdext_dx12_helloworld/DXSample.h
    samples/igdext_dx12_helloworld/DXSampleHelper.h
    samples/igdext_dx12_helloworld/Main.cpp
    samples/igdext_dx12_helloworld/Win32Application.cpp
    samples/igdext_dx12_helloworld/Win32Application.h
    samples/igdext_dx12_helloworld/stdafx.cpp
    samples/igdext_dx12_helloworld/stdafx.h

    Copyright (c) Microsoft. All rights reserved.
    Licensed under the MIT License (MIT).

Source: https://github.com/microsoft/DirectX-Graphics-Samples

## Microsoft DirectX 12 Agility SDK

`samples/igdext_dx12_helloworld` references the `Microsoft.Direct3D.D3D12`
NuGet package (see `packages.config`). The package is restored at build time and
is **not** redistributed in this repository. It is governed by the Microsoft
Software License Terms delivered with the package, which are not MIT.

Source: https://www.nuget.org/packages/Microsoft.Direct3D.D3D12
