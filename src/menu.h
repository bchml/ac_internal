#pragma once
#include "constants.h"
#include <windows.h> // Add this include to define HDC and BOOL

namespace Menu {
	void init();
	void toggleMenu();
	void startRender();	
	void render();
	void endRender();

	BOOL __stdcall newSwapBuffers(HDC hDc);
};
