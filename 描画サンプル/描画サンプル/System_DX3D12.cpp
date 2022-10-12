#include "System_DX3D12.h"

bool DX3D12::Initialize(HWND hwnd , int screen_width , int screen_height)
{
    // �t�@�N�g���̍쐬
    IDXGIFactory4 * factory;

    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
    {
        return false;
    }

    // �A�_�v�^�̍쐬
    IDXGIAdapter3 * adapter;

    factory->EnumAdapters(0 , (IDXGIAdapter **) &adapter);

    // �A�_�v�^���g�p���ăf�o�C�X�̍쐬
    ID3D12Device * device;

    if (FAILED(D3D12CreateDevice(adapter , D3D_FEATURE_LEVEL_11_1 , IID_PPV_ARGS(&device))))
    {
        return false;
    }

    // �R�}���h�L���[�̐ݒ�
    D3D12_COMMAND_QUEUE_DESC command_queue_desc;
    command_queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    command_queue_desc.NodeMask = 0;
    command_queue_desc.Priority = 0;
    command_queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    // �R�}���h�L���[�̍쐬
    ID3D12CommandQueue * commandqueue;

    if (FAILED(device->CreateCommandQueue(&command_queue_desc , IID_PPV_ARGS(&commandqueue))))
    {
        return false;
    }

    // �t�F���X�̍쐬
    ID3D12Fence * command_queue_fence;

    HANDLE fence;
    fence = CreateEventEx(nullptr , FALSE , FALSE , EVENT_ALL_ACCESS);
    if (fence == NULL)
    {
        return false;
    }

    if (FAILED(device->CreateFence(0 , D3D12_FENCE_FLAG_NONE , IID_PPV_ARGS(&command_queue_fence))))
    {
        return false;
    }

    // �X���b�v�`�F�C���̐ݒ�
    DXGI_SWAP_CHAIN_DESC swap_chain_desc;
    swap_chain_desc.BufferCount = 2;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swap_chain_desc.BufferDesc.Height = screen_height;
    swap_chain_desc.BufferDesc.Width = screen_width;
    swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swap_chain_desc.OutputWindow = hwnd;
    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.SampleDesc.Quality = 0;
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swap_chain_desc.Windowed = true;

    // �X���b�v�`�F�C���̍쐬
    IDXGISwapChain * swapchain;

    if (FAILED(factory->CreateSwapChain(commandqueue , &swap_chain_desc , &swapchain)))
    {
        return false;
    }

    if (FAILED(swapchain->QueryInterface(&swapchain)))
    {
        return false;
    }

    // �f�X�N���v�^�q�[�v�̐ݒ�
    D3D12_DESCRIPTOR_HEAP_DESC descriptor_heap_desc;
    descriptor_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    descriptor_heap_desc.NodeMask = 0;
    descriptor_heap_desc.NumDescriptors = 2;
    descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

    // �f�X�N���v�^�[�q�[�v�̍쐬
    ID3D12DescriptorHeap * descriptorheap;

    if (FAILED(device->CreateDescriptorHeap(&descriptor_heap_desc , IID_PPV_ARGS(&descriptorheap))))
    {
        return false;
    }

    // �����_�[�^�[�Q�b�g�r���[�̍쐬�Ɠo�^
    UINT size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    ID3D12Resource * rendertarget [2];
    D3D12_CPU_DESCRIPTOR_HANDLE rendertargetview [2];

    for (int i = 0; i < 2; i++)
    {
        if (FAILED(swapchain->GetBuffer(i , IID_PPV_ARGS(&rendertarget [i]))))
        {
            return false;
        }

        rendertargetview [i] = descriptorheap->GetCPUDescriptorHandleForHeapStart();
        rendertargetview [i].ptr += size * i;
        device->CreateRenderTargetView(rendertarget [i] , nullptr , rendertargetview [i]);
    }

    // �R�}���h�A���P�[�^�̍쐬
    ID3D12CommandAllocator * commandallocator;

    if (FAILED(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT , IID_PPV_ARGS(&commandallocator))))
    {
        return false;
    }

    // �R�}���h���X�g�̍쐬�Ɗ��蓖��
    ID3D12GraphicsCommandList * commandlist;

    if (FAILED(device->CreateCommandList(0 , D3D12_COMMAND_LIST_TYPE_DIRECT ,
        commandallocator , nullptr , IID_PPV_ARGS(&commandlist))))
    {
        return false;
    }

    // ���[�g�V�O�l�`���̐ݒ�
    D3D12_ROOT_PARAMETER root_parameter [1];
    D3D12_ROOT_SIGNATURE_DESC root_signature_desc;
    ID3DBlob * blob;

    root_parameter [0].Descriptor.RegisterSpace = 0;
    root_parameter [0].Descriptor.ShaderRegister = 0;
    root_parameter [0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
    root_parameter [0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    root_signature_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    root_signature_desc.NumParameters = ARRAYSIZE(root_parameter);
    root_signature_desc.NumStaticSamplers = 0;
    root_signature_desc.pParameters = root_parameter;
    root_signature_desc.pStaticSamplers = nullptr;

    if (FAILED(D3D12SerializeRootSignature(&root_signature_desc , D3D_ROOT_SIGNATURE_VERSION_1 , &blob , nullptr)))
    {
        return false;
    }

    // ���[�g�V�O�l�`���̍쐬
    ID3D12RootSignature * rootsignature;

    if (FAILED(device->CreateRootSignature(0 , blob->GetBufferPointer() , blob->GetBufferSize() , IID_PPV_ARGS(&rootsignature))))
    {
        return false;
    }

    // PSO�̍쐬
    ID3DBlob * vertexshader;
    ID3DBlob * pixelshader;

    if (FAILED(D3DCompileFromFile(L"DX12_VS.hlsl" , nullptr , nullptr , "VSmain" , "vs_5_0" , 0 , 0 , &vertexshader , nullptr)))
    {
        return false;
    }

    if (FAILED(D3DCompileFromFile(L"DX12_PS.hlsl" , nullptr , nullptr , "PSmain" , "ps_5_0" , 0 , 0 , &pixelshader , nullptr)))
    {
        return false;
    }

    // ���_���C�A�E�g
    D3D12_INPUT_ELEMENT_DESC input_element_desc [] =
    {
        { "POSITION" , 0 , DXGI_FORMAT_R32G32B32_FLOAT , 0 , 0 , D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA , 0 },
        { "COLOR" , 0 , DXGI_FORMAT_R32G32B32A32_FLOAT , 0 , 24 , D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA , 0 }
    };

    // PSO�̐ݒ�
    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipline_state_desc;

    // �V�F�[�_�[�̐ݒ�
    pipline_state_desc.VS.BytecodeLength = vertexshader->GetBufferSize();
    pipline_state_desc.VS.pShaderBytecode = vertexshader->GetBufferPointer();
    pipline_state_desc.PS.BytecodeLength = pixelshader->GetBufferSize();
    pipline_state_desc.PS.pShaderBytecode = pixelshader->GetBufferPointer();
    // ���_���C�A�E�g�̍쐬
    pipline_state_desc.InputLayout.NumElements = ARRAYSIZE(input_element_desc);
    pipline_state_desc.InputLayout.pInputElementDescs = input_element_desc;
    // �T���v���n�̐ݒ�
    pipline_state_desc.SampleDesc.Count = 1;
    pipline_state_desc.SampleDesc.Quality = 0;
    pipline_state_desc.SampleMask = UINT_MAX;
    // �����_�[�^�[�Q�b�g�̐ݒ�
    pipline_state_desc.NumRenderTargets = 1;
    pipline_state_desc.RTVFormats [0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    // �g�|���W�[�̐ݒ�
    pipline_state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    // ���[�g�V�O�l�`��
    pipline_state_desc.pRootSignature = rootsignature;
    // ���X�^���C�U�X�e�[�g�̐ݒ�
    pipline_state_desc.RasterizerState.AntialiasedLineEnable = FALSE;
    pipline_state_desc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
    pipline_state_desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    pipline_state_desc.RasterizerState.DepthBias = 0;
    pipline_state_desc.RasterizerState.DepthBiasClamp = 0;
    pipline_state_desc.RasterizerState.DepthClipEnable = TRUE;
    pipline_state_desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    pipline_state_desc.RasterizerState.FrontCounterClockwise = FALSE;
    pipline_state_desc.RasterizerState.MultisampleEnable = FALSE;
    pipline_state_desc.RasterizerState.SlopeScaledDepthBias = 0;
    // �u�����h�X�e�[�g�̐ݒ�
    for (int i = 0; i < ARRAYSIZE(pipline_state_desc.BlendState.RenderTarget); ++i)
    {
        pipline_state_desc.BlendState.RenderTarget [i].BlendEnable = FALSE;
        pipline_state_desc.BlendState.RenderTarget [i].BlendOp = D3D12_BLEND_OP_ADD;
        pipline_state_desc.BlendState.RenderTarget [i].BlendOpAlpha = D3D12_BLEND_OP_ADD;
        pipline_state_desc.BlendState.RenderTarget [i].DestBlend = D3D12_BLEND_ZERO;
        pipline_state_desc.BlendState.RenderTarget [i].DestBlendAlpha = D3D12_BLEND_ZERO;
        pipline_state_desc.BlendState.RenderTarget [i].LogicOp = D3D12_LOGIC_OP_CLEAR;
        pipline_state_desc.BlendState.RenderTarget [i].LogicOpEnable = FALSE;
        pipline_state_desc.BlendState.RenderTarget [i].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
        pipline_state_desc.BlendState.RenderTarget [i].SrcBlend = D3D12_BLEND_ONE;
        pipline_state_desc.BlendState.RenderTarget [i].SrcBlendAlpha = D3D12_BLEND_ONE;
    }
    pipline_state_desc.BlendState.AlphaToCoverageEnable = FALSE;
    pipline_state_desc.BlendState.IndependentBlendEnable = FALSE;
    // �f�v�X�X�e���V���X�e�[�g�̐ݒ�
    pipline_state_desc.DepthStencilState.DepthEnable = TRUE;
    pipline_state_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
    pipline_state_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    pipline_state_desc.DepthStencilState.StencilEnable = FALSE;
    pipline_state_desc.DepthStencilState.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
    pipline_state_desc.DepthStencilState.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

    pipline_state_desc.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
    pipline_state_desc.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
    pipline_state_desc.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
    pipline_state_desc.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;

    pipline_state_desc.DepthStencilState.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
    pipline_state_desc.DepthStencilState.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
    pipline_state_desc.DepthStencilState.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
    pipline_state_desc.DepthStencilState.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;

    pipline_state_desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

    ID3D12PipelineState *pipelinestate;

    if (FAILED(device->CreateGraphicsPipelineState(&pipline_state_desc , IID_PPV_ARGS(&pipelinestate))))
    {
        return false;
    }

    return true;
}
