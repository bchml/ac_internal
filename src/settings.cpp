#include "settings.h"
#include "imgui.h"

namespace Settings {
	namespace ESP {
		extern bool enabled = false;
		extern bool drawTeam = false;
		extern ImColor* teamColor = new ImColor(0, 255, 0, 255);
		extern ImColor* enemyColor = new ImColor(255, 0, 0, 255);
	}
	namespace Aimbot {

	}
}