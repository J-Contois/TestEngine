#include <windows.h>
#include "Engine/Graphics.h"

// Fonction de gestion des événements Windows
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// Fonction principale
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"DX11Engine";
    RegisterClass(&wc);

    HWND hWnd = CreateWindow(wc.lpszClassName, L"DirectX 11 Engine",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hWnd, nCmdShow);

    // Initialisation de DirectX 11
    Graphics graphics;
    if (!graphics.Init(hWnd)) {
        return -1;
    }

    // Boucle principale
    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        graphics.Render();  // Rendu de la scène
    }

    return 0;
}