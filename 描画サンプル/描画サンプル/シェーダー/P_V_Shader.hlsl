//*=============================================================================
 // \Filename : P_V_Shader.hlsl
 // \Description : 頂点とピクセルのシェーダーを兼ねる
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

cbuffer cbTansMatrix : register(b0)
{
    float4x4 WVP;
};

struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float4 color : COLOR;
};

PS_INPUT VSmain(VS_INPUT input)
{
    PS_INPUT output;

    float4 POS = float4(input.position , 1.0f);
    float4 NOR = float4(input.normal , 1.0f);

    output.position = mul(POS , WVP);
    output.normal = mul(NOR , WVP);
    output.color = input.color;

    return output;
}

float4 PSmain(PS_INPUT input) : SV_TARGET
{
    return input.color;
}
