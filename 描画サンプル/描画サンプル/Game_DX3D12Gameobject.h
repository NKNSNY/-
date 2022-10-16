//*=============================================================================
 // \Filename : Game_DX3D12Gameobject.h
 // \Description : オブジェクトの設定
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

#include "System_DX3D12.h"

class DX3D12GameObject
{
public:
//---------------------------------------------------------------------------
    // publicなメソッド

    // 初期化
    bool Initialize();
    // 更新
    bool Update();
    // 描画
    bool Draw();

//---------------------------------------------------------------------------

private:
//---------------------------------------------------------------------------
    // privateなメソッド

    ID3D12Resource * pm_vertexbuffer;
    ID3D12Resource * pm_constbuffer;

    DirectX::XMFLOAT3 m_eyepos;

//---------------------------------------------------------------------------
    ///<
    /// pm_vertexbuffer         頂点バッファー
    /// pm_constbuffer          定数バッファー
    /// m_eyepos                   カメラの位置
    /// <
};
