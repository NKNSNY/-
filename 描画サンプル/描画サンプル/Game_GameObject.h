#pragma once

#include "System_DirectX3D.h"

class GameObject
{
public:
    //---------------------------------------------------------------------------
        // public�ȃ��\�b�h

    bool Initialize();
    bool Update();
    bool Draw();
    bool Finalize();

    DirectX::XMFLOAT3 m_vertexlist [];

    //---------------------------------------------------------------------------

};
