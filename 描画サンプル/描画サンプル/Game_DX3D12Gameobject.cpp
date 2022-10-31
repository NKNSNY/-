//*=============================================================================
 // \Filename : Game_DX3D12Gameobject.cpp
 // \Description : オブジェクトの設定
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Game_DX3D12Gameobject.h"

using namespace DirectX;

/**--------------------------------------------
/// \description オブジェクトの初期化
///
///
///  \return true or false
//--------------------------------------------*/
bool DX3D12GameObject::Initialize(QubeStatus qube)
{
    // バッファ設定
    D3D12_HEAP_PROPERTIES heap_properties {};
    heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heap_properties.CreationNodeMask = 0;
    heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heap_properties.Type = D3D12_HEAP_TYPE_UPLOAD;
    heap_properties.VisibleNodeMask = 0;

    D3D12_RESOURCE_DESC resource_desc {};
    resource_desc.DepthOrArraySize = 1;
    resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resource_desc.Format = DXGI_FORMAT_UNKNOWN;
    resource_desc.Height = 1;
    resource_desc.Width = 256;
    resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    resource_desc.MipLevels = 1;
    resource_desc.SampleDesc.Count = 1;
    resource_desc.SampleDesc.Quality = 0;

    // 頂点バッファの作成
    if (FAILED(DX3D12::GetDX3D12Device()->CreateCommittedResource(
        &heap_properties , D3D12_HEAP_FLAG_NONE , &resource_desc ,
        D3D12_RESOURCE_STATE_GENERIC_READ , nullptr , IID_PPV_ARGS(&pm_vertexbuffer))))
    {
        return false;
    }

    // 定数バッファの作成
    if (FAILED(DX3D12::GetDX3D12Device()->CreateCommittedResource(
        &heap_properties , D3D12_HEAP_FLAG_NONE , &resource_desc ,
        D3D12_RESOURCE_STATE_GENERIC_READ , nullptr , IID_PPV_ARGS(&pm_constbuffer))))
    {
        return false;
    }

    // 頂点データの書き込み
    Vertex * buffer {};

    XMFLOAT3 vp = qube.size;

    if (FAILED(pm_vertexbuffer->Map(0 , nullptr , (void **) &buffer)))
    {
        return false;
    }

    // 手前
    buffer [0].position = { -vp.x,   vp.y,  -vp.z };
    buffer [1].position = { vp.x,   vp.y,  -vp.z };
    buffer [2].position = { -vp.x, -vp.y,  -vp.z };
    buffer [3].position = { vp.x,   vp.y,  -vp.z };
    buffer [4].position = { vp.x, -vp.y,  -vp.z };
    buffer [5].position = { -vp.x, -vp.y,  -vp.z };

    // 後ろ
    buffer [6].position = { vp.x,   vp.y,   vp.z };
    buffer [7].position = { -vp.x,   vp.y,   vp.z };
    buffer [8].position = { vp.x, -vp.y,   vp.z };
    buffer [9].position = { -vp.x,   vp.y,   vp.z };
    buffer [10].position = { -vp.x, -vp.y,   vp.z };
    buffer [11].position = { vp.x, -vp.y,   vp.z };

    // 右
    buffer [12].position = { vp.x,   vp.y, -vp.z };
    buffer [13].position = { vp.x,   vp.y,   vp.z };
    buffer [14].position = { vp.x, -vp.y, -vp.z };
    buffer [15].position = { vp.x,   vp.y,   vp.z };
    buffer [16].position = { vp.x, -vp.y,   vp.z };
    buffer [17].position = { vp.x, -vp.y, -vp.z };

    // 左
    buffer [18].position = { -vp.x,   vp.y,   vp.z };
    buffer [19].position = { -vp.x,   vp.y, -vp.z };
    buffer [20].position = { -vp.x, -vp.y,   vp.z };
    buffer [21].position = { -vp.x,   vp.y, -vp.z };
    buffer [22].position = { -vp.x, -vp.y, -vp.z };
    buffer [23].position = { -vp.x, -vp.y,   vp.z };

    // 上
    buffer [24].position = { -vp.x,   vp.y,   vp.z };
    buffer [25].position = { vp.x,   vp.y,   vp.z };
    buffer [26].position = { -vp.x,   vp.y, -vp.z };
    buffer [27].position = { vp.x,   vp.y,   vp.z };
    buffer [28].position = { vp.x,   vp.y, -vp.z };
    buffer [29].position = { -vp.x,   vp.y, -vp.z };

    // 下
    buffer [30].position = { -vp.x, -vp.y, -vp.z };
    buffer [31].position = { vp.x, -vp.y, -vp.z };
    buffer [32].position = { -vp.x, -vp.y,   vp.z };
    buffer [33].position = { vp.x, -vp.y, -vp.z };
    buffer [34].position = { vp.x, -vp.y,   vp.z };
    buffer [35].position = { -vp.x, -vp.y,   vp.z };

    // 法線ベクトル
    // カラー
    for (int i = 0; i < 36; i++)
    {
        buffer [i].normal = { 0.0f,0.0f,0.0f };
        buffer [i].color = qube.color;
    }

    for (int i = 0; i < 36; i++)
    {
        buffer [i].position.x += qube.position.x;
        buffer [i].position.y += qube.position.y;
        buffer [i].position.z += qube.position.z;
    }

    pm_vertexbuffer->Unmap(0 , nullptr);

    buffer = nullptr;

    return true;
}

/**--------------------------------------------
/// \description オブジェクトの更新
///
///
///  \return true or false
//--------------------------------------------*/
bool DX3D12GameObject::Update()
{

    return true;
}

/**--------------------------------------------
/// \description オブジェクトの描画
///
///
///  \return true or false
//--------------------------------------------*/
bool DX3D12GameObject::Draw(DirectX::XMFLOAT3 eye , DirectX::XMFLOAT3 focus)
{

    // カメラの設定
    XMMATRIX view = XMMatrixLookAtLH({ eye.x,eye.y,eye.z } , { focus.x,focus.y,focus.z } , { 0.0f,1.0f,0.0f });
    XMMATRIX proj = XMMatrixPerspectiveFovLH({ XMConvertToRadians(60.0f) } , 2.0f , 1.0f , 20.0f);

    // 変換行列
    XMFLOAT4X4 mat;
    XMStoreFloat4x4(&mat , XMMatrixTranspose(view * proj));


    XMFLOAT4X4 * buffer {};

    if (FAILED(pm_constbuffer->Map(0 , nullptr , (void **) &buffer)));
    {
        //return false;
    }

    // 行列を定数バッファに書き込み
    *buffer = mat;

    pm_constbuffer->Unmap(0 , nullptr);
    buffer = nullptr;

    D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view {};
    vertex_buffer_view.BufferLocation = pm_vertexbuffer->GetGPUVirtualAddress();
    vertex_buffer_view.SizeInBytes = sizeof(Vertex) * 36;
    vertex_buffer_view.StrideInBytes = sizeof(Vertex);

    // 定数バッファをシェーダーのレジスタにセット
    DX3D12::GetDX3D12CommandList()->SetGraphicsRootConstantBufferView(0 , pm_constbuffer->GetGPUVirtualAddress());

    // インデックスを使用しないで描画
    //DX3D12::GetDX3D12CommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    DX3D12::GetDX3D12CommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    DX3D12::GetDX3D12CommandList()->IASetVertexBuffers(0 , 1 , &vertex_buffer_view);

    // 描画
    DX3D12::GetDX3D12CommandList()->DrawInstanced(36 , 1 , 0 , 0);


    return true;
}
