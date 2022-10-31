//*=============================================================================
 // \Filename : System_Shader.h
 // \Description : シェーダー関連
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once
#include "System_DirectX3D.h"

class Shader
{
public:
    //---------------------------------------------------------------------------
        // publicなメソッド

    static bool SetCamera(DirectX::XMFLOAT3 eye , DirectX::XMFLOAT3 focus);

    static bool Initialize();
    static bool Draw(DirectX::XMFLOAT3 vertexlist [] , DirectX::XMFLOAT3 position);
    static bool Finalize();

    //---------------------------------------------------------------------------

private:
    //---------------------------------------------------------------------------
        // privateな変数

    static ID3D11VertexShader * ps_m_vertexshader;
    static ID3D11PixelShader * ps_m_pixelshader;
    static ID3D11InputLayout * ps_m_inputlayout;
    static D3D11_VIEWPORT  m_viewport;
    static DirectX::XMFLOAT3 m_eyepostion;
    static DirectX::XMFLOAT3 m_focusposition;

    //---------------------------------------------------------------------------
        ///<
        /// ps_m_vertexshader       頂点シェーダー
        /// ps_m_pixelshader          ピクセルシェーダー
        /// ps_m_inputlayout          頂点レイアウト
        /// m_viewport                  ビューポート
        /// m_eyeposition              見る場所を変える
        /// m_focusposition           注視点を変える
        ///<

};
