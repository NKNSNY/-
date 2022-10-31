//*=============================================================================
 // \Filename : DirectX3D.h
 // \Description : �_�C���N�gX���g����
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
    // public�ȃ��\�b�h

    // �Q�b�^�[
    static ID3D11Device * GetDevice();                                  // �f�o�C�X���擾
    static ID3D11DeviceContext * GetDeviceContext();            // �f�o�C�X�R���e�L�X�g���擾
    static IDXGISwapChain * GetSwapChain();                         // �X���b�v�`�F�C�����擾
    static ID3D11RenderTargetView * GetRenderTarget();       // �����_�[�^�[�Q�b�g�r���[���擾
    static ID3D11DepthStencilView * GetDepthStenvilView();    // �[�x�o�b�t�@���擾

    // �_�C���N�gX11������
    static bool Initialize(HWND hwnd , int screen_widht , int screen_height);

//---------------------------------------------------------------------------

private:
//---------------------------------------------------------------------------
    // private�ȕϐ�

    static ID3D11Device* ps_m_device;
    static ID3D11DeviceContext * ps_m_devicecontext;
    static IDXGISwapChain * ps_m_swapchain;
    static ID3D11RenderTargetView * ps_m_rendertargetview;
    static ID3D11Texture2D * ps_m_texture;
    static ID3D11DepthStencilView * ps_m_depthstencilview;

//---------------------------------------------------------------------------
    ///<
    /// ps_m_device                      �f�o�C�X
    /// ps_m_devicecontext            �f�o�C�X�R���e�L�X�g
    /// ps_m_swapchain                 �X���b�v�`�F�C��
    /// ps_m_rendertargetview       �����_�[�^�[�Q�b�g�r���[
    /// ps_m_texture                    �[�x�o�b�t�@�p�̃e�N�X�`��
    /// ps_m_depthstencilview       �[�x�o�b�t�@�r���[
    ///<
};
