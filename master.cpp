#include <windows.h>
#include "TheWorld.h"
TheWorld * theWorld;
LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hi,HINSTANCE p,LPSTR command,int tmp) {
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
    while((hr = GetMessage(&msg,hWnd,0,0)) != 0) {
        if(hr == -1) {
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
  return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam) {
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
        theWorld->onResize();
        return 0;
    case WM_PAINT:
        theWorld->render();
        return 0;
    default:
        break;
    }
    return DefWindowProc(hWnd,msg,wParam,lParam);
}