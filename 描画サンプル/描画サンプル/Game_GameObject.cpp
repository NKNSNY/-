//*=============================================================================
 // \Filename : Game_GameObject.cpp
 // \Description : 今回は一つだけ表示する
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Game_GameObject.h"
#include "System_Shader.h"
#include "Game_Game.h"

/**-------------------------------------------- 
/// \description 初期化
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
/// \description 更新
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
/// \description 描画
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
/// \description 解放
///
///
///  \return
//--------------------------------------------*/
bool GameObject::Finalize()
{
    return true;
}
