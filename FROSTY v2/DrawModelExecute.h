#pragma once
#include "HookIncludes.h"
typedef void(__thiscall* dme_t)(void*, void*, void*, const ModelRenderInfo_t&, matrix3x4*);

float flColor[3];
float flVColor[3];

IMaterial* GetCurrentMaterial(int mati)
{
	static IMaterial* mat;

	switch (mati)
	{
	case 3:
		mat = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", nullptr);
		break;
	case 4:
		mat = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/gold", nullptr);
		break;
	case 5:
		mat = g_MaterialSystem->FindMaterial("models/player/ct_fbi/ct_fbi_glass", nullptr);
		break;
	case 6:
		mat = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/gloss", nullptr);
		break;
	case 7:
		mat = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", nullptr);
		break;
	default:
		mat = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", nullptr);
		return mat;
		break;
	}
	return mat;
}

IMaterial* GetCurrentZMaterial(int mati)
{
	static IMaterial* zmat;

	switch (mati)
	{
	case 3:
		zmat = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", nullptr);
		zmat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, g_Options.Visuals.XQZ);
		return zmat;
		break;
	case 4:
		zmat = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/gold", nullptr);
		zmat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, g_Options.Visuals.XQZ);
		return zmat;
		break;
	case 5:
		zmat = g_MaterialSystem->FindMaterial("models/player/ct_fbi/ct_fbi_glass", nullptr);
		zmat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, g_Options.Visuals.XQZ);
		return zmat;
		break;
	case 6:
		zmat = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/gloss", nullptr);
		zmat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, g_Options.Visuals.XQZ);
		return zmat;
		break;
	case 7:
		zmat = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", nullptr);
		zmat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, g_Options.Visuals.XQZ);
		return zmat;
		break;
	default:
		zmat = g_MaterialSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", nullptr);
		return zmat;
		break;
	}
}

void __fastcall hkDrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld)
{
	static bool DontDraw = false;
	static auto ofunc = hooks::modelrender.get_original<dme_t>(21);

	IMaterial* zmat = GetCurrentZMaterial(g_Options.Visuals.matierial);
	IMaterial* mat = GetCurrentMaterial(g_Options.Visuals.matierial);

	IMaterial* hmat = GetCurrentMaterial(g_Options.Visuals.matierial);
	IMaterial* wmat = GetCurrentMaterial(g_Options.Visuals.matierial);

	static IMaterial* norm = CreateMaterial(false, true, false);
	static IMaterial* flat = CreateMaterial(false, false, false);
	static IMaterial* wire = CreateMaterial(false, false, true);

	static IMaterial* znorm = CreateMaterial(true, true, false);
	static IMaterial* zflat = CreateMaterial(true, false, false);
	static IMaterial* zwire = CreateMaterial(true, false, true);

	static IMaterial* Outline = CreateMaterial(true, false, true);
	DontDraw = false;

	const char * ModelName = g_ModelInfo->GetModelName((model_t*)pInfo.pModel);
	C_BaseEntity* pModelEntity = (C_BaseEntity*)g_EntityList->GetClientEntity(pInfo.entity_index);
	C_BaseEntity* pLocal = (C_BaseEntity*)g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	if (ModelName && strstr(ModelName, "models/player"))
	{
		if (pModelEntity && pLocal)
		{
			if ((g_Options.Visuals.Teamchams || pModelEntity->GetTeamNum() != pLocal->GetTeamNum()) && g_Options.Visuals.Chams)
			{
				pModelEntity = g_EntityList->GetClientEntity(pInfo.entity_index);

				if (pModelEntity->GetTeamNum() != pLocal->GetTeamNum())
				{
					flColor[0] = g_Options.Colors.EnemyChamsNVis[0];
					flColor[1] = g_Options.Colors.EnemyChamsNVis[1];
					flColor[2] = g_Options.Colors.EnemyChamsNVis[2];
					flVColor[0] = g_Options.Colors.EnemyChamsVis[0];
					flVColor[1] = g_Options.Colors.EnemyChamsVis[1];
					flVColor[2] = g_Options.Colors.EnemyChamsVis[2];
				}
				if (pModelEntity->GetTeamNum() == pLocal->GetTeamNum())
				{
					flColor[0] = g_Options.Colors.TeamChamsVis[0];
					flColor[1] = g_Options.Colors.TeamChamsVis[1];
					flColor[2] = g_Options.Colors.TeamChamsVis[2];
					flVColor[0] = g_Options.Colors.TeamChamsVis[0];
					flVColor[1] = g_Options.Colors.TeamChamsVis[1];
					flVColor[2] = g_Options.Colors.TeamChamsVis[2];
				}
				if (pModelEntity)
				{
					if (pModelEntity->IsAlive() && pModelEntity->GetHealth() > 0)
					{
						if (g_Options.Visuals.matierial == 0)
						{
							if (g_Options.Visuals.XQZ)
							{

								g_RenderView->SetColorModulation(flColor);
								g_RenderView->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
								g_ModelRender->ForcedMaterialOverride(znorm);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
							}
							g_RenderView->SetColorModulation(flVColor);
							g_RenderView->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
							g_ModelRender->ForcedMaterialOverride(norm);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
						}
						else if (g_Options.Visuals.matierial == 1)
						{
							if (g_Options.Visuals.XQZ)
							{

								g_RenderView->SetColorModulation(flColor);
								g_RenderView->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
								g_ModelRender->ForcedMaterialOverride(zflat);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
							}
							g_RenderView->SetColorModulation(flVColor);
							g_RenderView->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
							g_ModelRender->ForcedMaterialOverride(flat);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
						}
						else if (g_Options.Visuals.matierial == 2)
						{
							if (g_Options.Visuals.XQZ)
							{

								g_RenderView->SetColorModulation(flColor);
								g_RenderView->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
								g_ModelRender->ForcedMaterialOverride(zwire);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
							}
							g_RenderView->SetColorModulation(flVColor);
							g_RenderView->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
							g_ModelRender->ForcedMaterialOverride(wire);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
						}
						else
						{
							if (g_Options.Visuals.XQZ)
							{

								g_RenderView->SetColorModulation(flColor);
								g_RenderView->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
								g_ModelRender->ForcedMaterialOverride(zmat);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
							}
							g_RenderView->SetColorModulation(flVColor);
							g_RenderView->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
							g_ModelRender->ForcedMaterialOverride(mat);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
						}
					}
					else
					{
						ForceMaterial(Color(255, 255, 255), znorm);
					}

				}
			}

			if (pModelEntity == pLocal)
			{
				if (pModelEntity->IsAlive() && pModelEntity->GetHealth() > 0)
				{

					g_RenderView->SetBlend(0.3f);
					g_ModelRender->ForcedMaterialOverride(nullptr);
					ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

				}
				else
				{
					ForceMaterial(Color(255, 255, 255), zmat);
				}
			}
		}
	}




	if (!DontDraw)
		ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
	g_ModelRender->ForcedMaterialOverride(NULL);


}