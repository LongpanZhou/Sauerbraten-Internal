#pragma once
#include <Windows.h>
#include "structure.h"

extern HMODULE hModule;
extern uintptr_t baseAddress;
extern PlayerEntity* localPlayer;
extern EntityList* entityList;

extern int* numPlayers;
extern float* ViewMatrix;

extern int* windowWidth;
extern int* windowHeight;

typedef BOOL(__stdcall* _wglSwapBuffers)(HDC hdc);
extern _wglSwapBuffers originalSwapBuffers;
extern _wglSwapBuffers end_originalSwapBuffers;

typedef __int64(__fastcall* _SelectWeapon)(uint32_t WeaponID, PlayerEntity* localPlayer);
extern _SelectWeapon SelectWeapon;

typedef void(__fastcall* _shoot)(PlayerEntity* Source, Vec3* dest);
extern _shoot originalShoot;
extern _shoot end_originalShoot;

typedef void(__fastcall* _damaged)(uint32_t damage, PlayerEntity* target, PlayerEntity* actor, bool local);
extern _damaged Damage;

typedef int(*SDL_SetRelativeMouseMode_t)(int);
extern SDL_SetRelativeMouseMode_t SDL_SetRelativeMouseMode; 

extern void* NoMoveAddrTarget;