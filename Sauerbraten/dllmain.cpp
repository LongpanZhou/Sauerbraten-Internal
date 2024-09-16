#include <Windows.h>
#include "Menu.h"
#include <iostream>
#include "constants.h"
#include <MinHook.h>
#pragma comment(lib, "libMinHook.x64.lib")

bool init_hook()
{
    MH_CreateHook(originalSwapBuffers, &Menu::newSwapBuffers, reinterpret_cast<void**>(&end_originalSwapBuffers));
    return true;
}

void hook()
{
    // This is the function that will be called when the DLL is injected.
    // We don't need to do anything here, so we just return.
    if (MH_Initialize() != MH_OK)
        std::cout << "MH Initialized" << std::endl;
	if (init_hook())
        std::cout << "MH Hooked" << std::endl;
    if (MH_EnableHook(MH_ALL_HOOKS) == MH_OK)
        std::cout << "MH Enable" << std::endl;
}

void unhook()
{
    // This is the function that will be called when the DLL is ejected.
    // We don't need to do anything here, so we just return.
    if (MH_DisableHook(MH_ALL_HOOKS) == MH_OK)
        std::cout << "MH Disable" << std::endl;
    if (MH_RemoveHook(MH_ALL_HOOKS) == MH_OK)
        std::cout << "MH Unhooked" << std::endl;
    if (MH_Uninitialize() == MH_OK)
        std::cout << "MH Uninitialize" << std::endl;
}

void injected_thread(HMODULE hModule)
{
    // This is the thread that will be executed when the DLL is injected.
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);
    freopen_s(&file, "CONIN$", "r", stdin);
    Menu::init();
    hook();

    std::cout << "Injected successfully" << std::hex << std::endl;
    std::cout << *windowWidth << std::endl;
    std::cout << *windowHeight << std::endl;

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        if (GetAsyncKeyState(VK_END) & 1)
			break;
    }

    unhook();
    Menu::shutdown();
    std::cout << "Uninjecting..." << std::endl;
    fclose(file);
    FreeConsole();
    FreeLibraryAndExitThread(static_cast<HMODULE>(hModule), 0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)injected_thread, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}