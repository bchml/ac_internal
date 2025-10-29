#pragma once
#include <Windows.h>
#include "player.h"
#include <vector>

extern HMODULE hModule;
extern uintptr_t baseAddress;

extern entityList* players;

extern playerEntity* localPlayerPtr;
extern entityList* entityListPtr;
extern entityList* players;
extern int numPlayers;