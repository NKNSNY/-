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

        { vp,  vp,  vp,  },  // 裏
        {  -vp,  vp,  vp,  },
        {  -vp, -vp,  vp,  },

        {  -vp, -vp,  vp,  },
        { vp, -vp,  vp,  },
        { vp,  vp,  vp,  },


        {  vp,  vp, -vp, },  // 右
        {  vp,  vp,  vp,  },
        {  vp, -vp,  vp,  },

        {  vp, -vp,  vp,  },
        {  vp, -vp, -vp,  },
        {  vp,  vp, -vp, },

        { -vp,  vp, vp,  },  // 左
        { -vp,  vp,  -vp, },
        { -vp, -vp,  -vp,  },

        { -vp, -vp,  -vp,  },
        { -vp, -vp, vp, },
        { -vp,  vp, vp,  },

        {  -vp,  vp, vp,  },  // 上
        {  vp,  vp,  vp, },
        { vp,  vp,  -vp,  },

        { vp,  vp,  -vp,  },
        { -vp,  vp, -vp, },
        {  -vp,  vp, vp,  },

          {  -vp,  -vp, -vp,  },  // 下
        {  vp,  -vp,  -vp, },
        { vp,  -vp,  vp,  },

        { vp,  -vp,  vp,  },
        { -vp,  -vp, vp, },
        {  -vp,  -vp, -vp,  },

    };


    for (int i = 0; i < 36; i++)
    {
        m_vertexlist [i] = vertexlist [i];
    }

    change_num = 0;
    y_change_flg = true;

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

    if (Shader::m_eyepostion.x <= 10.0f && change_num == 0)
    {
        Shader::m_eyepostion.x += 0.1f;
        if (Shader::m_eyepostion.x >= 10.0f)
        {
            Shader::m_eyepostion.x = 10.0f;
            change_num = 1;
        }
    }
    if (Shader::m_eyepostion.z <= 10.0f && change_num == 1)
    {
        Shader::m_eyepostion.z += 0.1f;
        if (Shader::m_eyepostion.z >= 10.0f)
        {
            Shader::m_eyepostion.z = 10.0f;
            change_num = 2;
        }
    }
    if (Shader::m_eyepostion.x >= -10.0f && change_num == 2)
    {
        Shader::m_eyepostion.x -= 0.1f;
        if (Shader::m_eyepostion.x <= -10.0f)
        {
            Shader::m_eyepostion.x = -10.0f;
            change_num = 3;
        }
    }
    if (Shader::m_eyepostion.z >= -10.0f && change_num == 3)
    {
        Shader::m_eyepostion.z -= 0.1f;
        if (Shader::m_eyepostion.z <= -10.0f)
        {
            Shader::m_eyepostion.z = -10.0f;
            change_num = 0;
        }
    }

    if (y_change_flg)
    {
        Shader::m_eyepostion.y += 0.1f;
        if (Shader::m_eyepostion.y >= 6.0f)
        {
            Shader::m_eyepostion.y = 6.0f;
            y_change_flg = false;
        }
    }
    else
    {
        Shader::m_eyepostion.y -= 0.1f;
        if (Shader::m_eyepostion.y <= -6.0f)
        {
            Shader::m_eyepostion.y = -6.0f;
            y_change_flg = true;
        }
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
