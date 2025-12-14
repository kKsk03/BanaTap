#include "banapass.h"

#define PATCH_OFFSET 0x8D0179

BOOL WINAPI DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        initBanapass();
        patchCardDataCheck(PATCH_OFFSET);
        CreateThread(NULL, 0, cardPollThread, NULL, 0, NULL);
    }
    return TRUE;
}
