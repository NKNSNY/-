//*=============================================================================
 // \Filename : System_Shader.h
 // \Description : �V�F�[�_�[�֘A
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once
#include "System_DirectX3D.h"

class Shader
{
public:
//---------------------------------------------------------------------------
    // public�ȃ��\�b�h

    static bool Initialize();
    static bool Draw(DirectX::XMFLOAT3 vertexlist []);

    // public�ȕϐ�

    static DirectX::XMFLOAT3 m_eyepostion;

//---------------------------------------------------------------------------

private:
//---------------------------------------------------------------------------
    // private�ȕϐ�

    static ID3D11VertexShader * ps_m_vertexshader;
    static ID3D11PixelShader * ps_m_pixelshader;
    static ID3D11InputLayout * ps_m_inputlayout;
    static D3D11_VIEWPORT  m_viewport;

//---------------------------------------------------------------------------
    ///<
    /// ps_m_vertexshader       ���_�V�F�[�_�[
    /// ps_m_pixelshader          �s�N�Z���V�F�[�_�[
    /// ps_m_inputlayout          ���_���C�A�E�g
    /// m_viewport                  �r���[�|�[�g
    /// m_eyeposition              ����ꏊ��ς���
    ///<

};
