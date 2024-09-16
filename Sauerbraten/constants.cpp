#include "constants.h"

HMODULE hModule = GetModuleHandle(nullptr);
extern uintptr_t baseAddress = (uintptr_t)GetModuleHandle(NULL);
extern LocalPlayer* localPlayer = *(LocalPlayer**)(baseAddress + 0x2A2560);

extern EntityList* entityList = *(EntityList**)(baseAddress + 0x3472E0);
extern int* numPlayers = (int*)(baseAddress + 0x346C9C);

extern float* ViewMatrix = (float*)(baseAddress + 0x32D040);
extern int* windowWidth = (int*)(baseAddress + 0x2A3538);
extern int* windowHeight = (int*)(baseAddress + 0x2A3534);

extern _wglSwapBuffers originalSwapBuffers = (_wglSwapBuffers)GetProcAddress(GetModuleHandle(L"OPENGL32.dll"), "wglSwapBuffers");
extern _wglSwapBuffers end_originalSwapBuffers = originalSwapBuffers;

extern _SelectWeapon SelectWeapon = (_SelectWeapon)(baseAddress + 0x1DB430);
extern SDL_SetRelativeMouseMode_t SDL_SetRelativeMouseMode = (SDL_SetRelativeMouseMode_t)(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));