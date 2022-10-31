//*=============================================================================
 // \Filename : DirectX3D.h
 // \Description : ダイレクトXを使うよ
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d11.h>
#include <DirectXMath.h>

class DirectX3D
{
public:
//---------------------------------------------------------------------------
    // publicなメソッド

    // ゲッター
    static ID3D11Device * GetDevice();                                  // デバイスを取得
    static ID3D11DeviceContext * GetDeviceContext();            // デバイスコンテキストを取得
    static IDXGISwapChain * GetSwapChain();                         // スワップチェインを取得
    static ID3D11RenderTargetView * GetRenderTarget();       // レンダーターゲットビューを取得
    static ID3D11DepthStencilView * GetDepthStenvilView();    // 深度バッファを取得

    // ダイレクトX11初期化
    static bool Initialize(HWND hwnd , int screen_widht , int screen_height);

//---------------------------------------------------------------------------

private:
//---------------------------------------------------------------------------
    // privateな変数

    static ID3D11Device* ps_m_device;
    static ID3D11DeviceContext * ps_m_devicecontext;
    static IDXGISwapChain * ps_m_swapchain;
    static ID3D11RenderTargetView * ps_m_rendertargetview;
    static ID3D11Texture2D * ps_m_texture;
    static ID3D11DepthStencilView * ps_m_depthstencilview;

//---------------------------------------------------------------------------
    ///<
    /// ps_m_device                      デバイス
    /// ps_m_devicecontext            デバイスコンテキスト
    /// ps_m_swapchain                 スワップチェイン
    /// ps_m_rendertargetview       レンダーターゲットビュー
    /// ps_m_texture                    深度バッファ用のテクスチャ
    /// ps_m_depthstencilview       深度バッファビュー
    ///<
};
