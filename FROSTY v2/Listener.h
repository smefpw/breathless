#pragma once
#include "singleton.hpp"
#include "MiscClasses.h"
#include "Interfaces.h"
#include "Interface.h"
#include "Sounds.h"
#include "Logging.h"

#pragma comment(lib, "winmm.lib")
		class item_purchase

			: public singleton<item_purchase>
		{
			class item_purchase_listener
				: public IGameEventListener2
			{
			public:
				void start()
				{
					g_EventManager->AddListener(this, "item_purchase", false);
					g_EventManager->AddListener(this, "player_hurt", false);
				}
				void stop()
				{
					g_EventManager->RemoveListener(this);
				}
				void FireGameEvent(IGameEvent *event) override
				{
					singleton()->on_fire_event(event, false);
				}
				int GetEventDebugID(void) override
				{
					return 42 /*0x2A*/;
				}
			};

		public:

			static item_purchase* singleton()
			{
				static item_purchase* instance = new item_purchase;
				return instance;
			}

			void initialize()
			{
				listener.start();
			}

			void remove()
			{
				listener.stop();
			}

			void on_fire_event(IGameEvent* event, bool drawing)
			{
				static AppLog log;
				if (drawing)
				{
					log.Draw("Event Log");
				}

				if (!drawing)
				{
					C_BaseEntity* local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
					if (!strcmp(event->GetName(), "item_purchase"))
					{
						auto buyer = event->GetInt("userid");
						std::string gun = event->GetString("weapon");

						if (strstr(gun.c_str(), "molotov")
							|| strstr(gun.c_str(), "nade")
							|| strstr(gun.c_str(), "kevlar")
							|| strstr(gun.c_str(), "decoy")
							|| strstr(gun.c_str(), "suit")
							|| strstr(gun.c_str(), "flash")
							|| strstr(gun.c_str(), "vest")
							|| strstr(gun.c_str(), "cutter")
							|| strstr(gun.c_str(), "defuse")
							)  return;
						auto player_index = g_Engine->GetPlayerForUserID(buyer);
						C_BaseEntity* player = (C_BaseEntity*)g_EntityList->GetClientEntity(player_index);
						player_info_t pinfo;

						if (player && local && g_Engine->GetPlayerInfo(player_index, &pinfo))
						{
							gun.erase(gun.find("weapon_"), 7);
							if (player->GetTeamNum() == local->GetTeamNum())
							{
								log.AddLog("[Team] ""%s bought a %s\n", pinfo.name, gun.c_str());

							}
							else
							{
								log.AddLog("[Enemy] ""%s bought a %s\n", pinfo.name, gun.c_str());
							}

						}
					}

					if (!strcmp(event->GetName(), "player_hurt"))
					{
						int deadfag = event->GetInt("userid");
						int attackingfag = event->GetInt("attacker");
						C_BaseEntity* pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
						if (g_Engine->GetPlayerForUserID(deadfag) != g_Engine->GetLocalPlayer() && g_Engine->GetPlayerForUserID(attackingfag) == g_Engine->GetLocalPlayer())
						{
							C_BaseEntity* hittedplayer = (C_BaseEntity*)(g_Engine->GetPlayerForUserID(deadfag));
							int hit = event->GetInt("hitgroup");
							if (hit >= 0 && hittedplayer && deadfag && attackingfag)
							{
								Globals::missedshots++;
							}
							else
							{
								Globals::missedshots++;
							}
						}
					}

					if (!strcmp(event->GetName(), "player_hurt"))
					{
						auto bitch = event->GetInt("userid");
						auto coolguy49 = event->GetInt("attacker");
						int dmg = event->GetInt("dmg_health");


						auto bitch_index = g_Engine->GetPlayerForUserID(bitch);
						auto coolguy49_index = g_Engine->GetPlayerForUserID(coolguy49);
						C_BaseEntity* bitch_ = (C_BaseEntity*)g_EntityList->GetClientEntity(bitch_index);
						C_BaseEntity* coolguy49_ = (C_BaseEntity*)g_EntityList->GetClientEntity(coolguy49_index);
						player_info_t bitch_info;
						player_info_t coolguy49_info;

						if (coolguy49_ == local)
						{
							G::hitmarkeralpha = 1.f;
							switch (g_Options.Visuals.Hitsound)
							{
							case 0: break;
							case 1: PlaySoundA(rawData, NULL, SND_ASYNC | SND_MEMORY); break; // Default
							case 2:	PlaySoundA(roblox, NULL, SND_ASYNC | SND_MEMORY); break; // Anime
							case 3:	PlaySoundA(china, NULL, SND_ASYNC | SND_MEMORY); break; // CHINA
							case 4: PlaySoundA(skeethitmarker_wav, NULL, SND_ASYNC | SND_MEMORY); break; // Skeet
							}

						}

						if (bitch && local && g_Engine->GetPlayerInfo(bitch_index, &bitch_info), g_Engine->GetPlayerInfo(coolguy49_index, &coolguy49_info) && bitch_ && coolguy49_)
						{
							log.AddLog("[Dmg] ""%s did %i to %s\n", coolguy49_info.name, dmg, bitch_info.name);
						}
					}
				}
			}
		private:
			item_purchase_listener  listener;
		};

		item_purchase purchase;