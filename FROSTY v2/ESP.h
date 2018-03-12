
#pragma once

#include "SDK.h"
#include "singleton.hpp"
class visuals
	:public singleton<visuals>
{
public:
	visuals();
	void OnPaintTraverse(C_BaseEntity* local);
private:
	C_BaseEntity *BombCarrier;

	void DrawBox(RECT rect, Color Col);
	void DrawCorners(RECT rect, Color Col);
	void ThreeDBox(Vector minin, Vector maxin, Vector pos, Color Col);
	void DrawInfo(RECT rect, C_BaseEntity* pPlayer, C_BaseEntity* local);
	void BulletTrace(C_BaseEntity* pEntity, Color color);
	void Skeleton(C_BaseEntity* pEntity, Color Color);
	void DrawSnapLine(Vector to, Color clr);
	void DrawHealth(RECT rect, C_BaseEntity* pPlayer);
	void DrawAngles();
	void DrawAwall();

	RECT DynamicBox(C_BaseEntity* pPlayer, bool& PVS, C_BaseEntity* local);


	void DLight(C_BaseEntity* local, C_BaseEntity* entity);
	void Crosshair(C_BaseEntity* local);
	void NightMode();
	void Hitmarker();
};

inline int flGetDistance(Vector from, Vector to)
{
	Vector angle;
	angle.x = to.x - from.x;	angle.y = to.y - from.y;	angle.z = to.z - from.z;

	return floor(sqrt(angle.x*angle.x + angle.y*angle.y + angle.z*angle.z) * 0.0254f);
}

inline float CSGO_Armor(float flDamage, int ArmorValue)
{
	float flArmorRatio = 0.5f;
	float flArmorBonus = 0.5f;
	if (ArmorValue > 0) {
		float flNew = flDamage * flArmorRatio;
		float flArmor = (flDamage - flNew) * flArmorBonus;

		if (flArmor > static_cast<float>(ArmorValue)) {
			flArmor = static_cast<float>(ArmorValue) * (1.f / flArmorBonus);
			flNew = flDamage - flArmor;
		}

		flDamage = flNew;
	}
	return flDamage;
}