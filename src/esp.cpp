#include "esp.h"
#include "constants.h"
#include "stdio.h"
#include <iostream>
#include "settings.h"
#include "vec.h"
#include "imgui.h"



/*playerEntity* ESP::getClosestEnemy() {
	playerEntity* closestEnemy = nullptr;
	float closestDistance = FLT_MAX;
	Vec3 localPlayerPos = localPlayerPtr->positionFeet;
	for (int i = 1; i < numPlayers + 1; i++) {
		playerEntity* currentPlayer = players->players[i];
		if (currentPlayer == nullptr || currentPlayer->health > 100) {
			continue;
		}
		float distance = (currentPlayer->positionFeet - localPlayerPos).length();
		if (distance < closestDistance) {
			closestDistance = distance;
			closestEnemy = currentPlayer;
		}
	}
	return closestEnemy;
}*/

void ESP::drawESP() {
	if(!Settings::ESP::enabled) {
		return;
	}
	bool teammate = false;
	playerEntity* currentPlayer = nullptr;
	for(int i = 0; i < numPlayers; i++) {
		currentPlayer = players->players[i];
		if (!currentPlayer) {
			std::cout << "CURRENTPLAYER IS NULLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n";
			break;
		}
		if (currentPlayer->health > 100 || currentPlayer->health <= 0) {
			continue;
		}
		teammate = currentPlayer->team == localPlayerPtr->team;
		if(teammate && !Settings::ESP::drawTeam) {
			continue;
		}
		
		Vec3 headPos = { currentPlayer->o.x, currentPlayer->o.y, currentPlayer->o.z };
		Vec3 feetPos = { currentPlayer->o.x, currentPlayer->o.y, currentPlayer->o.z - currentPlayer->eyeHeight };
		

		Vec3 headScreenPos = OpenGLWorldToScreen(headPos, viewMatrix, 1280, 720);
		Vec3 feetScreenPos = OpenGLWorldToScreen(feetPos, viewMatrix, 1280, 720);

		float height = abs(headScreenPos.y - feetScreenPos.y);
		float width = height / 4;

		ImVec2 topLeft = ImVec2(headScreenPos.x - width, headScreenPos.y);
		ImVec2 topRight = ImVec2(headScreenPos.x + width, headScreenPos.y);

		ImVec2 bottomRight = ImVec2(feetScreenPos.x + width, feetScreenPos.y);
		ImVec2 bottomLeft = ImVec2(feetScreenPos.x - width, feetScreenPos.y);

		ImColor boxColor = teammate ? *Settings::ESP::teamColor : *Settings::ESP::enemyColor;
		//ImColor boxColor = *Settings::ESP::enemyColor;
		ImGui::GetBackgroundDrawList()->AddQuad(topLeft, bottomLeft, bottomRight, topRight, boxColor, 2.0f);
		std::cout << "drawing esp\n";
	}
}