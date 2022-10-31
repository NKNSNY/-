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

    bool Initialize(DirectX::XMFLOAT3 vertexlist [] , DirectX::XMFLOAT3 position);
    bool Update();
    bool Draw();
    bool Finalize();

    // public �ȕϐ�

    DirectX::XMFLOAT3 m_position;
    DirectX::XMFLOAT3 m_vertexlist [36];

    //---------------------------------------------------------------------------
    ///<
    /// m_position          �ړ���
    /// m_vertexlist        ���_�f�[�^
    /// <
};
