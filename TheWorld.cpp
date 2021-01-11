#include "TheWorld.h"
#include "image.h"
TheWorld::TheWorld(HWND hWnd):BaseWorld(hWnd) {
}
bool TheWorld::initResource() {
    if((FAILED(decodeImage(L"e:\\white_clear.png",bitmapSource.GetAddressOf())))) {
        return false;
    }
    if(!BaseWorld::initResource()) {
        return false;
    }
    return true;
}
bool TheWorld::resize() {
    if(!BaseWorld::resize()) {
        return false;
    }
    HRESULT hr = renderTarget->CreateBitmapFromWicBitmap(bitmapSource.Get(),bitmap.ReleaseAndGetAddressOf());
    if(FAILED(hr)) {
        return false;
    }
    return true;
}
void TheWorld::render() {
    renderTarget->BeginDraw();
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
    D2D1_RECT_F rect{200,100,400,400};
    renderTarget->FillRectangle(rect,mainBrush.Get());
    WICPixelFormatGUID format;
    bitmapSource->GetPixelFormat(&format);
    auto width = bitmap->GetSize().width;
    auto height = bitmap->GetSize().height;
    renderTarget->DrawBitmap(bitmap.Get()
    ,D2D1::RectF(0,0,width,height)
    ,1.0,D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
    ,D2D1::RectF(0,0,width,height));
    renderTarget->EndDraw();
}