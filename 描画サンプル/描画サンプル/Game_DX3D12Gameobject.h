//*=============================================================================
 // \Filename : Game_DX3D12Gameobject.h
 // \Description : �I�u�W�F�N�g�̐ݒ�
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

#include "System_DX3D12.h"

class DX3D12GameObject
{
public:
//---------------------------------------------------------------------------
    // public�ȃ��\�b�h

    // ������
    bool Initialize();
    // �X�V
    bool Update();
    // �`��
    bool Draw();

//---------------------------------------------------------------------------

private:
//---------------------------------------------------------------------------
    // private�ȃ��\�b�h

    ID3D12Resource * pm_vertexbuffer;
    ID3D12Resource * pm_constbuffer;

    DirectX::XMFLOAT3 m_eyepos;

//---------------------------------------------------------------------------
    ///<
    /// pm_vertexbuffer         ���_�o�b�t�@�[
    /// pm_constbuffer          �萔�o�b�t�@�[
    /// m_eyepos                   �J�����̈ʒu
    /// <
};
