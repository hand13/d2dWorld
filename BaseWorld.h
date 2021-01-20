#pragma once
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wrl/client.h>
#include <map>
#include <vector>
using Microsoft::WRL::ComPtr;

enum WorldEventType {
    WE_NONE,
    WE_MOUSE_CLICKED,
    WE_MOUSE_RELEASED,
    WE_MOUSE_WHEEL,
    WE_MOUSE_MOVED
};
struct Event {
    WorldEventType eventType;
    int x;
    int y;
    int key;
};
class BaseWorld {
    protected:
    ComPtr<ID2D1Factory> d2dFactory;
    ComPtr<ID2D1HwndRenderTarget> renderTarget;
    ComPtr<ID2D1SolidColorBrush> mainBrush;
    HWND hWnd;
    virtual void processEvent(Event event);
    virtual bool resize();
    public:
    BaseWorld(HWND hWnd);
    virtual bool initResource();
    virtual void render() = 0;
    RECT size();
    void processEvent(UINT msg,WPARAM wParam,LPARAM lParam);
    private:
    Event fromWindowsEvent(UINT msg,WPARAM wParam,LPARAM lParam);
    virtual void onResize();
};