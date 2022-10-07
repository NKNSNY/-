//*=============================================================================
 // \Filename : Game_GameObject.h
 // \Description : �\���������I�u�W�F�N�g�̌^
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

#include "System_DirectX3D.h"

class GameObject
{
public:
    //---------------------------------------------------------------------------
        // public�ȃ��\�b�h

    bool Initialize();
    bool Update();
    bool Draw();
    bool Finalize();

    // public �ȕϐ�

    DirectX::XMFLOAT3 m_vertexlist [];

    //---------------------------------------------------------------------------
    ///<
    /// m_vertexrist ���_���W���������
    /// <
};
