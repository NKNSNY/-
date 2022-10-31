//*=============================================================================
 // \Filename : DirectX3D.cpp
 // \Description : ダイレクトXの初期化が主
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
/// \description ダイレクトX11の初期化
///
/// \param[in] hwnd
/// \param[in] screen_width
/// \param[in] screen_height
///
///  \return true or false
//--------------------------------------------*/
bool DirectX3D::Initialize(HWND hwnd , int screen_width , int screen_height)
{
    // ファクトリーの作成
    IDXGIFactory * factory;

    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
    {
        return false;
    }

    // 機能レベルの設定
    D3D_FEATURE_LEVEL featurelevels [] =
    {
        D3D_FEATURE_LEVEL_11_1,         // ダイレクトX11
        D3D_FEATURE_LEVEL_11_0,         // ダイレクトX11
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // デバイスとデバイスコンテキストを作成
    D3D_FEATURE_LEVEL feature_level;
    if (FAILED(D3D11CreateDevice(nullptr , D3D_DRIVER_TYPE_HARDWARE , nullptr ,
        0 , featurelevels , _countof(featurelevels) , D3D11_SDK_VERSION , &ps_m_device , &feature_level , &ps_m_devicecontext)))
    {
        return false;
    };

    // スワップチェインの設定
    DXGI_SWAP_CHAIN_DESC scd;
    scd.BufferCount = 2;                                                            // バッファの数
    scd.BufferDesc.Width = screen_width;                                      // バッファの幅
    scd.BufferDesc.Height = screen_height;                                    // バッファの高さ
    scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;          // バッファのフォーマット
    scd.BufferDesc.RefreshRate.Numerator = 0;                              // リフレッシュレート
    scd.BufferDesc.RefreshRate.Denominator = 1;                           // リフレッシュレート
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;          // バッファの使用方法
    scd.OutputWindow = hwnd;                                                   // 関連ウィンドウ
    scd.SampleDesc.Count = 1;                                                   // サンプルの数
    scd.SampleDesc.Quality = 0;                                                 // サンプルのクオリティ
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.Windowed = true;                                                        // ウィンドウモード
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // スワップチェインの作成
    if (FAILED(factory->CreateSwapChain(ps_m_device , &scd , &ps_m_swapchain)))
    {
        return false;
    }

    // バックバッファ
    ID3D11Texture2D * backbuffer;

    if (FAILED(ps_m_swapchain->GetBuffer(0 , IID_PPV_ARGS(&backbuffer))))
    {
        return false;
    }

    if (FAILED(ps_m_device->CreateRenderTargetView(backbuffer , nullptr , &ps_m_rendertargetview)))
    {
        return false;
    }

    // 深度ステンシルバッファの設定
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

    // レンダリングターゲットの設定
    ps_m_devicecontext->OMSetRenderTargets(1 , &ps_m_rendertargetview , ps_m_depthstencilview);

    // ビューポートの設定
    D3D11_VIEWPORT viewport = { 0,0,(float) screen_width,(float) screen_height,0.0f,1.0f };
    ps_m_devicecontext->RSSetViewports(1 , &viewport);

    return true;

}
