#pragma once
#include "HookIncludes.h"
using do_post_screen_space_effects_t = bool(__thiscall*)(void*, CViewSetup*);



bool _fastcall hkDoPostScreenSpaceEffects(void* ecx, void* edx, CViewSetup* pSetup)
{
	static auto ofunc = hooks::clientmode.get_original<do_post_screen_space_effects_t>(44);

	IMaterial *pMatGlowColor = g_MaterialSystem->FindMaterial("dev/glow_color", TEXTURE_GROUP_OTHER, true);
	g_ModelRender->ForcedMaterialOverride(pMatGlowColor);

	if (g_GlowObjManager && g_Engine->IsConnected())
	{
		auto local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
		if (local)
		{
			for (int i = 0; i < g_GlowObjManager->m_GlowObjectDefinitions.Count(); ++i)
			{
				if (g_GlowObjManager->m_GlowObjectDefinitions[i].IsUnused() || !g_GlowObjManager->m_GlowObjectDefinitions[i].getEnt())
					continue;

				CGlowObjectManager::GlowObjectDefinition_t* glowEnt = &g_GlowObjManager->m_GlowObjectDefinitions[i];

				switch (glowEnt->getEnt()->GetClientClass()->m_ClassID)
				{
				default:
					if (strstr(glowEnt->getEnt()->GetClientClass()->m_pNetworkName, ("CWeapon")) && g_Options.Visuals.weaponglow)
						glowEnt->set(g_Options.Colors.WeaponGlow[0], g_Options.Colors.WeaponGlow[1], g_Options.Colors.WeaponGlow[2], g_Options.Visuals.weaponglowalpha / 255.f);
					break;
				case 1:
					if (g_Options.Visuals.weaponglow)
						glowEnt->set(g_Options.Colors.WeaponGlow[0], g_Options.Colors.WeaponGlow[1], g_Options.Colors.WeaponGlow[2], g_Options.Visuals.weaponglowalpha / 255.f);
					break;
				case 35:
					if (g_Options.Visuals.glowplayer)
					{
						if (!g_Options.Visuals.teamglow && glowEnt->getEnt()->GetTeamNum() == local->GetTeamNum())
							break;

						if (glowEnt->getEnt()->GetTeamNum() == local->GetTeamNum())
							glowEnt->set(g_Options.Colors.TeamGlow[0], g_Options.Colors.TeamGlow[1], g_Options.Colors.TeamGlow[2], g_Options.Visuals.playerglowalpha / 255.f);
						else if (glowEnt->getEnt()->GetTeamNum() != local->GetTeamNum())
							glowEnt->set(g_Options.Colors.EnemyGlow[0], g_Options.Colors.EnemyGlow[1], g_Options.Colors.EnemyGlow[2], g_Options.Visuals.playerglowalpha / 255.f);
					}
					break;
				case 39:
					if (g_Options.Visuals.weaponglow)
						glowEnt->set(g_Options.Colors.WeaponGlow[0], g_Options.Colors.WeaponGlow[1], g_Options.Colors.WeaponGlow[2], g_Options.Visuals.weaponglow / 255.f);
					break;
				case 29:
					if (g_Options.Visuals.bombglow)
						glowEnt->set(g_Options.Colors.C4glow[0], g_Options.Colors.C4glow[1], g_Options.Colors.C4glow[2], g_Options.Visuals.bombglowalpha / 255.f);
					break;
				case 105:
					if (g_Options.Visuals.bombglow)
						glowEnt->set(g_Options.Colors.C4glow[0], g_Options.Colors.C4glow[1], g_Options.Colors.C4glow[2], g_Options.Visuals.bombglowalpha / 255.f);
					break;
				}
			}
		}
	}
	return ofunc(ecx, pSetup);
}