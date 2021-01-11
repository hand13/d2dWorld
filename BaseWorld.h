#pragma once
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;
class BaseWorld {
    protected:
    ComPtr<ID2D1Factory> d2dFactory;
    ComPtr<ID2D1HwndRenderTarget> renderTarget;
    ComPtr<ID2D1SolidColorBrush> mainBrush;
    HWND hWnd;
    public:
    BaseWorld(HWND hWnd);
    virtual bool initResource();
    virtual void onResize();
    virtual void render() = 0;
    RECT size();
    bool resize();
};