//*=============================================================================
 // \Filename : Game_QubeStatus.h
 // \Description : キューブのステータスの定義
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#pragma once

#include <DirectXMath.h>

struct QubeStatus
{
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT4 color;
    DirectX::XMFLOAT3 size;
};