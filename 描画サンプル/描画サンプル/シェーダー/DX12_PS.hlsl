//*=============================================================================
 // \Filename : DX12_PS.hlsl
 // \Description : DX12用ピクセルシェーダー
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

float4 PSmain(PS_INPUT input) : SV_TARGET
{
    return input.color;
}
