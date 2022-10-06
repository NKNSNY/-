#include "Game_GameObject.h"
#include "System_Shader.h"

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

        {  vp,  vp, -vp,  },  // ��
        {  vp,  vp,  vp, },
        { -vp,  vp,  vp,  },

        { -vp,  vp,  vp,  },
        { -vp,  vp, -vp, },
        {  vp,  vp, -vp,  },

    };


    for (int i = 0; i < 30; i++)
    {
        m_vertexlist [i] = vertexlist [i];
    }

    return true;
}

bool GameObject::Update()
{
    return false;
}

bool GameObject::Draw()
{
    Shader::Draw(m_vertexlist);

    return true;
}

bool GameObject::Finalize()
{
    return false;
}
