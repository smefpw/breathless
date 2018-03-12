

#pragma once

#include "entities.h"
#include "SDK.h"
#include "singleton.hpp"

Vector GetAutostrafeView();

class misc
	: public singleton<misc>
{
public:
	void OnCreateMove(CInput::CUserCmd *cmd, C_BaseEntity *local);

	static void AutoStrafe(CInput::CUserCmd *cmd, C_BaseEntity *local, QAngle oldangles);

	static void misc::FakeWalk(CInput::CUserCmd* pCmd, bool &bSendPacket, C_BaseEntity *local);


	//void Slowmo(CInput::CUserCmd *pCmd, bool &bSendPacket);
};
template<class T, class U>
inline T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}

inline float bitsToFloat(unsigned long i)
{
	return *reinterpret_cast<float*>(&i);
}


inline float FloatNegate(float f)
{
	return bitsToFloat(FloatBits(f) ^ 0x80000000);
}

inline void SetName(const char* new_name)
{
	static auto name = g_CVar->FindVar("name");

	name->SetValue(new_name);
	*reinterpret_cast<int*>(uintptr_t(&name->fnChangeCallback) + 0xC) = 0;
}
inline void setclantag(const char* tag)
{
	static auto ClanTagOffset = U::FindPattern("engine.dll", (PBYTE)"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15", "xxxxxxxxx");
	if (ClanTagOffset)
	{
		auto tag_ = std::string(tag);
		if (strlen(tag) > 0) {
			auto newline = tag_.find("\\n");
			auto tab = tag_.find("\\t");
			if (newline != std::string::npos) {
				tag_.replace(newline, newline + 2, "\n");
			}
			if (tab != std::string::npos) {
				tag_.replace(tab, tab + 2, "\t");
			}
		}
		static auto dankesttSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(ClanTagOffset);
		dankesttSetClanTag(tag_.data(), tag_.data());
	}
}
inline void RankReveal(CInput::CUserCmd* cmd)
{
	if (cmd->buttons & IN_SCORE)
	{
		static auto ServerRankRevealAll = (bool(__cdecl*)(int*))((PDWORD)U::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xxxxx????x????"));
		if (ServerRankRevealAll)
		{
			static int fArray[3] = { 0,0,0 };
			ServerRankRevealAll(fArray);
		}
	}
}