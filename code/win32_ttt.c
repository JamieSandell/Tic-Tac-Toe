#include <windows.h>

LRESULT CALLBACK
main_window_callback
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
            OutputDebugStringA("WM_SIZE\n");
            break;
        }
        case WM_DESTROY:
        {
            OutputDebugStringA("WM_DESTROY\n");
            break;
        }
        case WM_CLOSE:
        {
            OutputDebugStringA("WM_CLOSE\n");
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
            int width = paint.rcPaint.right - x;
            int height = paint.rcPaint.bottom - y;
            static DWORD operation = WHITENESS;

            if (operation == WHITENESS)
            {
                operation = BLACKNESS;
            }
            else
            {
                operation = WHITENESS;
            }

            PatBlt(device_context, x, y, width, height, operation);
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
    window_class.lpfnWndProc = main_window_callback;
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
            for (;;)
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