//*=============================================================================
 // \Filename : System_Input.h
 // \Description : 入力周り
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

#include <Windows.h>

class InputKey
{
public:
//---------------------------------------------------------------------------
    // publicなメソッド    

    static bool Update();
    static bool Press(int vkey);
    static bool Trigger(int vkey);
    static bool Release(int vkey);

//---------------------------------------------------------------------------

private:
//---------------------------------------------------------------------------
    // privateな変数

    static BYTE m_after_keystate [256];
    static BYTE m_before_keystate [256];

//---------------------------------------------------------------------------
    ///<
    /// m_after_keystate            現在のキーの状態
    /// m_before_keystate           前回のキーの状態
    /// <

};
