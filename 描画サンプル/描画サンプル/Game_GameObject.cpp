//*=============================================================================
 // \Filename : Game_GameObject.cpp
 // \Description : 今回は一つだけ表示する
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Game_GameObject.h"
#include "System_Shader.h"

/**--------------------------------------------
/// \description 初期化
///
///
///  \return
//--------------------------------------------*/
bool GameObject::Initialize()
{
    float vp = 0.5f;

    DirectX::XMFLOAT3 vertexlist [] =
    {
      { -vp,  vp, -vp,  },  // 手前
        {  vp,  vp, -vp,  },
        {  vp, -vp, -vp,  },

        {  vp, -vp, -vp,  },
        { -vp, -vp, -vp, },
        { -vp,  vp, -vp,  },

        { -vp,  vp,  vp,  },  // 裏
        {  vp,  vp,  vp,  },
        {  vp, -vp,  vp,  },

        {  vp, -vp,  vp,  },
        { -vp, -vp,  vp,  },
        { -vp,  vp,  vp,  },

        {  vp,  vp, -vp, },  // 右
        {  vp,  vp,  vp,  },
        {  vp, -vp,  vp,  },

        {  vp, -vp,  vp,  },
        {  vp, -vp, -vp,  },
        {  vp,  vp, -vp, },

        { -vp,  vp, -vp,  },  // 左
        { -vp,  vp,  vp, },
        { -vp, -vp,  vp,  },

        { -vp, -vp,  vp,  },
        { -vp, -vp, -vp, },
        { -vp,  vp, -vp,  },

        {  -vp,  vp, vp,  },  // 上
        {  vp,  vp,  vp, },
        { vp,  vp,  -vp,  },

        { vp,  vp,  -vp,  },
        { -vp,  vp, -vp, },
        {  -vp,  vp, vp,  },

          {  -vp,  -vp, vp,  },  // 下
        {  vp,  -vp,  vp, },
        { vp,  -vp,  -vp,  },

        { vp,  -vp,  -vp,  },
        { -vp,  -vp, -vp, },
        {  -vp,  -vp, vp,  },

    };


    for (int i = 0; i < 36; i++)
    {
        m_vertexlist [i] = vertexlist [i];
    }

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
 
    for (int i = 0; i < 6; i++)
    {
        m_vertexlist [i].z -= 0.001f;
        m_vertexlist [i + 6].z += 0.001f;
        m_vertexlist [i + 12].x += 0.001f;
        m_vertexlist [i + 18].x -= 0.001f;
        m_vertexlist [i + 24].y += 0.001f;
        m_vertexlist [i + 30].y -= 0.001f;
    }
 
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
    Shader::Draw(m_vertexlist);

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
    return false;
}
