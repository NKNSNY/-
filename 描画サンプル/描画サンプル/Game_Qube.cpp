//*=============================================================================
 // \Filename : Game_Qube.cpp
 // \Description : �eAPI�œ����ݒ�ŕ`�悷��悤�ɐ݌v����
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "Game_Qube.h"

Qube::API Qube::sm_api;
QubeStatus Qube::sm_qube [10];

DirectX::XMFLOAT3 Qube::sm_eye;
DirectX::XMFLOAT3 Qube::sm_focus;

/**-------------------------------------------- 
/// \description �L���[�u�̐ݒ�
///
///
///  \return true
//--------------------------------------------*/
bool Qube::SetQubeStatus()
{
    for (int i = 0; i < 10; i++)
    {
        sm_qube [i].position = { -(float) i,0.0f,(float) i };
        sm_qube [i].color = { 1.0f,1.0f,1.0f,1.0f };
        sm_qube [i].size = { 0.3f,0.3f,0.3f };
    }

    sm_eye = { 0.0f,5.0f,-5.0f };
    sm_focus = { 0.0f,0.0f,0.0f };

    return true;
}

/**-------------------------------------------- 
/// \description ������
///
/// \param[in] hwnd
/// \param[in] api
///
///  \return true
//--------------------------------------------*/
bool Qube::Initialize(HWND hwnd , API api)
{
    SetQubeStatus();

    sm_api = api;

    switch (sm_api)
    {
        case Qube::API::DIRECTX11:
            DirectX3D::Initialize(hwnd , 1000 , 500);
            Game::Initialize(ARRAYSIZE(sm_qube) , sm_qube);
            break;
        case Qube::API::DIRECTX12:
            DX3D12::Initialize(hwnd , 1000 , 500 , ARRAYSIZE(sm_qube) , sm_qube);
            break;
        case Qube::API::OPENGL:
            Camera::SetCameraStatus(sm_eye , sm_focus , 3);
            OpenGL::Initialize(hwnd , ARRAYSIZE(sm_qube) , sm_qube);
            break;
        case Qube::API::VULKAN:
            break;
        case Qube::API::NONE:
            break;
    }

    return true;
}

/**-------------------------------------------- 
/// \description �X�V
///
///
///  \return true
//--------------------------------------------*/
bool Qube::Update()
{
    InputKey::Update();

    // �J�����̈ړ�
    if (InputKey::Press(0x44))
    {
        sm_eye.x += 0.1f;
        sm_focus.x += 0.1f;
    }
    if (InputKey::Press(0x41))
    {
        sm_eye.x -= 0.1f;
        sm_focus.x -= 0.1f;
    }
    if (InputKey::Press(0x57))
    {
        sm_eye.z += 0.1f;
        sm_focus.z += 0.1f;
    }
    if (InputKey::Press(0x53))
    {
        sm_eye.z -= 0.1f;
        sm_focus.z -= 0.1f;
    }

    // OpenGL�͌ʂ̈ړ��ʂ�ݒ�
    float gl_trans [3] = { 0.001f,0.0f,0.001f };

    switch (sm_api)
    {
        case Qube::API::DIRECTX11:
            Game::Update();
            Camera::SetCameraStatus(sm_eye , sm_focus , 1);
            break;
        case Qube::API::DIRECTX12:
            Camera::SetCameraStatus(sm_eye , sm_focus , 2);
            DX3D12::Draw();
            break;
        case Qube::API::OPENGL:
            OpenGL::Update();
            OpenGL::CameraMove(gl_trans , 0.0f);
            break;
        case Qube::API::VULKAN:
            break;
        case Qube::API::NONE:
            break;
    }

    return true;
}

/**-------------------------------------------- 
/// \description �`��
///
///
///  \return true
//--------------------------------------------*/
bool Qube::Draw()
{
    switch (sm_api)
    {
        case Qube::API::DIRECTX11:
            Game::Draw();
            break;
        case Qube::API::DIRECTX12:
            DX3D12::Draw();
            break;
        case Qube::API::OPENGL:
            OpenGL::Draw();
            break;
        case Qube::API::VULKAN:
            break;
        case Qube::API::NONE:
            break;
    }

    return true;
}

/**-------------------------------------------- 
/// \description ���
///
///
///  \return true
//--------------------------------------------*/
bool Qube::Finalize()
{
    switch (sm_api)
    {
        case Qube::API::DIRECTX11:
            Game::Finalize();
            break;
        case Qube::API::DIRECTX12:
            DX3D12::Finalize();
            break;
        case Qube::API::OPENGL:
            OpenGL::Finalize();
            break;
        case Qube::API::VULKAN:
            break;
        case Qube::API::NONE:
            break;
    }

    return true;
}
