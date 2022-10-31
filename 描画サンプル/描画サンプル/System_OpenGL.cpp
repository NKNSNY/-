//*=============================================================================
 // \Filename : System_OpenGL.cpp
 // \Description : glu32を使用させていただきます
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_OpenGL.h"

#include <string.h>
#include <time.h>

HDC OpenGL::m_hdc;
Vertex_GL OpenGL::m_vertex [100];
Vertex_GL OpenGL::m_texture;

float OpenGL::sm_eye [3];
float OpenGL::sm_focus [3];

int g_gl_qube_num;

/**-------------------------------------------- 
/// \description カメラをセット
///
/// \param[in] eye
/// \param[in] focus
///
///  \return true
//--------------------------------------------*/
bool OpenGL::SetCamera(float eye [3] , float focus [3])
{
    for (int i = 0; i < 3; i++)
    {
        sm_eye [i] = eye [i];
        sm_focus [i] = focus [i];
    }

    return true;
}

/**--------------------------------------------
/// \description 初期化
///
/// \param[in] hwnd
///
///  \return true
//--------------------------------------------*/
bool OpenGL::Initialize(HWND hwnd , int qube_num , QubeStatus qube [])
{
    m_hdc = GetDC(hwnd);

    // OpenGL初期化の設定
    PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR),
                                               1,
                                               PFD_DRAW_TO_WINDOW |
                                               PFD_SUPPORT_OPENGL |
                                               PFD_DOUBLEBUFFER,
                                               PFD_TYPE_RGBA,
                                               24,
                                               0, 0, 0, 0, 0, 0,
                                               0,
                                               0,
                                               0,
                                               0, 0, 0, 0,
                                               32,
                                               0,
                                               0,
                                               PFD_MAIN_PLANE,
                                               0,
                                               0, 0, 0 };

    HGLRC hrc;
    int pixel_format;

    pixel_format = ChoosePixelFormat(m_hdc , &pfd);
    SetPixelFormat(m_hdc , pixel_format , &pfd);

    hrc = wglCreateContext(m_hdc);
    wglMakeCurrent(m_hdc , hrc);

    glPixelStorei(GL_UNPACK_ALIGNMENT , 1);
    glClearColor(0.0f , 0.0f , 0.0f , 0.4f);
    glDepthRange(0.0 , 1.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glViewport(0 , 0 , 1920 / 2 , 1080 / 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-10.0 / 200.0 , 10.0 / 200.0 , -5.5 / 200.0 , 5.5 / 200.0 , 0.1 , 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt((GLdouble) sm_eye [0] , (GLdouble) sm_eye [1] , (GLdouble) sm_eye [2] ,
        (GLdouble) sm_focus [0] , (GLdouble) sm_focus [1] , (GLdouble) sm_focus [2] , 0.0 , 1.0 , 0.0);

    glDisable(GL_STENCIL_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    Vertex_List_GL gl_xmfloat [100];

    for (int i = 0; i < qube_num; i++)
    {
        gl_xmfloat [i].postion.x = qube [i].position.x;
        gl_xmfloat [i].postion.y = qube [i].position.y;
        gl_xmfloat [i].postion.z = -qube [i].position.z;

        gl_xmfloat [i].color.r = qube [i].color.x;
        gl_xmfloat [i].color.g = qube [i].color.y;
        gl_xmfloat [i].color.b = qube [i].color.z;
        gl_xmfloat [i].color.a = qube [i].color.w;
    }

    for (int i = 0; i < qube_num; i++)
    {

        Position_GL vp;
        vp.x = qube [i].size.x;
        vp.y = qube [i].size.y;
        vp.z = qube [i].size.z;

        // 手前
        m_vertex [i].vertexlist [0].postion = { vp.x ,     vp.y ,     vp.z };
        m_vertex [i].vertexlist [1].postion = { vp.x ,   -vp.y ,     vp.z };
        m_vertex [i].vertexlist [2].postion = { -vp.x ,   -vp.y ,     vp.z };
        m_vertex [i].vertexlist [3].postion = { -vp.x ,     vp.y ,     vp.z };
        // 後ろ    
        m_vertex [i].vertexlist [4].postion = { -vp.x ,     vp.y ,   -vp.z };
        m_vertex [i].vertexlist [5].postion = { -vp.x ,   -vp.y ,   -vp.z };
        m_vertex [i].vertexlist [6].postion = { vp.x ,   -vp.y ,   -vp.z };
        m_vertex [i].vertexlist [7].postion = { vp.x ,     vp.y ,   -vp.z };
        // 右       
        m_vertex [i].vertexlist [8].postion = { vp.x ,     vp.y ,   -vp.z };
        m_vertex [i].vertexlist [9].postion = { vp.x ,   -vp.y ,   -vp.z };
        m_vertex [i].vertexlist [10].postion = { vp.x ,  -vp.y ,     vp.z };
        m_vertex [i].vertexlist [11].postion = { vp.x ,    vp.y ,     vp.z };
        // 左       
        m_vertex [i].vertexlist [12].postion = { -vp.x ,    vp.y ,     vp.z };
        m_vertex [i].vertexlist [13].postion = { -vp.x ,  -vp.y ,     vp.z };
        m_vertex [i].vertexlist [14].postion = { -vp.x ,  -vp.y ,   -vp.z };
        m_vertex [i].vertexlist [15].postion = { -vp.x ,    vp.y ,   -vp.z };
        // 上       
        m_vertex [i].vertexlist [16].postion = { vp.x ,    vp.y ,   -vp.z };
        m_vertex [i].vertexlist [17].postion = { vp.x ,    vp.y ,     vp.z };
        m_vertex [i].vertexlist [18].postion = { -vp.x ,    vp.y ,     vp.z };
        m_vertex [i].vertexlist [19].postion = { -vp.x ,    vp.y ,   -vp.z };
        // 下       
        m_vertex [i].vertexlist [20].postion = { vp.x ,  -vp.y ,   -vp.z };
        m_vertex [i].vertexlist [21].postion = { vp.x ,  -vp.y ,     vp.z };
        m_vertex [i].vertexlist [22].postion = { -vp.x ,  -vp.y ,     vp.z };
        m_vertex [i].vertexlist [23].postion = { -vp.x ,  -vp.y ,   -vp.z };

        // カラー
        for (int j = 0; j < 24; j++)
        {
            m_vertex [i].vertexlist [j].postion.x += gl_xmfloat [i].postion.x;
            m_vertex [i].vertexlist [j].postion.y += gl_xmfloat [i].postion.y;
            m_vertex [i].vertexlist [j].postion.z += gl_xmfloat [i].postion.z;
            m_vertex [i].vertexlist [j].color = gl_xmfloat [i].color;
        }

    }

    // HAL

    m_texture.vertexlist [0].postion = { -0.7f,0.7f,-8.9f };
    m_texture.vertexlist [1].postion = { -0.7f,-0.7f,-8.9f };
    m_texture.vertexlist [2].postion = { -0.8f,-0.7f,-8.9f };
    m_texture.vertexlist [3].postion = { -0.8f,0.7f,-8.9f };

    m_texture.vertexlist [4].postion = { -0.5f,0.1f,-8.9f };
    m_texture.vertexlist [5].postion = { -0.5f,-0.1f,-8.9f };
    m_texture.vertexlist [6].postion = { -0.7f,-0.1f,-8.9f };
    m_texture.vertexlist [7].postion = { -0.7f,0.1f,-8.9f };

    m_texture.vertexlist [8].postion = { -0.4f,0.7f,-8.9f };
    m_texture.vertexlist [9].postion = { -0.4f,-0.7f,-8.9f };
    m_texture.vertexlist [10].postion = { -0.5f,-0.7f,-8.9f };
    m_texture.vertexlist [11].postion = { -0.5f,0.7f,-8.9f };

    m_texture.vertexlist [12].postion = { 0.05f,0.5f,-8.9f };
    m_texture.vertexlist [13].postion = { -0.1f,-0.7f,-8.9f };
    m_texture.vertexlist [14].postion = { -0.2f,-0.5f,-8.9f };
    m_texture.vertexlist [15].postion = { -0.05f,0.7f,-8.9f };

    m_texture.vertexlist [16].postion = { 0.05f,0.7f,-8.9f };
    m_texture.vertexlist [17].postion = { 0.2f,-0.5f,-8.9f };
    m_texture.vertexlist [18].postion = { 0.1f,-0.7f,-8.9f };
    m_texture.vertexlist [19].postion = { -0.05f,0.5f,-8.9f };

    m_texture.vertexlist [20].postion = { 0.1f,-0.2f,-8.9f };
    m_texture.vertexlist [21].postion = { 0.1f,-0.4f,-8.9f };
    m_texture.vertexlist [22].postion = { -0.1f,-0.4f,-8.9f };
    m_texture.vertexlist [23].postion = { -0.1f,-0.2f,-8.9f };

    m_texture.vertexlist [24].postion = { 0.5f,0.7f,-8.9f };
    m_texture.vertexlist [25].postion = { 0.5f,-0.7f,-8.9f };
    m_texture.vertexlist [26].postion = { 0.4f,-0.7f,-8.9f };
    m_texture.vertexlist [27].postion = { 0.4f,0.7f,-8.9f };

    m_texture.vertexlist [28].postion = { 0.8f,-0.5f,-8.9f };
    m_texture.vertexlist [29].postion = { 0.8f,-0.7f,-8.9f };
    m_texture.vertexlist [30].postion = { 0.5f,-0.7f,-8.9f };
    m_texture.vertexlist [31].postion = { 0.5f,-0.5f,-8.9f };

    srand((unsigned int) time(NULL));

    g_gl_qube_num = qube_num;

    return true;
}

/**--------------------------------------------
/// \description 更新
///
///
///  \return true
//--------------------------------------------*/
bool OpenGL::Update()
{

    return true;
}

/**--------------------------------------------
/// \description 描画
///
///
///  \return true
//--------------------------------------------*/
bool OpenGL::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // カラー、頂点

    for (int k = 0; k < g_gl_qube_num; k++)
    {

        for (int i = 0; i < 24; i += 4)
        {
            glBegin(GL_TRIANGLE_FAN);

            for (int j = 0; j < 4; j++)
            {
                glColor4f(m_vertex [k].vertexlist [i + j].color.r ,
                    m_vertex [k].vertexlist [i + j].color.g ,
                    m_vertex [k].vertexlist [i + j].color.b ,
                    m_vertex [k].vertexlist [i + j].color.a);
                glVertex3f(m_vertex [k].vertexlist [i + j].postion.x ,
                    m_vertex [k].vertexlist [i + j].postion.y ,
                    m_vertex [k].vertexlist [i + j].postion.z);
            }

            glEnd();
        }

    }

    for (int i = 0; i < 32; i += 4)
    {
        glBegin(GL_TRIANGLE_FAN);

        m_texture.vertexlist [i].color.r = (rand() % 100) / 100.0f;
        m_texture.vertexlist [i].color.g = (rand() % 100) / 100.0f;
        m_texture.vertexlist [i].color.b = (rand() % 100) / 100.0f;

        for (int j = 0; j < 4; j++)
        {
            glColor3f(m_texture.vertexlist [i + j].color.r ,
                m_texture.vertexlist [i + j].color.g ,
                m_texture.vertexlist [i + j].color.b);
            glVertex3f(m_texture.vertexlist [i + j].postion.x ,
                m_texture.vertexlist [i + j].postion.y ,
                m_texture.vertexlist [i + j].postion.z);
        }

        glEnd();
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_TEXTURE_2D);

    glFlush();
    SwapBuffers(m_hdc);

    return true;
}

/**--------------------------------------------
/// \description 解放
///
///
///  \return true
//--------------------------------------------*/
bool OpenGL::Finalize()
{
    return true;
}

/**-------------------------------------------- 
/// \description カメラの移動
///
/// \param[in] trans
/// \param[in] angle
///
///  \return true
//--------------------------------------------*/
bool OpenGL::CameraMove(float trans [3] , float angle)
{
    if (InputKey::Press(0x44))
    {
        glTranslatef(-(GLfloat) trans [0] , 0.0 , 0.0);
    }
    if (InputKey::Press(0x41))
    {
        glTranslatef((GLfloat) trans [0] , 0.0 , 0.0);
    }
    if (InputKey::Press(0x57))
    {
        glTranslatef(0.0 , 0.0 , (GLfloat) trans [2]);
    }
    if (InputKey::Press(0x53))
    {
        glTranslatef(0.0 , 0.0 , -(GLfloat) trans [2]);
    }

    return true;
}
