#include "ESP.h"
#include "constants.h"
#include "imgui.h"
#include <iostream>
#include "Settings.h"

void ESP::esp()
{
	if (!Settings::esp)
		return;

	PlayerEntity* local = entityList->players[0];

	for (int i = 1; i < *numPlayers; i++)
	{
		PlayerEntity* player = entityList->players[i];
		if (!strcmp(local->Team, player->Team))
			continue;

		bool Draw = false;
		Vec3 wtsFeet, wtsHead;
		Draw |= WorldToScreen(player->Position, wtsFeet, ViewMatrix, *windowWidth, *windowHeight);
		Draw |= WorldToScreen(player->Position + Vec3{ 0, 0, 15 }, wtsHead, ViewMatrix, *windowWidth, *windowHeight);

		if (!Draw)
			continue;

		std::string text = player->Name;
		float textWidth = ImGui::CalcTextSize(text.c_str()).x;
		ImVec2 position(wtsFeet.x - textWidth / 2, wtsFeet.y);
		ImGui::GetBackgroundDrawList()->AddText(position, ImColor(255, 255, 255, 255), text.c_str());
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(*windowWidth / 2, *windowWidth), { wtsFeet.x, wtsFeet.y }, ImColor{ 255,0,0,255 }, 1.0f);
		
		Vec4 ESPrect = CalcRect(wtsFeet, wtsHead);
		ImGui::GetForegroundDrawList()->AddRect({ ESPrect.x,ESPrect.y }, { ESPrect.z,ESPrect.w }, ImColor{ 255,0,0,255 });

		ImVec2 start{ ESPrect.x + 5, wtsFeet.y };
		ImVec2 end{ ESPrect.x + 5, wtsFeet.y + (wtsHead.y - wtsFeet.y) * (player->Health / 100.f) };
		ImColor color{ (int)(255 * (1 - player->Health / 100.f)), (int)(255 * player->Health / 100.f), 0 };
		ImGui::GetForegroundDrawList()->AddLine(start, end, color, 3.0f);
	}
}