#include "player.h"
#include "constants.h"

HMODULE hModule = GetModuleHandle(nullptr);
uintptr_t baseAddress = (uintptr_t)GetModuleHandle(nullptr);

extern playerEntity* localPlayerPtr = *(playerEntity**)(baseAddress + 0x18AC00);
extern entityList* entityListPtr = (entityList*)(baseAddress + 0x191FCC);
extern entityList* players = *(entityList**)(baseAddress + 0x191FCC); //array of players

extern int numPlayers = *(int*)(baseAddress + 0x191FD4);

// "ac_client.exe"+00191FCC