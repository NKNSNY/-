//*=============================================================================
 // \Filename : Game_Game.cpp
 // \Description : �Q�[���A�V�X�e���̏����͑S�Ă����ɗ���
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Game_Game.h"
#include "System_DirectX3D.h"
#include "Game_GameObject.h"
#include "System_Shader.h"

GameObject gameobject;

/**-------------------------------------------- 
/// \description ������
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
/// \description �X�V
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
/// \description �`��
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
/// \description ���
///
///
///  \return
//--------------------------------------------*/
bool Game::Finalize()
{
    return false;
}
