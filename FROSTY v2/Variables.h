#pragma once
#include <set>
#include <map>
#include <unordered_map>

extern void RenderInterface();

struct skinInfo
{
	int seed = -1;
	int paintkit;
	std::string tagName;
};


struct Variables
{
	Variables()
	{

	}

	struct Ragebot_s
	{
		bool	MainSwitch;
		bool 	Enabled;
		bool 	AutoFire;
		float 	FOV;
		bool 	Silent;
		bool	AutoPistol;
		int		KeyPress;
		bool	AimStep;

		//AA Builder 
		//THESE NOW BECOME WHAT I WILL SET DEPENDING ON THE MVOEMENT TYPE EXACMPLE: IF WERE WALKING { JITTER = WALK_JITTER; } //LESS CODE!
		bool	BuilderAAs;
		bool	Jitter;
		bool	FJitter;
		bool	LBYBreaker;
		float	BuilderReal;
		float	BuilderFake;
		float	BuilderPitch;
		float	JitterRange;
		float	FJitterRange;


		//walking builder aa's
		bool	walk_BuilderAAs;
		bool	walk_Jitter;
		bool	walk_FJitter;
		bool	walk_LBYBreaker;
		float	walk_BuilderReal;
		float	walk_BuilderFake;
		float	walk_BuilderPitch;
		float	walk_JitterRange;
		float	walk_FJitterRange;

		//running builder aa's
		bool	run_BuilderAAs;
		bool	run_Jitter;
		bool	run_FJitter;
		bool	run_LBYBreaker;
		float	run_BuilderReal;
		float	run_BuilderFake;
		float	run_BuilderPitch;
		float	run_JitterRange;
		float	run_FJitterRange;


		//crouching builder aa's
		bool	crouch_BuilderAAs;
		bool	crouch_Jitter;
		bool	crouch_FJitter;
		bool	crouch_LBYBreaker;
		float	crouch_BuilderReal;
		float	crouch_BuilderFake;
		float	crouch_BuilderPitch;
		float	crouch_JitterRange;
		float	crouch_FJitterRange;

		
		//fakewalk builder aa's
		bool	fwalk_BuilderAAs;
		bool	fwalk_Jitter;
		bool	fwalk_FJitter;
		bool	fwalk_LBYBreaker;
		float	fwalk_BuilderReal;
		float	fwalk_BuilderFake;
		float	fwalk_BuilderPitch;
		float	fwalk_JitterRange;
		float	fwalk_FJitterRange;

		
		//standing builder aa's
		bool	stand_BuilderAAs;
		bool	stand_Jitter;
		bool	stand_FJitter;
		bool	stand_LBYBreaker;
		float	stand_BuilderReal;
		float	stand_BuilderFake;
		float	stand_BuilderPitch;
		float	stand_JitterRange;
		float	stand_FJitterRange;


		int flip_aa;

		bool ayywarecrasher = false;

		bool	EnabledAntiAim;
		int		SubAATabs;
		bool	PreAAs;
		int		Pitch;
		int		YawTrue;
		int		YawFake;
		int		YawTrueMove;
		float	PitchAdder;
		float	YawTrueAdder;
		float	YawFakeAdder;
		float	YawFakeMove;
		bool	AtTarget;
		bool	Edge;
		bool	KnifeAA;
		bool	FakeLag;
		int		FakeLagAmt;

		// Pitch  PitchAdder  YawTrue  YawFakeAdder  YawFake  YawFakeAdder

		//walking prebuilt aa
		bool	walk_PreAAs;
		int		walk_Pitch;
		float	walk_PitchAdder;
		int		walk_YawTrue;
		float	walk_YawTrueAdder;
		int		walk_YawFake;
		float	walk_YawFakeAdder;


		//running prebuilt aa
		bool	run_PreAAs;
		int		run_Pitch;
		float	run_PitchAdder;
		int		run_YawTrue;
		float	run_YawTrueAdder;
		int		run_YawFake;
		float	run_YawFakeAdder;

		
		//crouching prebuilt aa
		bool	crouch_PreAAs;
		int		crouch_Pitch;
		float	crouch_PitchAdder;
		int		crouch_YawTrue;
		float	crouch_YawTrueAdder;
		int		crouch_YawFake;
		float	crouch_YawFakeAdder;


		//fakewalk prebuilt aa fwalk
		bool	fwalk_PreAAs;
		int		fwalk_Pitch;
		float	fwalk_PitchAdder;
		int		fwalk_YawTrue;
		float	fwalk_YawTrueAdder;
		int		fwalk_YawFake;
		float	fwalk_YawFakeAdder;

		
		//standing prebuilt aa's 
		bool	stand_PreAAs;
		int		stand_Pitch;
		float	stand_PitchAdder;
		int		stand_YawTrue;
		float	stand_YawTrueAdder;
		int		stand_YawFake;
		float	stand_YawFakeAdder;


		bool stand_allowflip;
		bool fwalk_allowflip;
		bool crouch_allowflip;
		bool walk_allowflip;
		bool run_allowflip;
		
		int flipkey;

		bool fakehead;

		bool walk_fakehead;
		bool run_fakehead;
		bool crouch_fakehead;
		bool fwalk_fakehead;
		bool stand_fakehead;

		int error_type;  //aa warning variable

		bool	FriendlyFire;
		int		Hitbox;
		int		Hitscan;
		float	Pointscale;
		bool	Multipoint;
		float	Multipoints;

		bool	AntiRecoil;
		bool	AutoWall;
		bool	AutoStop;
		int		autostopkey;
		bool	AutoCrouch;
		bool	AutoScope;
		float	MinimumDamageSniper;
		float	MinimumDamageRifle;
		float	MinimumDamagePistol;
		float	MinimumDamageHeavy;
		float	MinimumDamageSmg;
		float	MinimumDamageRevolver;
		bool	Hitchance;
		float	HitchanceSniper;
		float	HitchancePistol;
		float	HitchanceRifle;
		float	HitchanceHeavy;
		float	HitchanceSmgs;
		float	HitchanceRevolver;
		bool	Resolver;
		bool	FakeLagFix;
		bool	PosAdjust;
		bool	playerlist;
		int		BAIMkey;
		float	bruteAfterX;

		
		bool	MovingAA; //eventually get rid of this
		
		//and replace with this
		bool	AA_onRun;
		bool	AA_onWalk;
		bool	AA_onCrouch;
		bool	AA_onFakeWalk;
		bool	AA_onStand;

		bool	break_in_air;
	} Ragebot;

	struct
	{
		bool MainSwitch;
		bool backtrack;
		float backtrackTicks;
		struct
		{
			bool 	Enabled;
			bool AutoPistol;
			bool	Resolver;

		} Aimbot;

		int hitboxrifle;
		int MainKey = 1;
		float MainSmooth;
		float Mainfov;
		float main_random_smooth;
		float main_recoil_min;
		float main_recoil_max;
		float main_randomized_angle;


		int hitboxpistol;
		int PistolKey = 6;
		float Pistolfov;
		float PistolSmooth;
		float pistol_random_smooth;
		float pistol_recoil_min;
		float pistol_recoil_max;
		float pistol_randomized_angle;


		int hitboxsniper;
		int SniperKey = 6;
		float Sniperfov;
		float SniperSmooth;
		float sniper_random_smooth;
		float sniper_recoil_min;
		float sniper_recoil_max;
		float sniper_randomized_angle;


		struct
		{
			bool	Enabled;
			float Delay;
			int Key = 6;
			float hitchance;
			struct
			{
				bool Head;
				bool Arms;
				bool Chest;
				bool Stomach;
				bool Legs;
			} Filter;

		} Triggerbot;

	} Legitbot;

	struct
	{
		bool TeamESP;
		bool Box;
		int BoxType;
		bool health;
		bool Armor;
		bool Money;
		bool VisCheck;
		bool Name;
		bool Distance;
		bool Skeleton;
		bool Callout;
		bool Weapon;
		int wpnmode;
		bool Flashed;
		bool AimLine;
		bool angleLines;
		bool barrel;
		int barrelL;
		bool DrawAwall;
		bool LBYIndicator;

		bool Bomb;
		bool resolveMode;

		bool Droppedguns;
		bool Grenades;

		int chamsubtab = 0;

		bool Chams;
		int matierial;
		bool outline;
		bool Teamchams;
		int champlayeralpha;

		bool Chamweapon;
		bool XQZ;

		bool handcham;
		bool weaponviewcham;
		int chamhandalpha;

		int weaponmat;
		int handmat;
		int weaponhandalpha;

		bool Crosshair;
		bool xSpread;
		bool xRecoil;

		bool Hitmarker = true;
		int Hitsound = 4;

		bool EventLog;

		bool NoVisualRecoil;
		float FOVChanger;
		float viewmodelChanger = 68;
		bool NoFlash;
		bool NoSmoke;
		int TPKey;
		float tpdist = 200;
		bool ThirdPerson;
		bool Time = true;

		bool noscopeborder;
		bool GrenadePrediction;
		bool bChamsFakeAA;

		int glowsubtab = 0;
		bool glowplayer;
		int playerglowalpha;
		bool teamglow;

		bool weaponglow;
		int weaponglowalpha;

		bool bombglow;
		int bombglowalpha;



	} Visuals;

	struct
	{
		bool antiuntrusted = true;
		bool silentstealer;
		int ragequit;
		bool 	Bhop;
		bool 	AutoStrafe;
		float MinVel;
		int		AirStuckKey;
		int lagexploit;
		int lagexploitmultiplier = 3;
		float lagexploitvalue;
		float FakeLag;
		bool AdaptiveFakeLag;
		bool nightMode;
		int NameSpammer;
		bool NameChangerFix;
		bool NoName;
		int		ChatSpamMode;
		bool ClantagChanger;
		int ClanTagSpeed;
		bool syncclantag;
		bool breathless_clantag;

		int clantag_SLN;

		bool SpecList;
		bool FPSBooster;
		int SkyBoxChanger;
		bool namespam;
		int spammer;
		int AutoDefuse;
		bool Spam;
		bool isRecording;
		bool isReplaying;
		bool RecordPath;
		bool AutoAccept;
		bool SpoofConfirmation = false;
		bool animatedclantag = false;
		int customtab;
		int Slowmo;

		bool niggatest;

		bool show_the_fucking_shit = false;
		float dab_on_the_haters = 0.f;

		bool legit_aa = false;

		bool moonwalk = false;
		bool spookwalk = false;

		int fakewalkkey;
		bool fakewalk = false;


	} Misc;
	struct
	{
		bool Enabled;

		int knifemodel;

		int glove;
		int gloeskin;


		class WeaponCFG
		{
		public:
			bool ChangerEnabled = false;
			int ChangerSkin = 0;
			char ChangerName[32] = "";
			int ChangerStatTrak = 0;
			int ChangerSeed = 0;
			float ChangerWear = 0;
		};
		WeaponCFG* W = new WeaponCFG[520];

		std::unordered_map<std::string, std::set<std::string>> weaponSkins;
		std::unordered_map<std::string, skinInfo> skinMap;
		std::unordered_map<std::string, std::string> skinNames;
		std::vector<std::string> weaponNames;
	} Skinchanger;

	struct
	{
		bool	Opened = false;
		int 	Key;
		int		rageSubtab;
		int		ConfigFile = 0;
		int		Theme = 0;
		int		iTab;
		bool	bShowTabs;
		float   flMainAlpha;
		float   flTabsAlpha;
		int currentWeapon;
	} Menu;

	struct
	{
		float TeamESP[3] = { 0, 1.f, 0 };
		float EnemyESP[3] = { 1.f, 0, 0 };
		float TeamDLights[3] = { 0, 1.f, 0 };
		float EnemyDLights[3] = { 1.f, 0, 0 };
		float EnemyGlow[3] = { 1.f, 0, 0 };
		float TeamGlow[3] = { 0, 1.f, 0 };
		float WeaponGlow[3] = { 1.f, 0, 0 };
		float C4glow[3] = { 1.f, 0, 0 };
		float EnemyChamsVis[3] = { 1.f, 0, 0 };
		float EnemyChamsNVis[3] = { 1.f, 0, 0 };
		float TeamChamsVis[3] = { 0, 1.f, 0 };
		float TeamChamsNVis[3] = { 0, 1.f, 0 };
		float WeaponCham[3] = { 1.f, 0, 0 };
		float HandCham[3] = { 1.f, 0, 0 };
		float WeaponViewCham[3] = { 1.f, 0, 0 };
	}Colors;
};

extern Variables g_Options;