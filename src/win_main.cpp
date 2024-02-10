#include "framework.h"
#include "main.hpp"
#include "resource.h"
#include <glad/glad.h>
#include <iostream>

#define MAX_LOADSTRING 100

struct WGL_WindowData {
  HDC hDC;
};

static HGLRC g_hRC;
static WGL_WindowData g_MainWindow;
static int g_Width;
static int g_Height;

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

void CirclesRegisterClass(HINSTANCE hInstance, WNDCLASSEXW &wcex);
// BOOL InitInstance(HINSTANCE, int);
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData *data);
void CleanupDeviceWGL(HWND hWnd, WGL_WindowData *data);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine,
// int nCmdShow) {
//   return wWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
// }

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow) {

  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // More setup if required

  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_CIRCLESPLUSPLUS, szWindowClass, MAX_LOADSTRING);
  WNDCLASSEXW wcex;
  CirclesRegisterClass(hInstance, wcex);

  RawMain rawMain;

  HWND hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, 0, rawMain.windowControl.width,
                            rawMain.windowControl.height, nullptr, nullptr,
                            hInstance, nullptr);

  if (!CreateDeviceWGL(hwnd, &g_MainWindow)) {
    CleanupDeviceWGL(hwnd, &g_MainWindow);
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wcex.lpszClassName, wcex.hInstance);
    return 1;
  };

  HMENU hMenu = ::GetMenu(hwnd);
  // RemoveMenu(hMenu, UINT uPosition, UINT uFlags);
  ::SetMenu(hwnd, NULL);
  wglMakeCurrent(g_MainWindow.hDC, g_hRC);

  if (!gladLoadGL()) {
    throw "Failed to initialize GLAD";
  }

  ::ShowWindow(hwnd, SW_SHOWDEFAULT);
  ::UpdateWindow(hwnd);

  rawMain.fillMembers();

  HACCEL hAccelTable =
      LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CIRCLESPLUSPLUS));

  bool done = false;
  while (!done) {

    MSG msg;

    while (::PeekMessageA(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
      if (msg.message == WM_QUIT)
        done = true;
    }

    if (done)
      break;
    rawMain.pushClock();
    // handle input here maybe? , or use proc?

    rawMain.windowControl.clearBuffer();
    rawMain.renderWindow();
    ::SwapBuffers(g_MainWindow.hDC);
  }

  CleanupDeviceWGL(hwnd, &g_MainWindow);
  wglDeleteContext(g_hRC);
  ::DestroyWindow(hwnd);
  ::UnregisterClassW(wcex.lpszClassName, wcex.hInstance);

  return 0;
}

void CirclesRegisterClass(HINSTANCE hInstance, WNDCLASSEXW &wcex) {

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CIRCLESPLUSPLUS));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CIRCLESPLUSPLUS);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  RegisterClassExW(&wcex);
}

// HWND InitInstance(HINSTANCE hInstance, int nCmdShow) {
//   hInst = hInstance;
//
//   return CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance,
//       nullptr);
//
//   if (!hWnd) {
//     std::cout << "no hWnd?! " << *szTitle << std::endl;
//     return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
// }

bool CreateDeviceWGL(HWND hWnd, WGL_WindowData *data) {
  HDC hDc = ::GetDC(hWnd);
  PIXELFORMATDESCRIPTOR pfd = {0};
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 64;

  const int pf = ::ChoosePixelFormat(hDc, &pfd);
  if (pf == 0)
    return false;
  if (::SetPixelFormat(hDc, pf, &pfd) == FALSE)
    return false;
  ::ReleaseDC(hWnd, hDc);

  data->hDC = ::GetDC(hWnd);
  if (!g_hRC)
    g_hRC = wglCreateContext(data->hDC);
  return true;
}

void CleanupDeviceWGL(HWND hWnd, WGL_WindowData *data) {
  wglMakeCurrent(nullptr, nullptr);
  ::ReleaseDC(hWnd, data->hDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {

  // ImGui has this and handles a set of messages here.
  // We can define our own cases instead.
  // if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
  //     return true;
  switch (message) {
  case WM_CREATE: {
    // std::cout << "Created Window" << std::endl;
  } break;
  case WM_COMMAND: {
    int wmId = LOWORD(wParam);
    switch (wmId) {
    case IDM_ABOUT:
      DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
      break;
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
  } break;
    // case WM_PAINT: {
    //     PAINTSTRUCT ps;
    //     HDC hdc = BeginPaint(hWnd, &ps);
    //     EndPaint(hWnd, &ps);
    //   }
    //   break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
  UNREFERENCED_PARAMETER(lParam);
  switch (message) {
  case WM_INITDIALOG:
    return (INT_PTR)TRUE;
  case WM_COMMAND: {
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
      EndDialog(hDlg, LOWORD(wParam));
      return (INT_PTR)TRUE;
    }
  } break;
  }
  return (INT_PTR)FALSE;
}
