//*=============================================================================
 // \Filename : Game_Game.h
 // \Description : ゲームのメイン部分
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

#include "System_DirectX3D.h"
#include "Game_QubeStatus.h"

class Game
{
public:
    //---------------------------------------------------------------------------
        // publicなメソッド

    static bool Initialize(int qube_num , QubeStatus qube []);
    static bool Update();
    static bool Draw();
    static bool Finalize();

    //---------------------------------------------------------------------------

private:
    //---------------------------------------------------------------------------
        // privateな変数

    static int change_num;
    static bool y_change_flg;

    //---------------------------------------------------------------------------
    ///<
    /// change_num      カメラを動かす
    /// y_change_flg     カメラを動かす
    /// <
};
