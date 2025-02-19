#include <windows.h>
#include <iostream>

DWORD startTime = 0;

class Shortcut
{
private:
    int codekeys;

    Shortcut(int codekeys)
    {
        this->codekeys = codekeys;
    }
};

// Función para interceptar eventos del teclado
LRESULT CALLBACK LowLevelKeysboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT *pKeyInfo = (KBDLLHOOKSTRUCT *)lParam;

        // Verifica si se presionó la tecla ';' (VK_OEM_1)
        if (wParam == WM_KEYDOWN && pKeyInfo->vkCode == VK_OEM_1)
        {
            // if (wParam == WM_KEYUP ==)
            startTime = GetTickCount();
            keybd_event(VK_LEFT, 0, 0, 0); // Simula la flecha izquierda
            return 1;                      // Bloquea la tecla original
        }

        // Verifica si se presionó la tecla 'a'
        if (wParam == WM_KEYDOWN && pKeyInfo->vkCode == 'A')
        {
            keybd_event(VK_LEFT, 0, 0, 0); // Simula la flecha izquierda
            return 1;                      // Bloquea la tecla original
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeysboardProc, NULL, 0);

    // Mantener el programa en ejecución
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHook);
    return 0;
}