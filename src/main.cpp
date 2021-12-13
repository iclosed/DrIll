#include <windows.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <tchar.h>
#include "img_proc.h"
#include "sample_mod.h"
#include "window_controller.h"

#define MYPRINT(...) {char output[512]; sprintf_s(output, __VA_ARGS__);  OutputDebugString(output);}

// Global variables
static TCHAR szWindowClass[] = _T("DeskTopApp");  // The main window class name.
static TCHAR szTitle[] = _T("≤‚ ‘App");  // The string that appears in the application's title bar.
static int windowWidth = 300;
static int windowHeight = 350;

double outputValue;
HINSTANCE hInst;

static struct {
    const wchar_t* txt;    // pointer to text to display on button face
    int      iCount;       // count of number of times button clicked
    HWND     hwnd;         // button window handle which identifies the button
} myButtons[] = {
    {L"Points up", 0, 0},
    {L"Points dwn", 0, 0},
    {L"Level up", 0, 0},
    {L"Level dwn", 0, 0}
};

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    match_img("res/astro_cat.png", "res/saturn.png");
    //MYPRINT("\nhahaha %d\n\n", WinController::find_window_hwnd("œﬂ…œ"));

    WinController win = WinController("Õ¯“◊");
    UINT x = 348;
    UINT y = 132;
    //PostMessage(win.get_hwnd(), WM_RBUTTONDOWN, 0, x + (y << 16));
    //PostMessage(win.get_hwnd(), WM_RBUTTONUP, 0, x + (y << 16));
    return 0;

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    RegisterClassEx(&wcex);

    // Store instance handle in our global variable
    hInst = hInstance;
    
    MyCircle c(3);
	outputValue = mysqrt(1337);
    MYPRINT("\n\\fucking dubug log: %f, circle:%f\n\n\n", outputValue, c.Area());
 

	HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW, szWindowClass, szTitle,
        WS_OVERLAPPEDWINDOW,
        //CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300, windowWidth, windowHeight,
        NULL, NULL, hInstance, NULL
    );

    if (!hWnd) {
        MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Windows Desktop Guided Tour"), NULL);
        return 1;
    }

    POINT myPoint = { 10, 10 };  // x, y
    for (auto& a : myButtons) {
		a.hwnd = CreateWindow(TEXT("button"), TEXT("Print"), WS_VISIBLE | WS_CHILD, myPoint.x, myPoint.y, 80, 25, hWnd, NULL, NULL, NULL);
        myPoint.y += 30;    // button width plus a separation distance
    }

    ShowWindow(hWnd, nCmdShow);  // nCmdShow: the fourth parameter from WinMain
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

int buttonClick(HWND hWnd, HWND hButton) {
    // look through the list of buttons to see if the window handle
    // of the button event matches one of our buttons.
    for (auto& a : myButtons) {
        if (a.hwnd == hButton) {
            // this is one of our buttons so we increment button click count.
            // then invalidate the window area and update to trigger WM_PAINT message.
            a.iCount++;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            MYPRINT("wtf??? %d", 1)
            return 1;    // indicate we processed this event.
        }
    }
    return 0;    // indicate we did not process this event
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND: {
        //if (LOWORD(wParam) == 1) {
        //    MYPRINT("\nclicked Button1\n")
        //}
        //if (LOWORD(wParam) == 2) {
        //    PostQuitMessage(0);
        //}

        int wmId = LOWORD(wParam);
        int wmCode = HIWORD(wParam);
        // Parse the menu selections:
        switch (wmId) {
        default:
            // not a menu event so see if it is a button click or not.
            if (wmCode == BN_CLICKED) {
                // if we are managing this button then we skip
                // the DefWindowProc() otherwise it is called.
                if (buttonClick(hWnd, (HWND)lParam)) break;
            }
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
		break;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // TODO: Add any drawing code that uses hdc here...

        // create the text strings we are going to display/update

        wchar_t myText[2][64];
        // following swprintf_s() works because template
        // generates the proper call with the additional buffer
        // size argument.
        swprintf_s(myText[0], L"Points: %d", myButtons[0].iCount - myButtons[1].iCount);
        swprintf_s(myText[1], L"Level: %d", myButtons[2].iCount - myButtons[3].iCount);

        // get the text metrics of the font we are using to draw the text so
        // that we can find out how tall the letters are and can adjust the
        // distance for each line of text properly.
        TEXTMETRIC myTextMetric = { 0 };
        GetTextMetrics(hdc, &myTextMetric);

        // we will use a POINT struct for maintaining the point at which
        // the text output will start. x coordinate is horizontal position
        // and y coordinate is the vertical position.
        POINT myPoint = { 10, 150 };  // x, y
        int   myMargin = 5;

        // iterate over the list of strings we are displaying and
        // display each one on a separate line.
        for (auto& a : myText) {
            std::string s = (char*)a;
            LPCSTR ss = s.c_str();
            TextOut(hdc, myPoint.x, myPoint.y, ss, strlen(ss));
            myPoint.y += myTextMetric.tmHeight + myMargin;
        }

        EndPaint(hWnd, &ps);
		break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    case WM_CREATE: {
		//CreateWindow(TEXT("button"), TEXT("Print"), WS_VISIBLE | WS_CHILD, 20, 50, 80, 25, hWnd, (HMENU)1, NULL, NULL);
        //CreateWindow(TEXT("button"), TEXT("Quit"), WS_VISIBLE | WS_CHILD, 120, 50, 80, 25, hWnd, (HMENU)2, NULL, NULL);
        break;
    }
    default: return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
