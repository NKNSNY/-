//*=============================================================================
 // \Filename : Game_Game.cpp
 // \Description : ゲーム、システムの処理は全てここに来る
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
/// \description 初期化
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
            // 四角形
            { -vp.x,  vp.y, -vp.z,  },  // 手前
              {  vp.x,  vp.y, -vp.z,  },
              {  vp.x, -vp.y, -vp.z,  },

              {    vp.x,  -vp.y,  -vp.z,  },
              {  -vp.x,  -vp.y,  -vp.z, },
              {  -vp.x,    vp.y,  -vp.z,  },

              {    vp.x,    vp.y,    vp.z,  },  // 裏
              {  -vp.x,    vp.y,    vp.z,  },
              {  -vp.x,  -vp.y,    vp.z,  },

              {  -vp.x,  -vp.y,    vp.z,  },
              {    vp.x,  -vp.y,    vp.z,  },
              {    vp.x,    vp.y,    vp.z,  },

              {    vp.x,    vp.y,  -vp.z, },  // 右
              {    vp.x,    vp.y,    vp.z,  },
              {    vp.x,  -vp.y,    vp.z,  },

              {    vp.x,  -vp.y,    vp.z,  },
              {    vp.x,  -vp.y,  -vp.z,  },
              {    vp.x,    vp.y,  -vp.z, },

              {  -vp.x,    vp.y,    vp.z,  },  // 左
              {  -vp.x,    vp.y,  -vp.z, },
              {  -vp.x,  -vp.y,  -vp.z,  },

              {  -vp.x,  -vp.y,  -vp.z,  },
              {  -vp.x,  -vp.y,    vp.z, },
              {  -vp.x,    vp.y,    vp.z,  },

              {  -vp.x,    vp.y,    vp.z,  },  // 上
              {    vp.x,    vp.y,    vp.z, },
              {    vp.x,    vp.y,  -vp.z,  },

              {    vp.x,    vp.y,  -vp.z,  },
              {  -vp.x,    vp.y,  -vp.z, },
              {  -vp.x,    vp.y,    vp.z,  },

              {  -vp.x,  -vp.y,  -vp.z,  },  // 下
              {    vp.x,  -vp.y,  -vp.z, },
              {    vp.x,  -vp.y,    vp.z,  },

              {    vp.x,  -vp.y,    vp.z,  },
              {  -vp.x,  -vp.y,    vp.z, },
              {  -vp.x,  -vp.y,  -vp.z,  },

              // 三角形
              //{   vp.x - vp.x,        vp.y,             vp.z - vp.z},     // 手前
              //{   vp.x,                -vp.y,           -vp.z},
              //{ -vp.x,                -vp.y,           -vp.z},

              //{   vp.x - vp.x,        vp.y,             vp.z - vp.z},    // 後ろ
              //{ -vp.x,                -vp.y,             vp.z},
              //{   vp.x,                -vp.y,             vp.z},

              //{   vp.x - vp.x,         vp.y,             vp.z - vp.z},  // 右
              //{   vp.x,                -vp.y,             vp.z},
              //{   vp.x,                -vp.y,           -vp.z},

              //{   vp.x - vp.x,        vp.y,              vp.z - vp.z},  // 左
              //{ -vp.x,               -vp.y,             -vp.z},
              //{ -vp.x,               -vp.y,               vp.z},

              //{  -vp.x,  -vp.y,  -vp.z,  },  // 下
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
/// \description 更新
///
///
///  \return
//--------------------------------------------*/
bool Game::Update()
{


    return true;
}

/**--------------------------------------------
/// \description 描画
///
///
///  \return
//--------------------------------------------*/
bool Game::Draw()
{
    // 画面クリア
    float color [4] = { 0.0f,0.0f,0.0f,1.0f };
    DirectX3D::GetDeviceContext()->ClearRenderTargetView(DirectX3D::GetRenderTarget() , color);

    // 深度バッファクリア
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
/// \description 解放
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
