#pragma once
#include <Windows.h>
#include "structure.h"

extern HMODULE hModule;
extern uintptr_t baseAddress;
extern LocalPlayer* localPlayer;
extern EntityList* entityList;

extern int* numPlayers;
extern float* ViewMatrix;

extern int* windowWidth;
extern int* windowHeight;

typedef BOOL(__stdcall* _wglSwapBuffers)(HDC hdc);
extern _wglSwapBuffers originalSwapBuffers;
extern _wglSwapBuffers end_originalSwapBuffers;

typedef __int64(__fastcall* _SelectWeapon)(int WeaponID, LocalPlayer* localPlayer);
extern _SelectWeapon SelectWeapon;

typedef int(*SDL_SetRelativeMouseMode_t)(int);
extern SDL_SetRelativeMouseMode_t SDL_SetRelativeMouseMode;