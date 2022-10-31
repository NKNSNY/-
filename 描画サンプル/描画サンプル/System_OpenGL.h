//*=============================================================================
 // \Filename : System_OpenGL.h
 // \Description : OpenGL�֘A
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#pragma once

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include <windows.h>
#include	<gl/gl.h>
#include	<gl/glu.h>

#include "Game_QubeStatus.h"
#include "System_Input.h"

struct Position_GL
{
    float x;
    float y;
    float z;
};

struct Color_GL
{
    float r;
    float g;
    float b;
    float a;
};

struct Vertex_List_GL
{
    Position_GL postion;
    Color_GL color;
};

struct Vertex_GL
{
    Vertex_List_GL  vertexlist [256];
};

class OpenGL
{
public:
    //---------------------------------------------------------------------------
        // public�ȃ��\�b�h

    static bool SetCamera(float eye [3] , float focus [3]);

    static bool Initialize(HWND hwnd , int qube_num , QubeStatus qube []);
    static bool Update();
    static bool Draw();
    static bool Finalize();

    static bool CameraMove(float trans [3] , float angle);

    // public�ȕϐ�

    static HDC m_hdc;
    static Vertex_GL m_vertex [100];
    static Vertex_GL m_texture;

    static float sm_eye [3];
    static float sm_focus [3];

    //---------------------------------------------------------------------------
    ///<
    /// m_hdc            HDC
    /// m_vertex        ���_�f�[�^
    /// m_texture       �e�N�X�`���̒��_�f�[�^
    /// sm_eye            �J�����̈ʒu
    /// sm_focus          �J�����̌���
    /// <
};
