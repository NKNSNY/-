//*=============================================================================
 // \Filename : System_Input.h
 // \Description : ���͎���
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

#include <Windows.h>

class InputKey
{
public:
//---------------------------------------------------------------------------
    // public�ȃ��\�b�h    

    static bool Update();
    static bool Press(int vkey);
    static bool Trigger(int vkey);
    static bool Release(int vkey);

//---------------------------------------------------------------------------

private:
//---------------------------------------------------------------------------
    // private�ȕϐ�

    static BYTE m_after_keystate [256];
    static BYTE m_before_keystate [256];

//---------------------------------------------------------------------------
    ///<
    /// m_after_keystate            ���݂̃L�[�̏��
    /// m_before_keystate           �O��̃L�[�̏��
    /// <

};
