//*=============================================================================
 // \Filename : System_DX3D12.h
 // \Description : �_�C���N�gX12���g�p����
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#pragma once

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#include "Game_DX3D12Gameobject.h"
#include "Game_QubeStatus.h" 


struct Vertex
{
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT4 color;
};


class DX3D12
{
public:
    //---------------------------------------------------------------------------
        // public�ȃ��\�b�h

        // �Q�b�^�[
    static ID3D12Device * GetDX3D12Device();
    static ID3D12GraphicsCommandList * GetDX3D12CommandList();

    // �Z�b�^�[
    static bool SetCamera(DirectX::XMFLOAT3 eye , DirectX::XMFLOAT3 focus);

    // ������
    static bool Initialize(HWND hwnd , int screen_width , int screen_height , int qube_num , QubeStatus qube []);
    // �`��
    static bool Draw();
    // ���
    static bool Finalize();

    // �R�}���h���X�g
    static bool ConfiguringCommandLists();
    // ���\�[�X�o���A�[
    static bool SetResourceBarrier(D3D12_RESOURCE_STATES before_state ,
        D3D12_RESOURCE_STATES after_state);
    // �t���[����҂�
    static bool WaitFrame();

    //---------------------------------------------------------------------------

private:
    //---------------------------------------------------------------------------
        // private�ȕϐ�

    static UINT64 m_frame;
    static UINT m_rtv_index;

    static IDXGIFactory4 * ps_m_factory;
    static IDXGIAdapter3 * ps_m_adapter;
    static ID3D12Device * ps_m_device;
    static ID3D12CommandQueue * ps_m_commandqueue;
    static HANDLE m_fence_event;
    static ID3D12Fence * ps_m_fence;
    static IDXGISwapChain3 * ps_m_swapchain;
    static ID3D12GraphicsCommandList * ps_m_commandlist;
    static ID3D12CommandAllocator * ps_m_commandallocator;
    static ID3D12Resource * ps_m_rendertarget [2];
    static ID3D12DescriptorHeap * ps_m_descriptorheap_rtv;
    static D3D12_CPU_DESCRIPTOR_HANDLE m_rtvhandle [2];
    static ID3D12Resource * ps_m_depthbuffer;
    static ID3D12DescriptorHeap * ps_m_descripterheap_dsv;
    static D3D12_CPU_DESCRIPTOR_HANDLE m_dsvhandle;
    static ID3D12PipelineState * ps_m_piplinestate;
    static ID3D12RootSignature * ps_m_rootsignature;
    static D3D12_RECT m_scissorrect;
    static D3D12_VIEWPORT m_viewport;

    static DirectX::XMFLOAT3 sm_eyepos;
    static DirectX::XMFLOAT3 sm_focuspos;

    //---------------------------------------------------------------------------
        ///<
        /// m_frame                                 �t���[��
        /// m_rtv_index                             RTV�̃C���f�b�N�X
        /// ps_m_factory                           �t�@�N�g��
        /// ps_m_adapter                            �A�_�v�^�[
        /// ps_m_device                             �f�o�C�X
        /// ps_m_commandqueue                   �R�}���h�L���[
        /// m_fence_event                           �t�F���X
        /// ps_m_fence                                  �t�F���X
        /// ps_m_swapchain                          �X���b�v�`�F�C��
        /// ps_m_commandlist                        �R�}���h���X�g
        /// ps_m_commandallcator                �R�}���h�A���P�[�^
        /// ps_m_rendertarget                       �����_�[�^�[�Q�b�g
        /// ps_m_descliptorheap_rtv             RTV�p�̃f�X�N���v�^�q�[�v
        /// m_rtvhandle                             RTV�p�̃n���h��
        /// ps_m_depthbuffer                        �[�x�o�b�t�@
        /// ps_m_descrlpterheap_dsv             DSV�p�̃f�X�N���v�^�q�[�v
        /// m_dsvhandle                             DSV�p�̃n���h��
        /// ps_m_piplinestate                       �p�C�v���C���X�e�[�g
        /// ps_m_rootsignature                      ���[�g�V�O�l�`��
        /// m_scissorrect                           �V�U�[��`
        /// m_viewport                              �r���[�|�[�g
        /// sm_eyepos                               �J�����̈ʒu
        /// sm_focuspos                             �J�����̌���
        /// < 
};
