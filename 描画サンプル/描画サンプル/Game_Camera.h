//*=============================================================================
 // \Filename : Game_Camera.h
 // \Description : カメラを設定
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#pragma once

#include "System_Shader.h"
#include "System_DX3D12.h"
#include "System_OpenGL.h"

#include <directxmath.h>

class Camera
{
public:
    //---------------------------------------------------------------------------
        // publicなメソッド

    static bool SetCameraStatus(DirectX::XMFLOAT3 eye , DirectX::XMFLOAT3 focus , int api);

    //---------------------------------------------------------------------------
};
