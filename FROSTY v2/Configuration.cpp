#include "Configuration.hpp"
#include "Variables.h"
#include <winerror.h>
#pragma warning( disable : 4091)
#include <ShlObj.h>
#include <string>
#include <sstream>
#include "XorStr.hpp"
void CConfig::Setup()
{


	SetupValue(g_Options.Ragebot.MainSwitch, false, ("Ragebot"), ("RageToggle"));
	SetupValue(g_Options.Ragebot.Enabled, false, ("Ragebot"), ("Enabled"));
	SetupValue(g_Options.Ragebot.AutoFire, false, ("Ragebot"), ("AutoFire"));
	SetupValue(g_Options.Ragebot.FOV, 0.f, ("Ragebot"), ("FOV"));
	SetupValue(g_Options.Ragebot.Silent, false, ("Ragebot"), ("Silent"));
	SetupValue(g_Options.Ragebot.AutoPistol, false, ("Ragebot"), ("AutoPistol"));
	SetupValue(g_Options.Ragebot.KeyPress, 0, ("Ragebot"), ("Key"));

	SetupValue(g_Options.Ragebot.flipkey, 1, ("Ragebot"), ("FlipKey"));
	SetupValue(g_Options.Ragebot.EnabledAntiAim, false, ("Ragebot"), ("AntiaimEnabled"));
	SetupValue(g_Options.Ragebot.PreAAs, false, ("Ragebot"), ("Pre-set-AAs"));
	SetupValue(g_Options.Ragebot.Pitch, 0, ("Ragebot"), ("AntiaimPitch"));
	SetupValue(g_Options.Ragebot.YawTrue, 0, ("Ragebot"), ("AntiaimYaw-true"));
	SetupValue(g_Options.Ragebot.YawFake, 0, ("Ragebot"), ("AntiaimYaw-fake"));
	SetupValue(g_Options.Ragebot.AtTarget, false, ("Ragebot"), ("attargets"));
	SetupValue(g_Options.Ragebot.Edge, false, ("Ragebot"), ("edge"));
	SetupValue(g_Options.Ragebot.KnifeAA, false, ("Ragebot"), ("KnifeAA"));
	SetupValue(g_Options.Ragebot.BuilderAAs, false, ("Ragebot"), ("Builder-AAs"));
	SetupValue(g_Options.Ragebot.BuilderPitch, 0, ("Ragebot"), ("Builder-Pitch"));
	SetupValue(g_Options.Ragebot.BuilderReal, 0, ("Ragebot"), ("Builder-Yaw"));
	SetupValue(g_Options.Ragebot.BuilderFake, 0, ("Ragebot"), ("Builder-Fake"));
	SetupValue(g_Options.Ragebot.Jitter, false, ("Ragebot"), ("Builder-Jitter"));
	SetupValue(g_Options.Ragebot.JitterRange, 0, ("Ragebot"), ("Builder-Jitter-Range"));
	SetupValue(g_Options.Ragebot.FJitter, false, ("Ragebot"), ("Builder-fJitter"));
	SetupValue(g_Options.Ragebot.FJitterRange, 0, ("Ragebot"), ("Builder-fJitter-Range"));
	SetupValue(g_Options.Ragebot.LBYBreaker, false, ("Ragebot"), ("Builder-LBY-Breaker"));
	SetupValue(g_Options.Ragebot.FakeLag, false, ("Ragebot"), ("Fakelag"));
	SetupValue(g_Options.Ragebot.FakeLagAmt, 0, ("Ragebot"), ("Fakelag Amount"));

	SetupValue(g_Options.Ragebot.FriendlyFire, false, ("Ragebot"), ("FriendlyFire"));
	SetupValue(g_Options.Ragebot.Hitbox, 0, ("Ragebot"), ("Hitbox"));
	SetupValue(g_Options.Ragebot.Hitscan, 0, ("Ragebot"), ("Hitscan"));

	SetupValue(g_Options.Ragebot.AntiRecoil, false, ("Ragebot"), ("AntiRecoil"));
	SetupValue(g_Options.Ragebot.AutoStop, false, ("Ragebot"), ("AutoStop"));
	SetupValue(g_Options.Ragebot.AutoCrouch, false, ("Ragebot"), ("AutoCrouch"));
	SetupValue(g_Options.Ragebot.AutoScope, false, ("Ragebot"), ("AutoScope"));
	SetupValue(g_Options.Ragebot.MinimumDamageSniper, 0.f, ("Ragebot"), ("AutoWallDamageSniper"));
	SetupValue(g_Options.Ragebot.MinimumDamagePistol, 0.f, ("Ragebot"), ("AutoWallDamagePistol"));
	SetupValue(g_Options.Ragebot.MinimumDamageRifle, 0.f, ("Ragebot"), ("AutoWallDamageRifle"));
	SetupValue(g_Options.Ragebot.MinimumDamageHeavy, 0.f, ("Ragebot"), ("AutoWallDamageHeavy"));
	SetupValue(g_Options.Ragebot.MinimumDamageSmg, 0.f, ("Ragebot"), ("AutoWallDamageSmgs"));
	SetupValue(g_Options.Ragebot.MinimumDamageRevolver, 0.f, ("Ragebot"), ("AutoWallDamageRevolver"));
	SetupValue(g_Options.Ragebot.Hitchance, false, ("Ragebot"), ("HitChance"));
	SetupValue(g_Options.Ragebot.HitchanceSniper, 0.f, ("Ragebot"), ("HitChanceSniper"));
	SetupValue(g_Options.Ragebot.HitchancePistol, 0.f, ("Ragebot"), ("HitChancePistol"));
	SetupValue(g_Options.Ragebot.HitchanceHeavy, 0.f, ("Ragebot"), ("HitChanceHeavy"));
	SetupValue(g_Options.Ragebot.HitchanceSmgs, 0.f, ("Ragebot"), ("HitChanceSmgs"));
	SetupValue(g_Options.Ragebot.HitchanceRifle, 0.f, ("Ragebot"), ("HitChanceRifle"));
	SetupValue(g_Options.Ragebot.HitchanceRevolver, 0.f, ("Ragebot"), ("HitChanceRevolver"));
	SetupValue(g_Options.Ragebot.Resolver, false, ("Ragebot"), ("Resolver"));
	SetupValue(g_Options.Ragebot.FakeLagFix, false, ("Ragebot"), ("Fakelag Fix"));
	SetupValue(g_Options.Ragebot.PosAdjust, false, ("Ragebot"), ("Position Adjustment"));
	SetupValue(g_Options.Ragebot.BAIMkey, 0, ("Ragebot"), ("BAIMKey"));


	//new aa stuff going here
	SetupValue(g_Options.Ragebot.AA_onCrouch, false, ("RageBot"), ("AACrouch"));
	SetupValue(g_Options.Ragebot.AA_onFakeWalk, false, ("RageBot"), ("AAFakeWalk"));
	SetupValue(g_Options.Ragebot.AA_onRun, false, ("RageBot"), ("AARun"));
	SetupValue(g_Options.Ragebot.AA_onWalk, false, ("RageBot"), ("AAWalk"));
	SetupValue(g_Options.Ragebot.AA_onStand, false, ("RageBot"), ("AAStand"));


	//walkiing builder aa's
	SetupValue(g_Options.Ragebot.walk_BuilderAAs, false, ("RageBot"), ("walk_BuilderAAs"));
	SetupValue(g_Options.Ragebot.walk_Jitter, false, ("RageBot"), ("walk_Jitter"));
	SetupValue(g_Options.Ragebot.walk_FJitter, false, ("RageBot"), ("walk_FJitter"));
	SetupValue(g_Options.Ragebot.walk_LBYBreaker, false, ("RageBot"), ("walk_LBYBreaker"));
	SetupValue(g_Options.Ragebot.walk_BuilderReal, 0, ("RageBot"), ("walk_BuilderReal"));
	SetupValue(g_Options.Ragebot.walk_BuilderFake, 0, ("RageBot"), ("walk_BuilderFake"));
	SetupValue(g_Options.Ragebot.walk_BuilderPitch, 0, ("RageBot"), ("walk_BuilderPitch"));
	SetupValue(g_Options.Ragebot.walk_JitterRange, 0, ("RageBot"), ("walk_JitterRange"));
	SetupValue(g_Options.Ragebot.walk_FJitterRange, 0, ("RageBot"), ("walk_FJitterRange"));

	//ruinning builder aa's
	SetupValue(g_Options.Ragebot.run_BuilderAAs, false, ("RageBot"), ("run_BuilderAAs"));
	SetupValue(g_Options.Ragebot.run_Jitter, false, ("RageBot"), ("run_Jitter"));
	SetupValue(g_Options.Ragebot.run_FJitter, false, ("RageBot"), ("run_FJitter"));
	SetupValue(g_Options.Ragebot.run_LBYBreaker, false, ("RageBot"), ("run_LBYBreaker"));
	SetupValue(g_Options.Ragebot.run_BuilderReal, 0, ("RageBot"), ("run_BuilderReal"));
	SetupValue(g_Options.Ragebot.run_BuilderFake, 0, ("RageBot"), ("run_BuilderFake"));
	SetupValue(g_Options.Ragebot.run_BuilderPitch, 0, ("RageBot"), ("run_BuilderPitch"));
	SetupValue(g_Options.Ragebot.run_JitterRange, 0, ("RageBot"), ("run_JitterRange"));
	SetupValue(g_Options.Ragebot.run_FJitterRange, 0, ("RageBot"), ("run_FJitterRange"));

	//crouching builder aa's
	SetupValue(g_Options.Ragebot.crouch_BuilderAAs, false, ("RageBot"), ("crouch_BuilderAAs"));
	SetupValue(g_Options.Ragebot.crouch_Jitter, false, ("RageBot"), ("crouch_Jitter"));
	SetupValue(g_Options.Ragebot.crouch_FJitter, false, ("RageBot"), ("crouch_FJitter"));
	SetupValue(g_Options.Ragebot.crouch_LBYBreaker, false, ("RageBot"), ("crouch_LBYBreaker"));
	SetupValue(g_Options.Ragebot.crouch_BuilderReal, 0, ("RageBot"), ("crouch_BuilderReal"));
	SetupValue(g_Options.Ragebot.crouch_BuilderFake, 0, ("RageBot"), ("crouch_BuilderFake"));
	SetupValue(g_Options.Ragebot.crouch_BuilderPitch, 0, ("RageBot"), ("crouch_BuilderPitch"));
	SetupValue(g_Options.Ragebot.crouch_JitterRange, 0, ("RageBot"), ("crouch_JitterRange"));
	SetupValue(g_Options.Ragebot.crouch_FJitterRange, 0, ("RageBot"), ("crouch_FJitterRange"));

	//fakewalk builder aa's
	SetupValue(g_Options.Ragebot.fwalk_BuilderAAs, false, ("RageBot"), ("fwalk_BuilderAAs"));
	SetupValue(g_Options.Ragebot.fwalk_Jitter, false, ("RageBot"), ("fwalk_Jitter"));
	SetupValue(g_Options.Ragebot.fwalk_FJitter, false, ("RageBot"), ("fwalk_FJitter"));
	SetupValue(g_Options.Ragebot.fwalk_LBYBreaker, false, ("RageBot"), ("fwalk_LBYBreaker"));
	SetupValue(g_Options.Ragebot.fwalk_BuilderReal, 0, ("RageBot"), ("fwalk_BuilderReal"));
	SetupValue(g_Options.Ragebot.fwalk_BuilderFake, 0, ("RageBot"), ("fwalk_BuilderFake"));
	SetupValue(g_Options.Ragebot.fwalk_BuilderPitch, 0, ("RageBot"), ("fwalk_BuilderPitch"));
	SetupValue(g_Options.Ragebot.fwalk_JitterRange, 0, ("RageBot"), ("fwalk_JitterRange"));
	SetupValue(g_Options.Ragebot.fwalk_FJitterRange, 0, ("RageBot"), ("fwalk_FJitterRange"));

	//standing builder aa's
	SetupValue(g_Options.Ragebot.stand_BuilderAAs, false, ("RageBot"), ("stand_BuilderAAs"));
	SetupValue(g_Options.Ragebot.stand_Jitter, false, ("RageBot"), ("stand_Jitter"));
	SetupValue(g_Options.Ragebot.stand_FJitter, false, ("RageBot"), ("stand_FJitter"));
	SetupValue(g_Options.Ragebot.stand_LBYBreaker, false, ("RageBot"), ("stand_LBYBreaker"));
	SetupValue(g_Options.Ragebot.stand_BuilderReal, 0, ("RageBot"), ("stand_BuilderReal"));
	SetupValue(g_Options.Ragebot.stand_BuilderFake, 0, ("RageBot"), ("stand_BuilderFake"));
	SetupValue(g_Options.Ragebot.stand_BuilderPitch, 0, ("RageBot"), ("stand_BuilderPitch"));
	SetupValue(g_Options.Ragebot.stand_JitterRange, 0, ("RageBot"), ("stand_JitterRange"));
	SetupValue(g_Options.Ragebot.stand_FJitterRange, 0, ("RageBot"), ("stand_FJitterRange"));


	//BEGINNING OF PREBUILT AA'S

	//walking prebuild aa's  walk
	SetupValue(g_Options.Ragebot.walk_PreAAs, false, ("RageBot"), ("walk_PreAAs"));
	SetupValue(g_Options.Ragebot.walk_Pitch, false, ("RageBot"), ("walk_Pitch"));
	SetupValue(g_Options.Ragebot.walk_PitchAdder, 0, ("RageBot"), ("walk_PitchAdder"));
	SetupValue(g_Options.Ragebot.walk_YawTrue, false, ("RageBot"), ("walk_YawTrue"));
	SetupValue(g_Options.Ragebot.walk_YawTrueAdder, 0, ("RageBot"), ("walk_YawTrueAdder"));
	SetupValue(g_Options.Ragebot.walk_YawFake, false, ("RageBot"), ("walk_YawFake"));
	SetupValue(g_Options.Ragebot.walk_YawFakeAdder, 0, ("RageBot"), ("walk_YawFakeAdder"));

	//running prebuild aa's
	SetupValue(g_Options.Ragebot.run_PreAAs, false, ("RageBot"), ("run_PreAAs"));
	SetupValue(g_Options.Ragebot.run_Pitch, false, ("RageBot"), ("run_Pitch"));
	SetupValue(g_Options.Ragebot.run_PitchAdder, 0, ("RageBot"), ("run_PitchAdder"));
	SetupValue(g_Options.Ragebot.run_YawTrue, false, ("RageBot"), ("run_YawTrue"));
	SetupValue(g_Options.Ragebot.run_YawTrueAdder, 0, ("RageBot"), ("run_YawTrueAdder"));
	SetupValue(g_Options.Ragebot.run_YawFake, false, ("RageBot"), ("run_YawFake"));
	SetupValue(g_Options.Ragebot.run_YawFakeAdder, 0, ("RageBot"), ("run_YawFakeAdder"));

	//crouching prebuild aa's crouch
	SetupValue(g_Options.Ragebot.crouch_PreAAs, false, ("RageBot"), ("_PreAAs"));
	SetupValue(g_Options.Ragebot.crouch_Pitch, false, ("RageBot"), ("_Pitch"));
	SetupValue(g_Options.Ragebot.crouch_PitchAdder, 0, ("RageBot"), ("_PitchAdder"));
	SetupValue(g_Options.Ragebot.crouch_YawTrue, false, ("RageBot"), ("_YawTrue"));
	SetupValue(g_Options.Ragebot.crouch_YawTrueAdder, 0, ("RageBot"), ("_YawTrueAdder"));
	SetupValue(g_Options.Ragebot.crouch_YawFake, false, ("RageBot"), ("_YawFake"));
	SetupValue(g_Options.Ragebot.crouch_YawFakeAdder, 0, ("RageBot"), ("_YawFakeAdder"));

	//fakewalking prebuild aa's fwalk
	SetupValue(g_Options.Ragebot.fwalk_PreAAs, false, ("RageBot"), ("fwalk_PreAAs"));
	SetupValue(g_Options.Ragebot.fwalk_Pitch, false, ("RageBot"), ("fwalk_Pitch"));
	SetupValue(g_Options.Ragebot.fwalk_PitchAdder, 0, ("RageBot"), ("fwalk_PitchAdder"));
	SetupValue(g_Options.Ragebot.fwalk_YawTrue, false, ("RageBot"), ("fwalk_YawTrue"));
	SetupValue(g_Options.Ragebot.fwalk_YawTrueAdder, 0, ("RageBot"), ("fwalk_YawTrueAdder"));
	SetupValue(g_Options.Ragebot.fwalk_YawFake, false, ("RageBot"), ("fwalk_YawFake"));
	SetupValue(g_Options.Ragebot.fwalk_YawFakeAdder, 0, ("RageBot"), ("fwalk_YawFakeAdder"));

	//standing prebuild aa's  stand
	SetupValue(g_Options.Ragebot.stand_PreAAs, false, ("RageBot"), ("stand_PreAAs"));
	SetupValue(g_Options.Ragebot.stand_Pitch, false, ("RageBot"), ("stand_Pitch"));
	SetupValue(g_Options.Ragebot.stand_PitchAdder, 0, ("RageBot"), ("stand_PitchAdder"));
	SetupValue(g_Options.Ragebot.stand_YawTrue, false, ("RageBot"), ("stand_YawTrue"));
	SetupValue(g_Options.Ragebot.stand_YawTrueAdder, 0, ("RageBot"), ("stand_YawTrueAdder"));
	SetupValue(g_Options.Ragebot.stand_YawFake, false, ("RageBot"), ("stand_YawFake"));
	SetupValue(g_Options.Ragebot.stand_YawFakeAdder, 0, ("RageBot"), ("stand_YawFakeAdder"));

	SetupValue(g_Options.Ragebot.walk_allowflip, false, ("RageBot"), ("walk_allowflip"));
	SetupValue(g_Options.Ragebot.run_allowflip, false, ("RageBot"), ("run_allowflip"));
	SetupValue(g_Options.Ragebot.crouch_allowflip, false, ("RageBot"), ("crouch_allowflip"));
	SetupValue(g_Options.Ragebot.fwalk_allowflip, false, ("RageBot"), ("fwalk_allowflip"));
	SetupValue(g_Options.Ragebot.stand_allowflip, false, ("RageBot"), ("stand_allowflip"));

	SetupValue(g_Options.Legitbot.MainSwitch, false, ("Legitbot"), ("LegitToggle"));
	SetupValue(g_Options.Legitbot.Aimbot.Enabled, false, ("Legitbot"), ("Enabled"));
	SetupValue(g_Options.Legitbot.backtrack, false, ("Legitbot"), ("Backtrack"));
	SetupValue(g_Options.Legitbot.backtrackTicks, 0, ("Legitbot"), ("BacktrackTicks"));


	SetupValue(g_Options.Legitbot.MainKey, 1, ("Legitbot"), ("Key"));
	//SetupValue(g_Options.Legitbot.hitboxrifle, 0, ("Legitbot"), ("Hitbox-Rifle"));
	SetupValue(g_Options.Legitbot.Mainfov, 0.f, ("Legitbot"), ("FOV"));
	SetupValue(g_Options.Legitbot.MainSmooth, 1.f, ("Legitbot"), ("Speed"));
	SetupValue(g_Options.Legitbot.main_recoil_min, 0, ("Legitbot"), ("RCS-min"));
	SetupValue(g_Options.Legitbot.main_recoil_max, 0, ("Legitbot"), ("RCS-max"));

	SetupValue(g_Options.Legitbot.PistolKey, 6, ("Legitbot"), ("Key-Pistol"));
	//SetupValue(g_Options.Legitbot.hitboxpistol, 0, ("Legitbot"), ("Hitbox-Pistol"));
	SetupValue(g_Options.Legitbot.Pistolfov, 0.f, ("Legitbot"), ("FOV-Pistol"));
	SetupValue(g_Options.Legitbot.PistolSmooth, 1.f, ("Legitbot"), ("Speed-Pistol"));
	SetupValue(g_Options.Legitbot.pistol_recoil_min, 0, ("Legitbot"), ("RCS-min-pistol"));
	SetupValue(g_Options.Legitbot.pistol_recoil_max, 0, ("Legitbot"), ("RCS-max-pistol"));

	SetupValue(g_Options.Legitbot.SniperKey, 6, ("Legitbot"), ("Key-Sniper"));
	//SetupValue(g_Options.Legitbot.hitboxsniper, 0, ("Legitbot"), ("Hitbox-Sniper"));
	SetupValue(g_Options.Legitbot.Sniperfov, 0.f, ("Legitbot"), ("FOV-Sniper"));
	SetupValue(g_Options.Legitbot.SniperSmooth, 0.f, ("Legitbot"), ("Speed-Sniper"));
	SetupValue(g_Options.Legitbot.sniper_recoil_min, 0, ("Legitbot"), ("RCS-min-sniper"));
	SetupValue(g_Options.Legitbot.sniper_recoil_max, 0, ("Legitbot"), ("RCS-max-sniper"));

	SetupValue(g_Options.Legitbot.Triggerbot.Enabled, false, ("Triggerbot"), ("Enabled"));
	SetupValue(g_Options.Legitbot.Triggerbot.Key, 6, ("Triggerbot"), ("Key"));
	SetupValue(g_Options.Legitbot.Triggerbot.Delay, 0.f, ("Triggerbot"), ("Delay"));
	SetupValue(g_Options.Legitbot.Triggerbot.hitchance, 0.f, ("Triggerbot"), ("Hitchance"));

	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Head, false, ("Triggerbot"), ("FilterHead"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Chest, false, ("Triggerbot"), ("FilterChest"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Stomach, false, ("Triggerbot"), ("FilterStomach"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Arms, false, ("Triggerbot"), ("FilterArms"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Legs, false, ("Triggerbot"), ("FilterLegs"));





	//SetupValue(g_Options.Visuals.Enabled, false, ("Visuals"), ("VisualsEnabled"));
	SetupValue(g_Options.Visuals.Box, false, ("Visuals"), ("Box"));
	SetupValue(g_Options.Visuals.BoxType, 0, ("Visuals"), ("BoxType"));
	SetupValue(g_Options.Visuals.Name, false, ("Visuals"), ("Name"));
	SetupValue(g_Options.Visuals.health, false, ("Visuals"), ("HP"));
	SetupValue(g_Options.Visuals.Weapon, false, ("Visuals"), ("Weapon"));
	SetupValue(g_Options.Visuals.wpnmode, 0, ("Visuals"), ("WeaponType"));
	SetupValue(g_Options.Visuals.Chams, false, ("Visuals"), ("Chams"));
	SetupValue(g_Options.Visuals.Skeleton, false, ("Visuals"), ("Skeleton"));
	SetupValue(g_Options.Visuals.TeamESP, false, ("Visuals"), ("TeamEsp"));
	SetupValue(g_Options.Visuals.Grenades, false, ("Visuals"), ("GrenadeESP"));
	SetupValue(g_Options.Visuals.AimLine, false, ("Visuals"), ("Aimlines"));

	SetupValue(g_Options.Visuals.NoVisualRecoil, false, ("Visuals"), ("NoVisualRecoil"));
	SetupValue(g_Options.Visuals.Hitmarker, false, ("Visuals"), ("Hitmarker"));
	SetupValue(g_Options.Visuals.Hitsound, 0, ("Visuals"), ("Hitsound"));
	SetupValue(g_Options.Visuals.FOVChanger, 0.f, ("Visuals"), ("fovchanger"));
	SetupValue(g_Options.Visuals.viewmodelChanger, 68.f, ("Visuals"), ("viewmodel_fov"));
	SetupValue(g_Options.Visuals.NoFlash, false, ("Visuals"), ("NoFlash"));
	SetupValue(g_Options.Visuals.NoSmoke, false, ("Visuals"), ("NoSmoke"));
	SetupValue(g_Options.Visuals.Time, false, ("Visuals"), ("Time"));
	SetupValue(g_Options.Visuals.noscopeborder, false, ("Visuals"), ("noscopeborder"));
	SetupValue(g_Options.Visuals.Droppedguns, false, ("Visuals"), ("DroppedGuns"));
	SetupValue(g_Options.Visuals.GrenadePrediction, false, ("Visuals"), ("GrenadePrediction"));
	SetupValue(g_Options.Visuals.tpdist, false, ("Visuals"), ("thirdperson distance"));
	SetupValue(g_Options.Visuals.TPKey, false, ("Visuals"), ("thirdperson key"));
	SetupValue(g_Options.Visuals.ThirdPerson, false, ("Visuals"), ("thirdperson switch"));
	SetupValue(g_Options.Visuals.EventLog, false, ("Visuals"), ("EventLog"));
	SetupValue(g_Options.Visuals.Callout, false, ("Visuals"), ("Callout"));
	SetupValue(g_Options.Visuals.Armor, false, ("Visuals"), ("Armor"));
	SetupValue(g_Options.Visuals.Flashed, false, ("Visuals"), ("EnemyState"));
	SetupValue(g_Options.Visuals.Distance, false, ("Visuals"), ("Distance"));
	SetupValue(g_Options.Visuals.Money, false, ("Visuals"), ("Money"));
	SetupValue(g_Options.Visuals.resolveMode, false, ("Visuals"), ("ResolveMode"));
	SetupValue(g_Options.Visuals.Chams, false, ("Visuals"), ("PlayerChams"));
	SetupValue(g_Options.Visuals.Teamchams, false, ("Visuals"), ("Teamchams"));
	SetupValue(g_Options.Visuals.Chamweapon, false, ("Visuals"), ("WeaponChams"));
	SetupValue(g_Options.Visuals.XQZ, false, ("Visuals"), ("XQZ Chams"));
	SetupValue(g_Options.Visuals.champlayeralpha, 0, ("Visuals"), ("PlayerCham Alpha"));
	SetupValue(g_Options.Visuals.matierial, 0, ("Visuals"), ("PlayerCham Material"));
	SetupValue(g_Options.Visuals.weaponviewcham, false, ("Visuals"), ("Weapon Chams"));
	SetupValue(g_Options.Visuals.weaponhandalpha, 0, ("Visuals"), ("Weapon Chams Alpha"));
	SetupValue(g_Options.Visuals.handmat, 0, ("Visuals"), ("WeaponCham Material"));
	SetupValue(g_Options.Visuals.handcham, false, ("Visuals"), ("Hand Chams"));
	SetupValue(g_Options.Visuals.chamhandalpha, 0, ("Visuals"), ("Hand Chams Alpha"));
	SetupValue(g_Options.Visuals.weaponmat, 0, ("Visuals"), ("HandCham Material"));
	SetupValue(g_Options.Visuals.glowplayer, false, ("Visuals"), ("PlayerGlow"));
	SetupValue(g_Options.Visuals.teamglow, false, ("Visuals"), ("PlayerGlow Team"));
	SetupValue(g_Options.Visuals.playerglowalpha, 0, ("Visuals"), ("PlayerGlow Alpha"));
	SetupValue(g_Options.Visuals.weaponglow, false, ("Visuals"), ("WeaponGlow"));
	SetupValue(g_Options.Visuals.weaponglowalpha, 0, ("Visuals"), ("WeaponGlow Alpha"));
	SetupValue(g_Options.Visuals.bombglow, false, ("Visuals"), ("BombGlow"));
	SetupValue(g_Options.Visuals.bombglowalpha, 0, ("Visuals"), ("BombGlow Alpha"));
	SetupValue(g_Options.Visuals.angleLines, false, ("Visuals"), ("AngleLines"));
	SetupValue(g_Options.Visuals.LBYIndicator, false, ("Visuals"), ("LBY Indicator"));
	SetupValue(g_Options.Visuals.DrawAwall, false, ("Visuals"), ("Awall Indicator"));

	SetupValue(g_Options.Misc.nightMode, false, ("Visuals"), ("Nightmode"));
	SetupValue(g_Options.Visuals.Bomb, false, ("Visuals"), ("BombEsp"));


	SetupValue(g_Options.Misc.Bhop, false, ("Misc"), ("Bhop"));
	SetupValue(g_Options.Misc.AutoStrafe, false, ("Misc"), ("Autostrafe"));
	SetupValue(g_Options.Misc.clantag_SLN, 0, ("Misc"), ("clantag_SLN"));

	SetupValue(g_Options.Misc.fakewalk, false, ("Misc"), ("fakewalk"));
	SetupValue(g_Options.Misc.fakewalkkey, false, ("Misc"), ("fakewalkkey"));
	SetupValue(g_Options.Misc.moonwalk, false, ("Misc"), ("moonwalk"));
	// SetupValue(g_Options.Misc.SpecList, false, ("Misc"), ("speclist"));
	// SetupValue(g_Options.Misc.ragequit, 0, ("Misc"), ("ragequit-key"));

	/*
	SetupValue(g_Options.Skinchanger.Enabled, false, ("Skinchanger"), ("Enabled"));
	SetupValue(g_Options.Skinchanger.Knife, 0, ("SkinChanger"), ("Knife"));
	SetupValue(g_Options.Skinchanger.KnifeSkin, 0, ("SkinChanger"), ("KnifeSkin"));
	SetupValue(g_Options.Skinchanger.gloves, 0, ("SkinChanger"), ("gloves"));

	SetupValue(g_Options.Skinchanger.AK47Skin, 0, ("SkinChanger"), ("AK47Skin"));
	SetupValue(g_Options.Skinchanger.M4A1SSkin, 0, ("SkinChanger"), ("M4A1SSkin"));
	SetupValue(g_Options.Skinchanger.M4A4Skin, 0, ("SkinChanger"), ("M4A4Skin"));
	SetupValue(g_Options.Skinchanger.AUGSkin, 0, ("SkinChanger"), ("AUGSkin"));
	SetupValue(g_Options.Skinchanger.FAMASSkin, 0, ("SkinChanger"), ("FAMASSkin"));

	SetupValue(g_Options.Skinchanger.AWPSkin, 0, ("SkinChanger"), ("AWPSkin"));
	SetupValue(g_Options.Skinchanger.SSG08Skin, 0, ("SkinChanger"), ("SSG08Skin"));
	SetupValue(g_Options.Skinchanger.SCAR20Skin, 0, ("SkinChanger"), ("SCAR20Skin"));

	SetupValue(g_Options.Skinchanger.P90Skin, 0, ("SkinChanger"), ("P90Skin"));
	SetupValue(g_Options.Skinchanger.UMP45Skin, 0, ("SkinChanger"), ("UMP45Skin"));

	SetupValue(g_Options.Skinchanger.GlockSkin, 0, ("SkinChanger"), ("GlockSkin"));
	SetupValue(g_Options.Skinchanger.USPSkin, 0, ("SkinChanger"), ("USPSkin"));
	SetupValue(g_Options.Skinchanger.DeagleSkin, 0, ("SkinChanger"), ("DeagleSkin"));

	SetupValue(g_Options.Skinchanger.tec9Skin, 0, ("SkinChanger"), ("tec9Skin"));
	SetupValue(g_Options.Skinchanger.P2000Skin, 0, ("SkinChanger"), ("P2000Skin"));
	SetupValue(g_Options.Skinchanger.P250Skin, 0, ("SkinChanger"), ("P250Skin"));*/
}

void CConfig::SetupValue(int &value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue<int>(category, name, &value));
}

void CConfig::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue<float>(category, name, &value));
}

void CConfig::SetupValue(bool &value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue<bool>(category, name, &value));
}

void CConfig::Save()
{
    static TCHAR path[MAX_PATH];
    std::string folder, file;
 
    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
    {
 
 
        folder = std::string(path) + ("\\\\");
        switch (g_Options.Menu.ConfigFile)
        {
        case 0:
            file = std::string(path) + ("\\\\") + std::string("Legit") + XorStr("");
            break;
        case 1:
            file = std::string(path) + ("\\\\") + std::string("HvH-Scout") + XorStr("");
            break;
        case 2:
            file = std::string(path) + ("\\\\") + std::string("HvH-Auto") + XorStr("");
            break;
        case 3:
            file = std::string(path) + ("\\\\") + std::string("Rage") + XorStr("");
            break;
        }
 
    }
 
    CreateDirectory(folder.c_str(), NULL);
 
    for (auto value : ints)
        WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());
 
    for (auto value : floats)
        WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());
 
    for (auto value : bools)
        WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}
 
void CConfig::Load()
{
    static TCHAR path[MAX_PATH];
    std::string folder, file;
 
    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
    {
        folder = std::string(path) + ("\\\\");
        switch (g_Options.Menu.ConfigFile)
        {
        case 0:
            file = std::string(path) + ("\\\\") + std::string("Legit") + XorStr("");;
            break;
        case 1:
            file = std::string(path) + ("\\\\") + std::string("HvH-Scout") + XorStr("");;
            break;
        case 2:
            file = std::string(path) + ("\\\\") + std::string("HvH-Auto") + XorStr("");;
            break;
        case 3:
            file = std::string(path) + ("\\\\") + std::string("Rage") + XorStr("");;
            break;
        }
    }

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = (float)atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

CConfig* Config = new CConfig();
Variables g_Options;