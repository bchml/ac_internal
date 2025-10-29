#include <Windows.h>
#include <iostream>
#include "constants.h"
#include "player.h"
#include "detours/detours.h"
#include "menu.h"

void aimbot() {
    while (true) {
        Sleep(100);
        if (GetAsyncKeyState(VK_DELETE))
            Menu::toggleMenu();
    }
}
void hook() {
    Sleep(1000);
	DisableThreadLibraryCalls(hModule);
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)oWglSwapBuffers, Menu::newSwapBuffers);
	DetourTransactionCommit();
}

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
    FreeConsole();
}

DWORD __stdcall Thread(HMODULE hModule){

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReasonForCall, LPVOID lpReserved) {
    switch (dwReasonForCall) {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)console, hModule, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hook, hModule, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)aimbot, hModule, 0, nullptr);
        /*if (dwReasonForCall == DLL_PROCESS_ATTACH) {
            HANDLE hConsole =
            HANDLE hHook =
            HANDLE hAimbot =
        }*/
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}
