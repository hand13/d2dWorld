#include <windows.h>
#include "TheWorld.h"
#include "tool.h"
TheWorld * theWorld;
LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hi,HINSTANCE p,LPSTR command,int tmp) {
    Time time;
    CoInitialize(NULL);
    WNDCLASSEX wndClass = {sizeof(WNDCLASSEX),CS_CLASSDC,WndProc,0L,0L,hi,NULL,NULL,NULL,NULL,TEXT("live2dworld"),NULL};
    RegisterClassEx(&wndClass);
    HWND hWnd = CreateWindowEx(0,TEXT("live2dworld"),TEXT("live2d"),WS_OVERLAPPEDWINDOW
  ,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,wndClass.hInstance,NULL);
    theWorld = new TheWorld(hWnd);
    if(!theWorld->initResource()) {
        return -1;
    }
    ::ShowWindow(hWnd,tmp);
    ::UpdateWindow(hWnd);
    MSG msg;
    ZeroMemory(&msg,sizeof(msg));
    HRESULT hr;
    time.init();
    long expectedDelta = 1000/60;
    while(msg.message != WM_QUIT) {
        if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        continue;
        }
        auto delta = expectedDelta - time.getDelta();
        if(delta > 0) {
            Sleep(delta);
        }
        theWorld->render();
    }
  return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam) {
    if (theWorld != nullptr) {
        theWorld->processEvent(msg, wParam, lParam);
    }
    return DefWindowProc(hWnd,msg,wParam,lParam);
}