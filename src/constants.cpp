#include "player.h"
#include "constants.h"

HMODULE hModule = GetModuleHandle(nullptr);
uintptr_t baseAddress = (uintptr_t)GetModuleHandle(nullptr);

extern playerEntity* localPlayerPtr = *(playerEntity**)(baseAddress + 0x18AC00);
extern entityList* entityListPtr = (entityList*)(baseAddress + 0x191FCC);
extern entityList* players = *(entityList**)(baseAddress + 0x191FCC); //array of players

extern int numPlayers = *(int*)(baseAddress + 0x191FD4);
//extern float* viewMatrix = (float*)(baseAddress + 0x192078);
extern float* viewMatrix = (float*)(baseAddress + 0x17DFD0);

void resetPointers() {
	localPlayerPtr = *(playerEntity**)(baseAddress + 0x18AC00);
	entityListPtr = (entityList*)(baseAddress + 0x191FCC);
	players = *(entityList**)(baseAddress + 0x191FCC);
}

_wglSwapBuffers oWglSwapBuffers = (_wglSwapBuffers)(GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers"));
_SDL_ShowCursor oShowCursor = (_SDL_ShowCursor)GetProcAddress(GetModuleHandle(L"SDL.dll"), "SDL_ShowCursor");
_SDL_SetRelativeMouseMode oSDL_SetRelativeMouseMode = (_SDL_SetRelativeMouseMode)(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));

// "ac_client.exe"+00191FCC