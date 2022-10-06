//*=============================================================================
 // \Filename : Game_Game.h
 // \Description : ゲームのメイン部分
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

class Game
{
//---------------------------------------------------------------------------
    // publicなメソッド

public:
    static bool Initialize();
    static bool Update();
    static bool Draw();
    static bool Finalize();

//---------------------------------------------------------------------------

};
