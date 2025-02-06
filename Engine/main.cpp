#include <windows.h>
#include "include/Graphics.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY) PostQuitMessage(0);
    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"DX11Window";
    RegisterClass(&wc);

    HWND hWnd = CreateWindow(wc.lpszClassName, L"DirectX 11", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(hWnd, SW_SHOW);

    Graphics graphics(hWnd);

    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        graphics.Render();
    }

    return 0;
}
