#pragma once

#include "System_DirectX3D.h"

class GameObject
{
public:
    //---------------------------------------------------------------------------
        // publicÇ»ÉÅÉ\ÉbÉh

    bool Initialize();
    bool Update();
    bool Draw();
    bool Finalize();

    DirectX::XMFLOAT3 m_vertexlist [];

    //---------------------------------------------------------------------------

};
