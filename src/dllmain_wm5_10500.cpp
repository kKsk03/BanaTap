#include "banapass.h"
#include "MinHook.h"

#define PATCH_OFFSET 0x72AE48

// WM5 1.05.00 Function Address Offset
#define ADDR_BngRwAttach       0xACBCE0
#define ADDR_BngRwInit         0xACB3A0
#define ADDR_BngRwFin          0xACB430
#define ADDR_BngRwGetVersion   0xACBCD0
#define ADDR_BngRwIsCmdExec    0xACB500
#define ADDR_BngRwReqLed       0xACBA00
#define ADDR_BngRwReqAction    0xACBBF0
#define ADDR_BngRwReqBeep      0xACBAF0
#define ADDR_BngRwReqCancel    0xACB570
#define ADDR_BngRwReqSendUrlTo 0xACB750
#define ADDR_BngRwReqWaitTouch 0xACB640

static uintptr_t imageBase;

static void installHooks() {
    imageBase = (uintptr_t)GetModuleHandleA(NULL);
    
    MH_Initialize();
    
    MH_CreateHook((void*)(imageBase + ADDR_BngRwAttach), (void*)BngRwAttach, NULL);
    MH_CreateHook((void*)(imageBase + ADDR_BngRwInit), (void*)BngRwInit, NULL);
    MH_CreateHook((void*)(imageBase + ADDR_BngRwFin), (void*)BngRwFin, NULL);
    MH_CreateHook((void*)(imageBase + ADDR_BngRwGetVersion), (void*)BngRwGetVersion, NULL);
    MH_CreateHook((void*)(imageBase + ADDR_BngRwIsCmdExec), (void*)BngRwIsCmdExec, NULL);
    MH_CreateHook((void*)(imageBase + ADDR_BngRwReqLed), (void*)BngRwReqLed, NULL);
    MH_CreateHook((void*)(imageBase + ADDR_BngRwReqAction), (void*)BngRwReqAction, NULL);
    MH_CreateHook((void*)(imageBase + ADDR_BngRwReqBeep), (void*)BngRwReqBeep, NULL);
    MH_CreateHook((void*)(imageBase + ADDR_BngRwReqCancel), (void*)BngRwReqCancel, NULL);
    MH_CreateHook((void*)(imageBase + ADDR_BngRwReqSendUrlTo), (void*)BngRwReqSendUrlTo, NULL);
    MH_CreateHook((void*)(imageBase + ADDR_BngRwReqWaitTouch), (void*)BngRwReqWaitTouch, NULL);
    
    MH_EnableHook(MH_ALL_HOOKS);
}

BOOL WINAPI DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(module);
        initBanapass();
        installHooks();
        patchCardDataCheck(PATCH_OFFSET);
        CreateThread(NULL, 0, cardPollThread, NULL, 0, NULL);
    }
    else if (reason == DLL_PROCESS_DETACH) {
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
    }
    return TRUE;
}
