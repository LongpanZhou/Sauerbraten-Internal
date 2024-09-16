#pragma once
#include <wtypes.h>

namespace Menu 
{
	void toggleMenu();
	void init();
	void startRender();
	void render();
	void endRender();
	void shutdown();
	BOOL __stdcall newSwapBuffers(HDC hdc);
}