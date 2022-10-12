//*=============================================================================
 // \Filename : DX12_VS.hlsl
 // \Description : DX12用頂点シェーダー
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

struct VS_INPUT
{
    float3 position : POSITION;
    float4 color : COLOR;
};

cbuffer cbTansMatrix : register(b0)
{
    // world , view , projection
    float4x4 WVP;
};

VS_INPUT VSmain(VS_INPUT input)
{
    VS_INPUT output;

    float4 pos = float4(input.position , 1.0f);

    output.position = mul(pos , WVP);
    output.color = input.color;

    return output;
}

