//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#include "stdafx.h"
#include "D3D12HelloWindow.h"

INTC_D3D12_API_CALLBACKS1 d3d12_api_callbacks = { 0 };

HRESULT INTC_D3D12_CreateDeviceExtensionContext1(
    PFNINTCDX12EXT_CREATEDEVICEEXTENSIONCONTEXT1 pfnCreateDeviceExtensionContext1,
    const ID3D12Device* pDevice,
    INTCExtensionContext** ppExtensionContext,
    INTCExtensionInfo* pExtensionInfo,
    INTCExtensionAppInfo1* pExtensionAppInfo )
{
    if( pfnCreateDeviceExtensionContext1 == nullptr )
    {
        return E_INVALIDARG;
    }

    return pfnCreateDeviceExtensionContext1( pDevice, ppExtensionContext, pExtensionInfo, pExtensionAppInfo );
}

HRESULT INTC_D3D12_SetApplicationInfo(
    PFNINTCDX12EXT_SETAPPLICATIONINFO pfnSetApplicationInfo,
    INTCExtensionAppInfo1* pExtensionAppInfo )
{
    if( pfnSetApplicationInfo == nullptr )
    {
        return E_INVALIDARG;
    }
    return pfnSetApplicationInfo( pExtensionAppInfo );
}

HRESULT INTC_D3D12_SetDeviceParams(
    PFNINTCDX12EXT_SETDEVICEPARAMS pfnSetDeviceParams,
    INTCDeviceParams* pDeviceParams )
{
    if( pfnSetDeviceParams == nullptr )
    {
        return E_INVALIDARG;
    }
    return pfnSetDeviceParams( pDeviceParams );
}

HRESULT INTC_D3D12_CreateDeviceExtensionContext2(
    PFNINTCDX12EXT_CREATEDEVICEEXTENSIONCONTEXT2 pfnCreateDeviceExtensionContext2,
    const ID3D12Device* pDevice,
    INTCExtensionContext** ppExtensionContext,
    INTCExtensionInfo1* pExtensionInfo,
    INTCExtensionAppInfo1* pExtensionAppInfo )
{
    if( pfnCreateDeviceExtensionContext2 == nullptr )
    {
        return E_INVALIDARG;
    }
    return pfnCreateDeviceExtensionContext2( pDevice, ppExtensionContext, pExtensionInfo, pExtensionAppInfo );
}


D3D12HelloWindow::D3D12HelloWindow( UINT width, UINT height, std::wstring name ) :
    DXSample( width, height, name ),
    m_frameIndex( 0 ),
    m_rtvDescriptorSize( 0 )
{
}

void D3D12HelloWindow::OnInit()
{
    // Prepare to load assets and create the rendering pipeline.
    LoadPipeline();
    LoadAssets();

}

// Load the rendering pipeline dependencies.
void D3D12HelloWindow::LoadPipeline()
{
    UINT dxgiFactoryFlags = 0;

#if defined(_DEBUG)
    // Enable the debug layer (requires the Graphics Tools "optional feature").
    // NOTE: Enabling the debug layer after device creation will invalidate the active device.
    {
        ComPtr<ID3D12Debug> debugController;
        if( SUCCEEDED( D3D12GetDebugInterface( IID_PPV_ARGS( &debugController ) ) ) )
        {
            debugController->EnableDebugLayer();

            // Enable additional debug layers.
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }
#endif

    ComPtr<IDXGIFactory4> factory;
    ThrowIfFailed( CreateDXGIFactory2( dxgiFactoryFlags, IID_PPV_ARGS( &factory ) ) );

    if( m_useWarpDevice )
    {
        ComPtr<IDXGIAdapter> warpAdapter;
        ThrowIfFailed( factory->EnumWarpAdapter( IID_PPV_ARGS( &warpAdapter ) ) );

        ThrowIfFailed( D3D12CreateDevice(
            warpAdapter.Get(),
            D3D_FEATURE_LEVEL_11_0,
            IID_PPV_ARGS( &m_device )
        ) );
    }
    else
    {
        ComPtr<IDXGIAdapter1> hardwareAdapter;
        GetHardwareAdapter( factory.Get(), &hardwareAdapter );

#if defined(INTEL_GRAPHICS_EXTENSIONS)
        // INTEL_GRAPHICS_EXTENSIONS
        // Initialize Graphics Extensions for D3D12

        DXGI_ADAPTER_DESC1 desc;
        hardwareAdapter->GetDesc1( &desc );

        intel_extensions.init(
            // Application Info
            *intel_extensions.make_extension_app_info( 
                L"Sample App", intel_extensions.make_appinfo_version( 0, 0 ), 
                L"Unreal Engine", intel_extensions.make_appinfo_version( 5, 5, 0 )).get(),

            // Requested Graphics Extensions Version
            intel_extensions.make_extension_version( 5, 20 ),

            // Vendor and Device ID - needed if initializing Graphics Extensions before creating D3D12 Device
            desc.VendorId, desc.DeviceId
        );

        // Enable Tools Support

        // Initialize callbacks
        INTC_D3D12_API_CALLBACKS_INIT( d3d12_api_callbacks );

        // Set version 1 function pointers
        d3d12_api_callbacks.INTC_D3D12_SetApplicationInfo = INTC_D3D12_SetApplicationInfo;
        d3d12_api_callbacks.INTC_D3D12_CreateDeviceExtensionContext1 = INTC_D3D12_CreateDeviceExtensionContext1;

        // Set version 2 function pointers if available
        if( INTC_D3D12_API_CALLBACKS_CHECK_VERSION( d3d12_api_callbacks, 2 ) )
        {
            d3d12_api_callbacks.INTC_D3D12_SetDeviceParams = INTC_D3D12_SetDeviceParams;
            d3d12_api_callbacks.INTC_D3D12_CreateDeviceExtensionContext2 = INTC_D3D12_CreateDeviceExtensionContext2;
        }

        intel_extensions.register_api_callbacks( &d3d12_api_callbacks );

        // Enable Intel App Detection Extension - before creating D3D12 Device
        intel_extensions.enable_app_detection();

        // Enable Capture Mode
        intel_extensions.enable_capture_mode();
#endif

        ThrowIfFailed( D3D12CreateDevice(
            hardwareAdapter.Get(),
            D3D_FEATURE_LEVEL_11_0,
            IID_PPV_ARGS( &m_device )
        ) );

#if defined(INTEL_GRAPHICS_EXTENSIONS)
        // INTEL_GRAPHICS_EXTENSIONS

        // Create Device Extension Context for Graphics Extensionss
        intel_extensions.set_device( m_device.Get() );

        // Print Graphics Extensionss status
        intel_extensions.print_status();

        // Check if at least Xe Architecture device
        if( intel_extensions.device_architecture( INTC_GMD_ARCH_12 ) )
        {
            // Platform does not meet minimum feature criteria
        }
        
        // Check if at least Xe2 HPG X2 Architecture device (BMG-B580)
        if( intel_extensions.device_architecture( INTC_GMD_ID( INTC_GMD_ARCH_20, INTC_GMD_ARCH_20_RELEASE_XE2_HPG_X2 ) ) )
        {
            OutputDebugStringA( "Intel Graphics Extensions for D3D12: Platform is supported.\n" );

            if( intel_extensions.get_performance_estimate() >= igdext_impl::INTC_PERFORMANCE_MEDIUM )
            {
                OutputDebugStringA( "Intel Graphics Extensions for D3D12: Device Performance is balanced or higher.\n" );
            }
            else
            {
                OutputDebugStringA( "Intel Graphics Extensions for D3D12: Device Performance is estimated as low.\n" );
            }
        }
        else
        {
            OutputDebugStringA( "Intel Graphics Extensions for D3D12: Platform is NOT supported.\n" );
        }

        UINT64 shaderHeapUsage = 0;
        intel_extensions.get_current_shader_heap_usage( &shaderHeapUsage );

        char buf[ 256 ];
        sprintf_s( buf, sizeof( buf ), "Current Shader Heap Usage: %llu bytes\n", shaderHeapUsage );
        OutputDebugStringA( buf );
#endif
    }
    
    // Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    ThrowIfFailed(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue)));

    // Describe and create the swap chain.
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = FrameCount;
    swapChainDesc.Width = m_width;
    swapChainDesc.Height = m_height;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    ComPtr<IDXGISwapChain1> swapChain;
    ThrowIfFailed(factory->CreateSwapChainForHwnd(
        m_commandQueue.Get(),        // Swap chain needs the queue so that it can force a flush on it.
        Win32Application::GetHwnd(),
        &swapChainDesc,
        nullptr,
        nullptr,
        &swapChain
        ));

    // This sample does not support fullscreen transitions.
    ThrowIfFailed(factory->MakeWindowAssociation(Win32Application::GetHwnd(), DXGI_MWA_NO_ALT_ENTER));

    ThrowIfFailed(swapChain.As(&m_swapChain));
    m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

    // Create descriptor heaps.
    {
        // Describe and create a render target view (RTV) descriptor heap.
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
        rtvHeapDesc.NumDescriptors = FrameCount;
        rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        ThrowIfFailed(m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap)));

        m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }

    // Create frame resources.
    {
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());

        // Create a RTV for each frame.
        for (UINT n = 0; n < FrameCount; n++)
        {
            ThrowIfFailed(m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n])));
            m_device->CreateRenderTargetView(m_renderTargets[n].Get(), nullptr, rtvHandle);
            rtvHandle.Offset(1, m_rtvDescriptorSize);
        }
    }

    ThrowIfFailed(m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator)));
}

// Load the sample assets.
void D3D12HelloWindow::LoadAssets()
{
    // Create the command list.
    ThrowIfFailed( m_device->CreateCommandList( 0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), nullptr, IID_PPV_ARGS( &m_commandList ) ) );


    // Command lists are created in the recording state, but there is nothing
    // to record yet. The main loop expects it to be closed, so close it now.
    ThrowIfFailed( m_commandList->Close() );

    // Create synchronization objects.
    {
        ThrowIfFailed( m_device->CreateFence( 0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS( &m_fence ) ) );
        m_fenceValue = 1;

        // Create an event handle to use for frame synchronization.
        m_fenceEvent = CreateEvent( nullptr, FALSE, FALSE, nullptr );
        if( m_fenceEvent == nullptr )
        {
            ThrowIfFailed( HRESULT_FROM_WIN32( GetLastError() ) );
        }
    }

#if defined(INTEL_GRAPHICS_EXTENSIONS)

    for( int i = 0; i < 1; ++i )
    {
        // Make each shader unique by injecting a macro with the loop index
        std::ostringstream oss;
        oss << "#define UNIQUE_ID " << i << "\n";
        std::string shaderPrefix = oss.str();

        // Vertex shader with unique macro
        std::string vsCode = shaderPrefix +
            "struct VSOut { float4 pos : SV_POSITION; };"
            "VSOut main(float4 pos : POSITION) { VSOut o; o.pos = pos + float4(UNIQUE_ID * 0.00001f, 0, 0, 0); return o; }";

        // Pixel shader with unique macro
        std::string psCode = shaderPrefix +
            "float4 main() : SV_TARGET { return float4(UNIQUE_ID * 0.00001f, 0, 0, 1); }";

        // Compile vertex shader
        ComPtr<ID3DBlob> vsBlob;
        ComPtr<ID3DBlob> errorBlob;
        HRESULT hr = D3DCompile( vsCode.c_str(), vsCode.size(), nullptr, nullptr, nullptr, "main", "vs_5_0", 0, 0, &vsBlob, &errorBlob );
        if( FAILED( hr ) )
        {
            OutputDebugStringA( "Failed to compile vertex shader\n" );
            continue;
        }

        // Compile pixel shader
        ComPtr<ID3DBlob> psBlob;
        hr = D3DCompile( psCode.c_str(), psCode.size(), nullptr, nullptr, nullptr, "main", "ps_5_0", 0, 0, &psBlob, &errorBlob );
        if( FAILED( hr ) )
        {
            OutputDebugStringA( "Failed to compile pixel shader\n" );
            continue;
        }

        // Minimal root signature (empty)
        D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
        rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

        ComPtr<ID3DBlob> signature;
        hr = D3D12SerializeRootSignature( &rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &errorBlob );
        if( FAILED( hr ) )
        {
            OutputDebugStringA( "Failed to serialize root signature\n" );
            continue;
        }

        ComPtr<ID3D12RootSignature> rootSignature;
        hr = m_device->CreateRootSignature( 0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS( &rootSignature ) );
        if( FAILED( hr ) )
        {
            OutputDebugStringA( "Failed to create root signature\n" );
            continue;
        }

        // Input layout (single float4 POSITION)
        D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
        };

        // PSO description
        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.pRootSignature = rootSignature.Get();
        psoDesc.VS = { vsBlob->GetBufferPointer(), vsBlob->GetBufferSize() };
        psoDesc.PS = { psBlob->GetBufferPointer(), psBlob->GetBufferSize() };
        psoDesc.InputLayout = { inputElementDescs, _countof( inputElementDescs ) };
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC( D3D12_DEFAULT );
        psoDesc.BlendState = CD3DX12_BLEND_DESC( D3D12_DEFAULT );
        psoDesc.DepthStencilState.DepthEnable = FALSE;
        psoDesc.DepthStencilState.StencilEnable = FALSE;
        psoDesc.SampleDesc.Count = 1;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[ 0 ] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

        hr = m_device->CreateGraphicsPipelineState( &psoDesc, IID_PPV_ARGS( &pipelineState ) );
        if( FAILED( hr ) )
        {
            OutputDebugStringA( "Failed to create PSO\n" );
            continue;
        }

        UINT64 shaderHeapUsage = 0;
        intel_extensions.get_current_shader_heap_usage( &shaderHeapUsage );

        char buf[ 256 ];
        sprintf_s( buf, sizeof( buf ), "[%d] Current Shader Heap Usage: %llu bytes\n", i, shaderHeapUsage );
        OutputDebugStringA( buf );
    }
#endif
}

// Update frame-based values.
void D3D12HelloWindow::OnUpdate()
{
}

// Render the scene.
void D3D12HelloWindow::OnRender()
{
    // Record all the commands we need to render the scene into the command list.
    PopulateCommandList();

    // Execute the command list.
    ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
    m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    // Present the frame.
    ThrowIfFailed(m_swapChain->Present(1, 0));

    WaitForPreviousFrame();
}

void D3D12HelloWindow::OnDestroy()
{
    // Ensure that the GPU is no longer referencing resources that are about to be
    // cleaned up by the destructor.
    WaitForPreviousFrame();

    CloseHandle(m_fenceEvent);

#if defined(INTEL_GRAPHICS_EXTENSIONS)
    // INTEL_GRAPHICS_EXTENSIONS
    // Shutdown Graphics Extensions for D3D12
    intel_extensions.shutdown();
#endif
}

void D3D12HelloWindow::PopulateCommandList()
{
    // Command list allocators can only be reset when the associated 
    // command lists have finished execution on the GPU; apps should use 
    // fences to determine GPU execution progress.
    ThrowIfFailed( m_commandAllocator->Reset() );

    // However, when ExecuteCommandList() is called on a particular command 
    // list, that command list can then be reset at any time and must be before 
    // re-recording.
    ThrowIfFailed( m_commandList->Reset( m_commandAllocator.Get(), m_pipelineState.Get() ) );

    m_commandList->SetPipelineState( pipelineState.Get() );

    // Retrieve (stage-2 - optimized) cached blob for the pipeline state object
    {
        ComPtr<ID3DBlob> cachedBlob = nullptr;
        if( intel_extensions.get_cached_blob( pipelineState.Get(), &cachedBlob, static_cast<INTC_D3D12_CACHED_BLOB_FLAGS>( INTC_D3D12_CACHED_BLOB_FLAG_STAGE_2 | INTC_D3D12_CACHED_BLOB_FLAG_WAIT_FOR_READY ) ) )
        {
            // Use cachedBlob as needed
            void* pData = cachedBlob->GetBufferPointer();
            size_t dataLength = cachedBlob->GetBufferSize();

            // For demonstration, we just output the size
            char buf[ 256 ];
            sprintf_s( buf, sizeof( buf ), "Retrieved cached blob of size: %zu bytes\n", dataLength );
            OutputDebugStringA( buf );
        }
        else
        {
            OutputDebugStringA( "Failed to retrieve cached blob for PSO\n" );
        }
    }

    // Set driver event metadata for this command list
    {
        INTC_D3D12_SetDriverEventMetadata(
            intel_extensions.get_device_extension_context(),
            m_commandList.Get(),
            0x80085 );
    }

    // Indicate that the back buffer will be used as a render target.
    CD3DX12_RESOURCE_BARRIER barrier;
    
    barrier = CD3DX12_RESOURCE_BARRIER::Transition( m_renderTargets[ m_frameIndex ].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET );
    m_commandList->ResourceBarrier(1, &barrier);

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_frameIndex, m_rtvDescriptorSize);

    // Record commands.
    const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
    m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

    // Indicate that the back buffer will now be used to present.
    barrier = CD3DX12_RESOURCE_BARRIER::Transition( m_renderTargets[ m_frameIndex ].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET );
    m_commandList->ResourceBarrier(1, &barrier);

    ThrowIfFailed(m_commandList->Close());
}

void D3D12HelloWindow::WaitForPreviousFrame()
{
    // WAITING FOR THE FRAME TO COMPLETE BEFORE CONTINUING IS NOT BEST PRACTICE.
    // This is code implemented as such for simplicity. The D3D12HelloFrameBuffering
    // sample illustrates how to use fences for efficient resource usage and to
    // maximize GPU utilization.

    // Signal and increment the fence value.
    const UINT64 fence = m_fenceValue;
    ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), fence));
    m_fenceValue++;

    // Wait until the previous frame is finished.
    if (m_fence->GetCompletedValue() < fence)
    {
        ThrowIfFailed(m_fence->SetEventOnCompletion(fence, m_fenceEvent));
        WaitForSingleObject(m_fenceEvent, INFINITE);
    }

    m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}
