//*=============================================================================
 // \Filename : DirectX3D.cpp
 // \Description : �_�C���N�gX�̏���������
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "System_DirectX3D.h"

ID3D11Device * DirectX3D::ps_m_device;
ID3D11DeviceContext * DirectX3D::ps_m_devicecontext;
IDXGISwapChain * DirectX3D::ps_m_swapchain;
ID3D11RenderTargetView * DirectX3D::ps_m_rendertargetview;
ID3D11Texture2D * DirectX3D::ps_m_texture;
ID3D11DepthStencilView * DirectX3D::ps_m_depthstencilview;

ID3D11Device * DirectX3D::GetDevice()
{
    return ps_m_device;
}

ID3D11DeviceContext * DirectX3D::GetDeviceContext()
{
    return ps_m_devicecontext;
}

IDXGISwapChain * DirectX3D::GetSwapChain()
{
    return ps_m_swapchain;
}

ID3D11RenderTargetView * DirectX3D::GetRenderTarget()
{
    return ps_m_rendertargetview;
}

ID3D11DepthStencilView * DirectX3D::GetDepthStenvilView()
{
    return ps_m_depthstencilview;
}


/**--------------------------------------------
/// \description �_�C���N�gX11�̏�����
///
/// \param[in] hwnd
/// \param[in] screen_width
/// \param[in] screen_height
///
///  \return true or false
//--------------------------------------------*/
bool DirectX3D::Initialize(HWND hwnd , int screen_width , int screen_height)
{
    // �t�@�N�g���[�̍쐬
    IDXGIFactory * factory;

    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
    {
        return false;
    }

    // �@�\���x���̐ݒ�
    D3D_FEATURE_LEVEL featurelevels [] =
    {
        D3D_FEATURE_LEVEL_11_1,         // �_�C���N�gX11
        D3D_FEATURE_LEVEL_11_0,         // �_�C���N�gX11
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // �f�o�C�X�ƃf�o�C�X�R���e�L�X�g���쐬
    D3D_FEATURE_LEVEL feature_level;
    if (FAILED(D3D11CreateDevice(nullptr , D3D_DRIVER_TYPE_HARDWARE , nullptr ,
        0 , featurelevels , _countof(featurelevels) , D3D11_SDK_VERSION , &ps_m_device , &feature_level , &ps_m_devicecontext)))
    {
        return false;
    };

    // �X���b�v�`�F�C���̐ݒ�
    DXGI_SWAP_CHAIN_DESC scd;
    scd.BufferCount = 2;                                                            // �o�b�t�@�̐�
    scd.BufferDesc.Width = screen_width;                                      // �o�b�t�@�̕�
    scd.BufferDesc.Height = screen_height;                                    // �o�b�t�@�̍���
    scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;          // �o�b�t�@�̃t�H�[�}�b�g
    scd.BufferDesc.RefreshRate.Numerator = 0;                              // ���t���b�V�����[�g
    scd.BufferDesc.RefreshRate.Denominator = 1;                           // ���t���b�V�����[�g
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;          // �o�b�t�@�̎g�p���@
    scd.OutputWindow = hwnd;                                                   // �֘A�E�B���h�E
    scd.SampleDesc.Count = 1;                                                   // �T���v���̐�
    scd.SampleDesc.Quality = 0;                                                 // �T���v���̃N�I���e�B
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.Windowed = true;                                                        // �E�B���h�E���[�h
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // �X���b�v�`�F�C���̍쐬
    if (FAILED(factory->CreateSwapChain(ps_m_device , &scd , &ps_m_swapchain)))
    {
        return false;
    }

    // �o�b�N�o�b�t�@
    ID3D11Texture2D * backbuffer;

    if (FAILED(ps_m_swapchain->GetBuffer(0 , IID_PPV_ARGS(&backbuffer))))
    {
        return false;
    }

    if (FAILED(ps_m_device->CreateRenderTargetView(backbuffer , nullptr , &ps_m_rendertargetview)))
    {
        return false;
    }

    // �[�x�X�e���V���o�b�t�@�̐ݒ�
    D3D11_TEXTURE2D_DESC texture_desc;

    ZeroMemory(&texture_desc , sizeof(texture_desc));
    texture_desc.Height = screen_height;
    texture_desc.Width = screen_width;
    texture_desc.MipLevels = 1;
    texture_desc.ArraySize = 1;
    texture_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    texture_desc.SampleDesc.Count = 1;
    texture_desc.SampleDesc.Quality = 0;
    texture_desc.Usage = D3D11_USAGE_DEFAULT;
    texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    texture_desc.CPUAccessFlags = 0;
    texture_desc.MiscFlags = 0;

    if (FAILED(ps_m_device->CreateTexture2D(&texture_desc , NULL , &ps_m_texture)))
    {
        return false;
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC ds_desc;
    ZeroMemory(&ds_desc , sizeof(ds_desc));
    ds_desc.Format = texture_desc.Format;
    ds_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    ds_desc.Texture2D.MipSlice = 0;

    if (FAILED(ps_m_device->CreateDepthStencilView(ps_m_texture , &ds_desc , &ps_m_depthstencilview)))
    {
        return false;
    }

    // �����_�����O�^�[�Q�b�g�̐ݒ�
    ps_m_devicecontext->OMSetRenderTargets(1 , &ps_m_rendertargetview , ps_m_depthstencilview);

    // �r���[�|�[�g�̐ݒ�
    D3D11_VIEWPORT viewport = { 0,0,(float) screen_width,(float) screen_height,0.0f,1.0f };
    ps_m_devicecontext->RSSetViewports(1 , &viewport);

    return true;

}
