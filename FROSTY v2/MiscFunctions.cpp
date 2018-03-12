

#include "MiscFunctions.h"
#include "Utilities.h"
#include "Autowall.h"
#include "Render.h"

void UTIL_TraceLine(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, C_BaseEntity *ignore, int collisionGroup, trace_t *ptr)
{
	Ray_t ray;
	ray.Init(vecAbsStart, vecAbsEnd);
	CTraceFilter traceFilter;
	traceFilter.pSkip = ignore;
	g_EngineTrace->TraceRay(ray, mask, &traceFilter, ptr);
}
void UTIL_ClipTraceToPlayers(C_BaseEntity* pEntity, Vector start, Vector end, unsigned int mask, ITraceFilter* filter, trace_t* tr)
{
	trace_t playerTrace;
	Ray_t ray;
	float smallestFraction = tr->fraction;

	ray.Init(start, end);

	if (!pEntity || !pEntity->IsAlive() || pEntity->IsDormant())
		return;

	if (filter && filter->ShouldHitEntity(pEntity, mask) == false)
		return;

	g_EngineTrace->ClipRayToEntity(ray, mask | CONTENTS_HITBOX, pEntity, &playerTrace);
	if (playerTrace.fraction < smallestFraction)
	{
		// we shortened the ray - save off the trace
		*tr = playerTrace;
		smallestFraction = playerTrace.fraction;
	}
}
bool IsBreakableEntity(C_BaseEntity* entity)
{
	ClientClass* client_class = entity->GetClientClass();

	if (!client_class)
		return false;

	return client_class->m_ClassID == (int)ClassID::CBreakableProp || client_class->m_ClassID == (int)ClassID::CBreakableSurface;
}
bool DidHitNonWorldEntity(C_BaseEntity* entity) { return entity != nullptr && entity->GetIndex() != 0; }

bool TraceToExit(Vector& end, trace_t& tr, Vector start, Vector vEnd, trace_t* trace)
{
	typedef bool(__fastcall* TraceToExitFn)(Vector&, trace_t&, float, float, float, float, float, float, trace_t*);
	static DWORD TraceToExit = U::FindPattern("client.dll", (BYTE*)"\x55\x8B\xEC\x83\xEC\x30\xF3\x0F\x10\x75", "xxxxxxxxxx");

	if (!TraceToExit)
		return false;

	float start_y = start.y, start_z = start.z, start_x = start.x, dir_y = vEnd.y, dir_x = vEnd.x, dir_z = vEnd.z;

	_asm
	{
		push trace
		push dir_z
		push dir_y
		push dir_x
		push start_z
		push start_y
		push start_x
		mov edx, tr
		mov ecx, end
		call TraceToExit
		add esp, 0x1C
	}
}

void MiscFunctions::NormaliseViewAngle(Vector &angle)
{
	while (angle.y <= -180) angle.y += 360;
	while (angle.y > 180) angle.y -= 360;
	while (angle.x <= -180) angle.x += 360;
	while (angle.x > 180) angle.x -= 360;


	if (angle.x > 89.0f)
		angle.x = 89.0f;
	else if (angle.x < -89.0f)
		angle.x = -89.0f;

	if (angle.y > 179.99999f)
		angle.y = 179.99999f;
	else if (angle.y < -179.99999f)
		angle.y = -179.99999f;

	angle.z = 0;
}


char shit[16];
trace_t Trace;
char shit2[16];
C_BaseEntity* entCopy;

bool MiscFunctions::IsVisible(C_BaseEntity* pLocal, C_BaseEntity* pEntity, int BoneID)
{
	if (BoneID < 0) return false;

	entCopy = pEntity;
	Vector start = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector end = GetHitboxPosition(pEntity, BoneID);//pEntity->GetBonePos(BoneID); //pvs fix disabled




	//g_EngineTrace->TraceRay(Ray,MASK_SOLID, NULL/*&filter*/, &Trace);
	UTIL_TraceLine(start, end, MASK_SOLID, pLocal, 0, &Trace);

	if (Trace.m_pEnt == entCopy)
	{
		return true;
	}

	if (Trace.fraction == 1.0f)
	{
		return true;
	}

	return false;

}

bool MiscFunctions::IsKnife(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CKnife || pWeaponClass->m_ClassID == (int)ClassID::CC4 || pWeaponClass->m_ClassID == (int)ClassID::CKnifeGG)
		return true;
	else
		return false;
}

bool MiscFunctions::IsPistol(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CWeaponElite || pWeaponClass->m_ClassID == (int)ClassID::CWeaponFiveSeven || pWeaponClass->m_ClassID == (int)ClassID::CWeaponGlock || pWeaponClass->m_ClassID == (int)ClassID::CWeaponHKP2000 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponP250 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponP228 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponTec9 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponUSP)
		return true;
	else
		return false;
}

bool MiscFunctions::IsRevolver(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CDEagle)
		return true;
	else
		return false;
}

bool MiscFunctions::IsSniper(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CWeaponAWP || pWeaponClass->m_ClassID == (int)ClassID::CWeaponSSG08 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponSCAR20 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponG3SG1)
		return true;
	else
		return false;
}

bool MiscFunctions::IsRifle(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CWeaponFamas || pWeaponClass->m_ClassID == (int)ClassID::CAK47 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponM4A1 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponGalil || pWeaponClass->m_ClassID == (int)ClassID::CWeaponGalilAR || pWeaponClass->m_ClassID == (int)ClassID::CWeaponAug || pWeaponClass->m_ClassID == (int)ClassID::CWeaponSG556)
		return true;
	else
		return false;
}

bool MiscFunctions::IsSmg(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CWeaponMP7 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponMP9 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponUMP45 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponP90 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponBizon || pWeaponClass->m_ClassID == (int)ClassID::CWeaponMAC10)
		return true;
	else
		return false;
}

bool MiscFunctions::IsHeavy(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CWeaponNegev || pWeaponClass->m_ClassID == (int)ClassID::CWeaponM249 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponXM1014 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponNOVA || pWeaponClass->m_ClassID == (int)ClassID::CWeaponMag7 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponSawedoff)
		return true;
	else
		return false;
}

bool MiscFunctions::IsGrenade(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CDecoyGrenade || pWeaponClass->m_ClassID == (int)ClassID::CHEGrenade || pWeaponClass->m_ClassID == (int)ClassID::CIncendiaryGrenade || pWeaponClass->m_ClassID == (int)ClassID::CMolotovGrenade || pWeaponClass->m_ClassID == (int)ClassID::CSensorGrenade || pWeaponClass->m_ClassID == (int)ClassID::CSmokeGrenade || pWeaponClass->m_ClassID == (int)ClassID::CFlashbang)
		return true;
	else
		return false;
}


void SayInChat(const char *text)
{
	char buffer[250];
	sprintf_s(buffer, "say \"%s\"", text);
	g_Engine->ClientCmd_Unrestricted(buffer);
}

float GenerateRandomFloat(float Min, float Max)
{
	float randomized = (float)rand() / (float)RAND_MAX;
	return Min + randomized * (Max - Min);
}





Vector GetHitboxPosition(C_BaseEntity* pEntity, int Hitbox)
{
    matrix3x4 matrix[128];


    if (!pEntity->SetupBones(matrix, 128, 0x00000100, pEntity->GetSimulationTime()))
        return Vector(0, 0, 0);



    studiohdr_t* hdr = g_ModelInfo->GetStudiomodel(pEntity->GetModel());
    mstudiohitboxset_t* set = hdr->GetHitboxSet(0);

    mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

    if (!hitbox)
        return Vector(0, 0, 0);

    Vector vMin, vMax, vCenter, sCenter;
    VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
    VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
    vCenter = (vMin + vMax) *0.5f;
    return vCenter;
}

Vector GetHitboxPositionFromMatrix(C_BaseEntity* pEntity, matrix3x4 matrix[128], int Hitbox)
{

    studiohdr_t* hdr = g_ModelInfo->GetStudiomodel(pEntity->GetModel());
    mstudiohitboxset_t* set = hdr->GetHitboxSet(0);

    mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

    if (!hitbox)
        return Vector(0, 0, 0);

    Vector vMin, vMax, vCenter, sCenter;
    VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
    VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
    vCenter = (vMin + vMax) *0.5f;
    return vCenter;
}
