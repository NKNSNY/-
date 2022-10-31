#include "System_DX3D12.h"

using namespace DirectX;


UINT64 DX3D12::m_frame;
UINT DX3D12::m_rtv_index;

IDXGIFactory4 * DX3D12::ps_m_factory;
IDXGIAdapter3 * DX3D12::ps_m_adapter;
ID3D12Device * DX3D12::ps_m_device;
ID3D12CommandQueue * DX3D12::ps_m_commandqueue;
HANDLE DX3D12::m_fence_event;
ID3D12Fence * DX3D12::ps_m_fence;
IDXGISwapChain3 * DX3D12::ps_m_swapchain;
ID3D12GraphicsCommandList * DX3D12::ps_m_commandlist;
ID3D12CommandAllocator * DX3D12::ps_m_commandallocator;
ID3D12Resource * DX3D12::ps_m_rendertarget [2];
ID3D12DescriptorHeap * DX3D12::ps_m_descriptorheap_rtv;
D3D12_CPU_DESCRIPTOR_HANDLE DX3D12::m_rtvhandle [2];
ID3D12Resource * DX3D12::ps_m_depthbuffer;
ID3D12DescriptorHeap * DX3D12::ps_m_descripterheap_dsv;
D3D12_CPU_DESCRIPTOR_HANDLE DX3D12::m_dsvhandle;
ID3D12PipelineState * DX3D12::ps_m_piplinestate;
ID3D12RootSignature * DX3D12::ps_m_rootsignature;

D3D12_RECT DX3D12::m_scissorrect;
D3D12_VIEWPORT DX3D12::m_viewport;

XMFLOAT3 DX3D12::sm_eyepos;
XMFLOAT3 DX3D12::sm_focuspos;

DX3D12GameObject g_gameobject [1000];

int g_d3d12_qube_num;

ID3D12Device * DX3D12::GetDX3D12Device()
{
    return ps_m_device;
}

ID3D12GraphicsCommandList * DX3D12::GetDX3D12CommandList()
{
    return ps_m_commandlist;
}

bool DX3D12::SetCamera(DirectX::XMFLOAT3 eye , DirectX::XMFLOAT3 focus)
{
    sm_eyepos = eye;
    sm_focuspos = focus;

    return true;
}

/**--------------------------------------------
/// \description ダイレクトX12の初期化
///
/// \param[in] hwnd
/// \param[in] screen_width
/// \param[in] screen_height
///
///  \return true or false
//--------------------------------------------*/
bool DX3D12::Initialize(HWND hwnd , int screen_width , int screen_height , int qube_num , QubeStatus qube [])
{
    // ビューポート
    m_viewport.TopLeftX = 0.0f;
    m_viewport.TopLeftY = 0.0f;
    m_viewport.Height = screen_height;
    m_viewport.Width = screen_width;
    m_viewport.MaxDepth = 1.0f;
    m_viewport.MinDepth = 0.0f;

    // シザー矩形
    m_scissorrect.top = 0.0f;
    m_scissorrect.bottom = screen_height;
    m_scissorrect.left = 0.0f;
    m_scissorrect.right = screen_width;


    // ファクトリの作成
    if (FAILED(CreateDXGIFactory2(0 , IID_PPV_ARGS(&ps_m_factory))))
    {
        return false;
    }

    // アダプターの使用
    if (FAILED(ps_m_factory->EnumAdapters(0 , (IDXGIAdapter **) &ps_m_adapter)))
    {
        return false;
    }

    // 見つかったアダプターからデバイスの作成
    if (FAILED(D3D12CreateDevice(ps_m_adapter , D3D_FEATURE_LEVEL_11_1 , IID_PPV_ARGS(&ps_m_device))))
    {
        return false;
    }

    // コマンドキューの設定
    D3D12_COMMAND_QUEUE_DESC command_queue_desc {};
    command_queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    command_queue_desc.Priority = 0;
    command_queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    command_queue_desc.NodeMask = 0;

    //コマンドキューの作成
    if (FAILED(ps_m_device->CreateCommandQueue(&command_queue_desc ,
        IID_PPV_ARGS(&ps_m_commandqueue))))
    {
        return false;
    }

    // コマンドキュー用のフェンス設定、作成
    m_fence_event = CreateEventEx(nullptr , FALSE , FALSE , EVENT_ALL_ACCESS);
    if (FAILED(ps_m_device->CreateFence(0 , D3D12_FENCE_FLAG_NONE , IID_PPV_ARGS(&ps_m_fence))))
    {
        return false;
    }

    // スワップチェインの設定
    DXGI_SWAP_CHAIN_DESC swap_chain_desc {};
    swap_chain_desc.OutputWindow = hwnd;
    swap_chain_desc.Windowed = TRUE;
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.BufferCount = 2;
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swap_chain_desc.BufferDesc.Height = screen_height;
    swap_chain_desc.BufferDesc.Width = screen_width;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.SampleDesc.Quality = 0;

    // スワップチェインの作成
    IDXGISwapChain * swap_chain {};
    if (FAILED(ps_m_factory->CreateSwapChain(ps_m_commandqueue , &swap_chain_desc , &swap_chain)))
    {
        return false;
    }

    if (FAILED(swap_chain->QueryInterface(&ps_m_swapchain)))
    {
        return false;
    }

    // カレントのバックバッファのインデックスを取得
    m_rtv_index = ps_m_swapchain->GetCurrentBackBufferIndex();

    // レンダーターゲットビュー(RTV)のデスクリプタヒープの設定
    D3D12_DESCRIPTOR_HEAP_DESC heap_desc {};
    heap_desc.NumDescriptors = 2;
    heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    heap_desc.NodeMask = 0;

    // RTVのデスクリプタヒープの作成
    if (FAILED(ps_m_device->CreateDescriptorHeap(&heap_desc , IID_PPV_ARGS(&ps_m_descriptorheap_rtv))))
    {
        return false;
    }

    // RTVの作成
    UINT size = ps_m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    for (int i = 0; i < 2; i++)
    {
        // スワップチェインからバッファを受け取る
        if (FAILED(ps_m_swapchain->GetBuffer(i , IID_PPV_ARGS(&ps_m_rendertarget [i]))))
        {
            return false;
        }

        // RTVをヒープデスクリプタに登録
        m_rtvhandle [i] = ps_m_descriptorheap_rtv->GetCPUDescriptorHandleForHeapStart();
        m_rtvhandle [i].ptr += size * i;
        ps_m_device->CreateRenderTargetView(ps_m_rendertarget [i] , nullptr , m_rtvhandle [i]);

    }

    // 深度バッファ(DSV)のデスクリプタヒープの設定
    D3D12_DESCRIPTOR_HEAP_DESC descriptor_heap_desc {};
    descriptor_heap_desc.NumDescriptors = 1;
    descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    descriptor_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    descriptor_heap_desc.NodeMask = 0;

    // DSVのデスクリプタヒープの作成
    if (FAILED(ps_m_device->CreateDescriptorHeap(&descriptor_heap_desc ,
        IID_PPV_ARGS(&ps_m_descripterheap_dsv))))
    {
        return false;
    }

    // 深度バッファの設定
    D3D12_HEAP_PROPERTIES heap_properties {};
    heap_properties.Type = D3D12_HEAP_TYPE_DEFAULT;
    heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heap_properties.CreationNodeMask = 0;
    heap_properties.VisibleNodeMask = 0;

    D3D12_RESOURCE_DESC resource_desc {};
    resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    resource_desc.Height = screen_height;
    resource_desc.Width = screen_width;
    resource_desc.DepthOrArraySize = 1;
    resource_desc.MipLevels = 0;
    resource_desc.Format = DXGI_FORMAT_R32_TYPELESS;
    resource_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    resource_desc.SampleDesc.Count = 1;
    resource_desc.SampleDesc.Quality = 0;
    resource_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

    D3D12_CLEAR_VALUE clear_value {};
    clear_value.Format = DXGI_FORMAT_D32_FLOAT;
    clear_value.DepthStencil.Depth = 1.0f;
    clear_value.DepthStencil.Stencil = 0;

    // 深度バッファの作成
    if (FAILED(ps_m_device->CreateCommittedResource(&heap_properties , D3D12_HEAP_FLAG_NONE ,
        &resource_desc , D3D12_RESOURCE_STATE_DEPTH_WRITE ,
        &clear_value , IID_PPV_ARGS(&ps_m_depthbuffer))))
    {
        return false;
    }

    // 深度バッファビューの設定
    D3D12_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc {};
    depth_stencil_view_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    depth_stencil_view_desc.Format = DXGI_FORMAT_D32_FLOAT;
    depth_stencil_view_desc.Texture2D.MipSlice = 0;
    depth_stencil_view_desc.Flags = D3D12_DSV_FLAG_NONE;

    m_dsvhandle = ps_m_descripterheap_dsv->GetCPUDescriptorHandleForHeapStart();

    // 深度バッファビューの作成
    ps_m_device->CreateDepthStencilView(ps_m_depthbuffer , &depth_stencil_view_desc , m_dsvhandle);

    // コマンドアロケータの作成
    if (FAILED(ps_m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT ,
        IID_PPV_ARGS(&ps_m_commandallocator))))
    {
        return false;
    }

    // コマンドリストの作成
    if (FAILED(ps_m_device->CreateCommandList(0 , D3D12_COMMAND_LIST_TYPE_DIRECT ,
        ps_m_commandallocator , nullptr , IID_PPV_ARGS(&ps_m_commandlist))))
    {
        return false;
    }

    // ルートシグネチャの設定
    D3D12_ROOT_PARAMETER root_parameter [1] {};
    root_parameter [0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
    root_parameter [0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
    root_parameter [0].Descriptor.RegisterSpace = 0;
    root_parameter [0].Descriptor.ShaderRegister = 0;

    D3D12_ROOT_SIGNATURE_DESC root_signature_desc {};
    root_signature_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    root_signature_desc.NumParameters = ARRAYSIZE(root_parameter);
    root_signature_desc.pParameters = root_parameter;
    root_signature_desc.NumStaticSamplers = 0;
    root_signature_desc.pStaticSamplers = nullptr;

    ID3DBlob * blob {};
    if (FAILED(D3D12SerializeRootSignature(&root_signature_desc , D3D_ROOT_SIGNATURE_VERSION_1 , &blob , nullptr)))
    {
        return false;
    }

    // ルートシグネチャの作成
    if (FAILED(ps_m_device->CreateRootSignature(0 , blob->GetBufferPointer() ,
        blob->GetBufferSize() , IID_PPV_ARGS(&ps_m_rootsignature))))
    {
        return false;
    }

    // シェーダーコンパイル
    ID3DBlob * vertex_shader {};
    ID3DBlob * pixel_shader {};

    if (FAILED(D3DCompileFromFile(L"シェーダー/P_V_Shader.hlsl" , nullptr , nullptr ,
        "VSmain" , "vs_5_0" , 0 , 0 , &vertex_shader , nullptr)))
    {
        return false;
    }

    if (FAILED(D3DCompileFromFile(L"シェーダー/P_V_Shader.hlsl" , nullptr , nullptr ,
        "PSmain" , "ps_5_0" , 0 , 0 , &pixel_shader , nullptr)))
    {
        return false;
    }

    // 頂点レイアウト
    D3D12_INPUT_ELEMENT_DESC input_element_desc [] =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
        {"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
        {"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,24,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
    };

    // パイプラインステートの設定
    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipline_state_desc {};
    // シェーダーの設定
    pipline_state_desc.VS.BytecodeLength = vertex_shader->GetBufferSize();
    pipline_state_desc.VS.pShaderBytecode = vertex_shader->GetBufferPointer();
    pipline_state_desc.PS.BytecodeLength = pixel_shader->GetBufferSize();
    pipline_state_desc.PS.pShaderBytecode = pixel_shader->GetBufferPointer();
    // インプットレイアウトの設定
    pipline_state_desc.InputLayout.NumElements = ARRAYSIZE(input_element_desc);
    pipline_state_desc.InputLayout.pInputElementDescs = input_element_desc;
    // サンプル系の設定
    pipline_state_desc.SampleDesc.Count = 1;
    pipline_state_desc.SampleDesc.Quality = 0;
    pipline_state_desc.SampleMask = UINT_MAX;
    // レンダーターゲットの設定
    pipline_state_desc.NumRenderTargets = 1;
    pipline_state_desc.RTVFormats [0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    // 三角形に設定
    pipline_state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    // ルートシグネチャ
    pipline_state_desc.pRootSignature = ps_m_rootsignature;
    // ラスタライザステートの設定
    pipline_state_desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    pipline_state_desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    pipline_state_desc.RasterizerState.FrontCounterClockwise = FALSE;
    pipline_state_desc.RasterizerState.DepthBias = 0;
    pipline_state_desc.RasterizerState.DepthBiasClamp = 0;
    pipline_state_desc.RasterizerState.SlopeScaledDepthBias = 0;
    pipline_state_desc.RasterizerState.DepthClipEnable = TRUE;
    pipline_state_desc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
    pipline_state_desc.RasterizerState.AntialiasedLineEnable = FALSE;
    pipline_state_desc.RasterizerState.MultisampleEnable = FALSE;
    // ブレンドステートの設定
    for (int i = 0; i < ARRAYSIZE(pipline_state_desc.BlendState.RenderTarget); ++i)
    {
        pipline_state_desc.BlendState.RenderTarget [i].BlendEnable = FALSE;
        pipline_state_desc.BlendState.RenderTarget [i].SrcBlend = D3D12_BLEND_ONE;
        pipline_state_desc.BlendState.RenderTarget [i].DestBlend = D3D12_BLEND_ZERO;
        pipline_state_desc.BlendState.RenderTarget [i].BlendOp = D3D12_BLEND_OP_ADD;
        pipline_state_desc.BlendState.RenderTarget [i].SrcBlend = D3D12_BLEND_ONE;
        pipline_state_desc.BlendState.RenderTarget [i].DestBlendAlpha = D3D12_BLEND_ZERO;
        pipline_state_desc.BlendState.RenderTarget [i].BlendOpAlpha = D3D12_BLEND_OP_ADD;
        pipline_state_desc.BlendState.RenderTarget [i].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
        pipline_state_desc.BlendState.RenderTarget [i].LogicOpEnable = FALSE;
        pipline_state_desc.BlendState.RenderTarget [i].LogicOp = D3D12_LOGIC_OP_CLEAR;
    }
    pipline_state_desc.BlendState.AlphaToCoverageEnable = FALSE;
    pipline_state_desc.BlendState.IndependentBlendEnable = FALSE;
    // デプスステンシルステートの設定
    pipline_state_desc.DepthStencilState.DepthEnable = TRUE;
    pipline_state_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
    pipline_state_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    pipline_state_desc.DepthStencilState.StencilEnable = FALSE;
    pipline_state_desc.DepthStencilState.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
    pipline_state_desc.DepthStencilState.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
    pipline_state_desc.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
    pipline_state_desc.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
    pipline_state_desc.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
    pipline_state_desc.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
    pipline_state_desc.DepthStencilState.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
    pipline_state_desc.DepthStencilState.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
    pipline_state_desc.DepthStencilState.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
    pipline_state_desc.DepthStencilState.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
    pipline_state_desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

    // パイプラインステートの作成
    if (FAILED(ps_m_device->CreateGraphicsPipelineState(&pipline_state_desc , IID_PPV_ARGS(&ps_m_piplinestate))))
    {
        return false;
    }

    g_d3d12_qube_num = qube_num;

    for (int i = 0; i < g_d3d12_qube_num; i++)
    {
        g_gameobject [i].Initialize(qube [i]);
    }

    return true;
}

/**--------------------------------------------
/// \description 描画周り
///
///
///  \return true or false
//--------------------------------------------*/
bool DX3D12::Draw()
{
    DX3D12::ConfiguringCommandLists();

    ID3D12CommandList * const command_list = ps_m_commandlist;
    ps_m_commandqueue->ExecuteCommandLists(1 , &command_list);

    DX3D12::WaitFrame();

    if (FAILED(ps_m_commandallocator->Reset()))
    {
        return false;
    }

    if (FAILED(ps_m_commandlist->Reset(ps_m_commandallocator , nullptr)))
    {
        return false;
    }

    ps_m_swapchain->Present(1 , 0);

    // カレントのバックバッファのインデックスの取得
    m_rtv_index = ps_m_swapchain->GetCurrentBackBufferIndex();

    return true;
}

/**--------------------------------------------
/// \description ポインターの解放
///
///
///  \return true or false
//--------------------------------------------*/
bool DX3D12::Finalize()
{
    ps_m_factory->Release();
    ps_m_adapter->Release();
    ps_m_device->Release();
    ps_m_commandqueue->Release();
    ps_m_fence->Release();
    ps_m_swapchain->Release();
    ps_m_commandlist->Release();
    ps_m_commandallocator->Release();
    ps_m_rendertarget [0]->Release();
    ps_m_rendertarget [1]->Release();
    ps_m_descriptorheap_rtv->Release();
    ps_m_depthbuffer->Release();
    ps_m_descripterheap_dsv->Release();
    ps_m_piplinestate->Release();
    ps_m_rootsignature->Release();

    return true;
}

/**--------------------------------------------
/// \description コマンドリストの設定
///
///
///  \return true
//--------------------------------------------*/
bool DX3D12::ConfiguringCommandLists()
{
    FLOAT color [4] = { 0.0f,0.0f,0.0f,1.0f };

    // リソースの状態を変更
    DX3D12::SetResourceBarrier(D3D12_RESOURCE_STATE_PRESENT , D3D12_RESOURCE_STATE_RENDER_TARGET);

    // 深度バッファとレンダーターゲットのクリア
    ps_m_commandlist->ClearDepthStencilView(m_dsvhandle , D3D12_CLEAR_FLAG_DEPTH , 1.0f , 0 , 0 , nullptr);
    ps_m_commandlist->ClearRenderTargetView(m_rtvhandle [m_rtv_index] , color , 0 , nullptr);

    // ルートシグネチャとPSOの設定
    ps_m_commandlist->SetGraphicsRootSignature(ps_m_rootsignature);
    ps_m_commandlist->SetPipelineState(ps_m_piplinestate);

    // ビューポートとシザー矩形の設定
    ps_m_commandlist->RSSetViewports(1 , &m_viewport);
    ps_m_commandlist->RSSetScissorRects(1 , &m_scissorrect);

    // レンダーターゲットの設定
    ps_m_commandlist->OMSetRenderTargets(1 , &m_rtvhandle [m_rtv_index] , TRUE , &m_dsvhandle);

    for (int i = 0; i < g_d3d12_qube_num; i++)
    {
        g_gameobject [i].Update();
        g_gameobject [i].Draw(sm_eyepos , sm_focuspos);
    }

    // リソースの状態を変更
    DX3D12::SetResourceBarrier(D3D12_RESOURCE_STATE_RENDER_TARGET , D3D12_RESOURCE_STATE_PRESENT);

    ps_m_commandlist->Close();

    return true;
}

/**--------------------------------------------
/// \description リソースの状態を変更
///
/// \param[in] before_state
/// \param[in] after_state
///
///  \return true
//--------------------------------------------*/
bool DX3D12::SetResourceBarrier(D3D12_RESOURCE_STATES before_state , D3D12_RESOURCE_STATES after_state)
{
    D3D12_RESOURCE_BARRIER resource_barrier {};
    resource_barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    resource_barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    resource_barrier.Transition.pResource = ps_m_rendertarget [m_rtv_index];
    resource_barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    resource_barrier.Transition.StateBefore = before_state;
    resource_barrier.Transition.StateAfter = after_state;

    ps_m_commandlist->ResourceBarrier(1 , &resource_barrier);

    return true;
}

/**--------------------------------------------
/// \description 待つ
///
///
///  \return true or false
//--------------------------------------------*/
bool DX3D12::WaitFrame()
{
    const UINT64 fence = m_frame;

    if (FAILED(ps_m_commandqueue->Signal(ps_m_fence , fence)))
    {
        return false;
    }
    ++m_frame;

    if (ps_m_fence->GetCompletedValue() < fence)
    {
        if (FAILED(ps_m_fence->SetEventOnCompletion(fence , m_fence_event)))
        {
            return false;
        }

        WaitForSingleObject(m_fence_event , INFINITE);

    }

    return true;
}
