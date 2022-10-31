//*=============================================================================
 // \Filename : Game_Game.cpp
 // \Description : �Q�[���A�V�X�e���̏����͑S�Ă����ɗ���
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Game_Game.h"
#include "Game_GameObject.h"
#include "System_Shader.h"

int Game::change_num;
bool Game::y_change_flg;

GameObject g_gameobject [100];

int g_d3d_qube_num;

bool g_flg;

/**--------------------------------------------
/// \description ������
///
///
///  \return
//--------------------------------------------*/
bool Game::Initialize(int qube_num , QubeStatus qube [])
{
    g_d3d_qube_num = qube_num;

    for (int i = 0; i < g_d3d_qube_num; i++)
    {

        DirectX::XMFLOAT3 vp = qube [i].size;

        DirectX::XMFLOAT3 vertexlist [] =
        {
            // �l�p�`
            { -vp.x,  vp.y, -vp.z,  },  // ��O
              {  vp.x,  vp.y, -vp.z,  },
              {  vp.x, -vp.y, -vp.z,  },

              {    vp.x,  -vp.y,  -vp.z,  },
              {  -vp.x,  -vp.y,  -vp.z, },
              {  -vp.x,    vp.y,  -vp.z,  },

              {    vp.x,    vp.y,    vp.z,  },  // ��
              {  -vp.x,    vp.y,    vp.z,  },
              {  -vp.x,  -vp.y,    vp.z,  },

              {  -vp.x,  -vp.y,    vp.z,  },
              {    vp.x,  -vp.y,    vp.z,  },
              {    vp.x,    vp.y,    vp.z,  },

              {    vp.x,    vp.y,  -vp.z, },  // �E
              {    vp.x,    vp.y,    vp.z,  },
              {    vp.x,  -vp.y,    vp.z,  },

              {    vp.x,  -vp.y,    vp.z,  },
              {    vp.x,  -vp.y,  -vp.z,  },
              {    vp.x,    vp.y,  -vp.z, },

              {  -vp.x,    vp.y,    vp.z,  },  // ��
              {  -vp.x,    vp.y,  -vp.z, },
              {  -vp.x,  -vp.y,  -vp.z,  },

              {  -vp.x,  -vp.y,  -vp.z,  },
              {  -vp.x,  -vp.y,    vp.z, },
              {  -vp.x,    vp.y,    vp.z,  },

              {  -vp.x,    vp.y,    vp.z,  },  // ��
              {    vp.x,    vp.y,    vp.z, },
              {    vp.x,    vp.y,  -vp.z,  },

              {    vp.x,    vp.y,  -vp.z,  },
              {  -vp.x,    vp.y,  -vp.z, },
              {  -vp.x,    vp.y,    vp.z,  },

              {  -vp.x,  -vp.y,  -vp.z,  },  // ��
              {    vp.x,  -vp.y,  -vp.z, },
              {    vp.x,  -vp.y,    vp.z,  },

              {    vp.x,  -vp.y,    vp.z,  },
              {  -vp.x,  -vp.y,    vp.z, },
              {  -vp.x,  -vp.y,  -vp.z,  },

              // �O�p�`
              //{   vp.x - vp.x,        vp.y,             vp.z - vp.z},     // ��O
              //{   vp.x,                -vp.y,           -vp.z},
              //{ -vp.x,                -vp.y,           -vp.z},

              //{   vp.x - vp.x,        vp.y,             vp.z - vp.z},    // ���
              //{ -vp.x,                -vp.y,             vp.z},
              //{   vp.x,                -vp.y,             vp.z},

              //{   vp.x - vp.x,         vp.y,             vp.z - vp.z},  // �E
              //{   vp.x,                -vp.y,             vp.z},
              //{   vp.x,                -vp.y,           -vp.z},

              //{   vp.x - vp.x,        vp.y,              vp.z - vp.z},  // ��
              //{ -vp.x,               -vp.y,             -vp.z},
              //{ -vp.x,               -vp.y,               vp.z},

              //{  -vp.x,  -vp.y,  -vp.z,  },  // ��
              //{    vp.x,  -vp.y,  -vp.z, },
              //{    vp.x,  -vp.y,    vp.z,  },

              //{    vp.x,  -vp.y,    vp.z,  },
              //{  -vp.x,  -vp.y,    vp.z, },
              //{  -vp.x,  -vp.y,  -vp.z,  },

        };

        g_gameobject [i].Initialize(vertexlist , qube [i].position);

    }

    Shader::Initialize();

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
bool Game::Update()
{


    return true;
}

/**--------------------------------------------
/// \description �`��
///
///
///  \return
//--------------------------------------------*/
bool Game::Draw()
{
    // ��ʃN���A
    float color [4] = { 0.0f,0.0f,0.0f,1.0f };
    DirectX3D::GetDeviceContext()->ClearRenderTargetView(DirectX3D::GetRenderTarget() , color);

    // �[�x�o�b�t�@�N���A
    DirectX3D::GetDeviceContext()->ClearDepthStencilView(DirectX3D::GetDepthStenvilView() ,
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , 1.0f , 0);

    for (int i = 0; i < g_d3d_qube_num; i++)
    {
        g_gameobject [i].Draw();
    }

    DirectX3D::GetSwapChain()->Present(1 , 0);

    return true;
}

/**--------------------------------------------
/// \description ���
///
///
///  \return
//--------------------------------------------*/
bool Game::Finalize()
{
    for (int i = 0; i < ARRAYSIZE(g_gameobject); i++)
    {
        g_gameobject [i].Finalize();
    }

    Shader::Finalize();

    return true;
}
