//*=============================================================================
 // \Filename : Game_GameObject.cpp
 // \Description : ����͈�����\������
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Game_GameObject.h"
#include "System_Shader.h"

/**--------------------------------------------
/// \description ������
///
///
///  \return
//--------------------------------------------*/
bool GameObject::Initialize()
{
    float vp = 0.5f;

    DirectX::XMFLOAT3 vertexlist [] =
    {
      { -vp,  vp, -vp,  },  // ��O
        {  vp,  vp, -vp,  },
        {  vp, -vp, -vp,  },

        {  vp, -vp, -vp,  },
        { -vp, -vp, -vp, },
        { -vp,  vp, -vp,  },

        { vp,  vp,  vp,  },  // ��
        {  -vp,  vp,  vp,  },
        {  -vp, -vp,  vp,  },

        {  -vp, -vp,  vp,  },
        { vp, -vp,  vp,  },
        { vp,  vp,  vp,  },


        {  vp,  vp, -vp, },  // �E
        {  vp,  vp,  vp,  },
        {  vp, -vp,  vp,  },

        {  vp, -vp,  vp,  },
        {  vp, -vp, -vp,  },
        {  vp,  vp, -vp, },

        { -vp,  vp, vp,  },  // ��
        { -vp,  vp,  -vp, },
        { -vp, -vp,  -vp,  },

        { -vp, -vp,  -vp,  },
        { -vp, -vp, vp, },
        { -vp,  vp, vp,  },

        {  -vp,  vp, vp,  },  // ��
        {  vp,  vp,  vp, },
        { vp,  vp,  -vp,  },

        { vp,  vp,  -vp,  },
        { -vp,  vp, -vp, },
        {  -vp,  vp, vp,  },

          {  -vp,  -vp, -vp,  },  // ��
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
/// \description �X�V
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
/// \description �`��
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
/// \description ���
///
///
///  \return
//--------------------------------------------*/
bool GameObject::Finalize()
{
    return false;
}
