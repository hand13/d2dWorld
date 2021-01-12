#pragma once
#include "BaseWorld.h"
class TheWorld:public BaseWorld {
    private:
    ComPtr<IWICBitmapSource> bitmapSource;
    ComPtr<ID2D1Bitmap> bitmap;
    ComPtr<IDWriteTextFormat> textFormat;
    ComPtr<IDWriteFactory> writeFactory;
    protected:
    public:
    TheWorld(HWND hWnd);
    virtual bool initResource();
    virtual void render();
    virtual bool resize();
};