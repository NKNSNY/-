//*=============================================================================
 // \Filename : Game_DX3D12Gameobject.h
 // \Description : �I�u�W�F�N�g�̐ݒ�
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

#include "System_DX3D12.h"
#include "Game_QubeStatus.h"

class DX3D12GameObject
{
public:
    //---------------------------------------------------------------------------
        // public�ȃ��\�b�h

    // ������
    bool Initialize(QubeStatus qube);
    // �X�V
    bool Update();
    // �`��
    bool Draw(DirectX::XMFLOAT3 eye , DirectX::XMFLOAT3 focus);

    //---------------------------------------------------------------------------

private:
    //---------------------------------------------------------------------------
        // private�ȃ��\�b�h

    ID3D12Resource * pm_vertexbuffer;
    ID3D12Resource * pm_constbuffer;

    //---------------------------------------------------------------------------
        ///<
        /// pm_vertexbuffer         ���_�o�b�t�@�[
        /// pm_constbuffer          �萔�o�b�t�@�[
        /// <
};
