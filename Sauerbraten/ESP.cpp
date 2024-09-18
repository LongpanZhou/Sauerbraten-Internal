#include "ESP.h"
#include "constants.h"
#include "imgui.h"
#include <iostream>
#include "Settings.h"

#define deg2rad(x) (x * 3.14159265358979323846 / 180)

void ESP::esp()
{
	if (!Settings::esp)
		return;

	//Online Mode
	if (entityList == nullptr)
		return;

	//Local Player
	PlayerEntity* local = entityList->players[0];
	if (local == nullptr)
		return;

	for (int i = 1; i < *numPlayers; i++)
	{
		PlayerEntity* player = entityList->players[i];
		if (player == nullptr)
			continue;

		bool Draw = false;
		Vec3 wtsFeet, wtsHead;
		Draw |= WorldToScreen(player->Position + Vec3{ 0, 0, -15 }, wtsFeet, ViewMatrix, *windowWidth, *windowHeight);
		Draw |= WorldToScreen(player->Position, wtsHead, ViewMatrix, *windowWidth, *windowHeight);

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
		ImVec2 end{ ESPrect.x + 5, wtsFeet.y + (wtsHead.y - wtsFeet.y) * ((player->Health <= 150 ? player->Health : 150.0f) / 100.f) };
		ImColor color{ (int)(255 * (1 - player->Health / 100.f)), (int)(255 * player->Health / 100.f), 0 };
		ImGui::GetForegroundDrawList()->AddLine(start, end, color, 3.0f);
	}
}

void ESP::noClip()
{
	if (!Settings::NoClip)
		return;

	float forwardX = (float)(Settings::Speed)*cos(deg2rad((localPlayer->ViewAngle.x)));
	float forwardY = (float)(Settings::Speed)*sin(deg2rad((localPlayer->ViewAngle.x)));
	float forwardZ = (float)(Settings::Speed)*sin(deg2rad((localPlayer->ViewAngle.y)));

	if (GetAsyncKeyState('A'))
	{
		localPlayer->NewPosition.x += forwardX;
		localPlayer->NewPosition.y += forwardY;
	}
	else if (GetAsyncKeyState('D'))
	{
		localPlayer->NewPosition.x -= forwardX;
		localPlayer->NewPosition.y -= forwardY;
	}
	else if (GetAsyncKeyState('S'))
	{
		localPlayer->NewPosition.x += forwardY;
		localPlayer->NewPosition.y -= forwardX;
		localPlayer->NewPosition.z -= forwardZ;
	}
	else if (GetAsyncKeyState('W'))
	{
		localPlayer->NewPosition.x -= forwardY;
		localPlayer->NewPosition.y += forwardX;
		localPlayer->NewPosition.z += forwardZ;
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		localPlayer->NewPosition.z += Settings::Speed;
	}
	else if (GetAsyncKeyState(VK_LSHIFT))
	{
		localPlayer->NewPosition.z -= Settings::Speed;
	}
}

void ESP::Kill()
{
	for (int i = 0; i < *numPlayers; i++)
	{
		PlayerEntity* player = entityList->players[i];
		if (player == nullptr)
			continue;

		if (player->Health <= 0 || player->Health > 150)
			continue;

		Damage(999, player, player, true);
	}
}

PlayerEntity* getclosedtarget()
{
	PlayerEntity* target = nullptr;
	float closest = FLT_MAX;

	for (int i = 1; i < *numPlayers; i++)
	{
		PlayerEntity* player = entityList->players[i];
		if (player == nullptr)
			continue;
		if (player->Health <= 0 || player->Health > 150)
			continue;

		Vec3 localPos = localPlayer->Position;
		Vec3 targetPos = player->Position;
		float distance = sqrt(pow(localPos.x - targetPos.x, 2) + pow(localPos.y - targetPos.y, 2) + pow(localPos.z - targetPos.z, 2));
		if (distance < closest)
		{
			closest = distance;
			target = player;
		}
	}
	return target;
}

void ESP::Aimbot()
{
	if ((!Settings::aimbot) && GetAsyncKeyState(VK_LSHIFT))
	{	
		PlayerEntity* target = getclosedtarget();
		if (target != nullptr)
			localPlayer->ViewAngle = CalcAngle(localPlayer->Position, target->Position);
	}
}

void ESP::newShoot(PlayerEntity* source, Vec3* dest)
{
	if (!Settings::slient)
		return end_originalShoot(source, dest);

	PlayerEntity* target = getclosedtarget();
	if (target != nullptr)
		end_originalShoot(localPlayer, &target->Position);
}