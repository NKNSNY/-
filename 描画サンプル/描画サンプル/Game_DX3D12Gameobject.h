//*=============================================================================
 // \Filename : Game_DX3D12Gameobject.h
 // \Description : オブジェクトの設定
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

#include "System_DX3D12.h"
#include "Game_QubeStatus.h"

class DX3D12GameObject
{
public:
    //---------------------------------------------------------------------------
        // publicなメソッド

    // 初期化
    bool Initialize(QubeStatus qube);
    // 更新
    bool Update();
    // 描画
    bool Draw(DirectX::XMFLOAT3 eye , DirectX::XMFLOAT3 focus);

    //---------------------------------------------------------------------------

private:
    //---------------------------------------------------------------------------
        // privateなメソッド

    ID3D12Resource * pm_vertexbuffer;
    ID3D12Resource * pm_constbuffer;

    //---------------------------------------------------------------------------
        ///<
        /// pm_vertexbuffer         頂点バッファー
        /// pm_constbuffer          定数バッファー
        /// <
};
