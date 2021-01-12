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
    static int x = 0;
    static int y = 0;
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
        theWorld->onResize();
        break;
    case WM_PAINT:
        theWorld->render();
        break;
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        theWorld->touched(D2D1::Point2F(static_cast<float>(x),static_cast<float>(y)));
        break;
    default:
        break;
    }
    return DefWindowProc(hWnd,msg,wParam,lParam);
}