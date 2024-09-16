#include "Menu.h"
#include "constants.h"
#include <iostream>
#include "ESP.h"
#include "Settings.h"

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_opengl2.h>
#include <gl/GL.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

bool showMenu, initialized, contextCreated, insert_pressed;

HWND gameWindow;
HGLRC myContext;
HGLRC gameContext;
HDC gameHDC;
WNDPROC originalWndProc;
RECT rect;
LPCSTR gameName = "Cube 2: Sauerbraten";

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK newWNDProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (showMenu)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;
		ImGuiIO& io = ImGui::GetIO();

		if (uMsg == WM_MOUSEMOVE || uMsg == WM_LBUTTONDOWN || uMsg == WM_RBUTTONDOWN)
			return 0;
	}
	return CallWindowProc(originalWndProc, hWnd, uMsg, wParam, lParam);
}

void HackMenu()
{
	ImGui::BeginTabItem("Hack Menu");
	ImGui::Checkbox("ESP", &Settings::esp);
	ImGui::InputInt("Switch Weapons", &Settings::switchWeapons);
	if (ImGui::Button("Apply"))
		SelectWeapon(Settings::switchWeapons,localPlayer);
	ImGui::EndTabItem();
}

void SetupContext(HDC hdc)
{
	myContext = wglCreateContext(hdc);

	wglMakeCurrent(hdc, myContext);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	contextCreated = true;
}

void Menu::toggleMenu()
{
	showMenu = !showMenu;
	ImGuiIO& io = ImGui::GetIO();
	io.WantCaptureMouse = showMenu;
	io.WantCaptureKeyboard = showMenu;
	io.MouseDrawCursor = showMenu;
	SDL_SetRelativeMouseMode(!showMenu);
}

void Menu::init()
{
	gameWindow = FindWindowA(NULL, gameName);
	originalWndProc = (WNDPROC)SetWindowLongPtr(gameWindow, GWLP_WNDPROC, (LONG_PTR)newWNDProc);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

	ImGui_ImplWin32_Init(gameWindow);
	ImGui_ImplOpenGL2_Init();
	ImGui::StyleColorsDark();

	ImGui::SetCurrentContext(ImGui::GetCurrentContext());
	initialized = true;
}

void Menu::startRender()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Menu::render()
{
	if (GetAsyncKeyState(VK_HOME) & 0x8000)
	{
		if (!insert_pressed)
		{
			toggleMenu();
			insert_pressed = true;
		}
	}
	else
	{
		insert_pressed = false;
	}
	if (showMenu)
	{
		ImGui::SetNextWindowSize(ImVec2(400, 400));
		ImGui::Begin("Menu", &showMenu);
		ImGui::BeginTabBar("Tabs");
		HackMenu();
		ImGui::EndTabBar();
		ImGui::End();
	}
}

void Menu::endRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void Menu::shutdown()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	SetWindowLongPtr(FindWindowA(NULL, gameName), GWLP_WNDPROC, (LONG_PTR)originalWndProc);
}


BOOL __stdcall Menu::newSwapBuffers(HDC hdc)
{
	gameContext = wglGetCurrentContext();
	if (!contextCreated)
		SetupContext(hdc);

	wglMakeCurrent(hdc, myContext);
	Menu::startRender();
	Menu::render();
	ESP::esp();
	Menu::endRender();

	wglMakeCurrent(hdc, gameContext);
	return end_originalSwapBuffers(hdc);
}