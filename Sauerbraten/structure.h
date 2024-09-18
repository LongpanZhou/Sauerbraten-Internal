#pragma once
#include <geom.h>

class PlayerEntity
{
public:
	Vector3 Position; //0x0000
	Vector3 Velocity; //0x000C
	Vector3 Falling; //0x0018
	Vector3 DeltaPosition; //0x0024
	Vector3 NewPosition; //0x0030
	Vector3 ViewAngle; //0x003C
	float MaxSpeed; //0x0048
	uint32_t TimeInAir; //0x004C
	char pad_0050[296]; //0x0050
	uint32_t Health; //0x0178
	char pad_017C[24]; //0x017C
	int32_t WeaponAmmo[7]; //0x0194
	char pad_01B0[192]; //0x01B0
	int32_t Alive; //0x0270
	char Name[16]; //0x0274
}; //Size: 0x0284

class EntityList
{
public:
	PlayerEntity* players [20];
};