#pragma once
#include <Windows.h>
#include "player.h"
#include <vector>


void resetPointers();

extern HMODULE hModule;
extern uintptr_t baseAddress;

extern entityList* players;
extern playerEntity* localPlayerPtr;
extern entityList* entityListPtr;
extern entityList* players;
extern float* viewMatrix;

extern int numPlayers;

typedef BOOL(__stdcall* _wglSwapBuffers)(HDC hDc);
extern _wglSwapBuffers oWglSwapBuffers;

typedef int(__cdecl* _SDL_ShowCursor)(int toggle);
extern _SDL_ShowCursor oShowCursor;

typedef int(__cdecl* _SDL_SetRelativeMouseMode)(int mode);
extern _SDL_SetRelativeMouseMode oSDL_SetRelativeMouseMode;