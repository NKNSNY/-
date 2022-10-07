//*=============================================================================
 // \Filename : System_Shader.cpp
 // \Description : シェーダーの処理を書いていく
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "System_Shader.h"
#include "ps.h"
#include "vs.h"

ID3D11VertexShader * Shader::ps_m_vertexshader;
ID3D11PixelShader * Shader::ps_m_pixelshader;
ID3D11InputLayout * Shader::ps_m_inputlayout;
D3D11_VIEWPORT Shader::m_viewport;

DirectX::XMFLOAT3 Shader::m_eyepostion;

struct ConstBuffer
{
    DirectX::XMFLOAT4X4 world;
    DirectX::XMFLOAT4X4 view;
    DirectX::XMFLOAT4X4 proj;
};

/**--------------------------------------------
/// \description 初期化
///
///
///  \return
//--------------------------------------------*/
bool Shader::Initialize()
{
    // 頂点シェーダー作成
    if (FAILED(DirectX3D::GetDevice()->CreateVertexShader(&g_VSmain , sizeof(g_VSmain) , nullptr , &ps_m_vertexshader)))
    {
        return false;
    }

    // ピクセルシェーダー作成
    if (FAILED(DirectX3D::GetDevice()->CreatePixelShader(&g_PSmain , sizeof(g_PSmain) , nullptr , &ps_m_pixelshader)))
    {
        return false;
    }

    // 頂点レイアウト作成
    D3D11_INPUT_ELEMENT_DESC vertexdesc [] =
    {
        {"POSITION",    0,  DXGI_FORMAT_R32G32B32_FLOAT,    0,  0,  D3D11_INPUT_PER_VERTEX_DATA,    0},
    };

    //頂点レイアウト作成
    if (FAILED(DirectX3D::GetDevice()->CreateInputLayout(vertexdesc , ARRAYSIZE(vertexdesc) ,
        g_VSmain , sizeof(g_VSmain) , &ps_m_inputlayout)))
    {
        return false;
    }

    // ビューポートの設定
    m_viewport.TopLeftX = 0;
    m_viewport.TopLeftY = 0;
    m_viewport.Width = 1000;
    m_viewport.Height = 500;
    m_viewport.MinDepth = 0.0f;
    m_viewport.MaxDepth = 1.0f;

    m_eyepostion = { 2.0f,2.0f,-2.0f };

    return true;
}



/**--------------------------------------------
/// \description 描画系
///
/// \param[in] vertexlist
///
///  \return
//--------------------------------------------*/
bool Shader::Draw(DirectX::XMFLOAT3 vertexlist [])
{
    //DirectX::XMFLOAT3 vertexpos [3] = { {0.0f,0.0f,0.0f},{1.0f,-1.0f,0.0f},{-1.0f,-1.0f,0.0f} };
    //DirectX::XMFLOAT3 vertexpos [4] = { {-0.5f,-0.5f,0.0f},{-0.5f,0.5f,0.0f},{0.5f,-0.5f,0.0f},{0.5f,0.5f,0.0f} };
    DirectX::XMFLOAT3 vertexpos [36];

    for (int i = 0; i < 36; i++)
    {
        vertexpos [i] = vertexlist [i];
    }

    // 頂点バッファ作成
    D3D11_BUFFER_DESC buffer_desc;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.ByteWidth = sizeof(vertexpos) * 3;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.MiscFlags = 0;
    buffer_desc.StructureByteStride = 0;
    buffer_desc.Usage = D3D11_USAGE_DEFAULT;

    // バッファの初期値作成
    D3D11_SUBRESOURCE_DATA initdata;
    initdata.pSysMem = vertexpos;
    initdata.SysMemPitch = 0;
    initdata.SysMemSlicePitch = 0;

    ID3D11Buffer * vb;

    if (FAILED(DirectX3D::GetDevice()->CreateBuffer(&buffer_desc , &initdata , &vb)))
    {
        return false;
    }

    // 定数バッファの作成
    D3D11_BUFFER_DESC constbuffer_desc;
    constbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constbuffer_desc.ByteWidth = sizeof(ConstBuffer);
    constbuffer_desc.CPUAccessFlags = 0;
    constbuffer_desc.MiscFlags = 0;
    constbuffer_desc.StructureByteStride = 0;
    constbuffer_desc.Usage = D3D11_USAGE_DEFAULT;

    ID3D11Buffer * cb;

    if (FAILED(DirectX3D::GetDevice()->CreateBuffer(&constbuffer_desc , nullptr , &cb)))
    {
        return false;
    }


    DirectX::XMMATRIX worldmatrix = DirectX::XMMatrixTranslation(0.0f , 0.0f , 0.0f);

    DirectX::XMVECTOR eye = { m_eyepostion.x,m_eyepostion.y,m_eyepostion.z,0.0f };
    DirectX::XMVECTOR focus = { 0.0f,0.0f,0.0f,0.0f };
    DirectX::XMVECTOR up { 0.0f,1.0f,0.0f,0.0f };
    DirectX::XMMATRIX viewmatrix = DirectX::XMMatrixLookAtLH(eye , focus , up);
    //DirectX::XMMATRIX viewmatrix = DirectX::XMMatrixIdentity();

    constexpr float fov = DirectX::XMConvertToRadians(45.0f);
    float aspect = 1000 / 500;
    float nearz = 0.1f;
    float farz = 100.0f;
    DirectX::XMMATRIX projmatrix = DirectX::XMMatrixPerspectiveFovLH(fov , aspect , nearz , farz);

    ConstBuffer const_buffer;

    DirectX::XMStoreFloat4x4(&const_buffer.world , DirectX::XMMatrixTranspose(worldmatrix));
    DirectX::XMStoreFloat4x4(&const_buffer.view , DirectX::XMMatrixTranspose(viewmatrix));
    DirectX::XMStoreFloat4x4(&const_buffer.proj , DirectX::XMMatrixTranspose(projmatrix));

    DirectX3D::GetDeviceContext()->UpdateSubresource(cb , 0 , nullptr , &const_buffer , 0 , 0);


    UINT stride = sizeof(DirectX::XMFLOAT3);
    UINT offset = 0;

    DirectX3D::GetDeviceContext()->IASetVertexBuffers(0 , 1 , &vb , &stride , &offset);

    DirectX3D::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 頂点シェーダーをセット
    DirectX3D::GetDeviceContext()->VSSetShader(ps_m_vertexshader , 0 , 0);

    // ピクセルシェーダーをセット
    DirectX3D::GetDeviceContext()->PSSetShader(ps_m_pixelshader , 0 , 0);

    // 頂点レイアウトをセット
    DirectX3D::GetDeviceContext()->IASetInputLayout(ps_m_inputlayout);

    // 定数バッファをセット
    DirectX3D::GetDeviceContext()->VSSetConstantBuffers(0 , 1 , &cb);

    // ビューポートをセット
    DirectX3D::GetDeviceContext()->RSSetViewports(1 , &m_viewport);

    DirectX3D::GetDeviceContext()->Draw(36, 0);

    return true;
}

/**-------------------------------------------- 
/// \description 解放
///
///
///  \return
//--------------------------------------------*/
bool Shader::Finalize()
{
    ps_m_vertexshader->Release();
    ps_m_pixelshader->Release();
    ps_m_inputlayout->Release();

    return true;;
}

