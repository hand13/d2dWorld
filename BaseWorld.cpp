#include "BaseWorld.h"
BaseWorld::BaseWorld(HWND hWnd):hWnd(hWnd){
}
bool BaseWorld::initResource() {
    HRESULT hr;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,d2dFactory.GetAddressOf());
    if(FAILED(hr)) {
        return false;
    }
    if(!resize()) {
        return false;
    }
    return true;
}
bool BaseWorld::resize() {
    RECT rc = size();
    D2D1_SIZE_U s = D2D1::SizeU(rc.right - rc.left,rc.bottom -  rc.top);
    HRESULT hr = d2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties()
    ,D2D1::HwndRenderTargetProperties(hWnd,s),renderTarget.ReleaseAndGetAddressOf());
    if(FAILED(hr)) {
        return false;
    }
    hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray),mainBrush.ReleaseAndGetAddressOf());
    if(FAILED(hr)) {
        return false;
    }
    return true;
}
void BaseWorld::onResize() {
    resize();
}
RECT BaseWorld::size() {
    RECT tmp;
    GetClientRect(hWnd,&tmp);
    return tmp;
}