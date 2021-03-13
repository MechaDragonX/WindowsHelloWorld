#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// A resource file header that links the CPP to the RC using shared definitions
#include "resource.h"

// Global Variables
// Current Instance Handle
HINSTANCE hInst;
// Title Bar Text
WCHAR szTitle[MAX_PATH];
// Main Window Class Name
WCHAR szWindowClass[MAX_PATH];

// Forward Declarations of functions (in logical order)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// Main Entry Point
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                        _In_opt_ HINSTANCE hPrevIsntance,
                        _In_ LPWSTR lpCmdLine,
                        _In_ int nCmdShow)
{
    // Load global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_PATH);
    LoadStringW(hInstance, IDC_WINDOWSHELLOWORLD, szWindowClass, MAX_PATH);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSHELLOWORLD));

    WNDCLASSEXW wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_WINDOWSHELLOWORLD));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WINDOWSHELLOWORLD);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    if(RegisterClassExW(&wcex) == 0)
        return FALSE;
    
    hInst = hInstance;
    
    HWND hWnd = CreateWindow(szWindowClass,
                                szTitle,
                                WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT,
                                0,
                                CW_USEDEFAULT,
                                0,
                                nullptr,
                                nullptr,
                                hInstance,
                                nullptr);
    if(!hWnd)
        return FALSE;
    
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Keep pumpin' messages
    MSG msg;
    while(GetMessage(&msg, nullptr, 0, 0))
    {
        if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Use wParam of the last successfully process message as return code
    return (int)msg.wParam;
}

/*
    WndProc(HWND, UINT, WPARAM, LPARAM)

    Process window messages for the main window

    WM_COMMAND  Process the app meny
    WM_PAINT    Paint the main window
    WM_DESTROY  Post a quit message, then return
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse out menu selections
            switch(wmId)
            {
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;            
            RECT rect;
            HDC hdc = BeginPaint(hWnd, &ps);

            GetClientRect(hWnd, &rect);
            DrawText(hdc, L"Hello, Windows!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            EndPaint(hWnd, &ps);

            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

// About Message Handler for About Dialog Box
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}
