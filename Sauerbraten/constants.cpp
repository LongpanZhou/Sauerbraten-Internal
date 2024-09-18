#include "constants.h"

HMODULE hModule = GetModuleHandle(nullptr);
extern uintptr_t baseAddress = (uintptr_t)GetModuleHandle(NULL);
extern PlayerEntity* localPlayer = *(PlayerEntity**)(baseAddress + 0x2A2560);

extern EntityList* entityList = *(EntityList**)(baseAddress + 0x346C90);
extern int* numPlayers = (int*)(baseAddress + 0x346C9C);

extern float* ViewMatrix = (float*)(baseAddress + 0x32D040);
extern int* windowWidth = (int*)(baseAddress + 0x2A3538);
extern int* windowHeight = (int*)(baseAddress + 0x2A3534);

extern SDL_SetRelativeMouseMode_t SDL_SetRelativeMouseMode = (SDL_SetRelativeMouseMode_t)(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));

extern _wglSwapBuffers originalSwapBuffers = (_wglSwapBuffers)GetProcAddress(GetModuleHandle(L"OPENGL32.dll"), "wglSwapBuffers");
extern _wglSwapBuffers end_originalSwapBuffers = originalSwapBuffers;

extern _shoot originalShoot = (_shoot)(baseAddress + 0x1DB4C0);
extern _shoot end_originalShoot = originalShoot;

extern void* NoMoveAddrTarget = (void*)(baseAddress + 0x10F1A7);

extern _damaged Damage = (_damaged)(baseAddress + 0x1C4980);
extern _SelectWeapon SelectWeapon = (_SelectWeapon)(baseAddress + 0x1DB430);