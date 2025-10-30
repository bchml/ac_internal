#include "menu.h"
#include "constants.h"
#include "GL/Gl.h"
#include "GL/GLU.h"
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

#include "imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"
#include <iostream>
#include "settings.h"
#include "esp.h"

const ImVec2 windowSize = ImVec2(400, 400);
bool showMenu = false;
bool initialized = false;
bool contextCreated = false;
HWND gameWindow;
HGLRC myContext;
HGLRC gameContext;
HDC gHDC;
WNDPROC oWNDProc = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK newWNDProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (showMenu) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return 0;
		switch (uMsg) {
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			return 0;
		}
	}
	return CallWindowProc(oWNDProc, hWnd, uMsg, wParam, lParam);
}

void testSettings() {
	if (!ImGui::BeginTabItem("Test"))
		return;

	ImGui::Text("Hello, world!");
	if (ImGui::Button("Test Button")) {
		localPlayerPtr->health = 1337;
	}
	ImGui::EndTabItem();
}

void espSettings() {
	if (!ImGui::BeginTabItem("ESP"))
		return;
	ImGui::Checkbox("Enable ESP", &Settings::ESP::enabled);
	ImGui::Checkbox("Draw team", &Settings::ESP::drawTeam);
	ImGui::ColorEdit4("Team color", (float*)&Settings::ESP::teamColor->Value);
	ImGui::ColorEdit4("Enemy color", (float*)&Settings::ESP::enemyColor->Value);
	ImGui::EndTabItem();
}

void Menu::toggleMenu() {
	showMenu = !showMenu;
	ImGuiIO& io = ImGui::GetIO();
	io.WantCaptureMouse = showMenu;
	io.WantCaptureKeyboard = showMenu;
	io.MouseDrawCursor = showMenu;
	oSDL_SetRelativeMouseMode(!showMenu);
}

void Menu::init() {
	ImGui::CreateContext();
	gameWindow = FindWindowA(NULL, "AssaultCube");
	oWNDProc = (WNDPROC)SetWindowLongPtrA(gameWindow, GWLP_WNDPROC, (LONG_PTR)newWNDProc);
	ImGui_ImplWin32_Init(gameWindow);
	ImGui_ImplOpenGL2_Init();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos; // we will provide mouse position
	io.Fonts->AddFontDefault();
	ImGui::SetCurrentContext(ImGui::GetCurrentContext());

	ImGui::SetNextWindowSize(windowSize);
	initialized = true;
	std::cout << "menu initialized\n";
}

void Menu::startRender()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Menu::render()
{

	if (!showMenu)
		return;
	ImGui::Begin("MONEYHACK $$$", &showMenu);
	if(ImGui::BeginTabBar("Tabbar")) {
		espSettings();
		testSettings();
		ImGui::EndTabBar();
	}
	oSDL_SetRelativeMouseMode(!showMenu);
	ImGui::End();

}

void setupContext(HDC& hDc) {
	myContext = wglCreateContext(hDc);

	wglMakeCurrent(hDc, myContext);
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

void Menu::endRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

BOOL __stdcall Menu::newSwapBuffers(HDC hDc)
{
	if (!initialized) {
		Menu::init();
		oWglSwapBuffers(hDc);
	}

	gameContext = wglGetCurrentContext();
	if (!contextCreated)
		setupContext(hDc);
	wglMakeCurrent(hDc, myContext);
	Menu::startRender();
	Menu::render();
	ESP::drawESP();
	Menu::endRender();

	wglMakeCurrent(hDc, gameContext);
	return oWglSwapBuffers(hDc);
}
