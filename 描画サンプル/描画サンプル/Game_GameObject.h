//*=============================================================================
 // \Filename : Game_GameObject.h
 // \Description : 表示したいオブジェクトの型
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

#include "System_DirectX3D.h"

class GameObject
{
public:
    //---------------------------------------------------------------------------
        // publicなメソッド

    bool Initialize(DirectX::XMFLOAT3 vertexlist [] , DirectX::XMFLOAT3 position);
    bool Update();
    bool Draw();
    bool Finalize();

    // public な変数

    DirectX::XMFLOAT3 m_position;
    DirectX::XMFLOAT3 m_vertexlist [36];

    //---------------------------------------------------------------------------
    ///<
    /// m_position          移動量
    /// m_vertexlist        頂点データ
    /// <
};
