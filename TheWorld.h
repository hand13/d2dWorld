#pragma once
#include "BaseWorld.h"
class TheWorld:public BaseWorld {
    private:
    ComPtr<IWICBitmapSource> bitmapSource;
    ComPtr<ID2D1Bitmap> bitmap;
    ComPtr<IDWriteTextFormat> textFormat;
    ComPtr<IDWriteFactory> writeFactory;
    HRESULT getTextSize(const WCHAR * text,IDWriteTextFormat * pTextFormat,D2D1_SIZE_F & size);
    protected:
    public:
    TheWorld(HWND hWnd);
    virtual bool initResource();
    virtual void render();
    virtual bool resize();
};