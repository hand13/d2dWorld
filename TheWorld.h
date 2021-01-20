#pragma once
#include "BaseWorld.h"
#include <memory>
#include "Map.h"
class TheWorld:public BaseWorld {
    private:
    std::unique_ptr<Map> worldMap;
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
    bool touched(D2D1_POINT_2F & point);
    bool click(const Event& event);
    static bool clickProcessor(BaseWorld * data,const Event & event);
};