//*=============================================================================
 // \Filename : Game_DX3D12Gameobject.cpp
 // \Description : �I�u�W�F�N�g�̐ݒ�
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Game_DX3D12Gameobject.h"

using namespace DirectX;

/**--------------------------------------------
/// \description �I�u�W�F�N�g�̏�����
///
///
///  \return true or false
//--------------------------------------------*/
bool DX3D12GameObject::Initialize()
{
    // �o�b�t�@�ݒ�
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

    // ���_�o�b�t�@�̍쐬
    if (FAILED(DX3D12::GetDX3D12Device()->CreateCommittedResource(
        &heap_properties , D3D12_HEAP_FLAG_NONE , &resource_desc ,
        D3D12_RESOURCE_STATE_GENERIC_READ , nullptr , IID_PPV_ARGS(&pm_vertexbuffer))))
    {
        return false;
    }

    // �萔�o�b�t�@�̍쐬
    if (FAILED(DX3D12::GetDX3D12Device()->CreateCommittedResource(
        &heap_properties , D3D12_HEAP_FLAG_NONE , &resource_desc ,
        D3D12_RESOURCE_STATE_GENERIC_READ , nullptr , IID_PPV_ARGS(&pm_constbuffer))))
    {
        return false;
    }

    // ���_�f�[�^�̏�������
    Vertex * buffer {};

    if (FAILED(pm_vertexbuffer->Map(0 , nullptr , (void **) &buffer)))
    {
        return false;
    }

    // �|�W�V����
    // ��O
    buffer [0].position = { -1.0f,1.0f,-1.0f };
    buffer [1].position = { 1.0f,1.0f,-1.0f };
    buffer [2].position = { -1.0f,-1.0f,-1.0f };
    buffer [3].position = { 1.0f,-1.0f,-1.0f };
    // ���
    buffer [4].position = { 1.0f,1.0f,1.0f };
    buffer [5].position = { -1.0f,1.0f,1.0f };
    buffer [6].position = { 1.0f,-1.0f,1.0f };
    buffer [7].position = { -1.0f,-1.0f,1.0f };
    // �E
    buffer [8].position = { 1.0f,1.0f,-1.0f };
    buffer [9].position = { 1.0f,1.0f,1.0f };
    buffer [10].position = { 1.0f,-1.0f,-1.0f };
    buffer [11].position = { 1.0f, -1.0f,1.0f };
    // ��
    buffer [12].position = { -1.0f,1.0f,1.0f };
    buffer [13].position = { -1.0f,1.0f,-1.0f };
    buffer [14].position = { -1.0f,-1.0f,1.0f };
    buffer [15].position = { -1.0f,-1.0f,-1.0f };
    // ��
    buffer [16].position = { -1.0f,1.0f,1.0f };
    buffer [17].position = { 1.0f,1.0f,1.0f };
    buffer [18].position = { -1.0f,1.0f,-1.0f };
    buffer [19].position = { 1.0f,1.0f,-1.0f };
    // ��
    buffer [20].position = { -1.0f,-1.0f,-1.0f };
    buffer [21].position = { 1.0f, -1.0f,-1.0f, };
    buffer [22].position = { -1.0f,-1.0f,1.0f };
    buffer [23].position = { 1.0f,-1.0f,1.0f };

    // �@���x�N�g��
    for (int i = 0; i < 24; i++)
    {
        buffer [i].normal = { 0.0f,0.0f,0.0f };
    }

    // �J���[
    // ��O
    buffer [0].color = { 1.0f,0.0f,0.0f,1.0f };
    buffer [1].color = { 0.0f,1.0f,0.0f,1.0f };
    buffer [2].color = { 0.0f,0.0f,1.0f,1.0f };
    buffer [3].color = { 1.0f,1.0f,1.0f,1.0f };
    // ���
    buffer [4].color = { 0.0f,1.0f,0.0f,1.0f };
    buffer [5].color = { 0.0f,0.0f,1.0f,1.0f };
    buffer [6].color = { 1.0f,1.0f,1.0f,1.0f };
    buffer [7].color = { 1.0f,0.0f,0.0f,1.0f };
    // �E
    buffer [8].color = { 0.0f,0.0f,1.0f,1.0f };
    buffer [9].color = { 1.0f,1.0f,1.0f,1.0f };
    buffer [10].color = { 1.0f,0.0f,0.0f,1.0f };
    buffer [11].color = { 0.0f,1.0f,0.0f,1.0f };
    // ��
    buffer [12].color = { 1.0f,1.0f,1.0f,1.0f };
    buffer [13].color = { 1.0f,0.0f,0.0f,1.0f };
    buffer [14].color = { 0.0f,1.0f,0.0f,1.0f };
    buffer [15].color = { 0.0f,0.0f,1.0f,1.0f };

    for (int i = 16; i < 24; i++)
    {
        buffer [i].color = { 1.0f,1.0f,1.0f,1.0f };
    }

    pm_vertexbuffer->Unmap(0 , nullptr);
    buffer = nullptr;

    m_eyepos = { 5.0f,10.0f,-5.0f };

    return true;
}

/**-------------------------------------------- 
/// \description �I�u�W�F�N�g�̍X�V
///
///
///  \return true or false
//--------------------------------------------*/
bool DX3D12GameObject::Update()
{
    Vertex * buffer {};

    if (FAILED(pm_vertexbuffer->Map(0 , nullptr , (void **) &buffer)))
    {
        return false;
    }

    for (int i = 0; i < 24; i++)
    {
        if (buffer [i].color.x > 0.0f && buffer [i].color.z <= 0.0f)
        {
            buffer [i].color.x -= 0.01f;
            buffer [i].color.y += 0.01f;
        }
        if (buffer [i].color.y > 0.0f && buffer [i].color.x <= 0.0f)
        {
            buffer [i].color.y -= 0.01f;
            buffer [i].color.z += 0.01f;
        }
        if (buffer [i].color.z > 0.0f && buffer [i].color.y <= 0.0f)
        {
            buffer [i].color.z -= 0.01f;
            buffer [i].color.x += 0.01f;
        }

        if (buffer [i].color.x == 1.0f && buffer [i].color.y == 1.0f && buffer [i].color.z == 1.0f)
        {
            buffer [i].color = { 0.5f,0.0f,0.5f,1.0f };
        }
    }

    pm_vertexbuffer->Unmap(0 , nullptr);
    buffer = nullptr;

    return true;
}

/**--------------------------------------------
/// \description �I�u�W�F�N�g�̕`��
///
///
///  \return true or false
//--------------------------------------------*/
bool DX3D12GameObject::Draw()
{
    // �J�����̐ݒ�
    XMMATRIX view = XMMatrixLookAtLH({ m_eyepos.x,m_eyepos.y,m_eyepos.z } , { 0.0f,0.0f,0.0f } , { 0.0f,1.0f,0.0f });
    XMMATRIX proj = XMMatrixPerspectiveFovLH({ XMConvertToRadians(60.0f) } , 2.0f , 1.0f , 20.0f);

    // �ϊ��s��
    XMFLOAT4X4 mat;
    XMStoreFloat4x4(&mat , XMMatrixTranspose(view * proj));


    XMFLOAT4X4 * buffer {};

    if (FAILED(pm_constbuffer->Map(0 , nullptr , (void **) &buffer)));
    {
        //return false;
    }

    // �s���萔�o�b�t�@�ɏ�������
    *buffer = mat;

    pm_constbuffer->Unmap(0 , nullptr);
    buffer = nullptr;

    D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view {};
    vertex_buffer_view.BufferLocation = pm_vertexbuffer->GetGPUVirtualAddress();
    vertex_buffer_view.SizeInBytes = sizeof(Vertex) * 20;
    vertex_buffer_view.StrideInBytes = sizeof(Vertex);

    // �萔�o�b�t�@���V�F�[�_�[�̃��W�X�^�ɃZ�b�g
    DX3D12::GetDX3D12CommandList()->SetGraphicsRootConstantBufferView(0 , pm_constbuffer->GetGPUVirtualAddress());

    // �C���f�b�N�X���g�p���Ȃ��ŕ`��
    DX3D12::GetDX3D12CommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    DX3D12::GetDX3D12CommandList()->IASetVertexBuffers(0 , 1 , &vertex_buffer_view);

    // �`��
    DX3D12::GetDX3D12CommandList()->DrawInstanced(24 , 1 , 0 , 0);


    return true;
}
