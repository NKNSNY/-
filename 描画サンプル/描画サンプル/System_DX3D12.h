//*=============================================================================
 // \Filename : System_DX3D12.h
 // \Description : ダイレクトX12を使用する
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
        // publicなメソッド

        // ゲッター
    static ID3D12Device * GetDX3D12Device();
    static ID3D12GraphicsCommandList * GetDX3D12CommandList();

    // セッター
    static bool SetCamera(DirectX::XMFLOAT3 eye , DirectX::XMFLOAT3 focus);

    // 初期化
    static bool Initialize(HWND hwnd , int screen_width , int screen_height , int qube_num , QubeStatus qube []);
    // 描画
    static bool Draw();
    // 解放
    static bool Finalize();

    // コマンドリスト
    static bool ConfiguringCommandLists();
    // リソースバリアー
    static bool SetResourceBarrier(D3D12_RESOURCE_STATES before_state ,
        D3D12_RESOURCE_STATES after_state);
    // フレームを待つ
    static bool WaitFrame();

    //---------------------------------------------------------------------------

private:
    //---------------------------------------------------------------------------
        // privateな変数

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
        /// m_frame                                 フレーム
        /// m_rtv_index                             RTVのインデックス
        /// ps_m_factory                           ファクトリ
        /// ps_m_adapter                            アダプター
        /// ps_m_device                             デバイス
        /// ps_m_commandqueue                   コマンドキュー
        /// m_fence_event                           フェンス
        /// ps_m_fence                                  フェンス
        /// ps_m_swapchain                          スワップチェイン
        /// ps_m_commandlist                        コマンドリスト
        /// ps_m_commandallcator                コマンドアロケータ
        /// ps_m_rendertarget                       レンダーターゲット
        /// ps_m_descliptorheap_rtv             RTV用のデスクリプタヒープ
        /// m_rtvhandle                             RTV用のハンドル
        /// ps_m_depthbuffer                        深度バッファ
        /// ps_m_descrlpterheap_dsv             DSV用のデスクリプタヒープ
        /// m_dsvhandle                             DSV用のハンドル
        /// ps_m_piplinestate                       パイプラインステート
        /// ps_m_rootsignature                      ルートシグネチャ
        /// m_scissorrect                           シザー矩形
        /// m_viewport                              ビューポート
        /// sm_eyepos                               カメラの位置
        /// sm_focuspos                             カメラの向き
        /// < 
};
