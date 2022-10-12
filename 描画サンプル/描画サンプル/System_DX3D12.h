//*=============================================================================
 // \Filename : System_DX3D12.h
 // \Description : ダイレクトX12を使用する
 // \Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#pragma once

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

class DX3D12
{
public:

    static bool Initialize(HWND hwnd , int screen_width , int screen_height);

};
