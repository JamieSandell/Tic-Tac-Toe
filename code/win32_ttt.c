#include <stdbool.h>
#include <windows.h>

#define internal static
#define local_persist static
#define global_variable static

global_variable bool running;

internal void
win32_resize_dib_section(int width, int height)
{
    BITMAPINFO bitmap_info = {0};
    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);

    void *bitmap_memory;
    HBITMAP bitmap_handle = CreateDIBSection
    (
        ,
        ,
        DIB_RGB_COLORS,
        &bitmap_memory,
        0,
        0
    );
}

internal void
win32_update_window(HDC device_context, int x, int y, int width, int height)
{
    StretchDIBits
    (
        device_context,
        x,
        y,
        width,
        height,
        ,
        ,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}

LRESULT CALLBACK
win_32_main_window_callback
(
    HWND window,
    UINT message,
    WPARAM w_param,
    LPARAM l_param
)
{
    LRESULT result = 0;

    switch (message)
    {

        case WM_SIZE:
        {
            RECT client_rect;
            GetClientRect(window, &client_rect);
            int width = client_rect.right - client_rect.left;
            int height = client_rect.bottom - client_rect.top;
            win32_resize_dib_section(width, height);
            break;
        }
        case WM_DESTROY:
        {
            running = false;
            break;
        }
        case WM_CLOSE:
        {
            running = false;
            break;
        }
        case WM_ACTIVATEAPP:
        {
            OutputDebugStringA("WM_ACTIVATEAPP\n");
            break;
        }
        case WM_PAINT:
        {
            OutputDebugStringA("WM_PAINT\n");
            
            PAINTSTRUCT paint = {0};
            HDC device_context = BeginPaint(window, &paint);
            int x = paint.rcPaint.left;
            int y = paint.rcPaint.top;
            int width = paint.rcPaint.right - paint.rcPaint.left;
            int height = paint.rcPaint.bottom - paint.rcPaint.top;
            win32_update_window(device_context, x, y, width, height);

            EndPaint(window, &paint);
            break;
        }
        default:
        {
            result = DefWindowProcA(window, message, w_param, l_param);
            break;
        }
    }

    return result;
}

int CALLBACK
WinMain
(
    HINSTANCE instance,
    HINSTANCE previous_instance,
    LPSTR command_line,
    int show_command
)
{
    WNDCLASSA window_class = {0};
    window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = win_32_main_window_callback;
    window_class.hInstance = instance;
    window_class.lpszClassName = "TicTacToeWindowClass";

    if (RegisterClassA(&window_class))
    {
        HWND window = CreateWindowExA
        (
            0, // dwExStyle
            window_class.lpszClassName,
            "Tic-Tac-Toe",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, // x
            CW_USEDEFAULT, // y
            CW_USEDEFAULT, // width
            CW_USEDEFAULT, // height
            0, //hWndParent
            0, // hMenu
            instance,
            0
        );

        if (window)
        {        
            running = true;

            while(running)
            {
                MSG message;
                BOOL message_result = GetMessageA(&message, 0, 0, 0);

                if (message_result > 0)
                {
                    TranslateMessage(&message);
                    DispatchMessageA(&message);
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            // Window creation failed.
            // TODO: Logging.
        }
    }
    else
    {
        // Window class registration failed.
        // TODO: Logging.
    }

    return 0;
}