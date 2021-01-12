#include "TheWorld.h"
#include "image.h"
TheWorld::TheWorld(HWND hWnd):BaseWorld(hWnd) {
}
bool TheWorld::initResource() {
    worldMap = std::make_unique<Map>(20,20,D2D1::RectF(50.f,100.f,550.f,550.f));
    if((FAILED(decodeImage(L"e:\\white_clear.png",bitmapSource.GetAddressOf())))) {
        return false;
    }
    if(!BaseWorld::initResource()) {
        return false;
    }
    if(FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(writeFactory.GetAddressOf())))) {
        return false;
    }
    if(FAILED(writeFactory->CreateTextFormat(L"Arial",NULL
    ,DWRITE_FONT_WEIGHT_REGULAR,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL
    ,60.f,L"en-us",textFormat.GetAddressOf()
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
    WICPixelFormatGUID format;
    bitmapSource->GetPixelFormat(&format);
    auto width = bitmap->GetSize().width;
    auto height = bitmap->GetSize().height;
    RECT size = this->size();
    renderTarget->DrawBitmap(bitmap.Get()
    ,D2D1::RectF(size.left,size.top,size.right,size.bottom)
    ,1.0,D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
    ,D2D1::RectF(0,0,width,height));
    // Create text layout rect
    auto text = L"link start";
    D2D1_SIZE_F textSize = {0.0,0.0};
    getTextSize(text,textFormat.Get(),textSize);
    int x = (size.left + size.right)/2 - textSize.width/2;
    int y = size.top + 10.0;
    D2D1_RECT_F layoutRect = D2D1::RectF(
        static_cast<float>(x),
        static_cast<float>(y),
        static_cast<float>(x + textSize.width),
        static_cast<float>(y + textSize.height)
    );
    renderTarget->DrawText(text,lstrlenW(text),textFormat.Get(),layoutRect,mainBrush.Get());
    worldMap->draw(renderTarget.Get(),mainBrush.Get());
    renderTarget->EndDraw();
}
HRESULT TheWorld::getTextSize(const WCHAR * text,IDWriteTextFormat * pTextFormat,D2D1_SIZE_F & size) {
    HRESULT hr= S_OK;
    IDWriteTextLayout * pLayout = NULL;
    hr = writeFactory->CreateTextLayout(text,wcslen(text),pTextFormat,1000.f,1000.f,&pLayout);
    if(SUCCEEDED(hr)) {
        DWRITE_TEXT_METRICS textMetrics;
        hr = pLayout->GetMetrics(&textMetrics);
        size = D2D1::SizeF(textMetrics.widthIncludingTrailingWhitespace,textMetrics.height);
    }
    if(pLayout != NULL) {
        pLayout->Release();
    }
    return hr;
}
bool TheWorld::touched(D2D1_POINT_2F & point) {
    if (worldMap->touched(point)) {
        render();
    }
    return true;
}
