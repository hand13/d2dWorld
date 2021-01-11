#include "TheWorld.h"
#include "image.h"
TheWorld::TheWorld(HWND hWnd):BaseWorld(hWnd) {
}
bool TheWorld::initResource() {
    if(!BaseWorld::initResource()) {
        return false;
    }
    if((FAILED(decodeImage(L"e:\\test.jpg",bitmapSource.GetAddressOf())))) {
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
    HRESULT hr = renderTarget->CreateBitmapFromWicBitmap(bitmapSource.Get(),bitmap.ReleaseAndGetAddressOf());
    if(SUCCEEDED(hr)) {
        renderTarget->DrawBitmap(bitmap.Get()
        ,D2D1::RectF(0,0,300,300)
        ,1.0,D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
        ,D2D1::RectF(0,0,300,300));
    }
    renderTarget->EndDraw();
}