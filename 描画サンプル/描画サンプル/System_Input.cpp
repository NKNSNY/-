//*=============================================================================
 // \Filename : System_Input.cpp
 // \Description : インプットの中身
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "System_Input.h"

BYTE InputKey::m_after_keystate [256];
BYTE InputKey::m_before_keystate [256];

/**-------------------------------------------- 
/// \description 入力の更新
///
///
///  \return GetKeyboardState
//--------------------------------------------*/
bool InputKey::Update()
{
    // 前のキーの状態を保存
    memcpy_s(m_before_keystate , sizeof(m_before_keystate) , m_after_keystate , sizeof(m_after_keystate));

    return GetKeyboardState(m_after_keystate);
}

/**-------------------------------------------- 
/// \description 長押し
///
/// \param[in] vkey
///
///  \return key
//--------------------------------------------*/
bool InputKey::Press(int vkey)
{
    return m_after_keystate [vkey] & 0x80;
}

/**-------------------------------------------- 
/// \description 一回押し
///
/// \param[in] vkey
///
///  \return key
//--------------------------------------------*/
bool InputKey::Trigger(int vkey)
{
    return (m_after_keystate [vkey] & 0x80) & (~(m_before_keystate [vkey] & 0x80));
}

/**-------------------------------------------- 
/// \description 離す
///
/// \param[in] vkey
///
///  \return true or false
//--------------------------------------------*/
bool InputKey::Release(int vkey)
{
    if ((m_after_keystate [vkey] & 0x80) == 0 && (m_before_keystate [vkey] & 0x80) != 0)
    {
        return true;
    }
    return false;
}
