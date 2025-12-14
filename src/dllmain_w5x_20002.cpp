#include "banapass.h"
#include "MinHook.h"

#define PATCH_OFFSET 0x793A68

// W5X 2.00.02 Function Address Offset
#define ADDR_BngRwAttach       0xB4D6E0
#define ADDR_BngRwInit         0xB4CDA0
#define ADDR_BngRwFin          0xB4CE30
#define ADDR_BngRwGetVersion   0xB4D6D0
#define ADDR_BngRwIsCmdExec    0xB4CF00
#define ADDR_BngRwReqLed       0xB4D400
#define ADDR_BngRwReqAction    0xB4D5F0
#define ADDR_BngRwReqBeep      0xB4D4F0
#define ADDR_BngRwReqCancel    0xB4CF70
#define ADDR_BngRwReqSendUrlTo 0xB4D150
#define ADDR_BngRwReqWaitTouch 0xB4D040

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
