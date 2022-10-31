//*=============================================================================
 // \Filename : System_Input.cpp
 // \Description : �C���v�b�g�̒��g
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "System_Input.h"

BYTE InputKey::m_after_keystate [256];
BYTE InputKey::m_before_keystate [256];

/**-------------------------------------------- 
/// \description ���͂̍X�V
///
///
///  \return GetKeyboardState
//--------------------------------------------*/
bool InputKey::Update()
{
    // �O�̃L�[�̏�Ԃ�ۑ�
    memcpy_s(m_before_keystate , sizeof(m_before_keystate) , m_after_keystate , sizeof(m_after_keystate));

    return GetKeyboardState(m_after_keystate);
}

/**-------------------------------------------- 
/// \description ������
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
/// \description ��񉟂�
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
/// \description ����
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
