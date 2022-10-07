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

    bool Initialize();
    bool Update();
    bool Draw();
    bool Finalize();

    // public な変数

    DirectX::XMFLOAT3 m_vertexlist [36];
    int change_num;
    bool y_change_flg;

    //---------------------------------------------------------------------------
    ///<
    /// m_vertexrist 頂点座標を入れるもの
    /// change_num    eyeの場所を変えるフラグ
    /// <
};
