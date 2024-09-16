#pragma once
#include <geom.h>

class LocalPlayer
{
public:
	Vector3 Position; //0x0000
	Vector3 Velocity; //0x000C
	Vector3 Padding; //0x0018
	char pad_0024[24]; //0x0024
	Vector2 ViewAngle; //0x003C
	char pad_0044[308]; //0x0044
	uint32_t Health; //0x0178
}; //Size: 0x017C

class PlayerEntity
{
public:
	char pad_0000[20]; //0x0000
	char Name[16]; //0x0014
	char pad_0024[244]; //0x0024
	char Team[4]; //0x0118 
	char pad_011C[548]; //0x011C
	int32_t Health; //0x0340
	char pad_0344[80]; //0x0344
	Vector3 Position; //0x0394
}; //Size: 0x03A0

class EntityList
{
public:
	PlayerEntity* players [21];
};