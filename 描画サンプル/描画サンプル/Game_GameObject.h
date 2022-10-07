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

    DirectX::XMFLOAT3 m_vertexlist [36];
    int change_num;
    bool y_change_flg;

    //---------------------------------------------------------------------------
    ///<
    /// m_vertexrist ���_���W���������
    /// change_num    eye�̏ꏊ��ς���t���O
    /// <
};
