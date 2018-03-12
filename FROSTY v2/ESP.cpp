
#include "ESP.h"
#include "Interfaces.h"
#include "Render.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include "GrenadePrediction.h"
#include "LagComp.h"
#include "Autowall.h"




visuals::visuals()
{
	BombCarrier = nullptr;
}

int width = 0;
int height = 0;
bool done = false;

float damage;
char bombdamagestringdead[24];
char bombdamagestringalive[24];

void visuals::OnPaintTraverse(C_BaseEntity* local)
{
	NightMode();
	grenade_prediction::instance().Paint();
	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	if (g_Options.Visuals.Crosshair)
		Crosshair(local);

	if (g_Options.Visuals.Hitmarker)
		Hitmarker();

	if (g_Options.Visuals.angleLines && pLocal->IsAlive())
		DrawAngles();

	if (g_Options.Visuals.DrawAwall && pLocal->IsAlive())
		DrawAwall();


	for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
	{

		C_BaseEntity *entity = g_EntityList->GetClientEntity(i);
		if (entity == nullptr)
			continue;
		if (entity == local)
			continue;
		if (entity->IsDormant())
			continue;



		player_info_t pinfo;
		Vector pos, pos3D;
		pos3D = entity->GetOrigin();

		int owner = 0;
		ClientClass* cClass = (ClientClass*)entity->GetClientClass();

		if (!g_Render->WorldToScreen(pos3D, pos))
			continue;



		/*if (strstr(cClass->m_pNetworkName, "Weapon") || cClass->m_ClassID == (int)ClassID::CDEagle || cClass->m_ClassID == (int)ClassID::CAK47 || cClass->m_ClassID == (int)ClassID::CC4 || cClass->m_ClassID == (int)ClassID::CBaseAnimating)
		{
		CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)(entity);

		if (weapon)
		owner = weapon->GetOwnerHandle();
		int ClassID = cClass->m_ClassID;

		if (ClassID == (int)ClassID::CC4)
		{
		// Null it out incase bomb has been dropped or planted
		BombCarrier = nullptr;
		CBaseCombatWeapon *BombWeapon = (CBaseCombatWeapon *)entity;
		Vector vOrig; Vector vScreen;
		vOrig = entity->GetOrigin();
		bool adopted = true;
		auto parent = BombWeapon->GetOwnerHandle();
		if (parent || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
		{
		C_BaseEntity* pParentEnt = (g_EntityList->GetClientEntityFromHandle(parent));
		if (pParentEnt && pParentEnt->IsAlive())
		{
		BombCarrier = pParentEnt;
		adopted = false;
		}
		}
		}

		if (owner == -1)
		{
		if (g_Options.Visuals.Droppedguns)
		{

		if (strstr(entity->GetClientClass()->m_pNetworkName, XorStr("CWeapon")))
		{
		CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)(entity);
		g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, Color(255, 255, 255, 255), FONT_CENTER, "%s" " " "(" "%i" "/" "%i" ")", std::string(entity->GetClientClass()->m_pNetworkName).substr(7).c_str(), weapon->ammo(), weapon->ammo2());
		}
		if (ClassID == 1)
		{
		CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)(entity);
		g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, Color(255, 255, 255, 255), FONT_CENTER, "%s" " " "(" "%i" "/" "%i" ")", XorStr("AK-47"), weapon->ammo(), weapon->ammo2());
		}
		if (ClassID == 39)
		{
		CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)(entity);
		g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, Color(255, 255, 255, 255), FONT_CENTER, "%s" " " "(" "%i" "/" "%i" ")", XorStr("Desert Eagle"), weapon->ammo(), weapon->ammo2());
		}
		if (ClassID == 29)
		{
		g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, Color(255, 255, 255, 255), FONT_CENTER, "%s", XorStr("Dropped C4"));
		}
		if (ClassID == 2)
		{
		g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, Color(255, 255, 255, 255), FONT_CENTER, "%s", XorStr("Defuse Kit"));
		}
		}
		}

		}*/

		if (g_Options.Visuals.Bomb && cClass->m_ClassID == (int)ClassID::CPlantedC4)
		{
			BombCarrier = nullptr;

			Vector vOrig; Vector vScreen;
			vOrig = entity->GetOrigin();
			CCSBomb* Bomb = (CCSBomb*)entity;
			float flBlow = Bomb->GetC4BlowTime();
			float lifetime = flBlow - (g_Globals->interval_per_tick * local->GetTickBase());
			if (g_Render->WorldToScreen(vOrig, vScreen))
			{
				if (local->IsAlive() && !Bomb->IsBombDefused())
				{
					float flDistance = local->GetEyePosition().DistTo(entity->GetEyePosition());
					float a = 450.7f;
					float b = 75.68f;
					float c = 789.2f;
					float d = ((flDistance - b) / c);
					float flDamage = a*exp(-d * d);

					g_Render->DrawString2(g_Render->font.ESPMini, (int)vScreen.x, int(vScreen.y - 7), Color(250, 255, 255, 255), FONT_LEFT, "%iFT", flGetDistance(local->GetOrigin(), vOrig));
					damage = float((std::max)((int)ceilf(CSGO_Armor(flDamage, local->ArmorValue())), 0));

					sprintf_s(bombdamagestringdead, sizeof(bombdamagestringdead) - 1, "Health left: 0 :(");
					sprintf_s(bombdamagestringalive, sizeof(bombdamagestringalive) - 1, "Health left: %.0f", local->GetHealth() - damage);
					if (lifetime > -2.f)
					{
						if (damage >= local->GetHealth())
						{
							g_Render->Text((int)vScreen.x, int(vScreen.y + 10), Color(250, 42, 42, 255), g_Render->font.ESP, bombdamagestringdead);
						}
						else if (local->GetHealth() > damage)
						{
							g_Render->Text((int)vScreen.x, int(vScreen.y + 10), Color(0, 255, 0, 255), g_Render->font.ESP, bombdamagestringalive);
						}
					}
				}
				char buffer[64];
				if (lifetime > 0.01f && !Bomb->IsBombDefused())
				{
					sprintf_s(buffer, "Bomb: %.1f", lifetime);
					g_Render->Text((int)vScreen.x, (int)vScreen.y, Color(250, 42, 42, 255), g_Render->font.ESP, buffer);
				}

			}

			g_Engine->GetScreenSize(width, height);
			int halfX = width / 2;
			int halfY = height / 2;


			if (Bomb->GetBombDefuser() > 0)
			{
				float countdown = Bomb->GetC4DefuseCountDown() - (local->GetTickBase() * g_Globals->interval_per_tick);
				if (countdown > 0.01f)
				{
					if (lifetime > countdown)
					{
						char defuseTimeString[24];
						sprintf_s(defuseTimeString, sizeof(defuseTimeString) - 1, "Defusing: %.1f", countdown);
						g_Render->Text(halfX - 50, halfY + 200, Color(0, 255, 0, 255), g_Render->font.ESP, defuseTimeString);
					}
					else
					{
						g_Render->Text(halfX - 50, halfY + 200, Color(255, 0, 0, 255), g_Render->font.ESP, "No Time :(");
					}
				}
			}
		}

		if (g_Options.Visuals.Grenades)
		{

			if (!g_Render->WorldToScreen(pos3D, pos))
				continue;

			Color GrenadeColor = Color(0, 0, 0, 0);
			char* szModelName = "";
			if (strstr(cClass->m_pNetworkName, XorStr("Projectile")))
			{
				const model_t* pModel = entity->GetModel();
				if (!pModel)
					return;


				const studiohdr_t* pHdr = g_ModelInfo->GetStudiomodel(pModel);
				if (!pHdr)
					return;

				if (!strstr(pHdr->name, XorStr("thrown")) && !strstr(pHdr->name, XorStr("dropped")))
					return;



				IMaterial* mats[32];
				g_ModelInfo->GetModelMaterials(pModel, pHdr->numtextures, mats);

				for (int i = 0; i < pHdr->numtextures; i++)
				{
					IMaterial* mat = mats[i];
					if (!mat)
						continue;

					if (strstr(mat->GetName(), "flashbang"))
					{
						GrenadeColor = Color(255, 255, 0, 255);
						szModelName = "Flashbang";
					}
					else if (strstr(mat->GetName(), "m67_grenade") || strstr(mat->GetName(), "hegrenade"))
					{
						szModelName = "Grenade";
						GrenadeColor = Color(255, 0, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "smoke"))
					{
						szModelName = "Smoke";
						GrenadeColor = Color(0, 255, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "decoy"))
					{
						szModelName = "Decoy";
						GrenadeColor = Color(0, 255, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "incendiary"))
					{
						szModelName = "Incendiary";
						GrenadeColor = Color(255, 0, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "molotov"))
					{
						szModelName = "Molotov";
						GrenadeColor = Color(255, 0, 0, 255);
						break;
					}
				}
				g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, GrenadeColor, FONT_CENTER, "%s", szModelName);
			}
		}

		if (g_Engine->GetPlayerInfo(i, &pinfo) && entity->IsAlive())
		{
			if (g_Options.Legitbot.backtrack)
			{
				if (local->IsAlive())
				{
					for (int t = 0; t < g_Options.Legitbot.backtrackTicks; ++t)
					{
						Vector screenbacktrack[64][12];

						if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimulationTime())
						{
							if (g_Render->WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
							{

								g_Surface->DrawSetColor(Color::Green());
								g_Surface->DrawOutlinedRect(screenbacktrack[i][t].x, screenbacktrack[i][t].y, screenbacktrack[i][t].x + 2, screenbacktrack[i][t].y + 2);

							}
						}
					}
				}
				else
				{
					memset(&headPositions[0][0], 0, sizeof(headPositions));
				}
			}
			if (g_Options.Ragebot.PosAdjust)
			{
				if (local->IsAlive())
				{
					for (int t = 0; t < 12; ++t)
					{
						Vector screenbacktrack[64][12];

						if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimulationTime())
						{
							if (g_Render->WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
							{

								g_Surface->DrawSetColor(Color::Green());
								g_Surface->DrawOutlinedRect(screenbacktrack[i][t].x, screenbacktrack[i][t].y, screenbacktrack[i][t].x + 2, screenbacktrack[i][t].y + 2);

							}
						}
					}
				}
				else
				{
					memset(&headPositions[0][0], 0, sizeof(headPositions));
				}
			}
			if (g_Options.Ragebot.FakeLagFix)
			{
				if (local->IsAlive())
				{
					Vector screenbacktrack[64];

					if (backtracking->records[i].tick_count + 12 > g_Globals->tickcount)
					{
						if (g_Render->WorldToScreen(backtracking->records[i].headPosition, screenbacktrack[i]))
						{

							g_Surface->DrawSetColor(Color::Black());
							g_Surface->DrawLine(screenbacktrack[i].x, screenbacktrack[i].y, screenbacktrack[i].x + 2, screenbacktrack[i].y + 2);

						}
					}
				}
				else
				{
					memset(&backtracking->records[0], 0, sizeof(backtracking->records));
				}
			}

			if (!g_Render->WorldToScreen(pos3D, pos))
				continue;

			Color clr = entity->GetTeamNum() == local->GetTeamNum() ?
				Color(g_Options.Colors.TeamESP[0] * 255, g_Options.Colors.TeamESP[1] * 255, g_Options.Colors.TeamESP[2] * 255, 255) :
				Color(g_Options.Colors.EnemyESP[0] * 255, g_Options.Colors.EnemyESP[1] * 255, g_Options.Colors.EnemyESP[2] * 255, 255);
			if (entity->GetTeamNum() == local->GetTeamNum() && !g_Options.Visuals.TeamESP)
				continue;
			if (!entity->IsAlive())
				continue;

			bool PVS = false;
			RECT rect = DynamicBox(entity, PVS, local);

			DrawInfo(rect, entity, local);

			if (g_Options.Visuals.Box)
			{
				switch (g_Options.Visuals.BoxType)
				{
				case 0:
					DrawBox(rect, clr);
					break;
				case 1:
					DrawCorners(rect, clr);
					break;
				case 2:
					ThreeDBox(entity->GetCollideable()->OBBMins(), entity->GetCollideable()->OBBMaxs(), entity->GetOrigin(), clr);
					break;
				}
			}
			if (g_Options.Visuals.AimLine)
				DrawSnapLine(Vector(rect.left + ((rect.right - rect.left) / 2), rect.bottom, 0), clr);
			if (g_Options.Visuals.Skeleton)
				Skeleton(entity, Color(255, 255, 255, 255));
			if (g_Options.Visuals.health)
				DrawHealth(rect, entity);
			if (g_Options.Visuals.barrel)
				BulletTrace(entity, clr);
		}


	}
}

void visuals::DrawBox(RECT rect, Color Col)
{
	g_Render->DrawOutlinedRect(rect.left - 1, rect.top - 1, rect.right - rect.left + 2, rect.bottom - rect.top + 2, Color(0, 0, 0, 150));
	g_Render->DrawOutlinedRect(rect.left + 1, rect.top + 1, rect.right - rect.left - 2, rect.bottom - rect.top - 2, Color(0, 0, 0, 125));
	g_Render->DrawOutlinedRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, Col);
}

void visuals::DrawCorners(RECT rect, Color Col)
{
	int x1, y1, x2, y2, w, h;
	x1 = rect.left;
	y1 = rect.top;
	x2 = rect.right;
	y2 = rect.bottom;

	w = x2;
	h = y2;

	int Line_Size = (y1 - h) / 6;
	int Line_Size2 = (y1 - h) / 6;

	int red = 0;
	int green = 0;
	int blue = 0;
	int alpha = 0;
	Col.GetColor(red, green, blue, alpha);
	g_Surface->DrawSetColor(red, green, blue, alpha);

	//top inwards
	g_Surface->DrawLine(w, y1, w + Line_Size, y1);
	g_Surface->DrawLine(x1, y1, x1 - Line_Size, y1);

	//top downwards
	g_Surface->DrawLine(x1, y1, x1, y1 - Line_Size);
	g_Surface->DrawLine(w, y1, w, y1 - Line_Size);

	//bottom inwards
	g_Surface->DrawLine(x1, h, x1 - Line_Size, h);
	g_Surface->DrawLine(w, h, w + Line_Size, h);

	//bottom upwards
	g_Surface->DrawLine(x1, h, x1, h + Line_Size);
	g_Surface->DrawLine(w, h, w, h + Line_Size);

	//outlines

	g_Surface->DrawSetColor(0, 0, 0, 200);

	//top inwards
	g_Surface->DrawLine(w, y1 - 1, w + Line_Size, y1 - 1);
	g_Surface->DrawLine(x1, y1 - 1, x1 - Line_Size, y1 - 1);
	//inlines
	g_Surface->DrawLine(w - 1, y1 + 1, w + Line_Size, y1 + 1);
	g_Surface->DrawLine(x1 + 1, y1 + 1, x1 - Line_Size, y1 + 1);

	// top downwards
	g_Surface->DrawLine(x1 - 1, y1 - 1, x1 - 1, y1 - Line_Size);
	g_Surface->DrawLine(w + 1, y1 - 1, w + 1, y1 - Line_Size);
	//inlines
	g_Surface->DrawLine(x1 + 1, y1, x1 + 1, y1 - Line_Size);
	g_Surface->DrawLine(w - 1, y1, w - 1, y1 - Line_Size);

	//bottom inwards
	g_Surface->DrawLine(x1, h + 1, x1 - Line_Size, h + 1);
	g_Surface->DrawLine(w, h + 1, w + Line_Size, h + 1);
	//inlines
	g_Surface->DrawLine(x1 + 1, h - 1, x1 - Line_Size, h - 1);
	g_Surface->DrawLine(w - 1, h - 1, w + Line_Size, h - 1);

	//bottom upwards
	g_Surface->DrawLine(x1 - 1, h + 1, x1 - 1, h + Line_Size);
	g_Surface->DrawLine(w + 1, h + 1, w + 1, h + Line_Size);
	//inlines
	g_Surface->DrawLine(x1 + 1, h, x1 + 1, h + Line_Size);
	g_Surface->DrawLine(w - 1, h, w - 1, h + Line_Size);
}

void visuals::ThreeDBox(Vector minin, Vector maxin, Vector pos, Color Col)
{
	Vector min = minin + pos;
	Vector max = maxin + pos;

	Vector corners[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(min.x, min.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(max.x, max.y, max.z),
		Vector(max.x, min.y, max.z) };


	int edges[12][2] = { { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 },{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 }, };

	for (const auto edge : edges)
	{
		Vector p1, p2;
		if (!g_Render->WorldToScreen(corners[edge[0]], p1) || !g_Render->WorldToScreen(corners[edge[1]], p2))
			return;
		int red = 0;
		int green = 0;
		int blue = 0;
		int alpha = 0;
		Col.GetColor(red, green, blue, alpha);
		g_Surface->DrawSetColor(red, green, blue, alpha);
		g_Surface->DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void visuals::DrawInfo(RECT rect, C_BaseEntity* pPlayer, C_BaseEntity* local)
{
	player_info_t info;
	static class Text
	{
	public:
		std::string text;
		int side;
		int Font;
		Color color;

		Text(std::string text, int side, int Font, Color color) : text(text), side(side), Font(Font), color(color)
		{
		}
	};
	std::vector< Text > texts;
	if (pPlayer->GetClientClass()->m_ClassID == 83 || pPlayer->GetClientClass()->m_ClassID == 84)
	{
		if (g_Options.Visuals.Name)
			texts.push_back(Text("Hostage", 0, g_Render->font.ESP, Color(255, 255, 255, 255)));
	}
	else if (g_Engine->GetPlayerInfo(pPlayer->GetIndex(), &info))
	{
		if (g_Options.Visuals.Flashed && pPlayer == BombCarrier)
			texts.push_back(Text("Bomb Carrier", 0, g_Render->font.ESP, Color(255, 220, 220, 255)));

		if (g_Options.Visuals.Flashed && pPlayer->IsFlashed())
			texts.push_back(Text("Flashed", 0, g_Render->font.ESP, Color(255, 255, 183, 255)));
		if (g_Options.Visuals.Name)
			texts.push_back(Text(info.name, 0, g_Render->font.ESP, Color(255, 255, 255, 255)));

		if (g_Options.Visuals.resolveMode)
		{
			if (Globals::resolvemode == 1)
			{
				texts.push_back(Text(std::string("Resolver: Bruteforce"), 0, g_Render->font.ESP, Color(200, 200, 200, 255)));
			}
			else if (Globals::resolvemode == 2)
			{
				texts.push_back(Text(std::string("Resolver: Predicting LBY"), 0, g_Render->font.ESP, Color(200, 200, 200, 255)));
			}
			else if (Globals::resolvemode == 3)
			{
				texts.push_back(Text(std::string("Resolver: LBY Update"), 0, g_Render->font.ESP, Color(200, 200, 200, 255)));
			}
			else if (Globals::resolvemode == 4)
			{
				texts.push_back(Text(std::string("Resolver: Legit Player"), 0, g_Render->font.ESP, Color(200, 200, 200, 255)));
			}
		}
		if (g_Options.Visuals.Distance)
			texts.push_back(Text(std::to_string(flGetDistance(local->GetOrigin(), pPlayer->GetOrigin())) + std::string("FT"), 2, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
		if (g_Options.Visuals.Callout)
			texts.push_back(Text(pPlayer->GetCallout(), 1, g_Render->font.ESP, Color(255, 220, 220, 255)));

		CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(pPlayer->GetActiveWeaponHandle());
		if (weapon)
		{
			if (g_Options.Visuals.Weapon && weapon)
				switch (g_Options.Visuals.wpnmode)
				{
				case 0:
					texts.push_back(Text(weapon->GetGunName() + std::string("[") + std::to_string(weapon->ammo()) + std::string("|") + std::to_string(weapon->ammo2()) + std::string("]"), 2, g_Render->font.ESP, Color(255, 255, 255, 255)));
					break;
				case 1:
					//texts.push_back(Text(weapon->GetGunIcon(), 2, 0xA1, CColor(255, 255, 255, 255)));
					//texts.push_back(Text(string("(") + std::to_string(weapon->ammo()) + string("/") + std::to_string(weapon->ammo2()) + string(")"), 2, Hacks.Font_Health, CColor(255, 255, 255, 255)));
					break;
				}
			if (g_Options.Visuals.Flashed && pPlayer->IsScoped())
				texts.push_back(Text("Scoped", 2, g_Render->font.ESP, Color(121, 252, 250, 255)));
			if (g_Options.Visuals.Flashed && weapon->IsInReload())
				texts.push_back(Text("Reloading", 2, g_Render->font.ESP, Color(121, 252, 250, 255)));
			if (g_Options.Visuals.Armor)
				texts.push_back(Text(pPlayer->GetArmorName(), 1, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
			if (g_Options.Visuals.Money)
				texts.push_back(Text(std::string("$") + std::to_string(pPlayer->iAccount()), 1, g_Render->font.ESP, Color(71, 132, 60, 255)));
		}
	}

	int middle = ((rect.right - rect.left) / 2) + rect.left;
	int Top[3] = { rect.top,rect.top, rect.bottom };
	for (auto text : texts)
	{
		RECT nameSize = g_Render->GetTextSize(text.Font, (char*)text.text.c_str());
		switch (text.side)
		{
		case 0:
			Top[0] -= nameSize.bottom + 1;
			g_Render->DrawString2(text.Font, middle, Top[0] + 6, text.color, FONT_CENTER, (char*)text.text.c_str());
			break;
		case 1:
			g_Render->DrawString2(text.Font, rect.right + 2, Top[1] + 6, text.color, FONT_LEFT, (char*)text.text.c_str());
			Top[1] += nameSize.bottom - 4;
			break;
		case 2:
			g_Render->DrawString2(text.Font, middle, Top[2] + 6, text.color, FONT_CENTER, (char*)text.text.c_str());
			Top[2] += nameSize.bottom - 4;
			break;
		}
	}
}

void visuals::DrawAwall()
{
	int MidX;
	int MidY;
	g_Engine->GetScreenSize(MidX, MidY);

	int damage;
	if (CanWallbang(damage))
	{
		g_Render->OutlineCircle(MidX / 2, MidY / 2, 10, 10, Color(0, 255, 0));
		g_Render->Textf(MidX / 2, MidY / 2 + 6, Color(255, 255, 255, 255), g_Render->font.ESP, "DMG: %1i", damage);
	}
	else
	{
		g_Render->OutlineCircle(MidX / 2, MidY / 2, 10, 10, Color(255, 0, 0));
		g_Render->Textf(MidX / 2, MidY / 2 + 6, Color(255, 255, 255, 255), g_Render->font.ESP, "DMG: 0");
	}
}

void visuals::DrawAngles()
{
	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	filter.pSkip = pLocal;

	/*AngleVectors(QAngle(0, pLocal->GetLowerBodyYaw(), 0), &forward);
	src3D = pLocal->GetOrigin();
	dst3D = src3D + (forward * 35.f); //replace 50 with the length you want the line to have

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
	return;

	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(255, 165, 0, 255));
	g_Render->Text(dst.x, dst.y, Color(255, 165.f, 0, 255), g_Render->font.ESP, "lby");*/

	AngleVectors(QAngle(0, Globals::RealAngle, 0), &forward);
	src3D = pLocal->GetOrigin();
	dst3D = src3D + (forward * 45.f);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;

	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(0, 255, 0, 255));
	g_Render->Text(dst.x, dst.y, Color(0, 255, 0, 255), g_Render->font.ESP, "REAL");

	AngleVectors(QAngle(0, Globals::FakeAngle, 0), &forward);
	dst3D = src3D + (forward * 45.f);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;

	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(255, 0, 0, 255));
	g_Render->Text(dst.x, dst.y, Color(255, 0, 0, 255), g_Render->font.ESP, "FAKE");
}

RECT visuals::DynamicBox(C_BaseEntity* pPlayer, bool& PVS, C_BaseEntity* local)
{
	Vector trans = pPlayer->GetOrigin();

	Vector min;
	Vector max;

	min = pPlayer->GetCollideable()->OBBMins();
	max = pPlayer->GetCollideable()->OBBMaxs();

	Vector pointList[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector Distance = pointList[0] - pointList[1];
	int dst = Distance.Length();
	dst /= 1.3f;
	Vector angs;
	CalcAngle(trans, local->GetEyePosition(), angs);

	Vector all[8];
	angs.y += 45;
	for (int i = 0; i < 4; i++)
	{
		AngleVectors(angs, &all[i]);
		all[i] *= dst;
		all[i + 4] = all[i];
		all[i].z = max.z;
		all[i + 4].z = min.z;
		VectorAdd(all[i], trans, all[i]);
		VectorAdd(all[i + 4], trans, all[i + 4]);
		angs.y += 90;
	}

	Vector flb, brt, blb, frt, frb, brb, blt, flt;
	PVS = true;

	if (!g_DebugOverlay->ScreenPosition(all[3], flb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[0], blb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[2], frb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[6], blt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[5], brt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[4], frt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[1], brb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[7], flt))
		PVS = false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
	}
	RECT rect;
	rect.left = left;
	rect.bottom = bottom;
	rect.right = right;
	rect.top = top;
	return rect;
}

void visuals::BulletTrace(C_BaseEntity* pEntity, Color color)
{
	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;
	Vector eyes = *pEntity->GetEyeAngles();

	AngleVectors(eyes, &forward);
	filter.pSkip = pEntity;
	src3D = pEntity->GetBonePos(6) - Vector(0, 0, 0);
	dst3D = src3D + (forward * g_Options.Visuals.barrelL);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;


	g_Render->Line(src.x, src.y, dst.x, dst.y, color);
	g_Render->DrawOutlinedRect(dst.x - 3, dst.y - 3, 6, 6, color);
};

void visuals::Skeleton(C_BaseEntity* pEntity, Color Col)
{

	studiohdr_t* pStudioHdr = g_ModelInfo->GetStudiomodel(pEntity->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);

		if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
		{
			vChild = pEntity->GetBonePos(j);
			vParent = pEntity->GetBonePos(pBone->parent);
			g_DebugOverlay->ScreenPosition(vParent, sParent);
			g_DebugOverlay->ScreenPosition(vChild, sChild);
			g_Render->Line(sParent[0], sParent[1], sChild[0], sChild[1], Col);
		}
	}

}

void visuals::DrawSnapLine(Vector to, Color clr)
{
	int width = 0;
	int height = 0;
	g_Engine->GetScreenSize(width, height);
	Vector From((width / 2), height - 1, 0);
	g_Render->Line(From.x, From.y, to.x, to.y, clr);
}

void visuals::DrawHealth(RECT rect, C_BaseEntity* pPlayer)
{
	float HealthValue = pPlayer->GetHealth();

	float HealthValue2 = pPlayer->GetHealth();
	if (HealthValue2 > 100)
		HealthValue2 = 100;

	char hp[256];
	sprintf(hp, "%.0f", HealthValue);
	int Red = 255 - (HealthValue2 * 2.55);
	int Green = HealthValue2 * 2.55;
	float height = (rect.bottom - rect.top) * (HealthValue2 / 100);
	g_Render->GradientH(rect.left - 9, rect.top - 1, 6, rect.bottom - rect.top + 2, Color(0, 0, 0, 150), Color(0, 0, 0, 150));
	g_Render->GradientH(rect.left - 8, rect.bottom - height, 4, height, Color(Red, Green, 0, 255), Color(Red, Green, 0, 255));
	g_Render->DrawOutlinedRect(rect.left - 9, rect.top - 1, 6, rect.bottom - rect.top + 2, Color(0, 0, 0, 255));
	g_Render->DrawString2(g_Render->font.ESPMini, rect.left - 6, rect.bottom - height + 1, Color(255, 255, 255, 255), FONT_CENTER, hp);
}


void visuals::Hitmarker()
{
	if (G::hitmarkeralpha < 0.f)
		G::hitmarkeralpha = 0.f;
	else if (G::hitmarkeralpha > 0.f)
		G::hitmarkeralpha -= 0.01f;

	int W, H;
	g_Engine->GetScreenSize(W, H);

	if (G::hitmarkeralpha > 0.f)
	{
		g_Render->Line(W / 2 - 10, H / 2 - 10, W / 2 - 5, H / 2 - 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 - 10, H / 2 + 10, W / 2 - 5, H / 2 + 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 + 10, H / 2 - 10, W / 2 + 5, H / 2 - 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 + 10, H / 2 + 10, W / 2 + 5, H / 2 + 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));

	}
}

void visuals::Crosshair(C_BaseEntity* local)
{
	g_Engine->GetScreenSize(width, height);
	if (local  && local->IsAlive())
	{
		static Vector ViewAngles;
		g_Engine->GetViewAngles(ViewAngles);
		ViewAngles += local->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

		static Vector fowardVec;
		AngleVectors(ViewAngles, &fowardVec);
		fowardVec *= 10000;

		// Get ray start / end
		Vector start = local->GetOrigin() + local->GetViewOffset();
		Vector end = start + fowardVec, endScreen;

		CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(local->GetActiveWeaponHandle());
		float cone = pWeapon->GetSpread() + pWeapon->GetInaccuracy();
		if (cone > 0.0f)
		{
			if (cone < 0.01f) cone = 0.01f;
			float size = (cone * height) * 0.7f;
			Color color(255, 255, 255, 100);

			if (g_Render->WorldToScreen(end, endScreen))
			{
				g_Render->OutlineCircle(endScreen.x, endScreen.y, (int)size, 100, color);
			}
		}
	}
}

void visuals::DLight(C_BaseEntity *local, C_BaseEntity* entity)
{
	player_info_t pinfo;
	if (local && entity && entity != local)
	{
		if (g_Engine->GetPlayerInfo(entity->GetIndex(), &pinfo) && entity->IsAlive() && !entity->IsDormant())
		{
			if (local->GetTeamNum() != entity->GetTeamNum())
			{
				dlight_t* pElight = g_Dlight->CL_AllocElight(entity->GetIndex());
				pElight->origin = entity->GetOrigin() + Vector(0.0f, 0.0f, 35.0f);
				pElight->radius = 300.0f;
				pElight->color.b = 36;
				pElight->color.g = 224;
				pElight->color.r = 41;
				pElight->die = g_Globals->curtime + 0.05f;
				pElight->decay = pElight->radius / 5.0f;
				pElight->key = entity->GetIndex();

				dlight_t* pDlight = g_Dlight->CL_AllocDlight(entity->GetIndex());
				pDlight->origin = entity->GetOrigin();
				pDlight->radius = 300.0f;
				pDlight->color.b = 36;
				pDlight->color.g = 224;
				pDlight->color.r = 41;
				pDlight->die = g_Globals->curtime + 0.05f;
				pDlight->decay = pDlight->radius; // / 5.0f;
				pDlight->key = entity->GetIndex();
			}
		}
	}
}

void visuals::NightMode()
{
	if (g_Options.Misc.nightMode)
	{
		if (!done)
		{


			static auto sv_skyname = g_CVar->FindVar("sv_skyname");
			static auto r_DrawSpecificStaticProp = g_CVar->FindVar("r_DrawSpecificStaticProp");
			r_DrawSpecificStaticProp->SetValue(1);
			sv_skyname->SetValue("sky_csgo_night02");

			for (MaterialHandle_t i = g_MaterialSystem->FirstMaterial(); i != g_MaterialSystem->InvalidMaterial(); i = g_MaterialSystem->NextMaterial(i))
			{
				IMaterial *pMaterial = g_MaterialSystem->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{
					pMaterial->ColorModulate(0.10, 0.10, 0.10);
				}
				if (strstr(group, "StaticProp"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}

				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				done = true;
			}

		}
	}
	else
	{
		if (done)
		{
			for (MaterialHandle_t i = g_MaterialSystem->FirstMaterial(); i != g_MaterialSystem->InvalidMaterial(); i = g_MaterialSystem->NextMaterial(i))
			{
				IMaterial *pMaterial = g_MaterialSystem->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "StaticProp"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
			}
			done = false;
		}
	}
}
