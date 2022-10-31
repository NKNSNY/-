//*=============================================================================
 // \Filename : Game_Qube.h
 // \Description : API���܂Ƃ߂Ďg�����߂̃N���X
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#pragma once

#include "System_DirectX3D.h"
#include "Game_Game.h"
#include "System_DX3D12.h"
#include "System_OpenGL.h"
#include "Game_QubeStatus.h"
#include "Game_Camera.h"
#include "System_Input.h"

class Qube
{
public:
    //---------------------------------------------------------------------------
        // public�ȃ��\�b�h

    enum class API
    {
        DIRECTX11 ,
        DIRECTX12 ,
        OPENGL ,
        VULKAN ,
        NONE
    };

    static bool SetQubeStatus();

    static bool Initialize(HWND hwnd , API api);
    static bool Update();
    static bool Draw();
    static bool Finalize();

    //---------------------------------------------------------------------------

private:
    //---------------------------------------------------------------------------
        // private�ȕϐ�

    static API sm_api;
    static QubeStatus sm_qube [10];

    static DirectX::XMFLOAT3 sm_eye;
    static DirectX::XMFLOAT3 sm_focus;

    //---------------------------------------------------------------------------
    ///<
    /// am_api              API�̎��
    /// sm_qube            �`�悷��L���[�u
    /// sm_eye              �J�����̈ʒu
    /// sm_focus            �J�����̌���

};
