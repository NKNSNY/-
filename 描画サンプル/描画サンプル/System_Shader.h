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

    static bool Initialize();
    static bool Draw(DirectX::XMFLOAT3 vertexlist []);

    // publicな変数

    static DirectX::XMFLOAT3 m_eyepostion;

//---------------------------------------------------------------------------

private:
//---------------------------------------------------------------------------
    // privateな変数

    static ID3D11VertexShader * ps_m_vertexshader;
    static ID3D11PixelShader * ps_m_pixelshader;
    static ID3D11InputLayout * ps_m_inputlayout;
    static D3D11_VIEWPORT  m_viewport;

//---------------------------------------------------------------------------
    ///<
    /// ps_m_vertexshader       頂点シェーダー
    /// ps_m_pixelshader          ピクセルシェーダー
    /// ps_m_inputlayout          頂点レイアウト
    /// m_viewport                  ビューポート
    /// m_eyeposition              見る場所を変える
    ///<

};
