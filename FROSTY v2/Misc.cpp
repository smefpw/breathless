#include "Misc.h"
#include "Interfaces.h"
#include "Render.h"
#include <time.h>
#include "BaseClient.h"
#include "Strafer.h"

std::string animatedclantag;
int iLastTime;
bool bDone = false;
bool sliding = false;
int switchstate = 3;
bool positive = true;
void misc::OnCreateMove(CInput::CUserCmd *cmd, C_BaseEntity *local)
{

	if (g_Options.Misc.Bhop && local->IsAlive())
	{
		if (cmd->buttons & IN_JUMP && !(local->GetMoveType() & MOVETYPE_LADDER))
		{

			int iFlags = local->GetFlags();
			if (!(iFlags & FL_ONGROUND))
				cmd->buttons &= ~IN_JUMP;
		}
	}

	if (g_Options.Misc.moonwalk)
	{
		if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
			return;

		if (cmd->buttons & IN_FORWARD && cmd->buttons & IN_BACK)
		{
			cmd->forwardmove = 0.f;
		}
		else if (cmd->buttons & IN_FORWARD)
		{
			cmd->buttons &= ~IN_FORWARD;
			cmd->buttons |= IN_BACK;
			cmd->forwardmove = 450.f;
		}
		else if (cmd->buttons & IN_BACK)
		{
			cmd->buttons &= ~IN_BACK;
			cmd->buttons |= IN_FORWARD;
			cmd->forwardmove = -450.f;
		}

		if (cmd->buttons & IN_MOVELEFT && cmd->buttons & IN_MOVERIGHT)
		{
			cmd->sidemove = 0.f;
		}
		else if (cmd->buttons & IN_MOVELEFT)
		{
			cmd->buttons &= ~IN_MOVELEFT;
			cmd->buttons |= IN_MOVERIGHT;
			cmd->sidemove = -450.f;
		}
		else if (cmd->buttons & IN_MOVERIGHT)
		{
			cmd->buttons &= ~IN_MOVERIGHT;
			cmd->buttons |= IN_MOVELEFT;
			cmd->sidemove = 450.f;
		}
	}

	if (g_Options.Misc.spookwalk)
	{
		
			if (switchstate == 3) positive = true;
			if (switchstate == -3) positive = false;

			if (positive)
			{
				switchstate -= 1;
			}
			else
			{
				switchstate += 1;
			}

			if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP || cmd->buttons & IN_JUMP)
				return;

			if (cmd->buttons & IN_FORWARD && cmd->buttons & IN_BACK)
			{
				cmd->sidemove = 0.f;
			}
			if (cmd->buttons & IN_MOVELEFT && cmd->buttons & IN_MOVERIGHT)
			{
				cmd->forwardmove = 0.f;
			}

			if (cmd->buttons & IN_FORWARD && !(cmd->buttons & IN_BACK || cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT))
			{
				if (switchstate < 0)
				{

					cmd->sidemove = -450.f;
				}
				else if (switchstate > 0)
				{

					cmd->sidemove = 450.f;
				}
			}

			if (cmd->buttons & IN_BACK && !(cmd->buttons & IN_FORWARD || cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT))
			{
				if (switchstate < 0)
				{

					cmd->sidemove = -450.f;
				}
				else if (switchstate > 0)
				{

					cmd->sidemove = 450.f;
				}
			}

			if (cmd->buttons & IN_MOVELEFT && !(cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK || cmd->buttons & IN_MOVERIGHT))
			{
				if (switchstate < 0)
				{
					cmd->forwardmove = -450.f;
				}
				else if (switchstate > 0)
				{
					cmd->forwardmove = 450.f;
				}
			}

			if (cmd->buttons & IN_MOVERIGHT && !(cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK || cmd->buttons & IN_MOVELEFT))
			{
				if (switchstate < 0)
				{

					cmd->forwardmove = -450.f;
				}
				else if (switchstate > 0)
				{

					cmd->forwardmove = 450.f;
				}
			}
		
	}


	if (g_Options.Misc.clantag_SLN == 2)
	{
		static int counter = 0;
		static int motion = 0;
		int ServerTime = (float)local->GetTickBase() * g_Globals->interval_per_tick * 2.5;

		if (counter % 48 == 0)
			motion++;
		int value = ServerTime % 46;
		switch (value)
		{
		case 0:
		{
			setclantag("                  ");
			break;
		}
		case 1:
		{
			setclantag("                 g");
			break;
		}
		case 2:
		{
			setclantag("                ga");
			break;
		}
		case 3:
		{
			setclantag("               gam");
			break;
		}
		case 4:
		{
			setclantag("              game");
			break;
		}
		case 5:
		{
			setclantag("             games");
			break;
		}
		case 6:
		{
			setclantag("            gamese");
			break;
		}
		case 7:
		{
			setclantag("           gamesen");
			break;
		}
		case 8:
		{
			setclantag("          gamesens");
			break;
		}
		case 9:
		{
			setclantag("         gamesense");
			break;
		}
		case 10:
		{
			setclantag("        gamesense ");
			break;
		}
		case 11:
		{
			setclantag("        gamesense ");
			break;
		}
		case 12:
		{
			setclantag("        gamesense ");
			break;
		}
		case 13:
		{
			setclantag("       gamesense  ");
			break;
		}
		case 14:
		{
			setclantag("       gamesense  ");
			break;
		}
		case 15:
		{
			setclantag("       gamesense  ");
			break;
		}
		case 16:
		{
			setclantag("      gamesense   ");
			break;
		}
		case 17:
		{
			setclantag("      gamesense   ");
			break;
		}
		case 18:
		{
			setclantag("      gamesense   ");
			break;
		}
		case 19:
		{
			setclantag("     gamesense    ");
			break;
		}
		case 20:
		{
			setclantag("     gamesense    ");
			break;
		}
		case 21:
		{
			setclantag("     gamesense    ");
			break;
		}
		case 22:
		{
			setclantag("    gamesense     ");
			break;
		}
		case 23:
		{
			setclantag("    gamesense     ");
			break;
		}
		case 24:
		{
			setclantag("    gamesense     ");
			break;
		}
		case 25:
		{
			setclantag("   gamesense      ");
			break;
		}
		case 26:
		{
			setclantag("   gamesense      ");
			break;
		}
		case 27:
		{
			setclantag("   gamesense      ");
			break;
		}
		case 28:
		{
			setclantag("  gamesense       ");
			break;
		}
		case 29:
		{
			setclantag("  gamesense       ");
			break;
		}
		case 30:
		{
			setclantag("  gamesense       ");
			break;
		}
		case 31:
		{
			setclantag(" gamesense        ");
			break;
		}
		case 32:
		{
			setclantag(" gamesense        ");
			break;
		}
		case 33:
		{
			setclantag(" gamesense        ");
			break;
		}
		case 34:
		{
			setclantag("gamesense         ");
			break;
		}
		case 35:
		{
			setclantag("gamesense         ");
			break;
		}
		case 36:
		{
			setclantag("gamesense         ");
			break;
		}
		case 37:
		{
			setclantag("amesense          ");
			break;
		}
		case 38:
		{
			setclantag("mesense           ");
			break;
		}
		case 39:
		{
			setclantag("esense            ");
			break;
		}
		case 40:
		{
			setclantag("sense             ");
			break;
		}
		case 41:
		{
			setclantag("ense              ");
			break;
		}
		case 42:
		{
			setclantag("nse               ");
			break;
		}
		case 43:
		{
			setclantag("se                ");
			break;
		}
		case 44:
		{
			setclantag("e                 ");
			break;
		}
		case 45:
		{
			setclantag("                  ");
			break;
		}
		}
		counter++;
	}


	if (g_Options.Misc.clantag_SLN == 1)
		{
		static int counter = 0;
		static int motion = 0;
		int ServerTime = (float)local->GetTickBase() * g_Globals->interval_per_tick * 2.5;

		if (counter % 48 == 0)
			motion++;
		int value = ServerTime % 36;

		switch (value)
		{
		case 0: setclantag("                  "); break; 
		case 1: setclantag("                 b"); break;
		case 2: setclantag("                br"); break;
		case 3: setclantag("               bre"); break;
		case 4: setclantag("              brea"); break;
		case 5: setclantag("             breat"); break;
		case 6: setclantag("            breath"); break;
		case 7: setclantag("           breathl"); break;
		case 8: setclantag("          breathle"); break;
		case 9: setclantag("         breathles"); break;
		case 10: setclantag("        breathless"); break;
		case 11: setclantag("       breathless "); break;
		case 12: setclantag("       breathless "); break;
		case 13: setclantag("      breathless  "); break;
		case 14: setclantag("      breathless  "); break;
		case 15: setclantag("     breathless   "); break;
		case 16: setclantag("     breathless   "); break;
		case 17: setclantag("    breathless    "); break;
		case 18: setclantag("    breathless    "); break;
		case 19: setclantag("   breathless     "); break;
		case 20: setclantag("   breathless     "); break;
		case 21: setclantag("  breathless      "); break;
		case 22: setclantag("  breathless      "); break;
		case 23: setclantag(" breathless       "); break;
		case 24: setclantag(" breathless       "); break;
		case 25: setclantag("breathless        "); break;
		case 26: setclantag("breathless        "); break;
		case 27: setclantag("reathless         "); break;
		case 28: setclantag("eathless          "); break;
		case 29: setclantag("athless           "); break;
		case 30: setclantag("thless            "); break;
		case 31: setclantag("hless             "); break;
		case 32: setclantag("less              "); break;
		case 33: setclantag("ess               "); break;
		case 34: setclantag("ss                "); break;
		case 35: setclantag("s                 "); break;
		case 36: setclantag("                  "); break;
		}
		counter++;
		}

	if (!g_Options.Misc.animatedclantag && animatedclantag.c_str() != G::AnimatedClantag)
	{
		animatedclantag = G::AnimatedClantag;
	}
	if (g_Options.Misc.animatedclantag && animatedclantag.length() > 1)
	{
		if (int(g_Globals->curtime) != iLastTime)
		{
			auto length = animatedclantag.length();
			animatedclantag.insert(0, 1, animatedclantag[length - 2]);
			animatedclantag.erase(length - 1, 1);

			setclantag(animatedclantag.c_str());
			iLastTime = int(g_Globals->curtime);
		}
	}
	if (g_Options.Misc.namespam)
	{
		char name[151];
		char fucked_char = static_cast<char>(-1);
		for (auto i = 0; i <= 150; i++)
			name[i] = fucked_char;

		const char nick[14] = "breathless.cc";
		memcpy(name, nick, 14);

		SetName(name);
	}


	if (g_Options.Ragebot.ayywarecrasher)
	{
		g_Options.Misc.silentstealer = false;
		g_Options.Misc.namespam = false;
		SetName("BREATHLESS BREATHLESS BREATHLESS BREATHLESS BREATHLESS BREATHLESS BREATHLESS BREATHLESS BREATHLESS BREATHLESS BREATHLESS BREATHLESS BREATHLESS BREATHLESS BREATHLESS ");
		
	}

	if (g_Options.Misc.silentstealer)
	{
		bool bDidMeme = false;
		int iNameIndex = -1;
		char chName[130];
		static ConVar* name = g_CVar->FindVar("name");
		{
			for (int iPlayerIndex = 0; iPlayerIndex < g_Engine->GetMaxClients(); iPlayerIndex++)
			{
				C_BaseEntity *pEntity = g_EntityList->GetClientEntity(iPlayerIndex);
				if (!pEntity || pEntity == local || iPlayerIndex == g_Engine->GetLocalPlayer())
					continue;
				if (rand() % 3 == 1)
				{
					iNameIndex = pEntity->GetIndex();
					bDidMeme = true;
				}
			}
			if (bDidMeme)
			{
				player_info_t pInfo;
				g_Engine->GetPlayerInfo(iNameIndex, &pInfo);
				sprintf(chName, "%s ", pInfo.name);
				name->SetValue(chName);
			}
		}
	}


}

static vec_t Normalize_y(vec_t ang)
{
	while (ang < -180.0f)
		ang += 360.0f;
	while (ang > 180.0f)
		ang -= 360.0f;
	return ang;
}

void misc::AutoStrafe(CInput::CUserCmd *cmd, C_BaseEntity *local, QAngle oldangles)
{
	if (g_Options.Misc.AutoStrafe)
	{
		static AutoStrafer Strafer;

		if (!(local->GetFlags() & FL_ONGROUND))
		{
			if (cmd->mousedx > 1 || cmd->mousedx < -1)
				cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
			else
			{
				cmd->forwardmove = (1800.f * 4.f) / local->GetVelocity().Length2D();
				cmd->sidemove = (cmd->command_number % 2 == 0 ? -450.f : 450.f);
			}
		}
		movementfix(oldangles, cmd);
	}
}


void misc::FakeWalk(CInput::CUserCmd* pCmd, bool &bSendPacket, C_BaseEntity *local)
{
	
	if (g_Options.Misc.fakewalk)
	{
		int FakeWalkKey = g_Options.Misc.fakewalkkey;
		if (FakeWalkKey > 0 && G::PressedKeys[g_Options.Misc.fakewalkkey])
		{
			static int chocking = -1;
			chocking++;

			if (chocking < 3)
			{
				bSendPacket = false;
				pCmd->tick_count += 10;
				pCmd += 7 + pCmd->tick_count % 2 ? 0 : 1;
				pCmd->buttons |= local->GetMoveType() == IN_BACK;
				pCmd->forwardmove = pCmd->sidemove = 0.f;
			}
			else
			{
				bSendPacket = true;
				chocking = -1;
				g_Globals->frametime *= (local->GetVelocity().Length2D()) / 1.f;
				pCmd->buttons |= local->GetMoveType() == IN_FORWARD;
			}
		}
	}
}
