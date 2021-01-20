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
void BaseWorld::processEvent(UINT msg,WPARAM wParam,LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return;
    case WM_SIZE:
        onResize();
        return;
    default:
        break;
    }
    Event event = fromWindowsEvent(msg,wParam,lParam);
    processEvent(event);
}
Event BaseWorld::fromWindowsEvent(UINT msg,WPARAM wParam,LPARAM lParam){
    Event event;
    ZeroMemory(&event,sizeof(event));
    event.eventType = WE_NONE;
    switch(msg) {
    case WM_LBUTTONDOWN:
        event.eventType = WE_MOUSE_CLICKED;
        event.x = LOWORD(lParam);
        event.y = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        event.eventType = WE_MOUSE_RELEASED;
        event.x = LOWORD(lParam);
        event.y = HIWORD(lParam);
        break;
    default:
        break;
    }
    return event;
}

void BaseWorld::processEvent(Event event) {
    if(event.eventType == WE_NONE) {
        return;
    }
    auto & v = eventProcessors[event.eventType];
    for(EventProcesser & processor:v) {
        processor(this,event);
    }
}
void BaseWorld::addEventProcessor(WorldEventType type,EventProcesser eventProcessor) {
    auto & v = eventProcessors[type];
    v.push_back(eventProcessor);
}