#include <windows.h>

// Глобальные переменные
HWND g_hwnd;
HWND g_title;
HWND g_textbox;

// Обработчик сообщений окна
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

// Точка входа WinAPI-приложения
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Создание mutex для имитации единственного процесса Roblox
    CreateMutex(0, 1, "ROBLOX_singletonEvent");

    // Регистрация класса окна
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MULTIROBLOX_CLASS";

    RegisterClass(&wc);

    // Создание главного окна
    g_hwnd = CreateWindowEx(
        0,
        "MULTIROBLOX_CLASS",
        "MultiRoblox",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 455,
        NULL, NULL, hInstance, NULL);

    // Статический текст (заголовок)
    g_title = CreateWindow(
        "STATIC",
        "MultiRoblox 0.0.4",
        WS_VISIBLE | WS_CHILD,
        10, 10, 365, 20,
        g_hwnd, NULL, hInstance, NULL);

    // Текстовое поле с инструкцией
    g_textbox = CreateWindow(
        "EDIT",
        "Thanks for using MultiRoblox_By_Zlaoslav!\r\n\r\n"
        "In case if you're wondering, you must open\r\n"
        "MultiRoblox FIRST before opening multiple ROBLOX\r\n"
        "sessions. Once you close MultiRoblox, all but one\r\n"
        "ROBLOX instance will close.\r\n\r\n"
        "Discord Name: @78060 (Slavik)\r\n"
        "Roblox Name: Zlaoslav\r\n"
        "GitHub Link: https://github.com/CatHacker1/MultiRoblox_By_Zlaoslav\r\n",
        WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_AUTOHSCROLL | ES_MULTILINE | ES_READONLY,
        10, 40, 365, 365,
        g_hwnd, NULL, hInstance, NULL);

    if (g_hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(g_hwnd, nCmdShow);

    // Цикл обработки сообщений
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
