//*=============================================================================
 // \Filename : Game_Game.cpp
 // \Description : ゲーム、システムの処理は全てここに来る
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Game_Game.h"
#include "System_DirectX3D.h"
#include "Game_GameObject.h"
#include "System_Shader.h"

GameObject gameobject;

/**-------------------------------------------- 
/// \description 初期化
///
///
///  \return
//--------------------------------------------*/
bool Game::Initialize()
{
    gameobject.Initialize();

    Shader::Initialize();

    return false;
}

/**-------------------------------------------- 
/// \description 更新
///
///
///  \return
//--------------------------------------------*/
bool Game::Update()
{
    float color [4] = { 0.0f,0.0f,0.0f,1.0f };
    DirectX3D::GetDeviceContext()->ClearRenderTargetView(DirectX3D::GetRenderTarget() , color);

    gameobject.Update();

    return false;
}

/**-------------------------------------------- 
/// \description 描画
///
///
///  \return
//--------------------------------------------*/
bool Game::Draw()
{
    gameobject.Draw();

    DirectX3D::GetSwapChain()->Present(1 , 0);

    return false;
}

/**-------------------------------------------- 
/// \description 解放
///
///
///  \return
//--------------------------------------------*/
bool Game::Finalize()
{
    return false;
}
