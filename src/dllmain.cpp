#include <Windows.h>
#include <iostream>
#include "constants.h"
#include "player.h"


void console() {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	freopen_s(&f, "CONIN$", "r", stdin);
	std::cout << "Console allocated!" << std::endl;
    while (true) {
        std::string input;
        std::cin >> input;
        if (input == "exit") {
            break;
		}
        if (input == "test") {
            localPlayerPtr->health = 1337;
        }
        if (input == "exit") {
            break;
        }
        if (input == "players") {
            for (int i = 0; i < numPlayers; i++) {
				if (players->players[i] == nullptr || players->players[i]->vftable == nullptr) break;
                std::cout << "  Health: " << players->players[i]->health << std::endl;
                std::cout << "  Armor: " << players->players[i]->armor << std::endl;
                std::cout << "  Name: " << players->players[i]->name << std::endl;
            }
        }
        
    }
}

DWORD __stdcall Thread(HMODULE hModule){

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReasonForCall, LPVOID lpReserved) {
    if (dwReasonForCall == DLL_PROCESS_ATTACH) {
        HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Thread, hModule, 0, nullptr);
        HANDLE hConsole = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)console, hModule, 0, nullptr);
    }
    if (dwReasonForCall == DLL_PROCESS_DETACH) {
	    
    }

    return TRUE;
}
