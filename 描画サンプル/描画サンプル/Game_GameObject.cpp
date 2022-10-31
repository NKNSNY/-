//*=============================================================================
 // \Filename : Game_GameObject.cpp
 // \Description : ����͈�����\������
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Game_GameObject.h"
#include "System_Shader.h"
#include "Game_Game.h"

/**-------------------------------------------- 
/// \description ������
///
/// \param[in] vertexlist
/// \param[in] position
///
///  \return true
//--------------------------------------------*/
bool GameObject::Initialize(DirectX::XMFLOAT3 vertexlist [] , DirectX::XMFLOAT3 position)
{
    for (int i = 0; i < 36; i++)
    {
        m_vertexlist [i] = vertexlist [i];
    }

    m_position = position;

    return true;
}

/**--------------------------------------------
/// \description �X�V
///
///
///  \return
//--------------------------------------------*/
bool GameObject::Update()
{
    //m_position.x += 0.1f;


    return false;
}

/**--------------------------------------------
/// \description �`��
///
///
///  \return
//--------------------------------------------*/
bool GameObject::Draw()
{
    Shader::Draw(m_vertexlist , m_position);

    return true;
}

/**--------------------------------------------
/// \description ���
///
///
///  \return
//--------------------------------------------*/
bool GameObject::Finalize()
{
    return true;
}
