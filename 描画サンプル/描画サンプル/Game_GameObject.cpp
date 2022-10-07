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

        { -vp,  vp,  vp,  },  // ��
        {  vp,  vp,  vp,  },
        {  vp, -vp,  vp,  },

        {  vp, -vp,  vp,  },
        { -vp, -vp,  vp,  },
        { -vp,  vp,  vp,  },

        {  vp,  vp, -vp, },  // �E
        {  vp,  vp,  vp,  },
        {  vp, -vp,  vp,  },

        {  vp, -vp,  vp,  },
        {  vp, -vp, -vp,  },
        {  vp,  vp, -vp, },

        { -vp,  vp, -vp,  },  // ��
        { -vp,  vp,  vp, },
        { -vp, -vp,  vp,  },

        { -vp, -vp,  vp,  },
        { -vp, -vp, -vp, },
        { -vp,  vp, -vp,  },

        {  -vp,  vp, vp,  },  // ��
        {  vp,  vp,  vp, },
        { vp,  vp,  -vp,  },

        { vp,  vp,  -vp,  },
        { -vp,  vp, -vp, },
        {  -vp,  vp, vp,  },

          {  -vp,  -vp, vp,  },  // ��
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
/// \description �X�V
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
