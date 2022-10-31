//*=============================================================================
 // \Filename : Game_Camera.cpp
 // \Description : カメラ関連
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "Game_Camera.h"

/**-------------------------------------------- 
/// \description カメラを各APIでセット
///
/// \param[in] eye
/// \param[in] focus
/// \param[in] api
///
///  \return true
//--------------------------------------------*/
bool Camera::SetCameraStatus(DirectX::XMFLOAT3 eye , DirectX::XMFLOAT3 focus , int api)
{
    switch (api)
    {
        case 1:
            Shader::SetCamera(eye , focus);
            break;
        case 2:
            DX3D12::SetCamera(eye , focus);
            break;
        case 3:
            float gl_eye [3] = { eye.x,eye.y,-eye.z };
            float gl_focus [3] = { focus.x,focus.y,focus.z };
            OpenGL::SetCamera(gl_eye , gl_focus);
            break;
    }

    return true;
}
