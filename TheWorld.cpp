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
    if(FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(writeFactory.GetAddressOf())))) {
        return false;
    }
    if(FAILED(writeFactory->CreateTextFormat(L"楷体",NULL
    ,DWRITE_FONT_WEIGHT_REGULAR,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL
    ,50.f,L"en-us",textFormat.GetAddressOf()
    ))) {
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
    // Create text layout rect
    RECT size = this->size();
    D2D1_RECT_F layoutRect = D2D1::RectF(
        static_cast<float>(size.left),
        static_cast<float>(size.top),
        static_cast<float>(size.right - size.left),
        static_cast<float>(size.bottom - size.top)
    );
    auto text = L"           李白\n\
青青园中葵，朝露待日晞。\n\
阳春布德泽，万物生光辉。\n\
常恐秋节至，焜黄华叶衰。\n\
百川东到海，何时复西归？\n\
少壮不努力，老大徒伤悲。\n";
    renderTarget->DrawText(text,lstrlenW(text),textFormat.Get(),layoutRect,mainBrush.Get());
    renderTarget->EndDraw();
}