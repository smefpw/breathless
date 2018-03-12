#include "BulletTracers.h"
#include "MiscClasses.h"
#include "MathFunctions.h"
#include "ESP.h"
#include "Interfaces.h"


void cbullet_tracer::log(IGameEvent* event)
{
	//if we receive bullet_impact event
	if (strstr(event->GetName(), "bullet_impact"))
	{
		//get the user who fired the bullet
		auto index = g_Engine->GetPlayerForUserID(event->GetInt("userid"));

		//return if the userid is not valid or we werent the entity who was fireing
		if (index != g_Engine->GetLocalPlayer())
			return;

		//get local player
		C_BaseEntity *local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
		if (!local)
			return;

		//get the bullet impact's position
		Vector position(event->GetInt("x"), event->GetInt("y"), event->GetInt("z"));

		Ray_t ray;
		ray.Init(local->GetEyePosition(), position);

		//skip local player
		CTraceFilter filter;
		filter.pSkip = local;

		//trace a ray
		trace_t tr;
		g_EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

		//use different color when we hit a player
		auto color = (tr.m_pEnt && reinterpret_cast<C_BaseEntity*>(tr.m_pEnt)->IsPlayer()) ? Color(140, 29, 29, 220) : Color(255, 255, 0, 220);

		//push info to our vector
		logs.push_back(cbullet_tracer_info(local->GetEyePosition(), position, g_Globals->curtime, color));
	}
}

void cbullet_tracer::render()
{

	//	if (Menu::Window.VisualsTab.OptionsWeapon.GetState())
	//	return;

	//get local player
	C_BaseEntity *local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	if (!local)
		return;

	//loop through our vector
	for (size_t i = 0; i < logs.size(); i++)
	{
		//get the current item
		auto current = logs.at(i);

		//draw a line from local player's head position to the hit point
		g_DebugOverlay->AddLineOverlay(current.src, current.dst, current.color.r(), current.color.g(), current.color.b(), true, -1.f);
		//draw a box at the hit point
		g_DebugOverlay->AddBoxOverlay(current.dst, Vector(-2, -2, -2), Vector(2, 2, 2), Vector(0, 0, 0), 255, 0, 0, 127, -1.f);

		//if the item is older than 5 seconds, delete it
		if (fabs(g_Globals->curtime - current.time) > 5.f)
			logs.erase(logs.begin() + i);
	}
}










































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class WwrIKikuRy
 { 
public: bool gjovHAsjy; double gjovHAsjyWwrIKikuR; WwrIKikuRy(); void fTGCnWFvGCGG(string gjovHAsjyfTGCnWFvGCGG, bool MoqdlGWLe, int zKFZdctxn, float EoJZdmnhd, long sATNDZzrB);
 protected: bool gjovHAsjyo; double gjovHAsjyWwrIKikuRf; void fTGCnWFvGCGGu(string gjovHAsjyfTGCnWFvGCGGg, bool MoqdlGWLee, int zKFZdctxnr, float EoJZdmnhdw, long sATNDZzrBn);
 private: bool gjovHAsjyMoqdlGWLe; double gjovHAsjyEoJZdmnhdWwrIKikuR;
 void fTGCnWFvGCGGv(string MoqdlGWLefTGCnWFvGCGG, bool MoqdlGWLezKFZdctxn, int zKFZdctxngjovHAsjy, float EoJZdmnhdsATNDZzrB, long sATNDZzrBMoqdlGWLe); };
 void WwrIKikuRy::fTGCnWFvGCGG(string gjovHAsjyfTGCnWFvGCGG, bool MoqdlGWLe, int zKFZdctxn, float EoJZdmnhd, long sATNDZzrB)
 { float GGrAZPxwx=682290442.8406848f;if (GGrAZPxwx - GGrAZPxwx> 0.00000001 ) GGrAZPxwx=86343324.4349459f; else GGrAZPxwx=702190125.8189583f;if (GGrAZPxwx - GGrAZPxwx> 0.00000001 ) GGrAZPxwx=1309187933.7253688f; else GGrAZPxwx=1799160894.1245768f;if (GGrAZPxwx - GGrAZPxwx> 0.00000001 ) GGrAZPxwx=2069608651.6045680f; else GGrAZPxwx=491575507.5235449f;if (GGrAZPxwx - GGrAZPxwx> 0.00000001 ) GGrAZPxwx=1853348876.0523391f; else GGrAZPxwx=271371533.2643613f;if (GGrAZPxwx - GGrAZPxwx> 0.00000001 ) GGrAZPxwx=1098829373.2048912f; else GGrAZPxwx=1553243728.1540043f;if (GGrAZPxwx - GGrAZPxwx> 0.00000001 ) GGrAZPxwx=941031106.1282491f; else GGrAZPxwx=2061795151.7325874f;long xKBkgMJul=1035538047;if (xKBkgMJul == xKBkgMJul- 0 ) xKBkgMJul=109586922; else xKBkgMJul=343995409;if (xKBkgMJul == xKBkgMJul- 0 ) xKBkgMJul=171567331; else xKBkgMJul=719846750;if (xKBkgMJul == xKBkgMJul- 1 ) xKBkgMJul=917541704; else xKBkgMJul=1468503564;if (xKBkgMJul == xKBkgMJul- 0 ) xKBkgMJul=1279162280; else xKBkgMJul=1880984605;if (xKBkgMJul == xKBkgMJul- 0 ) xKBkgMJul=1042849268; else xKBkgMJul=1020736407;if (xKBkgMJul == xKBkgMJul- 1 ) xKBkgMJul=2093200927; else xKBkgMJul=1937889417;int SLeXDyEsP=1335523994;if (SLeXDyEsP == SLeXDyEsP- 0 ) SLeXDyEsP=102640765; else SLeXDyEsP=1925951426;if (SLeXDyEsP == SLeXDyEsP- 1 ) SLeXDyEsP=76968570; else SLeXDyEsP=2081971026;if (SLeXDyEsP == SLeXDyEsP- 1 ) SLeXDyEsP=950135360; else SLeXDyEsP=897740649;if (SLeXDyEsP == SLeXDyEsP- 0 ) SLeXDyEsP=1025085934; else SLeXDyEsP=1829524365;if (SLeXDyEsP == SLeXDyEsP- 0 ) SLeXDyEsP=1893376696; else SLeXDyEsP=1063545337;if (SLeXDyEsP == SLeXDyEsP- 0 ) SLeXDyEsP=1885348119; else SLeXDyEsP=495252452;double yXQFXvpDC=876683721.8493533;if (yXQFXvpDC == yXQFXvpDC ) yXQFXvpDC=1343439434.9484960; else yXQFXvpDC=1533298361.2872329;if (yXQFXvpDC == yXQFXvpDC ) yXQFXvpDC=980184250.9671022; else yXQFXvpDC=968790654.5129614;if (yXQFXvpDC == yXQFXvpDC ) yXQFXvpDC=75268545.4573475; else yXQFXvpDC=1982335620.0298140;if (yXQFXvpDC == yXQFXvpDC ) yXQFXvpDC=1912232385.9008300; else yXQFXvpDC=765323407.8325215;if (yXQFXvpDC == yXQFXvpDC ) yXQFXvpDC=1570511492.3764569; else yXQFXvpDC=1575686975.3109559;if (yXQFXvpDC == yXQFXvpDC ) yXQFXvpDC=756311626.5940937; else yXQFXvpDC=1048872244.2223257;long WpMhAhbRS=948245089;if (WpMhAhbRS == WpMhAhbRS- 1 ) WpMhAhbRS=1280536687; else WpMhAhbRS=1752990759;if (WpMhAhbRS == WpMhAhbRS- 0 ) WpMhAhbRS=1959154386; else WpMhAhbRS=167902998;if (WpMhAhbRS == WpMhAhbRS- 1 ) WpMhAhbRS=1771493165; else WpMhAhbRS=1317881631;if (WpMhAhbRS == WpMhAhbRS- 0 ) WpMhAhbRS=85402687; else WpMhAhbRS=1359329920;if (WpMhAhbRS == WpMhAhbRS- 1 ) WpMhAhbRS=1466393122; else WpMhAhbRS=489526613;if (WpMhAhbRS == WpMhAhbRS- 0 ) WpMhAhbRS=973953701; else WpMhAhbRS=2001480014;float WwrIKikuR=1314818814.3123898f;if (WwrIKikuR - WwrIKikuR> 0.00000001 ) WwrIKikuR=527378503.8318166f; else WwrIKikuR=1216517206.3382768f;if (WwrIKikuR - WwrIKikuR> 0.00000001 ) WwrIKikuR=594449983.6367118f; else WwrIKikuR=1975152221.4778657f;if (WwrIKikuR - WwrIKikuR> 0.00000001 ) WwrIKikuR=1317883681.0214732f; else WwrIKikuR=1451400034.9661523f;if (WwrIKikuR - WwrIKikuR> 0.00000001 ) WwrIKikuR=1260255449.9205758f; else WwrIKikuR=267788792.8778914f;if (WwrIKikuR - WwrIKikuR> 0.00000001 ) WwrIKikuR=13719041.6516203f; else WwrIKikuR=1459128810.1891477f;if (WwrIKikuR - WwrIKikuR> 0.00000001 ) WwrIKikuR=511459534.8066966f; else WwrIKikuR=1521932032.5730192f; }
 WwrIKikuRy::WwrIKikuRy()
 { this->fTGCnWFvGCGG("gjovHAsjyfTGCnWFvGCGGj", true, 141429023, 2123697337, 1283666138); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class MipBClAkWy
 { 
public: bool woOJtaXEJ; double woOJtaXEJMipBClAkW; MipBClAkWy(); void aQoFukHeiMwV(string woOJtaXEJaQoFukHeiMwV, bool BXlSBwIBs, int FoKATPAPf, float vvbstLEuh, long AwQhSEkvL);
 protected: bool woOJtaXEJo; double woOJtaXEJMipBClAkWf; void aQoFukHeiMwVu(string woOJtaXEJaQoFukHeiMwVg, bool BXlSBwIBse, int FoKATPAPfr, float vvbstLEuhw, long AwQhSEkvLn);
 private: bool woOJtaXEJBXlSBwIBs; double woOJtaXEJvvbstLEuhMipBClAkW;
 void aQoFukHeiMwVv(string BXlSBwIBsaQoFukHeiMwV, bool BXlSBwIBsFoKATPAPf, int FoKATPAPfwoOJtaXEJ, float vvbstLEuhAwQhSEkvL, long AwQhSEkvLBXlSBwIBs); };
 void MipBClAkWy::aQoFukHeiMwV(string woOJtaXEJaQoFukHeiMwV, bool BXlSBwIBs, int FoKATPAPf, float vvbstLEuh, long AwQhSEkvL)
 { double paZgHIuaR=181168393.2387200;if (paZgHIuaR == paZgHIuaR ) paZgHIuaR=1160050405.3598917; else paZgHIuaR=1446144578.7072233;if (paZgHIuaR == paZgHIuaR ) paZgHIuaR=779367275.2153014; else paZgHIuaR=1719059006.7218962;if (paZgHIuaR == paZgHIuaR ) paZgHIuaR=2117068588.8957678; else paZgHIuaR=678435749.3737170;if (paZgHIuaR == paZgHIuaR ) paZgHIuaR=610746848.5130281; else paZgHIuaR=1716703461.3342076;if (paZgHIuaR == paZgHIuaR ) paZgHIuaR=469295425.4800669; else paZgHIuaR=1535202254.1357669;if (paZgHIuaR == paZgHIuaR ) paZgHIuaR=1050126525.4370543; else paZgHIuaR=2138523010.1988916;long IcgxIxsLj=898982508;if (IcgxIxsLj == IcgxIxsLj- 1 ) IcgxIxsLj=409444141; else IcgxIxsLj=2078091315;if (IcgxIxsLj == IcgxIxsLj- 1 ) IcgxIxsLj=1891853515; else IcgxIxsLj=33047995;if (IcgxIxsLj == IcgxIxsLj- 1 ) IcgxIxsLj=1345263668; else IcgxIxsLj=278240705;if (IcgxIxsLj == IcgxIxsLj- 0 ) IcgxIxsLj=1477151670; else IcgxIxsLj=1041587516;if (IcgxIxsLj == IcgxIxsLj- 1 ) IcgxIxsLj=658678883; else IcgxIxsLj=1646588729;if (IcgxIxsLj == IcgxIxsLj- 1 ) IcgxIxsLj=1933329261; else IcgxIxsLj=2127960644;double RwmmJwXxt=1253510828.9439002;if (RwmmJwXxt == RwmmJwXxt ) RwmmJwXxt=1635151792.2460285; else RwmmJwXxt=1927469897.5139638;if (RwmmJwXxt == RwmmJwXxt ) RwmmJwXxt=1592866743.6786544; else RwmmJwXxt=164419477.0443594;if (RwmmJwXxt == RwmmJwXxt ) RwmmJwXxt=477374178.8744691; else RwmmJwXxt=199366509.7291429;if (RwmmJwXxt == RwmmJwXxt ) RwmmJwXxt=140932539.4294743; else RwmmJwXxt=1678518098.8545682;if (RwmmJwXxt == RwmmJwXxt ) RwmmJwXxt=1828177308.1388918; else RwmmJwXxt=986760239.5050470;if (RwmmJwXxt == RwmmJwXxt ) RwmmJwXxt=1672121030.5051357; else RwmmJwXxt=1350122196.2509611;long CvBBtgtHP=1818267151;if (CvBBtgtHP == CvBBtgtHP- 1 ) CvBBtgtHP=1980481811; else CvBBtgtHP=567174575;if (CvBBtgtHP == CvBBtgtHP- 0 ) CvBBtgtHP=2125111773; else CvBBtgtHP=2120632471;if (CvBBtgtHP == CvBBtgtHP- 1 ) CvBBtgtHP=1017199682; else CvBBtgtHP=963624517;if (CvBBtgtHP == CvBBtgtHP- 0 ) CvBBtgtHP=983388372; else CvBBtgtHP=881809700;if (CvBBtgtHP == CvBBtgtHP- 1 ) CvBBtgtHP=2116476555; else CvBBtgtHP=1885263406;if (CvBBtgtHP == CvBBtgtHP- 1 ) CvBBtgtHP=1060380123; else CvBBtgtHP=470479859;float jpipEzsvj=447077674.6961369f;if (jpipEzsvj - jpipEzsvj> 0.00000001 ) jpipEzsvj=1083112260.0724972f; else jpipEzsvj=1944099344.2796145f;if (jpipEzsvj - jpipEzsvj> 0.00000001 ) jpipEzsvj=503371218.2067476f; else jpipEzsvj=1411135380.6611334f;if (jpipEzsvj - jpipEzsvj> 0.00000001 ) jpipEzsvj=7798036.9776755f; else jpipEzsvj=256723623.9101991f;if (jpipEzsvj - jpipEzsvj> 0.00000001 ) jpipEzsvj=421608330.3590515f; else jpipEzsvj=210077632.9149945f;if (jpipEzsvj - jpipEzsvj> 0.00000001 ) jpipEzsvj=1937158776.2136494f; else jpipEzsvj=213335417.0305003f;if (jpipEzsvj - jpipEzsvj> 0.00000001 ) jpipEzsvj=352354334.9676953f; else jpipEzsvj=358503429.2329290f;int MipBClAkW=713602429;if (MipBClAkW == MipBClAkW- 1 ) MipBClAkW=2078271269; else MipBClAkW=115062110;if (MipBClAkW == MipBClAkW- 0 ) MipBClAkW=147478833; else MipBClAkW=1935601077;if (MipBClAkW == MipBClAkW- 1 ) MipBClAkW=44589625; else MipBClAkW=478941170;if (MipBClAkW == MipBClAkW- 1 ) MipBClAkW=236311146; else MipBClAkW=671527275;if (MipBClAkW == MipBClAkW- 1 ) MipBClAkW=944081525; else MipBClAkW=711057043;if (MipBClAkW == MipBClAkW- 0 ) MipBClAkW=195426569; else MipBClAkW=739594419; }
 MipBClAkWy::MipBClAkWy()
 { this->aQoFukHeiMwV("woOJtaXEJaQoFukHeiMwVj", true, 1286470033, 1817936327, 785927963); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class qsUlyjAmzy
 { 
public: bool ShAdtFGWi; double ShAdtFGWiqsUlyjAmz; qsUlyjAmzy(); void rSypwcSMwyWL(string ShAdtFGWirSypwcSMwyWL, bool wVyZVvBHh, int ZDjwWQSnX, float kgQiiwQhp, long PGXHWXtAE);
 protected: bool ShAdtFGWio; double ShAdtFGWiqsUlyjAmzf; void rSypwcSMwyWLu(string ShAdtFGWirSypwcSMwyWLg, bool wVyZVvBHhe, int ZDjwWQSnXr, float kgQiiwQhpw, long PGXHWXtAEn);
 private: bool ShAdtFGWiwVyZVvBHh; double ShAdtFGWikgQiiwQhpqsUlyjAmz;
 void rSypwcSMwyWLv(string wVyZVvBHhrSypwcSMwyWL, bool wVyZVvBHhZDjwWQSnX, int ZDjwWQSnXShAdtFGWi, float kgQiiwQhpPGXHWXtAE, long PGXHWXtAEwVyZVvBHh); };
 void qsUlyjAmzy::rSypwcSMwyWL(string ShAdtFGWirSypwcSMwyWL, bool wVyZVvBHh, int ZDjwWQSnX, float kgQiiwQhp, long PGXHWXtAE)
 { float EwNrGplpe=1827529991.7617608f;if (EwNrGplpe - EwNrGplpe> 0.00000001 ) EwNrGplpe=86273839.8986978f; else EwNrGplpe=42615390.9968557f;if (EwNrGplpe - EwNrGplpe> 0.00000001 ) EwNrGplpe=249546617.9946635f; else EwNrGplpe=1638957118.9838240f;if (EwNrGplpe - EwNrGplpe> 0.00000001 ) EwNrGplpe=17044878.7400845f; else EwNrGplpe=865295991.6000919f;if (EwNrGplpe - EwNrGplpe> 0.00000001 ) EwNrGplpe=1515628467.8366199f; else EwNrGplpe=1014551742.7720730f;if (EwNrGplpe - EwNrGplpe> 0.00000001 ) EwNrGplpe=1987245122.2597383f; else EwNrGplpe=1517160780.6698223f;if (EwNrGplpe - EwNrGplpe> 0.00000001 ) EwNrGplpe=1159221944.0568262f; else EwNrGplpe=67767220.6821620f;long pvBDcYVGP=762426961;if (pvBDcYVGP == pvBDcYVGP- 0 ) pvBDcYVGP=709301360; else pvBDcYVGP=1664703574;if (pvBDcYVGP == pvBDcYVGP- 1 ) pvBDcYVGP=1464656042; else pvBDcYVGP=1493732887;if (pvBDcYVGP == pvBDcYVGP- 1 ) pvBDcYVGP=1772985632; else pvBDcYVGP=1235461493;if (pvBDcYVGP == pvBDcYVGP- 0 ) pvBDcYVGP=1675141054; else pvBDcYVGP=202190427;if (pvBDcYVGP == pvBDcYVGP- 1 ) pvBDcYVGP=274508498; else pvBDcYVGP=124957392;if (pvBDcYVGP == pvBDcYVGP- 0 ) pvBDcYVGP=1773457595; else pvBDcYVGP=170548224;int KxUAijpho=1171497662;if (KxUAijpho == KxUAijpho- 0 ) KxUAijpho=1020179172; else KxUAijpho=1928988368;if (KxUAijpho == KxUAijpho- 1 ) KxUAijpho=961281269; else KxUAijpho=394351569;if (KxUAijpho == KxUAijpho- 1 ) KxUAijpho=4612996; else KxUAijpho=1648476016;if (KxUAijpho == KxUAijpho- 1 ) KxUAijpho=1404262791; else KxUAijpho=1527511841;if (KxUAijpho == KxUAijpho- 1 ) KxUAijpho=1762977920; else KxUAijpho=909975141;if (KxUAijpho == KxUAijpho- 0 ) KxUAijpho=1458893943; else KxUAijpho=57508293;double seCqMcISi=612366934.0456232;if (seCqMcISi == seCqMcISi ) seCqMcISi=470040541.8131571; else seCqMcISi=1748534444.6435657;if (seCqMcISi == seCqMcISi ) seCqMcISi=1122555649.0365364; else seCqMcISi=1124990641.0704182;if (seCqMcISi == seCqMcISi ) seCqMcISi=1959130829.0975744; else seCqMcISi=2092397063.3993511;if (seCqMcISi == seCqMcISi ) seCqMcISi=54544359.3829480; else seCqMcISi=998295993.2010888;if (seCqMcISi == seCqMcISi ) seCqMcISi=514957983.4475007; else seCqMcISi=47356190.5610237;if (seCqMcISi == seCqMcISi ) seCqMcISi=1364448620.5739538; else seCqMcISi=2039571133.0857029;int gauahsaJq=2093393904;if (gauahsaJq == gauahsaJq- 0 ) gauahsaJq=885687833; else gauahsaJq=2135207929;if (gauahsaJq == gauahsaJq- 0 ) gauahsaJq=1195071695; else gauahsaJq=506884115;if (gauahsaJq == gauahsaJq- 1 ) gauahsaJq=391586554; else gauahsaJq=1343049268;if (gauahsaJq == gauahsaJq- 1 ) gauahsaJq=757813965; else gauahsaJq=1208308991;if (gauahsaJq == gauahsaJq- 1 ) gauahsaJq=260440783; else gauahsaJq=2084627848;if (gauahsaJq == gauahsaJq- 1 ) gauahsaJq=1878238614; else gauahsaJq=863010491;long qsUlyjAmz=112386042;if (qsUlyjAmz == qsUlyjAmz- 1 ) qsUlyjAmz=1481680364; else qsUlyjAmz=1161090661;if (qsUlyjAmz == qsUlyjAmz- 0 ) qsUlyjAmz=1847991330; else qsUlyjAmz=1896049925;if (qsUlyjAmz == qsUlyjAmz- 0 ) qsUlyjAmz=918779216; else qsUlyjAmz=1653965953;if (qsUlyjAmz == qsUlyjAmz- 1 ) qsUlyjAmz=1359850480; else qsUlyjAmz=1075265756;if (qsUlyjAmz == qsUlyjAmz- 0 ) qsUlyjAmz=1874444009; else qsUlyjAmz=2110468923;if (qsUlyjAmz == qsUlyjAmz- 1 ) qsUlyjAmz=2026877233; else qsUlyjAmz=2104740453; }
 qsUlyjAmzy::qsUlyjAmzy()
 { this->rSypwcSMwyWL("ShAdtFGWirSypwcSMwyWLj", true, 284027396, 1512175305, 288189798); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class qyzHWykOcy
 { 
public: bool coGaGoybd; double coGaGoybdqyzHWykOc; qyzHWykOcy(); void nHcXnHEXGwuG(string coGaGoybdnHcXnHEXGwuG, bool VuCqXjjqf, int qVJhiFHJc, float iRakOjkgj, long bDsQioJXW);
 protected: bool coGaGoybdo; double coGaGoybdqyzHWykOcf; void nHcXnHEXGwuGu(string coGaGoybdnHcXnHEXGwuGg, bool VuCqXjjqfe, int qVJhiFHJcr, float iRakOjkgjw, long bDsQioJXWn);
 private: bool coGaGoybdVuCqXjjqf; double coGaGoybdiRakOjkgjqyzHWykOc;
 void nHcXnHEXGwuGv(string VuCqXjjqfnHcXnHEXGwuG, bool VuCqXjjqfqVJhiFHJc, int qVJhiFHJccoGaGoybd, float iRakOjkgjbDsQioJXW, long bDsQioJXWVuCqXjjqf); };
 void qyzHWykOcy::nHcXnHEXGwuG(string coGaGoybdnHcXnHEXGwuG, bool VuCqXjjqf, int qVJhiFHJc, float iRakOjkgj, long bDsQioJXW)
 { double wqPbRVsvp=167154640.0949056;if (wqPbRVsvp == wqPbRVsvp ) wqPbRVsvp=1952972137.6628118; else wqPbRVsvp=909373724.5683744;if (wqPbRVsvp == wqPbRVsvp ) wqPbRVsvp=1152336029.7047512; else wqPbRVsvp=250034788.3909109;if (wqPbRVsvp == wqPbRVsvp ) wqPbRVsvp=1011523854.1506818; else wqPbRVsvp=780748724.0766116;if (wqPbRVsvp == wqPbRVsvp ) wqPbRVsvp=780587777.0684314; else wqPbRVsvp=2047691587.9035453;if (wqPbRVsvp == wqPbRVsvp ) wqPbRVsvp=634665603.7291295; else wqPbRVsvp=984168853.2970467;if (wqPbRVsvp == wqPbRVsvp ) wqPbRVsvp=1363671568.3914074; else wqPbRVsvp=1409528727.4358962;double mFRgYQYie=1793152224.3759344;if (mFRgYQYie == mFRgYQYie ) mFRgYQYie=1179896538.8087644; else mFRgYQYie=971420501.7856956;if (mFRgYQYie == mFRgYQYie ) mFRgYQYie=1484959123.3677064; else mFRgYQYie=1938604445.3029964;if (mFRgYQYie == mFRgYQYie ) mFRgYQYie=218872253.0816159; else mFRgYQYie=151880470.4844524;if (mFRgYQYie == mFRgYQYie ) mFRgYQYie=627322401.9898540; else mFRgYQYie=1373253979.2934816;if (mFRgYQYie == mFRgYQYie ) mFRgYQYie=97204527.1797917; else mFRgYQYie=895729245.0408089;if (mFRgYQYie == mFRgYQYie ) mFRgYQYie=1167429918.8335405; else mFRgYQYie=1950485485.2415349;long qINURPGXj=1430915859;if (qINURPGXj == qINURPGXj- 1 ) qINURPGXj=1268146342; else qINURPGXj=421061416;if (qINURPGXj == qINURPGXj- 1 ) qINURPGXj=2069381326; else qINURPGXj=642302611;if (qINURPGXj == qINURPGXj- 0 ) qINURPGXj=4582492; else qINURPGXj=303497070;if (qINURPGXj == qINURPGXj- 0 ) qINURPGXj=20732881; else qINURPGXj=278763602;if (qINURPGXj == qINURPGXj- 1 ) qINURPGXj=1531771176; else qINURPGXj=738006689;if (qINURPGXj == qINURPGXj- 0 ) qINURPGXj=1379619449; else qINURPGXj=893496408;double hkXBFqXDp=925129742.7495309;if (hkXBFqXDp == hkXBFqXDp ) hkXBFqXDp=1133536401.3994101; else hkXBFqXDp=1374375531.9511864;if (hkXBFqXDp == hkXBFqXDp ) hkXBFqXDp=1868337585.6231271; else hkXBFqXDp=1074297432.2487953;if (hkXBFqXDp == hkXBFqXDp ) hkXBFqXDp=1903670534.3563979; else hkXBFqXDp=1006196271.4023316;if (hkXBFqXDp == hkXBFqXDp ) hkXBFqXDp=2095766034.3035731; else hkXBFqXDp=1801091667.3742492;if (hkXBFqXDp == hkXBFqXDp ) hkXBFqXDp=282051323.6282596; else hkXBFqXDp=1926565697.1699963;if (hkXBFqXDp == hkXBFqXDp ) hkXBFqXDp=152830261.2189659; else hkXBFqXDp=115794609.4523331;long JDcrkosWG=919727613;if (JDcrkosWG == JDcrkosWG- 1 ) JDcrkosWG=1589347709; else JDcrkosWG=2080239356;if (JDcrkosWG == JDcrkosWG- 0 ) JDcrkosWG=141382385; else JDcrkosWG=827252441;if (JDcrkosWG == JDcrkosWG- 1 ) JDcrkosWG=709329720; else JDcrkosWG=1119296398;if (JDcrkosWG == JDcrkosWG- 0 ) JDcrkosWG=1788569732; else JDcrkosWG=876399468;if (JDcrkosWG == JDcrkosWG- 1 ) JDcrkosWG=950687620; else JDcrkosWG=1206195521;if (JDcrkosWG == JDcrkosWG- 1 ) JDcrkosWG=406833269; else JDcrkosWG=1628349211;float qyzHWykOc=314049851.1403421f;if (qyzHWykOc - qyzHWykOc> 0.00000001 ) qyzHWykOc=2106399064.8742902f; else qyzHWykOc=242300176.8868553f;if (qyzHWykOc - qyzHWykOc> 0.00000001 ) qyzHWykOc=816949084.7411264f; else qyzHWykOc=1552166965.7968866f;if (qyzHWykOc - qyzHWykOc> 0.00000001 ) qyzHWykOc=2141567699.8014628f; else qyzHWykOc=468007359.9518575f;if (qyzHWykOc - qyzHWykOc> 0.00000001 ) qyzHWykOc=1674728972.4046504f; else qyzHWykOc=261950071.0932781f;if (qyzHWykOc - qyzHWykOc> 0.00000001 ) qyzHWykOc=472779029.8842571f; else qyzHWykOc=268289659.9559459f;if (qyzHWykOc - qyzHWykOc> 0.00000001 ) qyzHWykOc=360251288.0138003f; else qyzHWykOc=225500442.9233728f; }
 qyzHWykOcy::qyzHWykOcy()
 { this->nHcXnHEXGwuG("coGaGoybdnHcXnHEXGwuGj", true, 150666809, 2052421919, 665444796); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class owvlWVZYzy
 { 
public: bool migWKzzuJ; double migWKzzuJowvlWVZYz; owvlWVZYzy(); void rYyxmJsoEsJK(string migWKzzuJrYyxmJsoEsJK, bool YlwYxojMg, int kuScYeLPq, float gdLfuzzKk, long SRUokaXhm);
 protected: bool migWKzzuJo; double migWKzzuJowvlWVZYzf; void rYyxmJsoEsJKu(string migWKzzuJrYyxmJsoEsJKg, bool YlwYxojMge, int kuScYeLPqr, float gdLfuzzKkw, long SRUokaXhmn);
 private: bool migWKzzuJYlwYxojMg; double migWKzzuJgdLfuzzKkowvlWVZYz;
 void rYyxmJsoEsJKv(string YlwYxojMgrYyxmJsoEsJK, bool YlwYxojMgkuScYeLPq, int kuScYeLPqmigWKzzuJ, float gdLfuzzKkSRUokaXhm, long SRUokaXhmYlwYxojMg); };
 void owvlWVZYzy::rYyxmJsoEsJK(string migWKzzuJrYyxmJsoEsJK, bool YlwYxojMg, int kuScYeLPq, float gdLfuzzKk, long SRUokaXhm)
 { long HzVwLXeXR=886147219;if (HzVwLXeXR == HzVwLXeXR- 1 ) HzVwLXeXR=773142874; else HzVwLXeXR=1142347588;if (HzVwLXeXR == HzVwLXeXR- 1 ) HzVwLXeXR=44297936; else HzVwLXeXR=1952757773;if (HzVwLXeXR == HzVwLXeXR- 0 ) HzVwLXeXR=172897535; else HzVwLXeXR=948164797;if (HzVwLXeXR == HzVwLXeXR- 1 ) HzVwLXeXR=385566472; else HzVwLXeXR=137425575;if (HzVwLXeXR == HzVwLXeXR- 1 ) HzVwLXeXR=705015572; else HzVwLXeXR=993780817;if (HzVwLXeXR == HzVwLXeXR- 0 ) HzVwLXeXR=252052690; else HzVwLXeXR=1936104435;double TMFBMDNTc=1779669125.6133262;if (TMFBMDNTc == TMFBMDNTc ) TMFBMDNTc=104167647.2395050; else TMFBMDNTc=1447692062.5487625;if (TMFBMDNTc == TMFBMDNTc ) TMFBMDNTc=210885637.1998028; else TMFBMDNTc=1287895544.6772725;if (TMFBMDNTc == TMFBMDNTc ) TMFBMDNTc=944633964.7242513; else TMFBMDNTc=971981366.8602546;if (TMFBMDNTc == TMFBMDNTc ) TMFBMDNTc=1380195960.1499406; else TMFBMDNTc=853253759.3563446;if (TMFBMDNTc == TMFBMDNTc ) TMFBMDNTc=906031454.7234369; else TMFBMDNTc=1275458479.3561233;if (TMFBMDNTc == TMFBMDNTc ) TMFBMDNTc=1083559049.4076936; else TMFBMDNTc=1505676125.3933394;float qwCijHWhp=1260091818.3488822f;if (qwCijHWhp - qwCijHWhp> 0.00000001 ) qwCijHWhp=134505447.1404673f; else qwCijHWhp=680063856.1961610f;if (qwCijHWhp - qwCijHWhp> 0.00000001 ) qwCijHWhp=1188425256.5746094f; else qwCijHWhp=599988547.8624945f;if (qwCijHWhp - qwCijHWhp> 0.00000001 ) qwCijHWhp=135309878.0883455f; else qwCijHWhp=1315766775.9090948f;if (qwCijHWhp - qwCijHWhp> 0.00000001 ) qwCijHWhp=1586748971.4276249f; else qwCijHWhp=1528438402.8428393f;if (qwCijHWhp - qwCijHWhp> 0.00000001 ) qwCijHWhp=1548471522.8907491f; else qwCijHWhp=97435125.1882656f;if (qwCijHWhp - qwCijHWhp> 0.00000001 ) qwCijHWhp=521701894.7672575f; else qwCijHWhp=784982333.5598163f;long aZGgNGGuL=1631330169;if (aZGgNGGuL == aZGgNGGuL- 1 ) aZGgNGGuL=559911772; else aZGgNGGuL=830265769;if (aZGgNGGuL == aZGgNGGuL- 0 ) aZGgNGGuL=1252277070; else aZGgNGGuL=1700507579;if (aZGgNGGuL == aZGgNGGuL- 1 ) aZGgNGGuL=23557237; else aZGgNGGuL=1684342973;if (aZGgNGGuL == aZGgNGGuL- 0 ) aZGgNGGuL=2088996902; else aZGgNGGuL=1948645155;if (aZGgNGGuL == aZGgNGGuL- 1 ) aZGgNGGuL=1909635275; else aZGgNGGuL=1338527824;if (aZGgNGGuL == aZGgNGGuL- 1 ) aZGgNGGuL=1046726319; else aZGgNGGuL=1044922703;long bLECpQdKs=1807421133;if (bLECpQdKs == bLECpQdKs- 1 ) bLECpQdKs=1203005762; else bLECpQdKs=1139444519;if (bLECpQdKs == bLECpQdKs- 1 ) bLECpQdKs=1801598988; else bLECpQdKs=1322006521;if (bLECpQdKs == bLECpQdKs- 1 ) bLECpQdKs=433469354; else bLECpQdKs=552224189;if (bLECpQdKs == bLECpQdKs- 0 ) bLECpQdKs=1644359247; else bLECpQdKs=935884519;if (bLECpQdKs == bLECpQdKs- 1 ) bLECpQdKs=2008426738; else bLECpQdKs=829930882;if (bLECpQdKs == bLECpQdKs- 0 ) bLECpQdKs=1886907669; else bLECpQdKs=847198839;float owvlWVZYz=1543064572.1392440f;if (owvlWVZYz - owvlWVZYz> 0.00000001 ) owvlWVZYz=1325186998.9905814f; else owvlWVZYz=1599712527.0303919f;if (owvlWVZYz - owvlWVZYz> 0.00000001 ) owvlWVZYz=945764353.9499791f; else owvlWVZYz=742153476.8202164f;if (owvlWVZYz - owvlWVZYz> 0.00000001 ) owvlWVZYz=1940284663.2674268f; else owvlWVZYz=237751123.0003953f;if (owvlWVZYz - owvlWVZYz> 0.00000001 ) owvlWVZYz=1236534581.7991143f; else owvlWVZYz=597646121.9147602f;if (owvlWVZYz - owvlWVZYz> 0.00000001 ) owvlWVZYz=738550601.7148618f; else owvlWVZYz=1387263748.8497610f;if (owvlWVZYz - owvlWVZYz> 0.00000001 ) owvlWVZYz=837836919.5978581f; else owvlWVZYz=944265701.3120223f; }
 owvlWVZYzy::owvlWVZYzy()
 { this->rYyxmJsoEsJK("migWKzzuJrYyxmJsoEsJKj", true, 269040456, 541826268, 1663832654); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class LSdwcTsvRy
 { 
public: bool mgrbnOWZW; double mgrbnOWZWLSdwcTsvR; LSdwcTsvRy(); void EvAdosKAzSca(string mgrbnOWZWEvAdosKAzSca, bool ylHXcTnah, int vSoKGuKzw, float GMRpSlpSc, long othsFwckN);
 protected: bool mgrbnOWZWo; double mgrbnOWZWLSdwcTsvRf; void EvAdosKAzScau(string mgrbnOWZWEvAdosKAzScag, bool ylHXcTnahe, int vSoKGuKzwr, float GMRpSlpScw, long othsFwckNn);
 private: bool mgrbnOWZWylHXcTnah; double mgrbnOWZWGMRpSlpScLSdwcTsvR;
 void EvAdosKAzScav(string ylHXcTnahEvAdosKAzSca, bool ylHXcTnahvSoKGuKzw, int vSoKGuKzwmgrbnOWZW, float GMRpSlpScothsFwckN, long othsFwckNylHXcTnah); };
 void LSdwcTsvRy::EvAdosKAzSca(string mgrbnOWZWEvAdosKAzSca, bool ylHXcTnah, int vSoKGuKzw, float GMRpSlpSc, long othsFwckN)
 { double SPRdZuQnw=1499834056.4989222;if (SPRdZuQnw == SPRdZuQnw ) SPRdZuQnw=1503311210.6265046; else SPRdZuQnw=1420815675.7406520;if (SPRdZuQnw == SPRdZuQnw ) SPRdZuQnw=1248865115.1181182; else SPRdZuQnw=401708070.1466209;if (SPRdZuQnw == SPRdZuQnw ) SPRdZuQnw=1358552778.5934339; else SPRdZuQnw=1654171362.0980435;if (SPRdZuQnw == SPRdZuQnw ) SPRdZuQnw=1348898475.1757164; else SPRdZuQnw=988607253.8091506;if (SPRdZuQnw == SPRdZuQnw ) SPRdZuQnw=975478195.9008582; else SPRdZuQnw=109563079.5833921;if (SPRdZuQnw == SPRdZuQnw ) SPRdZuQnw=1142018993.3118671; else SPRdZuQnw=235105433.7202567;double XNpOOFrrI=724825859.0831764;if (XNpOOFrrI == XNpOOFrrI ) XNpOOFrrI=532421556.1886891; else XNpOOFrrI=2050130501.6059004;if (XNpOOFrrI == XNpOOFrrI ) XNpOOFrrI=202722776.8615711; else XNpOOFrrI=1864844666.5450986;if (XNpOOFrrI == XNpOOFrrI ) XNpOOFrrI=922214007.9753502; else XNpOOFrrI=1711379111.2053184;if (XNpOOFrrI == XNpOOFrrI ) XNpOOFrrI=172142399.1470352; else XNpOOFrrI=1465101031.3361637;if (XNpOOFrrI == XNpOOFrrI ) XNpOOFrrI=1201072083.5369267; else XNpOOFrrI=2129875358.3176137;if (XNpOOFrrI == XNpOOFrrI ) XNpOOFrrI=789021658.6736484; else XNpOOFrrI=524655259.1917347;double vJvkXkjrU=887742076.0367057;if (vJvkXkjrU == vJvkXkjrU ) vJvkXkjrU=1338677300.9868157; else vJvkXkjrU=1310599996.8698852;if (vJvkXkjrU == vJvkXkjrU ) vJvkXkjrU=1769736837.0680277; else vJvkXkjrU=1416898429.7678267;if (vJvkXkjrU == vJvkXkjrU ) vJvkXkjrU=326400356.5406711; else vJvkXkjrU=1909850306.1008856;if (vJvkXkjrU == vJvkXkjrU ) vJvkXkjrU=106375948.7452750; else vJvkXkjrU=1997691912.8988813;if (vJvkXkjrU == vJvkXkjrU ) vJvkXkjrU=1394927169.3010014; else vJvkXkjrU=196564741.3932419;if (vJvkXkjrU == vJvkXkjrU ) vJvkXkjrU=1211131393.6824220; else vJvkXkjrU=1693240642.2365178;double MmuArpCxq=1666956801.6969030;if (MmuArpCxq == MmuArpCxq ) MmuArpCxq=1989403841.7329007; else MmuArpCxq=646130461.6713381;if (MmuArpCxq == MmuArpCxq ) MmuArpCxq=398417334.4020375; else MmuArpCxq=1725149084.2416751;if (MmuArpCxq == MmuArpCxq ) MmuArpCxq=464101322.8563460; else MmuArpCxq=2108492907.2564202;if (MmuArpCxq == MmuArpCxq ) MmuArpCxq=577620049.7417452; else MmuArpCxq=1939415746.0597765;if (MmuArpCxq == MmuArpCxq ) MmuArpCxq=1248673276.0233568; else MmuArpCxq=1931247731.2510223;if (MmuArpCxq == MmuArpCxq ) MmuArpCxq=1348119634.5772836; else MmuArpCxq=1376161067.0004199;long kckAbLPOB=1019479675;if (kckAbLPOB == kckAbLPOB- 0 ) kckAbLPOB=1328390913; else kckAbLPOB=254276917;if (kckAbLPOB == kckAbLPOB- 0 ) kckAbLPOB=1043911780; else kckAbLPOB=1592407552;if (kckAbLPOB == kckAbLPOB- 1 ) kckAbLPOB=1947682026; else kckAbLPOB=2071713835;if (kckAbLPOB == kckAbLPOB- 0 ) kckAbLPOB=398425503; else kckAbLPOB=770054897;if (kckAbLPOB == kckAbLPOB- 1 ) kckAbLPOB=1943754553; else kckAbLPOB=352514511;if (kckAbLPOB == kckAbLPOB- 1 ) kckAbLPOB=469917497; else kckAbLPOB=725649266;float LSdwcTsvR=570343407.0484432f;if (LSdwcTsvR - LSdwcTsvR> 0.00000001 ) LSdwcTsvR=1164553720.2457390f; else LSdwcTsvR=1269548504.7013975f;if (LSdwcTsvR - LSdwcTsvR> 0.00000001 ) LSdwcTsvR=682735065.7210655f; else LSdwcTsvR=87155273.6485919f;if (LSdwcTsvR - LSdwcTsvR> 0.00000001 ) LSdwcTsvR=1705064833.6968756f; else LSdwcTsvR=1350990376.9739893f;if (LSdwcTsvR - LSdwcTsvR> 0.00000001 ) LSdwcTsvR=423640754.3086914f; else LSdwcTsvR=1377668040.2758876f;if (LSdwcTsvR - LSdwcTsvR> 0.00000001 ) LSdwcTsvR=732979947.1724821f; else LSdwcTsvR=1977804738.2652298f;if (LSdwcTsvR - LSdwcTsvR> 0.00000001 ) LSdwcTsvR=168225153.5929734f; else LSdwcTsvR=542636272.4100064f; }
 LSdwcTsvRy::LSdwcTsvRy()
 { this->EvAdosKAzSca("mgrbnOWZWEvAdosKAzScaj", true, 561730672, 877698528, 1132542208); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class eJkZcQjfUy
 { 
public: bool BcPtAacKA; double BcPtAacKAeJkZcQjfU; eJkZcQjfUy(); void vEhIrCTSyLTs(string BcPtAacKAvEhIrCTSyLTs, bool UmjECRlOP, int MVMikZkLe, float rCeiGydmp, long ZBegIHgay);
 protected: bool BcPtAacKAo; double BcPtAacKAeJkZcQjfUf; void vEhIrCTSyLTsu(string BcPtAacKAvEhIrCTSyLTsg, bool UmjECRlOPe, int MVMikZkLer, float rCeiGydmpw, long ZBegIHgayn);
 private: bool BcPtAacKAUmjECRlOP; double BcPtAacKArCeiGydmpeJkZcQjfU;
 void vEhIrCTSyLTsv(string UmjECRlOPvEhIrCTSyLTs, bool UmjECRlOPMVMikZkLe, int MVMikZkLeBcPtAacKA, float rCeiGydmpZBegIHgay, long ZBegIHgayUmjECRlOP); };
 void eJkZcQjfUy::vEhIrCTSyLTs(string BcPtAacKAvEhIrCTSyLTs, bool UmjECRlOP, int MVMikZkLe, float rCeiGydmp, long ZBegIHgay)
 { long fllQhFBEj=1298380436;if (fllQhFBEj == fllQhFBEj- 0 ) fllQhFBEj=598340737; else fllQhFBEj=1860511788;if (fllQhFBEj == fllQhFBEj- 0 ) fllQhFBEj=465663467; else fllQhFBEj=768290441;if (fllQhFBEj == fllQhFBEj- 1 ) fllQhFBEj=898994; else fllQhFBEj=1256782183;if (fllQhFBEj == fllQhFBEj- 1 ) fllQhFBEj=612708297; else fllQhFBEj=974376275;if (fllQhFBEj == fllQhFBEj- 0 ) fllQhFBEj=1688451528; else fllQhFBEj=397052504;if (fllQhFBEj == fllQhFBEj- 1 ) fllQhFBEj=1895407449; else fllQhFBEj=833990158;float uXQFpOUfg=266727199.4341005f;if (uXQFpOUfg - uXQFpOUfg> 0.00000001 ) uXQFpOUfg=402579726.9560300f; else uXQFpOUfg=1185457852.6189962f;if (uXQFpOUfg - uXQFpOUfg> 0.00000001 ) uXQFpOUfg=223669785.6353700f; else uXQFpOUfg=323079738.2069605f;if (uXQFpOUfg - uXQFpOUfg> 0.00000001 ) uXQFpOUfg=2095408413.3035929f; else uXQFpOUfg=1939961811.4925827f;if (uXQFpOUfg - uXQFpOUfg> 0.00000001 ) uXQFpOUfg=173471900.1767448f; else uXQFpOUfg=26126264.0084057f;if (uXQFpOUfg - uXQFpOUfg> 0.00000001 ) uXQFpOUfg=914873048.6027154f; else uXQFpOUfg=1396574381.1650443f;if (uXQFpOUfg - uXQFpOUfg> 0.00000001 ) uXQFpOUfg=81787243.5380842f; else uXQFpOUfg=5669133.3133673f;long XCtjLquBs=1444294558;if (XCtjLquBs == XCtjLquBs- 1 ) XCtjLquBs=1818679299; else XCtjLquBs=1065173524;if (XCtjLquBs == XCtjLquBs- 0 ) XCtjLquBs=1282724961; else XCtjLquBs=1580049929;if (XCtjLquBs == XCtjLquBs- 1 ) XCtjLquBs=733752089; else XCtjLquBs=1158362998;if (XCtjLquBs == XCtjLquBs- 0 ) XCtjLquBs=279710080; else XCtjLquBs=724480239;if (XCtjLquBs == XCtjLquBs- 0 ) XCtjLquBs=1104966268; else XCtjLquBs=335682943;if (XCtjLquBs == XCtjLquBs- 1 ) XCtjLquBs=660663694; else XCtjLquBs=2146610108;int CXFLFDNJC=1915159193;if (CXFLFDNJC == CXFLFDNJC- 1 ) CXFLFDNJC=1560675745; else CXFLFDNJC=249328931;if (CXFLFDNJC == CXFLFDNJC- 1 ) CXFLFDNJC=1753934796; else CXFLFDNJC=184162380;if (CXFLFDNJC == CXFLFDNJC- 1 ) CXFLFDNJC=379036386; else CXFLFDNJC=1158829470;if (CXFLFDNJC == CXFLFDNJC- 0 ) CXFLFDNJC=1350455670; else CXFLFDNJC=805862573;if (CXFLFDNJC == CXFLFDNJC- 0 ) CXFLFDNJC=1687039888; else CXFLFDNJC=439537203;if (CXFLFDNJC == CXFLFDNJC- 1 ) CXFLFDNJC=2000901040; else CXFLFDNJC=751808260;long rYjUwluEG=390042718;if (rYjUwluEG == rYjUwluEG- 1 ) rYjUwluEG=1700734304; else rYjUwluEG=451112891;if (rYjUwluEG == rYjUwluEG- 0 ) rYjUwluEG=1162794506; else rYjUwluEG=582350619;if (rYjUwluEG == rYjUwluEG- 1 ) rYjUwluEG=30954793; else rYjUwluEG=2007036816;if (rYjUwluEG == rYjUwluEG- 0 ) rYjUwluEG=1680458757; else rYjUwluEG=1391700375;if (rYjUwluEG == rYjUwluEG- 1 ) rYjUwluEG=905747772; else rYjUwluEG=1646673193;if (rYjUwluEG == rYjUwluEG- 1 ) rYjUwluEG=1365597117; else rYjUwluEG=1759725470;int eJkZcQjfU=859548146;if (eJkZcQjfU == eJkZcQjfU- 1 ) eJkZcQjfU=941345049; else eJkZcQjfU=314111697;if (eJkZcQjfU == eJkZcQjfU- 0 ) eJkZcQjfU=592477035; else eJkZcQjfU=1089630549;if (eJkZcQjfU == eJkZcQjfU- 1 ) eJkZcQjfU=1691957661; else eJkZcQjfU=659639467;if (eJkZcQjfU == eJkZcQjfU- 1 ) eJkZcQjfU=1065258172; else eJkZcQjfU=659849829;if (eJkZcQjfU == eJkZcQjfU- 1 ) eJkZcQjfU=1862201501; else eJkZcQjfU=476862388;if (eJkZcQjfU == eJkZcQjfU- 0 ) eJkZcQjfU=2040493688; else eJkZcQjfU=294214886; }
 eJkZcQjfUy::eJkZcQjfUy()
 { this->vEhIrCTSyLTs("BcPtAacKAvEhIrCTSyLTsj", true, 1304945605, 1675385467, 1696968946); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class rwsSXqENny
 { 
public: bool YqvItHNLq; double YqvItHNLqrwsSXqENn; rwsSXqENny(); void tYabzpkrDknE(string YqvItHNLqtYabzpkrDknE, bool WhxYRrXBT, int VkukmNWvX, float FjzAZTjBE, long bcrHCBGqV);
 protected: bool YqvItHNLqo; double YqvItHNLqrwsSXqENnf; void tYabzpkrDknEu(string YqvItHNLqtYabzpkrDknEg, bool WhxYRrXBTe, int VkukmNWvXr, float FjzAZTjBEw, long bcrHCBGqVn);
 private: bool YqvItHNLqWhxYRrXBT; double YqvItHNLqFjzAZTjBErwsSXqENn;
 void tYabzpkrDknEv(string WhxYRrXBTtYabzpkrDknE, bool WhxYRrXBTVkukmNWvX, int VkukmNWvXYqvItHNLq, float FjzAZTjBEbcrHCBGqV, long bcrHCBGqVWhxYRrXBT); };
 void rwsSXqENny::tYabzpkrDknE(string YqvItHNLqtYabzpkrDknE, bool WhxYRrXBT, int VkukmNWvX, float FjzAZTjBE, long bcrHCBGqV)
 { long jPSrUZSOE=1148630278;if (jPSrUZSOE == jPSrUZSOE- 1 ) jPSrUZSOE=810307161; else jPSrUZSOE=1563323532;if (jPSrUZSOE == jPSrUZSOE- 1 ) jPSrUZSOE=1650299352; else jPSrUZSOE=1177200437;if (jPSrUZSOE == jPSrUZSOE- 1 ) jPSrUZSOE=1962911254; else jPSrUZSOE=2043111489;if (jPSrUZSOE == jPSrUZSOE- 1 ) jPSrUZSOE=389589680; else jPSrUZSOE=581997985;if (jPSrUZSOE == jPSrUZSOE- 1 ) jPSrUZSOE=2065515180; else jPSrUZSOE=269579732;if (jPSrUZSOE == jPSrUZSOE- 0 ) jPSrUZSOE=478250425; else jPSrUZSOE=241205880;long bCIBhkXsq=1621843746;if (bCIBhkXsq == bCIBhkXsq- 1 ) bCIBhkXsq=58213528; else bCIBhkXsq=2047555578;if (bCIBhkXsq == bCIBhkXsq- 0 ) bCIBhkXsq=208631899; else bCIBhkXsq=1798672304;if (bCIBhkXsq == bCIBhkXsq- 1 ) bCIBhkXsq=1062733128; else bCIBhkXsq=1748117453;if (bCIBhkXsq == bCIBhkXsq- 1 ) bCIBhkXsq=2003144721; else bCIBhkXsq=324711464;if (bCIBhkXsq == bCIBhkXsq- 1 ) bCIBhkXsq=1287164178; else bCIBhkXsq=97262455;if (bCIBhkXsq == bCIBhkXsq- 0 ) bCIBhkXsq=1437782632; else bCIBhkXsq=2035715215;double ZhWhvSfSp=1293863644.8867002;if (ZhWhvSfSp == ZhWhvSfSp ) ZhWhvSfSp=396125369.3475200; else ZhWhvSfSp=556279470.7621994;if (ZhWhvSfSp == ZhWhvSfSp ) ZhWhvSfSp=1402607904.1222222; else ZhWhvSfSp=896786950.3454361;if (ZhWhvSfSp == ZhWhvSfSp ) ZhWhvSfSp=1930697519.1977727; else ZhWhvSfSp=1386029689.4692122;if (ZhWhvSfSp == ZhWhvSfSp ) ZhWhvSfSp=432692118.1836088; else ZhWhvSfSp=1614060411.7559910;if (ZhWhvSfSp == ZhWhvSfSp ) ZhWhvSfSp=680369248.1220507; else ZhWhvSfSp=1156115483.8643778;if (ZhWhvSfSp == ZhWhvSfSp ) ZhWhvSfSp=1097136286.6411002; else ZhWhvSfSp=1050405781.6393835;long JpmImMVmK=1857291625;if (JpmImMVmK == JpmImMVmK- 0 ) JpmImMVmK=87728324; else JpmImMVmK=1983256744;if (JpmImMVmK == JpmImMVmK- 1 ) JpmImMVmK=1265686376; else JpmImMVmK=1547825694;if (JpmImMVmK == JpmImMVmK- 0 ) JpmImMVmK=1200915294; else JpmImMVmK=132720405;if (JpmImMVmK == JpmImMVmK- 1 ) JpmImMVmK=85897150; else JpmImMVmK=1209673355;if (JpmImMVmK == JpmImMVmK- 1 ) JpmImMVmK=1707662458; else JpmImMVmK=1325587888;if (JpmImMVmK == JpmImMVmK- 0 ) JpmImMVmK=2037519906; else JpmImMVmK=1865648799;long ydYTNkvAf=2050102113;if (ydYTNkvAf == ydYTNkvAf- 1 ) ydYTNkvAf=1288871636; else ydYTNkvAf=1331870428;if (ydYTNkvAf == ydYTNkvAf- 0 ) ydYTNkvAf=1992564158; else ydYTNkvAf=609785810;if (ydYTNkvAf == ydYTNkvAf- 0 ) ydYTNkvAf=737922986; else ydYTNkvAf=1069200528;if (ydYTNkvAf == ydYTNkvAf- 0 ) ydYTNkvAf=1838629874; else ydYTNkvAf=819667486;if (ydYTNkvAf == ydYTNkvAf- 1 ) ydYTNkvAf=1614863460; else ydYTNkvAf=742055135;if (ydYTNkvAf == ydYTNkvAf- 0 ) ydYTNkvAf=1118303056; else ydYTNkvAf=2054101292;long rwsSXqENn=1236671319;if (rwsSXqENn == rwsSXqENn- 1 ) rwsSXqENn=1071707350; else rwsSXqENn=1727974654;if (rwsSXqENn == rwsSXqENn- 1 ) rwsSXqENn=1947986891; else rwsSXqENn=324866952;if (rwsSXqENn == rwsSXqENn- 1 ) rwsSXqENn=897210338; else rwsSXqENn=1727849696;if (rwsSXqENn == rwsSXqENn- 1 ) rwsSXqENn=92948350; else rwsSXqENn=263404964;if (rwsSXqENn == rwsSXqENn- 0 ) rwsSXqENn=470382320; else rwsSXqENn=192934549;if (rwsSXqENn == rwsSXqENn- 1 ) rwsSXqENn=1336608139; else rwsSXqENn=605109631; }
 rwsSXqENny::rwsSXqENny()
 { this->tYabzpkrDknE("YqvItHNLqtYabzpkrDknEj", true, 1495993430, 714526966, 1008731554); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class ykLYXBmPhy
 { 
public: bool BMGIpSSsV; double BMGIpSSsVykLYXBmPh; ykLYXBmPhy(); void vvoIYlrOMDBL(string BMGIpSSsVvvoIYlrOMDBL, bool YJDoXPyQu, int AUpzAPjSl, float zTWfFuXnv, long byjdClCOh);
 protected: bool BMGIpSSsVo; double BMGIpSSsVykLYXBmPhf; void vvoIYlrOMDBLu(string BMGIpSSsVvvoIYlrOMDBLg, bool YJDoXPyQue, int AUpzAPjSlr, float zTWfFuXnvw, long byjdClCOhn);
 private: bool BMGIpSSsVYJDoXPyQu; double BMGIpSSsVzTWfFuXnvykLYXBmPh;
 void vvoIYlrOMDBLv(string YJDoXPyQuvvoIYlrOMDBL, bool YJDoXPyQuAUpzAPjSl, int AUpzAPjSlBMGIpSSsV, float zTWfFuXnvbyjdClCOh, long byjdClCOhYJDoXPyQu); };
 void ykLYXBmPhy::vvoIYlrOMDBL(string BMGIpSSsVvvoIYlrOMDBL, bool YJDoXPyQu, int AUpzAPjSl, float zTWfFuXnv, long byjdClCOh)
 { float SzDjQTmYY=1253936020.6494212f;if (SzDjQTmYY - SzDjQTmYY> 0.00000001 ) SzDjQTmYY=1047793209.3896138f; else SzDjQTmYY=1517829297.9291598f;if (SzDjQTmYY - SzDjQTmYY> 0.00000001 ) SzDjQTmYY=1485177727.7867663f; else SzDjQTmYY=136005831.0993441f;if (SzDjQTmYY - SzDjQTmYY> 0.00000001 ) SzDjQTmYY=2086113339.9736497f; else SzDjQTmYY=1504520997.0225445f;if (SzDjQTmYY - SzDjQTmYY> 0.00000001 ) SzDjQTmYY=1178720019.1281479f; else SzDjQTmYY=2115517589.7386594f;if (SzDjQTmYY - SzDjQTmYY> 0.00000001 ) SzDjQTmYY=1865402530.9048070f; else SzDjQTmYY=1163409434.6751128f;if (SzDjQTmYY - SzDjQTmYY> 0.00000001 ) SzDjQTmYY=624148891.6522399f; else SzDjQTmYY=321296947.8230822f;int ZxxzLDJri=515720282;if (ZxxzLDJri == ZxxzLDJri- 0 ) ZxxzLDJri=701714375; else ZxxzLDJri=1921388700;if (ZxxzLDJri == ZxxzLDJri- 0 ) ZxxzLDJri=1090204941; else ZxxzLDJri=571014281;if (ZxxzLDJri == ZxxzLDJri- 1 ) ZxxzLDJri=1810914796; else ZxxzLDJri=1828820604;if (ZxxzLDJri == ZxxzLDJri- 1 ) ZxxzLDJri=1816588206; else ZxxzLDJri=1340347619;if (ZxxzLDJri == ZxxzLDJri- 0 ) ZxxzLDJri=1800950476; else ZxxzLDJri=1770058481;if (ZxxzLDJri == ZxxzLDJri- 0 ) ZxxzLDJri=1648449154; else ZxxzLDJri=424443074;double lMAhXbNms=1495389345.1453196;if (lMAhXbNms == lMAhXbNms ) lMAhXbNms=205796268.9559821; else lMAhXbNms=184745770.9316848;if (lMAhXbNms == lMAhXbNms ) lMAhXbNms=2087823900.7796868; else lMAhXbNms=37563016.1606355;if (lMAhXbNms == lMAhXbNms ) lMAhXbNms=1870334427.7387863; else lMAhXbNms=1804215863.4366189;if (lMAhXbNms == lMAhXbNms ) lMAhXbNms=1331597584.2717334; else lMAhXbNms=246998034.7784498;if (lMAhXbNms == lMAhXbNms ) lMAhXbNms=850613947.0636773; else lMAhXbNms=416414303.1301854;if (lMAhXbNms == lMAhXbNms ) lMAhXbNms=1697272875.5308800; else lMAhXbNms=33633397.0900210;int BORnZXkPC=380381773;if (BORnZXkPC == BORnZXkPC- 1 ) BORnZXkPC=232095273; else BORnZXkPC=1623282274;if (BORnZXkPC == BORnZXkPC- 0 ) BORnZXkPC=1503485597; else BORnZXkPC=1910689;if (BORnZXkPC == BORnZXkPC- 0 ) BORnZXkPC=1027741539; else BORnZXkPC=386717169;if (BORnZXkPC == BORnZXkPC- 1 ) BORnZXkPC=1590504871; else BORnZXkPC=1366456252;if (BORnZXkPC == BORnZXkPC- 1 ) BORnZXkPC=1848724738; else BORnZXkPC=144830108;if (BORnZXkPC == BORnZXkPC- 1 ) BORnZXkPC=482539002; else BORnZXkPC=316054858;float bSsOHXxXy=1578253448.8326756f;if (bSsOHXxXy - bSsOHXxXy> 0.00000001 ) bSsOHXxXy=777144538.6472178f; else bSsOHXxXy=1276243193.4639549f;if (bSsOHXxXy - bSsOHXxXy> 0.00000001 ) bSsOHXxXy=115500679.0570632f; else bSsOHXxXy=834138859.0043334f;if (bSsOHXxXy - bSsOHXxXy> 0.00000001 ) bSsOHXxXy=1095333595.6568501f; else bSsOHXxXy=1130122308.5235350f;if (bSsOHXxXy - bSsOHXxXy> 0.00000001 ) bSsOHXxXy=792869502.3993979f; else bSsOHXxXy=1044982159.9671357f;if (bSsOHXxXy - bSsOHXxXy> 0.00000001 ) bSsOHXxXy=589791116.5408458f; else bSsOHXxXy=843206907.2710595f;if (bSsOHXxXy - bSsOHXxXy> 0.00000001 ) bSsOHXxXy=1867883981.4564827f; else bSsOHXxXy=1394500493.2504658f;double ykLYXBmPh=1290923562.9557450;if (ykLYXBmPh == ykLYXBmPh ) ykLYXBmPh=451128610.9124745; else ykLYXBmPh=1268067381.4354108;if (ykLYXBmPh == ykLYXBmPh ) ykLYXBmPh=192347801.7850908; else ykLYXBmPh=169851682.8974877;if (ykLYXBmPh == ykLYXBmPh ) ykLYXBmPh=931147132.5307315; else ykLYXBmPh=384354207.6861814;if (ykLYXBmPh == ykLYXBmPh ) ykLYXBmPh=467647806.7990152; else ykLYXBmPh=1966562746.8076631;if (ykLYXBmPh == ykLYXBmPh ) ykLYXBmPh=741724546.3600789; else ykLYXBmPh=721367648.0679041;if (ykLYXBmPh == ykLYXBmPh ) ykLYXBmPh=336321925.1991942; else ykLYXBmPh=1725504319.0847358; }
 ykLYXBmPhy::ykLYXBmPhy()
 { this->vvoIYlrOMDBL("BMGIpSSsVvvoIYlrOMDBLj", true, 1321676861, 1015542726, 390926191); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class KlpEFWHCLy
 { 
public: bool OKArmLWIR; double OKArmLWIRKlpEFWHCL; KlpEFWHCLy(); void KSIhfAQZuVYt(string OKArmLWIRKSIhfAQZuVYt, bool kBzThWaWq, int cRWqREzAZ, float UdubeXwto, long BRWvqYaGn);
 protected: bool OKArmLWIRo; double OKArmLWIRKlpEFWHCLf; void KSIhfAQZuVYtu(string OKArmLWIRKSIhfAQZuVYtg, bool kBzThWaWqe, int cRWqREzAZr, float UdubeXwtow, long BRWvqYaGnn);
 private: bool OKArmLWIRkBzThWaWq; double OKArmLWIRUdubeXwtoKlpEFWHCL;
 void KSIhfAQZuVYtv(string kBzThWaWqKSIhfAQZuVYt, bool kBzThWaWqcRWqREzAZ, int cRWqREzAZOKArmLWIR, float UdubeXwtoBRWvqYaGn, long BRWvqYaGnkBzThWaWq); };
 void KlpEFWHCLy::KSIhfAQZuVYt(string OKArmLWIRKSIhfAQZuVYt, bool kBzThWaWq, int cRWqREzAZ, float UdubeXwto, long BRWvqYaGn)
 { long YEZfpZoxq=752813971;if (YEZfpZoxq == YEZfpZoxq- 0 ) YEZfpZoxq=2121500290; else YEZfpZoxq=114300115;if (YEZfpZoxq == YEZfpZoxq- 1 ) YEZfpZoxq=955357069; else YEZfpZoxq=55903943;if (YEZfpZoxq == YEZfpZoxq- 0 ) YEZfpZoxq=2133573276; else YEZfpZoxq=1691381239;if (YEZfpZoxq == YEZfpZoxq- 1 ) YEZfpZoxq=2083601638; else YEZfpZoxq=1413365870;if (YEZfpZoxq == YEZfpZoxq- 0 ) YEZfpZoxq=1235868578; else YEZfpZoxq=1145367960;if (YEZfpZoxq == YEZfpZoxq- 0 ) YEZfpZoxq=733244310; else YEZfpZoxq=398024802;float jVccIuYMv=379164727.1208576f;if (jVccIuYMv - jVccIuYMv> 0.00000001 ) jVccIuYMv=1001571594.4428023f; else jVccIuYMv=1508000959.6968462f;if (jVccIuYMv - jVccIuYMv> 0.00000001 ) jVccIuYMv=663007458.1808249f; else jVccIuYMv=2031699173.2160154f;if (jVccIuYMv - jVccIuYMv> 0.00000001 ) jVccIuYMv=91153113.1656401f; else jVccIuYMv=638557745.7712726f;if (jVccIuYMv - jVccIuYMv> 0.00000001 ) jVccIuYMv=2014577584.3055900f; else jVccIuYMv=500950530.4003373f;if (jVccIuYMv - jVccIuYMv> 0.00000001 ) jVccIuYMv=1416780091.3799805f; else jVccIuYMv=248427132.4220725f;if (jVccIuYMv - jVccIuYMv> 0.00000001 ) jVccIuYMv=1488577488.2976349f; else jVccIuYMv=614514301.2152547f;double XQGQrSALO=1413376179.3368065;if (XQGQrSALO == XQGQrSALO ) XQGQrSALO=1738307295.1412115; else XQGQrSALO=186264241.0868694;if (XQGQrSALO == XQGQrSALO ) XQGQrSALO=1456238426.2638399; else XQGQrSALO=267495102.7980418;if (XQGQrSALO == XQGQrSALO ) XQGQrSALO=1397573245.1310235; else XQGQrSALO=1105841723.2150113;if (XQGQrSALO == XQGQrSALO ) XQGQrSALO=447444189.7391891; else XQGQrSALO=95991787.7318764;if (XQGQrSALO == XQGQrSALO ) XQGQrSALO=785414559.6438089; else XQGQrSALO=339629205.6595600;if (XQGQrSALO == XQGQrSALO ) XQGQrSALO=1484045790.6883970; else XQGQrSALO=888503141.6996274;float AKYkCjlKP=1321965203.6547518f;if (AKYkCjlKP - AKYkCjlKP> 0.00000001 ) AKYkCjlKP=869137650.4903476f; else AKYkCjlKP=657158504.3739663f;if (AKYkCjlKP - AKYkCjlKP> 0.00000001 ) AKYkCjlKP=500929473.2894136f; else AKYkCjlKP=1153752506.6930454f;if (AKYkCjlKP - AKYkCjlKP> 0.00000001 ) AKYkCjlKP=1969672696.3559289f; else AKYkCjlKP=1515489717.6754225f;if (AKYkCjlKP - AKYkCjlKP> 0.00000001 ) AKYkCjlKP=661660858.6647774f; else AKYkCjlKP=1482942545.7544939f;if (AKYkCjlKP - AKYkCjlKP> 0.00000001 ) AKYkCjlKP=247206178.1740320f; else AKYkCjlKP=454406539.3805846f;if (AKYkCjlKP - AKYkCjlKP> 0.00000001 ) AKYkCjlKP=786607499.2510110f; else AKYkCjlKP=1885146144.3037807f;double GaSdCbzHR=1077086029.1312908;if (GaSdCbzHR == GaSdCbzHR ) GaSdCbzHR=579720111.5974863; else GaSdCbzHR=1467351778.4416003;if (GaSdCbzHR == GaSdCbzHR ) GaSdCbzHR=807201154.4945724; else GaSdCbzHR=2077371241.0277256;if (GaSdCbzHR == GaSdCbzHR ) GaSdCbzHR=1479122113.3599757; else GaSdCbzHR=68964312.1289004;if (GaSdCbzHR == GaSdCbzHR ) GaSdCbzHR=1129075129.9156097; else GaSdCbzHR=2043213518.4772956;if (GaSdCbzHR == GaSdCbzHR ) GaSdCbzHR=1060556770.7076172; else GaSdCbzHR=567015671.9283574;if (GaSdCbzHR == GaSdCbzHR ) GaSdCbzHR=1246284614.7778201; else GaSdCbzHR=1899007555.2223799;double KlpEFWHCL=689707173.0988175;if (KlpEFWHCL == KlpEFWHCL ) KlpEFWHCL=2002021328.2565875; else KlpEFWHCL=166612285.2476043;if (KlpEFWHCL == KlpEFWHCL ) KlpEFWHCL=1892860298.4874809; else KlpEFWHCL=130300522.3166501;if (KlpEFWHCL == KlpEFWHCL ) KlpEFWHCL=1805336723.5728910; else KlpEFWHCL=1559378990.4704020;if (KlpEFWHCL == KlpEFWHCL ) KlpEFWHCL=1591187130.0945277; else KlpEFWHCL=222817578.1144760;if (KlpEFWHCL == KlpEFWHCL ) KlpEFWHCL=1672087030.4004847; else KlpEFWHCL=2120779528.7582331;if (KlpEFWHCL == KlpEFWHCL ) KlpEFWHCL=20288924.2808903; else KlpEFWHCL=943166706.3213354; }
 KlpEFWHCLy::KlpEFWHCLy()
 { this->KSIhfAQZuVYt("OKArmLWIRKSIhfAQZuVYtj", true, 319234224, 709781692, 2040671683); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class jlGTjziqUy
 { 
public: bool AvPWTLCEL; double AvPWTLCELjlGTjziqU; jlGTjziqUy(); void bgtDGKWPEOzz(string AvPWTLCELbgtDGKWPEOzz, bool OPHENPdpM, int aPiAwWcYP, float yRAURuNvt, long XcCOZMdYt);
 protected: bool AvPWTLCELo; double AvPWTLCELjlGTjziqUf; void bgtDGKWPEOzzu(string AvPWTLCELbgtDGKWPEOzzg, bool OPHENPdpMe, int aPiAwWcYPr, float yRAURuNvtw, long XcCOZMdYtn);
 private: bool AvPWTLCELOPHENPdpM; double AvPWTLCELyRAURuNvtjlGTjziqU;
 void bgtDGKWPEOzzv(string OPHENPdpMbgtDGKWPEOzz, bool OPHENPdpMaPiAwWcYP, int aPiAwWcYPAvPWTLCEL, float yRAURuNvtXcCOZMdYt, long XcCOZMdYtOPHENPdpM); };
 void jlGTjziqUy::bgtDGKWPEOzz(string AvPWTLCELbgtDGKWPEOzz, bool OPHENPdpM, int aPiAwWcYP, float yRAURuNvt, long XcCOZMdYt)
 { double cqkQrVBAU=1980019532.1475674;if (cqkQrVBAU == cqkQrVBAU ) cqkQrVBAU=841614374.3778431; else cqkQrVBAU=1569871153.1843788;if (cqkQrVBAU == cqkQrVBAU ) cqkQrVBAU=1248600647.2058874; else cqkQrVBAU=2131751227.0683288;if (cqkQrVBAU == cqkQrVBAU ) cqkQrVBAU=1985972963.2931926; else cqkQrVBAU=2114985178.8137799;if (cqkQrVBAU == cqkQrVBAU ) cqkQrVBAU=1802607381.1632479; else cqkQrVBAU=1065081418.4289003;if (cqkQrVBAU == cqkQrVBAU ) cqkQrVBAU=1827642882.2052630; else cqkQrVBAU=1473830776.0239735;if (cqkQrVBAU == cqkQrVBAU ) cqkQrVBAU=408230633.0311860; else cqkQrVBAU=1954405778.0519198;float YKtIQfEoY=175755500.8805266f;if (YKtIQfEoY - YKtIQfEoY> 0.00000001 ) YKtIQfEoY=829027210.6619274f; else YKtIQfEoY=1439967293.7083998f;if (YKtIQfEoY - YKtIQfEoY> 0.00000001 ) YKtIQfEoY=228613016.7074894f; else YKtIQfEoY=1089378458.3253902f;if (YKtIQfEoY - YKtIQfEoY> 0.00000001 ) YKtIQfEoY=1366191327.9630208f; else YKtIQfEoY=1082196392.2766279f;if (YKtIQfEoY - YKtIQfEoY> 0.00000001 ) YKtIQfEoY=430751991.7699401f; else YKtIQfEoY=1727052352.9415724f;if (YKtIQfEoY - YKtIQfEoY> 0.00000001 ) YKtIQfEoY=1164307739.5663738f; else YKtIQfEoY=1620070723.5537016f;if (YKtIQfEoY - YKtIQfEoY> 0.00000001 ) YKtIQfEoY=882358324.3186267f; else YKtIQfEoY=1743888699.6755120f;int JcZnYkFyN=330972875;if (JcZnYkFyN == JcZnYkFyN- 0 ) JcZnYkFyN=1601816948; else JcZnYkFyN=564585925;if (JcZnYkFyN == JcZnYkFyN- 1 ) JcZnYkFyN=87038457; else JcZnYkFyN=1187137763;if (JcZnYkFyN == JcZnYkFyN- 1 ) JcZnYkFyN=653234073; else JcZnYkFyN=1891788571;if (JcZnYkFyN == JcZnYkFyN- 0 ) JcZnYkFyN=418213834; else JcZnYkFyN=377543889;if (JcZnYkFyN == JcZnYkFyN- 0 ) JcZnYkFyN=1552281406; else JcZnYkFyN=828603704;if (JcZnYkFyN == JcZnYkFyN- 0 ) JcZnYkFyN=179716571; else JcZnYkFyN=1003961397;double YJrqnIRVD=54850994.6545292;if (YJrqnIRVD == YJrqnIRVD ) YJrqnIRVD=1297336162.4705596; else YJrqnIRVD=546677316.4430391;if (YJrqnIRVD == YJrqnIRVD ) YJrqnIRVD=1706600549.5503391; else YJrqnIRVD=1168537409.4701964;if (YJrqnIRVD == YJrqnIRVD ) YJrqnIRVD=86515496.4708194; else YJrqnIRVD=51992759.0654897;if (YJrqnIRVD == YJrqnIRVD ) YJrqnIRVD=613828205.8527081; else YJrqnIRVD=1906901629.1520120;if (YJrqnIRVD == YJrqnIRVD ) YJrqnIRVD=1139119162.0147420; else YJrqnIRVD=1669031942.8432085;if (YJrqnIRVD == YJrqnIRVD ) YJrqnIRVD=967443488.0595147; else YJrqnIRVD=365902240.2859834;int lqBnTzaGl=604321155;if (lqBnTzaGl == lqBnTzaGl- 0 ) lqBnTzaGl=1084447931; else lqBnTzaGl=77257758;if (lqBnTzaGl == lqBnTzaGl- 0 ) lqBnTzaGl=352588830; else lqBnTzaGl=521624942;if (lqBnTzaGl == lqBnTzaGl- 1 ) lqBnTzaGl=1099159528; else lqBnTzaGl=1839651556;if (lqBnTzaGl == lqBnTzaGl- 0 ) lqBnTzaGl=1670005074; else lqBnTzaGl=1084722286;if (lqBnTzaGl == lqBnTzaGl- 1 ) lqBnTzaGl=1021753459; else lqBnTzaGl=1998552774;if (lqBnTzaGl == lqBnTzaGl- 1 ) lqBnTzaGl=1684580699; else lqBnTzaGl=537587623;double jlGTjziqU=1394564663.9900183;if (jlGTjziqU == jlGTjziqU ) jlGTjziqU=1046647912.9039452; else jlGTjziqU=827507330.3239555;if (jlGTjziqU == jlGTjziqU ) jlGTjziqU=446552537.6195038; else jlGTjziqU=1455288521.0190096;if (jlGTjziqU == jlGTjziqU ) jlGTjziqU=1664204825.7245547; else jlGTjziqU=1368329083.0386710;if (jlGTjziqU == jlGTjziqU ) jlGTjziqU=244457379.3139664; else jlGTjziqU=1549824189.9162659;if (jlGTjziqU == jlGTjziqU ) jlGTjziqU=2098241367.0595666; else jlGTjziqU=327620475.1940297;if (jlGTjziqU == jlGTjziqU ) jlGTjziqU=48018601.8193298; else jlGTjziqU=1131685778.0624439; }
 jlGTjziqUy::jlGTjziqUy()
 { this->bgtDGKWPEOzz("AvPWTLCELbgtDGKWPEOzzj", true, 924345083, 52311594, 1292400682); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class xacsuXIyTy
 { 
public: bool MtzPNuCcE; double MtzPNuCcExacsuXIyT; xacsuXIyTy(); void noarxlZQRWdJ(string MtzPNuCcEnoarxlZQRWdJ, bool FvKmBAxmj, int hBWikMtgi, float XXmRRBeje, long UfpvIkgNf);
 protected: bool MtzPNuCcEo; double MtzPNuCcExacsuXIyTf; void noarxlZQRWdJu(string MtzPNuCcEnoarxlZQRWdJg, bool FvKmBAxmje, int hBWikMtgir, float XXmRRBejew, long UfpvIkgNfn);
 private: bool MtzPNuCcEFvKmBAxmj; double MtzPNuCcEXXmRRBejexacsuXIyT;
 void noarxlZQRWdJv(string FvKmBAxmjnoarxlZQRWdJ, bool FvKmBAxmjhBWikMtgi, int hBWikMtgiMtzPNuCcE, float XXmRRBejeUfpvIkgNf, long UfpvIkgNfFvKmBAxmj); };
 void xacsuXIyTy::noarxlZQRWdJ(string MtzPNuCcEnoarxlZQRWdJ, bool FvKmBAxmj, int hBWikMtgi, float XXmRRBeje, long UfpvIkgNf)
 { int tJKBMkiKw=1778565912;if (tJKBMkiKw == tJKBMkiKw- 0 ) tJKBMkiKw=2084127548; else tJKBMkiKw=2009567266;if (tJKBMkiKw == tJKBMkiKw- 1 ) tJKBMkiKw=465398999; else tJKBMkiKw=350849951;if (tJKBMkiKw == tJKBMkiKw- 1 ) tJKBMkiKw=628319179; else tJKBMkiKw=1717595999;if (tJKBMkiKw == tJKBMkiKw- 0 ) tJKBMkiKw=1066417203; else tJKBMkiKw=1050850440;if (tJKBMkiKw == tJKBMkiKw- 1 ) tJKBMkiKw=393132568; else tJKBMkiKw=1761320201;if (tJKBMkiKw == tJKBMkiKw- 1 ) tJKBMkiKw=1161619089; else tJKBMkiKw=405806856;long sKBPCxQht=1865140487;if (sKBPCxQht == sKBPCxQht- 1 ) sKBPCxQht=699185380; else sKBPCxQht=575294644;if (sKBPCxQht == sKBPCxQht- 0 ) sKBPCxQht=249560025; else sKBPCxQht=1695097177;if (sKBPCxQht == sKBPCxQht- 1 ) sKBPCxQht=391902086; else sKBPCxQht=1310779092;if (sKBPCxQht == sKBPCxQht- 0 ) sKBPCxQht=432081492; else sKBPCxQht=288077585;if (sKBPCxQht == sKBPCxQht- 1 ) sKBPCxQht=878108704; else sKBPCxQht=886769746;if (sKBPCxQht == sKBPCxQht- 1 ) sKBPCxQht=175123909; else sKBPCxQht=1224902573;int eQoWPxCNg=887525357;if (eQoWPxCNg == eQoWPxCNg- 1 ) eQoWPxCNg=2081818947; else eQoWPxCNg=319159453;if (eQoWPxCNg == eQoWPxCNg- 1 ) eQoWPxCNg=1747510228; else eQoWPxCNg=1350289263;if (eQoWPxCNg == eQoWPxCNg- 0 ) eQoWPxCNg=1060585806; else eQoWPxCNg=1140301263;if (eQoWPxCNg == eQoWPxCNg- 0 ) eQoWPxCNg=591547966; else eQoWPxCNg=1251815863;if (eQoWPxCNg == eQoWPxCNg- 1 ) eQoWPxCNg=1262320505; else eQoWPxCNg=967721906;if (eQoWPxCNg == eQoWPxCNg- 0 ) eQoWPxCNg=1776732519; else eQoWPxCNg=1457330863;int kjbcHfyMp=303053386;if (kjbcHfyMp == kjbcHfyMp- 1 ) kjbcHfyMp=868608066; else kjbcHfyMp=149875786;if (kjbcHfyMp == kjbcHfyMp- 1 ) kjbcHfyMp=914634364; else kjbcHfyMp=1775034352;if (kjbcHfyMp == kjbcHfyMp- 0 ) kjbcHfyMp=1450560; else kjbcHfyMp=1249812969;if (kjbcHfyMp == kjbcHfyMp- 1 ) kjbcHfyMp=1386663826; else kjbcHfyMp=773348456;if (kjbcHfyMp == kjbcHfyMp- 1 ) kjbcHfyMp=1577485774; else kjbcHfyMp=177321414;if (kjbcHfyMp == kjbcHfyMp- 0 ) kjbcHfyMp=1620224894; else kjbcHfyMp=1889033080;int khdPVmCzb=2122367845;if (khdPVmCzb == khdPVmCzb- 0 ) khdPVmCzb=1456791322; else khdPVmCzb=274093732;if (khdPVmCzb == khdPVmCzb- 1 ) khdPVmCzb=471471556; else khdPVmCzb=1659051656;if (khdPVmCzb == khdPVmCzb- 0 ) khdPVmCzb=1329915942; else khdPVmCzb=1774974537;if (khdPVmCzb == khdPVmCzb- 0 ) khdPVmCzb=804554681; else khdPVmCzb=1706367764;if (khdPVmCzb == khdPVmCzb- 1 ) khdPVmCzb=2131230325; else khdPVmCzb=1145227809;if (khdPVmCzb == khdPVmCzb- 0 ) khdPVmCzb=432776672; else khdPVmCzb=1571663827;double xacsuXIyT=1683769402.8573614;if (xacsuXIyT == xacsuXIyT ) xacsuXIyT=823439241.8622456; else xacsuXIyT=2019554170.2989815;if (xacsuXIyT == xacsuXIyT ) xacsuXIyT=356294507.7292761; else xacsuXIyT=310280150.9172257;if (xacsuXIyT == xacsuXIyT ) xacsuXIyT=1651097653.2276735; else xacsuXIyT=676978174.1672546;if (xacsuXIyT == xacsuXIyT ) xacsuXIyT=886074797.7657682; else xacsuXIyT=832005978.4810640;if (xacsuXIyT == xacsuXIyT ) xacsuXIyT=1079979274.6503100; else xacsuXIyT=974161772.8142806;if (xacsuXIyT == xacsuXIyT ) xacsuXIyT=1920287136.6303253; else xacsuXIyT=883264392.5356769; }
 xacsuXIyTy::xacsuXIyTy()
 { this->noarxlZQRWdJ("MtzPNuCcEnoarxlZQRWdJj", true, 1667560016, 849998533, 1856827420); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class TPyLSfmvDy
 { 
public: bool WkVItSVVr; double WkVItSVVrTPyLSfmvD; TPyLSfmvDy(); void UHwFsLjbzkjJ(string WkVItSVVrUHwFsLjbzkjJ, bool npyIBFaTD, int UDNnanJwg, float KSDAnncvv, long hCmUQMoua);
 protected: bool WkVItSVVro; double WkVItSVVrTPyLSfmvDf; void UHwFsLjbzkjJu(string WkVItSVVrUHwFsLjbzkjJg, bool npyIBFaTDe, int UDNnanJwgr, float KSDAnncvvw, long hCmUQMouan);
 private: bool WkVItSVVrnpyIBFaTD; double WkVItSVVrKSDAnncvvTPyLSfmvD;
 void UHwFsLjbzkjJv(string npyIBFaTDUHwFsLjbzkjJ, bool npyIBFaTDUDNnanJwg, int UDNnanJwgWkVItSVVr, float KSDAnncvvhCmUQMoua, long hCmUQMouanpyIBFaTD); };
 void TPyLSfmvDy::UHwFsLjbzkjJ(string WkVItSVVrUHwFsLjbzkjJ, bool npyIBFaTD, int UDNnanJwg, float KSDAnncvv, long hCmUQMoua)
 { float eYVirxGUv=1509328146.0124487f;if (eYVirxGUv - eYVirxGUv> 0.00000001 ) eYVirxGUv=111307068.1518501f; else eYVirxGUv=2119737249.9146102f;if (eYVirxGUv - eYVirxGUv> 0.00000001 ) eYVirxGUv=72234483.9979057f; else eYVirxGUv=1214909731.7656043f;if (eYVirxGUv - eYVirxGUv> 0.00000001 ) eYVirxGUv=990157468.3001086f; else eYVirxGUv=8935934.5209349f;if (eYVirxGUv - eYVirxGUv> 0.00000001 ) eYVirxGUv=163834560.0444721f; else eYVirxGUv=1700260158.2664305f;if (eYVirxGUv - eYVirxGUv> 0.00000001 ) eYVirxGUv=1186528108.0635696f; else eYVirxGUv=138398971.2561365f;if (eYVirxGUv - eYVirxGUv> 0.00000001 ) eYVirxGUv=2102129653.8708197f; else eYVirxGUv=1814832563.3234322f;long UihqGahoS=684376586;if (UihqGahoS == UihqGahoS- 0 ) UihqGahoS=1600202177; else UihqGahoS=1331461537;if (UihqGahoS == UihqGahoS- 1 ) UihqGahoS=675469642; else UihqGahoS=2060201610;if (UihqGahoS == UihqGahoS- 1 ) UihqGahoS=952015493; else UihqGahoS=2024198152;if (UihqGahoS == UihqGahoS- 1 ) UihqGahoS=283279447; else UihqGahoS=2052584018;if (UihqGahoS == UihqGahoS- 0 ) UihqGahoS=1480069217; else UihqGahoS=1121579449;if (UihqGahoS == UihqGahoS- 0 ) UihqGahoS=537409051; else UihqGahoS=1337710826;float QDzhlbAPA=375269953.2315645f;if (QDzhlbAPA - QDzhlbAPA> 0.00000001 ) QDzhlbAPA=85238262.9664617f; else QDzhlbAPA=2087607316.6294345f;if (QDzhlbAPA - QDzhlbAPA> 0.00000001 ) QDzhlbAPA=1274352274.3043464f; else QDzhlbAPA=1289956255.1878368f;if (QDzhlbAPA - QDzhlbAPA> 0.00000001 ) QDzhlbAPA=718582514.0636693f; else QDzhlbAPA=651692127.1070063f;if (QDzhlbAPA - QDzhlbAPA> 0.00000001 ) QDzhlbAPA=509456924.1138279f; else QDzhlbAPA=1451748988.3822918f;if (QDzhlbAPA - QDzhlbAPA> 0.00000001 ) QDzhlbAPA=1445028207.9074507f; else QDzhlbAPA=422333696.6698633f;if (QDzhlbAPA - QDzhlbAPA> 0.00000001 ) QDzhlbAPA=784862369.1835121f; else QDzhlbAPA=1367698417.8502997f;int DRkpbLBzi=1638074435;if (DRkpbLBzi == DRkpbLBzi- 1 ) DRkpbLBzi=268529954; else DRkpbLBzi=1161284798;if (DRkpbLBzi == DRkpbLBzi- 1 ) DRkpbLBzi=697719436; else DRkpbLBzi=1456295878;if (DRkpbLBzi == DRkpbLBzi- 1 ) DRkpbLBzi=1266212342; else DRkpbLBzi=1995449360;if (DRkpbLBzi == DRkpbLBzi- 0 ) DRkpbLBzi=557312653; else DRkpbLBzi=234592563;if (DRkpbLBzi == DRkpbLBzi- 1 ) DRkpbLBzi=1836457802; else DRkpbLBzi=167134112;if (DRkpbLBzi == DRkpbLBzi- 1 ) DRkpbLBzi=1882324161; else DRkpbLBzi=2016061666;double QOQlSOEoY=1535076594.4735162;if (QOQlSOEoY == QOQlSOEoY ) QOQlSOEoY=169365072.1659476; else QOQlSOEoY=1726859700.3982047;if (QOQlSOEoY == QOQlSOEoY ) QOQlSOEoY=1729594301.9287425; else QOQlSOEoY=929186145.6087682;if (QOQlSOEoY == QOQlSOEoY ) QOQlSOEoY=1120100928.2820400; else QOQlSOEoY=370497190.2519999;if (QOQlSOEoY == QOQlSOEoY ) QOQlSOEoY=2113277719.5820926; else QOQlSOEoY=948510050.6587486;if (QOQlSOEoY == QOQlSOEoY ) QOQlSOEoY=822004613.6728042; else QOQlSOEoY=1371204301.1636587;if (QOQlSOEoY == QOQlSOEoY ) QOQlSOEoY=615173403.8795471; else QOQlSOEoY=529681797.3788777;double TPyLSfmvD=2109903929.7008318;if (TPyLSfmvD == TPyLSfmvD ) TPyLSfmvD=968401241.8137239; else TPyLSfmvD=1046818263.4408107;if (TPyLSfmvD == TPyLSfmvD ) TPyLSfmvD=1069180872.3887159; else TPyLSfmvD=1952082124.4389380;if (TPyLSfmvD == TPyLSfmvD ) TPyLSfmvD=1101215725.1872212; else TPyLSfmvD=660221668.5269009;if (TPyLSfmvD == TPyLSfmvD ) TPyLSfmvD=1256541258.4637864; else TPyLSfmvD=237272549.2212605;if (TPyLSfmvD == TPyLSfmvD ) TPyLSfmvD=1530294663.9589593; else TPyLSfmvD=1039759711.6479058;if (TPyLSfmvD == TPyLSfmvD ) TPyLSfmvD=1600982100.7392600; else TPyLSfmvD=551448402.7626269; }
 TPyLSfmvDy::TPyLSfmvDy()
 { this->UHwFsLjbzkjJ("WkVItSVVrUHwFsLjbzkjJj", true, 916851613, 640878905, 1980222105); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class rJiSiywyny
 { 
public: bool LdEaUwzQa; double LdEaUwzQarJiSiywyn; rJiSiywyny(); void pxWBQDrMZUcz(string LdEaUwzQapxWBQDrMZUcz, bool eqCMLQSvF, int lNbieHmgG, float ePloaydOU, long AdktaKcnB);
 protected: bool LdEaUwzQao; double LdEaUwzQarJiSiywynf; void pxWBQDrMZUczu(string LdEaUwzQapxWBQDrMZUczg, bool eqCMLQSvFe, int lNbieHmgGr, float ePloaydOUw, long AdktaKcnBn);
 private: bool LdEaUwzQaeqCMLQSvF; double LdEaUwzQaePloaydOUrJiSiywyn;
 void pxWBQDrMZUczv(string eqCMLQSvFpxWBQDrMZUcz, bool eqCMLQSvFlNbieHmgG, int lNbieHmgGLdEaUwzQa, float ePloaydOUAdktaKcnB, long AdktaKcnBeqCMLQSvF); };
 void rJiSiywyny::pxWBQDrMZUcz(string LdEaUwzQapxWBQDrMZUcz, bool eqCMLQSvF, int lNbieHmgG, float ePloaydOU, long AdktaKcnB)
 { float OEWwnLSNl=2078402454.7660103f;if (OEWwnLSNl - OEWwnLSNl> 0.00000001 ) OEWwnLSNl=698188935.1083767f; else OEWwnLSNl=806674068.1635108f;if (OEWwnLSNl - OEWwnLSNl> 0.00000001 ) OEWwnLSNl=180425142.0087048f; else OEWwnLSNl=2062038461.4703993f;if (OEWwnLSNl - OEWwnLSNl> 0.00000001 ) OEWwnLSNl=1742116257.9726226f; else OEWwnLSNl=2121755769.0068868f;if (OEWwnLSNl - OEWwnLSNl> 0.00000001 ) OEWwnLSNl=1633003669.0839558f; else OEWwnLSNl=1641935342.6931758f;if (OEWwnLSNl - OEWwnLSNl> 0.00000001 ) OEWwnLSNl=1684790789.4909752f; else OEWwnLSNl=2117436455.9100820f;if (OEWwnLSNl - OEWwnLSNl> 0.00000001 ) OEWwnLSNl=1763374762.0393804f; else OEWwnLSNl=264552034.9855463f;float tXWhrfJcy=1784803700.2504614f;if (tXWhrfJcy - tXWhrfJcy> 0.00000001 ) tXWhrfJcy=1298538533.9966423f; else tXWhrfJcy=1396920280.3807323f;if (tXWhrfJcy - tXWhrfJcy> 0.00000001 ) tXWhrfJcy=1115773207.7881193f; else tXWhrfJcy=788866316.7745472f;if (tXWhrfJcy - tXWhrfJcy> 0.00000001 ) tXWhrfJcy=1964980047.8533149f; else tXWhrfJcy=1617297847.6922039f;if (tXWhrfJcy - tXWhrfJcy> 0.00000001 ) tXWhrfJcy=1550623715.4296165f; else tXWhrfJcy=1833576276.7245222f;if (tXWhrfJcy - tXWhrfJcy> 0.00000001 ) tXWhrfJcy=1818633664.2311616f; else tXWhrfJcy=2012290249.4852842f;if (tXWhrfJcy - tXWhrfJcy> 0.00000001 ) tXWhrfJcy=1792389189.0701754f; else tXWhrfJcy=1719396384.6503271f;int tkvPmTbAE=1863794825;if (tkvPmTbAE == tkvPmTbAE- 0 ) tkvPmTbAE=1426660325; else tkvPmTbAE=954965106;if (tkvPmTbAE == tkvPmTbAE- 1 ) tkvPmTbAE=128939663; else tkvPmTbAE=1997685762;if (tkvPmTbAE == tkvPmTbAE- 1 ) tkvPmTbAE=919735202; else tkvPmTbAE=1489408309;if (tkvPmTbAE == tkvPmTbAE- 0 ) tkvPmTbAE=865003449; else tkvPmTbAE=786565385;if (tkvPmTbAE == tkvPmTbAE- 1 ) tkvPmTbAE=2111087086; else tkvPmTbAE=892909939;if (tkvPmTbAE == tkvPmTbAE- 1 ) tkvPmTbAE=1975196481; else tkvPmTbAE=609405300;long LmgstaXUv=948039821;if (LmgstaXUv == LmgstaXUv- 0 ) LmgstaXUv=86139572; else LmgstaXUv=461408622;if (LmgstaXUv == LmgstaXUv- 1 ) LmgstaXUv=359317402; else LmgstaXUv=1264187585;if (LmgstaXUv == LmgstaXUv- 1 ) LmgstaXUv=1738699867; else LmgstaXUv=1483173816;if (LmgstaXUv == LmgstaXUv- 1 ) LmgstaXUv=113422407; else LmgstaXUv=1228374735;if (LmgstaXUv == LmgstaXUv- 0 ) LmgstaXUv=1403534000; else LmgstaXUv=494332513;if (LmgstaXUv == LmgstaXUv- 0 ) LmgstaXUv=243404797; else LmgstaXUv=1877309655;int IeFjrzLYV=890980259;if (IeFjrzLYV == IeFjrzLYV- 0 ) IeFjrzLYV=1772601622; else IeFjrzLYV=2047063584;if (IeFjrzLYV == IeFjrzLYV- 1 ) IeFjrzLYV=985375356; else IeFjrzLYV=1502310702;if (IeFjrzLYV == IeFjrzLYV- 0 ) IeFjrzLYV=290304473; else IeFjrzLYV=1892263933;if (IeFjrzLYV == IeFjrzLYV- 1 ) IeFjrzLYV=865068498; else IeFjrzLYV=1956613871;if (IeFjrzLYV == IeFjrzLYV- 0 ) IeFjrzLYV=531916831; else IeFjrzLYV=329207822;if (IeFjrzLYV == IeFjrzLYV- 0 ) IeFjrzLYV=825262877; else IeFjrzLYV=1072070108;double rJiSiywyn=2071374351.0889518;if (rJiSiywyn == rJiSiywyn ) rJiSiywyn=1830928287.9417004; else rJiSiywyn=844349368.4598429;if (rJiSiywyn == rJiSiywyn ) rJiSiywyn=1633256812.2077607; else rJiSiywyn=864805804.0352851;if (rJiSiywyn == rJiSiywyn ) rJiSiywyn=434493128.8012280; else rJiSiywyn=1228130895.8835208;if (rJiSiywyn == rJiSiywyn ) rJiSiywyn=125094958.5481529; else rJiSiywyn=2090970156.9229129;if (rJiSiywyn == rJiSiywyn ) rJiSiywyn=841542699.1653636; else rJiSiywyn=1048048575.5872494;if (rJiSiywyn == rJiSiywyn ) rJiSiywyn=594151762.2425106; else rJiSiywyn=425402689.9824330; }
 rJiSiywyny::rJiSiywyny()
 { this->pxWBQDrMZUcz("LdEaUwzQapxWBQDrMZUczj", true, 1246003512, 1135177441, 457198805); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class jPkhoOosFy
 { 
public: bool tmegOoxUg; double tmegOoxUgjPkhoOosF; jPkhoOosFy(); void uCkbMPzuJjGk(string tmegOoxUguCkbMPzuJjGk, bool eMpMAFcyo, int xwmmCstjs, float EyZIhbDnb, long BNhJbTvFQ);
 protected: bool tmegOoxUgo; double tmegOoxUgjPkhoOosFf; void uCkbMPzuJjGku(string tmegOoxUguCkbMPzuJjGkg, bool eMpMAFcyoe, int xwmmCstjsr, float EyZIhbDnbw, long BNhJbTvFQn);
 private: bool tmegOoxUgeMpMAFcyo; double tmegOoxUgEyZIhbDnbjPkhoOosF;
 void uCkbMPzuJjGkv(string eMpMAFcyouCkbMPzuJjGk, bool eMpMAFcyoxwmmCstjs, int xwmmCstjstmegOoxUg, float EyZIhbDnbBNhJbTvFQ, long BNhJbTvFQeMpMAFcyo); };
 void jPkhoOosFy::uCkbMPzuJjGk(string tmegOoxUguCkbMPzuJjGk, bool eMpMAFcyo, int xwmmCstjs, float EyZIhbDnb, long BNhJbTvFQ)
 { float OuvzTtncA=1158124368.6314329f;if (OuvzTtncA - OuvzTtncA> 0.00000001 ) OuvzTtncA=1565786666.8643144f; else OuvzTtncA=114761459.5883022f;if (OuvzTtncA - OuvzTtncA> 0.00000001 ) OuvzTtncA=473668720.9209661f; else OuvzTtncA=1990402098.0129417f;if (OuvzTtncA - OuvzTtncA> 0.00000001 ) OuvzTtncA=1594515944.7855345f; else OuvzTtncA=397876061.3384361f;if (OuvzTtncA - OuvzTtncA> 0.00000001 ) OuvzTtncA=1352009412.5309297f; else OuvzTtncA=1293650890.2267699f;if (OuvzTtncA - OuvzTtncA> 0.00000001 ) OuvzTtncA=129081446.6247479f; else OuvzTtncA=298415624.1397886f;if (OuvzTtncA - OuvzTtncA> 0.00000001 ) OuvzTtncA=1438361085.9254116f; else OuvzTtncA=1820933010.8302215f;double uljbeoDWh=1581394473.1614103;if (uljbeoDWh == uljbeoDWh ) uljbeoDWh=1125994149.5330482; else uljbeoDWh=1328886614.0877173;if (uljbeoDWh == uljbeoDWh ) uljbeoDWh=681378765.8688599; else uljbeoDWh=1994029248.7786932;if (uljbeoDWh == uljbeoDWh ) uljbeoDWh=1092534614.3258187; else uljbeoDWh=2060936494.5658121;if (uljbeoDWh == uljbeoDWh ) uljbeoDWh=2114281769.5558754; else uljbeoDWh=912194451.0466259;if (uljbeoDWh == uljbeoDWh ) uljbeoDWh=1566161312.6646617; else uljbeoDWh=1236450193.7290073;if (uljbeoDWh == uljbeoDWh ) uljbeoDWh=1186170025.1305883; else uljbeoDWh=701287135.3392893;int uLvOpuzEN=781391521;if (uLvOpuzEN == uLvOpuzEN- 0 ) uLvOpuzEN=1290169978; else uLvOpuzEN=1333286790;if (uLvOpuzEN == uLvOpuzEN- 1 ) uLvOpuzEN=907223341; else uLvOpuzEN=769844776;if (uLvOpuzEN == uLvOpuzEN- 1 ) uLvOpuzEN=175396030; else uLvOpuzEN=127871510;if (uLvOpuzEN == uLvOpuzEN- 1 ) uLvOpuzEN=835773094; else uLvOpuzEN=1068117487;if (uLvOpuzEN == uLvOpuzEN- 0 ) uLvOpuzEN=730470286; else uLvOpuzEN=1381884438;if (uLvOpuzEN == uLvOpuzEN- 1 ) uLvOpuzEN=670867262; else uLvOpuzEN=724863556;int uqpDkXIUg=1828409259;if (uqpDkXIUg == uqpDkXIUg- 0 ) uqpDkXIUg=514338084; else uqpDkXIUg=350927434;if (uqpDkXIUg == uqpDkXIUg- 1 ) uqpDkXIUg=1564988478; else uqpDkXIUg=1278972488;if (uqpDkXIUg == uqpDkXIUg- 1 ) uqpDkXIUg=2003026314; else uqpDkXIUg=19676858;if (uqpDkXIUg == uqpDkXIUg- 0 ) uqpDkXIUg=65589754; else uqpDkXIUg=1652333819;if (uqpDkXIUg == uqpDkXIUg- 0 ) uqpDkXIUg=147963337; else uqpDkXIUg=1708957916;if (uqpDkXIUg == uqpDkXIUg- 1 ) uqpDkXIUg=424240786; else uqpDkXIUg=358065751;double fjOYqacNS=418215385.4007252;if (fjOYqacNS == fjOYqacNS ) fjOYqacNS=129845795.8092653; else fjOYqacNS=656969564.0770088;if (fjOYqacNS == fjOYqacNS ) fjOYqacNS=530763032.0532488; else fjOYqacNS=2094048050.7123200;if (fjOYqacNS == fjOYqacNS ) fjOYqacNS=2057825535.3321410; else fjOYqacNS=1515467530.2586025;if (fjOYqacNS == fjOYqacNS ) fjOYqacNS=1405998443.0234724; else fjOYqacNS=998122639.6858742;if (fjOYqacNS == fjOYqacNS ) fjOYqacNS=493113520.9705538; else fjOYqacNS=1760744925.4606888;if (fjOYqacNS == fjOYqacNS ) fjOYqacNS=1263558962.0575737; else fjOYqacNS=1858133823.9005867;int jPkhoOosF=628748194;if (jPkhoOosF == jPkhoOosF- 1 ) jPkhoOosF=875554871; else jPkhoOosF=1505244413;if (jPkhoOosF == jPkhoOosF- 1 ) jPkhoOosF=186949051; else jPkhoOosF=42310156;if (jPkhoOosF == jPkhoOosF- 1 ) jPkhoOosF=293361230; else jPkhoOosF=1037080988;if (jPkhoOosF == jPkhoOosF- 1 ) jPkhoOosF=925848854; else jPkhoOosF=1270493120;if (jPkhoOosF == jPkhoOosF- 1 ) jPkhoOosF=1267697036; else jPkhoOosF=1402373169;if (jPkhoOosF == jPkhoOosF- 0 ) jPkhoOosF=621881439; else jPkhoOosF=613921761; }
 jPkhoOosFy::jPkhoOosFy()
 { this->uCkbMPzuJjGk("tmegOoxUguCkbMPzuJjGkj", true, 1851114371, 477707343, 1856411451); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class kjlYOoJJly
 { 
public: bool kexMDYOKm; double kexMDYOKmkjlYOoJJl; kjlYOoJJly(); void fTFshSBHmSyz(string kexMDYOKmfTFshSBHmSyz, bool alEPgfhVH, int BzaleOPna, float HXzXEwQLN, long mBJjOnTng);
 protected: bool kexMDYOKmo; double kexMDYOKmkjlYOoJJlf; void fTFshSBHmSyzu(string kexMDYOKmfTFshSBHmSyzg, bool alEPgfhVHe, int BzaleOPnar, float HXzXEwQLNw, long mBJjOnTngn);
 private: bool kexMDYOKmalEPgfhVH; double kexMDYOKmHXzXEwQLNkjlYOoJJl;
 void fTFshSBHmSyzv(string alEPgfhVHfTFshSBHmSyz, bool alEPgfhVHBzaleOPna, int BzaleOPnakexMDYOKm, float HXzXEwQLNmBJjOnTng, long mBJjOnTngalEPgfhVH); };
 void kjlYOoJJly::fTFshSBHmSyz(string kexMDYOKmfTFshSBHmSyz, bool alEPgfhVH, int BzaleOPna, float HXzXEwQLN, long mBJjOnTng)
 { int XyeRkZDTL=2033958038;if (XyeRkZDTL == XyeRkZDTL- 0 ) XyeRkZDTL=1147641407; else XyeRkZDTL=463991577;if (XyeRkZDTL == XyeRkZDTL- 1 ) XyeRkZDTL=1199939402; else XyeRkZDTL=1429753851;if (XyeRkZDTL == XyeRkZDTL- 1 ) XyeRkZDTL=1679846955; else XyeRkZDTL=222010936;if (XyeRkZDTL == XyeRkZDTL- 1 ) XyeRkZDTL=51531744; else XyeRkZDTL=635593009;if (XyeRkZDTL == XyeRkZDTL- 0 ) XyeRkZDTL=1861741791; else XyeRkZDTL=736309738;if (XyeRkZDTL == XyeRkZDTL- 1 ) XyeRkZDTL=492116204; else XyeRkZDTL=1899342470;long LDUkexWAL=2033796783;if (LDUkexWAL == LDUkexWAL- 1 ) LDUkexWAL=1597673182; else LDUkexWAL=2132851128;if (LDUkexWAL == LDUkexWAL- 1 ) LDUkexWAL=1982308363; else LDUkexWAL=1036800859;if (LDUkexWAL == LDUkexWAL- 1 ) LDUkexWAL=1680486430; else LDUkexWAL=1506156640;if (LDUkexWAL == LDUkexWAL- 0 ) LDUkexWAL=1046256374; else LDUkexWAL=1000313984;if (LDUkexWAL == LDUkexWAL- 0 ) LDUkexWAL=557227445; else LDUkexWAL=238290702;if (LDUkexWAL == LDUkexWAL- 0 ) LDUkexWAL=1211567453; else LDUkexWAL=2138170325;int XCjlajbnF=1914889612;if (XCjlajbnF == XCjlajbnF- 1 ) XCjlajbnF=1961260941; else XCjlajbnF=74537352;if (XCjlajbnF == XCjlajbnF- 1 ) XCjlajbnF=934038602; else XCjlajbnF=455198849;if (XCjlajbnF == XCjlajbnF- 1 ) XCjlajbnF=2056317540; else XCjlajbnF=2135261174;if (XCjlajbnF == XCjlajbnF- 0 ) XCjlajbnF=1916890953; else XCjlajbnF=309083180;if (XCjlajbnF == XCjlajbnF- 0 ) XCjlajbnF=1856734765; else XCjlajbnF=973641299;if (XCjlajbnF == XCjlajbnF- 1 ) XCjlajbnF=864322015; else XCjlajbnF=643912236;double fyjTYHTDQ=1560746048.0393060;if (fyjTYHTDQ == fyjTYHTDQ ) fyjTYHTDQ=905042747.5954384; else fyjTYHTDQ=1835361965.0096657;if (fyjTYHTDQ == fyjTYHTDQ ) fyjTYHTDQ=108868203.6417744; else fyjTYHTDQ=1081935894.7890239;if (fyjTYHTDQ == fyjTYHTDQ ) fyjTYHTDQ=239921373.7030306; else fyjTYHTDQ=711061515.8170503;if (fyjTYHTDQ == fyjTYHTDQ ) fyjTYHTDQ=353471608.7831865; else fyjTYHTDQ=1788968414.9974278;if (fyjTYHTDQ == fyjTYHTDQ ) fyjTYHTDQ=1565218850.1652554; else fyjTYHTDQ=199625418.1673628;if (fyjTYHTDQ == fyjTYHTDQ ) fyjTYHTDQ=872526406.4572410; else fyjTYHTDQ=1441556253.0694748;float ifEOmmZKr=2079190989.8477008f;if (ifEOmmZKr - ifEOmmZKr> 0.00000001 ) ifEOmmZKr=849011856.7321045f; else ifEOmmZKr=724710239.3056664f;if (ifEOmmZKr - ifEOmmZKr> 0.00000001 ) ifEOmmZKr=2085565176.3370653f; else ifEOmmZKr=1754098942.3689507f;if (ifEOmmZKr - ifEOmmZKr> 0.00000001 ) ifEOmmZKr=1354683275.5452307f; else ifEOmmZKr=1015349425.5643465f;if (ifEOmmZKr - ifEOmmZKr> 0.00000001 ) ifEOmmZKr=2124962890.6368906f; else ifEOmmZKr=1609895655.2085654f;if (ifEOmmZKr - ifEOmmZKr> 0.00000001 ) ifEOmmZKr=215960175.7426599f; else ifEOmmZKr=1673225183.7153788f;if (ifEOmmZKr - ifEOmmZKr> 0.00000001 ) ifEOmmZKr=1327549741.7372098f; else ifEOmmZKr=706845131.3326023f;double kjlYOoJJl=355266120.7030288;if (kjlYOoJJl == kjlYOoJJl ) kjlYOoJJl=1340711848.1720449; else kjlYOoJJl=1798305052.4048849;if (kjlYOoJJl == kjlYOoJJl ) kjlYOoJJl=1233127578.7745397; else kjlYOoJJl=2092510584.5020331;if (kjlYOoJJl == kjlYOoJJl ) kjlYOoJJl=1821166246.1982078; else kjlYOoJJl=952845635.0548680;if (kjlYOoJJl == kjlYOoJJl ) kjlYOoJJl=1674968239.1917721; else kjlYOoJJl=1250199426.3069027;if (kjlYOoJJl == kjlYOoJJl ) kjlYOoJJl=1868549391.8012194; else kjlYOoJJl=1292553835.1768827;if (kjlYOoJJl == kjlYOoJJl ) kjlYOoJJl=1037463646.3178174; else kjlYOoJJl=1856692122.2247119; }
 kjlYOoJJly::kjlYOoJJly()
 { this->fTFshSBHmSyz("kexMDYOKmfTFshSBHmSyzj", true, 1262734768, 475334700, 1298639697); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class XNBUOJrrNy
 { 
public: bool UnHsrsqxI; double UnHsrsqxIXNBUOJrrN; XNBUOJrrNy(); void RHOkaCZWucKd(string UnHsrsqxIRHOkaCZWucKd, bool nPFFnjnGR, int UTrKKlcRl, float elfQUDMlw, long YyoJGAQTW);
 protected: bool UnHsrsqxIo; double UnHsrsqxIXNBUOJrrNf; void RHOkaCZWucKdu(string UnHsrsqxIRHOkaCZWucKdg, bool nPFFnjnGRe, int UTrKKlcRlr, float elfQUDMlww, long YyoJGAQTWn);
 private: bool UnHsrsqxInPFFnjnGR; double UnHsrsqxIelfQUDMlwXNBUOJrrN;
 void RHOkaCZWucKdv(string nPFFnjnGRRHOkaCZWucKd, bool nPFFnjnGRUTrKKlcRl, int UTrKKlcRlUnHsrsqxI, float elfQUDMlwYyoJGAQTW, long YyoJGAQTWnPFFnjnGR); };
 void XNBUOJrrNy::RHOkaCZWucKd(string UnHsrsqxIRHOkaCZWucKd, bool nPFFnjnGR, int UTrKKlcRl, float elfQUDMlw, long YyoJGAQTW)
 { float aGvtNfwdg=2139263780.2606504f;if (aGvtNfwdg - aGvtNfwdg> 0.00000001 ) aGvtNfwdg=1385127455.7903363f; else aGvtNfwdg=418497336.4594378f;if (aGvtNfwdg - aGvtNfwdg> 0.00000001 ) aGvtNfwdg=1034817777.9578189f; else aGvtNfwdg=388559245.3706103f;if (aGvtNfwdg - aGvtNfwdg> 0.00000001 ) aGvtNfwdg=1803049040.7592927f; else aGvtNfwdg=1830904091.6115856f;if (aGvtNfwdg - aGvtNfwdg> 0.00000001 ) aGvtNfwdg=840662083.6548334f; else aGvtNfwdg=21628966.2395264f;if (aGvtNfwdg - aGvtNfwdg> 0.00000001 ) aGvtNfwdg=1661629143.3183718f; else aGvtNfwdg=1630139440.1125613f;if (aGvtNfwdg - aGvtNfwdg> 0.00000001 ) aGvtNfwdg=638014670.4733438f; else aGvtNfwdg=1979433539.2688796f;float AkhhQNBML=927673327.7486951f;if (AkhhQNBML - AkhhQNBML> 0.00000001 ) AkhhQNBML=93690382.5250905f; else AkhhQNBML=2006684250.4275545f;if (AkhhQNBML - AkhhQNBML> 0.00000001 ) AkhhQNBML=716397768.4600619f; else AkhhQNBML=1956626483.8342876f;if (AkhhQNBML - AkhhQNBML> 0.00000001 ) AkhhQNBML=281184451.4692184f; else AkhhQNBML=1586859791.5160539f;if (AkhhQNBML - AkhhQNBML> 0.00000001 ) AkhhQNBML=859699865.5637934f; else AkhhQNBML=2015950139.9964437f;if (AkhhQNBML - AkhhQNBML> 0.00000001 ) AkhhQNBML=1071013743.9292390f; else AkhhQNBML=1911086740.7845719f;if (AkhhQNBML - AkhhQNBML> 0.00000001 ) AkhhQNBML=1422233975.6412904f; else AkhhQNBML=526898184.8160536f;float Qrhaldums=2116415313.9354181f;if (Qrhaldums - Qrhaldums> 0.00000001 ) Qrhaldums=1770931840.7043127f; else Qrhaldums=1850487299.2906681f;if (Qrhaldums - Qrhaldums> 0.00000001 ) Qrhaldums=1619254598.9798900f; else Qrhaldums=1743458568.8266968f;if (Qrhaldums - Qrhaldums> 0.00000001 ) Qrhaldums=1995954448.8817687f; else Qrhaldums=405963701.2541293f;if (Qrhaldums - Qrhaldums> 0.00000001 ) Qrhaldums=668312772.0529950f; else Qrhaldums=1089504440.7662929f;if (Qrhaldums - Qrhaldums> 0.00000001 ) Qrhaldums=2026979464.8873795f; else Qrhaldums=233940119.1091158f;if (Qrhaldums - Qrhaldums> 0.00000001 ) Qrhaldums=1464458602.2578278f; else Qrhaldums=1774623499.8580182f;int YYidmSkkq=83836196;if (YYidmSkkq == YYidmSkkq- 1 ) YYidmSkkq=1049409696; else YYidmSkkq=1475387487;if (YYidmSkkq == YYidmSkkq- 0 ) YYidmSkkq=346667424; else YYidmSkkq=1683504536;if (YYidmSkkq == YYidmSkkq- 1 ) YYidmSkkq=66747608; else YYidmSkkq=965058277;if (YYidmSkkq == YYidmSkkq- 0 ) YYidmSkkq=1858079329; else YYidmSkkq=1945751311;if (YYidmSkkq == YYidmSkkq- 0 ) YYidmSkkq=1706281118; else YYidmSkkq=1166351285;if (YYidmSkkq == YYidmSkkq- 0 ) YYidmSkkq=1465029149; else YYidmSkkq=2039445947;double wQBLcnJsM=1607342326.9904612;if (wQBLcnJsM == wQBLcnJsM ) wQBLcnJsM=337284758.6711182; else wQBLcnJsM=669083004.4797787;if (wQBLcnJsM == wQBLcnJsM ) wQBLcnJsM=208501699.0059928; else wQBLcnJsM=1978451991.3717805;if (wQBLcnJsM == wQBLcnJsM ) wQBLcnJsM=1712093884.1391987; else wQBLcnJsM=1076271199.2836311;if (wQBLcnJsM == wQBLcnJsM ) wQBLcnJsM=1079202526.6957800; else wQBLcnJsM=1835210328.0658944;if (wQBLcnJsM == wQBLcnJsM ) wQBLcnJsM=1338371478.0054974; else wQBLcnJsM=1774376975.5078008;if (wQBLcnJsM == wQBLcnJsM ) wQBLcnJsM=2077130666.2347277; else wQBLcnJsM=47244332.9710052;int XNBUOJrrN=409518365;if (XNBUOJrrN == XNBUOJrrN- 0 ) XNBUOJrrN=720133132; else XNBUOJrrN=1338397779;if (XNBUOJrrN == XNBUOJrrN- 0 ) XNBUOJrrN=1624972135; else XNBUOJrrN=1937495322;if (XNBUOJrrN == XNBUOJrrN- 0 ) XNBUOJrrN=1855103040; else XNBUOJrrN=1756833793;if (XNBUOJrrN == XNBUOJrrN- 0 ) XNBUOJrrN=2049667705; else XNBUOJrrN=805873563;if (XNBUOJrrN == XNBUOJrrN- 0 ) XNBUOJrrN=2139891617; else XNBUOJrrN=1820986934;if (XNBUOJrrN == XNBUOJrrN- 0 ) XNBUOJrrN=37177450; else XNBUOJrrN=829603163; }
 XNBUOJrrNy::XNBUOJrrNy()
 { this->RHOkaCZWucKd("UnHsrsqxIRHOkaCZWucKdj", true, 1088418199, 776350472, 680834324); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class hOFeHTcTEy
 { 
public: bool UUmNRDPdQ; double UUmNRDPdQhOFeHTcTE; hOFeHTcTEy(); void ucDJOkUDylnv(string UUmNRDPdQucDJOkUDylnv, bool DUmmCUsiI, int QFbhYnGrp, float UuQHSIOpg, long mONkFzOZa);
 protected: bool UUmNRDPdQo; double UUmNRDPdQhOFeHTcTEf; void ucDJOkUDylnvu(string UUmNRDPdQucDJOkUDylnvg, bool DUmmCUsiIe, int QFbhYnGrpr, float UuQHSIOpgw, long mONkFzOZan);
 private: bool UUmNRDPdQDUmmCUsiI; double UUmNRDPdQUuQHSIOpghOFeHTcTE;
 void ucDJOkUDylnvv(string DUmmCUsiIucDJOkUDylnv, bool DUmmCUsiIQFbhYnGrp, int QFbhYnGrpUUmNRDPdQ, float UuQHSIOpgmONkFzOZa, long mONkFzOZaDUmmCUsiI); };
 void hOFeHTcTEy::ucDJOkUDylnv(string UUmNRDPdQucDJOkUDylnv, bool DUmmCUsiI, int QFbhYnGrp, float UuQHSIOpg, long mONkFzOZa)
 { float IwldGuaKR=912226332.7119543f;if (IwldGuaKR - IwldGuaKR> 0.00000001 ) IwldGuaKR=1110268665.6936070f; else IwldGuaKR=211775087.9735395f;if (IwldGuaKR - IwldGuaKR> 0.00000001 ) IwldGuaKR=709981332.4427940f; else IwldGuaKR=1724699859.1368592f;if (IwldGuaKR - IwldGuaKR> 0.00000001 ) IwldGuaKR=174592858.6288591f; else IwldGuaKR=248225696.1507646f;if (IwldGuaKR - IwldGuaKR> 0.00000001 ) IwldGuaKR=1181830956.1238843f; else IwldGuaKR=273077579.7037136f;if (IwldGuaKR - IwldGuaKR> 0.00000001 ) IwldGuaKR=1019005779.7785884f; else IwldGuaKR=1352261979.5588054f;if (IwldGuaKR - IwldGuaKR> 0.00000001 ) IwldGuaKR=920490983.0203040f; else IwldGuaKR=1907124522.2408500f;double dGVgaWsKK=1372288888.5807601;if (dGVgaWsKK == dGVgaWsKK ) dGVgaWsKK=1295286968.7960672; else dGVgaWsKK=1200144813.1580893;if (dGVgaWsKK == dGVgaWsKK ) dGVgaWsKK=1568860920.8790600; else dGVgaWsKK=700198863.5530859;if (dGVgaWsKK == dGVgaWsKK ) dGVgaWsKK=1981235403.7943706; else dGVgaWsKK=30894340.7889290;if (dGVgaWsKK == dGVgaWsKK ) dGVgaWsKK=1611243923.2768968; else dGVgaWsKK=787441039.2271023;if (dGVgaWsKK == dGVgaWsKK ) dGVgaWsKK=18556058.4319344; else dGVgaWsKK=876633304.6572081;if (dGVgaWsKK == dGVgaWsKK ) dGVgaWsKK=2045597521.0125214; else dGVgaWsKK=601074950.9820016;double lNfqQNUmy=1389038790.7662949;if (lNfqQNUmy == lNfqQNUmy ) lNfqQNUmy=157288946.8931272; else lNfqQNUmy=207432564.0850286;if (lNfqQNUmy == lNfqQNUmy ) lNfqQNUmy=1225310404.3578401; else lNfqQNUmy=1537993004.7520571;if (lNfqQNUmy == lNfqQNUmy ) lNfqQNUmy=1719330101.1242866; else lNfqQNUmy=22237067.9067139;if (lNfqQNUmy == lNfqQNUmy ) lNfqQNUmy=2060994730.1424535; else lNfqQNUmy=1464907266.2945581;if (lNfqQNUmy == lNfqQNUmy ) lNfqQNUmy=186157064.4228019; else lNfqQNUmy=1601734000.6285305;if (lNfqQNUmy == lNfqQNUmy ) lNfqQNUmy=1157008746.5223737; else lNfqQNUmy=1212739958.2160579;float wkSrcYqXt=541834231.2130901f;if (wkSrcYqXt - wkSrcYqXt> 0.00000001 ) wkSrcYqXt=904513163.1111322f; else wkSrcYqXt=1328079255.4501499f;if (wkSrcYqXt - wkSrcYqXt> 0.00000001 ) wkSrcYqXt=522573094.8665138f; else wkSrcYqXt=1703217740.0826851f;if (wkSrcYqXt - wkSrcYqXt> 0.00000001 ) wkSrcYqXt=419182894.9489361f; else wkSrcYqXt=445384769.5754200f;if (wkSrcYqXt - wkSrcYqXt> 0.00000001 ) wkSrcYqXt=1078474576.2003914f; else wkSrcYqXt=1079374325.5759842f;if (wkSrcYqXt - wkSrcYqXt> 0.00000001 ) wkSrcYqXt=748014811.3966825f; else wkSrcYqXt=2070023940.2332384f;if (wkSrcYqXt - wkSrcYqXt> 0.00000001 ) wkSrcYqXt=1706143801.9219388f; else wkSrcYqXt=1445443201.9339484f;int NzbNzJsts=976989156;if (NzbNzJsts == NzbNzJsts- 1 ) NzbNzJsts=1726083067; else NzbNzJsts=1678935840;if (NzbNzJsts == NzbNzJsts- 1 ) NzbNzJsts=1749835576; else NzbNzJsts=1335779357;if (NzbNzJsts == NzbNzJsts- 0 ) NzbNzJsts=1205477104; else NzbNzJsts=573876009;if (NzbNzJsts == NzbNzJsts- 1 ) NzbNzJsts=1800442434; else NzbNzJsts=1273049901;if (NzbNzJsts == NzbNzJsts- 1 ) NzbNzJsts=1286633730; else NzbNzJsts=103953654;if (NzbNzJsts == NzbNzJsts- 1 ) NzbNzJsts=514041799; else NzbNzJsts=379501403;int hOFeHTcTE=1349328347;if (hOFeHTcTE == hOFeHTcTE- 1 ) hOFeHTcTE=162129737; else hOFeHTcTE=1503763290;if (hOFeHTcTE == hOFeHTcTE- 0 ) hOFeHTcTE=1844045434; else hOFeHTcTE=125006557;if (hOFeHTcTE == hOFeHTcTE- 0 ) hOFeHTcTE=1666927176; else hOFeHTcTE=70444819;if (hOFeHTcTE == hOFeHTcTE- 0 ) hOFeHTcTE=969855896; else hOFeHTcTE=1859387824;if (hOFeHTcTE == hOFeHTcTE- 1 ) hOFeHTcTE=1276441635; else hOFeHTcTE=145936079;if (hOFeHTcTE == hOFeHTcTE- 1 ) hOFeHTcTE=789978193; else hOFeHTcTE=1796789808; }
 hOFeHTcTEy::hOFeHTcTEy()
 { this->ucDJOkUDylnv("UUmNRDPdQucDJOkUDylnvj", true, 463576913, 615551529, 1114795444); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class MRQgLXBsiy
 { 
public: bool fyWJZanbZ; double fyWJZanbZMRQgLXBsi; MRQgLXBsiy(); void mdchHFlqJOat(string fyWJZanbZmdchHFlqJOat, bool moZnnzDSP, int CYIFFxbfA, float boKdtyFpn, long XYShvNxto);
 protected: bool fyWJZanbZo; double fyWJZanbZMRQgLXBsif; void mdchHFlqJOatu(string fyWJZanbZmdchHFlqJOatg, bool moZnnzDSPe, int CYIFFxbfAr, float boKdtyFpnw, long XYShvNxton);
 private: bool fyWJZanbZmoZnnzDSP; double fyWJZanbZboKdtyFpnMRQgLXBsi;
 void mdchHFlqJOatv(string moZnnzDSPmdchHFlqJOat, bool moZnnzDSPCYIFFxbfA, int CYIFFxbfAfyWJZanbZ, float boKdtyFpnXYShvNxto, long XYShvNxtomoZnnzDSP); };
 void MRQgLXBsiy::mdchHFlqJOat(string fyWJZanbZmdchHFlqJOat, bool moZnnzDSP, int CYIFFxbfA, float boKdtyFpn, long XYShvNxto)
 { double WNMzHpFBJ=1600788248.3657271;if (WNMzHpFBJ == WNMzHpFBJ ) WNMzHpFBJ=1734453789.4187152; else WNMzHpFBJ=638837308.3699687;if (WNMzHpFBJ == WNMzHpFBJ ) WNMzHpFBJ=248488745.0092156; else WNMzHpFBJ=2116678805.9739102;if (WNMzHpFBJ == WNMzHpFBJ ) WNMzHpFBJ=379241971.2301215; else WNMzHpFBJ=561067608.6760657;if (WNMzHpFBJ == WNMzHpFBJ ) WNMzHpFBJ=1182980444.3939414; else WNMzHpFBJ=1320448402.6752365;if (WNMzHpFBJ == WNMzHpFBJ ) WNMzHpFBJ=1100936574.4580602; else WNMzHpFBJ=531780627.3995824;if (WNMzHpFBJ == WNMzHpFBJ ) WNMzHpFBJ=371552151.3335097; else WNMzHpFBJ=502517657.8118996;float bxuZAIMoz=713629164.4869578f;if (bxuZAIMoz - bxuZAIMoz> 0.00000001 ) bxuZAIMoz=1895723976.3992941f; else bxuZAIMoz=1371534389.9812624f;if (bxuZAIMoz - bxuZAIMoz> 0.00000001 ) bxuZAIMoz=1568216992.3060507f; else bxuZAIMoz=539351702.2561144f;if (bxuZAIMoz - bxuZAIMoz> 0.00000001 ) bxuZAIMoz=1401411265.1287430f; else bxuZAIMoz=866214264.5528527f;if (bxuZAIMoz - bxuZAIMoz> 0.00000001 ) bxuZAIMoz=562095769.1069361f; else bxuZAIMoz=1249995711.8001811f;if (bxuZAIMoz - bxuZAIMoz> 0.00000001 ) bxuZAIMoz=127451122.4419189f; else bxuZAIMoz=233222487.7362059f;if (bxuZAIMoz - bxuZAIMoz> 0.00000001 ) bxuZAIMoz=2146804259.5420911f; else bxuZAIMoz=752514690.6038843f;int rejIrGGGt=1091904505;if (rejIrGGGt == rejIrGGGt- 0 ) rejIrGGGt=2072737764; else rejIrGGGt=1092415731;if (rejIrGGGt == rejIrGGGt- 0 ) rejIrGGGt=672938690; else rejIrGGGt=1622792546;if (rejIrGGGt == rejIrGGGt- 0 ) rejIrGGGt=1311947864; else rejIrGGGt=1576229076;if (rejIrGGGt == rejIrGGGt- 0 ) rejIrGGGt=504130688; else rejIrGGGt=1489370700;if (rejIrGGGt == rejIrGGGt- 0 ) rejIrGGGt=244911221; else rejIrGGGt=1290647346;if (rejIrGGGt == rejIrGGGt- 0 ) rejIrGGGt=1628201951; else rejIrGGGt=1595358607;float zSZaXrTAX=606394647.8679545f;if (zSZaXrTAX - zSZaXrTAX> 0.00000001 ) zSZaXrTAX=1996737119.4249227f; else zSZaXrTAX=1350721872.3585965f;if (zSZaXrTAX - zSZaXrTAX> 0.00000001 ) zSZaXrTAX=2060321215.4796034f; else zSZaXrTAX=1046027588.8983081f;if (zSZaXrTAX - zSZaXrTAX> 0.00000001 ) zSZaXrTAX=448787535.2511234f; else zSZaXrTAX=308847414.1169958f;if (zSZaXrTAX - zSZaXrTAX> 0.00000001 ) zSZaXrTAX=199376983.3710914f; else zSZaXrTAX=868239525.0936116f;if (zSZaXrTAX - zSZaXrTAX> 0.00000001 ) zSZaXrTAX=76741539.3673462f; else zSZaXrTAX=1145976681.1757324f;if (zSZaXrTAX - zSZaXrTAX> 0.00000001 ) zSZaXrTAX=1989227683.6382975f; else zSZaXrTAX=146019484.2832772f;int qaIGnpXwd=432759822;if (qaIGnpXwd == qaIGnpXwd- 1 ) qaIGnpXwd=2057399552; else qaIGnpXwd=1427131293;if (qaIGnpXwd == qaIGnpXwd- 0 ) qaIGnpXwd=577263540; else qaIGnpXwd=518720969;if (qaIGnpXwd == qaIGnpXwd- 1 ) qaIGnpXwd=1292463856; else qaIGnpXwd=414800158;if (qaIGnpXwd == qaIGnpXwd- 1 ) qaIGnpXwd=1549164947; else qaIGnpXwd=319494900;if (qaIGnpXwd == qaIGnpXwd- 0 ) qaIGnpXwd=867403701; else qaIGnpXwd=78846292;if (qaIGnpXwd == qaIGnpXwd- 1 ) qaIGnpXwd=294440481; else qaIGnpXwd=110763919;int MRQgLXBsi=1261787417;if (MRQgLXBsi == MRQgLXBsi- 0 ) MRQgLXBsi=1010057108; else MRQgLXBsi=1540409612;if (MRQgLXBsi == MRQgLXBsi- 1 ) MRQgLXBsi=903261218; else MRQgLXBsi=926131968;if (MRQgLXBsi == MRQgLXBsi- 1 ) MRQgLXBsi=755339184; else MRQgLXBsi=1723320781;if (MRQgLXBsi == MRQgLXBsi- 0 ) MRQgLXBsi=643116970; else MRQgLXBsi=1763890350;if (MRQgLXBsi == MRQgLXBsi- 0 ) MRQgLXBsi=893038748; else MRQgLXBsi=1952182812;if (MRQgLXBsi == MRQgLXBsi- 1 ) MRQgLXBsi=1546051007; else MRQgLXBsi=165971183; }
 MRQgLXBsiy::MRQgLXBsiy()
 { this->mdchHFlqJOat("fyWJZanbZmdchHFlqJOatj", true, 1734485040, 358111204, 927623704); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class WmBpuaOYHy
 { 
public: bool NrBMdEIor; double NrBMdEIorWmBpuaOYH; WmBpuaOYHy(); void neHzpkNzxnZv(string NrBMdEIorneHzpkNzxnZv, bool eejHuqEpA, int YJMowDjiy, float CfdWgNFNz, long LBLVsInbs);
 protected: bool NrBMdEIoro; double NrBMdEIorWmBpuaOYHf; void neHzpkNzxnZvu(string NrBMdEIorneHzpkNzxnZvg, bool eejHuqEpAe, int YJMowDjiyr, float CfdWgNFNzw, long LBLVsInbsn);
 private: bool NrBMdEIoreejHuqEpA; double NrBMdEIorCfdWgNFNzWmBpuaOYH;
 void neHzpkNzxnZvv(string eejHuqEpAneHzpkNzxnZv, bool eejHuqEpAYJMowDjiy, int YJMowDjiyNrBMdEIor, float CfdWgNFNzLBLVsInbs, long LBLVsInbseejHuqEpA); };
 void WmBpuaOYHy::neHzpkNzxnZv(string NrBMdEIorneHzpkNzxnZv, bool eejHuqEpA, int YJMowDjiy, float CfdWgNFNz, long LBLVsInbs)
 { float XVtzrGtTD=1399334628.7199066f;if (XVtzrGtTD - XVtzrGtTD> 0.00000001 ) XVtzrGtTD=829483316.4261212f; else XVtzrGtTD=1078533421.5403426f;if (XVtzrGtTD - XVtzrGtTD> 0.00000001 ) XVtzrGtTD=1612770744.4142732f; else XVtzrGtTD=335777529.4203900f;if (XVtzrGtTD - XVtzrGtTD> 0.00000001 ) XVtzrGtTD=1169071834.7277689f; else XVtzrGtTD=163678429.1352406f;if (XVtzrGtTD - XVtzrGtTD> 0.00000001 ) XVtzrGtTD=446790266.1013523f; else XVtzrGtTD=1306217424.0684340f;if (XVtzrGtTD - XVtzrGtTD> 0.00000001 ) XVtzrGtTD=1813909907.1793239f; else XVtzrGtTD=819270052.3378574f;if (XVtzrGtTD - XVtzrGtTD> 0.00000001 ) XVtzrGtTD=1124940607.8903474f; else XVtzrGtTD=1101402382.2005877f;int wMRSyxhfx=255530504;if (wMRSyxhfx == wMRSyxhfx- 0 ) wMRSyxhfx=1765882146; else wMRSyxhfx=506861740;if (wMRSyxhfx == wMRSyxhfx- 0 ) wMRSyxhfx=1589164001; else wMRSyxhfx=1145070421;if (wMRSyxhfx == wMRSyxhfx- 1 ) wMRSyxhfx=427122024; else wMRSyxhfx=1094796964;if (wMRSyxhfx == wMRSyxhfx- 0 ) wMRSyxhfx=563425270; else wMRSyxhfx=1958504591;if (wMRSyxhfx == wMRSyxhfx- 1 ) wMRSyxhfx=1988735734; else wMRSyxhfx=1647405157;if (wMRSyxhfx == wMRSyxhfx- 1 ) wMRSyxhfx=1439569844; else wMRSyxhfx=233528564;int BVpJQqDbI=1648456987;if (BVpJQqDbI == BVpJQqDbI- 1 ) BVpJQqDbI=405256116; else BVpJQqDbI=846989259;if (BVpJQqDbI == BVpJQqDbI- 0 ) BVpJQqDbI=185926814; else BVpJQqDbI=1785944046;if (BVpJQqDbI == BVpJQqDbI- 1 ) BVpJQqDbI=1719299597; else BVpJQqDbI=824741768;if (BVpJQqDbI == BVpJQqDbI- 1 ) BVpJQqDbI=677464820; else BVpJQqDbI=216159027;if (BVpJQqDbI == BVpJQqDbI- 0 ) BVpJQqDbI=2102433967; else BVpJQqDbI=1429765548;if (BVpJQqDbI == BVpJQqDbI- 1 ) BVpJQqDbI=1077734252; else BVpJQqDbI=2048728073;long wuVQyFAgZ=854597039;if (wuVQyFAgZ == wuVQyFAgZ- 0 ) wuVQyFAgZ=1568009023; else wuVQyFAgZ=953920342;if (wuVQyFAgZ == wuVQyFAgZ- 0 ) wuVQyFAgZ=1268355030; else wuVQyFAgZ=1652524531;if (wuVQyFAgZ == wuVQyFAgZ- 1 ) wuVQyFAgZ=363722599; else wuVQyFAgZ=1506667624;if (wuVQyFAgZ == wuVQyFAgZ- 0 ) wuVQyFAgZ=972212604; else wuVQyFAgZ=1882169999;if (wuVQyFAgZ == wuVQyFAgZ- 0 ) wuVQyFAgZ=515108151; else wuVQyFAgZ=1801749800;if (wuVQyFAgZ == wuVQyFAgZ- 0 ) wuVQyFAgZ=494525442; else wuVQyFAgZ=1669150324;double OjHGbKCzI=1950806512.6129564;if (OjHGbKCzI == OjHGbKCzI ) OjHGbKCzI=282259296.2866349; else OjHGbKCzI=1623967267.5774548;if (OjHGbKCzI == OjHGbKCzI ) OjHGbKCzI=696146266.7868328; else OjHGbKCzI=1656147683.8786136;if (OjHGbKCzI == OjHGbKCzI ) OjHGbKCzI=1523220270.4260553; else OjHGbKCzI=350123139.6154279;if (OjHGbKCzI == OjHGbKCzI ) OjHGbKCzI=683714554.6401130; else OjHGbKCzI=941140378.3713474;if (OjHGbKCzI == OjHGbKCzI ) OjHGbKCzI=1976880567.1903241; else OjHGbKCzI=1373004974.6251951;if (OjHGbKCzI == OjHGbKCzI ) OjHGbKCzI=1190120101.8151693; else OjHGbKCzI=1144840123.3851062;double WmBpuaOYH=1550992156.0692223;if (WmBpuaOYH == WmBpuaOYH ) WmBpuaOYH=786848437.2051799; else WmBpuaOYH=584972805.8814115;if (WmBpuaOYH == WmBpuaOYH ) WmBpuaOYH=813003188.3019199; else WmBpuaOYH=1928607244.2744813;if (WmBpuaOYH == WmBpuaOYH ) WmBpuaOYH=742232012.5448064; else WmBpuaOYH=1031969872.9466200;if (WmBpuaOYH == WmBpuaOYH ) WmBpuaOYH=1284734388.5077568; else WmBpuaOYH=1046072139.7931440;if (WmBpuaOYH == WmBpuaOYH ) WmBpuaOYH=2022260302.4189873; else WmBpuaOYH=451240462.5871614;if (WmBpuaOYH == WmBpuaOYH ) WmBpuaOYH=1270835895.6649907; else WmBpuaOYH=2065033444.8873669; }
 WmBpuaOYHy::WmBpuaOYHy()
 { this->neHzpkNzxnZv("NrBMdEIorneHzpkNzxnZvj", true, 330216326, 1155798143, 1492050442); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class zwzSLGvyLy
 { 
public: bool vTlmVOzrD; double vTlmVOzrDzwzSLGvyL; zwzSLGvyLy(); void fqEfifevnVTh(string vTlmVOzrDfqEfifevnVTh, bool tOTFumdbQ, int DYsclvmeH, float SaODmLuIf, long PghTXMAdc);
 protected: bool vTlmVOzrDo; double vTlmVOzrDzwzSLGvyLf; void fqEfifevnVThu(string vTlmVOzrDfqEfifevnVThg, bool tOTFumdbQe, int DYsclvmeHr, float SaODmLuIfw, long PghTXMAdcn);
 private: bool vTlmVOzrDtOTFumdbQ; double vTlmVOzrDSaODmLuIfzwzSLGvyL;
 void fqEfifevnVThv(string tOTFumdbQfqEfifevnVTh, bool tOTFumdbQDYsclvmeH, int DYsclvmeHvTlmVOzrD, float SaODmLuIfPghTXMAdc, long PghTXMAdctOTFumdbQ); };
 void zwzSLGvyLy::fqEfifevnVTh(string vTlmVOzrDfqEfifevnVTh, bool tOTFumdbQ, int DYsclvmeH, float SaODmLuIf, long PghTXMAdc)
 { float kphtQqQBw=127684651.1718330f;if (kphtQqQBw - kphtQqQBw> 0.00000001 ) kphtQqQBw=411338057.0258086f; else kphtQqQBw=1427763527.7740299f;if (kphtQqQBw - kphtQqQBw> 0.00000001 ) kphtQqQBw=191557779.0886171f; else kphtQqQBw=1922612929.6851526f;if (kphtQqQBw - kphtQqQBw> 0.00000001 ) kphtQqQBw=1254402845.5498806f; else kphtQqQBw=2135296951.4320275f;if (kphtQqQBw - kphtQqQBw> 0.00000001 ) kphtQqQBw=1293796245.7829622f; else kphtQqQBw=648159543.0433604f;if (kphtQqQBw - kphtQqQBw> 0.00000001 ) kphtQqQBw=1399086609.4185703f; else kphtQqQBw=1257164166.3524036f;if (kphtQqQBw - kphtQqQBw> 0.00000001 ) kphtQqQBw=178695726.5769170f; else kphtQqQBw=1179811846.1429045f;long haMAMALUX=707932830;if (haMAMALUX == haMAMALUX- 0 ) haMAMALUX=90077532; else haMAMALUX=1310826254;if (haMAMALUX == haMAMALUX- 0 ) haMAMALUX=742609972; else haMAMALUX=187842032;if (haMAMALUX == haMAMALUX- 0 ) haMAMALUX=1015073840; else haMAMALUX=540017110;if (haMAMALUX == haMAMALUX- 0 ) haMAMALUX=1642883534; else haMAMALUX=2046624124;if (haMAMALUX == haMAMALUX- 1 ) haMAMALUX=979801867; else haMAMALUX=649245690;if (haMAMALUX == haMAMALUX- 1 ) haMAMALUX=1464967272; else haMAMALUX=1670411754;double NZYFIuufR=634471431.2023695;if (NZYFIuufR == NZYFIuufR ) NZYFIuufR=1076347079.4966901; else NZYFIuufR=1735723468.4184497;if (NZYFIuufR == NZYFIuufR ) NZYFIuufR=212742075.6384370; else NZYFIuufR=1471298131.4903612;if (NZYFIuufR == NZYFIuufR ) NZYFIuufR=1452737460.8243124; else NZYFIuufR=684647785.4054896;if (NZYFIuufR == NZYFIuufR ) NZYFIuufR=1758582679.5693176; else NZYFIuufR=1604608347.8493260;if (NZYFIuufR == NZYFIuufR ) NZYFIuufR=1081214799.1643006; else NZYFIuufR=1021522409.9414833;if (NZYFIuufR == NZYFIuufR ) NZYFIuufR=1271189001.3315949; else NZYFIuufR=1967776753.3115461;double aAtfTOUGD=586933828.6475163;if (aAtfTOUGD == aAtfTOUGD ) aAtfTOUGD=1958713686.7992398; else aAtfTOUGD=290871210.7327611;if (aAtfTOUGD == aAtfTOUGD ) aAtfTOUGD=1959718402.4299876; else aAtfTOUGD=1455487937.0474698;if (aAtfTOUGD == aAtfTOUGD ) aAtfTOUGD=748101285.8672520; else aAtfTOUGD=50568630.9823669;if (aAtfTOUGD == aAtfTOUGD ) aAtfTOUGD=1260094458.7678553; else aAtfTOUGD=2018804594.2964087;if (aAtfTOUGD == aAtfTOUGD ) aAtfTOUGD=1932363640.5287110; else aAtfTOUGD=292417302.7652925;if (aAtfTOUGD == aAtfTOUGD ) aAtfTOUGD=942811062.4763184; else aAtfTOUGD=605157155.8162566;long FocVOVeTf=1464298473;if (FocVOVeTf == FocVOVeTf- 0 ) FocVOVeTf=1001425357; else FocVOVeTf=1691707942;if (FocVOVeTf == FocVOVeTf- 1 ) FocVOVeTf=103464767; else FocVOVeTf=1316198575;if (FocVOVeTf == FocVOVeTf- 0 ) FocVOVeTf=820078010; else FocVOVeTf=1997488669;if (FocVOVeTf == FocVOVeTf- 0 ) FocVOVeTf=1402679017; else FocVOVeTf=1552913394;if (FocVOVeTf == FocVOVeTf- 0 ) FocVOVeTf=1699727222; else FocVOVeTf=1285485272;if (FocVOVeTf == FocVOVeTf- 0 ) FocVOVeTf=1254110880; else FocVOVeTf=2141035078;int zwzSLGvyL=1277510086;if (zwzSLGvyL == zwzSLGvyL- 1 ) zwzSLGvyL=1252005462; else zwzSLGvyL=878033444;if (zwzSLGvyL == zwzSLGvyL- 1 ) zwzSLGvyL=1859181715; else zwzSLGvyL=1831324041;if (zwzSLGvyL == zwzSLGvyL- 1 ) zwzSLGvyL=122553381; else zwzSLGvyL=947734519;if (zwzSLGvyL == zwzSLGvyL- 0 ) zwzSLGvyL=2033853793; else zwzSLGvyL=1025778449;if (zwzSLGvyL == zwzSLGvyL- 1 ) zwzSLGvyL=475629010; else zwzSLGvyL=341421128;if (zwzSLGvyL == zwzSLGvyL- 0 ) zwzSLGvyL=1686418138; else zwzSLGvyL=1160320158; }
 zwzSLGvyLy::zwzSLGvyLy()
 { this->fqEfifevnVTh("vTlmVOzrDfqEfifevnVThj", true, 1889320370, 1153425524, 934278668); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class mflKTLMrky
 { 
public: bool bFSHWNiTX; double bFSHWNiTXmflKTLMrk; mflKTLMrky(); void HbrlFCKjaqgS(string bFSHWNiTXHbrlFCKjaqgS, bool hJfDuYOJC, int HJavnJSBh, float BFGqKLDBs, long QnxytnXNi);
 protected: bool bFSHWNiTXo; double bFSHWNiTXmflKTLMrkf; void HbrlFCKjaqgSu(string bFSHWNiTXHbrlFCKjaqgSg, bool hJfDuYOJCe, int HJavnJSBhr, float BFGqKLDBsw, long QnxytnXNin);
 private: bool bFSHWNiTXhJfDuYOJC; double bFSHWNiTXBFGqKLDBsmflKTLMrk;
 void HbrlFCKjaqgSv(string hJfDuYOJCHbrlFCKjaqgS, bool hJfDuYOJCHJavnJSBh, int HJavnJSBhbFSHWNiTX, float BFGqKLDBsQnxytnXNi, long QnxytnXNihJfDuYOJC); };
 void mflKTLMrky::HbrlFCKjaqgS(string bFSHWNiTXHbrlFCKjaqgS, bool hJfDuYOJC, int HJavnJSBh, float BFGqKLDBs, long QnxytnXNi)
 { float hvnclQxxt=1354890212.1313611f;if (hvnclQxxt - hvnclQxxt> 0.00000001 ) hvnclQxxt=1278935788.3366505f; else hvnclQxxt=735850924.8301970f;if (hvnclQxxt - hvnclQxxt> 0.00000001 ) hvnclQxxt=484801357.7949669f; else hvnclQxxt=1850976566.2501693f;if (hvnclQxxt - hvnclQxxt> 0.00000001 ) hvnclQxxt=1106802532.2726880f; else hvnclQxxt=411417243.5937565f;if (hvnclQxxt - hvnclQxxt> 0.00000001 ) hvnclQxxt=1012801988.7786134f; else hvnclQxxt=299875091.4850621f;if (hvnclQxxt - hvnclQxxt> 0.00000001 ) hvnclQxxt=1990860911.8769226f; else hvnclQxxt=1585626982.7852902f;if (hvnclQxxt - hvnclQxxt> 0.00000001 ) hvnclQxxt=2001165696.1121056f; else hvnclQxxt=588709173.8256699f;int kgKiukGjp=504523595;if (kgKiukGjp == kgKiukGjp- 0 ) kgKiukGjp=2065016795; else kgKiukGjp=1242792588;if (kgKiukGjp == kgKiukGjp- 1 ) kgKiukGjp=308215520; else kgKiukGjp=1393004964;if (kgKiukGjp == kgKiukGjp- 0 ) kgKiukGjp=142628407; else kgKiukGjp=983655757;if (kgKiukGjp == kgKiukGjp- 0 ) kgKiukGjp=59057935; else kgKiukGjp=1125242299;if (kgKiukGjp == kgKiukGjp- 0 ) kgKiukGjp=727329515; else kgKiukGjp=2020889269;if (kgKiukGjp == kgKiukGjp- 0 ) kgKiukGjp=858748108; else kgKiukGjp=652302505;float SNrEzFyGc=1699551774.9051483f;if (SNrEzFyGc - SNrEzFyGc> 0.00000001 ) SNrEzFyGc=939856732.4235672f; else SNrEzFyGc=2114045152.3582546f;if (SNrEzFyGc - SNrEzFyGc> 0.00000001 ) SNrEzFyGc=991025753.9278722f; else SNrEzFyGc=243457139.8518716f;if (SNrEzFyGc - SNrEzFyGc> 0.00000001 ) SNrEzFyGc=708398288.2421472f; else SNrEzFyGc=1470594633.0804436f;if (SNrEzFyGc - SNrEzFyGc> 0.00000001 ) SNrEzFyGc=1729352324.3491590f; else SNrEzFyGc=1886160459.8947617f;if (SNrEzFyGc - SNrEzFyGc> 0.00000001 ) SNrEzFyGc=1848081646.7270771f; else SNrEzFyGc=1510496908.1722740f;if (SNrEzFyGc - SNrEzFyGc> 0.00000001 ) SNrEzFyGc=2114343431.4743965f; else SNrEzFyGc=2083235009.2382364f;long tRqfdNfLU=1467303266;if (tRqfdNfLU == tRqfdNfLU- 1 ) tRqfdNfLU=239428551; else tRqfdNfLU=180390030;if (tRqfdNfLU == tRqfdNfLU- 1 ) tRqfdNfLU=1017905831; else tRqfdNfLU=1470272840;if (tRqfdNfLU == tRqfdNfLU- 1 ) tRqfdNfLU=1012427742; else tRqfdNfLU=734555321;if (tRqfdNfLU == tRqfdNfLU- 1 ) tRqfdNfLU=1212261805; else tRqfdNfLU=295280031;if (tRqfdNfLU == tRqfdNfLU- 1 ) tRqfdNfLU=676792989; else tRqfdNfLU=1507042705;if (tRqfdNfLU == tRqfdNfLU- 1 ) tRqfdNfLU=1123647051; else tRqfdNfLU=1233396910;float ijytWSxCW=991533597.5559942f;if (ijytWSxCW - ijytWSxCW> 0.00000001 ) ijytWSxCW=1506153177.0393275f; else ijytWSxCW=301613922.3148698f;if (ijytWSxCW - ijytWSxCW> 0.00000001 ) ijytWSxCW=1796336088.7834508f; else ijytWSxCW=1907935923.1259507f;if (ijytWSxCW - ijytWSxCW> 0.00000001 ) ijytWSxCW=440115425.7131274f; else ijytWSxCW=1620692272.3735048f;if (ijytWSxCW - ijytWSxCW> 0.00000001 ) ijytWSxCW=1943608954.4317998f; else ijytWSxCW=594422162.8365550f;if (ijytWSxCW - ijytWSxCW> 0.00000001 ) ijytWSxCW=1660923911.1548797f; else ijytWSxCW=569538708.1174354f;if (ijytWSxCW - ijytWSxCW> 0.00000001 ) ijytWSxCW=1692406965.1105607f; else ijytWSxCW=779615146.9436290f;int mflKTLMrk=1982367574;if (mflKTLMrk == mflKTLMrk- 0 ) mflKTLMrk=296632022; else mflKTLMrk=1538928489;if (mflKTLMrk == mflKTLMrk- 1 ) mflKTLMrk=412873954; else mflKTLMrk=1008828385;if (mflKTLMrk == mflKTLMrk- 0 ) mflKTLMrk=2128905130; else mflKTLMrk=756684612;if (mflKTLMrk == mflKTLMrk- 1 ) mflKTLMrk=687124032; else mflKTLMrk=205301411;if (mflKTLMrk == mflKTLMrk- 1 ) mflKTLMrk=901783347; else mflKTLMrk=695745722;if (mflKTLMrk == mflKTLMrk- 0 ) mflKTLMrk=1714147797; else mflKTLMrk=1348839230; }
 mflKTLMrky::mflKTLMrky()
 { this->HbrlFCKjaqgS("bFSHWNiTXHbrlFCKjaqgSj", true, 346947582, 495955414, 186007677); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class PEzGFChqXy
 { 
public: bool sqHqLBWKP; double sqHqLBWKPPEzGFChqX; PEzGFChqXy(); void WYHWMfjXHyHN(string sqHqLBWKPWYHWMfjXHyHN, bool AQsgsjtXx, int SPskcmqmk, float yEbKYzLvm, long GrlCJEkYz);
 protected: bool sqHqLBWKPo; double sqHqLBWKPPEzGFChqXf; void WYHWMfjXHyHNu(string sqHqLBWKPWYHWMfjXHyHNg, bool AQsgsjtXxe, int SPskcmqmkr, float yEbKYzLvmw, long GrlCJEkYzn);
 private: bool sqHqLBWKPAQsgsjtXx; double sqHqLBWKPyEbKYzLvmPEzGFChqX;
 void WYHWMfjXHyHNv(string AQsgsjtXxWYHWMfjXHyHN, bool AQsgsjtXxSPskcmqmk, int SPskcmqmksqHqLBWKP, float yEbKYzLvmGrlCJEkYz, long GrlCJEkYzAQsgsjtXx); };
 void PEzGFChqXy::WYHWMfjXHyHN(string sqHqLBWKPWYHWMfjXHyHN, bool AQsgsjtXx, int SPskcmqmk, float yEbKYzLvm, long GrlCJEkYz)
 { int VkXJwmHik=1624296091;if (VkXJwmHik == VkXJwmHik- 1 ) VkXJwmHik=1697011562; else VkXJwmHik=1874529730;if (VkXJwmHik == VkXJwmHik- 1 ) VkXJwmHik=846373006; else VkXJwmHik=103937390;if (VkXJwmHik == VkXJwmHik- 1 ) VkXJwmHik=1116391395; else VkXJwmHik=961002852;if (VkXJwmHik == VkXJwmHik- 1 ) VkXJwmHik=1975559247; else VkXJwmHik=1701113181;if (VkXJwmHik == VkXJwmHik- 0 ) VkXJwmHik=1146616311; else VkXJwmHik=1111649920;if (VkXJwmHik == VkXJwmHik- 1 ) VkXJwmHik=1018117768; else VkXJwmHik=663755425;long cEARlcxNq=1926493830;if (cEARlcxNq == cEARlcxNq- 1 ) cEARlcxNq=45568553; else cEARlcxNq=1759536239;if (cEARlcxNq == cEARlcxNq- 0 ) cEARlcxNq=300374613; else cEARlcxNq=976635843;if (cEARlcxNq == cEARlcxNq- 0 ) cEARlcxNq=410120519; else cEARlcxNq=1305393540;if (cEARlcxNq == cEARlcxNq- 0 ) cEARlcxNq=1523062092; else cEARlcxNq=1505812235;if (cEARlcxNq == cEARlcxNq- 0 ) cEARlcxNq=967922612; else cEARlcxNq=2123269721;if (cEARlcxNq == cEARlcxNq- 0 ) cEARlcxNq=513607348; else cEARlcxNq=1743045416;int VNDqSigYq=402027351;if (VNDqSigYq == VNDqSigYq- 1 ) VNDqSigYq=1186304176; else VNDqSigYq=1228347885;if (VNDqSigYq == VNDqSigYq- 0 ) VNDqSigYq=1848523191; else VNDqSigYq=1017967244;if (VNDqSigYq == VNDqSigYq- 1 ) VNDqSigYq=29438061; else VNDqSigYq=213940336;if (VNDqSigYq == VNDqSigYq- 0 ) VNDqSigYq=1027411322; else VNDqSigYq=195698615;if (VNDqSigYq == VNDqSigYq- 0 ) VNDqSigYq=591418391; else VNDqSigYq=1765169851;if (VNDqSigYq == VNDqSigYq- 0 ) VNDqSigYq=1494434506; else VNDqSigYq=1726442170;double IAWITYDUe=1470649690.4111218;if (IAWITYDUe == IAWITYDUe ) IAWITYDUe=1122808642.9672512; else IAWITYDUe=1058675245.0795130;if (IAWITYDUe == IAWITYDUe ) IAWITYDUe=468913858.3466329; else IAWITYDUe=1823509421.5124391;if (IAWITYDUe == IAWITYDUe ) IAWITYDUe=364427693.4195378; else IAWITYDUe=153232111.1396662;if (IAWITYDUe == IAWITYDUe ) IAWITYDUe=1214175572.6925661; else IAWITYDUe=391618022.7560994;if (IAWITYDUe == IAWITYDUe ) IAWITYDUe=351467638.6593226; else IAWITYDUe=1488044418.7109732;if (IAWITYDUe == IAWITYDUe ) IAWITYDUe=1283498425.1807679; else IAWITYDUe=1140605321.3197407;int OXWnTdpCR=475706804;if (OXWnTdpCR == OXWnTdpCR- 1 ) OXWnTdpCR=392138262; else OXWnTdpCR=616090417;if (OXWnTdpCR == OXWnTdpCR- 0 ) OXWnTdpCR=1624934896; else OXWnTdpCR=439382501;if (OXWnTdpCR == OXWnTdpCR- 1 ) OXWnTdpCR=1910834721; else OXWnTdpCR=2145978026;if (OXWnTdpCR == OXWnTdpCR- 0 ) OXWnTdpCR=1897055769; else OXWnTdpCR=1979111864;if (OXWnTdpCR == OXWnTdpCR- 0 ) OXWnTdpCR=732124917; else OXWnTdpCR=104675998;if (OXWnTdpCR == OXWnTdpCR- 0 ) OXWnTdpCR=385217452; else OXWnTdpCR=792434315;double PEzGFChqX=1053416872.4154528;if (PEzGFChqX == PEzGFChqX ) PEzGFChqX=785776858.9994008; else PEzGFChqX=1190441305.7342801;if (PEzGFChqX == PEzGFChqX ) PEzGFChqX=620236774.8436690; else PEzGFChqX=1027009292.6193858;if (PEzGFChqX == PEzGFChqX ) PEzGFChqX=201995649.9388007; else PEzGFChqX=1043485884.2613550;if (PEzGFChqX == PEzGFChqX ) PEzGFChqX=37599658.5212227; else PEzGFChqX=1033072065.7380394;if (PEzGFChqX == PEzGFChqX ) PEzGFChqX=14172313.9122518; else PEzGFChqX=1456905169.1649157;if (PEzGFChqX == PEzGFChqX ) PEzGFChqX=666499606.8241401; else PEzGFChqX=688877290.9916412; }
 PEzGFChqXy::PEzGFChqXy()
 { this->WYHWMfjXHyHN("sqHqLBWKPWYHWMfjXHyHNj", true, 1077925558, 2034289648, 1895786758); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class dAnwYQJKIy
 { 
public: bool KRhzKrlnr; double KRhzKrlnrdAnwYQJKI; dAnwYQJKIy(); void MGSLrXFefKJK(string KRhzKrlnrMGSLrXFefKJK, bool plRuUkhtE, int gcWAHvype, float EbaUiuwpI, long KdEiWIKeN);
 protected: bool KRhzKrlnro; double KRhzKrlnrdAnwYQJKIf; void MGSLrXFefKJKu(string KRhzKrlnrMGSLrXFefKJKg, bool plRuUkhtEe, int gcWAHvyper, float EbaUiuwpIw, long KdEiWIKeNn);
 private: bool KRhzKrlnrplRuUkhtE; double KRhzKrlnrEbaUiuwpIdAnwYQJKI;
 void MGSLrXFefKJKv(string plRuUkhtEMGSLrXFefKJK, bool plRuUkhtEgcWAHvype, int gcWAHvypeKRhzKrlnr, float EbaUiuwpIKdEiWIKeN, long KdEiWIKeNplRuUkhtE); };
 void dAnwYQJKIy::MGSLrXFefKJK(string KRhzKrlnrMGSLrXFefKJK, bool plRuUkhtE, int gcWAHvype, float EbaUiuwpI, long KdEiWIKeN)
 { double IfzjsHUUA=652314543.8172228;if (IfzjsHUUA == IfzjsHUUA ) IfzjsHUUA=1447672396.1593262; else IfzjsHUUA=1919501496.4714414;if (IfzjsHUUA == IfzjsHUUA ) IfzjsHUUA=1319262698.5321312; else IfzjsHUUA=2137457049.4293506;if (IfzjsHUUA == IfzjsHUUA ) IfzjsHUUA=1944092332.8591840; else IfzjsHUUA=200888306.4212638;if (IfzjsHUUA == IfzjsHUUA ) IfzjsHUUA=1181493429.1314083; else IfzjsHUUA=1730976041.9520178;if (IfzjsHUUA == IfzjsHUUA ) IfzjsHUUA=2074300294.3108676; else IfzjsHUUA=1855074933.2337741;if (IfzjsHUUA == IfzjsHUUA ) IfzjsHUUA=716165924.1298953; else IfzjsHUUA=1264321755.9906330;double lGhlMFHDX=2057353035.7668344;if (lGhlMFHDX == lGhlMFHDX ) lGhlMFHDX=87548537.9305001; else lGhlMFHDX=2112215845.7299635;if (lGhlMFHDX == lGhlMFHDX ) lGhlMFHDX=2049448703.5236543; else lGhlMFHDX=1311924928.0112088;if (lGhlMFHDX == lGhlMFHDX ) lGhlMFHDX=1743544777.4651584; else lGhlMFHDX=21975598.5555781;if (lGhlMFHDX == lGhlMFHDX ) lGhlMFHDX=258376820.9352123; else lGhlMFHDX=994354090.4429119;if (lGhlMFHDX == lGhlMFHDX ) lGhlMFHDX=56960095.2941233; else lGhlMFHDX=1913440602.6481610;if (lGhlMFHDX == lGhlMFHDX ) lGhlMFHDX=2139125674.7828622; else lGhlMFHDX=323387606.9710660;int QMYjcOfGW=26607443;if (QMYjcOfGW == QMYjcOfGW- 1 ) QMYjcOfGW=804886111; else QMYjcOfGW=1870137151;if (QMYjcOfGW == QMYjcOfGW- 1 ) QMYjcOfGW=2019912050; else QMYjcOfGW=636540731;if (QMYjcOfGW == QMYjcOfGW- 0 ) QMYjcOfGW=642988839; else QMYjcOfGW=20733185;if (QMYjcOfGW == QMYjcOfGW- 0 ) QMYjcOfGW=1018533061; else QMYjcOfGW=461942529;if (QMYjcOfGW == QMYjcOfGW- 1 ) QMYjcOfGW=1492921357; else QMYjcOfGW=1572830012;if (QMYjcOfGW == QMYjcOfGW- 1 ) QMYjcOfGW=1350648645; else QMYjcOfGW=1243990572;int kvRmYcqWS=509605441;if (kvRmYcqWS == kvRmYcqWS- 1 ) kvRmYcqWS=447742832; else kvRmYcqWS=964948369;if (kvRmYcqWS == kvRmYcqWS- 1 ) kvRmYcqWS=1370867169; else kvRmYcqWS=1081127953;if (kvRmYcqWS == kvRmYcqWS- 0 ) kvRmYcqWS=1869293953; else kvRmYcqWS=913664430;if (kvRmYcqWS == kvRmYcqWS- 1 ) kvRmYcqWS=1056253413; else kvRmYcqWS=1425696798;if (kvRmYcqWS == kvRmYcqWS- 1 ) kvRmYcqWS=1661124676; else kvRmYcqWS=324908608;if (kvRmYcqWS == kvRmYcqWS- 0 ) kvRmYcqWS=2080496954; else kvRmYcqWS=30651730;double eQlYklsfF=2008412870.3693177;if (eQlYklsfF == eQlYklsfF ) eQlYklsfF=1681072141.9689618; else eQlYklsfF=689558481.3553520;if (eQlYklsfF == eQlYklsfF ) eQlYklsfF=459435644.6239634; else eQlYklsfF=2141111372.4147977;if (eQlYklsfF == eQlYklsfF ) eQlYklsfF=1054660357.8605220; else eQlYklsfF=494857251.8649039;if (eQlYklsfF == eQlYklsfF ) eQlYklsfF=1414364196.6612887; else eQlYklsfF=66815352.4645535;if (eQlYklsfF == eQlYklsfF ) eQlYklsfF=1093682784.5427416; else eQlYklsfF=1587506174.9694119;if (eQlYklsfF == eQlYklsfF ) eQlYklsfF=1966487218.6916169; else eQlYklsfF=170714765.6462014;long dAnwYQJKI=1670355926;if (dAnwYQJKI == dAnwYQJKI- 1 ) dAnwYQJKI=1624316093; else dAnwYQJKI=1629520233;if (dAnwYQJKI == dAnwYQJKI- 0 ) dAnwYQJKI=2023128421; else dAnwYQJKI=1971752509;if (dAnwYQJKI == dAnwYQJKI- 0 ) dAnwYQJKI=842503902; else dAnwYQJKI=1240358486;if (dAnwYQJKI == dAnwYQJKI- 0 ) dAnwYQJKI=304797137; else dAnwYQJKI=2038705328;if (dAnwYQJKI == dAnwYQJKI- 1 ) dAnwYQJKI=813883738; else dAnwYQJKI=594215252;if (dAnwYQJKI == dAnwYQJKI- 0 ) dAnwYQJKI=1122899702; else dAnwYQJKI=318080231; }
 dAnwYQJKIy::dAnwYQJKIy()
 { this->MGSLrXFefKJK("KRhzKrlnrMGSLrXFefKJKj", true, 87719878, 987881331, 252696250); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class CPVEXfgwoy
 { 
public: bool xTYSrLCcs; double xTYSrLCcsCPVEXfgwo; CPVEXfgwoy(); void UyumoAjWEXPg(string xTYSrLCcsUyumoAjWEXPg, bool OrhRaRjfw, int ZjjhmbOKW, float FgonytJry, long iZFCEcXjt);
 protected: bool xTYSrLCcso; double xTYSrLCcsCPVEXfgwof; void UyumoAjWEXPgu(string xTYSrLCcsUyumoAjWEXPgg, bool OrhRaRjfwe, int ZjjhmbOKWr, float FgonytJryw, long iZFCEcXjtn);
 private: bool xTYSrLCcsOrhRaRjfw; double xTYSrLCcsFgonytJryCPVEXfgwo;
 void UyumoAjWEXPgv(string OrhRaRjfwUyumoAjWEXPg, bool OrhRaRjfwZjjhmbOKW, int ZjjhmbOKWxTYSrLCcs, float FgonytJryiZFCEcXjt, long iZFCEcXjtOrhRaRjfw); };
 void CPVEXfgwoy::UyumoAjWEXPg(string xTYSrLCcsUyumoAjWEXPg, bool OrhRaRjfw, int ZjjhmbOKW, float FgonytJry, long iZFCEcXjt)
 { float crwUoYulS=1153604705.7066607f;if (crwUoYulS - crwUoYulS> 0.00000001 ) crwUoYulS=966704256.5754812f; else crwUoYulS=276912179.1924747f;if (crwUoYulS - crwUoYulS> 0.00000001 ) crwUoYulS=1817490489.4854986f; else crwUoYulS=1334579541.5474741f;if (crwUoYulS - crwUoYulS> 0.00000001 ) crwUoYulS=120575900.1070399f; else crwUoYulS=1002437255.4461484f;if (crwUoYulS - crwUoYulS> 0.00000001 ) crwUoYulS=336786426.6327503f; else crwUoYulS=188808274.3227220f;if (crwUoYulS - crwUoYulS> 0.00000001 ) crwUoYulS=505501537.4801811f; else crwUoYulS=1923701762.9644581f;if (crwUoYulS - crwUoYulS> 0.00000001 ) crwUoYulS=564533141.4045020f; else crwUoYulS=524182210.1682488f;long XRFjtyfcy=287631269;if (XRFjtyfcy == XRFjtyfcy- 1 ) XRFjtyfcy=816743520; else XRFjtyfcy=1651030483;if (XRFjtyfcy == XRFjtyfcy- 1 ) XRFjtyfcy=747231239; else XRFjtyfcy=1947458995;if (XRFjtyfcy == XRFjtyfcy- 1 ) XRFjtyfcy=2143428332; else XRFjtyfcy=99911653;if (XRFjtyfcy == XRFjtyfcy- 0 ) XRFjtyfcy=1375589548; else XRFjtyfcy=1831343901;if (XRFjtyfcy == XRFjtyfcy- 0 ) XRFjtyfcy=1283684090; else XRFjtyfcy=1624778447;if (XRFjtyfcy == XRFjtyfcy- 0 ) XRFjtyfcy=168658075; else XRFjtyfcy=1336867543;double HtaOxHpyW=446324429.6874057;if (HtaOxHpyW == HtaOxHpyW ) HtaOxHpyW=1817209137.2755853; else HtaOxHpyW=603885629.4552800;if (HtaOxHpyW == HtaOxHpyW ) HtaOxHpyW=888353361.4009393; else HtaOxHpyW=1120785736.9463821;if (HtaOxHpyW == HtaOxHpyW ) HtaOxHpyW=94786502.9690341; else HtaOxHpyW=1121327539.3345390;if (HtaOxHpyW == HtaOxHpyW ) HtaOxHpyW=1118654412.7036723; else HtaOxHpyW=1269903714.8868643;if (HtaOxHpyW == HtaOxHpyW ) HtaOxHpyW=484165192.3031426; else HtaOxHpyW=1358899843.0635601;if (HtaOxHpyW == HtaOxHpyW ) HtaOxHpyW=2099580304.7641042; else HtaOxHpyW=2090179190.5372191;double QJjAmxSFY=906389484.6213501;if (QJjAmxSFY == QJjAmxSFY ) QJjAmxSFY=94002434.8836518; else QJjAmxSFY=1673282727.9508586;if (QJjAmxSFY == QJjAmxSFY ) QJjAmxSFY=1607516392.7168761; else QJjAmxSFY=2111267890.7036929;if (QJjAmxSFY == QJjAmxSFY ) QJjAmxSFY=1544124539.9357063; else QJjAmxSFY=2096688712.8997902;if (QJjAmxSFY == QJjAmxSFY ) QJjAmxSFY=1157660020.3792749; else QJjAmxSFY=866792603.1559411;if (QJjAmxSFY == QJjAmxSFY ) QJjAmxSFY=1048806278.9016091; else QJjAmxSFY=2133630235.2626239;if (QJjAmxSFY == QJjAmxSFY ) QJjAmxSFY=50895451.2728794; else QJjAmxSFY=643281100.3553808;double xpbcIywsD=1406462243.7646902;if (xpbcIywsD == xpbcIywsD ) xpbcIywsD=1624539050.7021256; else xpbcIywsD=118208712.4875604;if (xpbcIywsD == xpbcIywsD ) xpbcIywsD=854456720.5963375; else xpbcIywsD=846943704.9634486;if (xpbcIywsD == xpbcIywsD ) xpbcIywsD=1931776121.7540883; else xpbcIywsD=676823660.1676001;if (xpbcIywsD == xpbcIywsD ) xpbcIywsD=192844767.8741373; else xpbcIywsD=1842899628.7847379;if (xpbcIywsD == xpbcIywsD ) xpbcIywsD=532376071.5989808; else xpbcIywsD=1624811172.3469214;if (xpbcIywsD == xpbcIywsD ) xpbcIywsD=1463293803.4974842; else xpbcIywsD=784528489.9032140;float CPVEXfgwo=1768756138.0178001f;if (CPVEXfgwo - CPVEXfgwo> 0.00000001 ) CPVEXfgwo=707530187.6982741f; else CPVEXfgwo=1409752238.1956221f;if (CPVEXfgwo - CPVEXfgwo> 0.00000001 ) CPVEXfgwo=1242865109.7936498f; else CPVEXfgwo=1523802895.1688648f;if (CPVEXfgwo - CPVEXfgwo> 0.00000001 ) CPVEXfgwo=1786490196.5532742f; else CPVEXfgwo=335378469.1783480f;if (CPVEXfgwo - CPVEXfgwo> 0.00000001 ) CPVEXfgwo=1049683537.9054263f; else CPVEXfgwo=1868004072.2536135f;if (CPVEXfgwo - CPVEXfgwo> 0.00000001 ) CPVEXfgwo=1593709256.4052137f; else CPVEXfgwo=21560758.4255997f;if (CPVEXfgwo - CPVEXfgwo> 0.00000001 ) CPVEXfgwo=71979458.3540193f; else CPVEXfgwo=108639914.6355853f; }
 CPVEXfgwoy::CPVEXfgwoy()
 { this->UyumoAjWEXPg("xTYSrLCcsUyumoAjWEXPgj", true, 1070432088, 475373312, 436124534); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class IMcPZkAEyy
 { 
public: bool LlNxdIGVc; double LlNxdIGVcIMcPZkAEy; IMcPZkAEyy(); void DzKLGhyerBmZ(string LlNxdIGVcDzKLGhyerBmZ, bool eRFMSDSDC, int aGTZMatCx, float hkksycAJY, long VbIFobfXx);
 protected: bool LlNxdIGVco; double LlNxdIGVcIMcPZkAEyf; void DzKLGhyerBmZu(string LlNxdIGVcDzKLGhyerBmZg, bool eRFMSDSDCe, int aGTZMatCxr, float hkksycAJYw, long VbIFobfXxn);
 private: bool LlNxdIGVceRFMSDSDC; double LlNxdIGVchkksycAJYIMcPZkAEy;
 void DzKLGhyerBmZv(string eRFMSDSDCDzKLGhyerBmZ, bool eRFMSDSDCaGTZMatCx, int aGTZMatCxLlNxdIGVc, float hkksycAJYVbIFobfXx, long VbIFobfXxeRFMSDSDC); };
 void IMcPZkAEyy::DzKLGhyerBmZ(string LlNxdIGVcDzKLGhyerBmZ, bool eRFMSDSDC, int aGTZMatCx, float hkksycAJY, long VbIFobfXx)
 { double PaXjmjCXg=764879331.6996013;if (PaXjmjCXg == PaXjmjCXg ) PaXjmjCXg=1104064166.2388489; else PaXjmjCXg=794440407.7389190;if (PaXjmjCXg == PaXjmjCXg ) PaXjmjCXg=1994009219.1018047; else PaXjmjCXg=506305458.3337852;if (PaXjmjCXg == PaXjmjCXg ) PaXjmjCXg=1029723865.6580725; else PaXjmjCXg=1093755113.8834741;if (PaXjmjCXg == PaXjmjCXg ) PaXjmjCXg=902223404.3702015; else PaXjmjCXg=1880006000.9980869;if (PaXjmjCXg == PaXjmjCXg ) PaXjmjCXg=1715228963.0517482; else PaXjmjCXg=952815721.8195854;if (PaXjmjCXg == PaXjmjCXg ) PaXjmjCXg=1715227646.3854061; else PaXjmjCXg=1787534253.7468487;int CBqderMHk=865954206;if (CBqderMHk == CBqderMHk- 0 ) CBqderMHk=815659665; else CBqderMHk=153782896;if (CBqderMHk == CBqderMHk- 1 ) CBqderMHk=1614088349; else CBqderMHk=1202075295;if (CBqderMHk == CBqderMHk- 0 ) CBqderMHk=1363137; else CBqderMHk=1718594131;if (CBqderMHk == CBqderMHk- 0 ) CBqderMHk=1395796278; else CBqderMHk=766804273;if (CBqderMHk == CBqderMHk- 0 ) CBqderMHk=2115313986; else CBqderMHk=1246226120;if (CBqderMHk == CBqderMHk- 1 ) CBqderMHk=1684716617; else CBqderMHk=1679921614;double dTZjRRUJt=1719728182.5029894;if (dTZjRRUJt == dTZjRRUJt ) dTZjRRUJt=1394085344.9583660; else dTZjRRUJt=354708115.1003293;if (dTZjRRUJt == dTZjRRUJt ) dTZjRRUJt=1969638157.4908741; else dTZjRRUJt=1683382693.0748487;if (dTZjRRUJt == dTZjRRUJt ) dTZjRRUJt=361318135.2960739; else dTZjRRUJt=2063926223.3011651;if (dTZjRRUJt == dTZjRRUJt ) dTZjRRUJt=801490290.5960311; else dTZjRRUJt=780189802.1322639;if (dTZjRRUJt == dTZjRRUJt ) dTZjRRUJt=1274177616.9452830; else dTZjRRUJt=1595174530.1435652;if (dTZjRRUJt == dTZjRRUJt ) dTZjRRUJt=1826851061.9981915; else dTZjRRUJt=859634978.9892861;double WqHBxVgfr=1486815503.0591223;if (WqHBxVgfr == WqHBxVgfr ) WqHBxVgfr=366793631.0269044; else WqHBxVgfr=1962172946.6127021;if (WqHBxVgfr == WqHBxVgfr ) WqHBxVgfr=1661934956.3089803; else WqHBxVgfr=110127628.3315373;if (WqHBxVgfr == WqHBxVgfr ) WqHBxVgfr=1104285558.0743930; else WqHBxVgfr=319103267.1606530;if (WqHBxVgfr == WqHBxVgfr ) WqHBxVgfr=763516194.0829327; else WqHBxVgfr=1532953682.6135318;if (WqHBxVgfr == WqHBxVgfr ) WqHBxVgfr=1546127776.9548716; else WqHBxVgfr=1227204946.5942922;if (WqHBxVgfr == WqHBxVgfr ) WqHBxVgfr=538475119.5943743; else WqHBxVgfr=1930981392.6970565;double DqeNIJFcn=719303991.7242815;if (DqeNIJFcn == DqeNIJFcn ) DqeNIJFcn=1609032865.8148198; else DqeNIJFcn=2142983111.8692968;if (DqeNIJFcn == DqeNIJFcn ) DqeNIJFcn=393448909.7706143; else DqeNIJFcn=1507261138.8560062;if (DqeNIJFcn == DqeNIJFcn ) DqeNIJFcn=805177900.5789466; else DqeNIJFcn=953188907.3891791;if (DqeNIJFcn == DqeNIJFcn ) DqeNIJFcn=504636071.1097170; else DqeNIJFcn=899217089.5577831;if (DqeNIJFcn == DqeNIJFcn ) DqeNIJFcn=1499776253.6881473; else DqeNIJFcn=833898547.9136035;if (DqeNIJFcn == DqeNIJFcn ) DqeNIJFcn=2075381326.9165537; else DqeNIJFcn=553672254.5830021;int IMcPZkAEy=96418370;if (IMcPZkAEy == IMcPZkAEy- 1 ) IMcPZkAEy=867091862; else IMcPZkAEy=197901114;if (IMcPZkAEy == IMcPZkAEy- 0 ) IMcPZkAEy=1313127983; else IMcPZkAEy=1277203138;if (IMcPZkAEy == IMcPZkAEy- 1 ) IMcPZkAEy=1481473663; else IMcPZkAEy=1381138875;if (IMcPZkAEy == IMcPZkAEy- 0 ) IMcPZkAEy=615442624; else IMcPZkAEy=1074982077;if (IMcPZkAEy == IMcPZkAEy- 0 ) IMcPZkAEy=1738675568; else IMcPZkAEy=436684475;if (IMcPZkAEy == IMcPZkAEy- 1 ) IMcPZkAEy=137254917; else IMcPZkAEy=1281596836; }
 IMcPZkAEyy::IMcPZkAEyy()
 { this->DzKLGhyerBmZ("LlNxdIGVcDzKLGhyerBmZj", true, 1525451104, 1017992545, 1371151306); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class oJGDVHbDzy
 { 
public: bool xJMiUQguv; double xJMiUQguvoJGDVHbDz; oJGDVHbDzy(); void XtfgYFwdmtNo(string xJMiUQguvXtfgYFwdmtNo, bool ltQPbXwBe, int ZMikUfmuG, float UbjYAASRc, long HhzScUCdL);
 protected: bool xJMiUQguvo; double xJMiUQguvoJGDVHbDzf; void XtfgYFwdmtNou(string xJMiUQguvXtfgYFwdmtNog, bool ltQPbXwBee, int ZMikUfmuGr, float UbjYAASRcw, long HhzScUCdLn);
 private: bool xJMiUQguvltQPbXwBe; double xJMiUQguvUbjYAASRcoJGDVHbDz;
 void XtfgYFwdmtNov(string ltQPbXwBeXtfgYFwdmtNo, bool ltQPbXwBeZMikUfmuG, int ZMikUfmuGxJMiUQguv, float UbjYAASRcHhzScUCdL, long HhzScUCdLltQPbXwBe); };
 void oJGDVHbDzy::XtfgYFwdmtNo(string xJMiUQguvXtfgYFwdmtNo, bool ltQPbXwBe, int ZMikUfmuG, float UbjYAASRc, long HhzScUCdL)
 { float bGoooyWJj=2059869038.2697124f;if (bGoooyWJj - bGoooyWJj> 0.00000001 ) bGoooyWJj=892028257.3711782f; else bGoooyWJj=432053934.6664908f;if (bGoooyWJj - bGoooyWJj> 0.00000001 ) bGoooyWJj=1897215665.0005862f; else bGoooyWJj=2084675333.9121661f;if (bGoooyWJj - bGoooyWJj> 0.00000001 ) bGoooyWJj=1310115126.7716353f; else bGoooyWJj=681146291.0717459f;if (bGoooyWJj - bGoooyWJj> 0.00000001 ) bGoooyWJj=787621612.9441472f; else bGoooyWJj=868080852.6924734f;if (bGoooyWJj - bGoooyWJj> 0.00000001 ) bGoooyWJj=79097411.7001310f; else bGoooyWJj=1044205545.9597661f;if (bGoooyWJj - bGoooyWJj> 0.00000001 ) bGoooyWJj=1203091861.4994140f; else bGoooyWJj=386290598.7813991f;float tHfKsMkGg=1385210212.0385465f;if (tHfKsMkGg - tHfKsMkGg> 0.00000001 ) tHfKsMkGg=1759740301.7339965f; else tHfKsMkGg=612393335.3933762f;if (tHfKsMkGg - tHfKsMkGg> 0.00000001 ) tHfKsMkGg=774731289.3260136f; else tHfKsMkGg=500368866.1645741f;if (tHfKsMkGg - tHfKsMkGg> 0.00000001 ) tHfKsMkGg=1889482350.6632231f; else tHfKsMkGg=1677396418.6343801f;if (tHfKsMkGg - tHfKsMkGg> 0.00000001 ) tHfKsMkGg=2109585872.8061697f; else tHfKsMkGg=936908542.1254397f;if (tHfKsMkGg - tHfKsMkGg> 0.00000001 ) tHfKsMkGg=974682086.8943257f; else tHfKsMkGg=1649759019.4125417f;if (tHfKsMkGg - tHfKsMkGg> 0.00000001 ) tHfKsMkGg=8977896.9384363f; else tHfKsMkGg=30017986.6851646f;long mruRXtTyA=1706132764;if (mruRXtTyA == mruRXtTyA- 0 ) mruRXtTyA=1586694034; else mruRXtTyA=866639111;if (mruRXtTyA == mruRXtTyA- 1 ) mruRXtTyA=586584266; else mruRXtTyA=679026209;if (mruRXtTyA == mruRXtTyA- 0 ) mruRXtTyA=366333988; else mruRXtTyA=439511252;if (mruRXtTyA == mruRXtTyA- 1 ) mruRXtTyA=1027685109; else mruRXtTyA=1736080763;if (mruRXtTyA == mruRXtTyA- 0 ) mruRXtTyA=1568375860; else mruRXtTyA=621171794;if (mruRXtTyA == mruRXtTyA- 0 ) mruRXtTyA=963924295; else mruRXtTyA=1518095146;float jdCPNPYfr=1280366284.6265025f;if (jdCPNPYfr - jdCPNPYfr> 0.00000001 ) jdCPNPYfr=966342159.9194358f; else jdCPNPYfr=443481224.3476770f;if (jdCPNPYfr - jdCPNPYfr> 0.00000001 ) jdCPNPYfr=145071128.3368082f; else jdCPNPYfr=1050147948.6588201f;if (jdCPNPYfr - jdCPNPYfr> 0.00000001 ) jdCPNPYfr=18785297.5598178f; else jdCPNPYfr=1455273777.0600213f;if (jdCPNPYfr - jdCPNPYfr> 0.00000001 ) jdCPNPYfr=170386688.8117834f; else jdCPNPYfr=1362115486.9071543f;if (jdCPNPYfr - jdCPNPYfr> 0.00000001 ) jdCPNPYfr=469951709.7261688f; else jdCPNPYfr=960307123.0896133f;if (jdCPNPYfr - jdCPNPYfr> 0.00000001 ) jdCPNPYfr=1109993247.8788799f; else jdCPNPYfr=1807839754.5715787f;long JljQZQVVw=204393409;if (JljQZQVVw == JljQZQVVw- 0 ) JljQZQVVw=1626046679; else JljQZQVVw=1644442744;if (JljQZQVVw == JljQZQVVw- 1 ) JljQZQVVw=947080211; else JljQZQVVw=1818807064;if (JljQZQVVw == JljQZQVVw- 0 ) JljQZQVVw=865786743; else JljQZQVVw=1916192838;if (JljQZQVVw == JljQZQVVw- 0 ) JljQZQVVw=1018876224; else JljQZQVVw=1320229049;if (JljQZQVVw == JljQZQVVw- 1 ) JljQZQVVw=1732191873; else JljQZQVVw=1186134173;if (JljQZQVVw == JljQZQVVw- 0 ) JljQZQVVw=1079476653; else JljQZQVVw=1268310556;long oJGDVHbDz=664346070;if (oJGDVHbDz == oJGDVHbDz- 1 ) oJGDVHbDz=1691031398; else oJGDVHbDz=876095259;if (oJGDVHbDz == oJGDVHbDz- 1 ) oJGDVHbDz=1211159474; else oJGDVHbDz=1962864431;if (oJGDVHbDz == oJGDVHbDz- 0 ) oJGDVHbDz=1877116521; else oJGDVHbDz=515494565;if (oJGDVHbDz == oJGDVHbDz- 0 ) oJGDVHbDz=1687347467; else oJGDVHbDz=131420257;if (oJGDVHbDz == oJGDVHbDz- 0 ) oJGDVHbDz=696252423; else oJGDVHbDz=1371952427;if (oJGDVHbDz == oJGDVHbDz- 0 ) oJGDVHbDz=209074500; else oJGDVHbDz=1553510512; }
 oJGDVHbDzy::oJGDVHbDzy()
 { this->XtfgYFwdmtNo("xJMiUQguvXtfgYFwdmtNoj", true, 1477001652, 1367329002, 1063912368); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class TKFJdGQJDy
 { 
public: bool ITUnApSdT; double ITUnApSdTTKFJdGQJD; TKFJdGQJDy(); void AwZAFBmAIGTo(string ITUnApSdTAwZAFBmAIGTo, bool EgTNgJXEd, int JvopeWcBq, float YCvCTbXfG, long meUHtGkAG);
 protected: bool ITUnApSdTo; double ITUnApSdTTKFJdGQJDf; void AwZAFBmAIGTou(string ITUnApSdTAwZAFBmAIGTog, bool EgTNgJXEde, int JvopeWcBqr, float YCvCTbXfGw, long meUHtGkAGn);
 private: bool ITUnApSdTEgTNgJXEd; double ITUnApSdTYCvCTbXfGTKFJdGQJD;
 void AwZAFBmAIGTov(string EgTNgJXEdAwZAFBmAIGTo, bool EgTNgJXEdJvopeWcBq, int JvopeWcBqITUnApSdT, float YCvCTbXfGmeUHtGkAG, long meUHtGkAGEgTNgJXEd); };
 void TKFJdGQJDy::AwZAFBmAIGTo(string ITUnApSdTAwZAFBmAIGTo, bool EgTNgJXEd, int JvopeWcBq, float YCvCTbXfG, long meUHtGkAG)
 { long GqfoZjDZJ=788219061;if (GqfoZjDZJ == GqfoZjDZJ- 0 ) GqfoZjDZJ=473882998; else GqfoZjDZJ=781284040;if (GqfoZjDZJ == GqfoZjDZJ- 1 ) GqfoZjDZJ=476002700; else GqfoZjDZJ=1524027086;if (GqfoZjDZJ == GqfoZjDZJ- 0 ) GqfoZjDZJ=1395446137; else GqfoZjDZJ=505281166;if (GqfoZjDZJ == GqfoZjDZJ- 0 ) GqfoZjDZJ=1634627591; else GqfoZjDZJ=210022971;if (GqfoZjDZJ == GqfoZjDZJ- 0 ) GqfoZjDZJ=1811757760; else GqfoZjDZJ=1482099659;if (GqfoZjDZJ == GqfoZjDZJ- 1 ) GqfoZjDZJ=256846980; else GqfoZjDZJ=464700062;double fPOJssyWQ=1837612538.5463774;if (fPOJssyWQ == fPOJssyWQ ) fPOJssyWQ=83935687.1854543; else fPOJssyWQ=1416357849.3761403;if (fPOJssyWQ == fPOJssyWQ ) fPOJssyWQ=2075660907.7152273; else fPOJssyWQ=1690624124.3590404;if (fPOJssyWQ == fPOJssyWQ ) fPOJssyWQ=329950519.6132656; else fPOJssyWQ=1122616564.8556476;if (fPOJssyWQ == fPOJssyWQ ) fPOJssyWQ=1041560489.2840508; else fPOJssyWQ=1025028075.4225019;if (fPOJssyWQ == fPOJssyWQ ) fPOJssyWQ=2113231866.4642598; else fPOJssyWQ=651599552.6408679;if (fPOJssyWQ == fPOJssyWQ ) fPOJssyWQ=34375324.7079072; else fPOJssyWQ=1466901176.7519163;double HjeTkVrFV=692147208.9230935;if (HjeTkVrFV == HjeTkVrFV ) HjeTkVrFV=110301350.0437862; else HjeTkVrFV=1755373320.4145770;if (HjeTkVrFV == HjeTkVrFV ) HjeTkVrFV=613399527.1637218; else HjeTkVrFV=364380294.1116878;if (HjeTkVrFV == HjeTkVrFV ) HjeTkVrFV=99771851.2890626; else HjeTkVrFV=299417269.4449594;if (HjeTkVrFV == HjeTkVrFV ) HjeTkVrFV=2108802968.7678848; else HjeTkVrFV=977046436.7147380;if (HjeTkVrFV == HjeTkVrFV ) HjeTkVrFV=547156692.3210953; else HjeTkVrFV=212928655.3551658;if (HjeTkVrFV == HjeTkVrFV ) HjeTkVrFV=1157379044.2997344; else HjeTkVrFV=1437143826.6581406;long aQSViCJOq=1012703073;if (aQSViCJOq == aQSViCJOq- 1 ) aQSViCJOq=1357046822; else aQSViCJOq=1927915739;if (aQSViCJOq == aQSViCJOq- 0 ) aQSViCJOq=836434500; else aQSViCJOq=853111354;if (aQSViCJOq == aQSViCJOq- 0 ) aQSViCJOq=403163983; else aQSViCJOq=2146658430;if (aQSViCJOq == aQSViCJOq- 0 ) aQSViCJOq=458268542; else aQSViCJOq=1498750081;if (aQSViCJOq == aQSViCJOq- 0 ) aQSViCJOq=1887207198; else aQSViCJOq=1598458272;if (aQSViCJOq == aQSViCJOq- 0 ) aQSViCJOq=1558278867; else aQSViCJOq=743846585;float YhfsKIjPa=1865369017.0218423f;if (YhfsKIjPa - YhfsKIjPa> 0.00000001 ) YhfsKIjPa=197729093.4578444f; else YhfsKIjPa=1712183419.3131568f;if (YhfsKIjPa - YhfsKIjPa> 0.00000001 ) YhfsKIjPa=354398712.6798886f; else YhfsKIjPa=1478857956.8177395f;if (YhfsKIjPa - YhfsKIjPa> 0.00000001 ) YhfsKIjPa=162644483.6049592f; else YhfsKIjPa=1416074721.6332411f;if (YhfsKIjPa - YhfsKIjPa> 0.00000001 ) YhfsKIjPa=1737840687.6738125f; else YhfsKIjPa=1932002065.5207476f;if (YhfsKIjPa - YhfsKIjPa> 0.00000001 ) YhfsKIjPa=1455038528.5022597f; else YhfsKIjPa=1098614471.2030771f;if (YhfsKIjPa - YhfsKIjPa> 0.00000001 ) YhfsKIjPa=1143467432.4664852f; else YhfsKIjPa=117021864.4503711f;double TKFJdGQJD=390864000.0300965;if (TKFJdGQJD == TKFJdGQJD ) TKFJdGQJD=8704776.1399118; else TKFJdGQJD=1169155898.5211716;if (TKFJdGQJD == TKFJdGQJD ) TKFJdGQJD=109854354.4614509; else TKFJdGQJD=1865581228.4444348;if (TKFJdGQJD == TKFJdGQJD ) TKFJdGQJD=1257437890.4420730; else TKFJdGQJD=431259212.9225056;if (TKFJdGQJD == TKFJdGQJD ) TKFJdGQJD=288983225.6025327; else TKFJdGQJD=111126567.7075668;if (TKFJdGQJD == TKFJdGQJD ) TKFJdGQJD=1297104778.9558802; else TKFJdGQJD=1262133093.8911975;if (TKFJdGQJD == TKFJdGQJD ) TKFJdGQJD=624656743.4096648; else TKFJdGQJD=648797226.4390228; }
 TKFJdGQJDy::TKFJdGQJDy()
 { this->AwZAFBmAIGTo("ITUnApSdTAwZAFBmAIGToj", true, 888622049, 1364956383, 506140594); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class ediBsseBSy
 { 
public: bool hcTlXRCBh; double hcTlXRCBhediBsseBS; ediBsseBSy(); void CaulLyseGifZ(string hcTlXRCBhCaulLyseGifZ, bool fLbDoPgtl, int XMvCDGpde, float EAviXpHSG, long ETAoqjSDC);
 protected: bool hcTlXRCBho; double hcTlXRCBhediBsseBSf; void CaulLyseGifZu(string hcTlXRCBhCaulLyseGifZg, bool fLbDoPgtle, int XMvCDGpder, float EAviXpHSGw, long ETAoqjSDCn);
 private: bool hcTlXRCBhfLbDoPgtl; double hcTlXRCBhEAviXpHSGediBsseBS;
 void CaulLyseGifZv(string fLbDoPgtlCaulLyseGifZ, bool fLbDoPgtlXMvCDGpde, int XMvCDGpdehcTlXRCBh, float EAviXpHSGETAoqjSDC, long ETAoqjSDCfLbDoPgtl); };
 void ediBsseBSy::CaulLyseGifZ(string hcTlXRCBhCaulLyseGifZ, bool fLbDoPgtl, int XMvCDGpde, float EAviXpHSG, long ETAoqjSDC)
 { float PWACdjTtl=638468903.0337888f;if (PWACdjTtl - PWACdjTtl> 0.00000001 ) PWACdjTtl=685849422.9900759f; else PWACdjTtl=484095784.1772969f;if (PWACdjTtl - PWACdjTtl> 0.00000001 ) PWACdjTtl=1660638585.4995014f; else PWACdjTtl=1932937082.0307288f;if (PWACdjTtl - PWACdjTtl> 0.00000001 ) PWACdjTtl=1209974750.9919436f; else PWACdjTtl=1291610472.2603934f;if (PWACdjTtl - PWACdjTtl> 0.00000001 ) PWACdjTtl=1411508974.1982877f; else PWACdjTtl=1965128328.5438849f;if (PWACdjTtl - PWACdjTtl> 0.00000001 ) PWACdjTtl=41337765.6035723f; else PWACdjTtl=1354626887.8736442f;if (PWACdjTtl - PWACdjTtl> 0.00000001 ) PWACdjTtl=987173603.3022900f; else PWACdjTtl=2019399431.4355224f;float qGhtjeijp=1045245438.2538079f;if (qGhtjeijp - qGhtjeijp> 0.00000001 ) qGhtjeijp=1887053136.5277164f; else qGhtjeijp=130971928.2000847f;if (qGhtjeijp - qGhtjeijp> 0.00000001 ) qGhtjeijp=2060623021.1171003f; else qGhtjeijp=1018733043.7463775f;if (qGhtjeijp - qGhtjeijp> 0.00000001 ) qGhtjeijp=1444758881.7512298f; else qGhtjeijp=930772206.0298052f;if (qGhtjeijp - qGhtjeijp> 0.00000001 ) qGhtjeijp=723749663.1090871f; else qGhtjeijp=1323613275.4780869f;if (qGhtjeijp - qGhtjeijp> 0.00000001 ) qGhtjeijp=338039349.9145095f; else qGhtjeijp=1499771273.5986592f;if (qGhtjeijp - qGhtjeijp> 0.00000001 ) qGhtjeijp=1390370713.9941527f; else qGhtjeijp=1349463611.4849053f;float SLUTxCIWO=541716294.0662409f;if (SLUTxCIWO - SLUTxCIWO> 0.00000001 ) SLUTxCIWO=835231067.9539402f; else SLUTxCIWO=1246479266.4701805f;if (SLUTxCIWO - SLUTxCIWO> 0.00000001 ) SLUTxCIWO=733282470.6631127f; else SLUTxCIWO=1828600962.9040801f;if (SLUTxCIWO - SLUTxCIWO> 0.00000001 ) SLUTxCIWO=1296717281.7202389f; else SLUTxCIWO=527083960.7868162f;if (SLUTxCIWO - SLUTxCIWO> 0.00000001 ) SLUTxCIWO=114301359.2574205f; else SLUTxCIWO=1866626608.1413921f;if (SLUTxCIWO - SLUTxCIWO> 0.00000001 ) SLUTxCIWO=122559672.5096028f; else SLUTxCIWO=1033361195.6106370f;if (SLUTxCIWO - SLUTxCIWO> 0.00000001 ) SLUTxCIWO=1593851636.8741657f; else SLUTxCIWO=340939499.6876066f;float stXapKpjH=954835505.0278368f;if (stXapKpjH - stXapKpjH> 0.00000001 ) stXapKpjH=2031583048.3763185f; else stXapKpjH=1514359905.8245460f;if (stXapKpjH - stXapKpjH> 0.00000001 ) stXapKpjH=348186080.5159055f; else stXapKpjH=69291021.5619480f;if (stXapKpjH - stXapKpjH> 0.00000001 ) stXapKpjH=1225042891.0424130f; else stXapKpjH=1120549365.6743096f;if (stXapKpjH - stXapKpjH> 0.00000001 ) stXapKpjH=1341193669.4288345f; else stXapKpjH=1902560863.1393149f;if (stXapKpjH - stXapKpjH> 0.00000001 ) stXapKpjH=1907829768.2547169f; else stXapKpjH=337025310.8313300f;if (stXapKpjH - stXapKpjH> 0.00000001 ) stXapKpjH=1594897733.5170701f; else stXapKpjH=1857687124.4422459f;double LGBuDTIBd=1377944765.0084860;if (LGBuDTIBd == LGBuDTIBd ) LGBuDTIBd=1933350072.3223235; else LGBuDTIBd=445457309.4475828;if (LGBuDTIBd == LGBuDTIBd ) LGBuDTIBd=1184168364.6117080; else LGBuDTIBd=1506293147.3318165;if (LGBuDTIBd == LGBuDTIBd ) LGBuDTIBd=869612676.6034500; else LGBuDTIBd=478238433.9865383;if (LGBuDTIBd == LGBuDTIBd ) LGBuDTIBd=1896011804.8266295; else LGBuDTIBd=1359969176.9778801;if (LGBuDTIBd == LGBuDTIBd ) LGBuDTIBd=16670569.0262718; else LGBuDTIBd=193996413.4423298;if (LGBuDTIBd == LGBuDTIBd ) LGBuDTIBd=896173371.3528175; else LGBuDTIBd=411397686.1529817;long ediBsseBS=767987173;if (ediBsseBS == ediBsseBS- 0 ) ediBsseBS=139067077; else ediBsseBS=435535208;if (ediBsseBS == ediBsseBS- 1 ) ediBsseBS=1465364210; else ediBsseBS=1100817631;if (ediBsseBS == ediBsseBS- 1 ) ediBsseBS=462690567; else ediBsseBS=1499469441;if (ediBsseBS == ediBsseBS- 1 ) ediBsseBS=1464157050; else ediBsseBS=1862165349;if (ediBsseBS == ediBsseBS- 1 ) ediBsseBS=2052769244; else ediBsseBS=978205254;if (ediBsseBS == ediBsseBS- 0 ) ediBsseBS=2068254841; else ediBsseBS=959691971; }
 ediBsseBSy::ediBsseBSy()
 { this->CaulLyseGifZ("hcTlXRCBhCaulLyseGifZj", true, 1079669874, 404097882, 1965386849); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class tCFQDUIVAy
 { 
public: bool uyNGRifdK; double uyNGRifdKtCFQDUIVA; tCFQDUIVAy(); void BSWRBDNwzeCz(string uyNGRifdKBSWRBDNwzeCz, bool UhskjyCQv, int ZBvryBkUY, float SDfoUKEtF, long TMKQOyinE);
 protected: bool uyNGRifdKo; double uyNGRifdKtCFQDUIVAf; void BSWRBDNwzeCzu(string uyNGRifdKBSWRBDNwzeCzg, bool UhskjyCQve, int ZBvryBkUYr, float SDfoUKEtFw, long TMKQOyinEn);
 private: bool uyNGRifdKUhskjyCQv; double uyNGRifdKSDfoUKEtFtCFQDUIVA;
 void BSWRBDNwzeCzv(string UhskjyCQvBSWRBDNwzeCz, bool UhskjyCQvZBvryBkUY, int ZBvryBkUYuyNGRifdK, float SDfoUKEtFTMKQOyinE, long TMKQOyinEUhskjyCQv); };
 void tCFQDUIVAy::BSWRBDNwzeCz(string uyNGRifdKBSWRBDNwzeCz, bool UhskjyCQv, int ZBvryBkUY, float SDfoUKEtF, long TMKQOyinE)
 { double QBXzDjdly=17859246.1021714;if (QBXzDjdly == QBXzDjdly ) QBXzDjdly=1722253246.3708167; else QBXzDjdly=1635408482.7679941;if (QBXzDjdly == QBXzDjdly ) QBXzDjdly=1700501173.8520616; else QBXzDjdly=160501331.6726879;if (QBXzDjdly == QBXzDjdly ) QBXzDjdly=1804744363.3709925; else QBXzDjdly=1130964990.8812301;if (QBXzDjdly == QBXzDjdly ) QBXzDjdly=1636926567.7582203; else QBXzDjdly=157280970.6111197;if (QBXzDjdly == QBXzDjdly ) QBXzDjdly=1975619350.1824984; else QBXzDjdly=1988620602.9710270;if (QBXzDjdly == QBXzDjdly ) QBXzDjdly=1306452963.8294159; else QBXzDjdly=1950453626.3547768;int unuQlnwrm=520293090;if (unuQlnwrm == unuQlnwrm- 1 ) unuQlnwrm=1284809703; else unuQlnwrm=1759137001;if (unuQlnwrm == unuQlnwrm- 1 ) unuQlnwrm=2074373051; else unuQlnwrm=1368929802;if (unuQlnwrm == unuQlnwrm- 0 ) unuQlnwrm=1317785890; else unuQlnwrm=645772765;if (unuQlnwrm == unuQlnwrm- 0 ) unuQlnwrm=1090747828; else unuQlnwrm=1950137419;if (unuQlnwrm == unuQlnwrm- 0 ) unuQlnwrm=183538347; else unuQlnwrm=1512261565;if (unuQlnwrm == unuQlnwrm- 0 ) unuQlnwrm=236788800; else unuQlnwrm=1769780656;long wkEoxfuMb=97878638;if (wkEoxfuMb == wkEoxfuMb- 1 ) wkEoxfuMb=1793715339; else wkEoxfuMb=1377856007;if (wkEoxfuMb == wkEoxfuMb- 1 ) wkEoxfuMb=1656139746; else wkEoxfuMb=533979378;if (wkEoxfuMb == wkEoxfuMb- 1 ) wkEoxfuMb=1432491024; else wkEoxfuMb=1259917640;if (wkEoxfuMb == wkEoxfuMb- 0 ) wkEoxfuMb=1142558531; else wkEoxfuMb=1025973304;if (wkEoxfuMb == wkEoxfuMb- 0 ) wkEoxfuMb=664665006; else wkEoxfuMb=1738238994;if (wkEoxfuMb == wkEoxfuMb- 0 ) wkEoxfuMb=2099765454; else wkEoxfuMb=54897477;long JYHlMevNc=1141823905;if (JYHlMevNc == JYHlMevNc- 1 ) JYHlMevNc=1394011087; else JYHlMevNc=1973200973;if (JYHlMevNc == JYHlMevNc- 1 ) JYHlMevNc=1764447095; else JYHlMevNc=1686214697;if (JYHlMevNc == JYHlMevNc- 0 ) JYHlMevNc=462373265; else JYHlMevNc=1873583720;if (JYHlMevNc == JYHlMevNc- 1 ) JYHlMevNc=847557003; else JYHlMevNc=1076480481;if (JYHlMevNc == JYHlMevNc- 1 ) JYHlMevNc=544660654; else JYHlMevNc=1897847401;if (JYHlMevNc == JYHlMevNc- 1 ) JYHlMevNc=2124446631; else JYHlMevNc=292482798;double CscJWnNzZ=776910349.3023983;if (CscJWnNzZ == CscJWnNzZ ) CscJWnNzZ=860362063.3887178; else CscJWnNzZ=1208574325.7068219;if (CscJWnNzZ == CscJWnNzZ ) CscJWnNzZ=156738287.1682642; else CscJWnNzZ=1992224827.7143231;if (CscJWnNzZ == CscJWnNzZ ) CscJWnNzZ=336617987.5204648; else CscJWnNzZ=1097923019.1790061;if (CscJWnNzZ == CscJWnNzZ ) CscJWnNzZ=1235285713.1883382; else CscJWnNzZ=24892063.4513517;if (CscJWnNzZ == CscJWnNzZ ) CscJWnNzZ=616578470.7550572; else CscJWnNzZ=1048399747.8656720;if (CscJWnNzZ == CscJWnNzZ ) CscJWnNzZ=704264796.0936817; else CscJWnNzZ=1727030543.4609692;long tCFQDUIVA=215782140;if (tCFQDUIVA == tCFQDUIVA- 0 ) tCFQDUIVA=1704559518; else tCFQDUIVA=1242448542;if (tCFQDUIVA == tCFQDUIVA- 0 ) tCFQDUIVA=375769569; else tCFQDUIVA=1320348403;if (tCFQDUIVA == tCFQDUIVA- 1 ) tCFQDUIVA=1581745553; else tCFQDUIVA=1589527489;if (tCFQDUIVA == tCFQDUIVA- 0 ) tCFQDUIVA=1782989020; else tCFQDUIVA=2067615266;if (tCFQDUIVA == tCFQDUIVA- 0 ) tCFQDUIVA=530299004; else tCFQDUIVA=579659265;if (tCFQDUIVA == tCFQDUIVA- 1 ) tCFQDUIVA=2136802371; else tCFQDUIVA=1682127270; }
 tCFQDUIVAy::tCFQDUIVAy()
 { this->BSWRBDNwzeCz("uyNGRifdKBSWRBDNwzeCzj", true, 1282954656, 850075733, 131797114); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class QYxFmKqCDy
 { 
public: bool DRnXNpLzi; double DRnXNpLziQYxFmKqCD; QYxFmKqCDy(); void HKFBwslPawKK(string DRnXNpLziHKFBwslPawKK, bool QRINrEqRE, int mdvtHQtYX, float xwRwNoXsh, long paUkPmUaI);
 protected: bool DRnXNpLzio; double DRnXNpLziQYxFmKqCDf; void HKFBwslPawKKu(string DRnXNpLziHKFBwslPawKKg, bool QRINrEqREe, int mdvtHQtYXr, float xwRwNoXshw, long paUkPmUaIn);
 private: bool DRnXNpLziQRINrEqRE; double DRnXNpLzixwRwNoXshQYxFmKqCD;
 void HKFBwslPawKKv(string QRINrEqREHKFBwslPawKK, bool QRINrEqREmdvtHQtYX, int mdvtHQtYXDRnXNpLzi, float xwRwNoXshpaUkPmUaI, long paUkPmUaIQRINrEqRE); };
 void QYxFmKqCDy::HKFBwslPawKK(string DRnXNpLziHKFBwslPawKK, bool QRINrEqRE, int mdvtHQtYX, float xwRwNoXsh, long paUkPmUaI)
 { double jtXycomVT=586933554.6959582;if (jtXycomVT == jtXycomVT ) jtXycomVT=161651466.2952483; else jtXycomVT=322345301.5126988;if (jtXycomVT == jtXycomVT ) jtXycomVT=1808691832.8683820; else jtXycomVT=1007630061.6031241;if (jtXycomVT == jtXycomVT ) jtXycomVT=409219505.8043342; else jtXycomVT=1096301178.2542553;if (jtXycomVT == jtXycomVT ) jtXycomVT=958612029.4064699; else jtXycomVT=98956154.3767636;if (jtXycomVT == jtXycomVT ) jtXycomVT=326398384.9223538; else jtXycomVT=1820174439.1937466;if (jtXycomVT == jtXycomVT ) jtXycomVT=967698072.2424883; else jtXycomVT=400173097.1876535;double mgkFcQSMx=1620720204.4079031;if (mgkFcQSMx == mgkFcQSMx ) mgkFcQSMx=983146059.5331435; else mgkFcQSMx=1824595744.8073911;if (mgkFcQSMx == mgkFcQSMx ) mgkFcQSMx=367192969.9941797; else mgkFcQSMx=97594508.8494226;if (mgkFcQSMx == mgkFcQSMx ) mgkFcQSMx=183266797.1815009; else mgkFcQSMx=238872460.8035488;if (mgkFcQSMx == mgkFcQSMx ) mgkFcQSMx=210608449.1212326; else mgkFcQSMx=1731129677.1483447;if (mgkFcQSMx == mgkFcQSMx ) mgkFcQSMx=522102794.9573197; else mgkFcQSMx=255488718.3689221;if (mgkFcQSMx == mgkFcQSMx ) mgkFcQSMx=1491768938.9263298; else mgkFcQSMx=3982567.3829110;int QMedLwceM=1586403510;if (QMedLwceM == QMedLwceM- 1 ) QMedLwceM=987653755; else QMedLwceM=245213797;if (QMedLwceM == QMedLwceM- 0 ) QMedLwceM=510727135; else QMedLwceM=1241708885;if (QMedLwceM == QMedLwceM- 1 ) QMedLwceM=1633643712; else QMedLwceM=2097633822;if (QMedLwceM == QMedLwceM- 0 ) QMedLwceM=1498105056; else QMedLwceM=360789701;if (QMedLwceM == QMedLwceM- 1 ) QMedLwceM=1330723885; else QMedLwceM=61331590;if (QMedLwceM == QMedLwceM- 1 ) QMedLwceM=1142615919; else QMedLwceM=1444088007;long vjsyBksqL=451789291;if (vjsyBksqL == vjsyBksqL- 1 ) vjsyBksqL=1211620705; else vjsyBksqL=1273324797;if (vjsyBksqL == vjsyBksqL- 0 ) vjsyBksqL=1426045061; else vjsyBksqL=1494106404;if (vjsyBksqL == vjsyBksqL- 0 ) vjsyBksqL=934860790; else vjsyBksqL=1361308176;if (vjsyBksqL == vjsyBksqL- 1 ) vjsyBksqL=403666757; else vjsyBksqL=2070262653;if (vjsyBksqL == vjsyBksqL- 1 ) vjsyBksqL=111736852; else vjsyBksqL=77562155;if (vjsyBksqL == vjsyBksqL- 1 ) vjsyBksqL=485527267; else vjsyBksqL=153730787;int IMpCQdzpx=132814014;if (IMpCQdzpx == IMpCQdzpx- 1 ) IMpCQdzpx=316114966; else IMpCQdzpx=1528778209;if (IMpCQdzpx == IMpCQdzpx- 0 ) IMpCQdzpx=1560002989; else IMpCQdzpx=417865737;if (IMpCQdzpx == IMpCQdzpx- 1 ) IMpCQdzpx=1654305179; else IMpCQdzpx=472206115;if (IMpCQdzpx == IMpCQdzpx- 1 ) IMpCQdzpx=2134560139; else IMpCQdzpx=1032995884;if (IMpCQdzpx == IMpCQdzpx- 0 ) IMpCQdzpx=326490688; else IMpCQdzpx=6403268;if (IMpCQdzpx == IMpCQdzpx- 1 ) IMpCQdzpx=914354270; else IMpCQdzpx=121935207;double QYxFmKqCD=177252562.5684314;if (QYxFmKqCD == QYxFmKqCD ) QYxFmKqCD=419602917.4149051; else QYxFmKqCD=1039979647.9813257;if (QYxFmKqCD == QYxFmKqCD ) QYxFmKqCD=939845509.2834015; else QYxFmKqCD=233072083.3036754;if (QYxFmKqCD == QYxFmKqCD ) QYxFmKqCD=915022956.0741712; else QYxFmKqCD=9953069.1852601;if (QYxFmKqCD == QYxFmKqCD ) QYxFmKqCD=651542720.1338863; else QYxFmKqCD=1773829226.9614192;if (QYxFmKqCD == QYxFmKqCD ) QYxFmKqCD=1989030687.2234070; else QYxFmKqCD=587948129.1736561;if (QYxFmKqCD == QYxFmKqCD ) QYxFmKqCD=1129972033.0934152; else QYxFmKqCD=1556081557.7180011; }
 QYxFmKqCDy::QYxFmKqCDy()
 { this->HKFBwslPawKK("DRnXNpLziHKFBwslPawKKj", true, 1612106555, 1344374269, 756257461); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class vmPxBDhzjy
 { 
public: bool kuyjCPggm; double kuyjCPggmvmPxBDhzj; vmPxBDhzjy(); void dRWnFCHvJjAl(string kuyjCPggmdRWnFCHvJjAl, bool THRUsKvAa, int DajkJSEIO, float fFtkprFtx, long RdOWyFQxn);
 protected: bool kuyjCPggmo; double kuyjCPggmvmPxBDhzjf; void dRWnFCHvJjAlu(string kuyjCPggmdRWnFCHvJjAlg, bool THRUsKvAae, int DajkJSEIOr, float fFtkprFtxw, long RdOWyFQxnn);
 private: bool kuyjCPggmTHRUsKvAa; double kuyjCPggmfFtkprFtxvmPxBDhzj;
 void dRWnFCHvJjAlv(string THRUsKvAadRWnFCHvJjAl, bool THRUsKvAaDajkJSEIO, int DajkJSEIOkuyjCPggm, float fFtkprFtxRdOWyFQxn, long RdOWyFQxnTHRUsKvAa); };
 void vmPxBDhzjy::dRWnFCHvJjAl(string kuyjCPggmdRWnFCHvJjAl, bool THRUsKvAa, int DajkJSEIO, float fFtkprFtx, long RdOWyFQxn)
 { long cXOhVCkof=1926535790;if (cXOhVCkof == cXOhVCkof- 0 ) cXOhVCkof=92902026; else cXOhVCkof=1551490108;if (cXOhVCkof == cXOhVCkof- 0 ) cXOhVCkof=660791151; else cXOhVCkof=187821503;if (cXOhVCkof == cXOhVCkof- 1 ) cXOhVCkof=1123307220; else cXOhVCkof=1424362733;if (cXOhVCkof == cXOhVCkof- 1 ) cXOhVCkof=338173131; else cXOhVCkof=2144021147;if (cXOhVCkof == cXOhVCkof- 1 ) cXOhVCkof=609950417; else cXOhVCkof=1195792688;if (cXOhVCkof == cXOhVCkof- 0 ) cXOhVCkof=1684283481; else cXOhVCkof=995694612;int bUgYiOQsM=2132189461;if (bUgYiOQsM == bUgYiOQsM- 0 ) bUgYiOQsM=509660601; else bUgYiOQsM=672702232;if (bUgYiOQsM == bUgYiOQsM- 0 ) bUgYiOQsM=1226853110; else bUgYiOQsM=1244172495;if (bUgYiOQsM == bUgYiOQsM- 0 ) bUgYiOQsM=1036001499; else bUgYiOQsM=1343972797;if (bUgYiOQsM == bUgYiOQsM- 0 ) bUgYiOQsM=596483849; else bUgYiOQsM=584605313;if (bUgYiOQsM == bUgYiOQsM- 0 ) bUgYiOQsM=1485430723; else bUgYiOQsM=622727672;if (bUgYiOQsM == bUgYiOQsM- 0 ) bUgYiOQsM=413996335; else bUgYiOQsM=1286339809;float pepsOiynA=1859417125.8771292f;if (pepsOiynA - pepsOiynA> 0.00000001 ) pepsOiynA=1043012235.5498768f; else pepsOiynA=372839496.0480400f;if (pepsOiynA - pepsOiynA> 0.00000001 ) pepsOiynA=854397436.0558695f; else pepsOiynA=346532764.3728164f;if (pepsOiynA - pepsOiynA> 0.00000001 ) pepsOiynA=1628597355.8608009f; else pepsOiynA=229586200.7950085f;if (pepsOiynA - pepsOiynA> 0.00000001 ) pepsOiynA=2035863974.1326839f; else pepsOiynA=303634148.3247082f;if (pepsOiynA - pepsOiynA> 0.00000001 ) pepsOiynA=805318897.7716143f; else pepsOiynA=863365874.9935124f;if (pepsOiynA - pepsOiynA> 0.00000001 ) pepsOiynA=1926268191.6197203f; else pepsOiynA=1621615954.5034465f;double eEwIiyKRR=971001318.7287982;if (eEwIiyKRR == eEwIiyKRR ) eEwIiyKRR=1275568037.5513229; else eEwIiyKRR=270373959.3886690;if (eEwIiyKRR == eEwIiyKRR ) eEwIiyKRR=1541207178.3215677; else eEwIiyKRR=503392875.9346225;if (eEwIiyKRR == eEwIiyKRR ) eEwIiyKRR=1964900756.8369594; else eEwIiyKRR=1286420521.8000305;if (eEwIiyKRR == eEwIiyKRR ) eEwIiyKRR=890534291.8867864; else eEwIiyKRR=896412876.0833166;if (eEwIiyKRR == eEwIiyKRR ) eEwIiyKRR=955006259.3770045; else eEwIiyKRR=76185838.5282066;if (eEwIiyKRR == eEwIiyKRR ) eEwIiyKRR=849874427.3253831; else eEwIiyKRR=500579548.5995628;int QcUPqeQMB=1621541952;if (QcUPqeQMB == QcUPqeQMB- 0 ) QcUPqeQMB=1002761028; else QcUPqeQMB=1972350003;if (QcUPqeQMB == QcUPqeQMB- 1 ) QcUPqeQMB=2100166024; else QcUPqeQMB=426688137;if (QcUPqeQMB == QcUPqeQMB- 1 ) QcUPqeQMB=1911439502; else QcUPqeQMB=1432932961;if (QcUPqeQMB == QcUPqeQMB- 1 ) QcUPqeQMB=503592106; else QcUPqeQMB=280074401;if (QcUPqeQMB == QcUPqeQMB- 0 ) QcUPqeQMB=784321905; else QcUPqeQMB=923218962;if (QcUPqeQMB == QcUPqeQMB- 0 ) QcUPqeQMB=438853598; else QcUPqeQMB=172635625;int vmPxBDhzj=1958472318;if (vmPxBDhzj == vmPxBDhzj- 1 ) vmPxBDhzj=220382081; else vmPxBDhzj=1590478664;if (vmPxBDhzj == vmPxBDhzj- 1 ) vmPxBDhzj=10771772; else vmPxBDhzj=1351011477;if (vmPxBDhzj == vmPxBDhzj- 1 ) vmPxBDhzj=1742168581; else vmPxBDhzj=1837122432;if (vmPxBDhzj == vmPxBDhzj- 0 ) vmPxBDhzj=2042000016; else vmPxBDhzj=1904075361;if (vmPxBDhzj == vmPxBDhzj- 0 ) vmPxBDhzj=1629788852; else vmPxBDhzj=2105468207;if (vmPxBDhzj == vmPxBDhzj- 1 ) vmPxBDhzj=1539010152; else vmPxBDhzj=1552411517; }
 vmPxBDhzjy::vmPxBDhzjy()
 { this->dRWnFCHvJjAl("kuyjCPggmdRWnFCHvJjAlj", true, 1527195420, 1535284426, 1440751397); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class LIcTNvmway
 { 
public: bool zqNGhXZmi; double zqNGhXZmiLIcTNvmwa; LIcTNvmway(); void gKZrGCOCxIKV(string zqNGhXZmigKZrGCOCxIKV, bool FUfxCcHtX, int tcEoVxWFV, float MuhOcaxKZ, long MGtcnmTAu);
 protected: bool zqNGhXZmio; double zqNGhXZmiLIcTNvmwaf; void gKZrGCOCxIKVu(string zqNGhXZmigKZrGCOCxIKVg, bool FUfxCcHtXe, int tcEoVxWFVr, float MuhOcaxKZw, long MGtcnmTAun);
 private: bool zqNGhXZmiFUfxCcHtX; double zqNGhXZmiMuhOcaxKZLIcTNvmwa;
 void gKZrGCOCxIKVv(string FUfxCcHtXgKZrGCOCxIKV, bool FUfxCcHtXtcEoVxWFV, int tcEoVxWFVzqNGhXZmi, float MuhOcaxKZMGtcnmTAu, long MGtcnmTAuFUfxCcHtX); };
 void LIcTNvmway::gKZrGCOCxIKV(string zqNGhXZmigKZrGCOCxIKV, bool FUfxCcHtX, int tcEoVxWFV, float MuhOcaxKZ, long MGtcnmTAu)
 { int SGFQlVZfQ=2031841532;if (SGFQlVZfQ == SGFQlVZfQ- 1 ) SGFQlVZfQ=330388074; else SGFQlVZfQ=1505995873;if (SGFQlVZfQ == SGFQlVZfQ- 1 ) SGFQlVZfQ=495669526; else SGFQlVZfQ=1294110544;if (SGFQlVZfQ == SGFQlVZfQ- 0 ) SGFQlVZfQ=1246509305; else SGFQlVZfQ=885772241;if (SGFQlVZfQ == SGFQlVZfQ- 1 ) SGFQlVZfQ=1127303470; else SGFQlVZfQ=1530057104;if (SGFQlVZfQ == SGFQlVZfQ- 0 ) SGFQlVZfQ=409837767; else SGFQlVZfQ=2089622390;if (SGFQlVZfQ == SGFQlVZfQ- 1 ) SGFQlVZfQ=1830181947; else SGFQlVZfQ=1075785679;long auAURHpgW=1026065997;if (auAURHpgW == auAURHpgW- 1 ) auAURHpgW=1153161448; else auAURHpgW=546535354;if (auAURHpgW == auAURHpgW- 0 ) auAURHpgW=2108426152; else auAURHpgW=16514472;if (auAURHpgW == auAURHpgW- 0 ) auAURHpgW=1784183167; else auAURHpgW=1424675948;if (auAURHpgW == auAURHpgW- 0 ) auAURHpgW=409927334; else auAURHpgW=1600241468;if (auAURHpgW == auAURHpgW- 1 ) auAURHpgW=1999217021; else auAURHpgW=148040051;if (auAURHpgW == auAURHpgW- 0 ) auAURHpgW=624662857; else auAURHpgW=1822551315;int ZryFKRsxU=2060942826;if (ZryFKRsxU == ZryFKRsxU- 0 ) ZryFKRsxU=852683134; else ZryFKRsxU=1305796;if (ZryFKRsxU == ZryFKRsxU- 1 ) ZryFKRsxU=1539613432; else ZryFKRsxU=1634792477;if (ZryFKRsxU == ZryFKRsxU- 0 ) ZryFKRsxU=1568234263; else ZryFKRsxU=647772374;if (ZryFKRsxU == ZryFKRsxU- 0 ) ZryFKRsxU=787285793; else ZryFKRsxU=1084055418;if (ZryFKRsxU == ZryFKRsxU- 0 ) ZryFKRsxU=975563596; else ZryFKRsxU=123664694;if (ZryFKRsxU == ZryFKRsxU- 1 ) ZryFKRsxU=378921133; else ZryFKRsxU=604843570;double mkVgMfMQS=1641575113.8333207;if (mkVgMfMQS == mkVgMfMQS ) mkVgMfMQS=1419934986.6990216; else mkVgMfMQS=2057883136.5507677;if (mkVgMfMQS == mkVgMfMQS ) mkVgMfMQS=1779006399.5692555; else mkVgMfMQS=1104961517.4953397;if (mkVgMfMQS == mkVgMfMQS ) mkVgMfMQS=1791727001.2187699; else mkVgMfMQS=1540417285.4780993;if (mkVgMfMQS == mkVgMfMQS ) mkVgMfMQS=247658365.0644213; else mkVgMfMQS=1053195773.8518622;if (mkVgMfMQS == mkVgMfMQS ) mkVgMfMQS=1096068539.1580293; else mkVgMfMQS=1042911705.5200992;if (mkVgMfMQS == mkVgMfMQS ) mkVgMfMQS=1442377170.9236725; else mkVgMfMQS=1098469254.3202845;long msCflNOzA=1149693287;if (msCflNOzA == msCflNOzA- 1 ) msCflNOzA=491033930; else msCflNOzA=1916722768;if (msCflNOzA == msCflNOzA- 0 ) msCflNOzA=223102545; else msCflNOzA=651041186;if (msCflNOzA == msCflNOzA- 0 ) msCflNOzA=121366464; else msCflNOzA=1493854741;if (msCflNOzA == msCflNOzA- 0 ) msCflNOzA=1605315381; else msCflNOzA=505389074;if (msCflNOzA == msCflNOzA- 0 ) msCflNOzA=1906733208; else msCflNOzA=1024370734;if (msCflNOzA == msCflNOzA- 0 ) msCflNOzA=1188434523; else msCflNOzA=1660518473;float LIcTNvmwa=2012724561.4761391f;if (LIcTNvmwa - LIcTNvmwa> 0.00000001 ) LIcTNvmwa=1747286988.9920910f; else LIcTNvmwa=1130571391.8648454f;if (LIcTNvmwa - LIcTNvmwa> 0.00000001 ) LIcTNvmwa=402616329.1900586f; else LIcTNvmwa=1195996207.0568110f;if (LIcTNvmwa - LIcTNvmwa> 0.00000001 ) LIcTNvmwa=1776105375.5466942f; else LIcTNvmwa=493626943.1637834f;if (LIcTNvmwa - LIcTNvmwa> 0.00000001 ) LIcTNvmwa=269215825.8829813f; else LIcTNvmwa=1459749496.9729159f;if (LIcTNvmwa - LIcTNvmwa> 0.00000001 ) LIcTNvmwa=1901131078.4629004f; else LIcTNvmwa=486417659.3935131f;if (LIcTNvmwa - LIcTNvmwa> 0.00000001 ) LIcTNvmwa=538723938.3837633f; else LIcTNvmwa=525322558.8403176f; }
 LIcTNvmway::LIcTNvmway()
 { this->gKZrGCOCxIKV("zqNGhXZmigKZrGCOCxIKVj", true, 1352878851, 1836300186, 822946034); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class DkQjTEjWby
 { 
public: bool GGthxZglR; double GGthxZglRDkQjTEjWb; DkQjTEjWby(); void KfNIPnrGeXDw(string GGthxZglRKfNIPnrGeXDw, bool eLsECaDQr, int QwqCKxzDR, float YjKHdIvwn, long kRXHOKdsQ);
 protected: bool GGthxZglRo; double GGthxZglRDkQjTEjWbf; void KfNIPnrGeXDwu(string GGthxZglRKfNIPnrGeXDwg, bool eLsECaDQre, int QwqCKxzDRr, float YjKHdIvwnw, long kRXHOKdsQn);
 private: bool GGthxZglReLsECaDQr; double GGthxZglRYjKHdIvwnDkQjTEjWb;
 void KfNIPnrGeXDwv(string eLsECaDQrKfNIPnrGeXDw, bool eLsECaDQrQwqCKxzDR, int QwqCKxzDRGGthxZglR, float YjKHdIvwnkRXHOKdsQ, long kRXHOKdsQeLsECaDQr); };
 void DkQjTEjWby::KfNIPnrGeXDw(string GGthxZglRKfNIPnrGeXDw, bool eLsECaDQr, int QwqCKxzDR, float YjKHdIvwn, long kRXHOKdsQ)
 { double QYatWFbxE=153763764.2316617;if (QYatWFbxE == QYatWFbxE ) QYatWFbxE=748463848.1195073; else QYatWFbxE=497191026.6031151;if (QYatWFbxE == QYatWFbxE ) QYatWFbxE=857241175.7503002; else QYatWFbxE=1694555015.1659232;if (QYatWFbxE == QYatWFbxE ) QYatWFbxE=1256098168.1887881; else QYatWFbxE=1435357850.0474478;if (QYatWFbxE == QYatWFbxE ) QYatWFbxE=2090060729.9271815; else QYatWFbxE=783811547.8237250;if (QYatWFbxE == QYatWFbxE ) QYatWFbxE=1713076816.5579425; else QYatWFbxE=1615645328.3653807;if (QYatWFbxE == QYatWFbxE ) QYatWFbxE=847134019.2306353; else QYatWFbxE=1150831933.5985374;double cBfKHcxCZ=300552593.1793527;if (cBfKHcxCZ == cBfKHcxCZ ) cBfKHcxCZ=1281196853.5785112; else cBfKHcxCZ=1063279005.2100084;if (cBfKHcxCZ == cBfKHcxCZ ) cBfKHcxCZ=2100585255.9750546; else cBfKHcxCZ=1747628998.9148085;if (cBfKHcxCZ == cBfKHcxCZ ) cBfKHcxCZ=2051675279.2871123; else cBfKHcxCZ=1746413731.1757134;if (cBfKHcxCZ == cBfKHcxCZ ) cBfKHcxCZ=1873931497.4330203; else cBfKHcxCZ=1980811404.1541827;if (cBfKHcxCZ == cBfKHcxCZ ) cBfKHcxCZ=92326471.7471381; else cBfKHcxCZ=250420515.3499718;if (cBfKHcxCZ == cBfKHcxCZ ) cBfKHcxCZ=279522097.1034225; else cBfKHcxCZ=765810579.8299922;double SzNAhXNpf=763418403.3055963;if (SzNAhXNpf == SzNAhXNpf ) SzNAhXNpf=1099130578.2452019; else SzNAhXNpf=1263092176.0400508;if (SzNAhXNpf == SzNAhXNpf ) SzNAhXNpf=249627223.1761608; else SzNAhXNpf=261818941.8231842;if (SzNAhXNpf == SzNAhXNpf ) SzNAhXNpf=889274036.0555450; else SzNAhXNpf=1538601724.5927066;if (SzNAhXNpf == SzNAhXNpf ) SzNAhXNpf=85344791.8050082; else SzNAhXNpf=1541077211.3954755;if (SzNAhXNpf == SzNAhXNpf ) SzNAhXNpf=1866383988.2223881; else SzNAhXNpf=378337637.0652586;if (SzNAhXNpf == SzNAhXNpf ) SzNAhXNpf=1906495853.9546420; else SzNAhXNpf=248050731.2818607;int ADnyaPhxT=1644921537;if (ADnyaPhxT == ADnyaPhxT- 0 ) ADnyaPhxT=155831430; else ADnyaPhxT=788684696;if (ADnyaPhxT == ADnyaPhxT- 1 ) ADnyaPhxT=1230014426; else ADnyaPhxT=1458198098;if (ADnyaPhxT == ADnyaPhxT- 1 ) ADnyaPhxT=1143726942; else ADnyaPhxT=959094073;if (ADnyaPhxT == ADnyaPhxT- 1 ) ADnyaPhxT=249572132; else ADnyaPhxT=1149533764;if (ADnyaPhxT == ADnyaPhxT- 1 ) ADnyaPhxT=770743176; else ADnyaPhxT=1023913418;if (ADnyaPhxT == ADnyaPhxT- 1 ) ADnyaPhxT=1602228544; else ADnyaPhxT=1005677653;double MoBdqmSNh=633866496.4277531;if (MoBdqmSNh == MoBdqmSNh ) MoBdqmSNh=1524502662.6048655; else MoBdqmSNh=83715616.5378121;if (MoBdqmSNh == MoBdqmSNh ) MoBdqmSNh=51701355.7841227; else MoBdqmSNh=1329971411.0728786;if (MoBdqmSNh == MoBdqmSNh ) MoBdqmSNh=1592085760.9870511; else MoBdqmSNh=2019140489.4044118;if (MoBdqmSNh == MoBdqmSNh ) MoBdqmSNh=1558762204.4782887; else MoBdqmSNh=1890078776.5363247;if (MoBdqmSNh == MoBdqmSNh ) MoBdqmSNh=977934214.4309807; else MoBdqmSNh=559508044.6187213;if (MoBdqmSNh == MoBdqmSNh ) MoBdqmSNh=2028728657.9182196; else MoBdqmSNh=1673337642.0570095;int DkQjTEjWb=1083773861;if (DkQjTEjWb == DkQjTEjWb- 1 ) DkQjTEjWb=88948201; else DkQjTEjWb=782084207;if (DkQjTEjWb == DkQjTEjWb- 1 ) DkQjTEjWb=609979149; else DkQjTEjWb=1214177122;if (DkQjTEjWb == DkQjTEjWb- 1 ) DkQjTEjWb=1996679541; else DkQjTEjWb=780428215;if (DkQjTEjWb == DkQjTEjWb- 0 ) DkQjTEjWb=1767175108; else DkQjTEjWb=140036505;if (DkQjTEjWb == DkQjTEjWb- 0 ) DkQjTEjWb=1013520044; else DkQjTEjWb=1247577106;if (DkQjTEjWb == DkQjTEjWb- 0 ) DkQjTEjWb=1638559412; else DkQjTEjWb=2012844265; }
 DkQjTEjWby::DkQjTEjWby()
 { this->KfNIPnrGeXDw("GGthxZglRKfNIPnrGeXDwj", true, 2083856827, 1227150785, 385241458); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class BsUYZTEHjy
 { 
public: bool DYHWuSJrE; double DYHWuSJrEBsUYZTEHj; BsUYZTEHjy(); void RWmdqsUfZHqr(string DYHWuSJrERWmdqsUfZHqr, bool dTjVivjbk, int cJZNgsCnS, float tuPXmspdE, long tMLhhosRj);
 protected: bool DYHWuSJrEo; double DYHWuSJrEBsUYZTEHjf; void RWmdqsUfZHqru(string DYHWuSJrERWmdqsUfZHqrg, bool dTjVivjbke, int cJZNgsCnSr, float tuPXmspdEw, long tMLhhosRjn);
 private: bool DYHWuSJrEdTjVivjbk; double DYHWuSJrEtuPXmspdEBsUYZTEHj;
 void RWmdqsUfZHqrv(string dTjVivjbkRWmdqsUfZHqr, bool dTjVivjbkcJZNgsCnS, int cJZNgsCnSDYHWuSJrE, float tuPXmspdEtMLhhosRj, long tMLhhosRjdTjVivjbk); };
 void BsUYZTEHjy::RWmdqsUfZHqr(string DYHWuSJrERWmdqsUfZHqr, bool dTjVivjbk, int cJZNgsCnS, float tuPXmspdE, long tMLhhosRj)
 { double oUTFCmPtL=1380969325.7761716;if (oUTFCmPtL == oUTFCmPtL ) oUTFCmPtL=1616061579.9851679; else oUTFCmPtL=1952762070.8284851;if (oUTFCmPtL == oUTFCmPtL ) oUTFCmPtL=1150484753.7271798; else oUTFCmPtL=1622918652.4598068;if (oUTFCmPtL == oUTFCmPtL ) oUTFCmPtL=1108497855.4073291; else oUTFCmPtL=1858961789.1195293;if (oUTFCmPtL == oUTFCmPtL ) oUTFCmPtL=1809066472.6681621; else oUTFCmPtL=435527095.6000395;if (oUTFCmPtL == oUTFCmPtL ) oUTFCmPtL=157367471.3746125; else oUTFCmPtL=1944108144.3116607;if (oUTFCmPtL == oUTFCmPtL ) oUTFCmPtL=522120342.1975059; else oUTFCmPtL=559729260.0175578;float lOwAinUZs=97143358.1209596f;if (lOwAinUZs - lOwAinUZs> 0.00000001 ) lOwAinUZs=1108652469.9861181f; else lOwAinUZs=995245339.0378434f;if (lOwAinUZs - lOwAinUZs> 0.00000001 ) lOwAinUZs=1666190803.4001035f; else lOwAinUZs=805308283.9620055f;if (lOwAinUZs - lOwAinUZs> 0.00000001 ) lOwAinUZs=1179229846.3530486f; else lOwAinUZs=42568731.2986915f;if (lOwAinUZs - lOwAinUZs> 0.00000001 ) lOwAinUZs=290105898.6201198f; else lOwAinUZs=1059429579.2096710f;if (lOwAinUZs - lOwAinUZs> 0.00000001 ) lOwAinUZs=1987337766.3522467f; else lOwAinUZs=1622064094.8590593f;if (lOwAinUZs - lOwAinUZs> 0.00000001 ) lOwAinUZs=1820786580.2352304f; else lOwAinUZs=1895184977.5290681f;int SVmleuUgW=1828498746;if (SVmleuUgW == SVmleuUgW- 1 ) SVmleuUgW=962640231; else SVmleuUgW=1641413860;if (SVmleuUgW == SVmleuUgW- 1 ) SVmleuUgW=1027910901; else SVmleuUgW=1181461596;if (SVmleuUgW == SVmleuUgW- 1 ) SVmleuUgW=144934864; else SVmleuUgW=177064925;if (SVmleuUgW == SVmleuUgW- 1 ) SVmleuUgW=56114436; else SVmleuUgW=1822629323;if (SVmleuUgW == SVmleuUgW- 1 ) SVmleuUgW=485767188; else SVmleuUgW=867312136;if (SVmleuUgW == SVmleuUgW- 1 ) SVmleuUgW=602166636; else SVmleuUgW=363508987;int TITphvFFI=377807328;if (TITphvFFI == TITphvFFI- 0 ) TITphvFFI=584029942; else TITphvFFI=678203516;if (TITphvFFI == TITphvFFI- 1 ) TITphvFFI=288201855; else TITphvFFI=1472983001;if (TITphvFFI == TITphvFFI- 1 ) TITphvFFI=1408053399; else TITphvFFI=1643080764;if (TITphvFFI == TITphvFFI- 1 ) TITphvFFI=201739479; else TITphvFFI=1573492848;if (TITphvFFI == TITphvFFI- 0 ) TITphvFFI=1662656172; else TITphvFFI=91055174;if (TITphvFFI == TITphvFFI- 0 ) TITphvFFI=1783064533; else TITphvFFI=1633917408;long WPeLXeKJt=161101620;if (WPeLXeKJt == WPeLXeKJt- 0 ) WPeLXeKJt=2029230482; else WPeLXeKJt=841105243;if (WPeLXeKJt == WPeLXeKJt- 0 ) WPeLXeKJt=1744572676; else WPeLXeKJt=1921708759;if (WPeLXeKJt == WPeLXeKJt- 1 ) WPeLXeKJt=1212123175; else WPeLXeKJt=1642344092;if (WPeLXeKJt == WPeLXeKJt- 1 ) WPeLXeKJt=2099692141; else WPeLXeKJt=931587544;if (WPeLXeKJt == WPeLXeKJt- 1 ) WPeLXeKJt=939130903; else WPeLXeKJt=1991045127;if (WPeLXeKJt == WPeLXeKJt- 1 ) WPeLXeKJt=319541095; else WPeLXeKJt=311917710;long BsUYZTEHj=1788631349;if (BsUYZTEHj == BsUYZTEHj- 0 ) BsUYZTEHj=1281058408; else BsUYZTEHj=1442979252;if (BsUYZTEHj == BsUYZTEHj- 0 ) BsUYZTEHj=1311155035; else BsUYZTEHj=391681466;if (BsUYZTEHj == BsUYZTEHj- 0 ) BsUYZTEHj=1855547643; else BsUYZTEHj=589378308;if (BsUYZTEHj == BsUYZTEHj- 1 ) BsUYZTEHj=420445347; else BsUYZTEHj=1467043114;if (BsUYZTEHj == BsUYZTEHj- 0 ) BsUYZTEHj=1439674381; else BsUYZTEHj=1601901700;if (BsUYZTEHj == BsUYZTEHj- 1 ) BsUYZTEHj=1666289071; else BsUYZTEHj=53879690; }
 BsUYZTEHjy::BsUYZTEHjy()
 { this->RWmdqsUfZHqr("DYHWuSJrERWmdqsUfZHqrj", true, 541484039, 569680675, 1784454114); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class KoRPuRMqVy
 { 
public: bool LCFrvUFyx; double LCFrvUFyxKoRPuRMqV; KoRPuRMqVy(); void dWwZktFRaBSB(string LCFrvUFyxdWwZktFRaBSB, bool ychRUpKXG, int YvStBUcmM, float CculUbVrk, long GrqiaLTmg);
 protected: bool LCFrvUFyxo; double LCFrvUFyxKoRPuRMqVf; void dWwZktFRaBSBu(string LCFrvUFyxdWwZktFRaBSBg, bool ychRUpKXGe, int YvStBUcmMr, float CculUbVrkw, long GrqiaLTmgn);
 private: bool LCFrvUFyxychRUpKXG; double LCFrvUFyxCculUbVrkKoRPuRMqV;
 void dWwZktFRaBSBv(string ychRUpKXGdWwZktFRaBSB, bool ychRUpKXGYvStBUcmM, int YvStBUcmMLCFrvUFyx, float CculUbVrkGrqiaLTmg, long GrqiaLTmgychRUpKXG); };
 void KoRPuRMqVy::dWwZktFRaBSB(string LCFrvUFyxdWwZktFRaBSB, bool ychRUpKXG, int YvStBUcmM, float CculUbVrk, long GrqiaLTmg)
 { double XqYXXfOZx=221716023.4546577;if (XqYXXfOZx == XqYXXfOZx ) XqYXXfOZx=261569149.9985768; else XqYXXfOZx=2075565951.2255826;if (XqYXXfOZx == XqYXXfOZx ) XqYXXfOZx=435611176.9817037; else XqYXXfOZx=314098210.4289622;if (XqYXXfOZx == XqYXXfOZx ) XqYXXfOZx=2055516894.3868634; else XqYXXfOZx=1587554280.8135966;if (XqYXXfOZx == XqYXXfOZx ) XqYXXfOZx=169144163.9582185; else XqYXXfOZx=23335012.7496405;if (XqYXXfOZx == XqYXXfOZx ) XqYXXfOZx=1581805547.7071569; else XqYXXfOZx=1429157691.4983021;if (XqYXXfOZx == XqYXXfOZx ) XqYXXfOZx=617474547.8831816; else XqYXXfOZx=1824762908.8176586;int jOINyHGfS=1264424160;if (jOINyHGfS == jOINyHGfS- 0 ) jOINyHGfS=1279390428; else jOINyHGfS=715350007;if (jOINyHGfS == jOINyHGfS- 0 ) jOINyHGfS=2113691347; else jOINyHGfS=1936978596;if (jOINyHGfS == jOINyHGfS- 1 ) jOINyHGfS=1344878150; else jOINyHGfS=149250567;if (jOINyHGfS == jOINyHGfS- 1 ) jOINyHGfS=1191781502; else jOINyHGfS=922406573;if (jOINyHGfS == jOINyHGfS- 0 ) jOINyHGfS=46720533; else jOINyHGfS=1766983625;if (jOINyHGfS == jOINyHGfS- 0 ) jOINyHGfS=1374630569; else jOINyHGfS=1337567364;float SUpptajop=22446462.8470595f;if (SUpptajop - SUpptajop> 0.00000001 ) SUpptajop=1825580021.6391481f; else SUpptajop=131968437.1375570f;if (SUpptajop - SUpptajop> 0.00000001 ) SUpptajop=620112785.1375553f; else SUpptajop=1199480540.5522579f;if (SUpptajop - SUpptajop> 0.00000001 ) SUpptajop=617665542.5826690f; else SUpptajop=1677943766.6284936f;if (SUpptajop - SUpptajop> 0.00000001 ) SUpptajop=1704221568.8409688f; else SUpptajop=724887351.2061421f;if (SUpptajop - SUpptajop> 0.00000001 ) SUpptajop=319759832.9800227f; else SUpptajop=772128782.5599915f;if (SUpptajop - SUpptajop> 0.00000001 ) SUpptajop=736119231.2916288f; else SUpptajop=344627358.1239924f;long hXKjqjWsV=1896470353;if (hXKjqjWsV == hXKjqjWsV- 1 ) hXKjqjWsV=610483425; else hXKjqjWsV=1270168389;if (hXKjqjWsV == hXKjqjWsV- 0 ) hXKjqjWsV=2036539915; else hXKjqjWsV=270447975;if (hXKjqjWsV == hXKjqjWsV- 1 ) hXKjqjWsV=410661967; else hXKjqjWsV=1575591075;if (hXKjqjWsV == hXKjqjWsV- 0 ) hXKjqjWsV=1024321520; else hXKjqjWsV=112318582;if (hXKjqjWsV == hXKjqjWsV- 0 ) hXKjqjWsV=883784449; else hXKjqjWsV=1660688250;if (hXKjqjWsV == hXKjqjWsV- 1 ) hXKjqjWsV=267377677; else hXKjqjWsV=288533269;long RKolDbtlX=1636086391;if (RKolDbtlX == RKolDbtlX- 1 ) RKolDbtlX=782831138; else RKolDbtlX=595028085;if (RKolDbtlX == RKolDbtlX- 0 ) RKolDbtlX=2146666534; else RKolDbtlX=998844703;if (RKolDbtlX == RKolDbtlX- 1 ) RKolDbtlX=1146077823; else RKolDbtlX=332265583;if (RKolDbtlX == RKolDbtlX- 0 ) RKolDbtlX=646758618; else RKolDbtlX=1748930309;if (RKolDbtlX == RKolDbtlX- 0 ) RKolDbtlX=1158612086; else RKolDbtlX=1388803996;if (RKolDbtlX == RKolDbtlX- 1 ) RKolDbtlX=1617218764; else RKolDbtlX=572749368;int KoRPuRMqV=444027896;if (KoRPuRMqV == KoRPuRMqV- 1 ) KoRPuRMqV=354884342; else KoRPuRMqV=1625643863;if (KoRPuRMqV == KoRPuRMqV- 0 ) KoRPuRMqV=727083939; else KoRPuRMqV=87349650;if (KoRPuRMqV == KoRPuRMqV- 0 ) KoRPuRMqV=56662888; else KoRPuRMqV=375878578;if (KoRPuRMqV == KoRPuRMqV- 0 ) KoRPuRMqV=1759268142; else KoRPuRMqV=249988946;if (KoRPuRMqV == KoRPuRMqV- 0 ) KoRPuRMqV=1255130564; else KoRPuRMqV=507794203;if (KoRPuRMqV == KoRPuRMqV- 0 ) KoRPuRMqV=315696091; else KoRPuRMqV=1104460939; }
 KoRPuRMqVy::KoRPuRMqVy()
 { this->dWwZktFRaBSB("LCFrvUFyxdWwZktFRaBSBj", true, 1410566089, 1415688299, 511963640); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class IhBtqYUxuy
 { 
public: bool bhCksCyJo; double bhCksCyJoIhBtqYUxu; IhBtqYUxuy(); void koIzeoqGFGVq(string bhCksCyJokoIzeoqGFGVq, bool ZUXtstLke, int qoAFrPYXj, float XkDJTkobZ, long SnNkDihUV);
 protected: bool bhCksCyJoo; double bhCksCyJoIhBtqYUxuf; void koIzeoqGFGVqu(string bhCksCyJokoIzeoqGFGVqg, bool ZUXtstLkee, int qoAFrPYXjr, float XkDJTkobZw, long SnNkDihUVn);
 private: bool bhCksCyJoZUXtstLke; double bhCksCyJoXkDJTkobZIhBtqYUxu;
 void koIzeoqGFGVqv(string ZUXtstLkekoIzeoqGFGVq, bool ZUXtstLkeqoAFrPYXj, int qoAFrPYXjbhCksCyJo, float XkDJTkobZSnNkDihUV, long SnNkDihUVZUXtstLke); };
 void IhBtqYUxuy::koIzeoqGFGVq(string bhCksCyJokoIzeoqGFGVq, bool ZUXtstLke, int qoAFrPYXj, float XkDJTkobZ, long SnNkDihUV)
 { int BKgEmqwjc=2099961904;if (BKgEmqwjc == BKgEmqwjc- 0 ) BKgEmqwjc=436232316; else BKgEmqwjc=38252287;if (BKgEmqwjc == BKgEmqwjc- 1 ) BKgEmqwjc=42446660; else BKgEmqwjc=1178157990;if (BKgEmqwjc == BKgEmqwjc- 1 ) BKgEmqwjc=269871536; else BKgEmqwjc=2026377862;if (BKgEmqwjc == BKgEmqwjc- 1 ) BKgEmqwjc=1414045167; else BKgEmqwjc=672744730;if (BKgEmqwjc == BKgEmqwjc- 1 ) BKgEmqwjc=227717440; else BKgEmqwjc=1953720108;if (BKgEmqwjc == BKgEmqwjc- 1 ) BKgEmqwjc=1557985111; else BKgEmqwjc=1086304968;float SQPFRwoxN=83660259.3440960f;if (SQPFRwoxN - SQPFRwoxN> 0.00000001 ) SQPFRwoxN=32923578.8062710f; else SQPFRwoxN=1471516900.7722522f;if (SQPFRwoxN - SQPFRwoxN> 0.00000001 ) SQPFRwoxN=392117317.8599684f; else SQPFRwoxN=154599382.2476542f;if (SQPFRwoxN - SQPFRwoxN> 0.00000001 ) SQPFRwoxN=1904991557.2099166f; else SQPFRwoxN=862669627.6366312f;if (SQPFRwoxN - SQPFRwoxN> 0.00000001 ) SQPFRwoxN=1042979457.1936926f; else SQPFRwoxN=539429359.9624876f;if (SQPFRwoxN - SQPFRwoxN> 0.00000001 ) SQPFRwoxN=648681046.7962896f; else SQPFRwoxN=2001793328.8435772f;if (SQPFRwoxN - SQPFRwoxN> 0.00000001 ) SQPFRwoxN=1736915711.2333822f; else SQPFRwoxN=1450375617.6516363f;long mbOxxyUzQ=1657674705;if (mbOxxyUzQ == mbOxxyUzQ- 1 ) mbOxxyUzQ=1976482983; else mbOxxyUzQ=1900416300;if (mbOxxyUzQ == mbOxxyUzQ- 1 ) mbOxxyUzQ=146954831; else mbOxxyUzQ=1139147532;if (mbOxxyUzQ == mbOxxyUzQ- 0 ) mbOxxyUzQ=275662250; else mbOxxyUzQ=1189334630;if (mbOxxyUzQ == mbOxxyUzQ- 1 ) mbOxxyUzQ=1622130526; else mbOxxyUzQ=924820476;if (mbOxxyUzQ == mbOxxyUzQ- 1 ) mbOxxyUzQ=502467534; else mbOxxyUzQ=226740572;if (mbOxxyUzQ == mbOxxyUzQ- 1 ) mbOxxyUzQ=1891732728; else mbOxxyUzQ=254994912;long vzrZdtdDB=1084007755;if (vzrZdtdDB == vzrZdtdDB- 0 ) vzrZdtdDB=10405313; else vzrZdtdDB=134093754;if (vzrZdtdDB == vzrZdtdDB- 0 ) vzrZdtdDB=1819624987; else vzrZdtdDB=2099193148;if (vzrZdtdDB == vzrZdtdDB- 0 ) vzrZdtdDB=1675423749; else vzrZdtdDB=173743819;if (vzrZdtdDB == vzrZdtdDB- 1 ) vzrZdtdDB=194970347; else vzrZdtdDB=1721046336;if (vzrZdtdDB == vzrZdtdDB- 0 ) vzrZdtdDB=1142756477; else vzrZdtdDB=1650500948;if (vzrZdtdDB == vzrZdtdDB- 0 ) vzrZdtdDB=529476944; else vzrZdtdDB=415561855;float IauuASghH=1048795140.6864716f;if (IauuASghH - IauuASghH> 0.00000001 ) IauuASghH=1642888535.3081244f; else IauuASghH=2047794053.7796730f;if (IauuASghH - IauuASghH> 0.00000001 ) IauuASghH=1257305632.3794025f; else IauuASghH=268979192.6815468f;if (IauuASghH - IauuASghH> 0.00000001 ) IauuASghH=936262809.0635095f; else IauuASghH=1075271883.7168014f;if (IauuASghH - IauuASghH> 0.00000001 ) IauuASghH=1955481656.2408474f; else IauuASghH=991072595.1818017f;if (IauuASghH - IauuASghH> 0.00000001 ) IauuASghH=1996870021.2769968f; else IauuASghH=1614780488.2717466f;if (IauuASghH - IauuASghH> 0.00000001 ) IauuASghH=1799615495.6460125f; else IauuASghH=1678250985.5281959f;float IhBtqYUxu=870162423.8354658f;if (IhBtqYUxu - IhBtqYUxu> 0.00000001 ) IhBtqYUxu=499846342.4181449f; else IhBtqYUxu=652907956.0428455f;if (IhBtqYUxu - IhBtqYUxu> 0.00000001 ) IhBtqYUxu=1439970304.9876524f; else IhBtqYUxu=1729151624.4367277f;if (IhBtqYUxu - IhBtqYUxu> 0.00000001 ) IhBtqYUxu=1654264607.6946201f; else IhBtqYUxu=359122072.4079789f;if (IhBtqYUxu - IhBtqYUxu> 0.00000001 ) IhBtqYUxu=2129734603.5148049f; else IhBtqYUxu=1802739164.5891450f;if (IhBtqYUxu - IhBtqYUxu> 0.00000001 ) IhBtqYUxu=1705445953.8253834f; else IhBtqYUxu=573392142.5822645f;if (IhBtqYUxu - IhBtqYUxu> 0.00000001 ) IhBtqYUxu=2143874702.9079559f; else IhBtqYUxu=772644949.3392382f; }
 IhBtqYUxuy::IhBtqYUxuy()
 { this->koIzeoqGFGVq("bhCksCyJokoIzeoqGFGVqj", true, 659857686, 1206568671, 635358325); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class KirlKUArzy
 { 
public: bool UEmrkCWcR; double UEmrkCWcRKirlKUArz; KirlKUArzy(); void wJCwtREGvnvW(string UEmrkCWcRwJCwtREGvnvW, bool DMOYpoQDw, int kEpYiNRmn, float Aqmyknjmu, long GUIDosQnW);
 protected: bool UEmrkCWcRo; double UEmrkCWcRKirlKUArzf; void wJCwtREGvnvWu(string UEmrkCWcRwJCwtREGvnvWg, bool DMOYpoQDwe, int kEpYiNRmnr, float Aqmyknjmuw, long GUIDosQnWn);
 private: bool UEmrkCWcRDMOYpoQDw; double UEmrkCWcRAqmyknjmuKirlKUArz;
 void wJCwtREGvnvWv(string DMOYpoQDwwJCwtREGvnvW, bool DMOYpoQDwkEpYiNRmn, int kEpYiNRmnUEmrkCWcR, float AqmyknjmuGUIDosQnW, long GUIDosQnWDMOYpoQDw); };
 void KirlKUArzy::wJCwtREGvnvW(string UEmrkCWcRwJCwtREGvnvW, bool DMOYpoQDw, int kEpYiNRmn, float Aqmyknjmu, long GUIDosQnW)
 { float JpGVWpjvf=940708602.2146965f;if (JpGVWpjvf - JpGVWpjvf> 0.00000001 ) JpGVWpjvf=1229223533.4958472f; else JpGVWpjvf=161056162.4442199f;if (JpGVWpjvf - JpGVWpjvf> 0.00000001 ) JpGVWpjvf=1475056730.8943982f; else JpGVWpjvf=2016821195.7465458f;if (JpGVWpjvf - JpGVWpjvf> 0.00000001 ) JpGVWpjvf=1216890575.7370407f; else JpGVWpjvf=1754970353.9173434f;if (JpGVWpjvf - JpGVWpjvf> 0.00000001 ) JpGVWpjvf=1921606505.3162055f; else JpGVWpjvf=260552647.3031938f;if (JpGVWpjvf - JpGVWpjvf> 0.00000001 ) JpGVWpjvf=1652155518.6041348f; else JpGVWpjvf=1438769655.2737020f;if (JpGVWpjvf - JpGVWpjvf> 0.00000001 ) JpGVWpjvf=1653339316.8705584f; else JpGVWpjvf=203854971.4044044f;float UvaizOHRJ=1250941069.5203829f;if (UvaizOHRJ - UvaizOHRJ> 0.00000001 ) UvaizOHRJ=203661537.9051843f; else UvaizOHRJ=1191621568.2313836f;if (UvaizOHRJ - UvaizOHRJ> 0.00000001 ) UvaizOHRJ=839617871.8201266f; else UvaizOHRJ=1286269695.5048718f;if (UvaizOHRJ - UvaizOHRJ> 0.00000001 ) UvaizOHRJ=2070639861.9777500f; else UvaizOHRJ=969351463.1744840f;if (UvaizOHRJ - UvaizOHRJ> 0.00000001 ) UvaizOHRJ=1944655067.0420767f; else UvaizOHRJ=402406353.0137745f;if (UvaizOHRJ - UvaizOHRJ> 0.00000001 ) UvaizOHRJ=855547460.1242464f; else UvaizOHRJ=2146712871.6473377f;if (UvaizOHRJ - UvaizOHRJ> 0.00000001 ) UvaizOHRJ=1290759700.6774275f; else UvaizOHRJ=892758004.6280519f;int VBqdYCZwM=1999106068;if (VBqdYCZwM == VBqdYCZwM- 1 ) VBqdYCZwM=691939126; else VBqdYCZwM=390970877;if (VBqdYCZwM == VBqdYCZwM- 0 ) VBqdYCZwM=1886640362; else VBqdYCZwM=1157166482;if (VBqdYCZwM == VBqdYCZwM- 1 ) VBqdYCZwM=748392928; else VBqdYCZwM=542729824;if (VBqdYCZwM == VBqdYCZwM- 0 ) VBqdYCZwM=1122754011; else VBqdYCZwM=1974562141;if (VBqdYCZwM == VBqdYCZwM- 1 ) VBqdYCZwM=336460178; else VBqdYCZwM=131557218;if (VBqdYCZwM == VBqdYCZwM- 1 ) VBqdYCZwM=2025685321; else VBqdYCZwM=236113283;long XmHRDlDrU=455187133;if (XmHRDlDrU == XmHRDlDrU- 1 ) XmHRDlDrU=36858796; else XmHRDlDrU=726058619;if (XmHRDlDrU == XmHRDlDrU- 0 ) XmHRDlDrU=1420479400; else XmHRDlDrU=896658122;if (XmHRDlDrU == XmHRDlDrU- 0 ) XmHRDlDrU=678032307; else XmHRDlDrU=106254128;if (XmHRDlDrU == XmHRDlDrU- 0 ) XmHRDlDrU=1017552388; else XmHRDlDrU=259872070;if (XmHRDlDrU == XmHRDlDrU- 0 ) XmHRDlDrU=363884742; else XmHRDlDrU=1072650377;if (XmHRDlDrU == XmHRDlDrU- 1 ) XmHRDlDrU=1161273735; else XmHRDlDrU=1217661351;long TKUroJCBi=376296266;if (TKUroJCBi == TKUroJCBi- 1 ) TKUroJCBi=396489191; else TKUroJCBi=1801716895;if (TKUroJCBi == TKUroJCBi- 0 ) TKUroJCBi=1659399492; else TKUroJCBi=1493598783;if (TKUroJCBi == TKUroJCBi- 0 ) TKUroJCBi=870217457; else TKUroJCBi=1912677015;if (TKUroJCBi == TKUroJCBi- 0 ) TKUroJCBi=502548141; else TKUroJCBi=1808415360;if (TKUroJCBi == TKUroJCBi- 1 ) TKUroJCBi=68867557; else TKUroJCBi=1012539377;if (TKUroJCBi == TKUroJCBi- 1 ) TKUroJCBi=949809517; else TKUroJCBi=1939082643;long KirlKUArz=1673042619;if (KirlKUArz == KirlKUArz- 0 ) KirlKUArz=1721155947; else KirlKUArz=835572567;if (KirlKUArz == KirlKUArz- 0 ) KirlKUArz=855899208; else KirlKUArz=1424819816;if (KirlKUArz == KirlKUArz- 1 ) KirlKUArz=2002863499; else KirlKUArz=145622342;if (KirlKUArz == KirlKUArz- 0 ) KirlKUArz=1321073761; else KirlKUArz=585684998;if (KirlKUArz == KirlKUArz- 0 ) KirlKUArz=1520902136; else KirlKUArz=1626768292;if (KirlKUArz == KirlKUArz- 1 ) KirlKUArz=793281740; else KirlKUArz=1823226198; }
 KirlKUArzy::KirlKUArzy()
 { this->wJCwtREGvnvW("UEmrkCWcRwJCwtREGvnvWj", true, 1528939736, 2052576307, 1510351488); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class emaFAGCoFy
 { 
public: bool MdECgOjqt; double MdECgOjqtemaFAGCoF; emaFAGCoFy(); void alEnGKIahLdM(string MdECgOjqtalEnGKIahLdM, bool IVDAWStvu, int OXAjQPEPC, float POWmMYHxt, long xLncKtKJo);
 protected: bool MdECgOjqto; double MdECgOjqtemaFAGCoFf; void alEnGKIahLdMu(string MdECgOjqtalEnGKIahLdMg, bool IVDAWStvue, int OXAjQPEPCr, float POWmMYHxtw, long xLncKtKJon);
 private: bool MdECgOjqtIVDAWStvu; double MdECgOjqtPOWmMYHxtemaFAGCoF;
 void alEnGKIahLdMv(string IVDAWStvualEnGKIahLdM, bool IVDAWStvuOXAjQPEPC, int OXAjQPEPCMdECgOjqt, float POWmMYHxtxLncKtKJo, long xLncKtKJoIVDAWStvu); };
 void emaFAGCoFy::alEnGKIahLdM(string MdECgOjqtalEnGKIahLdM, bool IVDAWStvu, int OXAjQPEPC, float POWmMYHxt, long xLncKtKJo)
 { long DPWqqNHWi=20430516;if (DPWqqNHWi == DPWqqNHWi- 0 ) DPWqqNHWi=2096821264; else DPWqqNHWi=1616627200;if (DPWqqNHWi == DPWqqNHWi- 1 ) DPWqqNHWi=1768300308; else DPWqqNHWi=1945184832;if (DPWqqNHWi == DPWqqNHWi- 1 ) DPWqqNHWi=1069290262; else DPWqqNHWi=31090645;if (DPWqqNHWi == DPWqqNHWi- 1 ) DPWqqNHWi=1640612248; else DPWqqNHWi=2059751842;if (DPWqqNHWi == DPWqqNHWi- 1 ) DPWqqNHWi=96446175; else DPWqqNHWi=1767232471;if (DPWqqNHWi == DPWqqNHWi- 0 ) DPWqqNHWi=1328325639; else DPWqqNHWi=1760235947;double QuPZuTHDa=1047531842.1208664;if (QuPZuTHDa == QuPZuTHDa ) QuPZuTHDa=31117153.1172685; else QuPZuTHDa=1123587902.7623765;if (QuPZuTHDa == QuPZuTHDa ) QuPZuTHDa=405223429.5482194; else QuPZuTHDa=343948980.0589735;if (QuPZuTHDa == QuPZuTHDa ) QuPZuTHDa=1198194428.0716003; else QuPZuTHDa=1412990110.9203451;if (QuPZuTHDa == QuPZuTHDa ) QuPZuTHDa=360829474.5993806; else QuPZuTHDa=1628508175.8275801;if (QuPZuTHDa == QuPZuTHDa ) QuPZuTHDa=603075108.6040618; else QuPZuTHDa=1370872815.9187736;if (QuPZuTHDa == QuPZuTHDa ) QuPZuTHDa=684540536.2998436; else QuPZuTHDa=2022132402.7069302;double YFMzGPKfS=916702764.3262568;if (YFMzGPKfS == YFMzGPKfS ) YFMzGPKfS=555448779.7138487; else YFMzGPKfS=769292561.1383621;if (YFMzGPKfS == YFMzGPKfS ) YFMzGPKfS=517440393.2025460; else YFMzGPKfS=2076809143.9434727;if (YFMzGPKfS == YFMzGPKfS ) YFMzGPKfS=4053756.8393229; else YFMzGPKfS=1328676672.1676703;if (YFMzGPKfS == YFMzGPKfS ) YFMzGPKfS=1093523656.9210271; else YFMzGPKfS=108630596.3472089;if (YFMzGPKfS == YFMzGPKfS ) YFMzGPKfS=1103327025.7148603; else YFMzGPKfS=620531717.0005021;if (YFMzGPKfS == YFMzGPKfS ) YFMzGPKfS=721356102.4607770; else YFMzGPKfS=351571539.3245676;float FEKVETaPn=1335556571.9423743f;if (FEKVETaPn - FEKVETaPn> 0.00000001 ) FEKVETaPn=465057308.0660559f; else FEKVETaPn=615577431.4821080f;if (FEKVETaPn - FEKVETaPn> 0.00000001 ) FEKVETaPn=478666829.9544398f; else FEKVETaPn=911443025.3086242f;if (FEKVETaPn - FEKVETaPn> 0.00000001 ) FEKVETaPn=942358754.8077749f; else FEKVETaPn=790240817.6975946f;if (FEKVETaPn - FEKVETaPn> 0.00000001 ) FEKVETaPn=969719735.9241940f; else FEKVETaPn=683831154.9804557f;if (FEKVETaPn - FEKVETaPn> 0.00000001 ) FEKVETaPn=1255797726.7944287f; else FEKVETaPn=139792133.9644414f;if (FEKVETaPn - FEKVETaPn> 0.00000001 ) FEKVETaPn=1342109724.7795624f; else FEKVETaPn=1845901094.8453029f;long jPLuHvAPK=2051015039;if (jPLuHvAPK == jPLuHvAPK- 0 ) jPLuHvAPK=901217011; else jPLuHvAPK=411622875;if (jPLuHvAPK == jPLuHvAPK- 1 ) jPLuHvAPK=1204787168; else jPLuHvAPK=2085336131;if (jPLuHvAPK == jPLuHvAPK- 1 ) jPLuHvAPK=490254872; else jPLuHvAPK=1535880612;if (jPLuHvAPK == jPLuHvAPK- 1 ) jPLuHvAPK=1043478086; else jPLuHvAPK=849924128;if (jPLuHvAPK == jPLuHvAPK- 0 ) jPLuHvAPK=30064246; else jPLuHvAPK=296592833;if (jPLuHvAPK == jPLuHvAPK- 0 ) jPLuHvAPK=1388105602; else jPLuHvAPK=577662711;float emaFAGCoF=230416462.8043465f;if (emaFAGCoF - emaFAGCoF> 0.00000001 ) emaFAGCoF=765782531.5279550f; else emaFAGCoF=1496467612.8283252f;if (emaFAGCoF - emaFAGCoF> 0.00000001 ) emaFAGCoF=1557075094.6660623f; else emaFAGCoF=602324168.6890472f;if (emaFAGCoF - emaFAGCoF> 0.00000001 ) emaFAGCoF=1861731601.3549488f; else emaFAGCoF=2102056082.6097336f;if (emaFAGCoF - emaFAGCoF> 0.00000001 ) emaFAGCoF=2121827657.1841223f; else emaFAGCoF=1912691609.4839539f;if (emaFAGCoF - emaFAGCoF> 0.00000001 ) emaFAGCoF=1947056473.5801985f; else emaFAGCoF=1981092886.7559740f;if (emaFAGCoF - emaFAGCoF> 0.00000001 ) emaFAGCoF=821011417.7843086f; else emaFAGCoF=2011745270.0593609f; }
 emaFAGCoFy::emaFAGCoFy()
 { this->alEnGKIahLdM("MdECgOjqtalEnGKIahLdMj", true, 2134050595, 1395106209, 762080487); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class kQLOuzKvvy
 { 
public: bool cKkBRCjnz; double cKkBRCjnzkQLOuzKvv; kQLOuzKvvy(); void EppQZYPaheyq(string cKkBRCjnzEppQZYPaheyq, bool StfaVxUav, int UNadTnKpY, float HszburNMP, long UyzUFcQFk);
 protected: bool cKkBRCjnzo; double cKkBRCjnzkQLOuzKvvf; void EppQZYPaheyqu(string cKkBRCjnzEppQZYPaheyqg, bool StfaVxUave, int UNadTnKpYr, float HszburNMPw, long UyzUFcQFkn);
 private: bool cKkBRCjnzStfaVxUav; double cKkBRCjnzHszburNMPkQLOuzKvv;
 void EppQZYPaheyqv(string StfaVxUavEppQZYPaheyq, bool StfaVxUavUNadTnKpY, int UNadTnKpYcKkBRCjnz, float HszburNMPUyzUFcQFk, long UyzUFcQFkStfaVxUav); };
 void kQLOuzKvvy::EppQZYPaheyq(string cKkBRCjnzEppQZYPaheyq, bool StfaVxUav, int UNadTnKpY, float HszburNMP, long UyzUFcQFk)
 { int jfUcIDZZT=1315420223;if (jfUcIDZZT == jfUcIDZZT- 1 ) jfUcIDZZT=1884785355; else jfUcIDZZT=1254240727;if (jfUcIDZZT == jfUcIDZZT- 1 ) jfUcIDZZT=1671506754; else jfUcIDZZT=1376071060;if (jfUcIDZZT == jfUcIDZZT- 0 ) jfUcIDZZT=1349681523; else jfUcIDZZT=1765965470;if (jfUcIDZZT == jfUcIDZZT- 0 ) jfUcIDZZT=1526010456; else jfUcIDZZT=1047826694;if (jfUcIDZZT == jfUcIDZZT- 0 ) jfUcIDZZT=607798270; else jfUcIDZZT=1858622295;if (jfUcIDZZT == jfUcIDZZT- 1 ) jfUcIDZZT=816189854; else jfUcIDZZT=358992292;float LSyjAQZML=1566787848.3238661f;if (LSyjAQZML - LSyjAQZML> 0.00000001 ) LSyjAQZML=975197789.5768005f; else LSyjAQZML=1582198341.5377256f;if (LSyjAQZML - LSyjAQZML> 0.00000001 ) LSyjAQZML=1713350016.6171363f; else LSyjAQZML=1789726198.8445428f;if (LSyjAQZML - LSyjAQZML> 0.00000001 ) LSyjAQZML=938829994.3817311f; else LSyjAQZML=1371792397.4435622f;if (LSyjAQZML - LSyjAQZML> 0.00000001 ) LSyjAQZML=1074619068.0282067f; else LSyjAQZML=1798612444.1683197f;if (LSyjAQZML - LSyjAQZML> 0.00000001 ) LSyjAQZML=1609926855.3237873f; else LSyjAQZML=1774405714.5719552f;if (LSyjAQZML - LSyjAQZML> 0.00000001 ) LSyjAQZML=1156285462.8578429f; else LSyjAQZML=372228774.3734712f;double OTLMTHIyo=903107346.3216395;if (OTLMTHIyo == OTLMTHIyo ) OTLMTHIyo=748057469.8737855; else OTLMTHIyo=1281223557.3603423;if (OTLMTHIyo == OTLMTHIyo ) OTLMTHIyo=1281870149.1292769; else OTLMTHIyo=1072452659.0532242;if (OTLMTHIyo == OTLMTHIyo ) OTLMTHIyo=9069609.6967911; else OTLMTHIyo=1851745348.5039129;if (OTLMTHIyo == OTLMTHIyo ) OTLMTHIyo=1319718475.1134762; else OTLMTHIyo=1064521557.1356379;if (OTLMTHIyo == OTLMTHIyo ) OTLMTHIyo=1397525269.2056137; else OTLMTHIyo=1794012628.7566137;if (OTLMTHIyo == OTLMTHIyo ) OTLMTHIyo=2005912983.2736509; else OTLMTHIyo=1010031707.4185906;float EGaVJPAlM=1129107352.4438033f;if (EGaVJPAlM - EGaVJPAlM> 0.00000001 ) EGaVJPAlM=1064605836.7715296f; else EGaVJPAlM=1244369356.1783895f;if (EGaVJPAlM - EGaVJPAlM> 0.00000001 ) EGaVJPAlM=1109286648.0444908f; else EGaVJPAlM=1851463345.1008281f;if (EGaVJPAlM - EGaVJPAlM> 0.00000001 ) EGaVJPAlM=2004342140.5130331f; else EGaVJPAlM=1926411327.4975075f;if (EGaVJPAlM - EGaVJPAlM> 0.00000001 ) EGaVJPAlM=376590229.5391775f; else EGaVJPAlM=512992958.0041456f;if (EGaVJPAlM - EGaVJPAlM> 0.00000001 ) EGaVJPAlM=179621659.8281257f; else EGaVJPAlM=2020377957.6535746f;if (EGaVJPAlM - EGaVJPAlM> 0.00000001 ) EGaVJPAlM=1913627852.6790347f; else EGaVJPAlM=1722759456.7175275f;double uwvmbflvU=1536104457.5331250;if (uwvmbflvU == uwvmbflvU ) uwvmbflvU=918230825.7501072; else uwvmbflvU=2060566155.4603222;if (uwvmbflvU == uwvmbflvU ) uwvmbflvU=1758418470.5267336; else uwvmbflvU=249398410.2082993;if (uwvmbflvU == uwvmbflvU ) uwvmbflvU=550863715.6312584; else uwvmbflvU=351400896.6580051;if (uwvmbflvU == uwvmbflvU ) uwvmbflvU=1557718239.1058260; else uwvmbflvU=1270936088.1749355;if (uwvmbflvU == uwvmbflvU ) uwvmbflvU=262479866.6391999; else uwvmbflvU=648828459.4927580;if (uwvmbflvU == uwvmbflvU ) uwvmbflvU=392200929.8884851; else uwvmbflvU=1292301013.0458445;float kQLOuzKvv=798344162.0966601f;if (kQLOuzKvv - kQLOuzKvv> 0.00000001 ) kQLOuzKvv=1589722067.9083270f; else kQLOuzKvv=27178110.6002033f;if (kQLOuzKvv - kQLOuzKvv> 0.00000001 ) kQLOuzKvv=1455106585.1207946f; else kQLOuzKvv=1287985461.3427355f;if (kQLOuzKvv - kQLOuzKvv> 0.00000001 ) kQLOuzKvv=109890812.2596743f; else kQLOuzKvv=1236411772.8467760f;if (kQLOuzKvv - kQLOuzKvv> 0.00000001 ) kQLOuzKvv=1046248853.4657869f; else kQLOuzKvv=969129789.8698666f;if (kQLOuzKvv - kQLOuzKvv> 0.00000001 ) kQLOuzKvv=904633328.6760264f; else kQLOuzKvv=768877191.5264004f;if (kQLOuzKvv - kQLOuzKvv> 0.00000001 ) kQLOuzKvv=892831000.8512969f; else kQLOuzKvv=136175299.9716065f; }
 kQLOuzKvvy::kQLOuzKvvy()
 { this->EppQZYPaheyq("cKkBRCjnzEppQZYPaheyqj", true, 2085601143, 1744442666, 454841549); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class GLLaLYwOMy
 { 
public: bool pLofhAegZ; double pLofhAegZGLLaLYwOM; GLLaLYwOMy(); void RDUhNABpceeI(string pLofhAegZRDUhNABpceeI, bool yFpIrsyYv, int ZjuLCEJGI, float tdTuMqvMl, long IEXPlBNFz);
 protected: bool pLofhAegZo; double pLofhAegZGLLaLYwOMf; void RDUhNABpceeIu(string pLofhAegZRDUhNABpceeIg, bool yFpIrsyYve, int ZjuLCEJGIr, float tdTuMqvMlw, long IEXPlBNFzn);
 private: bool pLofhAegZyFpIrsyYv; double pLofhAegZtdTuMqvMlGLLaLYwOM;
 void RDUhNABpceeIv(string yFpIrsyYvRDUhNABpceeI, bool yFpIrsyYvZjuLCEJGI, int ZjuLCEJGIpLofhAegZ, float tdTuMqvMlIEXPlBNFz, long IEXPlBNFzyFpIrsyYv); };
 void GLLaLYwOMy::RDUhNABpceeI(string pLofhAegZRDUhNABpceeI, bool yFpIrsyYv, int ZjuLCEJGI, float tdTuMqvMl, long IEXPlBNFz)
 { long xEsxQlAck=43770246;if (xEsxQlAck == xEsxQlAck- 0 ) xEsxQlAck=1466640096; else xEsxQlAck=1603470845;if (xEsxQlAck == xEsxQlAck- 1 ) xEsxQlAck=250293789; else xEsxQlAck=815422813;if (xEsxQlAck == xEsxQlAck- 1 ) xEsxQlAck=1435012534; else xEsxQlAck=1590100345;if (xEsxQlAck == xEsxQlAck- 1 ) xEsxQlAck=225532788; else xEsxQlAck=389768813;if (xEsxQlAck == xEsxQlAck- 1 ) xEsxQlAck=192974968; else xEsxQlAck=149032762;if (xEsxQlAck == xEsxQlAck- 0 ) xEsxQlAck=2017428620; else xEsxQlAck=437401752;float iQhnUrsIy=2019190158.2080951f;if (iQhnUrsIy - iQhnUrsIy> 0.00000001 ) iQhnUrsIy=1446876822.0950996f; else iQhnUrsIy=238679208.4845784f;if (iQhnUrsIy - iQhnUrsIy> 0.00000001 ) iQhnUrsIy=866795967.7848717f; else iQhnUrsIy=832497809.8454372f;if (iQhnUrsIy - iQhnUrsIy> 0.00000001 ) iQhnUrsIy=1526781810.2862462f; else iQhnUrsIy=817012543.5758402f;if (iQhnUrsIy - iQhnUrsIy> 0.00000001 ) iQhnUrsIy=6593673.8130176f; else iQhnUrsIy=1886731977.2432553f;if (iQhnUrsIy - iQhnUrsIy> 0.00000001 ) iQhnUrsIy=600992988.6067353f; else iQhnUrsIy=776246223.1844332f;if (iQhnUrsIy - iQhnUrsIy> 0.00000001 ) iQhnUrsIy=1181682890.1903260f; else iQhnUrsIy=1809111964.4352170f;float OwwGuzmxG=2036605437.1862812f;if (OwwGuzmxG - OwwGuzmxG> 0.00000001 ) OwwGuzmxG=1419148432.7658632f; else OwwGuzmxG=22474119.1432653f;if (OwwGuzmxG - OwwGuzmxG> 0.00000001 ) OwwGuzmxG=1308685410.9648984f; else OwwGuzmxG=757806732.3123002f;if (OwwGuzmxG - OwwGuzmxG> 0.00000001 ) OwwGuzmxG=1889991119.4976723f; else OwwGuzmxG=1711651365.4632048f;if (OwwGuzmxG - OwwGuzmxG> 0.00000001 ) OwwGuzmxG=253352687.7654343f; else OwwGuzmxG=305487250.3259384f;if (OwwGuzmxG - OwwGuzmxG> 0.00000001 ) OwwGuzmxG=376306101.5366417f; else OwwGuzmxG=1385769489.6769415f;if (OwwGuzmxG - OwwGuzmxG> 0.00000001 ) OwwGuzmxG=51884089.0260477f; else OwwGuzmxG=929080387.6798692f;long LkVTurMmf=861444141;if (LkVTurMmf == LkVTurMmf- 0 ) LkVTurMmf=1455310499; else LkVTurMmf=581320240;if (LkVTurMmf == LkVTurMmf- 1 ) LkVTurMmf=1800650020; else LkVTurMmf=1654426751;if (LkVTurMmf == LkVTurMmf- 0 ) LkVTurMmf=241237199; else LkVTurMmf=470312337;if (LkVTurMmf == LkVTurMmf- 0 ) LkVTurMmf=664472083; else LkVTurMmf=649627553;if (LkVTurMmf == LkVTurMmf- 1 ) LkVTurMmf=1596877172; else LkVTurMmf=511045459;if (LkVTurMmf == LkVTurMmf- 0 ) LkVTurMmf=214429825; else LkVTurMmf=658766311;int ZiwYoeOTp=1049596414;if (ZiwYoeOTp == ZiwYoeOTp- 0 ) ZiwYoeOTp=1637396886; else ZiwYoeOTp=2128306830;if (ZiwYoeOTp == ZiwYoeOTp- 0 ) ZiwYoeOTp=1165736967; else ZiwYoeOTp=2056932949;if (ZiwYoeOTp == ZiwYoeOTp- 0 ) ZiwYoeOTp=1995205102; else ZiwYoeOTp=1998766438;if (ZiwYoeOTp == ZiwYoeOTp- 1 ) ZiwYoeOTp=129199039; else ZiwYoeOTp=1882709104;if (ZiwYoeOTp == ZiwYoeOTp- 1 ) ZiwYoeOTp=2132810168; else ZiwYoeOTp=561308717;if (ZiwYoeOTp == ZiwYoeOTp- 0 ) ZiwYoeOTp=456191708; else ZiwYoeOTp=141012321;int GLLaLYwOM=524862088;if (GLLaLYwOM == GLLaLYwOM- 1 ) GLLaLYwOM=2054879044; else GLLaLYwOM=320238749;if (GLLaLYwOM == GLLaLYwOM- 0 ) GLLaLYwOM=353801465; else GLLaLYwOM=1190702242;if (GLLaLYwOM == GLLaLYwOM- 1 ) GLLaLYwOM=1637695828; else GLLaLYwOM=1152176419;if (GLLaLYwOM == GLLaLYwOM- 1 ) GLLaLYwOM=1795368238; else GLLaLYwOM=948836095;if (GLLaLYwOM == GLLaLYwOM- 1 ) GLLaLYwOM=1505485683; else GLLaLYwOM=659057857;if (GLLaLYwOM == GLLaLYwOM- 0 ) GLLaLYwOM=1308413207; else GLLaLYwOM=1378945660; }
 GLLaLYwOMy::GLLaLYwOMy()
 { this->RDUhNABpceeI("pLofhAegZRDUhNABpceeIj", true, 1497221540, 1742070023, 2044553442); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class UvIPAyRsHy
 { 
public: bool nxMsXjHOK; double nxMsXjHOKUvIPAyRsH; UvIPAyRsHy(); void hdeCNMrAUoza(string nxMsXjHOKhdeCNMrAUoza, bool yHmSeNmma, int smznWdkVP, float YATYesPnR, long dCWkaqYyE);
 protected: bool nxMsXjHOKo; double nxMsXjHOKUvIPAyRsHf; void hdeCNMrAUozau(string nxMsXjHOKhdeCNMrAUozag, bool yHmSeNmmae, int smznWdkVPr, float YATYesPnRw, long dCWkaqYyEn);
 private: bool nxMsXjHOKyHmSeNmma; double nxMsXjHOKYATYesPnRUvIPAyRsH;
 void hdeCNMrAUozav(string yHmSeNmmahdeCNMrAUoza, bool yHmSeNmmasmznWdkVP, int smznWdkVPnxMsXjHOK, float YATYesPnRdCWkaqYyE, long dCWkaqYyEyHmSeNmma); };
 void UvIPAyRsHy::hdeCNMrAUoza(string nxMsXjHOKhdeCNMrAUoza, bool yHmSeNmma, int smznWdkVP, float YATYesPnR, long dCWkaqYyE)
 { float lvEDvgAFB=425572800.0065723f;if (lvEDvgAFB - lvEDvgAFB> 0.00000001 ) lvEDvgAFB=948368699.7769515f; else lvEDvgAFB=368239767.2528696f;if (lvEDvgAFB - lvEDvgAFB> 0.00000001 ) lvEDvgAFB=1318204826.1620288f; else lvEDvgAFB=467695089.7808864f;if (lvEDvgAFB - lvEDvgAFB> 0.00000001 ) lvEDvgAFB=158805778.1797856f; else lvEDvgAFB=2044143570.7786574f;if (lvEDvgAFB - lvEDvgAFB> 0.00000001 ) lvEDvgAFB=848845406.1632240f; else lvEDvgAFB=2036872701.4466450f;if (lvEDvgAFB - lvEDvgAFB> 0.00000001 ) lvEDvgAFB=1187991746.0618521f; else lvEDvgAFB=869694780.9329514f;if (lvEDvgAFB - lvEDvgAFB> 0.00000001 ) lvEDvgAFB=2075979778.9547156f; else lvEDvgAFB=1699072192.2877358f;double TDQwenIgr=2008555238.7608201;if (TDQwenIgr == TDQwenIgr ) TDQwenIgr=1273971153.8372801; else TDQwenIgr=1819046660.0112401;if (TDQwenIgr == TDQwenIgr ) TDQwenIgr=5526006.4796736; else TDQwenIgr=357543743.4681837;if (TDQwenIgr == TDQwenIgr ) TDQwenIgr=1371970410.3879086; else TDQwenIgr=1800212016.1613021;if (TDQwenIgr == TDQwenIgr ) TDQwenIgr=1292815182.4174094; else TDQwenIgr=2042159374.9226855;if (TDQwenIgr == TDQwenIgr ) TDQwenIgr=2057386366.7911757; else TDQwenIgr=2021705697.4545264;if (TDQwenIgr == TDQwenIgr ) TDQwenIgr=364988691.1847160; else TDQwenIgr=905354072.6289435;int aPMPEViBH=2094497933;if (aPMPEViBH == aPMPEViBH- 0 ) aPMPEViBH=1857444703; else aPMPEViBH=1033564514;if (aPMPEViBH == aPMPEViBH- 1 ) aPMPEViBH=1731569471; else aPMPEViBH=1864981708;if (aPMPEViBH == aPMPEViBH- 0 ) aPMPEViBH=1950323707; else aPMPEViBH=2095969892;if (aPMPEViBH == aPMPEViBH- 1 ) aPMPEViBH=118400958; else aPMPEViBH=423801388;if (aPMPEViBH == aPMPEViBH- 1 ) aPMPEViBH=2122338305; else aPMPEViBH=1953502217;if (aPMPEViBH == aPMPEViBH- 1 ) aPMPEViBH=1519956653; else aPMPEViBH=634357239;long TdfZLhZOx=503633154;if (TdfZLhZOx == TdfZLhZOx- 1 ) TdfZLhZOx=1974439410; else TdfZLhZOx=567135797;if (TdfZLhZOx == TdfZLhZOx- 0 ) TdfZLhZOx=161149088; else TdfZLhZOx=1002164900;if (TdfZLhZOx == TdfZLhZOx- 1 ) TdfZLhZOx=358950659; else TdfZLhZOx=1277598428;if (TdfZLhZOx == TdfZLhZOx- 0 ) TdfZLhZOx=1201086037; else TdfZLhZOx=1295640330;if (TdfZLhZOx == TdfZLhZOx- 1 ) TdfZLhZOx=1222908232; else TdfZLhZOx=1423529099;if (TdfZLhZOx == TdfZLhZOx- 0 ) TdfZLhZOx=557792370; else TdfZLhZOx=284583728;long mfdxbbbwm=347778788;if (mfdxbbbwm == mfdxbbbwm- 1 ) mfdxbbbwm=705300213; else mfdxbbbwm=2128965492;if (mfdxbbbwm == mfdxbbbwm- 0 ) mfdxbbbwm=1989111136; else mfdxbbbwm=5464579;if (mfdxbbbwm == mfdxbbbwm- 1 ) mfdxbbbwm=1955537659; else mfdxbbbwm=1714091788;if (mfdxbbbwm == mfdxbbbwm- 0 ) mfdxbbbwm=58231531; else mfdxbbbwm=1325484908;if (mfdxbbbwm == mfdxbbbwm- 1 ) mfdxbbbwm=1700645702; else mfdxbbbwm=1729208265;if (mfdxbbbwm == mfdxbbbwm- 1 ) mfdxbbbwm=382689085; else mfdxbbbwm=1565951840;double UvIPAyRsH=672273654.7214739;if (UvIPAyRsH == UvIPAyRsH ) UvIPAyRsH=1152692837.6691902; else UvIPAyRsH=2008839184.7123235;if (UvIPAyRsH == UvIPAyRsH ) UvIPAyRsH=1078398309.5198582; else UvIPAyRsH=1001834552.7656890;if (UvIPAyRsH == UvIPAyRsH ) UvIPAyRsH=679063870.9439675; else UvIPAyRsH=1309713314.6858216;if (UvIPAyRsH == UvIPAyRsH ) UvIPAyRsH=1735547274.8927712; else UvIPAyRsH=579846275.1273689;if (UvIPAyRsH == UvIPAyRsH ) UvIPAyRsH=1979962124.0561238; else UvIPAyRsH=435929141.7947700;if (UvIPAyRsH == UvIPAyRsH ) UvIPAyRsH=642073476.3404769; else UvIPAyRsH=526794608.8301888; }
 UvIPAyRsHy::UvIPAyRsHy()
 { this->hdeCNMrAUoza("nxMsXjHOKhdeCNMrAUozaj", true, 1538177522, 1981300877, 892130156); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class oLptmEljDy
 { 
public: bool xeUSBelfk; double xeUSBelfkoLptmEljD; oLptmEljDy(); void IyPjqBVZKbQo(string xeUSBelfkIyPjqBVZKbQo, bool RggNZKwCQ, int KtggpYApA, float zghbFeToU, long EqwfKDquh);
 protected: bool xeUSBelfko; double xeUSBelfkoLptmEljDf; void IyPjqBVZKbQou(string xeUSBelfkIyPjqBVZKbQog, bool RggNZKwCQe, int KtggpYApAr, float zghbFeToUw, long EqwfKDquhn);
 private: bool xeUSBelfkRggNZKwCQ; double xeUSBelfkzghbFeToUoLptmEljD;
 void IyPjqBVZKbQov(string RggNZKwCQIyPjqBVZKbQo, bool RggNZKwCQKtggpYApA, int KtggpYApAxeUSBelfk, float zghbFeToUEqwfKDquh, long EqwfKDquhRggNZKwCQ); };
 void oLptmEljDy::IyPjqBVZKbQo(string xeUSBelfkIyPjqBVZKbQo, bool RggNZKwCQ, int KtggpYApA, float zghbFeToU, long EqwfKDquh)
 { long VJszqASqE=156335034;if (VJszqASqE == VJszqASqE- 1 ) VJszqASqE=1123031866; else VJszqASqE=478409744;if (VJszqASqE == VJszqASqE- 1 ) VJszqASqE=925040310; else VJszqASqE=1331754869;if (VJszqASqE == VJszqASqE- 0 ) VJszqASqE=520644067; else VJszqASqE=335483505;if (VJszqASqE == VJszqASqE- 0 ) VJszqASqE=2093746410; else VJszqASqE=538798772;if (VJszqASqE == VJszqASqE- 0 ) VJszqASqE=1981387288; else VJszqASqE=1394257197;if (VJszqASqE == VJszqASqE- 1 ) VJszqASqE=869006695; else VJszqASqE=960614254;int wqlEeZcvz=827791345;if (wqlEeZcvz == wqlEeZcvz- 0 ) wqlEeZcvz=27504303; else wqlEeZcvz=427729906;if (wqlEeZcvz == wqlEeZcvz- 0 ) wqlEeZcvz=431435633; else wqlEeZcvz=722648176;if (wqlEeZcvz == wqlEeZcvz- 0 ) wqlEeZcvz=1932083817; else wqlEeZcvz=366147429;if (wqlEeZcvz == wqlEeZcvz- 1 ) wqlEeZcvz=1144013143; else wqlEeZcvz=1659182160;if (wqlEeZcvz == wqlEeZcvz- 0 ) wqlEeZcvz=511863232; else wqlEeZcvz=109031765;if (wqlEeZcvz == wqlEeZcvz- 0 ) wqlEeZcvz=727273833; else wqlEeZcvz=1018162325;long NSsNddCPp=1582242529;if (NSsNddCPp == NSsNddCPp- 1 ) NSsNddCPp=2008347665; else NSsNddCPp=654528730;if (NSsNddCPp == NSsNddCPp- 1 ) NSsNddCPp=1258411517; else NSsNddCPp=1804648706;if (NSsNddCPp == NSsNddCPp- 0 ) NSsNddCPp=1608320415; else NSsNddCPp=1607360756;if (NSsNddCPp == NSsNddCPp- 0 ) NSsNddCPp=36309916; else NSsNddCPp=623734503;if (NSsNddCPp == NSsNddCPp- 0 ) NSsNddCPp=157562360; else NSsNddCPp=1408114007;if (NSsNddCPp == NSsNddCPp- 0 ) NSsNddCPp=528086501; else NSsNddCPp=544724793;float SpPXItgtP=1838654203.9126125f;if (SpPXItgtP - SpPXItgtP> 0.00000001 ) SpPXItgtP=1374361298.4872671f; else SpPXItgtP=1578544801.9474652f;if (SpPXItgtP - SpPXItgtP> 0.00000001 ) SpPXItgtP=2091717807.9841489f; else SpPXItgtP=683426426.0124657f;if (SpPXItgtP - SpPXItgtP> 0.00000001 ) SpPXItgtP=1623712431.8736733f; else SpPXItgtP=2023234817.8640474f;if (SpPXItgtP - SpPXItgtP> 0.00000001 ) SpPXItgtP=371734864.2903420f; else SpPXItgtP=756884437.4968474f;if (SpPXItgtP - SpPXItgtP> 0.00000001 ) SpPXItgtP=1481880248.8681352f; else SpPXItgtP=1413341797.8489201f;if (SpPXItgtP - SpPXItgtP> 0.00000001 ) SpPXItgtP=819891637.2010259f; else SpPXItgtP=411612302.2222474f;float nsQhrBygy=1907971186.5938918f;if (nsQhrBygy - nsQhrBygy> 0.00000001 ) nsQhrBygy=1565357610.1640302f; else nsQhrBygy=1434247813.9591906f;if (nsQhrBygy - nsQhrBygy> 0.00000001 ) nsQhrBygy=1099750236.1395197f; else nsQhrBygy=1423082715.7416570f;if (nsQhrBygy - nsQhrBygy> 0.00000001 ) nsQhrBygy=1745722645.9711112f; else nsQhrBygy=309614435.4119527f;if (nsQhrBygy - nsQhrBygy> 0.00000001 ) nsQhrBygy=1366954577.2214605f; else nsQhrBygy=567627194.6539325f;if (nsQhrBygy - nsQhrBygy> 0.00000001 ) nsQhrBygy=391419990.3348421f; else nsQhrBygy=1955184777.8818948f;if (nsQhrBygy - nsQhrBygy> 0.00000001 ) nsQhrBygy=565085816.3876805f; else nsQhrBygy=523969810.2030763f;float oLptmEljD=1098408183.0436801f;if (oLptmEljD - oLptmEljD> 0.00000001 ) oLptmEljD=1297654861.8619889f; else oLptmEljD=1036103277.3467690f;if (oLptmEljD - oLptmEljD> 0.00000001 ) oLptmEljD=1791284674.9998497f; else oLptmEljD=496152887.2749572f;if (oLptmEljD - oLptmEljD> 0.00000001 ) oLptmEljD=129181942.5815181f; else oLptmEljD=1292956808.2216908f;if (oLptmEljD - oLptmEljD> 0.00000001 ) oLptmEljD=2106013745.1060691f; else oLptmEljD=2132596495.5595257f;if (oLptmEljD - oLptmEljD> 0.00000001 ) oLptmEljD=282793866.9713278f; else oLptmEljD=501527080.7635197f;if (oLptmEljD - oLptmEljD> 0.00000001 ) oLptmEljD=322768458.8825992f; else oLptmEljD=194978618.8990810f; }
 oLptmEljDy::oLptmEljDy()
 { this->IyPjqBVZKbQo("xeUSBelfkIyPjqBVZKbQoj", true, 787469119, 1772181261, 1015524831); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class liLLaCeTky
 { 
public: bool zSfQRXqzS; double zSfQRXqzSliLLaCeTk; liLLaCeTky(); void wjhEKNiWYCcJ(string zSfQRXqzSwjhEKNiWYCcJ, bool zypyeGQov, int wMVWJgDSn, float uVAVVaDpq, long HQqoPgUqX);
 protected: bool zSfQRXqzSo; double zSfQRXqzSliLLaCeTkf; void wjhEKNiWYCcJu(string zSfQRXqzSwjhEKNiWYCcJg, bool zypyeGQove, int wMVWJgDSnr, float uVAVVaDpqw, long HQqoPgUqXn);
 private: bool zSfQRXqzSzypyeGQov; double zSfQRXqzSuVAVVaDpqliLLaCeTk;
 void wjhEKNiWYCcJv(string zypyeGQovwjhEKNiWYCcJ, bool zypyeGQovwMVWJgDSn, int wMVWJgDSnzSfQRXqzS, float uVAVVaDpqHQqoPgUqX, long HQqoPgUqXzypyeGQov); };
 void liLLaCeTky::wjhEKNiWYCcJ(string zSfQRXqzSwjhEKNiWYCcJ, bool zypyeGQov, int wMVWJgDSn, float uVAVVaDpq, long HQqoPgUqX)
 { int xtzDMZKzi=1601243012;if (xtzDMZKzi == xtzDMZKzi- 0 ) xtzDMZKzi=1291768474; else xtzDMZKzi=1662060322;if (xtzDMZKzi == xtzDMZKzi- 0 ) xtzDMZKzi=1759501651; else xtzDMZKzi=1618235352;if (xtzDMZKzi == xtzDMZKzi- 1 ) xtzDMZKzi=1357933867; else xtzDMZKzi=124954568;if (xtzDMZKzi == xtzDMZKzi- 0 ) xtzDMZKzi=114954204; else xtzDMZKzi=1969899722;if (xtzDMZKzi == xtzDMZKzi- 0 ) xtzDMZKzi=2064826669; else xtzDMZKzi=1663705148;if (xtzDMZKzi == xtzDMZKzi- 1 ) xtzDMZKzi=1731490570; else xtzDMZKzi=1636226834;float DblOekjKA=233137130.9991555f;if (DblOekjKA - DblOekjKA> 0.00000001 ) DblOekjKA=197519692.8696419f; else DblOekjKA=1297153163.7897716f;if (DblOekjKA - DblOekjKA> 0.00000001 ) DblOekjKA=25185159.0148937f; else DblOekjKA=641568140.9635343f;if (DblOekjKA - DblOekjKA> 0.00000001 ) DblOekjKA=1385516540.2184674f; else DblOekjKA=1551950917.6674894f;if (DblOekjKA - DblOekjKA> 0.00000001 ) DblOekjKA=1343332022.3808460f; else DblOekjKA=1528293951.9537390f;if (DblOekjKA - DblOekjKA> 0.00000001 ) DblOekjKA=1988977459.1622765f; else DblOekjKA=1583086.8132435f;if (DblOekjKA - DblOekjKA> 0.00000001 ) DblOekjKA=2007651399.6851437f; else DblOekjKA=689247426.8479944f;float blQrTXBWK=2056781845.5228655f;if (blQrTXBWK - blQrTXBWK> 0.00000001 ) blQrTXBWK=1873377044.9477932f; else blQrTXBWK=410620729.3745252f;if (blQrTXBWK - blQrTXBWK> 0.00000001 ) blQrTXBWK=139814167.2944389f; else blQrTXBWK=50248645.7446178f;if (blQrTXBWK - blQrTXBWK> 0.00000001 ) blQrTXBWK=1542910966.0544242f; else blQrTXBWK=157499308.7166100f;if (blQrTXBWK - blQrTXBWK> 0.00000001 ) blQrTXBWK=1472974300.3753664f; else blQrTXBWK=1347000230.3944772f;if (blQrTXBWK - blQrTXBWK> 0.00000001 ) blQrTXBWK=1949885718.0418654f; else blQrTXBWK=1470447111.2010115f;if (blQrTXBWK - blQrTXBWK> 0.00000001 ) blQrTXBWK=1911875364.8992805f; else blQrTXBWK=1852964003.8945247f;long zCbnzlpZo=880956378;if (zCbnzlpZo == zCbnzlpZo- 0 ) zCbnzlpZo=1582675579; else zCbnzlpZo=215619501;if (zCbnzlpZo == zCbnzlpZo- 1 ) zCbnzlpZo=297195498; else zCbnzlpZo=294281539;if (zCbnzlpZo == zCbnzlpZo- 0 ) zCbnzlpZo=333095005; else zCbnzlpZo=54860281;if (zCbnzlpZo == zCbnzlpZo- 1 ) zCbnzlpZo=215726472; else zCbnzlpZo=1887301204;if (zCbnzlpZo == zCbnzlpZo- 0 ) zCbnzlpZo=318728300; else zCbnzlpZo=231207700;if (zCbnzlpZo == zCbnzlpZo- 1 ) zCbnzlpZo=1776741540; else zCbnzlpZo=1356350781;long fhaaiQNCy=777366810;if (fhaaiQNCy == fhaaiQNCy- 0 ) fhaaiQNCy=1740276574; else fhaaiQNCy=1822192372;if (fhaaiQNCy == fhaaiQNCy- 0 ) fhaaiQNCy=1910333437; else fhaaiQNCy=1656258164;if (fhaaiQNCy == fhaaiQNCy- 0 ) fhaaiQNCy=212783930; else fhaaiQNCy=1331263067;if (fhaaiQNCy == fhaaiQNCy- 1 ) fhaaiQNCy=837709811; else fhaaiQNCy=40020384;if (fhaaiQNCy == fhaaiQNCy- 1 ) fhaaiQNCy=1971662510; else fhaaiQNCy=825668576;if (fhaaiQNCy == fhaaiQNCy- 1 ) fhaaiQNCy=839166069; else fhaaiQNCy=2062553076;int liLLaCeTk=786396533;if (liLLaCeTk == liLLaCeTk- 1 ) liLLaCeTk=477855261; else liLLaCeTk=1126695021;if (liLLaCeTk == liLLaCeTk- 0 ) liLLaCeTk=1254055494; else liLLaCeTk=1459077003;if (liLLaCeTk == liLLaCeTk- 1 ) liLLaCeTk=990264361; else liLLaCeTk=1776630682;if (liLLaCeTk == liLLaCeTk- 1 ) liLLaCeTk=1723686840; else liLLaCeTk=1818516763;if (liLLaCeTk == liLLaCeTk- 1 ) liLLaCeTk=194894257; else liLLaCeTk=399996610;if (liLLaCeTk == liLLaCeTk- 1 ) liLLaCeTk=1879003992; else liLLaCeTk=1311703266; }
 liLLaCeTky::liLLaCeTky()
 { this->wjhEKNiWYCcJ("zSfQRXqzSwjhEKNiWYCcJj", true, 528241415, 116623519, 1082213414); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class QxhzKAYoly
 { 
public: bool kIwFgrdbB; double kIwFgrdbBQxhzKAYol; QxhzKAYoly(); void ghIBtJRSeNCU(string kIwFgrdbBghIBtJRSeNCU, bool TvkPYxQrH, int WHUhoBGZI, float odoSpLwFH, long ZLKKyWmDo);
 protected: bool kIwFgrdbBo; double kIwFgrdbBQxhzKAYolf; void ghIBtJRSeNCUu(string kIwFgrdbBghIBtJRSeNCUg, bool TvkPYxQrHe, int WHUhoBGZIr, float odoSpLwFHw, long ZLKKyWmDon);
 private: bool kIwFgrdbBTvkPYxQrH; double kIwFgrdbBodoSpLwFHQxhzKAYol;
 void ghIBtJRSeNCUv(string TvkPYxQrHghIBtJRSeNCU, bool TvkPYxQrHWHUhoBGZI, int WHUhoBGZIkIwFgrdbB, float odoSpLwFHZLKKyWmDo, long ZLKKyWmDoTvkPYxQrH); };
 void QxhzKAYoly::ghIBtJRSeNCU(string kIwFgrdbBghIBtJRSeNCU, bool TvkPYxQrH, int WHUhoBGZI, float odoSpLwFH, long ZLKKyWmDo)
 { long EiqgdWOsQ=1100120963;if (EiqgdWOsQ == EiqgdWOsQ- 1 ) EiqgdWOsQ=217991908; else EiqgdWOsQ=258531134;if (EiqgdWOsQ == EiqgdWOsQ- 1 ) EiqgdWOsQ=1229680993; else EiqgdWOsQ=1538133464;if (EiqgdWOsQ == EiqgdWOsQ- 1 ) EiqgdWOsQ=1405393804; else EiqgdWOsQ=311814810;if (EiqgdWOsQ == EiqgdWOsQ- 1 ) EiqgdWOsQ=1019835823; else EiqgdWOsQ=1267748003;if (EiqgdWOsQ == EiqgdWOsQ- 1 ) EiqgdWOsQ=1435292719; else EiqgdWOsQ=1645663674;if (EiqgdWOsQ == EiqgdWOsQ- 1 ) EiqgdWOsQ=1840585989; else EiqgdWOsQ=1712954691;long NdnGeLZzv=96581583;if (NdnGeLZzv == NdnGeLZzv- 1 ) NdnGeLZzv=497376911; else NdnGeLZzv=883765422;if (NdnGeLZzv == NdnGeLZzv- 0 ) NdnGeLZzv=1745471333; else NdnGeLZzv=2102253032;if (NdnGeLZzv == NdnGeLZzv- 1 ) NdnGeLZzv=1813238504; else NdnGeLZzv=361688058;if (NdnGeLZzv == NdnGeLZzv- 1 ) NdnGeLZzv=1541321406; else NdnGeLZzv=688896862;if (NdnGeLZzv == NdnGeLZzv- 0 ) NdnGeLZzv=1604807074; else NdnGeLZzv=627435396;if (NdnGeLZzv == NdnGeLZzv- 0 ) NdnGeLZzv=1847779733; else NdnGeLZzv=879318653;double QaqsXpOKB=1974768679.8217440;if (QaqsXpOKB == QaqsXpOKB ) QaqsXpOKB=1258404424.5944564; else QaqsXpOKB=412139200.7438420;if (QaqsXpOKB == QaqsXpOKB ) QaqsXpOKB=1655712340.8779383; else QaqsXpOKB=280180737.2270086;if (QaqsXpOKB == QaqsXpOKB ) QaqsXpOKB=1070149784.8344605; else QaqsXpOKB=1606608815.1634957;if (QaqsXpOKB == QaqsXpOKB ) QaqsXpOKB=588820905.5773420; else QaqsXpOKB=1195993973.6592783;if (QaqsXpOKB == QaqsXpOKB ) QaqsXpOKB=1884686330.7746990; else QaqsXpOKB=1393662013.1059367;if (QaqsXpOKB == QaqsXpOKB ) QaqsXpOKB=1698648277.1454478; else QaqsXpOKB=560350100.6086663;double ZMuKKXtur=1822539808.1415242;if (ZMuKKXtur == ZMuKKXtur ) ZMuKKXtur=72234309.3684621; else ZMuKKXtur=1396979370.5037500;if (ZMuKKXtur == ZMuKKXtur ) ZMuKKXtur=1442123021.6474060; else ZMuKKXtur=1446123356.1288405;if (ZMuKKXtur == ZMuKKXtur ) ZMuKKXtur=1275026152.5793525; else ZMuKKXtur=1183632827.3421089;if (ZMuKKXtur == ZMuKKXtur ) ZMuKKXtur=1434366106.2132416; else ZMuKKXtur=2003787497.0423923;if (ZMuKKXtur == ZMuKKXtur ) ZMuKKXtur=864693375.4062360; else ZMuKKXtur=540784131.4440854;if (ZMuKKXtur == ZMuKKXtur ) ZMuKKXtur=2080810037.1630919; else ZMuKKXtur=777958408.2661905;long lBkyMqSfw=276199393;if (lBkyMqSfw == lBkyMqSfw- 1 ) lBkyMqSfw=1542852147; else lBkyMqSfw=2013300957;if (lBkyMqSfw == lBkyMqSfw- 0 ) lBkyMqSfw=454550267; else lBkyMqSfw=752006899;if (lBkyMqSfw == lBkyMqSfw- 1 ) lBkyMqSfw=596572448; else lBkyMqSfw=270105065;if (lBkyMqSfw == lBkyMqSfw- 1 ) lBkyMqSfw=1173915446; else lBkyMqSfw=1038251743;if (lBkyMqSfw == lBkyMqSfw- 1 ) lBkyMqSfw=294944517; else lBkyMqSfw=549477360;if (lBkyMqSfw == lBkyMqSfw- 0 ) lBkyMqSfw=217566702; else lBkyMqSfw=419576491;long QxhzKAYol=185180146;if (QxhzKAYol == QxhzKAYol- 1 ) QxhzKAYol=2028748003; else QxhzKAYol=25239925;if (QxhzKAYol == QxhzKAYol- 1 ) QxhzKAYol=807084344; else QxhzKAYol=1419525851;if (QxhzKAYol == QxhzKAYol- 0 ) QxhzKAYol=1864453952; else QxhzKAYol=804171818;if (QxhzKAYol == QxhzKAYol- 1 ) QxhzKAYol=699742527; else QxhzKAYol=74771597;if (QxhzKAYol == QxhzKAYol- 1 ) QxhzKAYol=1125256741; else QxhzKAYol=1799408490;if (QxhzKAYol == QxhzKAYol- 1 ) QxhzKAYol=1562971009; else QxhzKAYol=529365653; }
 QxhzKAYoly::QxhzKAYoly()
 { this->ghIBtJRSeNCU("kIwFgrdbBghIBtJRSeNCUj", true, 1673282425, 1958346144, 584475249); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class unORpIGCCy
 { 
public: bool dtzMJWqPX; double dtzMJWqPXunORpIGCC; unORpIGCCy(); void utedBCYUCjJK(string dtzMJWqPXutedBCYUCjJK, bool QaAukooFi, int hziTjbOfD, float aoKQVlkfH, long LXXrPuzci);
 protected: bool dtzMJWqPXo; double dtzMJWqPXunORpIGCCf; void utedBCYUCjJKu(string dtzMJWqPXutedBCYUCjJKg, bool QaAukooFie, int hziTjbOfDr, float aoKQVlkfHw, long LXXrPuzcin);
 private: bool dtzMJWqPXQaAukooFi; double dtzMJWqPXaoKQVlkfHunORpIGCC;
 void utedBCYUCjJKv(string QaAukooFiutedBCYUCjJK, bool QaAukooFihziTjbOfD, int hziTjbOfDdtzMJWqPX, float aoKQVlkfHLXXrPuzci, long LXXrPuzciQaAukooFi); };
 void unORpIGCCy::utedBCYUCjJK(string dtzMJWqPXutedBCYUCjJK, bool QaAukooFi, int hziTjbOfD, float aoKQVlkfH, long LXXrPuzci)
 { float eZsczqPuM=1975954633.2959651f;if (eZsczqPuM - eZsczqPuM> 0.00000001 ) eZsczqPuM=1947330296.7107457f; else eZsczqPuM=607761240.7730625f;if (eZsczqPuM - eZsczqPuM> 0.00000001 ) eZsczqPuM=1955951675.2551206f; else eZsczqPuM=977485217.5301896f;if (eZsczqPuM - eZsczqPuM> 0.00000001 ) eZsczqPuM=1490724815.0426969f; else eZsczqPuM=135949685.7617017f;if (eZsczqPuM - eZsczqPuM> 0.00000001 ) eZsczqPuM=1866841802.2446640f; else eZsczqPuM=609690122.4184553f;if (eZsczqPuM - eZsczqPuM> 0.00000001 ) eZsczqPuM=1020469421.9167717f; else eZsczqPuM=2083557788.4248666f;if (eZsczqPuM - eZsczqPuM> 0.00000001 ) eZsczqPuM=894341108.0453003f; else eZsczqPuM=1791364155.9653667f;int UGSFgqZYz=548983909;if (UGSFgqZYz == UGSFgqZYz- 1 ) UGSFgqZYz=969055944; else UGSFgqZYz=1687729936;if (UGSFgqZYz == UGSFgqZYz- 0 ) UGSFgqZYz=898917304; else UGSFgqZYz=1145024643;if (UGSFgqZYz == UGSFgqZYz- 1 ) UGSFgqZYz=253706673; else UGSFgqZYz=1954391851;if (UGSFgqZYz == UGSFgqZYz- 0 ) UGSFgqZYz=473296023; else UGSFgqZYz=777016395;if (UGSFgqZYz == UGSFgqZYz- 0 ) UGSFgqZYz=595873207; else UGSFgqZYz=1776759576;if (UGSFgqZYz == UGSFgqZYz- 1 ) UGSFgqZYz=1873177161; else UGSFgqZYz=168718196;long EtuPfgeSz=960783123;if (EtuPfgeSz == EtuPfgeSz- 0 ) EtuPfgeSz=1929495387; else EtuPfgeSz=1300873409;if (EtuPfgeSz == EtuPfgeSz- 1 ) EtuPfgeSz=1682527601; else EtuPfgeSz=2113018469;if (EtuPfgeSz == EtuPfgeSz- 1 ) EtuPfgeSz=803587647; else EtuPfgeSz=1466514832;if (EtuPfgeSz == EtuPfgeSz- 0 ) EtuPfgeSz=1669938764; else EtuPfgeSz=436959646;if (EtuPfgeSz == EtuPfgeSz- 1 ) EtuPfgeSz=863467162; else EtuPfgeSz=985418874;if (EtuPfgeSz == EtuPfgeSz- 0 ) EtuPfgeSz=1892103026; else EtuPfgeSz=479398780;int NVVpgkYJQ=1554876597;if (NVVpgkYJQ == NVVpgkYJQ- 1 ) NVVpgkYJQ=462938972; else NVVpgkYJQ=733930238;if (NVVpgkYJQ == NVVpgkYJQ- 1 ) NVVpgkYJQ=2133486393; else NVVpgkYJQ=1249086762;if (NVVpgkYJQ == NVVpgkYJQ- 0 ) NVVpgkYJQ=1659404838; else NVVpgkYJQ=1875017480;if (NVVpgkYJQ == NVVpgkYJQ- 0 ) NVVpgkYJQ=1722247960; else NVVpgkYJQ=2140422092;if (NVVpgkYJQ == NVVpgkYJQ- 1 ) NVVpgkYJQ=134465217; else NVVpgkYJQ=1178935280;if (NVVpgkYJQ == NVVpgkYJQ- 1 ) NVVpgkYJQ=381612010; else NVVpgkYJQ=1861448886;int azSStWvOd=1937175001;if (azSStWvOd == azSStWvOd- 1 ) azSStWvOd=114534561; else azSStWvOd=2081041632;if (azSStWvOd == azSStWvOd- 0 ) azSStWvOd=2009352415; else azSStWvOd=412057791;if (azSStWvOd == azSStWvOd- 0 ) azSStWvOd=2040913835; else azSStWvOd=1917470595;if (azSStWvOd == azSStWvOd- 0 ) azSStWvOd=1892879909; else azSStWvOd=1650024759;if (azSStWvOd == azSStWvOd- 0 ) azSStWvOd=17791172; else azSStWvOd=461957658;if (azSStWvOd == azSStWvOd- 1 ) azSStWvOd=281557481; else azSStWvOd=1415771446;int unORpIGCC=2059181723;if (unORpIGCC == unORpIGCC- 0 ) unORpIGCC=346421381; else unORpIGCC=318300564;if (unORpIGCC == unORpIGCC- 1 ) unORpIGCC=1853262871; else unORpIGCC=1322242648;if (unORpIGCC == unORpIGCC- 1 ) unORpIGCC=1244775321; else unORpIGCC=719936465;if (unORpIGCC == unORpIGCC- 0 ) unORpIGCC=1448861932; else unORpIGCC=54477907;if (unORpIGCC == unORpIGCC- 0 ) unORpIGCC=1726109096; else unORpIGCC=1689589156;if (unORpIGCC == unORpIGCC- 1 ) unORpIGCC=1978553252; else unORpIGCC=1772136014; }
 unORpIGCCy::unORpIGCCy()
 { this->utedBCYUCjJK("dtzMJWqPXutedBCYUCjJKj", true, 1084902822, 1955973525, 26703475); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class yUpEmxgGoy
 { 
public: bool VVeCFQvkt; double VVeCFQvktyUpEmxgGo; yUpEmxgGoy(); void NWQUUyugoWVt(string VVeCFQvktNWQUUyugoWVt, bool FplxYkRzm, int aAWzcNiDu, float dKbYyRSzi, long dvyllIaYB);
 protected: bool VVeCFQvkto; double VVeCFQvktyUpEmxgGof; void NWQUUyugoWVtu(string VVeCFQvktNWQUUyugoWVtg, bool FplxYkRzme, int aAWzcNiDur, float dKbYyRSziw, long dvyllIaYBn);
 private: bool VVeCFQvktFplxYkRzm; double VVeCFQvktdKbYyRSziyUpEmxgGo;
 void NWQUUyugoWVtv(string FplxYkRzmNWQUUyugoWVt, bool FplxYkRzmaAWzcNiDu, int aAWzcNiDuVVeCFQvkt, float dKbYyRSzidvyllIaYB, long dvyllIaYBFplxYkRzm); };
 void yUpEmxgGoy::NWQUUyugoWVt(string VVeCFQvktNWQUUyugoWVt, bool FplxYkRzm, int aAWzcNiDu, float dKbYyRSzi, long dvyllIaYB)
 { long ghDOLGUxn=2006385296;if (ghDOLGUxn == ghDOLGUxn- 1 ) ghDOLGUxn=143315909; else ghDOLGUxn=413672877;if (ghDOLGUxn == ghDOLGUxn- 0 ) ghDOLGUxn=1309406169; else ghDOLGUxn=140745609;if (ghDOLGUxn == ghDOLGUxn- 0 ) ghDOLGUxn=447449383; else ghDOLGUxn=2138007493;if (ghDOLGUxn == ghDOLGUxn- 1 ) ghDOLGUxn=1470671009; else ghDOLGUxn=1947020581;if (ghDOLGUxn == ghDOLGUxn- 0 ) ghDOLGUxn=1008888597; else ghDOLGUxn=766167457;if (ghDOLGUxn == ghDOLGUxn- 1 ) ghDOLGUxn=331661062; else ghDOLGUxn=1575063083;int byLdzmzdk=1194160542;if (byLdzmzdk == byLdzmzdk- 0 ) byLdzmzdk=1440373692; else byLdzmzdk=1992611921;if (byLdzmzdk == byLdzmzdk- 0 ) byLdzmzdk=1772971403; else byLdzmzdk=655162903;if (byLdzmzdk == byLdzmzdk- 0 ) byLdzmzdk=1559292522; else byLdzmzdk=1939172823;if (byLdzmzdk == byLdzmzdk- 1 ) byLdzmzdk=127834095; else byLdzmzdk=1941945150;if (byLdzmzdk == byLdzmzdk- 1 ) byLdzmzdk=1295805070; else byLdzmzdk=652415992;if (byLdzmzdk == byLdzmzdk- 0 ) byLdzmzdk=1688099554; else byLdzmzdk=1719952743;long wYXYlBlsX=1087093367;if (wYXYlBlsX == wYXYlBlsX- 1 ) wYXYlBlsX=1027889321; else wYXYlBlsX=674892682;if (wYXYlBlsX == wYXYlBlsX- 1 ) wYXYlBlsX=1353943245; else wYXYlBlsX=1985904869;if (wYXYlBlsX == wYXYlBlsX- 1 ) wYXYlBlsX=1341697270; else wYXYlBlsX=924792528;if (wYXYlBlsX == wYXYlBlsX- 1 ) wYXYlBlsX=497851602; else wYXYlBlsX=1662171002;if (wYXYlBlsX == wYXYlBlsX- 1 ) wYXYlBlsX=821413351; else wYXYlBlsX=655933964;if (wYXYlBlsX == wYXYlBlsX- 1 ) wYXYlBlsX=562992264; else wYXYlBlsX=2135749703;int YiIoGwJXf=49032961;if (YiIoGwJXf == YiIoGwJXf- 1 ) YiIoGwJXf=944574034; else YiIoGwJXf=167177851;if (YiIoGwJXf == YiIoGwJXf- 1 ) YiIoGwJXf=2127161404; else YiIoGwJXf=385003414;if (YiIoGwJXf == YiIoGwJXf- 0 ) YiIoGwJXf=1897170537; else YiIoGwJXf=542217888;if (YiIoGwJXf == YiIoGwJXf- 1 ) YiIoGwJXf=447092774; else YiIoGwJXf=351626733;if (YiIoGwJXf == YiIoGwJXf- 1 ) YiIoGwJXf=285838782; else YiIoGwJXf=1514944666;if (YiIoGwJXf == YiIoGwJXf- 0 ) YiIoGwJXf=992424186; else YiIoGwJXf=1942517038;long UbIUbobUK=1221614210;if (UbIUbobUK == UbIUbobUK- 0 ) UbIUbobUK=1544359776; else UbIUbobUK=1392051342;if (UbIUbobUK == UbIUbobUK- 0 ) UbIUbobUK=547173762; else UbIUbobUK=1723870259;if (UbIUbobUK == UbIUbobUK- 1 ) UbIUbobUK=1678066717; else UbIUbobUK=1509474231;if (UbIUbobUK == UbIUbobUK- 1 ) UbIUbobUK=1999946919; else UbIUbobUK=515581164;if (UbIUbobUK == UbIUbobUK- 0 ) UbIUbobUK=1494760319; else UbIUbobUK=110800401;if (UbIUbobUK == UbIUbobUK- 1 ) UbIUbobUK=1981233199; else UbIUbobUK=903358558;double yUpEmxgGo=1228253729.4415454;if (yUpEmxgGo == yUpEmxgGo ) yUpEmxgGo=864765615.7947518; else yUpEmxgGo=1639066593.1883351;if (yUpEmxgGo == yUpEmxgGo ) yUpEmxgGo=775378709.3576296; else yUpEmxgGo=1858587403.6460683;if (yUpEmxgGo == yUpEmxgGo ) yUpEmxgGo=1955080277.6034729; else yUpEmxgGo=984287914.3999479;if (yUpEmxgGo == yUpEmxgGo ) yUpEmxgGo=1337406477.2952082; else yUpEmxgGo=485671433.0492781;if (yUpEmxgGo == yUpEmxgGo ) yUpEmxgGo=227799908.5970366; else yUpEmxgGo=1002316512.9507431;if (yUpEmxgGo == yUpEmxgGo ) yUpEmxgGo=1700066087.6989275; else yUpEmxgGo=1974236251.6187116; }
 yUpEmxgGoy::yUpEmxgGoy()
 { this->NWQUUyugoWVt("VVeCFQvktNWQUUyugoWVtj", true, 2079851989, 702818211, 1212263063); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class cZnTlgEXgy
 { 
public: bool FslbDwsdR; double FslbDwsdRcZnTlgEXg; cZnTlgEXgy(); void UjtvEqDNfsij(string FslbDwsdRUjtvEqDNfsij, bool mDIquYhpB, int KAJWINnKC, float SddKDVAjo, long gEvQrTnuC);
 protected: bool FslbDwsdRo; double FslbDwsdRcZnTlgEXgf; void UjtvEqDNfsiju(string FslbDwsdRUjtvEqDNfsijg, bool mDIquYhpBe, int KAJWINnKCr, float SddKDVAjow, long gEvQrTnuCn);
 private: bool FslbDwsdRmDIquYhpB; double FslbDwsdRSddKDVAjocZnTlgEXg;
 void UjtvEqDNfsijv(string mDIquYhpBUjtvEqDNfsij, bool mDIquYhpBKAJWINnKC, int KAJWINnKCFslbDwsdR, float SddKDVAjogEvQrTnuC, long gEvQrTnuCmDIquYhpB); };
 void cZnTlgEXgy::UjtvEqDNfsij(string FslbDwsdRUjtvEqDNfsij, bool mDIquYhpB, int KAJWINnKC, float SddKDVAjo, long gEvQrTnuC)
 { double LHpDKEeIX=1079016277.8213566;if (LHpDKEeIX == LHpDKEeIX ) LHpDKEeIX=37263212.8713969; else LHpDKEeIX=2050175929.4870304;if (LHpDKEeIX == LHpDKEeIX ) LHpDKEeIX=731188734.6428367; else LHpDKEeIX=1923570482.8206996;if (LHpDKEeIX == LHpDKEeIX ) LHpDKEeIX=1708846774.7725610; else LHpDKEeIX=2118563324.4843926;if (LHpDKEeIX == LHpDKEeIX ) LHpDKEeIX=170768085.5575103; else LHpDKEeIX=738906288.8062091;if (LHpDKEeIX == LHpDKEeIX ) LHpDKEeIX=1708772516.5170748; else LHpDKEeIX=793820895.1658942;if (LHpDKEeIX == LHpDKEeIX ) LHpDKEeIX=1258430412.7855513; else LHpDKEeIX=2024910934.7429949;float eSeKxvglN=1317232990.0017629f;if (eSeKxvglN - eSeKxvglN> 0.00000001 ) eSeKxvglN=64787582.1195169f; else eSeKxvglN=734787576.1626681f;if (eSeKxvglN - eSeKxvglN> 0.00000001 ) eSeKxvglN=926095390.9551332f; else eSeKxvglN=691252757.3929740f;if (eSeKxvglN - eSeKxvglN> 0.00000001 ) eSeKxvglN=1857332269.9281249f; else eSeKxvglN=1802052931.5831941f;if (eSeKxvglN - eSeKxvglN> 0.00000001 ) eSeKxvglN=682718270.3169292f; else eSeKxvglN=113858372.6663989f;if (eSeKxvglN - eSeKxvglN> 0.00000001 ) eSeKxvglN=341318735.2765303f; else eSeKxvglN=406292916.5464534f;if (eSeKxvglN - eSeKxvglN> 0.00000001 ) eSeKxvglN=1764100351.7315010f; else eSeKxvglN=1085072156.9605584f;long LmMdAODgh=998282492;if (LmMdAODgh == LmMdAODgh- 0 ) LmMdAODgh=509221046; else LmMdAODgh=932376651;if (LmMdAODgh == LmMdAODgh- 1 ) LmMdAODgh=1104572649; else LmMdAODgh=1713658713;if (LmMdAODgh == LmMdAODgh- 0 ) LmMdAODgh=1945185838; else LmMdAODgh=487952726;if (LmMdAODgh == LmMdAODgh- 0 ) LmMdAODgh=800537440; else LmMdAODgh=915368412;if (LmMdAODgh == LmMdAODgh- 1 ) LmMdAODgh=903313085; else LmMdAODgh=92147498;if (LmMdAODgh == LmMdAODgh- 0 ) LmMdAODgh=2065785443; else LmMdAODgh=1172365884;float LgJDVhmMf=1961133605.3270209f;if (LgJDVhmMf - LgJDVhmMf> 0.00000001 ) LgJDVhmMf=1881390675.8548334f; else LgJDVhmMf=589191867.6469713f;if (LgJDVhmMf - LgJDVhmMf> 0.00000001 ) LgJDVhmMf=366173366.4880887f; else LgJDVhmMf=2006855391.8119137f;if (LgJDVhmMf - LgJDVhmMf> 0.00000001 ) LgJDVhmMf=1222609740.5123605f; else LgJDVhmMf=91592044.3323981f;if (LgJDVhmMf - LgJDVhmMf> 0.00000001 ) LgJDVhmMf=1369167655.4254430f; else LgJDVhmMf=382693928.5904231f;if (LgJDVhmMf - LgJDVhmMf> 0.00000001 ) LgJDVhmMf=1367457659.5402081f; else LgJDVhmMf=617330362.4571182f;if (LgJDVhmMf - LgJDVhmMf> 0.00000001 ) LgJDVhmMf=1582251747.5770174f; else LgJDVhmMf=1302553858.9668171f;double GrVmYmwNJ=462991500.8516124;if (GrVmYmwNJ == GrVmYmwNJ ) GrVmYmwNJ=1355442256.4985002; else GrVmYmwNJ=260147920.5111330;if (GrVmYmwNJ == GrVmYmwNJ ) GrVmYmwNJ=1515689888.3554253; else GrVmYmwNJ=975391957.5581397;if (GrVmYmwNJ == GrVmYmwNJ ) GrVmYmwNJ=1018417833.7784557; else GrVmYmwNJ=2003560024.1204277;if (GrVmYmwNJ == GrVmYmwNJ ) GrVmYmwNJ=1519530799.1988696; else GrVmYmwNJ=1724318503.1629720;if (GrVmYmwNJ == GrVmYmwNJ ) GrVmYmwNJ=2081733783.5158269; else GrVmYmwNJ=10726978.4479832;if (GrVmYmwNJ == GrVmYmwNJ ) GrVmYmwNJ=1935423319.4611874; else GrVmYmwNJ=1765184771.7037027;float cZnTlgEXg=911001190.5899518f;if (cZnTlgEXg - cZnTlgEXg> 0.00000001 ) cZnTlgEXg=680144454.6089371f; else cZnTlgEXg=1950450393.8292973f;if (cZnTlgEXg - cZnTlgEXg> 0.00000001 ) cZnTlgEXg=1351165128.3462558f; else cZnTlgEXg=1088125066.2992122f;if (cZnTlgEXg - cZnTlgEXg> 0.00000001 ) cZnTlgEXg=879607650.4154404f; else cZnTlgEXg=1726490542.1797312f;if (cZnTlgEXg - cZnTlgEXg> 0.00000001 ) cZnTlgEXg=1923156399.0451053f; else cZnTlgEXg=417629002.5481614f;if (cZnTlgEXg - cZnTlgEXg> 0.00000001 ) cZnTlgEXg=1710692643.2072694f; else cZnTlgEXg=721878721.1595702f;if (cZnTlgEXg - cZnTlgEXg> 0.00000001 ) cZnTlgEXg=346201054.8763573f; else cZnTlgEXg=1327855476.5421809f; }
 cZnTlgEXgy::cZnTlgEXgy()
 { this->UjtvEqDNfsij("FslbDwsdRUjtvEqDNfsijj", true, 1053184626, 1645467229, 560905439); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class wHJlHoCMGy
 { 
public: bool NyyXKasBe; double NyyXKasBewHJlHoCMG; wHJlHoCMGy(); void UlLwRSIoOBGd(string NyyXKasBeUlLwRSIoOBGd, bool WzcVyoqWu, int YrFGVNPRm, float GstNHXGxN, long zgWJoqWCw);
 protected: bool NyyXKasBeo; double NyyXKasBewHJlHoCMGf; void UlLwRSIoOBGdu(string NyyXKasBeUlLwRSIoOBGdg, bool WzcVyoqWue, int YrFGVNPRmr, float GstNHXGxNw, long zgWJoqWCwn);
 private: bool NyyXKasBeWzcVyoqWu; double NyyXKasBeGstNHXGxNwHJlHoCMG;
 void UlLwRSIoOBGdv(string WzcVyoqWuUlLwRSIoOBGd, bool WzcVyoqWuYrFGVNPRm, int YrFGVNPRmNyyXKasBe, float GstNHXGxNzgWJoqWCw, long zgWJoqWCwWzcVyoqWu); };
 void wHJlHoCMGy::UlLwRSIoOBGd(string NyyXKasBeUlLwRSIoOBGd, bool WzcVyoqWu, int YrFGVNPRm, float GstNHXGxN, long zgWJoqWCw)
 { float UGeIgefzV=1348422156.9906157f;if (UGeIgefzV - UGeIgefzV> 0.00000001 ) UGeIgefzV=455338986.3125342f; else UGeIgefzV=1041371082.3208288f;if (UGeIgefzV - UGeIgefzV> 0.00000001 ) UGeIgefzV=1092760383.4548407f; else UGeIgefzV=176531306.7963989f;if (UGeIgefzV - UGeIgefzV> 0.00000001 ) UGeIgefzV=1718435637.7075238f; else UGeIgefzV=520665286.2560477f;if (UGeIgefzV - UGeIgefzV> 0.00000001 ) UGeIgefzV=1133525344.5942675f; else UGeIgefzV=2140144378.5798616f;if (UGeIgefzV - UGeIgefzV> 0.00000001 ) UGeIgefzV=864527918.3734647f; else UGeIgefzV=319843833.2341502f;if (UGeIgefzV - UGeIgefzV> 0.00000001 ) UGeIgefzV=275382484.1880413f; else UGeIgefzV=2099957188.0224253f;double nmeMFwnRb=591719586.4047980;if (nmeMFwnRb == nmeMFwnRb ) nmeMFwnRb=192822987.1595303; else nmeMFwnRb=1251531227.8419086;if (nmeMFwnRb == nmeMFwnRb ) nmeMFwnRb=918254493.5962026; else nmeMFwnRb=274883636.1389757;if (nmeMFwnRb == nmeMFwnRb ) nmeMFwnRb=2124824381.5844828; else nmeMFwnRb=2123790714.1862459;if (nmeMFwnRb == nmeMFwnRb ) nmeMFwnRb=2146722433.0274600; else nmeMFwnRb=494428308.2960751;if (nmeMFwnRb == nmeMFwnRb ) nmeMFwnRb=581911832.3266574; else nmeMFwnRb=508673380.6852785;if (nmeMFwnRb == nmeMFwnRb ) nmeMFwnRb=1418959591.1117772; else nmeMFwnRb=28331420.1262684;double oWHmoqjxf=1848241716.7423120;if (oWHmoqjxf == oWHmoqjxf ) oWHmoqjxf=755668490.6825371; else oWHmoqjxf=46679384.5293776;if (oWHmoqjxf == oWHmoqjxf ) oWHmoqjxf=1962070087.6899919; else oWHmoqjxf=340685177.8239852;if (oWHmoqjxf == oWHmoqjxf ) oWHmoqjxf=1266225611.3811248; else oWHmoqjxf=1378782076.4179503;if (oWHmoqjxf == oWHmoqjxf ) oWHmoqjxf=98596438.6103412; else oWHmoqjxf=1372390205.7343119;if (oWHmoqjxf == oWHmoqjxf ) oWHmoqjxf=1794133477.6076292; else oWHmoqjxf=346820441.5835492;if (oWHmoqjxf == oWHmoqjxf ) oWHmoqjxf=1445876516.7315273; else oWHmoqjxf=815573045.2375417;int ipDOwpHBS=1964480029;if (ipDOwpHBS == ipDOwpHBS- 0 ) ipDOwpHBS=617287119; else ipDOwpHBS=1467477074;if (ipDOwpHBS == ipDOwpHBS- 0 ) ipDOwpHBS=1964665040; else ipDOwpHBS=212608325;if (ipDOwpHBS == ipDOwpHBS- 0 ) ipDOwpHBS=574609681; else ipDOwpHBS=1657752479;if (ipDOwpHBS == ipDOwpHBS- 0 ) ipDOwpHBS=1371081422; else ipDOwpHBS=479031919;if (ipDOwpHBS == ipDOwpHBS- 1 ) ipDOwpHBS=1042132296; else ipDOwpHBS=598332075;if (ipDOwpHBS == ipDOwpHBS- 0 ) ipDOwpHBS=1742103121; else ipDOwpHBS=1209762257;float XsmhmsdgI=2094648356.3623182f;if (XsmhmsdgI - XsmhmsdgI> 0.00000001 ) XsmhmsdgI=241427341.9393895f; else XsmhmsdgI=574624415.1533360f;if (XsmhmsdgI - XsmhmsdgI> 0.00000001 ) XsmhmsdgI=1344288698.0982471f; else XsmhmsdgI=1654322182.2842493f;if (XsmhmsdgI - XsmhmsdgI> 0.00000001 ) XsmhmsdgI=341653482.3319480f; else XsmhmsdgI=381362125.3656259f;if (XsmhmsdgI - XsmhmsdgI> 0.00000001 ) XsmhmsdgI=1472977622.2775713f; else XsmhmsdgI=961524558.8427218f;if (XsmhmsdgI - XsmhmsdgI> 0.00000001 ) XsmhmsdgI=1152934789.6625029f; else XsmhmsdgI=1693347935.2350917f;if (XsmhmsdgI - XsmhmsdgI> 0.00000001 ) XsmhmsdgI=628233806.4463330f; else XsmhmsdgI=1778003940.1777915f;float wHJlHoCMG=2129534137.7298828f;if (wHJlHoCMG - wHJlHoCMG> 0.00000001 ) wHJlHoCMG=1169289314.2914169f; else wHJlHoCMG=1601963209.9531374f;if (wHJlHoCMG - wHJlHoCMG> 0.00000001 ) wHJlHoCMG=1558527948.4076266f; else wHJlHoCMG=1106305981.2421974f;if (wHJlHoCMG - wHJlHoCMG> 0.00000001 ) wHJlHoCMG=1100181816.5641789f; else wHJlHoCMG=2013291814.1453566f;if (wHJlHoCMG - wHJlHoCMG> 0.00000001 ) wHJlHoCMG=1273632035.7638534f; else wHJlHoCMG=1245399658.3336721f;if (wHJlHoCMG - wHJlHoCMG> 0.00000001 ) wHJlHoCMG=823081609.5032964f; else wHJlHoCMG=1483038168.0917063f;if (wHJlHoCMG - wHJlHoCMG> 0.00000001 ) wHJlHoCMG=1446036528.6338005f; else wHJlHoCMG=667893536.9044503f; }
 wHJlHoCMGy::wHJlHoCMGy()
 { this->UlLwRSIoOBGd("NyyXKasBeUlLwRSIoOBGdj", true, 1784162602, 1036317828, 123200863); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class XgovnUvrpy
 { 
public: bool YEriyXNqi; double YEriyXNqiXgovnUvrp; XgovnUvrpy(); void DfiNuItHVYgT(string YEriyXNqiDfiNuItHVYgT, bool MITBFhsLC, int kUirkiajB, float VVJPMZwRC, long zQoPZASkv);
 protected: bool YEriyXNqio; double YEriyXNqiXgovnUvrpf; void DfiNuItHVYgTu(string YEriyXNqiDfiNuItHVYgTg, bool MITBFhsLCe, int kUirkiajBr, float VVJPMZwRCw, long zQoPZASkvn);
 private: bool YEriyXNqiMITBFhsLC; double YEriyXNqiVVJPMZwRCXgovnUvrp;
 void DfiNuItHVYgTv(string MITBFhsLCDfiNuItHVYgT, bool MITBFhsLCkUirkiajB, int kUirkiajBYEriyXNqi, float VVJPMZwRCzQoPZASkv, long zQoPZASkvMITBFhsLC); };
 void XgovnUvrpy::DfiNuItHVYgT(string YEriyXNqiDfiNuItHVYgT, bool MITBFhsLC, int kUirkiajB, float VVJPMZwRC, long zQoPZASkv)
 { double kDgsySShi=76772179.3965590;if (kDgsySShi == kDgsySShi ) kDgsySShi=37193727.0233006; else kDgsySShi=1390601200.2855449;if (kDgsySShi == kDgsySShi ) kDgsySShi=1819031065.7560901; else kDgsySShi=1763366706.2041240;if (kDgsySShi == kDgsySShi ) kDgsySShi=1803766648.6907845; else kDgsySShi=344800161.8964977;if (kDgsySShi == kDgsySShi ) kDgsySShi=1980531323.5576906; else kDgsySShi=1482086497.4067008;if (kDgsySShi == kDgsySShi ) kDgsySShi=449704616.3938666; else kDgsySShi=757737947.0596140;if (kDgsySShi == kDgsySShi ) kDgsySShi=1476621250.7171358; else kDgsySShi=30883001.5764553;int UBtSjcyRb=1044121896;if (UBtSjcyRb == UBtSjcyRb- 0 ) UBtSjcyRb=664502020; else UBtSjcyRb=2055495741;if (UBtSjcyRb == UBtSjcyRb- 1 ) UBtSjcyRb=71700444; else UBtSjcyRb=1465138894;if (UBtSjcyRb == UBtSjcyRb- 0 ) UBtSjcyRb=565292550; else UBtSjcyRb=1569010860;if (UBtSjcyRb == UBtSjcyRb- 0 ) UBtSjcyRb=1078697038; else UBtSjcyRb=582547841;if (UBtSjcyRb == UBtSjcyRb- 0 ) UBtSjcyRb=1720461612; else UBtSjcyRb=1657997536;if (UBtSjcyRb == UBtSjcyRb- 1 ) UBtSjcyRb=1444357019; else UBtSjcyRb=1465214610;float DOpqWFkNU=834256160.0689872f;if (DOpqWFkNU - DOpqWFkNU> 0.00000001 ) DOpqWFkNU=1426759453.1165098f; else DOpqWFkNU=935413593.2141711f;if (DOpqWFkNU - DOpqWFkNU> 0.00000001 ) DOpqWFkNU=1988885348.8340575f; else DOpqWFkNU=26039250.4980646f;if (DOpqWFkNU - DOpqWFkNU> 0.00000001 ) DOpqWFkNU=999663474.2340129f; else DOpqWFkNU=1238688093.7699452f;if (DOpqWFkNU - DOpqWFkNU> 0.00000001 ) DOpqWFkNU=1179714297.7360653f; else DOpqWFkNU=613355898.3503178f;if (DOpqWFkNU - DOpqWFkNU> 0.00000001 ) DOpqWFkNU=772914309.2965520f; else DOpqWFkNU=2086060949.9027921f;if (DOpqWFkNU - DOpqWFkNU> 0.00000001 ) DOpqWFkNU=1639331269.8512237f; else DOpqWFkNU=734621725.6300030f;double WlBZHYkQX=1696816818.8818436;if (WlBZHYkQX == WlBZHYkQX ) WlBZHYkQX=1007991782.6939052; else WlBZHYkQX=804427958.4902087;if (WlBZHYkQX == WlBZHYkQX ) WlBZHYkQX=508544765.3095498; else WlBZHYkQX=15571731.0561692;if (WlBZHYkQX == WlBZHYkQX ) WlBZHYkQX=958988387.5800469; else WlBZHYkQX=201653489.1373606;if (WlBZHYkQX == WlBZHYkQX ) WlBZHYkQX=1658963276.2903756; else WlBZHYkQX=615666514.9330496;if (WlBZHYkQX == WlBZHYkQX ) WlBZHYkQX=311904162.5795709; else WlBZHYkQX=1236483224.2127393;if (WlBZHYkQX == WlBZHYkQX ) WlBZHYkQX=42905094.7228028; else WlBZHYkQX=145769112.6789477;double fAwhNfgrr=1608140313.5470817;if (fAwhNfgrr == fAwhNfgrr ) fAwhNfgrr=960593402.1985642; else fAwhNfgrr=642365090.1111517;if (fAwhNfgrr == fAwhNfgrr ) fAwhNfgrr=751607195.2043729; else fAwhNfgrr=1314373074.5611493;if (fAwhNfgrr == fAwhNfgrr ) fAwhNfgrr=1785994869.4428775; else fAwhNfgrr=2028727667.7730748;if (fAwhNfgrr == fAwhNfgrr ) fAwhNfgrr=44458422.6733603; else fAwhNfgrr=1573297574.5371087;if (fAwhNfgrr == fAwhNfgrr ) fAwhNfgrr=875781444.3852597; else fAwhNfgrr=1605828193.8049426;if (fAwhNfgrr == fAwhNfgrr ) fAwhNfgrr=692224585.3141929; else fAwhNfgrr=626715248.0888910;float XgovnUvrp=1856052063.2235945f;if (XgovnUvrp - XgovnUvrp> 0.00000001 ) XgovnUvrp=1634446291.0091879f; else XgovnUvrp=1895023848.0349751f;if (XgovnUvrp - XgovnUvrp> 0.00000001 ) XgovnUvrp=457222828.8514261f; else XgovnUvrp=1009022762.5115879f;if (XgovnUvrp - XgovnUvrp> 0.00000001 ) XgovnUvrp=480503185.2597798f; else XgovnUvrp=1929056461.1269713f;if (XgovnUvrp - XgovnUvrp> 0.00000001 ) XgovnUvrp=2022751420.7869245f; else XgovnUvrp=1225105964.8317956f;if (XgovnUvrp - XgovnUvrp> 0.00000001 ) XgovnUvrp=1423933964.9971018f; else XgovnUvrp=1373218834.8631738f;if (XgovnUvrp - XgovnUvrp> 0.00000001 ) XgovnUvrp=1861618735.3655589f; else XgovnUvrp=1910663897.4676445f; }
 XgovnUvrpy::XgovnUvrpy()
 { this->DfiNuItHVYgT("YEriyXNqiDfiNuItHVYgTj", true, 1195782999, 1033945185, 1712912756); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class oEjWWFVFmy
 { 
public: bool dmIXlHRTg; double dmIXlHRTgoEjWWFVFm; oEjWWFVFmy(); void LgesNMEnUxiz(string dmIXlHRTgLgesNMEnUxiz, bool HZcXFdItQ, int RRlvmNEYy, float EphrMlcek, long VfrNXbaVc);
 protected: bool dmIXlHRTgo; double dmIXlHRTgoEjWWFVFmf; void LgesNMEnUxizu(string dmIXlHRTgLgesNMEnUxizg, bool HZcXFdItQe, int RRlvmNEYyr, float EphrMlcekw, long VfrNXbaVcn);
 private: bool dmIXlHRTgHZcXFdItQ; double dmIXlHRTgEphrMlcekoEjWWFVFm;
 void LgesNMEnUxizv(string HZcXFdItQLgesNMEnUxiz, bool HZcXFdItQRRlvmNEYy, int RRlvmNEYydmIXlHRTg, float EphrMlcekVfrNXbaVc, long VfrNXbaVcHZcXFdItQ); };
 void oEjWWFVFmy::LgesNMEnUxiz(string dmIXlHRTgLgesNMEnUxiz, bool HZcXFdItQ, int RRlvmNEYy, float EphrMlcek, long VfrNXbaVc)
 { float wguDsQjQP=346178058.2299039f;if (wguDsQjQP - wguDsQjQP> 0.00000001 ) wguDsQjQP=455269501.9280774f; else wguDsQjQP=381796353.2979714f;if (wguDsQjQP - wguDsQjQP> 0.00000001 ) wguDsQjQP=33119067.6368192f; else wguDsQjQP=16327530.0536380f;if (wguDsQjQP - wguDsQjQP> 0.00000001 ) wguDsQjQP=1813355511.2915489f; else wguDsQjQP=894385770.3058227f;if (wguDsQjQP - wguDsQjQP> 0.00000001 ) wguDsQjQP=795804935.3141656f; else wguDsQjQP=735840940.9329579f;if (wguDsQjQP - wguDsQjQP> 0.00000001 ) wguDsQjQP=1752943665.7554051f; else wguDsQjQP=283760885.1643453f;if (wguDsQjQP - wguDsQjQP> 0.00000001 ) wguDsQjQP=493573322.3200757f; else wguDsQjQP=105929255.5058343f;float ygvCyhXBW=318608492.9036068f;if (ygvCyhXBW - ygvCyhXBW> 0.00000001 ) ygvCyhXBW=792537425.8172948f; else ygvCyhXBW=424755745.4651622f;if (ygvCyhXBW - ygvCyhXBW> 0.00000001 ) ygvCyhXBW=63859547.0812582f; else ygvCyhXBW=1048769773.0183406f;if (ygvCyhXBW - ygvCyhXBW> 0.00000001 ) ygvCyhXBW=832784662.0817729f; else ygvCyhXBW=1890748643.4273501f;if (ygvCyhXBW - ygvCyhXBW> 0.00000001 ) ygvCyhXBW=395217554.3790580f; else ygvCyhXBW=963117777.2246969f;if (ygvCyhXBW - ygvCyhXBW> 0.00000001 ) ygvCyhXBW=1961054709.1095424f; else ygvCyhXBW=1760378000.9449036f;if (ygvCyhXBW - ygvCyhXBW> 0.00000001 ) ygvCyhXBW=1099216259.7400817f; else ygvCyhXBW=408473874.5940279f;float jFsfDTOmn=1684215384.3622243f;if (jFsfDTOmn - jFsfDTOmn> 0.00000001 ) jFsfDTOmn=1673206897.2238220f; else jFsfDTOmn=49716326.5641642f;if (jFsfDTOmn - jFsfDTOmn> 0.00000001 ) jFsfDTOmn=698899139.5582334f; else jFsfDTOmn=800549361.1609720f;if (jFsfDTOmn - jFsfDTOmn> 0.00000001 ) jFsfDTOmn=320703247.7314302f; else jFsfDTOmn=2129517443.7187004f;if (jFsfDTOmn - jFsfDTOmn> 0.00000001 ) jFsfDTOmn=477773295.7824028f; else jFsfDTOmn=1070377691.2509202f;if (jFsfDTOmn - jFsfDTOmn> 0.00000001 ) jFsfDTOmn=1663734701.7396118f; else jFsfDTOmn=193250245.3384409f;if (jFsfDTOmn - jFsfDTOmn> 0.00000001 ) jFsfDTOmn=1019422342.4064414f; else jFsfDTOmn=377828886.8967036f;double IbFAEBpuF=1700163242.0529252;if (IbFAEBpuF == IbFAEBpuF ) IbFAEBpuF=1891371873.3491448; else IbFAEBpuF=1682713165.8008455;if (IbFAEBpuF == IbFAEBpuF ) IbFAEBpuF=2107036439.1320358; else IbFAEBpuF=368808312.2637321;if (IbFAEBpuF == IbFAEBpuF ) IbFAEBpuF=310988328.8460436; else IbFAEBpuF=1767813924.1009874;if (IbFAEBpuF == IbFAEBpuF ) IbFAEBpuF=1660877043.5655899; else IbFAEBpuF=712004505.2000041;if (IbFAEBpuF == IbFAEBpuF ) IbFAEBpuF=2134062446.9752370; else IbFAEBpuF=1217484937.7490301;if (IbFAEBpuF == IbFAEBpuF ) IbFAEBpuF=202756468.4315848; else IbFAEBpuF=52977511.0826327;int eyUrbKQbn=1092313522;if (eyUrbKQbn == eyUrbKQbn- 1 ) eyUrbKQbn=1994062134; else eyUrbKQbn=956841585;if (eyUrbKQbn == eyUrbKQbn- 0 ) eyUrbKQbn=580206005; else eyUrbKQbn=1993303299;if (eyUrbKQbn == eyUrbKQbn- 1 ) eyUrbKQbn=1109230518; else eyUrbKQbn=406529768;if (eyUrbKQbn == eyUrbKQbn- 1 ) eyUrbKQbn=2145388892; else eyUrbKQbn=810503629;if (eyUrbKQbn == eyUrbKQbn- 0 ) eyUrbKQbn=2094466097; else eyUrbKQbn=1140965503;if (eyUrbKQbn == eyUrbKQbn- 1 ) eyUrbKQbn=1532518719; else eyUrbKQbn=639534417;long oEjWWFVFm=927101363;if (oEjWWFVFm == oEjWWFVFm- 1 ) oEjWWFVFm=2123591151; else oEjWWFVFm=1546536664;if (oEjWWFVFm == oEjWWFVFm- 0 ) oEjWWFVFm=664585648; else oEjWWFVFm=1027203677;if (oEjWWFVFm == oEjWWFVFm- 0 ) oEjWWFVFm=701077351; else oEjWWFVFm=68374086;if (oEjWWFVFm == oEjWWFVFm- 0 ) oEjWWFVFm=1373227056; else oEjWWFVFm=2052876620;if (oEjWWFVFm == oEjWWFVFm- 0 ) oEjWWFVFm=536322930; else oEjWWFVFm=2134378281;if (oEjWWFVFm == oEjWWFVFm- 1 ) oEjWWFVFm=813970562; else oEjWWFVFm=1250701957; }
 oEjWWFVFmy::oEjWWFVFmy()
 { this->LgesNMEnUxiz("dmIXlHRTgLgesNMEnUxizj", true, 1926760975, 424795784, 1275208180); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class TBPnslOcky
 { 
public: bool OabWEPabb; double OabWEPabbTBPnslOck; TBPnslOcky(); void ancBXoZNdwaQ(string OabWEPabbancBXoZNdwaQ, bool IvsNmmVwp, int OHUoJnaja, float CzyAxXlDX, long wNDdByRvR);
 protected: bool OabWEPabbo; double OabWEPabbTBPnslOckf; void ancBXoZNdwaQu(string OabWEPabbancBXoZNdwaQg, bool IvsNmmVwpe, int OHUoJnajar, float CzyAxXlDXw, long wNDdByRvRn);
 private: bool OabWEPabbIvsNmmVwp; double OabWEPabbCzyAxXlDXTBPnslOck;
 void ancBXoZNdwaQv(string IvsNmmVwpancBXoZNdwaQ, bool IvsNmmVwpOHUoJnaja, int OHUoJnajaOabWEPabb, float CzyAxXlDXwNDdByRvR, long wNDdByRvRIvsNmmVwp); };
 void TBPnslOcky::ancBXoZNdwaQ(string OabWEPabbancBXoZNdwaQ, bool IvsNmmVwp, int OHUoJnaja, float CzyAxXlDX, long wNDdByRvR)
 { float OvKFxxOTx=1222011728.9611981f;if (OvKFxxOTx - OvKFxxOTx> 0.00000001 ) OvKFxxOTx=37124242.9238895f; else OvKFxxOTx=731026471.2298134f;if (OvKFxxOTx - OvKFxxOTx> 0.00000001 ) OvKFxxOTx=759389749.9481555f; else OvKFxxOTx=1603162930.3200967f;if (OvKFxxOTx - OvKFxxOTx> 0.00000001 ) OvKFxxOTx=1898686522.4318543f; else OvKFxxOTx=718520645.8476878f;if (OvKFxxOTx - OvKFxxOTx> 0.00000001 ) OvKFxxOTx=1642810914.8689180f; else OvKFxxOTx=77783059.3415467f;if (OvKFxxOTx - OvKFxxOTx> 0.00000001 ) OvKFxxOTx=1338120363.0480398f; else OvKFxxOTx=721654999.0806022f;if (OvKFxxOTx - OvKFxxOTx> 0.00000001 ) OvKFxxOTx=1694812088.0167875f; else OvKFxxOTx=184338715.7318872f;int EPElgnyvb=771010802;if (EPElgnyvb == EPElgnyvb- 1 ) EPElgnyvb=1264216458; else EPElgnyvb=1228720259;if (EPElgnyvb == EPElgnyvb- 0 ) EPElgnyvb=1364789145; else EPElgnyvb=91541384;if (EPElgnyvb == EPElgnyvb- 0 ) EPElgnyvb=1420736478; else EPElgnyvb=1335968789;if (EPElgnyvb == EPElgnyvb- 1 ) EPElgnyvb=1474675806; else EPElgnyvb=1051237310;if (EPElgnyvb == EPElgnyvb- 1 ) EPElgnyvb=952120842; else EPElgnyvb=762218509;if (EPElgnyvb == EPElgnyvb- 0 ) EPElgnyvb=1124613687; else EPElgnyvb=1845357064;double NFYcoSibh=670229828.8190340;if (NFYcoSibh == NFYcoSibh ) NFYcoSibh=196814213.4205986; else NFYcoSibh=938450535.2296311;if (NFYcoSibh == NFYcoSibh ) NFYcoSibh=725714400.1644812; else NFYcoSibh=485903434.8215029;if (NFYcoSibh == NFYcoSibh ) NFYcoSibh=54141110.9717477; else NFYcoSibh=1989423460.3280512;if (NFYcoSibh == NFYcoSibh ) NFYcoSibh=1558891154.9977847; else NFYcoSibh=311343384.5665497;if (NFYcoSibh == NFYcoSibh ) NFYcoSibh=642515533.1000783; else NFYcoSibh=1932490753.6809549;if (NFYcoSibh == NFYcoSibh ) NFYcoSibh=1212877095.5644009; else NFYcoSibh=296877566.3492825;double ZGzpBKIlD=1432500031.8991773;if (ZGzpBKIlD == ZGzpBKIlD ) ZGzpBKIlD=134592889.8297781; else ZGzpBKIlD=1019664049.8939146;if (ZGzpBKIlD == ZGzpBKIlD ) ZGzpBKIlD=650916164.6093813; else ZGzpBKIlD=171771718.7407129;if (ZGzpBKIlD == ZGzpBKIlD ) ZGzpBKIlD=695367034.2003216; else ZGzpBKIlD=311714934.0540326;if (ZGzpBKIlD == ZGzpBKIlD ) ZGzpBKIlD=1948758897.8359453; else ZGzpBKIlD=848639100.0080612;if (ZGzpBKIlD == ZGzpBKIlD ) ZGzpBKIlD=1403834312.8917636; else ZGzpBKIlD=1855636086.9470306;if (ZGzpBKIlD == ZGzpBKIlD ) ZGzpBKIlD=651042088.6645979; else ZGzpBKIlD=1136468013.1688873;long KPdCZIbON=605805479;if (KPdCZIbON == KPdCZIbON- 0 ) KPdCZIbON=565744548; else KPdCZIbON=1024582260;if (KPdCZIbON == KPdCZIbON- 1 ) KPdCZIbON=2135008149; else KPdCZIbON=1653354191;if (KPdCZIbON == KPdCZIbON- 1 ) KPdCZIbON=406088258; else KPdCZIbON=2053895310;if (KPdCZIbON == KPdCZIbON- 1 ) KPdCZIbON=716869692; else KPdCZIbON=1422276645;if (KPdCZIbON == KPdCZIbON- 1 ) KPdCZIbON=1817312752; else KPdCZIbON=1053445761;if (KPdCZIbON == KPdCZIbON- 0 ) KPdCZIbON=1596509498; else KPdCZIbON=1635729372;int TBPnslOck=653619289;if (TBPnslOck == TBPnslOck- 1 ) TBPnslOck=441264481; else TBPnslOck=1839597303;if (TBPnslOck == TBPnslOck- 1 ) TBPnslOck=1710764175; else TBPnslOck=929920458;if (TBPnslOck == TBPnslOck- 0 ) TBPnslOck=81398720; else TBPnslOck=2131622380;if (TBPnslOck == TBPnslOck- 1 ) TBPnslOck=2122346441; else TBPnslOck=2032582926;if (TBPnslOck == TBPnslOck- 0 ) TBPnslOck=1137175285; else TBPnslOck=2024558947;if (TBPnslOck == TBPnslOck- 1 ) TBPnslOck=1229552769; else TBPnslOck=345988671; }
 TBPnslOcky::TBPnslOcky()
 { this->ancBXoZNdwaQ("OabWEPabbancBXoZNdwaQj", true, 1338381372, 422423141, 717436426); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class qbBGyNhgZy
 { 
public: bool HDEgseQrQ; double HDEgseQrQqbBGyNhgZ; qbBGyNhgZy(); void xCjfYUOewnpe(string HDEgseQrQxCjfYUOewnpe, bool bysYSaatS, int BdhSZnwDU, float EmRajSIQH, long oCAAYjNzB);
 protected: bool HDEgseQrQo; double HDEgseQrQqbBGyNhgZf; void xCjfYUOewnpeu(string HDEgseQrQxCjfYUOewnpeg, bool bysYSaatSe, int BdhSZnwDUr, float EmRajSIQHw, long oCAAYjNzBn);
 private: bool HDEgseQrQbysYSaatS; double HDEgseQrQEmRajSIQHqbBGyNhgZ;
 void xCjfYUOewnpev(string bysYSaatSxCjfYUOewnpe, bool bysYSaatSBdhSZnwDU, int BdhSZnwDUHDEgseQrQ, float EmRajSIQHoCAAYjNzB, long oCAAYjNzBbysYSaatS); };
 void qbBGyNhgZy::xCjfYUOewnpe(string HDEgseQrQxCjfYUOewnpe, bool bysYSaatS, int BdhSZnwDU, float EmRajSIQH, long oCAAYjNzB)
 { int RJiGwoHeq=107370955;if (RJiGwoHeq == RJiGwoHeq- 1 ) RJiGwoHeq=973401928; else RJiGwoHeq=297877979;if (RJiGwoHeq == RJiGwoHeq- 0 ) RJiGwoHeq=1140892692; else RJiGwoHeq=43647702;if (RJiGwoHeq == RJiGwoHeq- 1 ) RJiGwoHeq=1131918368; else RJiGwoHeq=1187783513;if (RJiGwoHeq == RJiGwoHeq- 1 ) RJiGwoHeq=1644535146; else RJiGwoHeq=575097470;if (RJiGwoHeq == RJiGwoHeq- 0 ) RJiGwoHeq=387274732; else RJiGwoHeq=1638416618;if (RJiGwoHeq == RJiGwoHeq- 1 ) RJiGwoHeq=871403840; else RJiGwoHeq=1298653888;float vVRJVTUfY=1930504863.6589065f;if (vVRJVTUfY - vVRJVTUfY> 0.00000001 ) vVRJVTUfY=17388323.8730867f; else vVRJVTUfY=1485804623.6645846f;if (vVRJVTUfY - vVRJVTUfY> 0.00000001 ) vVRJVTUfY=1363823253.9218139f; else vVRJVTUfY=924012466.9804727f;if (vVRJVTUfY - vVRJVTUfY> 0.00000001 ) vVRJVTUfY=551000271.1676718f; else vVRJVTUfY=441465028.9913900f;if (vVRJVTUfY - vVRJVTUfY> 0.00000001 ) vVRJVTUfY=2048437222.1325777f; else vVRJVTUfY=1745069318.3829370f;if (vVRJVTUfY - vVRJVTUfY> 0.00000001 ) vVRJVTUfY=1115463438.0362406f; else vVRJVTUfY=870844107.1891391f;if (vVRJVTUfY - vVRJVTUfY> 0.00000001 ) vVRJVTUfY=1276423794.4063408f; else vVRJVTUfY=2072516674.5990608f;int ejVYnreWG=1298270224;if (ejVYnreWG == ejVYnreWG- 1 ) ejVYnreWG=922503793; else ejVYnreWG=1192183462;if (ejVYnreWG == ejVYnreWG- 0 ) ejVYnreWG=2044640476; else ejVYnreWG=613102747;if (ejVYnreWG == ejVYnreWG- 0 ) ejVYnreWG=516809578; else ejVYnreWG=1099186003;if (ejVYnreWG == ejVYnreWG- 1 ) ejVYnreWG=1371078738; else ejVYnreWG=348038535;if (ejVYnreWG == ejVYnreWG- 1 ) ejVYnreWG=1804388592; else ejVYnreWG=1465860772;if (ejVYnreWG == ejVYnreWG- 1 ) ejVYnreWG=845925079; else ejVYnreWG=1944547363;int IJGvfEUbl=1529340655;if (IJGvfEUbl == IJGvfEUbl- 1 ) IJGvfEUbl=1772928823; else IJGvfEUbl=2127369798;if (IJGvfEUbl == IJGvfEUbl- 0 ) IJGvfEUbl=1883796522; else IJGvfEUbl=1333470137;if (IJGvfEUbl == IJGvfEUbl- 0 ) IJGvfEUbl=1813515819; else IJGvfEUbl=1180650725;if (IJGvfEUbl == IJGvfEUbl- 0 ) IJGvfEUbl=1703854331; else IJGvfEUbl=531936900;if (IJGvfEUbl == IJGvfEUbl- 0 ) IJGvfEUbl=396924404; else IJGvfEUbl=1543307021;if (IJGvfEUbl == IJGvfEUbl- 0 ) IJGvfEUbl=1075667911; else IJGvfEUbl=261074261;int OCEVAdjGc=1936945125;if (OCEVAdjGc == OCEVAdjGc- 1 ) OCEVAdjGc=2136461099; else OCEVAdjGc=1720617263;if (OCEVAdjGc == OCEVAdjGc- 1 ) OCEVAdjGc=376150095; else OCEVAdjGc=427766609;if (OCEVAdjGc == OCEVAdjGc- 1 ) OCEVAdjGc=536568386; else OCEVAdjGc=741539710;if (OCEVAdjGc == OCEVAdjGc- 1 ) OCEVAdjGc=1413695285; else OCEVAdjGc=1065685967;if (OCEVAdjGc == OCEVAdjGc- 1 ) OCEVAdjGc=114725885; else OCEVAdjGc=1015784718;if (OCEVAdjGc == OCEVAdjGc- 1 ) OCEVAdjGc=1267107521; else OCEVAdjGc=1232623146;int qbBGyNhgZ=522307894;if (qbBGyNhgZ == qbBGyNhgZ- 0 ) qbBGyNhgZ=639413714; else qbBGyNhgZ=1894566786;if (qbBGyNhgZ == qbBGyNhgZ- 1 ) qbBGyNhgZ=299587851; else qbBGyNhgZ=1057866751;if (qbBGyNhgZ == qbBGyNhgZ- 1 ) qbBGyNhgZ=861500379; else qbBGyNhgZ=315969029;if (qbBGyNhgZ == qbBGyNhgZ- 0 ) qbBGyNhgZ=1632238052; else qbBGyNhgZ=1889336715;if (qbBGyNhgZ == qbBGyNhgZ- 0 ) qbBGyNhgZ=1635812778; else qbBGyNhgZ=1512703576;if (qbBGyNhgZ == qbBGyNhgZ- 0 ) qbBGyNhgZ=216178343; else qbBGyNhgZ=1120986204; }
 qbBGyNhgZy::qbBGyNhgZy()
 { this->xCjfYUOewnpe("HDEgseQrQxCjfYUOewnpej", true, 23518092, 1110004477, 436678816); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class AcWxUPMnyy
 { 
public: bool lFJjwbaWw; double lFJjwbaWwAcWxUPMny; AcWxUPMnyy(); void CCOlkVwUxqXS(string lFJjwbaWwCCOlkVwUxqXS, bool CjxaILktP, int SByNnPdPB, float qGzfCxaZm, long zBKhOcuSU);
 protected: bool lFJjwbaWwo; double lFJjwbaWwAcWxUPMnyf; void CCOlkVwUxqXSu(string lFJjwbaWwCCOlkVwUxqXSg, bool CjxaILktPe, int SByNnPdPBr, float qGzfCxaZmw, long zBKhOcuSUn);
 private: bool lFJjwbaWwCjxaILktP; double lFJjwbaWwqGzfCxaZmAcWxUPMny;
 void CCOlkVwUxqXSv(string CjxaILktPCCOlkVwUxqXS, bool CjxaILktPSByNnPdPB, int SByNnPdPBlFJjwbaWw, float qGzfCxaZmzBKhOcuSU, long zBKhOcuSUCjxaILktP); };
 void AcWxUPMnyy::CCOlkVwUxqXS(string lFJjwbaWwCCOlkVwUxqXS, bool CjxaILktP, int SByNnPdPB, float qGzfCxaZm, long zBKhOcuSU)
 { double JLEgZmHlJ=1514757337.2824636;if (JLEgZmHlJ == JLEgZmHlJ ) JLEgZmHlJ=1972502495.1532926; else JLEgZmHlJ=1856548910.8266989;if (JLEgZmHlJ == JLEgZmHlJ ) JLEgZmHlJ=1750438526.0630781; else JLEgZmHlJ=873845382.5922357;if (JLEgZmHlJ == JLEgZmHlJ ) JLEgZmHlJ=126514010.9619732; else JLEgZmHlJ=679632307.5556868;if (JLEgZmHlJ == JLEgZmHlJ ) JLEgZmHlJ=1190488713.1374843; else JLEgZmHlJ=1956521767.2050567;if (JLEgZmHlJ == JLEgZmHlJ ) JLEgZmHlJ=590404560.6206700; else JLEgZmHlJ=776961875.6683585;if (JLEgZmHlJ == JLEgZmHlJ ) JLEgZmHlJ=1400867141.2840344; else JLEgZmHlJ=1084034423.7596257;float eyHmZtQZC=1017155722.6821532f;if (eyHmZtQZC - eyHmZtQZC> 0.00000001 ) eyHmZtQZC=660527885.2982774f; else eyHmZtQZC=860555216.0146096f;if (eyHmZtQZC - eyHmZtQZC> 0.00000001 ) eyHmZtQZC=1818520796.5582317f; else eyHmZtQZC=163721092.2033604f;if (eyHmZtQZC - eyHmZtQZC> 0.00000001 ) eyHmZtQZC=2016815972.3580466f; else eyHmZtQZC=1061729005.7893991f;if (eyHmZtQZC - eyHmZtQZC> 0.00000001 ) eyHmZtQZC=436960527.7157311f; else eyHmZtQZC=1690031048.4593361f;if (eyHmZtQZC - eyHmZtQZC> 0.00000001 ) eyHmZtQZC=1190631819.0692817f; else eyHmZtQZC=269972393.7677409f;if (eyHmZtQZC - eyHmZtQZC> 0.00000001 ) eyHmZtQZC=1276615281.7095265f; else eyHmZtQZC=575595890.9873030f;float tjEychMzI=492608078.5895670f;if (tjEychMzI - tjEychMzI> 0.00000001 ) tjEychMzI=1306961310.3635883f; else tjEychMzI=1453418473.8966075f;if (tjEychMzI - tjEychMzI> 0.00000001 ) tjEychMzI=226973208.1826458f; else tjEychMzI=2088894787.0251379f;if (tjEychMzI - tjEychMzI> 0.00000001 ) tjEychMzI=1261118246.7228221f; else tjEychMzI=1115743856.1753488f;if (tjEychMzI - tjEychMzI> 0.00000001 ) tjEychMzI=16779183.6384525f; else tjEychMzI=965221821.0703333f;if (tjEychMzI - tjEychMzI> 0.00000001 ) tjEychMzI=806315001.4956142f; else tjEychMzI=804917821.8598651f;if (tjEychMzI - tjEychMzI> 0.00000001 ) tjEychMzI=2070979800.2841804f; else tjEychMzI=517593575.0779557f;float KZvwogrwg=961734025.6668400f;if (KZvwogrwg - KZvwogrwg> 0.00000001 ) KZvwogrwg=2008226171.6295104f; else KZvwogrwg=1863692057.3599807f;if (KZvwogrwg - KZvwogrwg> 0.00000001 ) KZvwogrwg=1423907382.9715082f; else KZvwogrwg=1267992025.7792110f;if (KZvwogrwg - KZvwogrwg> 0.00000001 ) KZvwogrwg=1493729057.7246914f; else KZvwogrwg=1557946887.3894761f;if (KZvwogrwg - KZvwogrwg> 0.00000001 ) KZvwogrwg=1645425012.3309567f; else KZvwogrwg=910773490.9535389f;if (KZvwogrwg - KZvwogrwg> 0.00000001 ) KZvwogrwg=1419588383.5131046f; else KZvwogrwg=60407478.3530047f;if (KZvwogrwg - KZvwogrwg> 0.00000001 ) KZvwogrwg=1830697210.0323324f; else KZvwogrwg=2004025264.5947549f;double DJfMVojeP=1236043712.4476943;if (DJfMVojeP == DJfMVojeP ) DJfMVojeP=187909508.7638902; else DJfMVojeP=908259063.5052399;if (DJfMVojeP == DJfMVojeP ) DJfMVojeP=1924556760.2527112; else DJfMVojeP=156397587.8092101;if (DJfMVojeP == DJfMVojeP ) DJfMVojeP=1234274137.3694913; else DJfMVojeP=894583231.9738883;if (DJfMVojeP == DJfMVojeP ) DJfMVojeP=1903521123.6381303; else DJfMVojeP=1692267676.9698419;if (DJfMVojeP == DJfMVojeP ) DJfMVojeP=843776033.6569012; else DJfMVojeP=853298975.4695863;if (DJfMVojeP == DJfMVojeP ) DJfMVojeP=1504889738.9903392; else DJfMVojeP=1211898151.8228094;double AcWxUPMny=19114217.9275740;if (AcWxUPMny == AcWxUPMny ) AcWxUPMny=72022231.5710758; else AcWxUPMny=314881256.9288545;if (AcWxUPMny == AcWxUPMny ) AcWxUPMny=714853366.0638156; else AcWxUPMny=1536479455.7708142;if (AcWxUPMny == AcWxUPMny ) AcWxUPMny=77937113.0626300; else AcWxUPMny=1468543989.8117306;if (AcWxUPMny == AcWxUPMny ) AcWxUPMny=1146362668.9734100; else AcWxUPMny=1896498070.7487948;if (AcWxUPMny == AcWxUPMny ) AcWxUPMny=1955477108.0137160; else AcWxUPMny=1463683365.6622552;if (AcWxUPMny == AcWxUPMny ) AcWxUPMny=669306404.5229519; else AcWxUPMny=1200710768.0840524; }
 AcWxUPMnyy::AcWxUPMnyy()
 { this->CCOlkVwUxqXS("lFJjwbaWwCCOlkVwUxqXSj", true, 1432530293, 160237566, 1562204795); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class kFEmoMmjTy
 { 
public: bool pgJIMRxYC; double pgJIMRxYCkFEmoMmjT; kFEmoMmjTy(); void QbyVVkaIRpaA(string pgJIMRxYCQbyVVkaIRpaA, bool wKTdGRSbL, int bCvOgdjbn, float NaDeHplUT, long qpAteGJpj);
 protected: bool pgJIMRxYCo; double pgJIMRxYCkFEmoMmjTf; void QbyVVkaIRpaAu(string pgJIMRxYCQbyVVkaIRpaAg, bool wKTdGRSbLe, int bCvOgdjbnr, float NaDeHplUTw, long qpAteGJpjn);
 private: bool pgJIMRxYCwKTdGRSbL; double pgJIMRxYCNaDeHplUTkFEmoMmjT;
 void QbyVVkaIRpaAv(string wKTdGRSbLQbyVVkaIRpaA, bool wKTdGRSbLbCvOgdjbn, int bCvOgdjbnpgJIMRxYC, float NaDeHplUTqpAteGJpj, long qpAteGJpjwKTdGRSbL); };
 void kFEmoMmjTy::QbyVVkaIRpaA(string pgJIMRxYCQbyVVkaIRpaA, bool wKTdGRSbL, int bCvOgdjbn, float NaDeHplUT, long qpAteGJpj)
 { long JGFZObwao=1013635288;if (JGFZObwao == JGFZObwao- 0 ) JGFZObwao=898725929; else JGFZObwao=453019722;if (JGFZObwao == JGFZObwao- 1 ) JGFZObwao=1220617868; else JGFZObwao=793743494;if (JGFZObwao == JGFZObwao- 0 ) JGFZObwao=173973947; else JGFZObwao=866492549;if (JGFZObwao == JGFZObwao- 1 ) JGFZObwao=2095370332; else JGFZObwao=1254370048;if (JGFZObwao == JGFZObwao- 0 ) JGFZObwao=2108354257; else JGFZObwao=758920401;if (JGFZObwao == JGFZObwao- 0 ) JGFZObwao=1509962560; else JGFZObwao=1160762280;long bhPWUcqXw=880600175;if (bhPWUcqXw == bhPWUcqXw- 0 ) bhPWUcqXw=960385104; else bhPWUcqXw=447167475;if (bhPWUcqXw == bhPWUcqXw- 0 ) bhPWUcqXw=1391323323; else bhPWUcqXw=1624405984;if (bhPWUcqXw == bhPWUcqXw- 0 ) bhPWUcqXw=297054289; else bhPWUcqXw=2018949793;if (bhPWUcqXw == bhPWUcqXw- 1 ) bhPWUcqXw=634949911; else bhPWUcqXw=850633959;if (bhPWUcqXw == bhPWUcqXw- 0 ) bhPWUcqXw=806461434; else bhPWUcqXw=895824703;if (bhPWUcqXw == bhPWUcqXw- 0 ) bhPWUcqXw=1116743615; else bhPWUcqXw=765667117;long HAmHRyLYL=410594912;if (HAmHRyLYL == HAmHRyLYL- 1 ) HAmHRyLYL=691988690; else HAmHRyLYL=1454936944;if (HAmHRyLYL == HAmHRyLYL- 1 ) HAmHRyLYL=1742871381; else HAmHRyLYL=171343232;if (HAmHRyLYL == HAmHRyLYL- 1 ) HAmHRyLYL=788357064; else HAmHRyLYL=417369716;if (HAmHRyLYL == HAmHRyLYL- 1 ) HAmHRyLYL=1280109435; else HAmHRyLYL=814215564;if (HAmHRyLYL == HAmHRyLYL- 0 ) HAmHRyLYL=741115613; else HAmHRyLYL=728132723;if (HAmHRyLYL == HAmHRyLYL- 1 ) HAmHRyLYL=1857752713; else HAmHRyLYL=1372463319;double aVHfCVoXd=1903317455.9808385;if (aVHfCVoXd == aVHfCVoXd ) aVHfCVoXd=497784901.4372039; else aVHfCVoXd=897568279.3054559;if (aVHfCVoXd == aVHfCVoXd ) aVHfCVoXd=421351258.5883817; else aVHfCVoXd=272350195.4187005;if (aVHfCVoXd == aVHfCVoXd ) aVHfCVoXd=288176557.9781535; else aVHfCVoXd=539235786.7632203;if (aVHfCVoXd == aVHfCVoXd ) aVHfCVoXd=716580999.4059715; else aVHfCVoXd=1027259783.0356881;if (aVHfCVoXd == aVHfCVoXd ) aVHfCVoXd=1965553458.3050455; else aVHfCVoXd=369983909.3840348;if (aVHfCVoXd == aVHfCVoXd ) aVHfCVoXd=2134765707.3617141; else aVHfCVoXd=1425632891.1494019;double OamYWYfoO=734876295.4937894;if (OamYWYfoO == OamYWYfoO ) OamYWYfoO=2137968728.1172291; else OamYWYfoO=1099367648.4478315;if (OamYWYfoO == OamYWYfoO ) OamYWYfoO=468773590.1632760; else OamYWYfoO=1399629969.7624646;if (OamYWYfoO == OamYWYfoO ) OamYWYfoO=1618062655.0032412; else OamYWYfoO=1980908876.8350340;if (OamYWYfoO == OamYWYfoO ) OamYWYfoO=92243111.7692084; else OamYWYfoO=543015388.3161444;if (OamYWYfoO == OamYWYfoO ) OamYWYfoO=1314541687.5586664; else OamYWYfoO=577107759.5479133;if (OamYWYfoO == OamYWYfoO ) OamYWYfoO=883290371.4925201; else OamYWYfoO=1716405213.0336638;long kFEmoMmjT=1565381477;if (kFEmoMmjT == kFEmoMmjT- 1 ) kFEmoMmjT=1622914973; else kFEmoMmjT=1360909807;if (kFEmoMmjT == kFEmoMmjT- 0 ) kFEmoMmjT=267882216; else kFEmoMmjT=1496928303;if (kFEmoMmjT == kFEmoMmjT- 1 ) kFEmoMmjT=952126704; else kFEmoMmjT=496085125;if (kFEmoMmjT == kFEmoMmjT- 1 ) kFEmoMmjT=122418355; else kFEmoMmjT=152752904;if (kFEmoMmjT == kFEmoMmjT- 1 ) kFEmoMmjT=738355945; else kFEmoMmjT=715611598;if (kFEmoMmjT == kFEmoMmjT- 1 ) kFEmoMmjT=353273421; else kFEmoMmjT=418373155; }
 kFEmoMmjTy::kFEmoMmjTy()
 { this->QbyVVkaIRpaA("pgJIMRxYCQbyVVkaIRpaAj", true, 430087656, 2001960191, 1064466630); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class OrVsuAapfy
 { 
public: bool sQcroceWG; double sQcroceWGOrVsuAapf; OrVsuAapfy(); void xXgHzXIXdxqE(string sQcroceWGxXgHzXIXdxqE, bool PBRTpkudR, int RBwCLGiRA, float EBLWTKTVZ, long tRMObblox);
 protected: bool sQcroceWGo; double sQcroceWGOrVsuAapff; void xXgHzXIXdxqEu(string sQcroceWGxXgHzXIXdxqEg, bool PBRTpkudRe, int RBwCLGiRAr, float EBLWTKTVZw, long tRMObbloxn);
 private: bool sQcroceWGPBRTpkudR; double sQcroceWGEBLWTKTVZOrVsuAapf;
 void xXgHzXIXdxqEv(string PBRTpkudRxXgHzXIXdxqE, bool PBRTpkudRRBwCLGiRA, int RBwCLGiRAsQcroceWG, float EBLWTKTVZtRMObblox, long tRMObbloxPBRTpkudR); };
 void OrVsuAapfy::xXgHzXIXdxqE(string sQcroceWGxXgHzXIXdxqE, bool PBRTpkudR, int RBwCLGiRA, float EBLWTKTVZ, long tRMObblox)
 { int eKCrYvQFw=512513239;if (eKCrYvQFw == eKCrYvQFw- 0 ) eKCrYvQFw=1972433010; else eKCrYvQFw=1196974181;if (eKCrYvQFw == eKCrYvQFw- 0 ) eKCrYvQFw=690797210; else eKCrYvQFw=713641606;if (eKCrYvQFw == eKCrYvQFw- 1 ) eKCrYvQFw=221433884; else eKCrYvQFw=1053352791;if (eKCrYvQFw == eKCrYvQFw- 1 ) eKCrYvQFw=852768304; else eKCrYvQFw=552218329;if (eKCrYvQFw == eKCrYvQFw- 0 ) eKCrYvQFw=1478820307; else eKCrYvQFw=740878927;if (eKCrYvQFw == eKCrYvQFw- 0 ) eKCrYvQFw=1619057979; else eKCrYvQFw=1237490137;double tSpqHmQHc=744044628.5176901;if (tSpqHmQHc == tSpqHmQHc ) tSpqHmQHc=1260242323.7523428; else tSpqHmQHc=33779734.3151384;if (tSpqHmQHc == tSpqHmQHc ) tSpqHmQHc=964125850.3075220; else tSpqHmQHc=937607229.5497491;if (tSpqHmQHc == tSpqHmQHc ) tSpqHmQHc=724776253.7238243; else tSpqHmQHc=828686934.8072018;if (tSpqHmQHc == tSpqHmQHc ) tSpqHmQHc=832939295.4573043; else tSpqHmQHc=11236870.1128822;if (tSpqHmQHc == tSpqHmQHc ) tSpqHmQHc=422291049.1470376; else tSpqHmQHc=1521677013.0331425;if (tSpqHmQHc == tSpqHmQHc ) tSpqHmQHc=956871949.0032232; else tSpqHmQHc=955738344.9255596;long DBWNDihBK=328581746;if (DBWNDihBK == DBWNDihBK- 1 ) DBWNDihBK=77016070; else DBWNDihBK=1456455415;if (DBWNDihBK == DBWNDihBK- 0 ) DBWNDihBK=1111285907; else DBWNDihBK=401275324;if (DBWNDihBK == DBWNDihBK- 0 ) DBWNDihBK=315595882; else DBWNDihBK=1866479223;if (DBWNDihBK == DBWNDihBK- 0 ) DBWNDihBK=395956040; else DBWNDihBK=663209307;if (DBWNDihBK == DBWNDihBK- 0 ) DBWNDihBK=675916225; else DBWNDihBK=651347625;if (DBWNDihBK == DBWNDihBK- 0 ) DBWNDihBK=1644525626; else DBWNDihBK=79849416;double mHqLtpKhV=697417238.9006803;if (mHqLtpKhV == mHqLtpKhV ) mHqLtpKhV=1134827278.1681527; else mHqLtpKhV=2078928148.7554381;if (mHqLtpKhV == mHqLtpKhV ) mHqLtpKhV=1566278781.4980548; else mHqLtpKhV=1424192012.0731708;if (mHqLtpKhV == mHqLtpKhV ) mHqLtpKhV=1230107704.5966851; else mHqLtpKhV=1668008332.1219602;if (mHqLtpKhV == mHqLtpKhV ) mHqLtpKhV=1935220633.6759645; else mHqLtpKhV=1143746076.2263652;if (mHqLtpKhV == mHqLtpKhV ) mHqLtpKhV=364034886.0619202; else mHqLtpKhV=679560340.7095414;if (mHqLtpKhV == mHqLtpKhV ) mHqLtpKhV=291350557.8829474; else mHqLtpKhV=847240518.0831634;int wPGzpGdDB=233708878;if (wPGzpGdDB == wPGzpGdDB- 0 ) wPGzpGdDB=1940544301; else wPGzpGdDB=1290476233;if (wPGzpGdDB == wPGzpGdDB- 1 ) wPGzpGdDB=1160474067; else wPGzpGdDB=495378704;if (wPGzpGdDB == wPGzpGdDB- 0 ) wPGzpGdDB=2001851173; else wPGzpGdDB=919750874;if (wPGzpGdDB == wPGzpGdDB- 1 ) wPGzpGdDB=428448746; else wPGzpGdDB=1541246747;if (wPGzpGdDB == wPGzpGdDB- 1 ) wPGzpGdDB=1785307341; else wPGzpGdDB=300916543;if (wPGzpGdDB == wPGzpGdDB- 0 ) wPGzpGdDB=261691004; else wPGzpGdDB=73428628;double OrVsuAapf=964165090.5256650;if (OrVsuAapf == OrVsuAapf ) OrVsuAapf=1026324068.9720431; else OrVsuAapf=259454711.3216445;if (OrVsuAapf == OrVsuAapf ) OrVsuAapf=1968394713.2894018; else OrVsuAapf=1457377151.3075645;if (OrVsuAapf == OrVsuAapf ) OrVsuAapf=1826316295.2881290; else OrVsuAapf=1671109908.4953003;if (OrVsuAapf == OrVsuAapf ) OrVsuAapf=1245957689.1416573; else OrVsuAapf=556491385.5626426;if (OrVsuAapf == OrVsuAapf ) OrVsuAapf=1668718429.8668961; else OrVsuAapf=2115023478.4463669;if (OrVsuAapf == OrVsuAapf ) OrVsuAapf=37240438.0521163; else OrVsuAapf=1783519189.6692838; }
 OrVsuAapfy::OrVsuAapfy()
 { this->xXgHzXIXdxqE("sQcroceWGxXgHzXIXdxqEj", true, 1575128666, 1696199169, 566728465); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class gUYSsDdecy
 { 
public: bool xWXTxkuzL; double xWXTxkuzLgUYSsDdec; gUYSsDdecy(); void SRSNHIswoGDO(string xWXTxkuzLSRSNHIswoGDO, bool HmODFFlvl, int ioatIPqwz, float zYPmoYEnk, long TvpBaNmlv);
 protected: bool xWXTxkuzLo; double xWXTxkuzLgUYSsDdecf; void SRSNHIswoGDOu(string xWXTxkuzLSRSNHIswoGDOg, bool HmODFFlvle, int ioatIPqwzr, float zYPmoYEnkw, long TvpBaNmlvn);
 private: bool xWXTxkuzLHmODFFlvl; double xWXTxkuzLzYPmoYEnkgUYSsDdec;
 void SRSNHIswoGDOv(string HmODFFlvlSRSNHIswoGDO, bool HmODFFlvlioatIPqwz, int ioatIPqwzxWXTxkuzL, float zYPmoYEnkTvpBaNmlv, long TvpBaNmlvHmODFFlvl); };
 void gUYSsDdecy::SRSNHIswoGDO(string xWXTxkuzLSRSNHIswoGDO, bool HmODFFlvl, int ioatIPqwz, float zYPmoYEnk, long TvpBaNmlv)
 { float CDNiCKGgd=1388346909.3818366f;if (CDNiCKGgd - CDNiCKGgd> 0.00000001 ) CDNiCKGgd=1554287751.6294736f; else CDNiCKGgd=1546204299.6449447f;if (CDNiCKGgd - CDNiCKGgd> 0.00000001 ) CDNiCKGgd=1417067892.4058042f; else CDNiCKGgd=152993359.8583342f;if (CDNiCKGgd - CDNiCKGgd> 0.00000001 ) CDNiCKGgd=306764895.7882404f; else CDNiCKGgd=877487666.0333169f;if (CDNiCKGgd - CDNiCKGgd> 0.00000001 ) CDNiCKGgd=1699774283.6546219f; else CDNiCKGgd=2041644095.9704249f;if (CDNiCKGgd - CDNiCKGgd> 0.00000001 ) CDNiCKGgd=1063997005.8225050f; else CDNiCKGgd=1178773041.7780445f;if (CDNiCKGgd - CDNiCKGgd> 0.00000001 ) CDNiCKGgd=672813098.7369932f; else CDNiCKGgd=1315899597.0581439f;float mrLeaKHGp=1196446938.4088192f;if (mrLeaKHGp - mrLeaKHGp> 0.00000001 ) mrLeaKHGp=1731921356.7487684f; else mrLeaKHGp=837744248.7022145f;if (mrLeaKHGp - mrLeaKHGp> 0.00000001 ) mrLeaKHGp=117571801.9759409f; else mrLeaKHGp=2127862487.1434860f;if (mrLeaKHGp - mrLeaKHGp> 0.00000001 ) mrLeaKHGp=1312728069.2043871f; else mrLeaKHGp=273907080.3584869f;if (mrLeaKHGp - mrLeaKHGp> 0.00000001 ) mrLeaKHGp=1912397547.6645756f; else mrLeaKHGp=99356403.4308046f;if (mrLeaKHGp - mrLeaKHGp> 0.00000001 ) mrLeaKHGp=1560840829.1638355f; else mrLeaKHGp=523517522.0894846f;if (mrLeaKHGp - mrLeaKHGp> 0.00000001 ) mrLeaKHGp=982269377.2856506f; else mrLeaKHGp=245137887.8002149f;long VbnMaLwYe=1462079837;if (VbnMaLwYe == VbnMaLwYe- 0 ) VbnMaLwYe=748107033; else VbnMaLwYe=197705977;if (VbnMaLwYe == VbnMaLwYe- 0 ) VbnMaLwYe=1138101168; else VbnMaLwYe=86629397;if (VbnMaLwYe == VbnMaLwYe- 0 ) VbnMaLwYe=49033745; else VbnMaLwYe=1726385240;if (VbnMaLwYe == VbnMaLwYe- 1 ) VbnMaLwYe=1477073899; else VbnMaLwYe=2051658647;if (VbnMaLwYe == VbnMaLwYe- 0 ) VbnMaLwYe=1802180704; else VbnMaLwYe=243104486;if (VbnMaLwYe == VbnMaLwYe- 0 ) VbnMaLwYe=1837980379; else VbnMaLwYe=2146381743;long ySkGMnyVH=429754027;if (ySkGMnyVH == ySkGMnyVH- 1 ) ySkGMnyVH=1525531941; else ySkGMnyVH=1415879032;if (ySkGMnyVH == ySkGMnyVH- 0 ) ySkGMnyVH=110158506; else ySkGMnyVH=1227155418;if (ySkGMnyVH == ySkGMnyVH- 0 ) ySkGMnyVH=1614486410; else ySkGMnyVH=211909342;if (ySkGMnyVH == ySkGMnyVH- 0 ) ySkGMnyVH=75618840; else ySkGMnyVH=1280380671;if (ySkGMnyVH == ySkGMnyVH- 1 ) ySkGMnyVH=1781290399; else ySkGMnyVH=1317711489;if (ySkGMnyVH == ySkGMnyVH- 0 ) ySkGMnyVH=739636177; else ySkGMnyVH=1930731020;long mxmgRSlFZ=1894684482;if (mxmgRSlFZ == mxmgRSlFZ- 1 ) mxmgRSlFZ=512226715; else mxmgRSlFZ=1358216908;if (mxmgRSlFZ == mxmgRSlFZ- 1 ) mxmgRSlFZ=567792564; else mxmgRSlFZ=155429596;if (mxmgRSlFZ == mxmgRSlFZ- 0 ) mxmgRSlFZ=1298708913; else mxmgRSlFZ=419632769;if (mxmgRSlFZ == mxmgRSlFZ- 0 ) mxmgRSlFZ=1147413193; else mxmgRSlFZ=5536116;if (mxmgRSlFZ == mxmgRSlFZ- 1 ) mxmgRSlFZ=1508153996; else mxmgRSlFZ=213396801;if (mxmgRSlFZ == mxmgRSlFZ- 1 ) mxmgRSlFZ=325681783; else mxmgRSlFZ=1069623583;long gUYSsDdec=690683016;if (gUYSsDdec == gUYSsDdec- 0 ) gUYSsDdec=1491481045; else gUYSsDdec=552515350;if (gUYSsDdec == gUYSsDdec- 1 ) gUYSsDdec=867089593; else gUYSsDdec=1360093932;if (gUYSsDdec == gUYSsDdec- 0 ) gUYSsDdec=1206637664; else gUYSsDdec=1586874555;if (gUYSsDdec == gUYSsDdec- 1 ) gUYSsDdec=1995077074; else gUYSsDdec=536197691;if (gUYSsDdec == gUYSsDdec- 1 ) gUYSsDdec=122087137; else gUYSsDdec=2005204144;if (gUYSsDdec == gUYSsDdec- 1 ) gUYSsDdec=452822645; else gUYSsDdec=878805903; }
 gUYSsDdecy::gUYSsDdecy()
 { this->SRSNHIswoGDO("xWXTxkuzLSRSNHIswoGDOj", true, 986749063, 1693826526, 8956711); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class VZKfeCWXqy
 { 
public: bool rduQceLWp; double rduQceLWpVZKfeCWXq; VZKfeCWXqy(); void TvsiWEYmDDeA(string rduQceLWpTvsiWEYmDDeA, bool LDCeSwHyx, int kmLNduzCA, float IQGUKkMLp, long TWinWGlRC);
 protected: bool rduQceLWpo; double rduQceLWpVZKfeCWXqf; void TvsiWEYmDDeAu(string rduQceLWpTvsiWEYmDDeAg, bool LDCeSwHyxe, int kmLNduzCAr, float IQGUKkMLpw, long TWinWGlRCn);
 private: bool rduQceLWpLDCeSwHyx; double rduQceLWpIQGUKkMLpVZKfeCWXq;
 void TvsiWEYmDDeAv(string LDCeSwHyxTvsiWEYmDDeA, bool LDCeSwHyxkmLNduzCA, int kmLNduzCArduQceLWp, float IQGUKkMLpTWinWGlRC, long TWinWGlRCLDCeSwHyx); };
 void VZKfeCWXqy::TvsiWEYmDDeA(string rduQceLWpTvsiWEYmDDeA, bool LDCeSwHyx, int kmLNduzCA, float IQGUKkMLp, long TWinWGlRC)
 { float trUPGYvku=1957421217.4406692f;if (trUPGYvku - trUPGYvku> 0.00000001 ) trUPGYvku=2141169618.4507262f; else trUPGYvku=233141106.0446463f;if (trUPGYvku - trUPGYvku> 0.00000001 ) trUPGYvku=1525258551.7068004f; else trUPGYvku=1000122089.8652286f;if (trUPGYvku - trUPGYvku> 0.00000001 ) trUPGYvku=1058723684.7640421f; else trUPGYvku=842823854.3780605f;if (trUPGYvku - trUPGYvku> 0.00000001 ) trUPGYvku=1021459745.8242477f; else trUPGYvku=1983319279.5496086f;if (trUPGYvku - trUPGYvku> 0.00000001 ) trUPGYvku=1562259690.9661963f; else trUPGYvku=1010326878.8160425f;if (trUPGYvku - trUPGYvku> 0.00000001 ) trUPGYvku=334058207.4885101f; else trUPGYvku=1913102719.5109103f;long YVVSXQDLx=149390421;if (YVVSXQDLx == YVVSXQDLx- 0 ) YVVSXQDLx=1430257712; else YVVSXQDLx=903202991;if (YVVSXQDLx == YVVSXQDLx- 0 ) YVVSXQDLx=557875386; else YVVSXQDLx=856527193;if (YVVSXQDLx == YVVSXQDLx- 1 ) YVVSXQDLx=178208976; else YVVSXQDLx=2014490422;if (YVVSXQDLx == YVVSXQDLx- 1 ) YVVSXQDLx=1032258180; else YVVSXQDLx=2027832308;if (YVVSXQDLx == YVVSXQDLx- 1 ) YVVSXQDLx=1899405276; else YVVSXQDLx=1414228346;if (YVVSXQDLx == YVVSXQDLx- 1 ) YVVSXQDLx=89765868; else YVVSXQDLx=626823445;double uAPYMHZAP=803121062.5762183;if (uAPYMHZAP == uAPYMHZAP ) uAPYMHZAP=2089529096.5452793; else uAPYMHZAP=1212547414.3687750;if (uAPYMHZAP == uAPYMHZAP ) uAPYMHZAP=2140172204.7169118; else uAPYMHZAP=794358916.7952063;if (uAPYMHZAP == uAPYMHZAP ) uAPYMHZAP=250186433.7819825; else uAPYMHZAP=416617775.6996003;if (uAPYMHZAP == uAPYMHZAP ) uAPYMHZAP=1832620424.3321149; else uAPYMHZAP=1386475024.7041858;if (uAPYMHZAP == uAPYMHZAP ) uAPYMHZAP=320755936.5018317; else uAPYMHZAP=713680729.8889351;if (uAPYMHZAP == uAPYMHZAP ) uAPYMHZAP=880830840.2731155; else uAPYMHZAP=1388088626.7410351;long nqykjEurr=1887203060;if (nqykjEurr == nqykjEurr- 0 ) nqykjEurr=1343141559; else nqykjEurr=716002840;if (nqykjEurr == nqykjEurr- 1 ) nqykjEurr=1919240119; else nqykjEurr=1035047125;if (nqykjEurr == nqykjEurr- 0 ) nqykjEurr=2086973915; else nqykjEurr=1847117441;if (nqykjEurr == nqykjEurr- 0 ) nqykjEurr=1779212241; else nqykjEurr=126679196;if (nqykjEurr == nqykjEurr- 0 ) nqykjEurr=1348366573; else nqykjEurr=1644909890;if (nqykjEurr == nqykjEurr- 0 ) nqykjEurr=1248200460; else nqykjEurr=1791978985;float FdjahKTjl=1250588151.0593814f;if (FdjahKTjl - FdjahKTjl> 0.00000001 ) FdjahKTjl=2115463265.6352173f; else FdjahKTjl=1678420792.8942979f;if (FdjahKTjl - FdjahKTjl> 0.00000001 ) FdjahKTjl=1971057270.0528771f; else FdjahKTjl=728554153.2542796f;if (FdjahKTjl - FdjahKTjl> 0.00000001 ) FdjahKTjl=468912458.6907700f; else FdjahKTjl=1941399500.8653177f;if (FdjahKTjl - FdjahKTjl> 0.00000001 ) FdjahKTjl=2046687635.0818040f; else FdjahKTjl=1013639937.1862544f;if (FdjahKTjl - FdjahKTjl> 0.00000001 ) FdjahKTjl=1218066214.8215882f; else FdjahKTjl=1318884009.1463892f;if (FdjahKTjl - FdjahKTjl> 0.00000001 ) FdjahKTjl=535771257.9766143f; else FdjahKTjl=1612011894.8347666f;int VZKfeCWXq=652153442;if (VZKfeCWXq == VZKfeCWXq- 1 ) VZKfeCWXq=206524492; else VZKfeCWXq=350046455;if (VZKfeCWXq == VZKfeCWXq- 0 ) VZKfeCWXq=1431165533; else VZKfeCWXq=272817628;if (VZKfeCWXq == VZKfeCWXq- 1 ) VZKfeCWXq=539915067; else VZKfeCWXq=7300135;if (VZKfeCWXq == VZKfeCWXq- 1 ) VZKfeCWXq=863630794; else VZKfeCWXq=242411655;if (VZKfeCWXq == VZKfeCWXq- 0 ) VZKfeCWXq=1580818820; else VZKfeCWXq=2013493008;if (VZKfeCWXq == VZKfeCWXq- 0 ) VZKfeCWXq=1593475990; else VZKfeCWXq=752760190; }
 VZKfeCWXqy::VZKfeCWXqy()
 { this->TvsiWEYmDDeA("rduQceLWpTvsiWEYmDDeAj", true, 1315900962, 40641439, 633417038); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class QZRFvmamEy
 { 
public: bool CfKsdVXQo; double CfKsdVXQoQZRFvmamE; QZRFvmamEy(); void egwVRMUCWAja(string CfKsdVXQoegwVRMUCWAja, bool RkltUjeZG, int kizTEpHJI, float EaeyyirpO, long SBbABeyrl);
 protected: bool CfKsdVXQoo; double CfKsdVXQoQZRFvmamEf; void egwVRMUCWAjau(string CfKsdVXQoegwVRMUCWAjag, bool RkltUjeZGe, int kizTEpHJIr, float EaeyyirpOw, long SBbABeyrln);
 private: bool CfKsdVXQoRkltUjeZG; double CfKsdVXQoEaeyyirpOQZRFvmamE;
 void egwVRMUCWAjav(string RkltUjeZGegwVRMUCWAja, bool RkltUjeZGkizTEpHJI, int kizTEpHJICfKsdVXQo, float EaeyyirpOSBbABeyrl, long SBbABeyrlRkltUjeZG); };
 void QZRFvmamEy::egwVRMUCWAja(string CfKsdVXQoegwVRMUCWAja, bool RkltUjeZG, int kizTEpHJI, float EaeyyirpO, long SBbABeyrl)
 { long ncpCUArSQ=72252516;if (ncpCUArSQ == ncpCUArSQ- 1 ) ncpCUArSQ=1585594964; else ncpCUArSQ=1552751920;if (ncpCUArSQ == ncpCUArSQ- 0 ) ncpCUArSQ=1015369187; else ncpCUArSQ=1107544149;if (ncpCUArSQ == ncpCUArSQ- 1 ) ncpCUArSQ=329826604; else ncpCUArSQ=949361355;if (ncpCUArSQ == ncpCUArSQ- 0 ) ncpCUArSQ=965308337; else ncpCUArSQ=377243881;if (ncpCUArSQ == ncpCUArSQ- 0 ) ncpCUArSQ=826124707; else ncpCUArSQ=235540438;if (ncpCUArSQ == ncpCUArSQ- 1 ) ncpCUArSQ=602793306; else ncpCUArSQ=881615848;double KOhmojXDi=1897842339.4889868;if (KOhmojXDi == KOhmojXDi ) KOhmojXDi=355251391.4061872; else KOhmojXDi=230155963.0210174;if (KOhmojXDi == KOhmojXDi ) KOhmojXDi=137552918.4131784; else KOhmojXDi=1418568641.5402498;if (KOhmojXDi == KOhmojXDi ) KOhmojXDi=1616186268.2143075; else KOhmojXDi=1755469666.1576949;if (KOhmojXDi == KOhmojXDi ) KOhmojXDi=340004817.3894761; else KOhmojXDi=1501697291.8691940;if (KOhmojXDi == KOhmojXDi ) KOhmojXDi=1437984390.6695858; else KOhmojXDi=2046325790.1772093;if (KOhmojXDi == KOhmojXDi ) KOhmojXDi=426845069.7759463; else KOhmojXDi=2100795018.6297485;float eHESbcqoE=499189068.7271241f;if (eHESbcqoE - eHESbcqoE> 0.00000001 ) eHESbcqoE=1953798612.4105157f; else eHESbcqoE=206012432.6559971f;if (eHESbcqoE - eHESbcqoE> 0.00000001 ) eHESbcqoE=1970015368.9875162f; else eHESbcqoE=376980210.5212275f;if (eHESbcqoE - eHESbcqoE> 0.00000001 ) eHESbcqoE=919053946.3468490f; else eHESbcqoE=84660475.6456121f;if (eHESbcqoE - eHESbcqoE> 0.00000001 ) eHESbcqoE=1462595615.0358778f; else eHESbcqoE=815142125.4172900f;if (eHESbcqoE - eHESbcqoE> 0.00000001 ) eHESbcqoE=526609215.0930823f; else eHESbcqoE=2063076354.1916823f;if (eHESbcqoE - eHESbcqoE> 0.00000001 ) eHESbcqoE=920560664.5290415f; else eHESbcqoE=2099937359.9755170f;int yiZvxebJi=774797043;if (yiZvxebJi == yiZvxebJi- 0 ) yiZvxebJi=587656132; else yiZvxebJi=2126783251;if (yiZvxebJi == yiZvxebJi- 1 ) yiZvxebJi=551072679; else yiZvxebJi=847867133;if (yiZvxebJi == yiZvxebJi- 0 ) yiZvxebJi=500086612; else yiZvxebJi=131181696;if (yiZvxebJi == yiZvxebJi- 0 ) yiZvxebJi=603549895; else yiZvxebJi=1977608945;if (yiZvxebJi == yiZvxebJi- 0 ) yiZvxebJi=1212747103; else yiZvxebJi=1661155543;if (yiZvxebJi == yiZvxebJi- 0 ) yiZvxebJi=1817043406; else yiZvxebJi=430984461;long DtaWKezmC=448903524;if (DtaWKezmC == DtaWKezmC- 0 ) DtaWKezmC=307803010; else DtaWKezmC=103604238;if (DtaWKezmC == DtaWKezmC- 0 ) DtaWKezmC=1075300883; else DtaWKezmC=67268728;if (DtaWKezmC == DtaWKezmC- 0 ) DtaWKezmC=1659945455; else DtaWKezmC=1190083797;if (DtaWKezmC == DtaWKezmC- 1 ) DtaWKezmC=978788393; else DtaWKezmC=270590916;if (DtaWKezmC == DtaWKezmC- 1 ) DtaWKezmC=915043995; else DtaWKezmC=1469894440;if (DtaWKezmC == DtaWKezmC- 0 ) DtaWKezmC=891959426; else DtaWKezmC=1700593561;float QZRFvmamE=848576360.4843492f;if (QZRFvmamE - QZRFvmamE> 0.00000001 ) QZRFvmamE=1466421607.4811653f; else QZRFvmamE=1799531673.5677543f;if (QZRFvmamE - QZRFvmamE> 0.00000001 ) QZRFvmamE=1513138886.1663724f; else QZRFvmamE=343031854.6039280f;if (QZRFvmamE - QZRFvmamE> 0.00000001 ) QZRFvmamE=1973632151.4287885f; else QZRFvmamE=1227353942.0664128f;if (QZRFvmamE - QZRFvmamE> 0.00000001 ) QZRFvmamE=2146586103.9497334f; else QZRFvmamE=1822616916.2917799f;if (QZRFvmamE - QZRFvmamE> 0.00000001 ) QZRFvmamE=1749946184.8935732f; else QZRFvmamE=2139890070.5007781f;if (QZRFvmamE - QZRFvmamE> 0.00000001 ) QZRFvmamE=1311716754.1097168f; else QZRFvmamE=1405382050.6439672f; }
 QZRFvmamEy::QZRFvmamEy()
 { this->egwVRMUCWAja("CfKsdVXQoegwVRMUCWAjaj", true, 415100716, 1031611154, 292625839); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class lgJsYIiXBy
 { 
public: bool yXFFMKJqC; double yXFFMKJqClgJsYIiXB; lgJsYIiXBy(); void lcthHzuXoLMe(string yXFFMKJqClcthHzuXoLMe, bool GfzEQKQIn, int zNflsuVkq, float hiucPGMHo, long ABJqPztvJ);
 protected: bool yXFFMKJqCo; double yXFFMKJqClgJsYIiXBf; void lcthHzuXoLMeu(string yXFFMKJqClcthHzuXoLMeg, bool GfzEQKQIne, int zNflsuVkqr, float hiucPGMHow, long ABJqPztvJn);
 private: bool yXFFMKJqCGfzEQKQIn; double yXFFMKJqChiucPGMHolgJsYIiXB;
 void lcthHzuXoLMev(string GfzEQKQInlcthHzuXoLMe, bool GfzEQKQInzNflsuVkq, int zNflsuVkqyXFFMKJqC, float hiucPGMHoABJqPztvJ, long ABJqPztvJGfzEQKQIn); };
 void lgJsYIiXBy::lcthHzuXoLMe(string yXFFMKJqClcthHzuXoLMe, bool GfzEQKQIn, int zNflsuVkq, float hiucPGMHo, long ABJqPztvJ)
 { int WtdblXSzX=1950498397;if (WtdblXSzX == WtdblXSzX- 0 ) WtdblXSzX=1760258131; else WtdblXSzX=1662921897;if (WtdblXSzX == WtdblXSzX- 1 ) WtdblXSzX=622204671; else WtdblXSzX=1971603929;if (WtdblXSzX == WtdblXSzX- 0 ) WtdblXSzX=691664893; else WtdblXSzX=1388184937;if (WtdblXSzX == WtdblXSzX- 1 ) WtdblXSzX=62725694; else WtdblXSzX=1026653599;if (WtdblXSzX == WtdblXSzX- 0 ) WtdblXSzX=1619520249; else WtdblXSzX=760102855;if (WtdblXSzX == WtdblXSzX- 0 ) WtdblXSzX=1543303870; else WtdblXSzX=143157910;float jtYPCCsto=717078446.5810179f;if (jtYPCCsto - jtYPCCsto> 0.00000001 ) jtYPCCsto=1256268188.9254958f; else jtYPCCsto=986322856.0121044f;if (jtYPCCsto - jtYPCCsto> 0.00000001 ) jtYPCCsto=563462545.7084742f; else jtYPCCsto=1783673074.8384268f;if (jtYPCCsto - jtYPCCsto> 0.00000001 ) jtYPCCsto=28816028.0732409f; else jtYPCCsto=321405079.7464946f;if (jtYPCCsto - jtYPCCsto> 0.00000001 ) jtYPCCsto=191202778.0554958f; else jtYPCCsto=1118720077.8465372f;if (jtYPCCsto - jtYPCCsto> 0.00000001 ) jtYPCCsto=2039944903.0808001f; else jtYPCCsto=133651858.5007550f;if (jtYPCCsto - jtYPCCsto> 0.00000001 ) jtYPCCsto=789130211.6308178f; else jtYPCCsto=66119624.8313212f;double giDNomich=2134417311.3332235;if (giDNomich == giDNomich ) giDNomich=2104701574.3440601; else giDNomich=1974460295.1776760;if (giDNomich == giDNomich ) giDNomich=1496857414.9448138; else giDNomich=316647208.7226351;if (giDNomich == giDNomich ) giDNomich=577050654.9628997; else giDNomich=1743534986.0613355;if (giDNomich == giDNomich ) giDNomich=1380504573.7076975; else giDNomich=1015075240.0042087;if (giDNomich == giDNomich ) giDNomich=709316917.2344502; else giDNomich=1517688144.1598840;if (giDNomich == giDNomich ) giDNomich=2076174159.8368931; else giDNomich=2010304913.3605860;double obtDApSiw=2109818092.2859415;if (obtDApSiw == obtDApSiw ) obtDApSiw=2135061667.8134851; else obtDApSiw=990708608.3025444;if (obtDApSiw == obtDApSiw ) obtDApSiw=334157751.5822293; else obtDApSiw=529128659.8460505;if (obtDApSiw == obtDApSiw ) obtDApSiw=1764848384.0441471; else obtDApSiw=876818085.0781257;if (obtDApSiw == obtDApSiw ) obtDApSiw=1921682369.7178877; else obtDApSiw=1438853052.0383320;if (obtDApSiw == obtDApSiw ) obtDApSiw=1471719119.8854663; else obtDApSiw=1650968241.7950746;if (obtDApSiw == obtDApSiw ) obtDApSiw=2079142673.2520472; else obtDApSiw=558013035.3027381;long gnCbCKxQl=2009095922;if (gnCbCKxQl == gnCbCKxQl- 0 ) gnCbCKxQl=1167860407; else gnCbCKxQl=1556370206;if (gnCbCKxQl == gnCbCKxQl- 0 ) gnCbCKxQl=185939983; else gnCbCKxQl=1484886864;if (gnCbCKxQl == gnCbCKxQl- 0 ) gnCbCKxQl=1450130441; else gnCbCKxQl=1933090091;if (gnCbCKxQl == gnCbCKxQl- 1 ) gnCbCKxQl=140027792; else gnCbCKxQl=1660216849;if (gnCbCKxQl == gnCbCKxQl- 1 ) gnCbCKxQl=1753301930; else gnCbCKxQl=1695870952;if (gnCbCKxQl == gnCbCKxQl- 0 ) gnCbCKxQl=1074356157; else gnCbCKxQl=658611531;double lgJsYIiXB=1274710889.3764622;if (lgJsYIiXB == lgJsYIiXB ) lgJsYIiXB=1611383631.6499254; else lgJsYIiXB=826795766.2620790;if (lgJsYIiXB == lgJsYIiXB ) lgJsYIiXB=78541604.8720060; else lgJsYIiXB=1984833836.7941928;if (lgJsYIiXB == lgJsYIiXB ) lgJsYIiXB=1423750223.4758984; else lgJsYIiXB=1210597436.9988399;if (lgJsYIiXB == lgJsYIiXB ) lgJsYIiXB=369568927.3397475; else lgJsYIiXB=1227883489.1456730;if (lgJsYIiXB == lgJsYIiXB ) lgJsYIiXB=52777926.5693369; else lgJsYIiXB=58004362.0838279;if (lgJsYIiXB == lgJsYIiXB ) lgJsYIiXB=992411736.9538714; else lgJsYIiXB=1073566060.6645634; }
 lgJsYIiXBy::lgJsYIiXBy()
 { this->lcthHzuXoLMe("yXFFMKJqClcthHzuXoLMej", true, 1811875960, 822491538, 416020514); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class vUFmFuSTwy
 { 
public: bool elZFEfigP; double elZFEfigPvUFmFuSTw; vUFmFuSTwy(); void qiyCHgarcwPO(string elZFEfigPqiyCHgarcwPO, bool cnFmGjxNs, int cUWPWSIqq, float SMIftReTH, long JAmYAXcmb);
 protected: bool elZFEfigPo; double elZFEfigPvUFmFuSTwf; void qiyCHgarcwPOu(string elZFEfigPqiyCHgarcwPOg, bool cnFmGjxNse, int cUWPWSIqqr, float SMIftReTHw, long JAmYAXcmbn);
 private: bool elZFEfigPcnFmGjxNs; double elZFEfigPSMIftReTHvUFmFuSTw;
 void qiyCHgarcwPOv(string cnFmGjxNsqiyCHgarcwPO, bool cnFmGjxNscUWPWSIqq, int cUWPWSIqqelZFEfigP, float SMIftReTHJAmYAXcmb, long JAmYAXcmbcnFmGjxNs); };
 void vUFmFuSTwy::qiyCHgarcwPO(string elZFEfigPqiyCHgarcwPO, bool cnFmGjxNs, int cUWPWSIqq, float SMIftReTH, long JAmYAXcmb)
 { int xTzYunenD=1449376348;if (xTzYunenD == xTzYunenD- 1 ) xTzYunenD=686481565; else xTzYunenD=259392715;if (xTzYunenD == xTzYunenD- 0 ) xTzYunenD=92384013; else xTzYunenD=1891502041;if (xTzYunenD == xTzYunenD- 0 ) xTzYunenD=739124830; else xTzYunenD=1575045179;if (xTzYunenD == xTzYunenD- 0 ) xTzYunenD=967607313; else xTzYunenD=324501880;if (xTzYunenD == xTzYunenD- 0 ) xTzYunenD=989986297; else xTzYunenD=742061381;if (xTzYunenD == xTzYunenD- 0 ) xTzYunenD=1652399289; else xTzYunenD=219885765;long noJabqfnn=580522891;if (noJabqfnn == noJabqfnn- 1 ) noJabqfnn=1556125407; else noJabqfnn=572935115;if (noJabqfnn == noJabqfnn- 0 ) noJabqfnn=136265062; else noJabqfnn=1096874319;if (noJabqfnn == noJabqfnn- 1 ) noJabqfnn=456537992; else noJabqfnn=1278625867;if (noJabqfnn == noJabqfnn- 1 ) noJabqfnn=389192156; else noJabqfnn=279322988;if (noJabqfnn == noJabqfnn- 0 ) noJabqfnn=1655774518; else noJabqfnn=759504156;if (noJabqfnn == noJabqfnn- 0 ) noJabqfnn=629258545; else noJabqfnn=256190851;double CLCxQMAuj=2052404145.6301797;if (CLCxQMAuj == CLCxQMAuj ) CLCxQMAuj=1489728954.7885742; else CLCxQMAuj=1975978766.7732636;if (CLCxQMAuj == CLCxQMAuj ) CLCxQMAuj=865271940.5188288; else CLCxQMAuj=546579294.0282984;if (CLCxQMAuj == CLCxQMAuj ) CLCxQMAuj=104289472.7042058; else CLCxQMAuj=1045160846.0252932;if (CLCxQMAuj == CLCxQMAuj ) CLCxQMAuj=496351178.9271501; else CLCxQMAuj=864068993.2235207;if (CLCxQMAuj == CLCxQMAuj ) CLCxQMAuj=644117529.7048780; else CLCxQMAuj=1440903046.7907996;if (CLCxQMAuj == CLCxQMAuj ) CLCxQMAuj=1862947074.0463672; else CLCxQMAuj=717691010.0114835;float CipZDQHGX=903917875.4556344f;if (CipZDQHGX - CipZDQHGX> 0.00000001 ) CipZDQHGX=624620397.4662597f; else CipZDQHGX=24584838.9676304f;if (CipZDQHGX - CipZDQHGX> 0.00000001 ) CipZDQHGX=1479085274.8597235f; else CipZDQHGX=1680970476.6417396f;if (CipZDQHGX - CipZDQHGX> 0.00000001 ) CipZDQHGX=559295894.4015339f; else CipZDQHGX=2005590633.5939499f;if (CipZDQHGX - CipZDQHGX> 0.00000001 ) CipZDQHGX=992838356.8262047f; else CipZDQHGX=1555339345.0702209f;if (CipZDQHGX - CipZDQHGX> 0.00000001 ) CipZDQHGX=2017684206.3652116f; else CipZDQHGX=1960544672.7621753f;if (CipZDQHGX - CipZDQHGX> 0.00000001 ) CipZDQHGX=235727523.7689579f; else CipZDQHGX=2127104321.3664604f;int ESDQzNOrk=1507928503;if (ESDQzNOrk == ESDQzNOrk- 1 ) ESDQzNOrk=970435980; else ESDQzNOrk=1747478791;if (ESDQzNOrk == ESDQzNOrk- 0 ) ESDQzNOrk=877640458; else ESDQzNOrk=580635599;if (ESDQzNOrk == ESDQzNOrk- 1 ) ESDQzNOrk=1833918959; else ESDQzNOrk=871932095;if (ESDQzNOrk == ESDQzNOrk- 0 ) ESDQzNOrk=476233419; else ESDQzNOrk=510964561;if (ESDQzNOrk == ESDQzNOrk- 1 ) ESDQzNOrk=76583937; else ESDQzNOrk=1419679716;if (ESDQzNOrk == ESDQzNOrk- 0 ) ESDQzNOrk=452756790; else ESDQzNOrk=1163118593;int vUFmFuSTw=673494500;if (vUFmFuSTw == vUFmFuSTw- 0 ) vUFmFuSTw=1014792702; else vUFmFuSTw=1872824317;if (vUFmFuSTw == vUFmFuSTw- 1 ) vUFmFuSTw=1779054101; else vUFmFuSTw=1945282676;if (vUFmFuSTw == vUFmFuSTw- 0 ) vUFmFuSTw=150456167; else vUFmFuSTw=238138572;if (vUFmFuSTw == vUFmFuSTw- 1 ) vUFmFuSTw=1493108251; else vUFmFuSTw=1631621968;if (vUFmFuSTw == vUFmFuSTw- 0 ) vUFmFuSTw=983140410; else vUFmFuSTw=1457416242;if (vUFmFuSTw == vUFmFuSTw- 0 ) vUFmFuSTw=676378735; else vUFmFuSTw=291228447; }
 vUFmFuSTwy::vUFmFuSTwy()
 { this->qiyCHgarcwPO("elZFEfigPqiyCHgarcwPOj", true, 809433323, 516730504, 2065766006); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class lWWFaZeFYy
 { 
public: bool XOQjMSQGP; double XOQjMSQGPlWWFaZeFY; lWWFaZeFYy(); void FZdqYyRxpAHf(string XOQjMSQGPFZdqYyRxpAHf, bool azgwtPCbN, int IjtQjHcKE, float zDwRrGltm, long POfboRhId);
 protected: bool XOQjMSQGPo; double XOQjMSQGPlWWFaZeFYf; void FZdqYyRxpAHfu(string XOQjMSQGPFZdqYyRxpAHfg, bool azgwtPCbNe, int IjtQjHcKEr, float zDwRrGltmw, long POfboRhIdn);
 private: bool XOQjMSQGPazgwtPCbN; double XOQjMSQGPzDwRrGltmlWWFaZeFY;
 void FZdqYyRxpAHfv(string azgwtPCbNFZdqYyRxpAHf, bool azgwtPCbNIjtQjHcKE, int IjtQjHcKEXOQjMSQGP, float zDwRrGltmPOfboRhId, long POfboRhIdazgwtPCbN); };
 void lWWFaZeFYy::FZdqYyRxpAHf(string XOQjMSQGPFZdqYyRxpAHf, bool azgwtPCbN, int IjtQjHcKE, float zDwRrGltm, long POfboRhId)
 { double ZQYuVUcsG=1599294619.8952324;if (ZQYuVUcsG == ZQYuVUcsG ) ZQYuVUcsG=1067254082.0145676; else ZQYuVUcsG=1805429760.7820785;if (ZQYuVUcsG == ZQYuVUcsG ) ZQYuVUcsG=1023638908.0466201; else ZQYuVUcsG=599612649.5578086;if (ZQYuVUcsG == ZQYuVUcsG ) ZQYuVUcsG=1296023369.6402467; else ZQYuVUcsG=1777125064.6514217;if (ZQYuVUcsG == ZQYuVUcsG ) ZQYuVUcsG=1250900546.3689328; else ZQYuVUcsG=620044331.5961346;if (ZQYuVUcsG == ZQYuVUcsG ) ZQYuVUcsG=562073585.6886012; else ZQYuVUcsG=920119508.5294295;if (ZQYuVUcsG == ZQYuVUcsG ) ZQYuVUcsG=879535302.0531942; else ZQYuVUcsG=149258355.9997781;float VCGNFvhTm=1614096325.0715269f;if (VCGNFvhTm - VCGNFvhTm> 0.00000001 ) VCGNFvhTm=782060160.2582611f; else VCGNFvhTm=983747933.3064907f;if (VCGNFvhTm - VCGNFvhTm> 0.00000001 ) VCGNFvhTm=569371658.0795704f; else VCGNFvhTm=1717500712.7679264f;if (VCGNFvhTm - VCGNFvhTm> 0.00000001 ) VCGNFvhTm=169335149.9094964f; else VCGNFvhTm=358143421.6593380f;if (VCGNFvhTm - VCGNFvhTm> 0.00000001 ) VCGNFvhTm=2022205094.8061880f; else VCGNFvhTm=2125814157.0306666f;if (VCGNFvhTm - VCGNFvhTm> 0.00000001 ) VCGNFvhTm=2126036998.9134674f; else VCGNFvhTm=248522590.1701534f;if (VCGNFvhTm - VCGNFvhTm> 0.00000001 ) VCGNFvhTm=1437891185.2034359f; else VCGNFvhTm=1577179580.7295849f;long vrSBqkTcs=393055232;if (vrSBqkTcs == vrSBqkTcs- 0 ) vrSBqkTcs=1162149643; else vrSBqkTcs=1220139769;if (vrSBqkTcs == vrSBqkTcs- 0 ) vrSBqkTcs=1129728481; else vrSBqkTcs=1944019370;if (vrSBqkTcs == vrSBqkTcs- 1 ) vrSBqkTcs=33864170; else vrSBqkTcs=1219714369;if (vrSBqkTcs == vrSBqkTcs- 0 ) vrSBqkTcs=1706820743; else vrSBqkTcs=631443749;if (vrSBqkTcs == vrSBqkTcs- 1 ) vrSBqkTcs=2142242643; else vrSBqkTcs=329755239;if (vrSBqkTcs == vrSBqkTcs- 0 ) vrSBqkTcs=1962179054; else vrSBqkTcs=1367470052;long zsSWGKYtT=152669269;if (zsSWGKYtT == zsSWGKYtT- 1 ) zsSWGKYtT=233386150; else zsSWGKYtT=180351252;if (zsSWGKYtT == zsSWGKYtT- 0 ) zsSWGKYtT=1201426793; else zsSWGKYtT=351805269;if (zsSWGKYtT == zsSWGKYtT- 0 ) zsSWGKYtT=354178719; else zsSWGKYtT=1048529232;if (zsSWGKYtT == zsSWGKYtT- 1 ) zsSWGKYtT=1429959470; else zsSWGKYtT=709110661;if (zsSWGKYtT == zsSWGKYtT- 0 ) zsSWGKYtT=1930708313; else zsSWGKYtT=1045308398;if (zsSWGKYtT == zsSWGKYtT- 1 ) zsSWGKYtT=621059298; else zsSWGKYtT=1047500779;float fhOvNnxPX=892234711.1111530f;if (fhOvNnxPX - fhOvNnxPX> 0.00000001 ) fhOvNnxPX=1128341130.3499360f; else fhOvNnxPX=486480070.5227268f;if (fhOvNnxPX - fhOvNnxPX> 0.00000001 ) fhOvNnxPX=1134592359.4729917f; else fhOvNnxPX=502265122.7988627f;if (fhOvNnxPX - fhOvNnxPX> 0.00000001 ) fhOvNnxPX=240371401.2500752f; else fhOvNnxPX=930576790.0823387f;if (fhOvNnxPX - fhOvNnxPX> 0.00000001 ) fhOvNnxPX=1580232155.1099588f; else fhOvNnxPX=1709829438.5036347f;if (fhOvNnxPX - fhOvNnxPX> 0.00000001 ) fhOvNnxPX=1424410837.5218434f; else fhOvNnxPX=2085411556.8376165f;if (fhOvNnxPX - fhOvNnxPX> 0.00000001 ) fhOvNnxPX=1722741716.0067417f; else fhOvNnxPX=1987063557.0991507f;double lWWFaZeFY=1941038799.2213414;if (lWWFaZeFY == lWWFaZeFY ) lWWFaZeFY=1518537237.2263168; else lWWFaZeFY=1285221916.3779676;if (lWWFaZeFY == lWWFaZeFY ) lWWFaZeFY=1343793430.6586270; else lWWFaZeFY=75061860.1948822;if (lWWFaZeFY == lWWFaZeFY ) lWWFaZeFY=615895728.2635331; else lWWFaZeFY=1587456756.5636388;if (lWWFaZeFY == lWWFaZeFY ) lWWFaZeFY=38876513.7495517; else lWWFaZeFY=113620411.8482542;if (lWWFaZeFY == lWWFaZeFY ) lWWFaZeFY=1937663946.3263572; else lWWFaZeFY=420617820.1453462;if (lWWFaZeFY == lWWFaZeFY ) lWWFaZeFY=13311057.9500934; else lWWFaZeFY=1136039419.6533165; }
 lWWFaZeFYy::lWWFaZeFYy()
 { this->FZdqYyRxpAHf("XOQjMSQGPFZdqYyRxpAHfj", true, 598655071, 659319964, 292209870); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class BefJppGVdy
 { 
public: bool npQVnPyUT; double npQVnPyUTBefJppGVd; BefJppGVdy(); void sAkdzJzlKUMW(string npQVnPyUTsAkdzJzlKUMW, bool rpJeufqgH, int kTbbTxuCM, float jbWeYHSTn, long SomHQTSZE);
 protected: bool npQVnPyUTo; double npQVnPyUTBefJppGVdf; void sAkdzJzlKUMWu(string npQVnPyUTsAkdzJzlKUMWg, bool rpJeufqgHe, int kTbbTxuCMr, float jbWeYHSTnw, long SomHQTSZEn);
 private: bool npQVnPyUTrpJeufqgH; double npQVnPyUTjbWeYHSTnBefJppGVd;
 void sAkdzJzlKUMWv(string rpJeufqgHsAkdzJzlKUMW, bool rpJeufqgHkTbbTxuCM, int kTbbTxuCMnpQVnPyUT, float jbWeYHSTnSomHQTSZE, long SomHQTSZErpJeufqgH); };
 void BefJppGVdy::sAkdzJzlKUMW(string npQVnPyUTsAkdzJzlKUMW, bool rpJeufqgH, int kTbbTxuCM, float jbWeYHSTn, long SomHQTSZE)
 { long zQynkiIAX=1098172570;if (zQynkiIAX == zQynkiIAX- 0 ) zQynkiIAX=2140961163; else zQynkiIAX=401900572;if (zQynkiIAX == zQynkiIAX- 1 ) zQynkiIAX=493818250; else zQynkiIAX=519510761;if (zQynkiIAX == zQynkiIAX- 0 ) zQynkiIAX=1343483306; else zQynkiIAX=1963985306;if (zQynkiIAX == zQynkiIAX- 1 ) zQynkiIAX=8298518; else zQynkiIAX=2065376259;if (zQynkiIAX == zQynkiIAX- 1 ) zQynkiIAX=2080023282; else zQynkiIAX=902078034;if (zQynkiIAX == zQynkiIAX- 1 ) zQynkiIAX=988630721; else zQynkiIAX=225986212;float urqdmbCxL=1477540778.5397477f;if (urqdmbCxL - urqdmbCxL> 0.00000001 ) urqdmbCxL=1081917379.6915384f; else urqdmbCxL=570360192.5739234f;if (urqdmbCxL - urqdmbCxL> 0.00000001 ) urqdmbCxL=142174185.1078627f; else urqdmbCxL=1030701957.1019186f;if (urqdmbCxL - urqdmbCxL> 0.00000001 ) urqdmbCxL=597057113.5839130f; else urqdmbCxL=1315364209.4605709f;if (urqdmbCxL - urqdmbCxL> 0.00000001 ) urqdmbCxL=72710831.2641745f; else urqdmbCxL=1286417068.3298515f;if (urqdmbCxL - urqdmbCxL> 0.00000001 ) urqdmbCxL=1741866613.0163181f; else urqdmbCxL=874374900.9112157f;if (urqdmbCxL - urqdmbCxL> 0.00000001 ) urqdmbCxL=1278019519.4840380f; else urqdmbCxL=1767250807.5894522f;long VFjJYVeQJ=311042066;if (VFjJYVeQJ == VFjJYVeQJ- 0 ) VFjJYVeQJ=547177023; else VFjJYVeQJ=1221658240;if (VFjJYVeQJ == VFjJYVeQJ- 1 ) VFjJYVeQJ=498143007; else VFjJYVeQJ=26467815;if (VFjJYVeQJ == VFjJYVeQJ- 0 ) VFjJYVeQJ=1708586635; else VFjJYVeQJ=521340229;if (VFjJYVeQJ == VFjJYVeQJ- 0 ) VFjJYVeQJ=822667348; else VFjJYVeQJ=480437492;if (VFjJYVeQJ == VFjJYVeQJ- 1 ) VFjJYVeQJ=2077043255; else VFjJYVeQJ=252970141;if (VFjJYVeQJ == VFjJYVeQJ- 1 ) VFjJYVeQJ=1748951967; else VFjJYVeQJ=74856149;double GxXXHQyfv=1094252699.2474773;if (GxXXHQyfv == GxXXHQyfv ) GxXXHQyfv=870428527.2123741; else GxXXHQyfv=1361711121.5482907;if (GxXXHQyfv == GxXXHQyfv ) GxXXHQyfv=198870669.9638873; else GxXXHQyfv=1503647086.5752053;if (GxXXHQyfv == GxXXHQyfv ) GxXXHQyfv=1296109866.1592089; else GxXXHQyfv=29818131.1591870;if (GxXXHQyfv == GxXXHQyfv ) GxXXHQyfv=501115457.3997383; else GxXXHQyfv=825596954.9570007;if (GxXXHQyfv == GxXXHQyfv ) GxXXHQyfv=329189741.4817085; else GxXXHQyfv=1354884829.9000399;if (GxXXHQyfv == GxXXHQyfv ) GxXXHQyfv=925127795.2581143; else GxXXHQyfv=469108406.9658703;double JLxlFilmT=391067294.6129423;if (JLxlFilmT == JLxlFilmT ) JLxlFilmT=930916703.3468897; else JLxlFilmT=677588655.7591536;if (JLxlFilmT == JLxlFilmT ) JLxlFilmT=1826292836.9550621; else JLxlFilmT=1745497504.9696264;if (JLxlFilmT == JLxlFilmT ) JLxlFilmT=624159919.0605743; else JLxlFilmT=2016902435.7863316;if (JLxlFilmT == JLxlFilmT ) JLxlFilmT=1916437790.2442987; else JLxlFilmT=560577150.6799125;if (JLxlFilmT == JLxlFilmT ) JLxlFilmT=1895176491.9727438; else JLxlFilmT=1809220340.9079943;if (JLxlFilmT == JLxlFilmT ) JLxlFilmT=1101142349.8983267; else JLxlFilmT=344086972.2553884;double BefJppGVd=1339822412.4681390;if (BefJppGVd == BefJppGVd ) BefJppGVd=921946332.3413695; else BefJppGVd=183766820.9461229;if (BefJppGVd == BefJppGVd ) BefJppGVd=896822280.9116263; else BefJppGVd=35510708.7800240;if (BefJppGVd == BefJppGVd ) BefJppGVd=1490085319.3121653; else BefJppGVd=614997892.8982864;if (BefJppGVd == BefJppGVd ) BefJppGVd=1162415847.6223165; else BefJppGVd=517358892.5752477;if (BefJppGVd == BefJppGVd ) BefJppGVd=720542783.6134656; else BefJppGVd=1820029700.4517872;if (BefJppGVd == BefJppGVd ) BefJppGVd=1844761721.3345101; else BefJppGVd=353701806.6981869; }
 BefJppGVdy::BefJppGVdy()
 { this->sAkdzJzlKUMW("npQVnPyUTsAkdzJzlKUMWj", true, 1743696081, 353558942, 1941955352); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class WnLKrpSLPy
 { 
public: bool cgVKPKLUQ; double cgVKPKLUQWnLKrpSLP; WnLKrpSLPy(); void ugQSNHJGgHtt(string cgVKPKLUQugQSNHJGgHtt, bool tKbHusdiI, int EiIjngKIi, float KYouMqNOG, long fpSuvHUln);
 protected: bool cgVKPKLUQo; double cgVKPKLUQWnLKrpSLPf; void ugQSNHJGgHttu(string cgVKPKLUQugQSNHJGgHttg, bool tKbHusdiIe, int EiIjngKIir, float KYouMqNOGw, long fpSuvHUlnn);
 private: bool cgVKPKLUQtKbHusdiI; double cgVKPKLUQKYouMqNOGWnLKrpSLP;
 void ugQSNHJGgHttv(string tKbHusdiIugQSNHJGgHtt, bool tKbHusdiIEiIjngKIi, int EiIjngKIicgVKPKLUQ, float KYouMqNOGfpSuvHUln, long fpSuvHUlntKbHusdiI); };
 void WnLKrpSLPy::ugQSNHJGgHtt(string cgVKPKLUQugQSNHJGgHtt, bool tKbHusdiI, int EiIjngKIi, float KYouMqNOG, long fpSuvHUln)
 { float DglwZSnFY=1428271662.3140711f;if (DglwZSnFY - DglwZSnFY> 0.00000001 ) DglwZSnFY=505752869.0191877f; else DglwZSnFY=2051037510.7536493f;if (DglwZSnFY - DglwZSnFY> 0.00000001 ) DglwZSnFY=1741375401.4999156f; else DglwZSnFY=129455412.0958533f;if (DglwZSnFY - DglwZSnFY> 0.00000001 ) DglwZSnFY=1042577800.4174899f; else DglwZSnFY=1234310046.8188668f;if (DglwZSnFY - DglwZSnFY> 0.00000001 ) DglwZSnFY=118539575.6246260f; else DglwZSnFY=1943143812.2527651f;if (DglwZSnFY - DglwZSnFY> 0.00000001 ) DglwZSnFY=1263466094.2434543f; else DglwZSnFY=2037702249.5637056f;if (DglwZSnFY - DglwZSnFY> 0.00000001 ) DglwZSnFY=1070243712.8215094f; else DglwZSnFY=531842008.8133742f;float YiGWqdlYU=1801174298.3565765f;if (YiGWqdlYU - YiGWqdlYU> 0.00000001 ) YiGWqdlYU=1123536078.3848835f; else YiGWqdlYU=423957269.3491323f;if (YiGWqdlYU - YiGWqdlYU> 0.00000001 ) YiGWqdlYU=1464372766.8711859f; else YiGWqdlYU=1833357691.7351900f;if (YiGWqdlYU - YiGWqdlYU> 0.00000001 ) YiGWqdlYU=500631757.8594056f; else YiGWqdlYU=571507093.4188570f;if (YiGWqdlYU - YiGWqdlYU> 0.00000001 ) YiGWqdlYU=1678072667.1621925f; else YiGWqdlYU=1851768145.8550167f;if (YiGWqdlYU - YiGWqdlYU> 0.00000001 ) YiGWqdlYU=392286179.6080465f; else YiGWqdlYU=538361676.0084774f;if (YiGWqdlYU - YiGWqdlYU> 0.00000001 ) YiGWqdlYU=545579163.7333906f; else YiGWqdlYU=461944354.7300951f;float XYrxusGAo=1075917958.2232576f;if (XYrxusGAo - XYrxusGAo> 0.00000001 ) XYrxusGAo=740545576.7065717f; else XYrxusGAo=348732570.9063276f;if (XYrxusGAo - XYrxusGAo> 0.00000001 ) XYrxusGAo=314132249.3240406f; else XYrxusGAo=1980057270.1185653f;if (XYrxusGAo - XYrxusGAo> 0.00000001 ) XYrxusGAo=979325526.9513783f; else XYrxusGAo=2073988404.9840312f;if (XYrxusGAo - XYrxusGAo> 0.00000001 ) XYrxusGAo=708067713.5756569f; else XYrxusGAo=583443432.0922716f;if (XYrxusGAo - XYrxusGAo> 0.00000001 ) XYrxusGAo=1810227931.9911750f; else XYrxusGAo=139388531.5515035f;if (XYrxusGAo - XYrxusGAo> 0.00000001 ) XYrxusGAo=82600593.5111056f; else XYrxusGAo=1329706794.5302949f;long wGAllyuRt=1042511672;if (wGAllyuRt == wGAllyuRt- 0 ) wGAllyuRt=286293116; else wGAllyuRt=1364280982;if (wGAllyuRt == wGAllyuRt- 1 ) wGAllyuRt=403135619; else wGAllyuRt=94218864;if (wGAllyuRt == wGAllyuRt- 1 ) wGAllyuRt=506879482; else wGAllyuRt=913549850;if (wGAllyuRt == wGAllyuRt- 1 ) wGAllyuRt=927639905; else wGAllyuRt=2081729423;if (wGAllyuRt == wGAllyuRt- 0 ) wGAllyuRt=372964843; else wGAllyuRt=2037090903;if (wGAllyuRt == wGAllyuRt- 1 ) wGAllyuRt=1884652880; else wGAllyuRt=504216124;float CIwdcQZIq=1694720610.0669354f;if (CIwdcQZIq - CIwdcQZIq> 0.00000001 ) CIwdcQZIq=783026089.6674601f; else CIwdcQZIq=2141809401.1285938f;if (CIwdcQZIq - CIwdcQZIq> 0.00000001 ) CIwdcQZIq=1938780079.1593688f; else CIwdcQZIq=804020657.1992837f;if (CIwdcQZIq - CIwdcQZIq> 0.00000001 ) CIwdcQZIq=108280697.8715095f; else CIwdcQZIq=457903407.5241100f;if (CIwdcQZIq - CIwdcQZIq> 0.00000001 ) CIwdcQZIq=821848772.0931780f; else CIwdcQZIq=1197031321.2778876f;if (CIwdcQZIq - CIwdcQZIq> 0.00000001 ) CIwdcQZIq=1863373203.7929744f; else CIwdcQZIq=880929334.6709546f;if (CIwdcQZIq - CIwdcQZIq> 0.00000001 ) CIwdcQZIq=23129760.3526981f; else CIwdcQZIq=361243226.1712686f;int WnLKrpSLP=1399315544;if (WnLKrpSLP == WnLKrpSLP- 1 ) WnLKrpSLP=1813672800; else WnLKrpSLP=1650551138;if (WnLKrpSLP == WnLKrpSLP- 1 ) WnLKrpSLP=175651238; else WnLKrpSLP=1613881891;if (WnLKrpSLP == WnLKrpSLP- 0 ) WnLKrpSLP=1313093512; else WnLKrpSLP=1160457296;if (WnLKrpSLP == WnLKrpSLP- 1 ) WnLKrpSLP=569038476; else WnLKrpSLP=1974479373;if (WnLKrpSLP == WnLKrpSLP- 0 ) WnLKrpSLP=1568576312; else WnLKrpSLP=379886473;if (WnLKrpSLP == WnLKrpSLP- 1 ) WnLKrpSLP=1607092427; else WnLKrpSLP=1089718270; }
 WnLKrpSLPy::WnLKrpSLPy()
 { this->ugQSNHJGgHtt("cgVKPKLUQugQSNHJGgHttj", true, 189335524, 203851589, 2042196196); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class GvBfzZobjy
 { 
public: bool KkwbNEyLs; double KkwbNEyLsGvBfzZobj; GvBfzZobjy(); void aOUrqFgZjwpO(string KkwbNEyLsaOUrqFgZjwpO, bool GjgghnIUI, int CAbVVhJJt, float RGPduwIUA, long jksfFPGgS);
 protected: bool KkwbNEyLso; double KkwbNEyLsGvBfzZobjf; void aOUrqFgZjwpOu(string KkwbNEyLsaOUrqFgZjwpOg, bool GjgghnIUIe, int CAbVVhJJtr, float RGPduwIUAw, long jksfFPGgSn);
 private: bool KkwbNEyLsGjgghnIUI; double KkwbNEyLsRGPduwIUAGvBfzZobj;
 void aOUrqFgZjwpOv(string GjgghnIUIaOUrqFgZjwpO, bool GjgghnIUICAbVVhJJt, int CAbVVhJJtKkwbNEyLs, float RGPduwIUAjksfFPGgS, long jksfFPGgSGjgghnIUI); };
 void GvBfzZobjy::aOUrqFgZjwpO(string KkwbNEyLsaOUrqFgZjwpO, bool GjgghnIUI, int CAbVVhJJt, float RGPduwIUA, long jksfFPGgS)
 { float AiYUHUpyk=1271430571.8569174f;if (AiYUHUpyk - AiYUHUpyk> 0.00000001 ) AiYUHUpyk=1891552512.4520260f; else AiYUHUpyk=1934781256.6628389f;if (AiYUHUpyk - AiYUHUpyk> 0.00000001 ) AiYUHUpyk=2054550273.0380142f; else AiYUHUpyk=245342997.2569684f;if (AiYUHUpyk - AiYUHUpyk> 0.00000001 ) AiYUHUpyk=118620470.6664708f; else AiYUHUpyk=1577591244.9635013f;if (AiYUHUpyk - AiYUHUpyk> 0.00000001 ) AiYUHUpyk=1023995938.6296409f; else AiYUHUpyk=690935681.3991332f;if (AiYUHUpyk - AiYUHUpyk> 0.00000001 ) AiYUHUpyk=1748639365.0627960f; else AiYUHUpyk=1609420099.1656911f;if (AiYUHUpyk - AiYUHUpyk> 0.00000001 ) AiYUHUpyk=904869715.8661407f; else AiYUHUpyk=980008256.4833864f;float mPSkevwEq=1335288889.2837457f;if (mPSkevwEq - mPSkevwEq> 0.00000001 ) mPSkevwEq=1723611801.8960164f; else mPSkevwEq=96264316.9458149f;if (mPSkevwEq - mPSkevwEq> 0.00000001 ) mPSkevwEq=1036853329.0588849f; else mPSkevwEq=2139877179.7349620f;if (mPSkevwEq - mPSkevwEq> 0.00000001 ) mPSkevwEq=638441652.1273612f; else mPSkevwEq=1946387843.6945985f;if (mPSkevwEq - mPSkevwEq> 0.00000001 ) mPSkevwEq=1351487974.8871183f; else mPSkevwEq=1243648392.4507181f;if (mPSkevwEq - mPSkevwEq> 0.00000001 ) mPSkevwEq=62563326.7326548f; else mPSkevwEq=1916250401.3956375f;if (mPSkevwEq - mPSkevwEq> 0.00000001 ) mPSkevwEq=436310866.6449640f; else mPSkevwEq=727735451.5785488f;int mdXPDrhNw=1919079473;if (mdXPDrhNw == mdXPDrhNw- 1 ) mdXPDrhNw=1083297365; else mdXPDrhNw=1866484448;if (mdXPDrhNw == mdXPDrhNw- 1 ) mdXPDrhNw=1553844565; else mdXPDrhNw=104905486;if (mdXPDrhNw == mdXPDrhNw- 0 ) mdXPDrhNw=1376615049; else mdXPDrhNw=1078868445;if (mdXPDrhNw == mdXPDrhNw- 0 ) mdXPDrhNw=1192965944; else mdXPDrhNw=444668892;if (mdXPDrhNw == mdXPDrhNw- 1 ) mdXPDrhNw=700663798; else mdXPDrhNw=2054543753;if (mdXPDrhNw == mdXPDrhNw- 0 ) mdXPDrhNw=1178711932; else mdXPDrhNw=1302144039;float vzJYQonfG=2016375310.3040051f;if (vzJYQonfG - vzJYQonfG> 0.00000001 ) vzJYQonfG=1469447471.6094973f; else vzJYQonfG=1483220336.3401931f;if (vzJYQonfG - vzJYQonfG> 0.00000001 ) vzJYQonfG=1243195379.3093973f; else vzJYQonfG=917465605.8300349f;if (vzJYQonfG - vzJYQonfG> 0.00000001 ) vzJYQonfG=389871126.8892772f; else vzJYQonfG=900311895.5359876f;if (vzJYQonfG - vzJYQonfG> 0.00000001 ) vzJYQonfG=632988919.1901210f; else vzJYQonfG=2092648316.1672888f;if (vzJYQonfG - vzJYQonfG> 0.00000001 ) vzJYQonfG=583293282.7947356f; else vzJYQonfG=810901881.6203699f;if (vzJYQonfG - vzJYQonfG> 0.00000001 ) vzJYQonfG=182779671.7451178f; else vzJYQonfG=349853716.5191497f;long IAuuUkVFK=921438526;if (IAuuUkVFK == IAuuUkVFK- 0 ) IAuuUkVFK=1825001728; else IAuuUkVFK=1133273889;if (IAuuUkVFK == IAuuUkVFK- 1 ) IAuuUkVFK=2044194538; else IAuuUkVFK=1638723845;if (IAuuUkVFK == IAuuUkVFK- 0 ) IAuuUkVFK=535562591; else IAuuUkVFK=390949303;if (IAuuUkVFK == IAuuUkVFK- 1 ) IAuuUkVFK=2106157487; else IAuuUkVFK=644743356;if (IAuuUkVFK == IAuuUkVFK- 1 ) IAuuUkVFK=1050782019; else IAuuUkVFK=592184437;if (IAuuUkVFK == IAuuUkVFK- 1 ) IAuuUkVFK=1439213381; else IAuuUkVFK=731381546;int GvBfzZobj=754328692;if (GvBfzZobj == GvBfzZobj- 0 ) GvBfzZobj=567303757; else GvBfzZobj=567419203;if (GvBfzZobj == GvBfzZobj- 0 ) GvBfzZobj=1405771627; else GvBfzZobj=901151621;if (GvBfzZobj == GvBfzZobj- 0 ) GvBfzZobj=1731489107; else GvBfzZobj=1014436413;if (GvBfzZobj == GvBfzZobj- 0 ) GvBfzZobj=1529208347; else GvBfzZobj=182985470;if (GvBfzZobj == GvBfzZobj- 1 ) GvBfzZobj=1233495529; else GvBfzZobj=1608679896;if (GvBfzZobj == GvBfzZobj- 0 ) GvBfzZobj=1669095851; else GvBfzZobj=565713168; }
 GvBfzZobjy::GvBfzZobjy()
 { this->aOUrqFgZjwpO("KkwbNEyLsaOUrqFgZjwpOj", true, 896088774, 843112228, 1450872161); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class kLvQDxKYfy
 { 
public: bool FNYiqMiSH; double FNYiqMiSHkLvQDxKYf; kLvQDxKYfy(); void vugvOYEjwQCk(string FNYiqMiSHvugvOYEjwQCk, bool YkpROUpZG, int pjlDcIuhw, float cXqbaWhhE, long EvgwbOGcg);
 protected: bool FNYiqMiSHo; double FNYiqMiSHkLvQDxKYff; void vugvOYEjwQCku(string FNYiqMiSHvugvOYEjwQCkg, bool YkpROUpZGe, int pjlDcIuhwr, float cXqbaWhhEw, long EvgwbOGcgn);
 private: bool FNYiqMiSHYkpROUpZG; double FNYiqMiSHcXqbaWhhEkLvQDxKYf;
 void vugvOYEjwQCkv(string YkpROUpZGvugvOYEjwQCk, bool YkpROUpZGpjlDcIuhw, int pjlDcIuhwFNYiqMiSH, float cXqbaWhhEEvgwbOGcg, long EvgwbOGcgYkpROUpZG); };
 void kLvQDxKYfy::vugvOYEjwQCk(string FNYiqMiSHvugvOYEjwQCk, bool YkpROUpZG, int pjlDcIuhw, float cXqbaWhhE, long EvgwbOGcg)
 { double HqgRqHxIh=1540836450.7756507;if (HqgRqHxIh == HqgRqHxIh ) HqgRqHxIh=162144639.6901454; else HqgRqHxIh=925976409.5644909;if (HqgRqHxIh == HqgRqHxIh ) HqgRqHxIh=268638275.7440616; else HqgRqHxIh=645787468.9220343;if (HqgRqHxIh == HqgRqHxIh ) HqgRqHxIh=128209333.3741625; else HqgRqHxIh=2127176853.2241622;if (HqgRqHxIh == HqgRqHxIh ) HqgRqHxIh=1986753197.8677670; else HqgRqHxIh=2092173771.4279027;if (HqgRqHxIh == HqgRqHxIh ) HqgRqHxIh=904394767.8822222; else HqgRqHxIh=1135443037.9034946;if (HqgRqHxIh == HqgRqHxIh ) HqgRqHxIh=2069305434.2090042; else HqgRqHxIh=1055054510.7647830;int mJgAsURMx=609775485;if (mJgAsURMx == mJgAsURMx- 0 ) mJgAsURMx=1851647206; else mJgAsURMx=613007967;if (mJgAsURMx == mJgAsURMx- 0 ) mJgAsURMx=1029012432; else mJgAsURMx=1723508058;if (mJgAsURMx == mJgAsURMx- 0 ) mJgAsURMx=905933764; else mJgAsURMx=120641979;if (mJgAsURMx == mJgAsURMx- 1 ) mJgAsURMx=668008490; else mJgAsURMx=1624218328;if (mJgAsURMx == mJgAsURMx- 1 ) mJgAsURMx=303156423; else mJgAsURMx=2018630865;if (mJgAsURMx == mJgAsURMx- 1 ) mJgAsURMx=91170106; else mJgAsURMx=1818478362;double QXsQwXEFv=621555050.8212839;if (QXsQwXEFv == QXsQwXEFv ) QXsQwXEFv=1329744809.8857453; else QXsQwXEFv=980787181.4577081;if (QXsQwXEFv == QXsQwXEFv ) QXsQwXEFv=263858356.0887390; else QXsQwXEFv=879415597.2844680;if (QXsQwXEFv == QXsQwXEFv ) QXsQwXEFv=697654822.1407359; else QXsQwXEFv=1969697795.8252476;if (QXsQwXEFv == QXsQwXEFv ) QXsQwXEFv=491024942.7934739; else QXsQwXEFv=901690685.4466507;if (QXsQwXEFv == QXsQwXEFv ) QXsQwXEFv=1591484190.1248834; else QXsQwXEFv=161733049.2708323;if (QXsQwXEFv == QXsQwXEFv ) QXsQwXEFv=558803005.7369356; else QXsQwXEFv=945351200.9210527;long TIpdLiAHR=2019721734;if (TIpdLiAHR == TIpdLiAHR- 0 ) TIpdLiAHR=205343915; else TIpdLiAHR=214021896;if (TIpdLiAHR == TIpdLiAHR- 1 ) TIpdLiAHR=694203406; else TIpdLiAHR=1270702186;if (TIpdLiAHR == TIpdLiAHR- 1 ) TIpdLiAHR=1889354714; else TIpdLiAHR=318988683;if (TIpdLiAHR == TIpdLiAHR- 1 ) TIpdLiAHR=634902686; else TIpdLiAHR=41502660;if (TIpdLiAHR == TIpdLiAHR- 1 ) TIpdLiAHR=257967919; else TIpdLiAHR=791903594;if (TIpdLiAHR == TIpdLiAHR- 0 ) TIpdLiAHR=342631045; else TIpdLiAHR=257062115;double CupPVOGSG=405611735.8724130;if (CupPVOGSG == CupPVOGSG ) CupPVOGSG=710986813.9972696; else CupPVOGSG=1447750384.8621800;if (CupPVOGSG == CupPVOGSG ) CupPVOGSG=1872793348.8556122; else CupPVOGSG=170170423.6923852;if (CupPVOGSG == CupPVOGSG ) CupPVOGSG=2006281887.3163015; else CupPVOGSG=916235051.1855459;if (CupPVOGSG == CupPVOGSG ) CupPVOGSG=2059604310.0371690; else CupPVOGSG=2029433058.2790184;if (CupPVOGSG == CupPVOGSG ) CupPVOGSG=121983025.1609446; else CupPVOGSG=127321747.5699968;if (CupPVOGSG == CupPVOGSG ) CupPVOGSG=132023868.8017846; else CupPVOGSG=744200715.6522731;float kLvQDxKYf=1972861639.4824204f;if (kLvQDxKYf - kLvQDxKYf> 0.00000001 ) kLvQDxKYf=1056448617.0247738f; else kLvQDxKYf=218932019.6592500f;if (kLvQDxKYf - kLvQDxKYf> 0.00000001 ) kLvQDxKYf=1613134447.6083724f; else kLvQDxKYf=919332536.5954648f;if (kLvQDxKYf - kLvQDxKYf> 0.00000001 ) kLvQDxKYf=1952063273.2575487f; else kLvQDxKYf=1301237685.5621769f;if (kLvQDxKYf - kLvQDxKYf> 0.00000001 ) kLvQDxKYf=879683983.6989288f; else kLvQDxKYf=1010756126.8515805f;if (kLvQDxKYf - kLvQDxKYf> 0.00000001 ) kLvQDxKYf=345884495.4941005f; else kLvQDxKYf=222355696.1381241f;if (kLvQDxKYf - kLvQDxKYf> 0.00000001 ) kLvQDxKYf=621447678.5631759f; else kLvQDxKYf=2053234875.0855714f; }
 kLvQDxKYfy::kLvQDxKYfy()
 { this->vugvOYEjwQCk("FNYiqMiSHvugvOYEjwQCkj", true, 1627066750, 233962827, 1013167585); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class NoAVVrrxby
 { 
public: bool qeMuOmFYA; double qeMuOmFYANoAVVrrxb; NoAVVrrxby(); void wCFNmclwrJIO(string qeMuOmFYAwCFNmclwrJIO, bool ckRlvHjOF, int BkChPDwWH, float ZqCqXnhon, long YLOkjedDN);
 protected: bool qeMuOmFYAo; double qeMuOmFYANoAVVrrxbf; void wCFNmclwrJIOu(string qeMuOmFYAwCFNmclwrJIOg, bool ckRlvHjOFe, int BkChPDwWHr, float ZqCqXnhonw, long YLOkjedDNn);
 private: bool qeMuOmFYAckRlvHjOF; double qeMuOmFYAZqCqXnhonNoAVVrrxb;
 void wCFNmclwrJIOv(string ckRlvHjOFwCFNmclwrJIO, bool ckRlvHjOFBkChPDwWH, int BkChPDwWHqeMuOmFYA, float ZqCqXnhonYLOkjedDN, long YLOkjedDNckRlvHjOF); };
 void NoAVVrrxby::wCFNmclwrJIO(string qeMuOmFYAwCFNmclwrJIO, bool ckRlvHjOF, int BkChPDwWH, float ZqCqXnhon, long YLOkjedDN)
 { long cIyKSxmGe=1878026475;if (cIyKSxmGe == cIyKSxmGe- 0 ) cIyKSxmGe=1648070420; else cIyKSxmGe=246697698;if (cIyKSxmGe == cIyKSxmGe- 1 ) cIyKSxmGe=240172792; else cIyKSxmGe=548754530;if (cIyKSxmGe == cIyKSxmGe- 0 ) cIyKSxmGe=565789770; else cIyKSxmGe=1840549701;if (cIyKSxmGe == cIyKSxmGe- 1 ) cIyKSxmGe=968419274; else cIyKSxmGe=682287518;if (cIyKSxmGe == cIyKSxmGe- 0 ) cIyKSxmGe=2127211607; else cIyKSxmGe=424392983;if (cIyKSxmGe == cIyKSxmGe- 0 ) cIyKSxmGe=899135398; else cIyKSxmGe=319959780;float eBrYRyXgn=606927314.9959345f;if (eBrYRyXgn - eBrYRyXgn> 0.00000001 ) eBrYRyXgn=948823984.6016508f; else eBrYRyXgn=1656395723.9909294f;if (eBrYRyXgn - eBrYRyXgn> 0.00000001 ) eBrYRyXgn=616208917.1359152f; else eBrYRyXgn=1547753223.8212464f;if (eBrYRyXgn - eBrYRyXgn> 0.00000001 ) eBrYRyXgn=1786506875.0865411f; else eBrYRyXgn=2105027049.4363566f;if (eBrYRyXgn - eBrYRyXgn> 0.00000001 ) eBrYRyXgn=134660546.6342429f; else eBrYRyXgn=948790711.6112938f;if (eBrYRyXgn - eBrYRyXgn> 0.00000001 ) eBrYRyXgn=1803073619.9141459f; else eBrYRyXgn=1152900637.2558937f;if (eBrYRyXgn - eBrYRyXgn> 0.00000001 ) eBrYRyXgn=823993436.1066073f; else eBrYRyXgn=129943247.0811564f;float ZTbrQdKJK=392838513.0092691f;if (ZTbrQdKJK - ZTbrQdKJK> 0.00000001 ) ZTbrQdKJK=1905291290.8531287f; else ZTbrQdKJK=228699226.8465567f;if (ZTbrQdKJK - ZTbrQdKJK> 0.00000001 ) ZTbrQdKJK=1107501872.0027824f; else ZTbrQdKJK=1877410210.9923770f;if (ZTbrQdKJK - ZTbrQdKJK> 0.00000001 ) ZTbrQdKJK=768049620.2061731f; else ZTbrQdKJK=450165326.2895520f;if (ZTbrQdKJK - ZTbrQdKJK> 0.00000001 ) ZTbrQdKJK=44509114.6488770f; else ZTbrQdKJK=2033051337.0768879f;if (ZTbrQdKJK - ZTbrQdKJK> 0.00000001 ) ZTbrQdKJK=2009635979.6285186f; else ZTbrQdKJK=1100912404.4148369f;if (ZTbrQdKJK - ZTbrQdKJK> 0.00000001 ) ZTbrQdKJK=380296531.3434154f; else ZTbrQdKJK=1131560273.5450103f;int yQwdLaeAw=936249501;if (yQwdLaeAw == yQwdLaeAw- 0 ) yQwdLaeAw=1260074022; else yQwdLaeAw=1831580216;if (yQwdLaeAw == yQwdLaeAw- 0 ) yQwdLaeAw=1717643823; else yQwdLaeAw=401690537;if (yQwdLaeAw == yQwdLaeAw- 0 ) yQwdLaeAw=2039011594; else yQwdLaeAw=189849292;if (yQwdLaeAw == yQwdLaeAw- 0 ) yQwdLaeAw=91519600; else yQwdLaeAw=1690527018;if (yQwdLaeAw == yQwdLaeAw- 1 ) yQwdLaeAw=112037152; else yQwdLaeAw=1438865728;if (yQwdLaeAw == yQwdLaeAw- 1 ) yQwdLaeAw=893164558; else yQwdLaeAw=1560372780;double DwEcwLUBm=1995122883.1400824;if (DwEcwLUBm == DwEcwLUBm ) DwEcwLUBm=1256741539.4789397; else DwEcwLUBm=506296885.8116791;if (DwEcwLUBm == DwEcwLUBm ) DwEcwLUBm=562152137.2293279; else DwEcwLUBm=568909226.0314885;if (DwEcwLUBm == DwEcwLUBm ) DwEcwLUBm=1770088964.9194699; else DwEcwLUBm=633837486.3651416;if (DwEcwLUBm == DwEcwLUBm ) DwEcwLUBm=1986361341.3159189; else DwEcwLUBm=498658658.3276654;if (DwEcwLUBm == DwEcwLUBm ) DwEcwLUBm=1611886609.5755130; else DwEcwLUBm=730641227.1222039;if (DwEcwLUBm == DwEcwLUBm ) DwEcwLUBm=1685600891.7539648; else DwEcwLUBm=685594471.2658167;float NoAVVrrxb=906981149.2097670f;if (NoAVVrrxb - NoAVVrrxb> 0.00000001 ) NoAVVrrxb=1177422782.8361243f; else NoAVVrrxb=2035227582.1941513f;if (NoAVVrrxb - NoAVVrrxb> 0.00000001 ) NoAVVrrxb=1017352872.9141315f; else NoAVVrrxb=298186745.1605753f;if (NoAVVrrxb - NoAVVrrxb> 0.00000001 ) NoAVVrrxb=561928548.3521074f; else NoAVVrrxb=913444554.1400965f;if (NoAVVrrxb - NoAVVrrxb> 0.00000001 ) NoAVVrrxb=501310566.9798114f; else NoAVVrrxb=1715441998.0564657f;if (NoAVVrrxb - NoAVVrrxb> 0.00000001 ) NoAVVrrxb=137179626.8766008f; else NoAVVrrxb=1564458501.5306598f;if (NoAVVrrxb - NoAVVrrxb> 0.00000001 ) NoAVVrrxb=1765373058.7414602f; else NoAVVrrxb=1476667539.0186504f; }
 NoAVVrrxby::NoAVVrrxby()
 { this->wCFNmclwrJIO("qeMuOmFYAwCFNmclwrJIOj", true, 1704484415, 631619981, 1016495072); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class zpsRfhfxry
 { 
public: bool sssTKtwgu; double sssTKtwguzpsRfhfxr; zpsRfhfxry(); void jwFzIdaUmQKP(string sssTKtwgujwFzIdaUmQKP, bool svPsmSWEF, int cFdicmrYY, float RMIIPXIuv, long qrIAQTZWg);
 protected: bool sssTKtwguo; double sssTKtwguzpsRfhfxrf; void jwFzIdaUmQKPu(string sssTKtwgujwFzIdaUmQKPg, bool svPsmSWEFe, int cFdicmrYYr, float RMIIPXIuvw, long qrIAQTZWgn);
 private: bool sssTKtwgusvPsmSWEF; double sssTKtwguRMIIPXIuvzpsRfhfxr;
 void jwFzIdaUmQKPv(string svPsmSWEFjwFzIdaUmQKP, bool svPsmSWEFcFdicmrYY, int cFdicmrYYsssTKtwgu, float RMIIPXIuvqrIAQTZWg, long qrIAQTZWgsvPsmSWEF); };
 void zpsRfhfxry::jwFzIdaUmQKP(string sssTKtwgujwFzIdaUmQKP, bool svPsmSWEF, int cFdicmrYY, float RMIIPXIuv, long qrIAQTZWg)
 { double DkWHgCScj=1376904426.2197328;if (DkWHgCScj == DkWHgCScj ) DkWHgCScj=574293854.1927478; else DkWHgCScj=990652157.7291131;if (DkWHgCScj == DkWHgCScj ) DkWHgCScj=1857835781.3510855; else DkWHgCScj=468652642.7141955;if (DkWHgCScj == DkWHgCScj ) DkWHgCScj=613249707.7122931; else DkWHgCScj=2027409943.4151742;if (DkWHgCScj == DkWHgCScj ) DkWHgCScj=1873300893.3139770; else DkWHgCScj=2127619446.7976734;if (DkWHgCScj == DkWHgCScj ) DkWHgCScj=1497677657.8976340; else DkWHgCScj=406351509.1893000;if (DkWHgCScj == DkWHgCScj ) DkWHgCScj=1008230817.4601144; else DkWHgCScj=396687637.1222860;int biJykcLoY=470371767;if (biJykcLoY == biJykcLoY- 0 ) biJykcLoY=1248681203; else biJykcLoY=1243007982;if (biJykcLoY == biJykcLoY- 0 ) biJykcLoY=189011444; else biJykcLoY=860954468;if (biJykcLoY == biJykcLoY- 0 ) biJykcLoY=66745192; else biJykcLoY=914764190;if (biJykcLoY == biJykcLoY- 1 ) biJykcLoY=332649930; else biJykcLoY=109393622;if (biJykcLoY == biJykcLoY- 1 ) biJykcLoY=1418903234; else biJykcLoY=1778752947;if (biJykcLoY == biJykcLoY- 0 ) biJykcLoY=664121770; else biJykcLoY=320014474;double EWJmckuyB=310825347.3657546;if (EWJmckuyB == EWJmckuyB ) EWJmckuyB=1290318670.9731476; else EWJmckuyB=230217697.3693906;if (EWJmckuyB == EWJmckuyB ) EWJmckuyB=475916398.9360738; else EWJmckuyB=2107342302.8606919;if (EWJmckuyB == EWJmckuyB ) EWJmckuyB=295288438.3918921; else EWJmckuyB=1899274833.5104334;if (EWJmckuyB == EWJmckuyB ) EWJmckuyB=1307839366.5531365; else EWJmckuyB=1882045080.4989292;if (EWJmckuyB == EWJmckuyB ) EWJmckuyB=1944436591.1456680; else EWJmckuyB=1024127306.7961965;if (EWJmckuyB == EWJmckuyB ) EWJmckuyB=167069444.2764043; else EWJmckuyB=1986430017.2866650;long OwiQwRmbt=1877832931;if (OwiQwRmbt == OwiQwRmbt- 0 ) OwiQwRmbt=1897116399; else OwiQwRmbt=865456438;if (OwiQwRmbt == OwiQwRmbt- 0 ) OwiQwRmbt=715087699; else OwiQwRmbt=1553532354;if (OwiQwRmbt == OwiQwRmbt- 0 ) OwiQwRmbt=833459094; else OwiQwRmbt=1318621838;if (OwiQwRmbt == OwiQwRmbt- 1 ) OwiQwRmbt=1310159234; else OwiQwRmbt=1807013311;if (OwiQwRmbt == OwiQwRmbt- 1 ) OwiQwRmbt=658002227; else OwiQwRmbt=1748442159;if (OwiQwRmbt == OwiQwRmbt- 0 ) OwiQwRmbt=1197233055; else OwiQwRmbt=981980407;int iIdorgYYg=1493955466;if (iIdorgYYg == iIdorgYYg- 0 ) iIdorgYYg=1059317112; else iIdorgYYg=697405470;if (iIdorgYYg == iIdorgYYg- 1 ) iIdorgYYg=1253852614; else iIdorgYYg=1812141608;if (iIdorgYYg == iIdorgYYg- 0 ) iIdorgYYg=6393835; else iIdorgYYg=1720163131;if (iIdorgYYg == iIdorgYYg- 0 ) iIdorgYYg=175083329; else iIdorgYYg=1496890017;if (iIdorgYYg == iIdorgYYg- 0 ) iIdorgYYg=2082652263; else iIdorgYYg=454450011;if (iIdorgYYg == iIdorgYYg- 0 ) iIdorgYYg=1064001524; else iIdorgYYg=1190101533;double zpsRfhfxr=305764762.2684648;if (zpsRfhfxr == zpsRfhfxr ) zpsRfhfxr=580831877.7798957; else zpsRfhfxr=933772486.3068222;if (zpsRfhfxr == zpsRfhfxr ) zpsRfhfxr=570381722.2264417; else zpsRfhfxr=258635593.7089778;if (zpsRfhfxr == zpsRfhfxr ) zpsRfhfxr=1436118139.3578188; else zpsRfhfxr=2088469337.1933664;if (zpsRfhfxr == zpsRfhfxr ) zpsRfhfxr=1624849900.6902121; else zpsRfhfxr=2119180479.5313321;if (zpsRfhfxr == zpsRfhfxr ) zpsRfhfxr=1067542110.8292900; else zpsRfhfxr=816386734.6012541;if (zpsRfhfxr == zpsRfhfxr ) zpsRfhfxr=1449340075.3329631; else zpsRfhfxr=694329926.1887579; }
 zpsRfhfxry::zpsRfhfxry()
 { this->jwFzIdaUmQKP("sssTKtwgujwFzIdaUmQKPj", true, 702041778, 325858959, 518756907); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class AtEtvRlyyy
 { 
public: bool oNncVqOLj; double oNncVqOLjAtEtvRlyy; AtEtvRlyyy(); void LuCbChkwUybk(string oNncVqOLjLuCbChkwUybk, bool slpyCRtjB, int CekMcrkIB, float dSVDuerQE, long toaAabFXh);
 protected: bool oNncVqOLjo; double oNncVqOLjAtEtvRlyyf; void LuCbChkwUybku(string oNncVqOLjLuCbChkwUybkg, bool slpyCRtjBe, int CekMcrkIBr, float dSVDuerQEw, long toaAabFXhn);
 private: bool oNncVqOLjslpyCRtjB; double oNncVqOLjdSVDuerQEAtEtvRlyy;
 void LuCbChkwUybkv(string slpyCRtjBLuCbChkwUybk, bool slpyCRtjBCekMcrkIB, int CekMcrkIBoNncVqOLj, float dSVDuerQEtoaAabFXh, long toaAabFXhslpyCRtjB); };
 void AtEtvRlyyy::LuCbChkwUybk(string oNncVqOLjLuCbChkwUybk, bool slpyCRtjB, int CekMcrkIB, float dSVDuerQE, long toaAabFXh)
 { double DGHqeUJkl=2058375409.1484851;if (DGHqeUJkl == DGHqeUJkl ) DGHqeUJkl=224828550.0616456; else DGHqeUJkl=1598646386.1955589;if (DGHqeUJkl == DGHqeUJkl ) DGHqeUJkl=524882181.4879878; else DGHqeUJkl=567609177.9893494;if (DGHqeUJkl == DGHqeUJkl ) DGHqeUJkl=79412877.4710326; else DGHqeUJkl=1897203747.3513506;if (DGHqeUJkl == DGHqeUJkl ) DGHqeUJkl=855541714.1323178; else DGHqeUJkl=167676781.6160932;if (DGHqeUJkl == DGHqeUJkl ) DGHqeUJkl=1687718069.9340738; else DGHqeUJkl=1432544426.2452741;if (DGHqeUJkl == DGHqeUJkl ) DGHqeUJkl=1711075012.4773729; else DGHqeUJkl=33031296.5713379;double cyZrSXJlK=138193726.3125721;if (cyZrSXJlK == cyZrSXJlK ) cyZrSXJlK=646076485.1553484; else cyZrSXJlK=224606879.9849364;if (cyZrSXJlK == cyZrSXJlK ) cyZrSXJlK=1923369602.4334116; else cyZrSXJlK=1678517876.6500748;if (cyZrSXJlK == cyZrSXJlK ) cyZrSXJlK=657406234.5852905; else cyZrSXJlK=1169325575.8210173;if (cyZrSXJlK == cyZrSXJlK ) cyZrSXJlK=1422211550.9273779; else cyZrSXJlK=1812726988.9027266;if (cyZrSXJlK == cyZrSXJlK ) cyZrSXJlK=825784315.0637475; else cyZrSXJlK=1665059122.0985797;if (cyZrSXJlK == cyZrSXJlK ) cyZrSXJlK=1447548469.1240548; else cyZrSXJlK=854682876.4481896;long SYlWyoerO=1007283491;if (SYlWyoerO == SYlWyoerO- 1 ) SYlWyoerO=676105913; else SYlWyoerO=994363149;if (SYlWyoerO == SYlWyoerO- 1 ) SYlWyoerO=1043374057; else SYlWyoerO=1000253033;if (SYlWyoerO == SYlWyoerO- 1 ) SYlWyoerO=1235733941; else SYlWyoerO=82996545;if (SYlWyoerO == SYlWyoerO- 0 ) SYlWyoerO=82891517; else SYlWyoerO=878153812;if (SYlWyoerO == SYlWyoerO- 1 ) SYlWyoerO=1318223635; else SYlWyoerO=1807763334;if (SYlWyoerO == SYlWyoerO- 1 ) SYlWyoerO=1297901398; else SYlWyoerO=1290206591;int RWfYSkxZr=826640906;if (RWfYSkxZr == RWfYSkxZr- 1 ) RWfYSkxZr=1350474837; else RWfYSkxZr=1420594251;if (RWfYSkxZr == RWfYSkxZr- 1 ) RWfYSkxZr=1433660353; else RWfYSkxZr=355925629;if (RWfYSkxZr == RWfYSkxZr- 0 ) RWfYSkxZr=2071660128; else RWfYSkxZr=47471948;if (RWfYSkxZr == RWfYSkxZr- 1 ) RWfYSkxZr=1400969175; else RWfYSkxZr=1202986622;if (RWfYSkxZr == RWfYSkxZr- 0 ) RWfYSkxZr=176434836; else RWfYSkxZr=859638840;if (RWfYSkxZr == RWfYSkxZr- 0 ) RWfYSkxZr=1889308509; else RWfYSkxZr=561837402;int SzjDYkuju=663868298;if (SzjDYkuju == SzjDYkuju- 1 ) SzjDYkuju=696988257; else SzjDYkuju=703791521;if (SzjDYkuju == SzjDYkuju- 1 ) SzjDYkuju=1504409030; else SzjDYkuju=1802351217;if (SzjDYkuju == SzjDYkuju- 1 ) SzjDYkuju=1961177935; else SzjDYkuju=284485823;if (SzjDYkuju == SzjDYkuju- 1 ) SzjDYkuju=1049943432; else SzjDYkuju=563079940;if (SzjDYkuju == SzjDYkuju- 1 ) SzjDYkuju=141715362; else SzjDYkuju=1045215790;if (SzjDYkuju == SzjDYkuju- 0 ) SzjDYkuju=360294241; else SzjDYkuju=997126547;long AtEtvRlyy=1343597452;if (AtEtvRlyy == AtEtvRlyy- 1 ) AtEtvRlyy=52027880; else AtEtvRlyy=620907563;if (AtEtvRlyy == AtEtvRlyy- 1 ) AtEtvRlyy=1651691686; else AtEtvRlyy=1111794323;if (AtEtvRlyy == AtEtvRlyy- 0 ) AtEtvRlyy=1737673065; else AtEtvRlyy=379630540;if (AtEtvRlyy == AtEtvRlyy- 1 ) AtEtvRlyy=1083107010; else AtEtvRlyy=628633965;if (AtEtvRlyy == AtEtvRlyy- 1 ) AtEtvRlyy=1740877621; else AtEtvRlyy=1987871082;if (AtEtvRlyy == AtEtvRlyy- 1 ) AtEtvRlyy=823818197; else AtEtvRlyy=376095101; }
 AtEtvRlyyy::AtEtvRlyyy()
 { this->LuCbChkwUybk("oNncVqOLjLuCbChkwUybkj", true, 341171683, 1668537762, 428498534); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class OzpTrhbgny
 { 
public: bool hPxGtITtB; double hPxGtITtBOzpTrhbgn; OzpTrhbgny(); void ugDQsiBTKxpR(string hPxGtITtBugDQsiBTKxpR, bool eaUSmCyyZ, int NdmsyuoxS, float YZecBDrLa, long SKSFylPRO);
 protected: bool hPxGtITtBo; double hPxGtITtBOzpTrhbgnf; void ugDQsiBTKxpRu(string hPxGtITtBugDQsiBTKxpRg, bool eaUSmCyyZe, int NdmsyuoxSr, float YZecBDrLaw, long SKSFylPROn);
 private: bool hPxGtITtBeaUSmCyyZ; double hPxGtITtBYZecBDrLaOzpTrhbgn;
 void ugDQsiBTKxpRv(string eaUSmCyyZugDQsiBTKxpR, bool eaUSmCyyZNdmsyuoxS, int NdmsyuoxShPxGtITtB, float YZecBDrLaSKSFylPRO, long SKSFylPROeaUSmCyyZ); };
 void OzpTrhbgny::ugDQsiBTKxpR(string hPxGtITtBugDQsiBTKxpR, bool eaUSmCyyZ, int NdmsyuoxS, float YZecBDrLa, long SKSFylPRO)
 { double pAMTkFCwY=173206708.2508590;if (pAMTkFCwY == pAMTkFCwY ) pAMTkFCwY=1816737543.8330537; else pAMTkFCwY=770773541.4248159;if (pAMTkFCwY == pAMTkFCwY ) pAMTkFCwY=14992817.9016310; else pAMTkFCwY=675031237.6664371;if (pAMTkFCwY == pAMTkFCwY ) pAMTkFCwY=1497999444.4767707; else pAMTkFCwY=2003741248.3258027;if (pAMTkFCwY == pAMTkFCwY ) pAMTkFCwY=799390306.2093033; else pAMTkFCwY=709085030.5933802;if (pAMTkFCwY == pAMTkFCwY ) pAMTkFCwY=951583090.8862661; else pAMTkFCwY=657757986.6924636;if (pAMTkFCwY == pAMTkFCwY ) pAMTkFCwY=1979810111.8783045; else pAMTkFCwY=1149028076.6724599;int NQwzVbVte=1886645660;if (NQwzVbVte == NQwzVbVte- 1 ) NQwzVbVte=1718553811; else NQwzVbVte=1699043498;if (NQwzVbVte == NQwzVbVte- 1 ) NQwzVbVte=1503047154; else NQwzVbVte=93075677;if (NQwzVbVte == NQwzVbVte- 1 ) NQwzVbVte=2095383526; else NQwzVbVte=910304819;if (NQwzVbVte == NQwzVbVte- 0 ) NQwzVbVte=729958199; else NQwzVbVte=1286591971;if (NQwzVbVte == NQwzVbVte- 1 ) NQwzVbVte=364363429; else NQwzVbVte=149672943;if (NQwzVbVte == NQwzVbVte- 0 ) NQwzVbVte=1784627670; else NQwzVbVte=181170802;float UYMGWmylG=703351497.1442464f;if (UYMGWmylG - UYMGWmylG> 0.00000001 ) UYMGWmylG=540375429.6190443f; else UYMGWmylG=2135311814.1729964f;if (UYMGWmylG - UYMGWmylG> 0.00000001 ) UYMGWmylG=873217221.6498885f; else UYMGWmylG=582874339.8932693f;if (UYMGWmylG - UYMGWmylG> 0.00000001 ) UYMGWmylG=1904601454.0269634f; else UYMGWmylG=1898522892.0635183f;if (UYMGWmylG - UYMGWmylG> 0.00000001 ) UYMGWmylG=1860350355.4624026f; else UYMGWmylG=306820893.0547909f;if (UYMGWmylG - UYMGWmylG> 0.00000001 ) UYMGWmylG=1524076914.2689502f; else UYMGWmylG=1009675312.5703307f;if (UYMGWmylG - UYMGWmylG> 0.00000001 ) UYMGWmylG=1337631218.8738125f; else UYMGWmylG=2002055324.3196780f;long KOjOalyah=1861718536;if (KOjOalyah == KOjOalyah- 1 ) KOjOalyah=594989410; else KOjOalyah=683890999;if (KOjOalyah == KOjOalyah- 1 ) KOjOalyah=65492913; else KOjOalyah=168745637;if (KOjOalyah == KOjOalyah- 1 ) KOjOalyah=484772805; else KOjOalyah=479019846;if (KOjOalyah == KOjOalyah- 0 ) KOjOalyah=225306829; else KOjOalyah=906432724;if (KOjOalyah == KOjOalyah- 1 ) KOjOalyah=40815342; else KOjOalyah=875884493;if (KOjOalyah == KOjOalyah- 1 ) KOjOalyah=310667808; else KOjOalyah=1348326501;float VnXiansco=2009667322.5108549f;if (VnXiansco - VnXiansco> 0.00000001 ) VnXiansco=1036811649.3981529f; else VnXiansco=1276458614.5769615f;if (VnXiansco - VnXiansco> 0.00000001 ) VnXiansco=608652647.2495681f; else VnXiansco=1141065792.0616687f;if (VnXiansco - VnXiansco> 0.00000001 ) VnXiansco=1004727285.6069532f; else VnXiansco=1680653755.0327192f;if (VnXiansco - VnXiansco> 0.00000001 ) VnXiansco=2129527853.7294323f; else VnXiansco=1967514566.7239793f;if (VnXiansco - VnXiansco> 0.00000001 ) VnXiansco=1986176790.4860439f; else VnXiansco=1196226261.7102943f;if (VnXiansco - VnXiansco> 0.00000001 ) VnXiansco=716482410.1796994f; else VnXiansco=1085708214.4334640f;long OzpTrhbgn=1540020374;if (OzpTrhbgn == OzpTrhbgn- 0 ) OzpTrhbgn=1311925043; else OzpTrhbgn=2070392781;if (OzpTrhbgn == OzpTrhbgn- 0 ) OzpTrhbgn=1733665039; else OzpTrhbgn=1182008565;if (OzpTrhbgn == OzpTrhbgn- 1 ) OzpTrhbgn=1023906502; else OzpTrhbgn=1599684347;if (OzpTrhbgn == OzpTrhbgn- 1 ) OzpTrhbgn=218578692; else OzpTrhbgn=61355583;if (OzpTrhbgn == OzpTrhbgn- 1 ) OzpTrhbgn=1910004985; else OzpTrhbgn=2114268144;if (OzpTrhbgn == OzpTrhbgn- 0 ) OzpTrhbgn=542058997; else OzpTrhbgn=1028716961; }
 OzpTrhbgny::OzpTrhbgny()
 { this->ugDQsiBTKxpR("hPxGtITtBugDQsiBTKxpRj", true, 1587855084, 512023854, 87707315); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class ramumYHngy
 { 
public: bool fyuxKFMsn; double fyuxKFMsnramumYHng; ramumYHngy(); void bnVMFFWwiTZK(string fyuxKFMsnbnVMFFWwiTZK, bool LDQnQihTl, int qyPGoAklh, float PgWnKRpyC, long DXWPSOHjn);
 protected: bool fyuxKFMsno; double fyuxKFMsnramumYHngf; void bnVMFFWwiTZKu(string fyuxKFMsnbnVMFFWwiTZKg, bool LDQnQihTle, int qyPGoAklhr, float PgWnKRpyCw, long DXWPSOHjnn);
 private: bool fyuxKFMsnLDQnQihTl; double fyuxKFMsnPgWnKRpyCramumYHng;
 void bnVMFFWwiTZKv(string LDQnQihTlbnVMFFWwiTZK, bool LDQnQihTlqyPGoAklh, int qyPGoAklhfyuxKFMsn, float PgWnKRpyCDXWPSOHjn, long DXWPSOHjnLDQnQihTl); };
 void ramumYHngy::bnVMFFWwiTZK(string fyuxKFMsnbnVMFFWwiTZK, bool LDQnQihTl, int qyPGoAklh, float PgWnKRpyC, long DXWPSOHjn)
 { float xHFqOvXUs=442612587.8668821f;if (xHFqOvXUs - xHFqOvXUs> 0.00000001 ) xHFqOvXUs=87329670.2274673f; else xHFqOvXUs=1909452353.9967243f;if (xHFqOvXUs - xHFqOvXUs> 0.00000001 ) xHFqOvXUs=376564466.4319263f; else xHFqOvXUs=1075475708.7877048f;if (xHFqOvXUs - xHFqOvXUs> 0.00000001 ) xHFqOvXUs=1507588307.1722170f; else xHFqOvXUs=405843210.9809146f;if (xHFqOvXUs - xHFqOvXUs> 0.00000001 ) xHFqOvXUs=1762147565.6568085f; else xHFqOvXUs=2110323120.4606695f;if (xHFqOvXUs - xHFqOvXUs> 0.00000001 ) xHFqOvXUs=107338488.4187458f; else xHFqOvXUs=183780924.2461745f;if (xHFqOvXUs - xHFqOvXUs> 0.00000001 ) xHFqOvXUs=996762183.5212372f; else xHFqOvXUs=1224074326.4290648f;long PeZrWXmKM=1161132240;if (PeZrWXmKM == PeZrWXmKM- 0 ) PeZrWXmKM=1846589216; else PeZrWXmKM=68303502;if (PeZrWXmKM == PeZrWXmKM- 0 ) PeZrWXmKM=1495206237; else PeZrWXmKM=1824190203;if (PeZrWXmKM == PeZrWXmKM- 0 ) PeZrWXmKM=215391991; else PeZrWXmKM=1232042602;if (PeZrWXmKM == PeZrWXmKM- 0 ) PeZrWXmKM=46478703; else PeZrWXmKM=1667161907;if (PeZrWXmKM == PeZrWXmKM- 1 ) PeZrWXmKM=604956526; else PeZrWXmKM=252053383;if (PeZrWXmKM == PeZrWXmKM- 0 ) PeZrWXmKM=1439486910; else PeZrWXmKM=1271913713;long LWHDzVeop=1553310721;if (LWHDzVeop == LWHDzVeop- 0 ) LWHDzVeop=786822873; else LWHDzVeop=1249614547;if (LWHDzVeop == LWHDzVeop- 1 ) LWHDzVeop=1730714659; else LWHDzVeop=1357384438;if (LWHDzVeop == LWHDzVeop- 1 ) LWHDzVeop=1225641227; else LWHDzVeop=641868595;if (LWHDzVeop == LWHDzVeop- 0 ) LWHDzVeop=1158409353; else LWHDzVeop=763842706;if (LWHDzVeop == LWHDzVeop- 1 ) LWHDzVeop=267413659; else LWHDzVeop=1264348255;if (LWHDzVeop == LWHDzVeop- 0 ) LWHDzVeop=717722295; else LWHDzVeop=1645262485;long RurAWHiVW=1865064960;if (RurAWHiVW == RurAWHiVW- 1 ) RurAWHiVW=1478369501; else RurAWHiVW=1562176222;if (RurAWHiVW == RurAWHiVW- 1 ) RurAWHiVW=1663984587; else RurAWHiVW=521982218;if (RurAWHiVW == RurAWHiVW- 1 ) RurAWHiVW=1984256413; else RurAWHiVW=2045180285;if (RurAWHiVW == RurAWHiVW- 1 ) RurAWHiVW=227220596; else RurAWHiVW=1002770715;if (RurAWHiVW == RurAWHiVW- 1 ) RurAWHiVW=1862973650; else RurAWHiVW=856886206;if (RurAWHiVW == RurAWHiVW- 1 ) RurAWHiVW=470519182; else RurAWHiVW=1255534924;long AplIVwIcL=1493840527;if (AplIVwIcL == AplIVwIcL- 1 ) AplIVwIcL=2070280381; else AplIVwIcL=1590935109;if (AplIVwIcL == AplIVwIcL- 0 ) AplIVwIcL=437251453; else AplIVwIcL=1819996017;if (AplIVwIcL == AplIVwIcL- 1 ) AplIVwIcL=327962934; else AplIVwIcL=58455868;if (AplIVwIcL == AplIVwIcL- 0 ) AplIVwIcL=2082974660; else AplIVwIcL=1204720621;if (AplIVwIcL == AplIVwIcL- 1 ) AplIVwIcL=1057377796; else AplIVwIcL=731363531;if (AplIVwIcL == AplIVwIcL- 1 ) AplIVwIcL=1556776544; else AplIVwIcL=1098527383;long ramumYHng=611069670;if (ramumYHng == ramumYHng- 1 ) ramumYHng=1801069855; else ramumYHng=1721905597;if (ramumYHng == ramumYHng- 0 ) ramumYHng=1941027859; else ramumYHng=1200189464;if (ramumYHng == ramumYHng- 0 ) ramumYHng=1244480668; else ramumYHng=1886485619;if (ramumYHng == ramumYHng- 0 ) ramumYHng=1716537955; else ramumYHng=889126235;if (ramumYHng == ramumYHng- 1 ) ramumYHng=1022393951; else ramumYHng=727943944;if (ramumYHng == ramumYHng- 0 ) ramumYHng=1641894435; else ramumYHng=368755021; }
 ramumYHngy::ramumYHngy()
 { this->bnVMFFWwiTZK("fyuxKFMsnbnVMFFWwiTZKj", true, 171349413, 2050358076, 1797486406); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class KaIfknxEFy
 { 
public: bool qWiVbFLTV; double qWiVbFLTVKaIfknxEF; KaIfknxEFy(); void JrutCTnLRejH(string qWiVbFLTVJrutCTnLRejH, bool noAjNmiUJ, int toCHPmNXL, float IvwOzQIyD, long pbQxHTWTC);
 protected: bool qWiVbFLTVo; double qWiVbFLTVKaIfknxEFf; void JrutCTnLRejHu(string qWiVbFLTVJrutCTnLRejHg, bool noAjNmiUJe, int toCHPmNXLr, float IvwOzQIyDw, long pbQxHTWTCn);
 private: bool qWiVbFLTVnoAjNmiUJ; double qWiVbFLTVIvwOzQIyDKaIfknxEF;
 void JrutCTnLRejHv(string noAjNmiUJJrutCTnLRejH, bool noAjNmiUJtoCHPmNXL, int toCHPmNXLqWiVbFLTV, float IvwOzQIyDpbQxHTWTC, long pbQxHTWTCnoAjNmiUJ); };
 void KaIfknxEFy::JrutCTnLRejH(string qWiVbFLTVJrutCTnLRejH, bool noAjNmiUJ, int toCHPmNXL, float IvwOzQIyD, long pbQxHTWTC)
 { float XQIgEjAbF=779802612.1204870f;if (XQIgEjAbF - XQIgEjAbF> 0.00000001 ) XQIgEjAbF=1573255451.3514816f; else XQIgEjAbF=1230173642.6467818f;if (XQIgEjAbF - XQIgEjAbF> 0.00000001 ) XQIgEjAbF=348098983.4273025f; else XQIgEjAbF=978442770.7667112f;if (XQIgEjAbF - XQIgEjAbF> 0.00000001 ) XQIgEjAbF=1945168744.6432811f; else XQIgEjAbF=119216058.7228189f;if (XQIgEjAbF - XQIgEjAbF> 0.00000001 ) XQIgEjAbF=743813642.9902887f; else XQIgEjAbF=700436867.0429557f;if (XQIgEjAbF - XQIgEjAbF> 0.00000001 ) XQIgEjAbF=1330155328.0678050f; else XQIgEjAbF=1620214517.0461188f;if (XQIgEjAbF - XQIgEjAbF> 0.00000001 ) XQIgEjAbF=1974075794.1560478f; else XQIgEjAbF=488979596.8754356f;float FOMdShdYy=1158284069.9313369f;if (FOMdShdYy - FOMdShdYy> 0.00000001 ) FOMdShdYy=943765994.5900111f; else FOMdShdYy=1111691258.1798668f;if (FOMdShdYy - FOMdShdYy> 0.00000001 ) FOMdShdYy=1082402722.9798807f; else FOMdShdYy=1648435368.9808840f;if (FOMdShdYy - FOMdShdYy> 0.00000001 ) FOMdShdYy=1095965102.1224773f; else FOMdShdYy=1068944025.3651854f;if (FOMdShdYy - FOMdShdYy> 0.00000001 ) FOMdShdYy=1660614406.0597781f; else FOMdShdYy=991734290.6366626f;if (FOMdShdYy - FOMdShdYy> 0.00000001 ) FOMdShdYy=2104873722.2033711f; else FOMdShdYy=1533806802.5750066f;if (FOMdShdYy - FOMdShdYy> 0.00000001 ) FOMdShdYy=24826593.2470640f; else FOMdShdYy=1730862245.4212605f;float jlDXgFgOo=1324594184.0070330f;if (jlDXgFgOo - jlDXgFgOo> 0.00000001 ) jlDXgFgOo=1362369354.0807903f; else jlDXgFgOo=497526592.4108875f;if (jlDXgFgOo - jlDXgFgOo> 0.00000001 ) jlDXgFgOo=426874528.4179003f; else jlDXgFgOo=207895404.7031015f;if (jlDXgFgOo - jlDXgFgOo> 0.00000001 ) jlDXgFgOo=1296036025.6242252f; else jlDXgFgOo=1269819773.4953770f;if (jlDXgFgOo - jlDXgFgOo> 0.00000001 ) jlDXgFgOo=711893525.8293747f; else jlDXgFgOo=1895203358.9123383f;if (jlDXgFgOo - jlDXgFgOo> 0.00000001 ) jlDXgFgOo=685565448.8860998f; else jlDXgFgOo=56043963.9667341f;if (jlDXgFgOo - jlDXgFgOo> 0.00000001 ) jlDXgFgOo=539215821.3263430f; else jlDXgFgOo=1831471558.9593788f;double NuqiscItR=781592727.2469962;if (NuqiscItR == NuqiscItR ) NuqiscItR=385615961.6737544; else NuqiscItR=1032250895.9168609;if (NuqiscItR == NuqiscItR ) NuqiscItR=539941357.6690400; else NuqiscItR=1800454216.2268809;if (NuqiscItR == NuqiscItR ) NuqiscItR=2133913293.9751117; else NuqiscItR=1916040894.6524828;if (NuqiscItR == NuqiscItR ) NuqiscItR=1831321157.8712947; else NuqiscItR=504311426.8795734;if (NuqiscItR == NuqiscItR ) NuqiscItR=1717042883.6808550; else NuqiscItR=1503848340.5175930;if (NuqiscItR == NuqiscItR ) NuqiscItR=1021052695.2776824; else NuqiscItR=411361942.5660631;int egXoLEjLe=935868028;if (egXoLEjLe == egXoLEjLe- 1 ) egXoLEjLe=468551460; else egXoLEjLe=649481610;if (egXoLEjLe == egXoLEjLe- 0 ) egXoLEjLe=1274093889; else egXoLEjLe=71251173;if (egXoLEjLe == egXoLEjLe- 0 ) egXoLEjLe=91770011; else egXoLEjLe=1923541950;if (egXoLEjLe == egXoLEjLe- 1 ) egXoLEjLe=2009731691; else egXoLEjLe=1821429868;if (egXoLEjLe == egXoLEjLe- 1 ) egXoLEjLe=399797733; else egXoLEjLe=1334683011;if (egXoLEjLe == egXoLEjLe- 0 ) egXoLEjLe=962869920; else egXoLEjLe=1039921139;long KaIfknxEF=1692672827;if (KaIfknxEF == KaIfknxEF- 1 ) KaIfknxEF=1922044020; else KaIfknxEF=1390717513;if (KaIfknxEF == KaIfknxEF- 0 ) KaIfknxEF=1345246284; else KaIfknxEF=579043673;if (KaIfknxEF == KaIfknxEF- 0 ) KaIfknxEF=2001829590; else KaIfknxEF=1498692488;if (KaIfknxEF == KaIfknxEF- 1 ) KaIfknxEF=1338164538; else KaIfknxEF=1593812107;if (KaIfknxEF == KaIfknxEF- 0 ) KaIfknxEF=813689082; else KaIfknxEF=2070046749;if (KaIfknxEF == KaIfknxEF- 0 ) KaIfknxEF=638336168; else KaIfknxEF=1939671332; }
 KaIfknxEFy::KaIfknxEFy()
 { this->JrutCTnLRejH("qWiVbFLTVJrutCTnLRejHj", true, 248767078, 300531583, 1800813893); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class djDaivpiny
 { 
public: bool LhkEYUKbF; double LhkEYUKbFdjDaivpin; djDaivpiny(); void XfHKXKoEcYfi(string LhkEYUKbFXfHKXKoEcYfi, bool MbGEvPKkB, int eLTfyzrkU, float QHCREMsDL, long eCEeCigiA);
 protected: bool LhkEYUKbFo; double LhkEYUKbFdjDaivpinf; void XfHKXKoEcYfiu(string LhkEYUKbFXfHKXKoEcYfig, bool MbGEvPKkBe, int eLTfyzrkUr, float QHCREMsDLw, long eCEeCigiAn);
 private: bool LhkEYUKbFMbGEvPKkB; double LhkEYUKbFQHCREMsDLdjDaivpin;
 void XfHKXKoEcYfiv(string MbGEvPKkBXfHKXKoEcYfi, bool MbGEvPKkBeLTfyzrkU, int eLTfyzrkULhkEYUKbF, float QHCREMsDLeCEeCigiA, long eCEeCigiAMbGEvPKkB); };
 void djDaivpiny::XfHKXKoEcYfi(string LhkEYUKbFXfHKXKoEcYfi, bool MbGEvPKkB, int eLTfyzrkU, float QHCREMsDL, long eCEeCigiA)
 { double uXfyvetMm=1049208491.1222840;if (uXfyvetMm == uXfyvetMm ) uXfyvetMm=1991331225.2909010; else uXfyvetMm=221368795.7642547;if (uXfyvetMm == uXfyvetMm ) uXfyvetMm=709670632.5084223; else uXfyvetMm=1378887241.0273184;if (uXfyvetMm == uXfyvetMm ) uXfyvetMm=1954757607.4941634; else uXfyvetMm=668801667.2617578;if (uXfyvetMm == uXfyvetMm ) uXfyvetMm=1706570901.8170817; else uXfyvetMm=2101674957.2496383;if (uXfyvetMm == uXfyvetMm ) uXfyvetMm=485910730.8469463; else uXfyvetMm=1146237455.7020133;if (uXfyvetMm == uXfyvetMm ) uXfyvetMm=991027866.5878652; else uXfyvetMm=564025850.1033773;float aXQcHWLZp=432770665.0785277f;if (aXQcHWLZp - aXQcHWLZp> 0.00000001 ) aXQcHWLZp=1071801399.6443450f; else aXQcHWLZp=1628434909.7920976f;if (aXQcHWLZp - aXQcHWLZp> 0.00000001 ) aXQcHWLZp=1074561825.3221411f; else aXQcHWLZp=1232066247.4172242f;if (aXQcHWLZp - aXQcHWLZp> 0.00000001 ) aXQcHWLZp=1363457214.4885260f; else aXQcHWLZp=1390681808.6043922f;if (aXQcHWLZp - aXQcHWLZp> 0.00000001 ) aXQcHWLZp=977134922.1137607f; else aXQcHWLZp=1372304226.5759762f;if (aXQcHWLZp - aXQcHWLZp> 0.00000001 ) aXQcHWLZp=197983172.4712183f; else aXQcHWLZp=1636187266.1457167f;if (aXQcHWLZp - aXQcHWLZp> 0.00000001 ) aXQcHWLZp=1827169480.2885904f; else aXQcHWLZp=674121509.1566450f;double PiZAnMPSF=27069761.1609666;if (PiZAnMPSF == PiZAnMPSF ) PiZAnMPSF=1608816798.5617566; else PiZAnMPSF=1759312972.0797798;if (PiZAnMPSF == PiZAnMPSF ) PiZAnMPSF=1284371966.8555705; else PiZAnMPSF=982405515.9526464;if (PiZAnMPSF == PiZAnMPSF ) PiZAnMPSF=617075798.8785502; else PiZAnMPSF=13165476.7673841;if (PiZAnMPSF == PiZAnMPSF ) PiZAnMPSF=9952523.5196484; else PiZAnMPSF=204741504.1549617;if (PiZAnMPSF == PiZAnMPSF ) PiZAnMPSF=1576385840.1912122; else PiZAnMPSF=310716906.0222961;if (PiZAnMPSF == PiZAnMPSF ) PiZAnMPSF=2066790541.0830655; else PiZAnMPSF=1474678719.5411818;long ShvrcfgeG=784939151;if (ShvrcfgeG == ShvrcfgeG- 1 ) ShvrcfgeG=1268996052; else ShvrcfgeG=1910536102;if (ShvrcfgeG == ShvrcfgeG- 0 ) ShvrcfgeG=2138433031; else ShvrcfgeG=6207150;if (ShvrcfgeG == ShvrcfgeG- 0 ) ShvrcfgeG=1485913234; else ShvrcfgeG=1334717682;if (ShvrcfgeG == ShvrcfgeG- 0 ) ShvrcfgeG=1833234924; else ShvrcfgeG=600649417;if (ShvrcfgeG == ShvrcfgeG- 0 ) ShvrcfgeG=1391717520; else ShvrcfgeG=1484850053;if (ShvrcfgeG == ShvrcfgeG- 0 ) ShvrcfgeG=1180904069; else ShvrcfgeG=318570341;int mYwjcyMHs=420041237;if (mYwjcyMHs == mYwjcyMHs- 1 ) mYwjcyMHs=1502020192; else mYwjcyMHs=963958105;if (mYwjcyMHs == mYwjcyMHs- 1 ) mYwjcyMHs=1102692699; else mYwjcyMHs=750181398;if (mYwjcyMHs == mYwjcyMHs- 0 ) mYwjcyMHs=1562489307; else mYwjcyMHs=301344051;if (mYwjcyMHs == mYwjcyMHs- 0 ) mYwjcyMHs=1963178514; else mYwjcyMHs=1058635923;if (mYwjcyMHs == mYwjcyMHs- 1 ) mYwjcyMHs=1618482386; else mYwjcyMHs=869820321;if (mYwjcyMHs == mYwjcyMHs- 1 ) mYwjcyMHs=1803164054; else mYwjcyMHs=1052740308;double djDaivpin=763722127.7381941;if (djDaivpin == djDaivpin ) djDaivpin=263705233.9593917; else djDaivpin=1042230329.7002804;if (djDaivpin == djDaivpin ) djDaivpin=1552609104.0413279; else djDaivpin=597224588.6174569;if (djDaivpin == djDaivpin ) djDaivpin=74920109.8362368; else djDaivpin=1785493760.6643296;if (djDaivpin == djDaivpin ) djDaivpin=688640174.9148748; else djDaivpin=274099116.9888834;if (djDaivpin == djDaivpin ) djDaivpin=2073561695.5294689; else djDaivpin=683722549.7515564;if (djDaivpin == djDaivpin ) djDaivpin=1738171642.9801938; else djDaivpin=1279709392.0479229; }
 djDaivpiny::djDaivpiny()
 { this->XfHKXKoEcYfi("LhkEYUKbFXfHKXKoEcYfij", true, 979745054, 1838865829, 1363109317); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class ltKtdXTMqy
 { 
public: bool vaMsVUSWL; double vaMsVUSWLltKtdXTMq; ltKtdXTMqy(); void ibBHibmThydK(string vaMsVUSWLibBHibmThydK, bool eHCSImuwh, int sIWRPCavr, float nbCSEouFO, long GOCXorgvx);
 protected: bool vaMsVUSWLo; double vaMsVUSWLltKtdXTMqf; void ibBHibmThydKu(string vaMsVUSWLibBHibmThydKg, bool eHCSImuwhe, int sIWRPCavrr, float nbCSEouFOw, long GOCXorgvxn);
 private: bool vaMsVUSWLeHCSImuwh; double vaMsVUSWLnbCSEouFOltKtdXTMq;
 void ibBHibmThydKv(string eHCSImuwhibBHibmThydK, bool eHCSImuwhsIWRPCavr, int sIWRPCavrvaMsVUSWL, float nbCSEouFOGOCXorgvx, long GOCXorgvxeHCSImuwh); };
 void ltKtdXTMqy::ibBHibmThydK(string vaMsVUSWLibBHibmThydK, bool eHCSImuwh, int sIWRPCavr, float nbCSEouFO, long GOCXorgvx)
 { float wHEKVpRIQ=1761110137.0239848f;if (wHEKVpRIQ - wHEKVpRIQ> 0.00000001 ) wHEKVpRIQ=1985335181.1405030f; else wHEKVpRIQ=635274661.7381002f;if (wHEKVpRIQ - wHEKVpRIQ> 0.00000001 ) wHEKVpRIQ=877655173.2815238f; else wHEKVpRIQ=641104168.7863993f;if (wHEKVpRIQ - wHEKVpRIQ> 0.00000001 ) wHEKVpRIQ=377645345.1525423f; else wHEKVpRIQ=393169632.0587233f;if (wHEKVpRIQ - wHEKVpRIQ> 0.00000001 ) wHEKVpRIQ=292640929.3815879f; else wHEKVpRIQ=1479062751.4256115f;if (wHEKVpRIQ - wHEKVpRIQ> 0.00000001 ) wHEKVpRIQ=664370318.7421487f; else wHEKVpRIQ=855040041.9666993f;if (wHEKVpRIQ - wHEKVpRIQ> 0.00000001 ) wHEKVpRIQ=1131192015.4481164f; else wHEKVpRIQ=2131552084.1692357f;double nwPFrPEdf=745769257.9406288;if (nwPFrPEdf == nwPFrPEdf ) nwPFrPEdf=940514429.8264761; else nwPFrPEdf=914915791.8847864;if (nwPFrPEdf == nwPFrPEdf ) nwPFrPEdf=1535490435.3831233; else nwPFrPEdf=1559767915.0657432;if (nwPFrPEdf == nwPFrPEdf ) nwPFrPEdf=1112220458.5253729; else nwPFrPEdf=1630024165.3616189;if (nwPFrPEdf == nwPFrPEdf ) nwPFrPEdf=1721234614.6919747; else nwPFrPEdf=2093082700.7750658;if (nwPFrPEdf == nwPFrPEdf ) nwPFrPEdf=304796116.6273404; else nwPFrPEdf=398149857.7051561;if (nwPFrPEdf == nwPFrPEdf ) nwPFrPEdf=278034925.3251545; else nwPFrPEdf=612540811.8487069;long yLGhCfSUP=849838149;if (yLGhCfSUP == yLGhCfSUP- 1 ) yLGhCfSUP=92997975; else yLGhCfSUP=1897477697;if (yLGhCfSUP == yLGhCfSUP- 1 ) yLGhCfSUP=1523245269; else yLGhCfSUP=1895686293;if (yLGhCfSUP == yLGhCfSUP- 0 ) yLGhCfSUP=2095630924; else yLGhCfSUP=1950132178;if (yLGhCfSUP == yLGhCfSUP- 1 ) yLGhCfSUP=1907884806; else yLGhCfSUP=426061592;if (yLGhCfSUP == yLGhCfSUP- 0 ) yLGhCfSUP=908119073; else yLGhCfSUP=764868024;if (yLGhCfSUP == yLGhCfSUP- 0 ) yLGhCfSUP=1868511733; else yLGhCfSUP=287322569;float esngUNoCG=375387137.8448330f;if (esngUNoCG - esngUNoCG> 0.00000001 ) esngUNoCG=1203989552.9190186f; else esngUNoCG=1898921528.0717184f;if (esngUNoCG - esngUNoCG> 0.00000001 ) esngUNoCG=703197049.4550079f; else esngUNoCG=92000724.1664391f;if (esngUNoCG - esngUNoCG> 0.00000001 ) esngUNoCG=814396320.6924847f; else esngUNoCG=878251847.5573966f;if (esngUNoCG - esngUNoCG> 0.00000001 ) esngUNoCG=648889679.3130605f; else esngUNoCG=355311016.9083719f;if (esngUNoCG - esngUNoCG> 0.00000001 ) esngUNoCG=1061523694.5478064f; else esngUNoCG=932056120.8044489f;if (esngUNoCG - esngUNoCG> 0.00000001 ) esngUNoCG=336308052.1981149f; else esngUNoCG=2126979135.6348967f;double SEEQqvIxa=1021876925.8684136;if (SEEQqvIxa == SEEQqvIxa ) SEEQqvIxa=422032905.0391558; else SEEQqvIxa=281353866.7864510;if (SEEQqvIxa == SEEQqvIxa ) SEEQqvIxa=2038554109.1338521; else SEEQqvIxa=2052203475.8373286;if (SEEQqvIxa == SEEQqvIxa ) SEEQqvIxa=1006942642.9646449; else SEEQqvIxa=605154026.6602214;if (SEEQqvIxa == SEEQqvIxa ) SEEQqvIxa=797621980.4135068; else SEEQqvIxa=1137865898.4577263;if (SEEQqvIxa == SEEQqvIxa ) SEEQqvIxa=1154514632.1284829; else SEEQqvIxa=1109428843.2381715;if (SEEQqvIxa == SEEQqvIxa ) SEEQqvIxa=651648842.8464184; else SEEQqvIxa=347352434.2592395;int ltKtdXTMq=970626823;if (ltKtdXTMq == ltKtdXTMq- 0 ) ltKtdXTMq=253245470; else ltKtdXTMq=2050131435;if (ltKtdXTMq == ltKtdXTMq- 0 ) ltKtdXTMq=1556034906; else ltKtdXTMq=1986728073;if (ltKtdXTMq == ltKtdXTMq- 1 ) ltKtdXTMq=1086779991; else ltKtdXTMq=341006412;if (ltKtdXTMq == ltKtdXTMq- 1 ) ltKtdXTMq=35441829; else ltKtdXTMq=1362229775;if (ltKtdXTMq == ltKtdXTMq- 1 ) ltKtdXTMq=1248588018; else ltKtdXTMq=1167934253;if (ltKtdXTMq == ltKtdXTMq- 1 ) ltKtdXTMq=834162599; else ltKtdXTMq=1163574804; }
 ltKtdXTMqy::ltKtdXTMqy()
 { this->ibBHibmThydK("vaMsVUSWLibBHibmThydKj", true, 1613824126, 1928389318, 310926885); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class RgVlKwGhvy
 { 
public: bool EicGeebJA; double EicGeebJARgVlKwGhv; RgVlKwGhvy(); void aUqsouDMiKjI(string EicGeebJAaUqsouDMiKjI, bool nwqMetWBC, int VNCVaHTRt, float tQEolaVLK, long XWfwqEyeR);
 protected: bool EicGeebJAo; double EicGeebJARgVlKwGhvf; void aUqsouDMiKjIu(string EicGeebJAaUqsouDMiKjIg, bool nwqMetWBCe, int VNCVaHTRtr, float tQEolaVLKw, long XWfwqEyeRn);
 private: bool EicGeebJAnwqMetWBC; double EicGeebJAtQEolaVLKRgVlKwGhv;
 void aUqsouDMiKjIv(string nwqMetWBCaUqsouDMiKjI, bool nwqMetWBCVNCVaHTRt, int VNCVaHTRtEicGeebJA, float tQEolaVLKXWfwqEyeR, long XWfwqEyeRnwqMetWBC); };
 void RgVlKwGhvy::aUqsouDMiKjI(string EicGeebJAaUqsouDMiKjI, bool nwqMetWBC, int VNCVaHTRt, float tQEolaVLK, long XWfwqEyeR)
 { int bbJkufLOw=1065625401;if (bbJkufLOw == bbJkufLOw- 1 ) bbJkufLOw=980238570; else bbJkufLOw=1637993231;if (bbJkufLOw == bbJkufLOw- 0 ) bbJkufLOw=436093880; else bbJkufLOw=1220607062;if (bbJkufLOw == bbJkufLOw- 1 ) bbJkufLOw=1953421088; else bbJkufLOw=625688803;if (bbJkufLOw == bbJkufLOw- 0 ) bbJkufLOw=1480241037; else bbJkufLOw=1622509895;if (bbJkufLOw == bbJkufLOw- 1 ) bbJkufLOw=639700082; else bbJkufLOw=1425297370;if (bbJkufLOw == bbJkufLOw- 0 ) bbJkufLOw=741892863; else bbJkufLOw=1766214140;double AttrujJnT=1972117006.9449600;if (AttrujJnT == AttrujJnT ) AttrujJnT=166087897.1547065; else AttrujJnT=826646080.0536937;if (AttrujJnT == AttrujJnT ) AttrujJnT=1541721522.5825601; else AttrujJnT=500277310.5026995;if (AttrujJnT == AttrujJnT ) AttrujJnT=1542651648.4216399; else AttrujJnT=1249102545.6434470;if (AttrujJnT == AttrujJnT ) AttrujJnT=1929327366.8539605; else AttrujJnT=721415797.7350096;if (AttrujJnT == AttrujJnT ) AttrujJnT=336440679.5221717; else AttrujJnT=1908467833.3217589;if (AttrujJnT == AttrujJnT ) AttrujJnT=876192530.4913427; else AttrujJnT=2047880897.6073018;long hcMzODNEN=330785036;if (hcMzODNEN == hcMzODNEN- 0 ) hcMzODNEN=340205282; else hcMzODNEN=1774407411;if (hcMzODNEN == hcMzODNEN- 1 ) hcMzODNEN=1432302193; else hcMzODNEN=1333175043;if (hcMzODNEN == hcMzODNEN- 1 ) hcMzODNEN=682393735; else hcMzODNEN=1723057380;if (hcMzODNEN == hcMzODNEN- 1 ) hcMzODNEN=865149350; else hcMzODNEN=30198374;if (hcMzODNEN == hcMzODNEN- 1 ) hcMzODNEN=1237925897; else hcMzODNEN=1879962093;if (hcMzODNEN == hcMzODNEN- 1 ) hcMzODNEN=445178200; else hcMzODNEN=526920207;float IfcJwtiod=533441753.7195128f;if (IfcJwtiod - IfcJwtiod> 0.00000001 ) IfcJwtiod=903685704.4467758f; else IfcJwtiod=3501032.3809897f;if (IfcJwtiod - IfcJwtiod> 0.00000001 ) IfcJwtiod=1875333854.8266180f; else IfcJwtiod=243272410.2082556f;if (IfcJwtiod - IfcJwtiod> 0.00000001 ) IfcJwtiod=462666148.1511882f; else IfcJwtiod=44489846.7686222f;if (IfcJwtiod - IfcJwtiod> 0.00000001 ) IfcJwtiod=1670457400.9597500f; else IfcJwtiod=1878619672.9491493f;if (IfcJwtiod - IfcJwtiod> 0.00000001 ) IfcJwtiod=1856149512.5863133f; else IfcJwtiod=1862161730.3980161f;if (IfcJwtiod - IfcJwtiod> 0.00000001 ) IfcJwtiod=884166383.7810783f; else IfcJwtiod=44953255.6051562f;float JzUytMoKO=177130383.6032282f;if (JzUytMoKO - JzUytMoKO> 0.00000001 ) JzUytMoKO=1290597209.4113135f; else JzUytMoKO=411107827.9046612f;if (JzUytMoKO - JzUytMoKO> 0.00000001 ) JzUytMoKO=1426008858.6300394f; else JzUytMoKO=1478110927.0584501f;if (JzUytMoKO - JzUytMoKO> 0.00000001 ) JzUytMoKO=1901173873.1666457f; else JzUytMoKO=755920468.6466656f;if (JzUytMoKO - JzUytMoKO> 0.00000001 ) JzUytMoKO=1289723271.0969271f; else JzUytMoKO=590514164.7430085f;if (JzUytMoKO - JzUytMoKO> 0.00000001 ) JzUytMoKO=2108980377.7307449f; else JzUytMoKO=1511523148.5803761f;if (JzUytMoKO - JzUytMoKO> 0.00000001 ) JzUytMoKO=1409835060.0457490f; else JzUytMoKO=1810173202.6264304f;int RgVlKwGhv=1680725200;if (RgVlKwGhv == RgVlKwGhv- 0 ) RgVlKwGhv=810177238; else RgVlKwGhv=342750777;if (RgVlKwGhv == RgVlKwGhv- 1 ) RgVlKwGhv=1144195193; else RgVlKwGhv=750135223;if (RgVlKwGhv == RgVlKwGhv- 0 ) RgVlKwGhv=734719492; else RgVlKwGhv=2038911398;if (RgVlKwGhv == RgVlKwGhv- 1 ) RgVlKwGhv=2015602535; else RgVlKwGhv=295715436;if (RgVlKwGhv == RgVlKwGhv- 1 ) RgVlKwGhv=103950011; else RgVlKwGhv=1701166168;if (RgVlKwGhv == RgVlKwGhv- 1 ) RgVlKwGhv=1624509178; else RgVlKwGhv=967715652; }
 RgVlKwGhvy::RgVlKwGhvy()
 { this->aUqsouDMiKjI("EicGeebJAaUqsouDMiKjIj", true, 838890997, 820196095, 280702101); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class JhfsRpwkfy
 { 
public: bool DMKFMvvdO; double DMKFMvvdOJhfsRpwkf; JhfsRpwkfy(); void sRzLLXhjjrBK(string DMKFMvvdOsRzLLXhjjrBK, bool fARPfgFSO, int BwWBCSMaJ, float qABbtypqJ, long XgYBePrYG);
 protected: bool DMKFMvvdOo; double DMKFMvvdOJhfsRpwkff; void sRzLLXhjjrBKu(string DMKFMvvdOsRzLLXhjjrBKg, bool fARPfgFSOe, int BwWBCSMaJr, float qABbtypqJw, long XgYBePrYGn);
 private: bool DMKFMvvdOfARPfgFSO; double DMKFMvvdOqABbtypqJJhfsRpwkf;
 void sRzLLXhjjrBKv(string fARPfgFSOsRzLLXhjjrBK, bool fARPfgFSOBwWBCSMaJ, int BwWBCSMaJDMKFMvvdO, float qABbtypqJXgYBePrYG, long XgYBePrYGfARPfgFSO); };
 void JhfsRpwkfy::sRzLLXhjjrBK(string DMKFMvvdOsRzLLXhjjrBK, bool fARPfgFSO, int BwWBCSMaJ, float qABbtypqJ, long XgYBePrYG)
 { float ujxrfYmvV=796387635.9522135f;if (ujxrfYmvV - ujxrfYmvV> 0.00000001 ) ujxrfYmvV=1154901737.3879750f; else ujxrfYmvV=1748163214.5738816f;if (ujxrfYmvV - ujxrfYmvV> 0.00000001 ) ujxrfYmvV=42929364.8655161f; else ujxrfYmvV=2084666842.5247353f;if (ujxrfYmvV - ujxrfYmvV> 0.00000001 ) ujxrfYmvV=167775730.3553772f; else ujxrfYmvV=1064512385.8796669f;if (ujxrfYmvV - ujxrfYmvV> 0.00000001 ) ujxrfYmvV=577658394.9977832f; else ujxrfYmvV=124435966.0770758f;if (ujxrfYmvV - ujxrfYmvV> 0.00000001 ) ujxrfYmvV=1433095622.6435083f; else ujxrfYmvV=1949859787.2961440f;if (ujxrfYmvV - ujxrfYmvV> 0.00000001 ) ujxrfYmvV=1682403427.9795136f; else ujxrfYmvV=1027756200.3815323f;long mNyOVIUfH=791353105;if (mNyOVIUfH == mNyOVIUfH- 0 ) mNyOVIUfH=1067104694; else mNyOVIUfH=1582812973;if (mNyOVIUfH == mNyOVIUfH- 1 ) mNyOVIUfH=1967631139; else mNyOVIUfH=865381743;if (mNyOVIUfH == mNyOVIUfH- 1 ) mNyOVIUfH=2102765055; else mNyOVIUfH=1962521605;if (mNyOVIUfH == mNyOVIUfH- 0 ) mNyOVIUfH=1780525321; else mNyOVIUfH=338438583;if (mNyOVIUfH == mNyOVIUfH- 0 ) mNyOVIUfH=938401192; else mNyOVIUfH=2143277536;if (mNyOVIUfH == mNyOVIUfH- 1 ) mNyOVIUfH=1238477672; else mNyOVIUfH=13205503;long lyIiRdXBr=1966013279;if (lyIiRdXBr == lyIiRdXBr- 1 ) lyIiRdXBr=491108244; else lyIiRdXBr=1395371627;if (lyIiRdXBr == lyIiRdXBr- 0 ) lyIiRdXBr=959144239; else lyIiRdXBr=1272842035;if (lyIiRdXBr == lyIiRdXBr- 1 ) lyIiRdXBr=340390443; else lyIiRdXBr=1234448244;if (lyIiRdXBr == lyIiRdXBr- 0 ) lyIiRdXBr=783058308; else lyIiRdXBr=230131499;if (lyIiRdXBr == lyIiRdXBr- 0 ) lyIiRdXBr=1420633599; else lyIiRdXBr=1334573883;if (lyIiRdXBr == lyIiRdXBr- 1 ) lyIiRdXBr=1600791697; else lyIiRdXBr=437287761;int CFdyLSPWg=1868462802;if (CFdyLSPWg == CFdyLSPWg- 1 ) CFdyLSPWg=303607592; else CFdyLSPWg=1014910044;if (CFdyLSPWg == CFdyLSPWg- 0 ) CFdyLSPWg=1658418926; else CFdyLSPWg=2072017583;if (CFdyLSPWg == CFdyLSPWg- 0 ) CFdyLSPWg=1727427930; else CFdyLSPWg=790126237;if (CFdyLSPWg == CFdyLSPWg- 1 ) CFdyLSPWg=841106227; else CFdyLSPWg=1339863779;if (CFdyLSPWg == CFdyLSPWg- 0 ) CFdyLSPWg=2115121540; else CFdyLSPWg=1851974428;if (CFdyLSPWg == CFdyLSPWg- 1 ) CFdyLSPWg=1146265650; else CFdyLSPWg=171981841;float kBMpudjNj=1737322779.9596069f;if (kBMpudjNj - kBMpudjNj> 0.00000001 ) kBMpudjNj=3170959.2416514f; else kBMpudjNj=1863873795.3362965f;if (kBMpudjNj - kBMpudjNj> 0.00000001 ) kBMpudjNj=536647956.8437718f; else kBMpudjNj=748245416.4317183f;if (kBMpudjNj - kBMpudjNj> 0.00000001 ) kBMpudjNj=1691358859.2821101f; else kBMpudjNj=1498926768.9071624f;if (kBMpudjNj - kBMpudjNj> 0.00000001 ) kBMpudjNj=450962662.8648602f; else kBMpudjNj=1980140097.1604518f;if (kBMpudjNj - kBMpudjNj> 0.00000001 ) kBMpudjNj=799754665.1005322f; else kBMpudjNj=1737499640.5528749f;if (kBMpudjNj - kBMpudjNj> 0.00000001 ) kBMpudjNj=1592231791.5661957f; else kBMpudjNj=768191172.8805921f;int JhfsRpwkf=2106859727;if (JhfsRpwkf == JhfsRpwkf- 1 ) JhfsRpwkf=955139238; else JhfsRpwkf=1517498517;if (JhfsRpwkf == JhfsRpwkf- 1 ) JhfsRpwkf=1857081558; else JhfsRpwkf=244453550;if (JhfsRpwkf == JhfsRpwkf- 1 ) JhfsRpwkf=184837564; else JhfsRpwkf=2022154892;if (JhfsRpwkf == JhfsRpwkf- 1 ) JhfsRpwkf=238585349; else JhfsRpwkf=1848465654;if (JhfsRpwkf == JhfsRpwkf- 0 ) JhfsRpwkf=554265400; else JhfsRpwkf=1766764107;if (JhfsRpwkf == JhfsRpwkf- 1 ) JhfsRpwkf=1305204142; else JhfsRpwkf=635899662; }
 JhfsRpwkfy::JhfsRpwkfy()
 { this->sRzLLXhjjrBK("DMKFMvvdOsRzLLXhjjrBKj", true, 88182594, 611076467, 404096786); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class OSpIIcauOy
 { 
public: bool YMpwYQcQB; double YMpwYQcQBOSpIIcauO; OSpIIcauOy(); void mYncXcJAxfRs(string YMpwYQcQBmYncXcJAxfRs, bool excuCflzR, int uRBHUreFj, float jcLTvsSrI, long UIHqOhWoH);
 protected: bool YMpwYQcQBo; double YMpwYQcQBOSpIIcauOf; void mYncXcJAxfRsu(string YMpwYQcQBmYncXcJAxfRsg, bool excuCflzRe, int uRBHUreFjr, float jcLTvsSrIw, long UIHqOhWoHn);
 private: bool YMpwYQcQBexcuCflzR; double YMpwYQcQBjcLTvsSrIOSpIIcauO;
 void mYncXcJAxfRsv(string excuCflzRmYncXcJAxfRs, bool excuCflzRuRBHUreFj, int uRBHUreFjYMpwYQcQB, float jcLTvsSrIUIHqOhWoH, long UIHqOhWoHexcuCflzR); };
 void OSpIIcauOy::mYncXcJAxfRs(string YMpwYQcQBmYncXcJAxfRs, bool excuCflzR, int uRBHUreFj, float jcLTvsSrI, long UIHqOhWoH)
 { float YSAjrznBg=1590255293.7442919f;if (YSAjrznBg - YSAjrznBg> 0.00000001 ) YSAjrznBg=2016572909.9403338f; else YSAjrznBg=2129731200.5611921f;if (YSAjrznBg - YSAjrznBg> 0.00000001 ) YSAjrznBg=1563798799.6510628f; else YSAjrznBg=1435451182.5457070f;if (YSAjrznBg - YSAjrznBg> 0.00000001 ) YSAjrznBg=495626928.6708243f; else YSAjrznBg=838763805.6306182f;if (YSAjrznBg - YSAjrznBg> 0.00000001 ) YSAjrznBg=1367938221.6994852f; else YSAjrznBg=557842746.0433014f;if (YSAjrznBg - YSAjrznBg> 0.00000001 ) YSAjrznBg=1314913767.1573689f; else YSAjrznBg=2023208137.0247990f;if (YSAjrznBg - YSAjrznBg> 0.00000001 ) YSAjrznBg=1279363061.3146469f; else YSAjrznBg=1850724049.5742397f;long iZLNuapQP=1174053564;if (iZLNuapQP == iZLNuapQP- 1 ) iZLNuapQP=163558902; else iZLNuapQP=1628035671;if (iZLNuapQP == iZLNuapQP- 0 ) iZLNuapQP=701076606; else iZLNuapQP=1624360206;if (iZLNuapQP == iZLNuapQP- 1 ) iZLNuapQP=123638938; else iZLNuapQP=731061033;if (iZLNuapQP == iZLNuapQP- 0 ) iZLNuapQP=544820652; else iZLNuapQP=1816629410;if (iZLNuapQP == iZLNuapQP- 0 ) iZLNuapQP=1561082554; else iZLNuapQP=1025179098;if (iZLNuapQP == iZLNuapQP- 1 ) iZLNuapQP=1550350932; else iZLNuapQP=700856749;long NatmLVNrf=1870404695;if (NatmLVNrf == NatmLVNrf- 0 ) NatmLVNrf=68744314; else NatmLVNrf=1908821094;if (NatmLVNrf == NatmLVNrf- 0 ) NatmLVNrf=1091988521; else NatmLVNrf=498417643;if (NatmLVNrf == NatmLVNrf- 0 ) NatmLVNrf=2020128761; else NatmLVNrf=1059142780;if (NatmLVNrf == NatmLVNrf- 1 ) NatmLVNrf=125099732; else NatmLVNrf=1035016203;if (NatmLVNrf == NatmLVNrf- 0 ) NatmLVNrf=1649632455; else NatmLVNrf=283786049;if (NatmLVNrf == NatmLVNrf- 0 ) NatmLVNrf=524637844; else NatmLVNrf=1950617673;float UaAOaHJtQ=456113366.5061132f;if (UaAOaHJtQ - UaAOaHJtQ> 0.00000001 ) UaAOaHJtQ=1540198497.7285407f; else UaAOaHJtQ=677578191.8101632f;if (UaAOaHJtQ - UaAOaHJtQ> 0.00000001 ) UaAOaHJtQ=1286482621.2782546f; else UaAOaHJtQ=2016396073.7409442f;if (UaAOaHJtQ - UaAOaHJtQ> 0.00000001 ) UaAOaHJtQ=1583858816.2567814f; else UaAOaHJtQ=907585646.7434156f;if (UaAOaHJtQ - UaAOaHJtQ> 0.00000001 ) UaAOaHJtQ=1466616355.2469584f; else UaAOaHJtQ=1285511876.3807070f;if (UaAOaHJtQ - UaAOaHJtQ> 0.00000001 ) UaAOaHJtQ=1584910548.9870767f; else UaAOaHJtQ=1894653036.7549295f;if (UaAOaHJtQ - UaAOaHJtQ> 0.00000001 ) UaAOaHJtQ=2021852275.3685905f; else UaAOaHJtQ=1617931477.0419789f;int gApUSmegV=721244780;if (gApUSmegV == gApUSmegV- 1 ) gApUSmegV=1970243993; else gApUSmegV=1556442013;if (gApUSmegV == gApUSmegV- 0 ) gApUSmegV=1781979735; else gApUSmegV=155540077;if (gApUSmegV == gApUSmegV- 1 ) gApUSmegV=2135756220; else gApUSmegV=1400772697;if (gApUSmegV == gApUSmegV- 1 ) gApUSmegV=1301408450; else gApUSmegV=1251899769;if (gApUSmegV == gApUSmegV- 0 ) gApUSmegV=1502935939; else gApUSmegV=1813544050;if (gApUSmegV == gApUSmegV- 0 ) gApUSmegV=2122211398; else gApUSmegV=1987336536;long OSpIIcauO=2073571040;if (OSpIIcauO == OSpIIcauO- 1 ) OSpIIcauO=1182487869; else OSpIIcauO=1094237566;if (OSpIIcauO == OSpIIcauO- 0 ) OSpIIcauO=1308141899; else OSpIIcauO=890563691;if (OSpIIcauO == OSpIIcauO- 0 ) OSpIIcauO=1454670013; else OSpIIcauO=184051718;if (OSpIIcauO == OSpIIcauO- 1 ) OSpIIcauO=286545879; else OSpIIcauO=1308642315;if (OSpIIcauO == OSpIIcauO- 1 ) OSpIIcauO=442204739; else OSpIIcauO=1953960292;if (OSpIIcauO == OSpIIcauO- 1 ) OSpIIcauO=1060990742; else OSpIIcauO=125475725; }
 OSpIIcauOy::OSpIIcauOy()
 { this->mYncXcJAxfRs("YMpwYQcQBmYncXcJAxfRsj", true, 1184774152, 654651902, 1746603330); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class tGmRWblsjy
 { 
public: bool lEpjHXglB; double lEpjHXglBtGmRWblsj; tGmRWblsjy(); void virnlvMvgUmT(string lEpjHXglBvirnlvMvgUmT, bool IRyYvelgY, int xDdykuWtd, float NTKNKdVco, long RVRixtRgO);
 protected: bool lEpjHXglBo; double lEpjHXglBtGmRWblsjf; void virnlvMvgUmTu(string lEpjHXglBvirnlvMvgUmTg, bool IRyYvelgYe, int xDdykuWtdr, float NTKNKdVcow, long RVRixtRgOn);
 private: bool lEpjHXglBIRyYvelgY; double lEpjHXglBNTKNKdVcotGmRWblsj;
 void virnlvMvgUmTv(string IRyYvelgYvirnlvMvgUmT, bool IRyYvelgYxDdykuWtd, int xDdykuWtdlEpjHXglB, float NTKNKdVcoRVRixtRgO, long RVRixtRgOIRyYvelgY); };
 void tGmRWblsjy::virnlvMvgUmT(string lEpjHXglBvirnlvMvgUmT, bool IRyYvelgY, int xDdykuWtd, float NTKNKdVco, long RVRixtRgO)
 { long bgjCSHcFL=611350925;if (bgjCSHcFL == bgjCSHcFL- 0 ) bgjCSHcFL=1386322256; else bgjCSHcFL=1457000110;if (bgjCSHcFL == bgjCSHcFL- 0 ) bgjCSHcFL=1133634611; else bgjCSHcFL=145485387;if (bgjCSHcFL == bgjCSHcFL- 0 ) bgjCSHcFL=956269074; else bgjCSHcFL=624010342;if (bgjCSHcFL == bgjCSHcFL- 0 ) bgjCSHcFL=1762621999; else bgjCSHcFL=1778523573;if (bgjCSHcFL == bgjCSHcFL- 1 ) bgjCSHcFL=152374662; else bgjCSHcFL=368925480;if (bgjCSHcFL == bgjCSHcFL- 1 ) bgjCSHcFL=39173233; else bgjCSHcFL=681345570;long ggzPnkTUA=1872600794;if (ggzPnkTUA == ggzPnkTUA- 1 ) ggzPnkTUA=31549362; else ggzPnkTUA=2063835142;if (ggzPnkTUA == ggzPnkTUA- 1 ) ggzPnkTUA=308254208; else ggzPnkTUA=739311525;if (ggzPnkTUA == ggzPnkTUA- 1 ) ggzPnkTUA=1307670248; else ggzPnkTUA=2049525042;if (ggzPnkTUA == ggzPnkTUA- 0 ) ggzPnkTUA=586563625; else ggzPnkTUA=396059034;if (ggzPnkTUA == ggzPnkTUA- 1 ) ggzPnkTUA=790659664; else ggzPnkTUA=1682257138;if (ggzPnkTUA == ggzPnkTUA- 1 ) ggzPnkTUA=1727749954; else ggzPnkTUA=867978765;double QrmKLrxFN=678797389.6415314;if (QrmKLrxFN == QrmKLrxFN ) QrmKLrxFN=1849982374.7160989; else QrmKLrxFN=1165039594.9546573;if (QrmKLrxFN == QrmKLrxFN ) QrmKLrxFN=620062590.6460691; else QrmKLrxFN=1786763069.1572733;if (QrmKLrxFN == QrmKLrxFN ) QrmKLrxFN=813060113.3158862; else QrmKLrxFN=45369193.5818586;if (QrmKLrxFN == QrmKLrxFN ) QrmKLrxFN=1811589267.0633990; else QrmKLrxFN=929860333.1658237;if (QrmKLrxFN == QrmKLrxFN ) QrmKLrxFN=792212755.6083577; else QrmKLrxFN=895453625.4987222;if (QrmKLrxFN == QrmKLrxFN ) QrmKLrxFN=1576195302.6632262; else QrmKLrxFN=2090382362.9508532;float ABhOaqrOZ=1865167796.7977014f;if (ABhOaqrOZ - ABhOaqrOZ> 0.00000001 ) ABhOaqrOZ=1657052795.8865928f; else ABhOaqrOZ=858557083.7666398f;if (ABhOaqrOZ - ABhOaqrOZ> 0.00000001 ) ABhOaqrOZ=603353564.3143364f; else ABhOaqrOZ=768096139.5981420f;if (ABhOaqrOZ - ABhOaqrOZ> 0.00000001 ) ABhOaqrOZ=619115898.3461710f; else ABhOaqrOZ=697718609.9309535f;if (ABhOaqrOZ - ABhOaqrOZ> 0.00000001 ) ABhOaqrOZ=1451164324.9948985f; else ABhOaqrOZ=1484280861.9447614f;if (ABhOaqrOZ - ABhOaqrOZ> 0.00000001 ) ABhOaqrOZ=870436485.9856094f; else ABhOaqrOZ=737575577.2067884f;if (ABhOaqrOZ - ABhOaqrOZ> 0.00000001 ) ABhOaqrOZ=1502309370.8459397f; else ABhOaqrOZ=1421495583.0535564f;int LTEzizdaQ=864974970;if (LTEzizdaQ == LTEzizdaQ- 0 ) LTEzizdaQ=164091367; else LTEzizdaQ=1507859491;if (LTEzizdaQ == LTEzizdaQ- 0 ) LTEzizdaQ=978846843; else LTEzizdaQ=466118012;if (LTEzizdaQ == LTEzizdaQ- 1 ) LTEzizdaQ=113316192; else LTEzizdaQ=1888826160;if (LTEzizdaQ == LTEzizdaQ- 1 ) LTEzizdaQ=1059540681; else LTEzizdaQ=2133663816;if (LTEzizdaQ == LTEzizdaQ- 0 ) LTEzizdaQ=252245875; else LTEzizdaQ=1525877522;if (LTEzizdaQ == LTEzizdaQ- 1 ) LTEzizdaQ=2094582417; else LTEzizdaQ=412216623;double tGmRWblsj=1165583894.9339449;if (tGmRWblsj == tGmRWblsj ) tGmRWblsj=1278402596.0251494; else tGmRWblsj=2010065805.3232871;if (tGmRWblsj == tGmRWblsj ) tGmRWblsj=1358409617.7638573; else tGmRWblsj=1399839469.1301845;if (tGmRWblsj == tGmRWblsj ) tGmRWblsj=831529775.2186658; else tGmRWblsj=1584221621.2675047;if (tGmRWblsj == tGmRWblsj ) tGmRWblsj=59681491.2767233; else tGmRWblsj=1152263765.8129760;if (tGmRWblsj == tGmRWblsj ) tGmRWblsj=1861358917.9516501; else tGmRWblsj=1283265376.1562245;if (tGmRWblsj == tGmRWblsj ) tGmRWblsj=916326584.1636469; else tGmRWblsj=75484536.7547225; }
 tGmRWblsjy::tGmRWblsjy()
 { this->virnlvMvgUmT("lEpjHXglBvirnlvMvgUmTj", true, 690543470, 390093684, 2033599945); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class sWYcbzigLy
 { 
public: bool tIekthAfD; double tIekthAfDsWYcbzigL; sWYcbzigLy(); void qHxkXAlbPWpq(string tIekthAfDqHxkXAlbPWpq, bool vZBPbrDyw, int FwqDRiQpU, float AoTtZVcgp, long WJngzUgQk);
 protected: bool tIekthAfDo; double tIekthAfDsWYcbzigLf; void qHxkXAlbPWpqu(string tIekthAfDqHxkXAlbPWpqg, bool vZBPbrDywe, int FwqDRiQpUr, float AoTtZVcgpw, long WJngzUgQkn);
 private: bool tIekthAfDvZBPbrDyw; double tIekthAfDAoTtZVcgpsWYcbzigL;
 void qHxkXAlbPWpqv(string vZBPbrDywqHxkXAlbPWpq, bool vZBPbrDywFwqDRiQpU, int FwqDRiQpUtIekthAfD, float AoTtZVcgpWJngzUgQk, long WJngzUgQkvZBPbrDyw); };
 void sWYcbzigLy::qHxkXAlbPWpq(string tIekthAfDqHxkXAlbPWpq, bool vZBPbrDyw, int FwqDRiQpU, float AoTtZVcgp, long WJngzUgQk)
 { int PzKBQzWLA=454509834;if (PzKBQzWLA == PzKBQzWLA- 0 ) PzKBQzWLA=624638252; else PzKBQzWLA=1340743856;if (PzKBQzWLA == PzKBQzWLA- 1 ) PzKBQzWLA=1446809483; else PzKBQzWLA=261372972;if (PzKBQzWLA == PzKBQzWLA- 1 ) PzKBQzWLA=32311744; else PzKBQzWLA=967291540;if (PzKBQzWLA == PzKBQzWLA- 0 ) PzKBQzWLA=520594715; else PzKBQzWLA=526315442;if (PzKBQzWLA == PzKBQzWLA- 1 ) PzKBQzWLA=637547933; else PzKBQzWLA=2088126977;if (PzKBQzWLA == PzKBQzWLA- 1 ) PzKBQzWLA=2021282883; else PzKBQzWLA=1129511818;long gyatkLCpA=1406715385;if (gyatkLCpA == gyatkLCpA- 0 ) gyatkLCpA=631625085; else gyatkLCpA=1736142189;if (gyatkLCpA == gyatkLCpA- 1 ) gyatkLCpA=2028218418; else gyatkLCpA=1045831013;if (gyatkLCpA == gyatkLCpA- 1 ) gyatkLCpA=1445480143; else gyatkLCpA=1276922145;if (gyatkLCpA == gyatkLCpA- 1 ) gyatkLCpA=259978932; else gyatkLCpA=1935422928;if (gyatkLCpA == gyatkLCpA- 1 ) gyatkLCpA=460936811; else gyatkLCpA=912662216;if (gyatkLCpA == gyatkLCpA- 1 ) gyatkLCpA=1618481657; else gyatkLCpA=1133769862;float HVbwdMRrr=1521958904.1568164f;if (HVbwdMRrr - HVbwdMRrr> 0.00000001 ) HVbwdMRrr=45250516.2291137f; else HVbwdMRrr=535307825.2500320f;if (HVbwdMRrr - HVbwdMRrr> 0.00000001 ) HVbwdMRrr=1859774906.8547930f; else HVbwdMRrr=2059094932.4086793f;if (HVbwdMRrr - HVbwdMRrr> 0.00000001 ) HVbwdMRrr=1210349636.6497094f; else HVbwdMRrr=1197732881.3647101f;if (HVbwdMRrr - HVbwdMRrr> 0.00000001 ) HVbwdMRrr=149003851.5432164f; else HVbwdMRrr=791085793.0223358f;if (HVbwdMRrr - HVbwdMRrr> 0.00000001 ) HVbwdMRrr=1830132269.2265447f; else HVbwdMRrr=663125200.2233365f;if (HVbwdMRrr - HVbwdMRrr> 0.00000001 ) HVbwdMRrr=524822994.0118490f; else HVbwdMRrr=2062819607.7546306f;long jZkThCTnK=691547787;if (jZkThCTnK == jZkThCTnK- 0 ) jZkThCTnK=692723503; else jZkThCTnK=977496437;if (jZkThCTnK == jZkThCTnK- 1 ) jZkThCTnK=1443413324; else jZkThCTnK=1591342880;if (jZkThCTnK == jZkThCTnK- 0 ) jZkThCTnK=502107542; else jZkThCTnK=684480654;if (jZkThCTnK == jZkThCTnK- 0 ) jZkThCTnK=1156513338; else jZkThCTnK=1495199754;if (jZkThCTnK == jZkThCTnK- 1 ) jZkThCTnK=1080764924; else jZkThCTnK=1658870202;if (jZkThCTnK == jZkThCTnK- 0 ) jZkThCTnK=1947919808; else jZkThCTnK=1267133175;double SsKRIGNJH=91692886.7385025;if (SsKRIGNJH == SsKRIGNJH ) SsKRIGNJH=1206067006.6732689; else SsKRIGNJH=499323979.3778400;if (SsKRIGNJH == SsKRIGNJH ) SsKRIGNJH=1084261302.3818927; else SsKRIGNJH=1300821200.5888602;if (SsKRIGNJH == SsKRIGNJH ) SsKRIGNJH=540598086.7966546; else SsKRIGNJH=1821872056.9302178;if (SsKRIGNJH == SsKRIGNJH ) SsKRIGNJH=196365749.5926605; else SsKRIGNJH=1581375851.5771181;if (SsKRIGNJH == SsKRIGNJH ) SsKRIGNJH=1587138338.9640986; else SsKRIGNJH=1237132625.9239644;if (SsKRIGNJH == SsKRIGNJH ) SsKRIGNJH=1363182391.6279501; else SsKRIGNJH=782354943.9730173;int sWYcbzigL=520597042;if (sWYcbzigL == sWYcbzigL- 1 ) sWYcbzigL=32033553; else sWYcbzigL=926933870;if (sWYcbzigL == sWYcbzigL- 0 ) sWYcbzigL=441046359; else sWYcbzigL=687109199;if (sWYcbzigL == sWYcbzigL- 0 ) sWYcbzigL=1249925370; else sWYcbzigL=1438200738;if (sWYcbzigL == sWYcbzigL- 0 ) sWYcbzigL=1019851362; else sWYcbzigL=1508253509;if (sWYcbzigL == sWYcbzigL- 1 ) sWYcbzigL=1526278134; else sWYcbzigL=364575152;if (sWYcbzigL == sWYcbzigL- 1 ) sWYcbzigL=978330008; else sWYcbzigL=1698963081; }
 sWYcbzigLy::sWYcbzigLy()
 { this->qHxkXAlbPWpq("tIekthAfDqHxkXAlbPWpqj", true, 1397296720, 1029354323, 1442275910); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class uohfQXYVuy
 { 
public: bool screUWHSB; double screUWHSBuohfQXYVu; uohfQXYVuy(); void QawBAzBreqGZ(string screUWHSBQawBAzBreqGZ, bool WUeNkeQYX, int dPomDZvAd, float daQtKzobV, long xRQchgZgc);
 protected: bool screUWHSBo; double screUWHSBuohfQXYVuf; void QawBAzBreqGZu(string screUWHSBQawBAzBreqGZg, bool WUeNkeQYXe, int dPomDZvAdr, float daQtKzobVw, long xRQchgZgcn);
 private: bool screUWHSBWUeNkeQYX; double screUWHSBdaQtKzobVuohfQXYVu;
 void QawBAzBreqGZv(string WUeNkeQYXQawBAzBreqGZ, bool WUeNkeQYXdPomDZvAd, int dPomDZvAdscreUWHSB, float daQtKzobVxRQchgZgc, long xRQchgZgcWUeNkeQYX); };
 void uohfQXYVuy::QawBAzBreqGZ(string screUWHSBQawBAzBreqGZ, bool WUeNkeQYX, int dPomDZvAd, float daQtKzobV, long xRQchgZgc)
 { int dGZkdisgn=1524874304;if (dGZkdisgn == dGZkdisgn- 1 ) dGZkdisgn=730551979; else dGZkdisgn=532574993;if (dGZkdisgn == dGZkdisgn- 1 ) dGZkdisgn=2053227933; else dGZkdisgn=305624194;if (dGZkdisgn == dGZkdisgn- 0 ) dGZkdisgn=1108237748; else dGZkdisgn=1734176677;if (dGZkdisgn == dGZkdisgn- 0 ) dGZkdisgn=1145056821; else dGZkdisgn=1073306506;if (dGZkdisgn == dGZkdisgn- 0 ) dGZkdisgn=1714495508; else dGZkdisgn=1988307643;if (dGZkdisgn == dGZkdisgn- 1 ) dGZkdisgn=1530895209; else dGZkdisgn=986575395;long YxmpVWdbS=737420749;if (YxmpVWdbS == YxmpVWdbS- 1 ) YxmpVWdbS=1059156424; else YxmpVWdbS=1340415570;if (YxmpVWdbS == YxmpVWdbS- 1 ) YxmpVWdbS=1166304539; else YxmpVWdbS=410029786;if (YxmpVWdbS == YxmpVWdbS- 0 ) YxmpVWdbS=710844605; else YxmpVWdbS=947957895;if (YxmpVWdbS == YxmpVWdbS- 1 ) YxmpVWdbS=497052293; else YxmpVWdbS=405921350;if (YxmpVWdbS == YxmpVWdbS- 0 ) YxmpVWdbS=2026225253; else YxmpVWdbS=1514710885;if (YxmpVWdbS == YxmpVWdbS- 0 ) YxmpVWdbS=902994196; else YxmpVWdbS=381451710;float pZmcdTfqb=1282717115.8548659f;if (pZmcdTfqb - pZmcdTfqb> 0.00000001 ) pZmcdTfqb=251511958.1302222f; else pZmcdTfqb=283897740.3266100f;if (pZmcdTfqb - pZmcdTfqb> 0.00000001 ) pZmcdTfqb=1730287253.6185198f; else pZmcdTfqb=1103585809.1488006f;if (pZmcdTfqb - pZmcdTfqb> 0.00000001 ) pZmcdTfqb=863299987.3062132f; else pZmcdTfqb=988559770.4001994f;if (pZmcdTfqb - pZmcdTfqb> 0.00000001 ) pZmcdTfqb=604671727.1586663f; else pZmcdTfqb=933863355.4635710f;if (pZmcdTfqb - pZmcdTfqb> 0.00000001 ) pZmcdTfqb=1487434983.9252361f; else pZmcdTfqb=919771274.2051793f;if (pZmcdTfqb - pZmcdTfqb> 0.00000001 ) pZmcdTfqb=316605114.1953051f; else pZmcdTfqb=3231461.9025449f;long PiVJKVnYr=398297216;if (PiVJKVnYr == PiVJKVnYr- 0 ) PiVJKVnYr=156592723; else PiVJKVnYr=985954603;if (PiVJKVnYr == PiVJKVnYr- 1 ) PiVJKVnYr=1341660513; else PiVJKVnYr=281890877;if (PiVJKVnYr == PiVJKVnYr- 1 ) PiVJKVnYr=649425633; else PiVJKVnYr=1355229388;if (PiVJKVnYr == PiVJKVnYr- 1 ) PiVJKVnYr=814029699; else PiVJKVnYr=1930077731;if (PiVJKVnYr == PiVJKVnYr- 0 ) PiVJKVnYr=35522700; else PiVJKVnYr=1647306583;if (PiVJKVnYr == PiVJKVnYr- 0 ) PiVJKVnYr=426882588; else PiVJKVnYr=1741010510;long wSNgzcqmZ=993129575;if (wSNgzcqmZ == wSNgzcqmZ- 1 ) wSNgzcqmZ=605286818; else wSNgzcqmZ=248178094;if (wSNgzcqmZ == wSNgzcqmZ- 1 ) wSNgzcqmZ=735063437; else wSNgzcqmZ=579778089;if (wSNgzcqmZ == wSNgzcqmZ- 1 ) wSNgzcqmZ=587917395; else wSNgzcqmZ=1378121549;if (wSNgzcqmZ == wSNgzcqmZ- 1 ) wSNgzcqmZ=2021604409; else wSNgzcqmZ=70596654;if (wSNgzcqmZ == wSNgzcqmZ- 1 ) wSNgzcqmZ=735743843; else wSNgzcqmZ=232441184;if (wSNgzcqmZ == wSNgzcqmZ- 0 ) wSNgzcqmZ=1070078450; else wSNgzcqmZ=1938556978;long uohfQXYVu=580467680;if (uohfQXYVu == uohfQXYVu- 0 ) uohfQXYVu=2125258388; else uohfQXYVu=504696980;if (uohfQXYVu == uohfQXYVu- 1 ) uohfQXYVu=224858987; else uohfQXYVu=1299366928;if (uohfQXYVu == uohfQXYVu- 0 ) uohfQXYVu=1527189067; else uohfQXYVu=1101129948;if (uohfQXYVu == uohfQXYVu- 1 ) uohfQXYVu=633291482; else uohfQXYVu=1043766217;if (uohfQXYVu == uohfQXYVu- 1 ) uohfQXYVu=1617351688; else uohfQXYVu=1947693169;if (uohfQXYVu == uohfQXYVu- 1 ) uohfQXYVu=1068063109; else uohfQXYVu=1363477051; }
 uohfQXYVuy::uohfQXYVuy()
 { this->QawBAzBreqGZ("screUWHSBQawBAzBreqGZj", true, 561677182, 1011144864, 102680874); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class YivBsXodty
 { 
public: bool EboWoROlF; double EboWoROlFYivBsXodt; YivBsXodty(); void HjxGSynWHEfj(string EboWoROlFHjxGSynWHEfj, bool EDQyyvaZB, int HmmZsOBXW, float ExJmcQyxU, long TcyyFHVEX);
 protected: bool EboWoROlFo; double EboWoROlFYivBsXodtf; void HjxGSynWHEfju(string EboWoROlFHjxGSynWHEfjg, bool EDQyyvaZBe, int HmmZsOBXWr, float ExJmcQyxUw, long TcyyFHVEXn);
 private: bool EboWoROlFEDQyyvaZB; double EboWoROlFExJmcQyxUYivBsXodt;
 void HjxGSynWHEfjv(string EDQyyvaZBHjxGSynWHEfj, bool EDQyyvaZBHmmZsOBXW, int HmmZsOBXWEboWoROlF, float ExJmcQyxUTcyyFHVEX, long TcyyFHVEXEDQyyvaZB); };
 void YivBsXodty::HjxGSynWHEfj(string EboWoROlFHjxGSynWHEfj, bool EDQyyvaZB, int HmmZsOBXW, float ExJmcQyxU, long TcyyFHVEX)
 { int JIiCreLoq=897173714;if (JIiCreLoq == JIiCreLoq- 1 ) JIiCreLoq=793305375; else JIiCreLoq=1864819699;if (JIiCreLoq == JIiCreLoq- 0 ) JIiCreLoq=1221629508; else JIiCreLoq=387649679;if (JIiCreLoq == JIiCreLoq- 0 ) JIiCreLoq=964521418; else JIiCreLoq=1130483087;if (JIiCreLoq == JIiCreLoq- 1 ) JIiCreLoq=351565747; else JIiCreLoq=553112954;if (JIiCreLoq == JIiCreLoq- 1 ) JIiCreLoq=1609403063; else JIiCreLoq=174008333;if (JIiCreLoq == JIiCreLoq- 1 ) JIiCreLoq=954473949; else JIiCreLoq=1958580114;long NGdnsbdDX=538950084;if (NGdnsbdDX == NGdnsbdDX- 0 ) NGdnsbdDX=1401354912; else NGdnsbdDX=1778789964;if (NGdnsbdDX == NGdnsbdDX- 0 ) NGdnsbdDX=767573008; else NGdnsbdDX=1738637114;if (NGdnsbdDX == NGdnsbdDX- 1 ) NGdnsbdDX=1754356794; else NGdnsbdDX=82199915;if (NGdnsbdDX == NGdnsbdDX- 0 ) NGdnsbdDX=855276585; else NGdnsbdDX=125740541;if (NGdnsbdDX == NGdnsbdDX- 1 ) NGdnsbdDX=1169710268; else NGdnsbdDX=2056918169;if (NGdnsbdDX == NGdnsbdDX- 1 ) NGdnsbdDX=431632244; else NGdnsbdDX=1184997417;int lzzvjJaog=1832471888;if (lzzvjJaog == lzzvjJaog- 0 ) lzzvjJaog=827818302; else lzzvjJaog=294436766;if (lzzvjJaog == lzzvjJaog- 1 ) lzzvjJaog=1625490255; else lzzvjJaog=764559061;if (lzzvjJaog == lzzvjJaog- 1 ) lzzvjJaog=199417823; else lzzvjJaog=498606800;if (lzzvjJaog == lzzvjJaog- 1 ) lzzvjJaog=1964845092; else lzzvjJaog=1212338996;if (lzzvjJaog == lzzvjJaog- 1 ) lzzvjJaog=1344573204; else lzzvjJaog=571888108;if (lzzvjJaog == lzzvjJaog- 0 ) lzzvjJaog=1482157681; else lzzvjJaog=785831011;long GHqrmtcJI=1617016822;if (GHqrmtcJI == GHqrmtcJI- 1 ) GHqrmtcJI=27638891; else GHqrmtcJI=1977290867;if (GHqrmtcJI == GHqrmtcJI- 0 ) GHqrmtcJI=1938746061; else GHqrmtcJI=1358397980;if (GHqrmtcJI == GHqrmtcJI- 0 ) GHqrmtcJI=1095352400; else GHqrmtcJI=973651208;if (GHqrmtcJI == GHqrmtcJI- 1 ) GHqrmtcJI=1290300567; else GHqrmtcJI=711105460;if (GHqrmtcJI == GHqrmtcJI- 0 ) GHqrmtcJI=1009543114; else GHqrmtcJI=1095888967;if (GHqrmtcJI == GHqrmtcJI- 1 ) GHqrmtcJI=1365423058; else GHqrmtcJI=1055086896;int OyRdFGJOF=106237325;if (OyRdFGJOF == OyRdFGJOF- 1 ) OyRdFGJOF=986137116; else OyRdFGJOF=1269485708;if (OyRdFGJOF == OyRdFGJOF- 0 ) OyRdFGJOF=1130761812; else OyRdFGJOF=1872977766;if (OyRdFGJOF == OyRdFGJOF- 0 ) OyRdFGJOF=1922720054; else OyRdFGJOF=721204678;if (OyRdFGJOF == OyRdFGJOF- 1 ) OyRdFGJOF=339532261; else OyRdFGJOF=902748112;if (OyRdFGJOF == OyRdFGJOF- 1 ) OyRdFGJOF=1961428519; else OyRdFGJOF=1702717659;if (OyRdFGJOF == OyRdFGJOF- 0 ) OyRdFGJOF=394063910; else OyRdFGJOF=1182468686;double YivBsXodt=1153636267.5440280;if (YivBsXodt == YivBsXodt ) YivBsXodt=166535814.4610162; else YivBsXodt=962099069.0127618;if (YivBsXodt == YivBsXodt ) YivBsXodt=1157358526.9985073; else YivBsXodt=1570931019.0229489;if (YivBsXodt == YivBsXodt ) YivBsXodt=1711903324.2710458; else YivBsXodt=2124440531.0270731;if (YivBsXodt == YivBsXodt ) YivBsXodt=737119488.7365607; else YivBsXodt=2001650741.6653284;if (YivBsXodt == YivBsXodt ) YivBsXodt=1151619846.5927838; else YivBsXodt=914384795.5283610;if (YivBsXodt == YivBsXodt ) YivBsXodt=1902499594.8164423; else YivBsXodt=1251012503.9749837; }
 YivBsXodty::YivBsXodty()
 { this->HjxGSynWHEfj("EboWoROlFHjxGSynWHEfjj", true, 1280667389, 909758196, 513488153); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class dsjZgQBmcy
 { 
public: bool CcQEnsxuR; double CcQEnsxuRdsjZgQBmc; dsjZgQBmcy(); void wMuOlJHIvuvY(string CcQEnsxuRwMuOlJHIvuvY, bool pLhgpKuHt, int dgRGDgTZR, float BdRLhWmzP, long BuePbtiCE);
 protected: bool CcQEnsxuRo; double CcQEnsxuRdsjZgQBmcf; void wMuOlJHIvuvYu(string CcQEnsxuRwMuOlJHIvuvYg, bool pLhgpKuHte, int dgRGDgTZRr, float BdRLhWmzPw, long BuePbtiCEn);
 private: bool CcQEnsxuRpLhgpKuHt; double CcQEnsxuRBdRLhWmzPdsjZgQBmc;
 void wMuOlJHIvuvYv(string pLhgpKuHtwMuOlJHIvuvY, bool pLhgpKuHtdgRGDgTZR, int dgRGDgTZRCcQEnsxuR, float BdRLhWmzPBuePbtiCE, long BuePbtiCEpLhgpKuHt); };
 void dsjZgQBmcy::wMuOlJHIvuvY(string CcQEnsxuRwMuOlJHIvuvY, bool pLhgpKuHt, int dgRGDgTZR, float BdRLhWmzP, long BuePbtiCE)
 { double ZNshSOygS=82369483.2264486;if (ZNshSOygS == ZNshSOygS ) ZNshSOygS=343644448.1005431; else ZNshSOygS=228777997.6212875;if (ZNshSOygS == ZNshSOygS ) ZNshSOygS=1318158594.3515120; else ZNshSOygS=539322961.2683556;if (ZNshSOygS == ZNshSOygS ) ZNshSOygS=1311550342.4425024; else ZNshSOygS=2003905725.0476958;if (ZNshSOygS == ZNshSOygS ) ZNshSOygS=919876445.8137660; else ZNshSOygS=1641512267.7594660;if (ZNshSOygS == ZNshSOygS ) ZNshSOygS=1950215657.4339852; else ZNshSOygS=1446886206.8989513;if (ZNshSOygS == ZNshSOygS ) ZNshSOygS=732821374.2403734; else ZNshSOygS=784156822.6669978;float OEShYiHYi=1618107374.3684392f;if (OEShYiHYi - OEShYiHYi> 0.00000001 ) OEShYiHYi=753879930.6270373f; else OEShYiHYi=710016317.4604602f;if (OEShYiHYi - OEShYiHYi> 0.00000001 ) OEShYiHYi=1632820318.0381677f; else OEShYiHYi=1664877335.5172642f;if (OEShYiHYi - OEShYiHYi> 0.00000001 ) OEShYiHYi=310214901.9346587f; else OEShYiHYi=1641698556.8712776f;if (OEShYiHYi - OEShYiHYi> 0.00000001 ) OEShYiHYi=400096589.9936213f; else OEShYiHYi=217587593.3148351f;if (OEShYiHYi - OEShYiHYi> 0.00000001 ) OEShYiHYi=126094177.1098425f; else OEShYiHYi=1143580647.4791363f;if (OEShYiHYi - OEShYiHYi> 0.00000001 ) OEShYiHYi=53223984.6899116f; else OEShYiHYi=1906650838.3564496f;int xnONbfkIV=1289298105;if (xnONbfkIV == xnONbfkIV- 1 ) xnONbfkIV=898349260; else xnONbfkIV=1183975346;if (xnONbfkIV == xnONbfkIV- 0 ) xnONbfkIV=1325845766; else xnONbfkIV=1539154885;if (xnONbfkIV == xnONbfkIV- 0 ) xnONbfkIV=521235687; else xnONbfkIV=2104960036;if (xnONbfkIV == xnONbfkIV- 1 ) xnONbfkIV=2050488159; else xnONbfkIV=783783649;if (xnONbfkIV == xnONbfkIV- 0 ) xnONbfkIV=1207729197; else xnONbfkIV=30446160;if (xnONbfkIV == xnONbfkIV- 0 ) xnONbfkIV=1313669623; else xnONbfkIV=1585575245;int soBZgaasa=211360234;if (soBZgaasa == soBZgaasa- 0 ) soBZgaasa=883506331; else soBZgaasa=1249045789;if (soBZgaasa == soBZgaasa- 1 ) soBZgaasa=468825810; else soBZgaasa=2009249632;if (soBZgaasa == soBZgaasa- 0 ) soBZgaasa=1803266825; else soBZgaasa=2075947842;if (soBZgaasa == soBZgaasa- 1 ) soBZgaasa=1919638229; else soBZgaasa=849429539;if (soBZgaasa == soBZgaasa- 1 ) soBZgaasa=1976165055; else soBZgaasa=1100571001;if (soBZgaasa == soBZgaasa- 0 ) soBZgaasa=413228784; else soBZgaasa=167969695;int aBCFarhPK=205989389;if (aBCFarhPK == aBCFarhPK- 0 ) aBCFarhPK=725180320; else aBCFarhPK=1591006916;if (aBCFarhPK == aBCFarhPK- 0 ) aBCFarhPK=2033291209; else aBCFarhPK=490649230;if (aBCFarhPK == aBCFarhPK- 0 ) aBCFarhPK=1013588713; else aBCFarhPK=1673622109;if (aBCFarhPK == aBCFarhPK- 1 ) aBCFarhPK=1096871687; else aBCFarhPK=796403541;if (aBCFarhPK == aBCFarhPK- 1 ) aBCFarhPK=807011805; else aBCFarhPK=849036669;if (aBCFarhPK == aBCFarhPK- 1 ) aBCFarhPK=457148138; else aBCFarhPK=279768741;float dsjZgQBmc=1409929825.7836040f;if (dsjZgQBmc - dsjZgQBmc> 0.00000001 ) dsjZgQBmc=1372174141.6639909f; else dsjZgQBmc=1989347397.3331551f;if (dsjZgQBmc - dsjZgQBmc> 0.00000001 ) dsjZgQBmc=1023144507.6535892f; else dsjZgQBmc=105919335.1569194f;if (dsjZgQBmc - dsjZgQBmc> 0.00000001 ) dsjZgQBmc=1275400458.2487675f; else dsjZgQBmc=859939901.5841490f;if (dsjZgQBmc - dsjZgQBmc> 0.00000001 ) dsjZgQBmc=1633514927.9995552f; else dsjZgQBmc=969885065.3112596f;if (dsjZgQBmc - dsjZgQBmc> 0.00000001 ) dsjZgQBmc=1411820764.2718161f; else dsjZgQBmc=476416227.0650861f;if (dsjZgQBmc - dsjZgQBmc> 0.00000001 ) dsjZgQBmc=1710473477.8944033f; else dsjZgQBmc=1568148333.6757420f; }
 dsjZgQBmcy::dsjZgQBmcy()
 { this->wMuOlJHIvuvY("CcQEnsxuRwMuOlJHIvuvYj", true, 1691731252, 1882518464, 980585555); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class xhZCDdlcAy
 { 
public: bool AFJLSvpKa; double AFJLSvpKaxhZCDdlcA; xhZCDdlcAy(); void fjbvrwTAqceD(string AFJLSvpKafjbvrwTAqceD, bool MbSxyHLgR, int cKwVBYwiX, float zLtMYHOyq, long qKRyYUlAi);
 protected: bool AFJLSvpKao; double AFJLSvpKaxhZCDdlcAf; void fjbvrwTAqceDu(string AFJLSvpKafjbvrwTAqceDg, bool MbSxyHLgRe, int cKwVBYwiXr, float zLtMYHOyqw, long qKRyYUlAin);
 private: bool AFJLSvpKaMbSxyHLgR; double AFJLSvpKazLtMYHOyqxhZCDdlcA;
 void fjbvrwTAqceDv(string MbSxyHLgRfjbvrwTAqceD, bool MbSxyHLgRcKwVBYwiX, int cKwVBYwiXAFJLSvpKa, float zLtMYHOyqqKRyYUlAi, long qKRyYUlAiMbSxyHLgR); };
 void xhZCDdlcAy::fjbvrwTAqceD(string AFJLSvpKafjbvrwTAqceD, bool MbSxyHLgR, int cKwVBYwiX, float zLtMYHOyq, long qKRyYUlAi)
 { long ZsJbuQKDJ=143230809;if (ZsJbuQKDJ == ZsJbuQKDJ- 1 ) ZsJbuQKDJ=1030582968; else ZsJbuQKDJ=1988084918;if (ZsJbuQKDJ == ZsJbuQKDJ- 1 ) ZsJbuQKDJ=25067582; else ZsJbuQKDJ=1013327392;if (ZsJbuQKDJ == ZsJbuQKDJ- 0 ) ZsJbuQKDJ=1372483125; else ZsJbuQKDJ=1713054047;if (ZsJbuQKDJ == ZsJbuQKDJ- 1 ) ZsJbuQKDJ=127534859; else ZsJbuQKDJ=21205891;if (ZsJbuQKDJ == ZsJbuQKDJ- 0 ) ZsJbuQKDJ=1927054009; else ZsJbuQKDJ=959589191;if (ZsJbuQKDJ == ZsJbuQKDJ- 0 ) ZsJbuQKDJ=1754944929; else ZsJbuQKDJ=351554678;long suCZEmQsY=760976993;if (suCZEmQsY == suCZEmQsY- 1 ) suCZEmQsY=1696515426; else suCZEmQsY=1319780287;if (suCZEmQsY == suCZEmQsY- 1 ) suCZEmQsY=1233444869; else suCZEmQsY=685153855;if (suCZEmQsY == suCZEmQsY- 0 ) suCZEmQsY=773902952; else suCZEmQsY=1611260500;if (suCZEmQsY == suCZEmQsY- 1 ) suCZEmQsY=1856656380; else suCZEmQsY=399961456;if (suCZEmQsY == suCZEmQsY- 0 ) suCZEmQsY=1525957903; else suCZEmQsY=1042377126;if (suCZEmQsY == suCZEmQsY- 0 ) suCZEmQsY=1830552417; else suCZEmQsY=714152638;long OQWItKkef=1541918593;if (OQWItKkef == OQWItKkef- 1 ) OQWItKkef=1242620775; else OQWItKkef=2079497539;if (OQWItKkef == OQWItKkef- 0 ) OQWItKkef=668677054; else OQWItKkef=1284927685;if (OQWItKkef == OQWItKkef- 0 ) OQWItKkef=1597454933; else OQWItKkef=1021515428;if (OQWItKkef == OQWItKkef- 1 ) OQWItKkef=1853797482; else OQWItKkef=1086722714;if (OQWItKkef == OQWItKkef- 1 ) OQWItKkef=1123621575; else OQWItKkef=1518959987;if (OQWItKkef == OQWItKkef- 1 ) OQWItKkef=802931746; else OQWItKkef=603309797;double QLkfkmgeS=1494640256.1388479;if (QLkfkmgeS == QLkfkmgeS ) QLkfkmgeS=1846776455.3575640; else QLkfkmgeS=115541015.4977149;if (QLkfkmgeS == QLkfkmgeS ) QLkfkmgeS=456175832.8808936; else QLkfkmgeS=281082936.1378127;if (QLkfkmgeS == QLkfkmgeS ) QLkfkmgeS=131314576.9657039; else QLkfkmgeS=1557832305.2752520;if (QLkfkmgeS == QLkfkmgeS ) QLkfkmgeS=1516811504.7112253; else QLkfkmgeS=1566806115.6915432;if (QLkfkmgeS == QLkfkmgeS ) QLkfkmgeS=131428538.2175235; else QLkfkmgeS=1772589773.4301106;if (QLkfkmgeS == QLkfkmgeS ) QLkfkmgeS=1634853136.1564274; else QLkfkmgeS=330105999.3679844;int UIdDmAfog=922351454;if (UIdDmAfog == UIdDmAfog- 1 ) UIdDmAfog=1437347103; else UIdDmAfog=213026336;if (UIdDmAfog == UIdDmAfog- 1 ) UIdDmAfog=1256417550; else UIdDmAfog=966790519;if (UIdDmAfog == UIdDmAfog- 0 ) UIdDmAfog=287894477; else UIdDmAfog=857629381;if (UIdDmAfog == UIdDmAfog- 1 ) UIdDmAfog=1311005707; else UIdDmAfog=674999998;if (UIdDmAfog == UIdDmAfog- 0 ) UIdDmAfog=1613466452; else UIdDmAfog=146722155;if (UIdDmAfog == UIdDmAfog- 0 ) UIdDmAfog=1709015927; else UIdDmAfog=1402426612;int xhZCDdlcA=1895557484;if (xhZCDdlcA == xhZCDdlcA- 1 ) xhZCDdlcA=261378962; else xhZCDdlcA=335912161;if (xhZCDdlcA == xhZCDdlcA- 0 ) xhZCDdlcA=1014859830; else xhZCDdlcA=1178608845;if (xhZCDdlcA == xhZCDdlcA- 1 ) xhZCDdlcA=548526723; else xhZCDdlcA=1388642799;if (xhZCDdlcA == xhZCDdlcA- 0 ) xhZCDdlcA=1410604017; else xhZCDdlcA=1832272117;if (xhZCDdlcA == xhZCDdlcA- 1 ) xhZCDdlcA=562686035; else xhZCDdlcA=1249354586;if (xhZCDdlcA == xhZCDdlcA- 1 ) xhZCDdlcA=1153499147; else xhZCDdlcA=1972348807; }
 xhZCDdlcAy::xhZCDdlcAy()
 { this->fjbvrwTAqceD("AFJLSvpKafjbvrwTAqceDj", true, 1534145939, 1523691483, 1204221084); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class gKbwYOQUpy
 { 
public: bool yxIlzFYRs; double yxIlzFYRsgKbwYOQUp; gKbwYOQUpy(); void IUhIIriAmVWL(string yxIlzFYRsIUhIIriAmVWL, bool dqXpuoPWh, int UDmblAcLW, float QsCrJKSYJ, long zstQMxLQe);
 protected: bool yxIlzFYRso; double yxIlzFYRsgKbwYOQUpf; void IUhIIriAmVWLu(string yxIlzFYRsIUhIIriAmVWLg, bool dqXpuoPWhe, int UDmblAcLWr, float QsCrJKSYJw, long zstQMxLQen);
 private: bool yxIlzFYRsdqXpuoPWh; double yxIlzFYRsQsCrJKSYJgKbwYOQUp;
 void IUhIIriAmVWLv(string dqXpuoPWhIUhIIriAmVWL, bool dqXpuoPWhUDmblAcLW, int UDmblAcLWyxIlzFYRs, float QsCrJKSYJzstQMxLQe, long zstQMxLQedqXpuoPWh); };
 void gKbwYOQUpy::IUhIIriAmVWL(string yxIlzFYRsIUhIIriAmVWL, bool dqXpuoPWh, int UDmblAcLW, float QsCrJKSYJ, long zstQMxLQe)
 { float cAzTavQqD=756917646.6019613f;if (cAzTavQqD - cAzTavQqD> 0.00000001 ) cAzTavQqD=1760751304.2410111f; else cAzTavQqD=119069364.7013881f;if (cAzTavQqD - cAzTavQqD> 0.00000001 ) cAzTavQqD=1229634761.0345615f; else cAzTavQqD=1609761336.8750761f;if (cAzTavQqD - cAzTavQqD> 0.00000001 ) cAzTavQqD=410654721.1289591f; else cAzTavQqD=271576965.9521286f;if (cAzTavQqD - cAzTavQqD> 0.00000001 ) cAzTavQqD=1090866862.2232667f; else cAzTavQqD=872387569.8751194f;if (cAzTavQqD - cAzTavQqD> 0.00000001 ) cAzTavQqD=50032983.7715517f; else cAzTavQqD=75371453.8344911f;if (cAzTavQqD - cAzTavQqD> 0.00000001 ) cAzTavQqD=497427585.8344397f; else cAzTavQqD=798039321.5391153f;long SsVDhJrJg=1853617366;if (SsVDhJrJg == SsVDhJrJg- 0 ) SsVDhJrJg=2124769335; else SsVDhJrJg=1922218726;if (SsVDhJrJg == SsVDhJrJg- 1 ) SsVDhJrJg=1225281998; else SsVDhJrJg=1262102977;if (SsVDhJrJg == SsVDhJrJg- 0 ) SsVDhJrJg=751482995; else SsVDhJrJg=203174598;if (SsVDhJrJg == SsVDhJrJg- 1 ) SsVDhJrJg=648602813; else SsVDhJrJg=1011808728;if (SsVDhJrJg == SsVDhJrJg- 1 ) SsVDhJrJg=1820998532; else SsVDhJrJg=1896793993;if (SsVDhJrJg == SsVDhJrJg- 0 ) SsVDhJrJg=1536015026; else SsVDhJrJg=1880615419;float KTNwFzehD=1169568851.5136176f;if (KTNwFzehD - KTNwFzehD> 0.00000001 ) KTNwFzehD=299308981.3723214f; else KTNwFzehD=562550032.7051340f;if (KTNwFzehD - KTNwFzehD> 0.00000001 ) KTNwFzehD=1249988635.8453815f; else KTNwFzehD=2101837561.8446919f;if (KTNwFzehD - KTNwFzehD> 0.00000001 ) KTNwFzehD=1788545411.6980283f; else KTNwFzehD=1615598959.0717521f;if (KTNwFzehD - KTNwFzehD> 0.00000001 ) KTNwFzehD=373424459.7609248f; else KTNwFzehD=1555976234.8933616f;if (KTNwFzehD - KTNwFzehD> 0.00000001 ) KTNwFzehD=970077222.4973151f; else KTNwFzehD=1618089603.1722788f;if (KTNwFzehD - KTNwFzehD> 0.00000001 ) KTNwFzehD=1492361247.7574041f; else KTNwFzehD=1511568106.9588829f;int WhbgnfpRR=1530266888;if (WhbgnfpRR == WhbgnfpRR- 0 ) WhbgnfpRR=1128784877; else WhbgnfpRR=2078889362;if (WhbgnfpRR == WhbgnfpRR- 1 ) WhbgnfpRR=1749799743; else WhbgnfpRR=305724441;if (WhbgnfpRR == WhbgnfpRR- 0 ) WhbgnfpRR=571858671; else WhbgnfpRR=1981982241;if (WhbgnfpRR == WhbgnfpRR- 0 ) WhbgnfpRR=5434651; else WhbgnfpRR=1557576706;if (WhbgnfpRR == WhbgnfpRR- 1 ) WhbgnfpRR=1617950198; else WhbgnfpRR=217826033;if (WhbgnfpRR == WhbgnfpRR- 1 ) WhbgnfpRR=1936246451; else WhbgnfpRR=661344375;double HOTxVUtbn=134409994.9821047;if (HOTxVUtbn == HOTxVUtbn ) HOTxVUtbn=1562732254.2594309; else HOTxVUtbn=1475342381.3230923;if (HOTxVUtbn == HOTxVUtbn ) HOTxVUtbn=498730340.7186717; else HOTxVUtbn=1237191550.8546503;if (HOTxVUtbn == HOTxVUtbn ) HOTxVUtbn=1802107149.7816990; else HOTxVUtbn=229635386.3936266;if (HOTxVUtbn == HOTxVUtbn ) HOTxVUtbn=65071955.6951872; else HOTxVUtbn=509170376.8454405;if (HOTxVUtbn == HOTxVUtbn ) HOTxVUtbn=1548794267.1698177; else HOTxVUtbn=1816789411.5250344;if (HOTxVUtbn == HOTxVUtbn ) HOTxVUtbn=292025755.2616522; else HOTxVUtbn=1280877039.6958319;float gKbwYOQUp=922836317.2287258f;if (gKbwYOQUp - gKbwYOQUp> 0.00000001 ) gKbwYOQUp=100745660.8735564f; else gKbwYOQUp=5748138.6819844f;if (gKbwYOQUp - gKbwYOQUp> 0.00000001 ) gKbwYOQUp=751830542.5498273f; else gKbwYOQUp=523610634.2250109f;if (gKbwYOQUp - gKbwYOQUp> 0.00000001 ) gKbwYOQUp=313306893.7271556f; else gKbwYOQUp=354398405.0003693f;if (gKbwYOQUp - gKbwYOQUp> 0.00000001 ) gKbwYOQUp=597710180.0007298f; else gKbwYOQUp=464810387.8000866f;if (gKbwYOQUp - gKbwYOQUp> 0.00000001 ) gKbwYOQUp=557115381.5854750f; else gKbwYOQUp=1839895576.7584095f;if (gKbwYOQUp - gKbwYOQUp> 0.00000001 ) gKbwYOQUp=483887363.5967903f; else gKbwYOQUp=1570719378.3640220f; }
 gKbwYOQUpy::gKbwYOQUpy()
 { this->IUhIIriAmVWL("yxIlzFYRsIUhIIriAmVWLj", true, 1826836155, 1859563731, 672930648); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class OjliHSjCyy
 { 
public: bool CedZFBpah; double CedZFBpahOjliHSjCy; OjliHSjCyy(); void OUVplbhxXhoR(string CedZFBpahOUVplbhxXhoR, bool JJzPPtWrB, int EaBNMSTLT, float rZBEfppOD, long EkfVckvEe);
 protected: bool CedZFBpaho; double CedZFBpahOjliHSjCyf; void OUVplbhxXhoRu(string CedZFBpahOUVplbhxXhoRg, bool JJzPPtWrBe, int EaBNMSTLTr, float rZBEfppODw, long EkfVckvEen);
 private: bool CedZFBpahJJzPPtWrB; double CedZFBpahrZBEfppODOjliHSjCy;
 void OUVplbhxXhoRv(string JJzPPtWrBOUVplbhxXhoR, bool JJzPPtWrBEaBNMSTLT, int EaBNMSTLTCedZFBpah, float rZBEfppODEkfVckvEe, long EkfVckvEeJJzPPtWrB); };
 void OjliHSjCyy::OUVplbhxXhoR(string CedZFBpahOUVplbhxXhoR, bool JJzPPtWrB, int EaBNMSTLT, float rZBEfppOD, long EkfVckvEe)
 { long akEgFabMK=1513263708;if (akEgFabMK == akEgFabMK- 1 ) akEgFabMK=1305302788; else akEgFabMK=875657715;if (akEgFabMK == akEgFabMK- 1 ) akEgFabMK=378105042; else akEgFabMK=1504262873;if (akEgFabMK == akEgFabMK- 0 ) akEgFabMK=1043295408; else akEgFabMK=1895689763;if (akEgFabMK == akEgFabMK- 1 ) akEgFabMK=1258408815; else akEgFabMK=1256117696;if (akEgFabMK == akEgFabMK- 0 ) akEgFabMK=51541571; else akEgFabMK=1165300756;if (akEgFabMK == akEgFabMK- 0 ) akEgFabMK=1908850292; else akEgFabMK=730775121;double TMlTFHMaK=1917622883.0787467;if (TMlTFHMaK == TMlTFHMaK ) TMlTFHMaK=1694347716.4916944; else TMlTFHMaK=472768760.6189628;if (TMlTFHMaK == TMlTFHMaK ) TMlTFHMaK=819675462.8811537; else TMlTFHMaK=1341870102.7361513;if (TMlTFHMaK == TMlTFHMaK ) TMlTFHMaK=784739856.1496066; else TMlTFHMaK=553658162.8448534;if (TMlTFHMaK == TMlTFHMaK ) TMlTFHMaK=1897069852.1672643; else TMlTFHMaK=418365847.9779407;if (TMlTFHMaK == TMlTFHMaK ) TMlTFHMaK=1041734048.6665315; else TMlTFHMaK=285272496.8037721;if (TMlTFHMaK == TMlTFHMaK ) TMlTFHMaK=567702207.5731147; else TMlTFHMaK=1400260780.8909812;float KmeetIrsR=1941242452.2994903f;if (KmeetIrsR - KmeetIrsR> 0.00000001 ) KmeetIrsR=396373189.9248528f; else KmeetIrsR=1581142511.7326127f;if (KmeetIrsR - KmeetIrsR> 0.00000001 ) KmeetIrsR=683762999.4969256f; else KmeetIrsR=262637964.5724802f;if (KmeetIrsR - KmeetIrsR> 0.00000001 ) KmeetIrsR=2130518199.3621679f; else KmeetIrsR=759229149.7539817f;if (KmeetIrsR - KmeetIrsR> 0.00000001 ) KmeetIrsR=1219469238.0136008f; else KmeetIrsR=107294870.1468585f;if (KmeetIrsR - KmeetIrsR> 0.00000001 ) KmeetIrsR=556162776.5357365f; else KmeetIrsR=1991509361.8165688f;if (KmeetIrsR - KmeetIrsR> 0.00000001 ) KmeetIrsR=257473256.4304596f; else KmeetIrsR=289705020.6999153f;long gMHuSGKqM=508008647;if (gMHuSGKqM == gMHuSGKqM- 1 ) gMHuSGKqM=244875202; else gMHuSGKqM=693321437;if (gMHuSGKqM == gMHuSGKqM- 1 ) gMHuSGKqM=565012960; else gMHuSGKqM=573769706;if (gMHuSGKqM == gMHuSGKqM- 0 ) gMHuSGKqM=1399120241; else gMHuSGKqM=150145058;if (gMHuSGKqM == gMHuSGKqM- 1 ) gMHuSGKqM=728523852; else gMHuSGKqM=751644626;if (gMHuSGKqM == gMHuSGKqM- 1 ) gMHuSGKqM=1126071510; else gMHuSGKqM=2107222842;if (gMHuSGKqM == gMHuSGKqM- 1 ) gMHuSGKqM=462528825; else gMHuSGKqM=758022912;long YjumJKfVJ=1695518601;if (YjumJKfVJ == YjumJKfVJ- 1 ) YjumJKfVJ=1406334733; else YjumJKfVJ=2115091487;if (YjumJKfVJ == YjumJKfVJ- 0 ) YjumJKfVJ=334401932; else YjumJKfVJ=139941740;if (YjumJKfVJ == YjumJKfVJ- 0 ) YjumJKfVJ=182181682; else YjumJKfVJ=1410359863;if (YjumJKfVJ == YjumJKfVJ- 0 ) YjumJKfVJ=1934588331; else YjumJKfVJ=935118567;if (YjumJKfVJ == YjumJKfVJ- 1 ) YjumJKfVJ=1400783169; else YjumJKfVJ=712380592;if (YjumJKfVJ == YjumJKfVJ- 0 ) YjumJKfVJ=785707326; else YjumJKfVJ=940714142;long OjliHSjCy=698365599;if (OjliHSjCy == OjliHSjCy- 0 ) OjliHSjCy=580502360; else OjliHSjCy=59693560;if (OjliHSjCy == OjliHSjCy- 0 ) OjliHSjCy=1155385578; else OjliHSjCy=685409347;if (OjliHSjCy == OjliHSjCy- 1 ) OjliHSjCy=2085977304; else OjliHSjCy=1332679964;if (OjliHSjCy == OjliHSjCy- 1 ) OjliHSjCy=542122211; else OjliHSjCy=246228131;if (OjliHSjCy == OjliHSjCy- 1 ) OjliHSjCy=852618659; else OjliHSjCy=2079602020;if (OjliHSjCy == OjliHSjCy- 0 ) OjliHSjCy=1284050101; else OjliHSjCy=23295357; }
 OjliHSjCyy::OjliHSjCyy()
 { this->OUVplbhxXhoR("CedZFBpahOUVplbhxXhoRj", true, 296700324, 461446326, 926790961); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class CtDlwqidWy
 { 
public: bool FVItQhzsb; double FVItQhzsbCtDlwqidW; CtDlwqidWy(); void JTuXIUfIzYhE(string FVItQhzsbJTuXIUfIzYhE, bool SotZJOnVD, int UXAYQbfNq, float DcqplISUf, long NlpPenXZh);
 protected: bool FVItQhzsbo; double FVItQhzsbCtDlwqidWf; void JTuXIUfIzYhEu(string FVItQhzsbJTuXIUfIzYhEg, bool SotZJOnVDe, int UXAYQbfNqr, float DcqplISUfw, long NlpPenXZhn);
 private: bool FVItQhzsbSotZJOnVD; double FVItQhzsbDcqplISUfCtDlwqidW;
 void JTuXIUfIzYhEv(string SotZJOnVDJTuXIUfIzYhE, bool SotZJOnVDUXAYQbfNq, int UXAYQbfNqFVItQhzsb, float DcqplISUfNlpPenXZh, long NlpPenXZhSotZJOnVD); };
 void CtDlwqidWy::JTuXIUfIzYhE(string FVItQhzsbJTuXIUfIzYhE, bool SotZJOnVD, int UXAYQbfNq, float DcqplISUf, long NlpPenXZh)
 { long OBonIOHDE=1349331684;if (OBonIOHDE == OBonIOHDE- 1 ) OBonIOHDE=1717452003; else OBonIOHDE=940333463;if (OBonIOHDE == OBonIOHDE- 0 ) OBonIOHDE=1967302548; else OBonIOHDE=1327128047;if (OBonIOHDE == OBonIOHDE- 0 ) OBonIOHDE=1528335782; else OBonIOHDE=1795922853;if (OBonIOHDE == OBonIOHDE- 1 ) OBonIOHDE=1144956511; else OBonIOHDE=1291563371;if (OBonIOHDE == OBonIOHDE- 1 ) OBonIOHDE=644824461; else OBonIOHDE=436209228;if (OBonIOHDE == OBonIOHDE- 0 ) OBonIOHDE=847775675; else OBonIOHDE=72408248;float DSyzwfbsK=1778219165.3192399f;if (DSyzwfbsK - DSyzwfbsK> 0.00000001 ) DSyzwfbsK=1091381713.2498780f; else DSyzwfbsK=1102768775.3716529f;if (DSyzwfbsK - DSyzwfbsK> 0.00000001 ) DSyzwfbsK=2127158121.3045331f; else DSyzwfbsK=479316512.7653910f;if (DSyzwfbsK - DSyzwfbsK> 0.00000001 ) DSyzwfbsK=2093034931.0607876f; else DSyzwfbsK=1347780373.9287002f;if (DSyzwfbsK - DSyzwfbsK> 0.00000001 ) DSyzwfbsK=1561711292.9635180f; else DSyzwfbsK=1051024788.2571796f;if (DSyzwfbsK - DSyzwfbsK> 0.00000001 ) DSyzwfbsK=9997212.8468813f; else DSyzwfbsK=45394578.2108644f;if (DSyzwfbsK - DSyzwfbsK> 0.00000001 ) DSyzwfbsK=1140653871.8693308f; else DSyzwfbsK=2049280539.0388309f;float PbFnxGrLt=1630512749.7801804f;if (PbFnxGrLt - PbFnxGrLt> 0.00000001 ) PbFnxGrLt=356947050.6798289f; else PbFnxGrLt=830573027.4278671f;if (PbFnxGrLt - PbFnxGrLt> 0.00000001 ) PbFnxGrLt=895821041.1470039f; else PbFnxGrLt=1490564669.2923484f;if (PbFnxGrLt - PbFnxGrLt> 0.00000001 ) PbFnxGrLt=1728151815.7016010f; else PbFnxGrLt=688806187.5606131f;if (PbFnxGrLt - PbFnxGrLt> 0.00000001 ) PbFnxGrLt=2036283662.6923347f; else PbFnxGrLt=1087649265.5329754f;if (PbFnxGrLt - PbFnxGrLt> 0.00000001 ) PbFnxGrLt=909115177.8868167f; else PbFnxGrLt=706419971.2737626f;if (PbFnxGrLt - PbFnxGrLt> 0.00000001 ) PbFnxGrLt=2013223342.8849196f; else PbFnxGrLt=1330783837.1101582f;float wjMhchmUr=366119844.0643872f;if (wjMhchmUr - wjMhchmUr> 0.00000001 ) wjMhchmUr=1936647686.7332517f; else wjMhchmUr=1344755979.0733521f;if (wjMhchmUr - wjMhchmUr> 0.00000001 ) wjMhchmUr=585897253.3599991f; else wjMhchmUr=856599874.1545472f;if (wjMhchmUr - wjMhchmUr> 0.00000001 ) wjMhchmUr=343224621.3917569f; else wjMhchmUr=1149778213.0062019f;if (wjMhchmUr - wjMhchmUr> 0.00000001 ) wjMhchmUr=1403780400.4700898f; else wjMhchmUr=369671630.1559916f;if (wjMhchmUr - wjMhchmUr> 0.00000001 ) wjMhchmUr=1526105818.8971568f; else wjMhchmUr=916277760.8260723f;if (wjMhchmUr - wjMhchmUr> 0.00000001 ) wjMhchmUr=1317130835.6389828f; else wjMhchmUr=1482941204.9566952f;long gpgZQKDwB=636378685;if (gpgZQKDwB == gpgZQKDwB- 0 ) gpgZQKDwB=1754665032; else gpgZQKDwB=1364746573;if (gpgZQKDwB == gpgZQKDwB- 1 ) gpgZQKDwB=1862944845; else gpgZQKDwB=1781912925;if (gpgZQKDwB == gpgZQKDwB- 1 ) gpgZQKDwB=329777277; else gpgZQKDwB=66804296;if (gpgZQKDwB == gpgZQKDwB- 1 ) gpgZQKDwB=50067350; else gpgZQKDwB=402575526;if (gpgZQKDwB == gpgZQKDwB- 1 ) gpgZQKDwB=1213968760; else gpgZQKDwB=1039508856;if (gpgZQKDwB == gpgZQKDwB- 1 ) gpgZQKDwB=1717684982; else gpgZQKDwB=1386614960;int CtDlwqidW=1178752369;if (CtDlwqidW == CtDlwqidW- 1 ) CtDlwqidW=104885620; else CtDlwqidW=774534027;if (CtDlwqidW == CtDlwqidW- 0 ) CtDlwqidW=112632853; else CtDlwqidW=24712404;if (CtDlwqidW == CtDlwqidW- 0 ) CtDlwqidW=1570032170; else CtDlwqidW=2119911616;if (CtDlwqidW == CtDlwqidW- 1 ) CtDlwqidW=1287288128; else CtDlwqidW=1354652484;if (CtDlwqidW == CtDlwqidW- 1 ) CtDlwqidW=1574276274; else CtDlwqidW=526149411;if (CtDlwqidW == CtDlwqidW- 0 ) CtDlwqidW=2111942498; else CtDlwqidW=811874055; }
 CtDlwqidWy::CtDlwqidWy()
 { this->JTuXIUfIzYhE("FVItQhzsbJTuXIUfIzYhEj", true, 1519158999, 553342458, 432380283); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class GzQSfjprvy
 { 
public: bool pUuxTcgWZ; double pUuxTcgWZGzQSfjprv; GzQSfjprvy(); void rJsWDXMQXOII(string pUuxTcgWZrJsWDXMQXOII, bool eHOqXvbLd, int bXOgMUAfP, float lkfDaNOjh, long JrmeKDfUv);
 protected: bool pUuxTcgWZo; double pUuxTcgWZGzQSfjprvf; void rJsWDXMQXOIIu(string pUuxTcgWZrJsWDXMQXOIIg, bool eHOqXvbLde, int bXOgMUAfPr, float lkfDaNOjhw, long JrmeKDfUvn);
 private: bool pUuxTcgWZeHOqXvbLd; double pUuxTcgWZlkfDaNOjhGzQSfjprv;
 void rJsWDXMQXOIIv(string eHOqXvbLdrJsWDXMQXOII, bool eHOqXvbLdbXOgMUAfP, int bXOgMUAfPpUuxTcgWZ, float lkfDaNOjhJrmeKDfUv, long JrmeKDfUveHOqXvbLd); };
 void GzQSfjprvy::rJsWDXMQXOII(string pUuxTcgWZrJsWDXMQXOII, bool eHOqXvbLd, int bXOgMUAfP, float lkfDaNOjh, long JrmeKDfUv)
 { long PeUDgqqVf=1761564901;if (PeUDgqqVf == PeUDgqqVf- 0 ) PeUDgqqVf=1542649866; else PeUDgqqVf=1658497675;if (PeUDgqqVf == PeUDgqqVf- 0 ) PeUDgqqVf=241184432; else PeUDgqqVf=142660715;if (PeUDgqqVf == PeUDgqqVf- 1 ) PeUDgqqVf=1356337241; else PeUDgqqVf=2104540239;if (PeUDgqqVf == PeUDgqqVf- 0 ) PeUDgqqVf=1372098336; else PeUDgqqVf=2128514071;if (PeUDgqqVf == PeUDgqqVf- 0 ) PeUDgqqVf=1628260413; else PeUDgqqVf=1986964562;if (PeUDgqqVf == PeUDgqqVf- 1 ) PeUDgqqVf=343646787; else PeUDgqqVf=1117777614;float QBravcmZY=265277223.6198524f;if (QBravcmZY - QBravcmZY> 0.00000001 ) QBravcmZY=1389793792.9807433f; else QBravcmZY=840534565.7808438f;if (QBravcmZY - QBravcmZY> 0.00000001 ) QBravcmZY=2139942249.2830654f; else QBravcmZY=1661984353.3068390f;if (QBravcmZY - QBravcmZY> 0.00000001 ) QBravcmZY=1096325733.7380272f; else QBravcmZY=168277171.2658397f;if (QBravcmZY - QBravcmZY> 0.00000001 ) QBravcmZY=354987220.2262934f; else QBravcmZY=223897293.3689817f;if (QBravcmZY - QBravcmZY> 0.00000001 ) QBravcmZY=18838806.9492430f; else QBravcmZY=166510456.6382671f;if (QBravcmZY - QBravcmZY> 0.00000001 ) QBravcmZY=138882065.3934682f; else QBravcmZY=549273547.9164664f;double vFViaSJah=1814715489.7614668;if (vFViaSJah == vFViaSJah ) vFViaSJah=2041120902.1501320; else vFViaSJah=1215682695.0188954;if (vFViaSJah == vFViaSJah ) vFViaSJah=990120746.0026513; else vFViaSJah=323142392.2275119;if (vFViaSJah == vFViaSJah ) vFViaSJah=179110379.5325463; else vFViaSJah=531402410.6460316;if (vFViaSJah == vFViaSJah ) vFViaSJah=729244771.9523588; else vFViaSJah=283691122.6091559;if (vFViaSJah == vFViaSJah ) vFViaSJah=465609923.3372125; else vFViaSJah=944667789.9635015;if (vFViaSJah == vFViaSJah ) vFViaSJah=4701499.7662174; else vFViaSJah=544927965.7626410;float QTvBVMEup=649948868.5703702f;if (QTvBVMEup - QTvBVMEup> 0.00000001 ) QTvBVMEup=789928012.5760432f; else QTvBVMEup=763819157.0126035f;if (QTvBVMEup - QTvBVMEup> 0.00000001 ) QTvBVMEup=1087554979.7351786f; else QTvBVMEup=1487738322.2366309f;if (QTvBVMEup - QTvBVMEup> 0.00000001 ) QTvBVMEup=698703790.2815867f; else QTvBVMEup=624264714.3562187f;if (QTvBVMEup - QTvBVMEup> 0.00000001 ) QTvBVMEup=665239168.4475739f; else QTvBVMEup=1374372695.4630363f;if (QTvBVMEup - QTvBVMEup> 0.00000001 ) QTvBVMEup=1303510455.5142448f; else QTvBVMEup=17287139.3123894f;if (QTvBVMEup - QTvBVMEup> 0.00000001 ) QTvBVMEup=123821909.9907108f; else QTvBVMEup=1189826785.0917708f;long tVaySrTJA=1366483913;if (tVaySrTJA == tVaySrTJA- 0 ) tVaySrTJA=104909927; else tVaySrTJA=676414945;if (tVaySrTJA == tVaySrTJA- 0 ) tVaySrTJA=1224140359; else tVaySrTJA=1042257023;if (tVaySrTJA == tVaySrTJA- 1 ) tVaySrTJA=2074746363; else tVaySrTJA=1521616935;if (tVaySrTJA == tVaySrTJA- 1 ) tVaySrTJA=86166844; else tVaySrTJA=858391382;if (tVaySrTJA == tVaySrTJA- 0 ) tVaySrTJA=111289794; else tVaySrTJA=1856251127;if (tVaySrTJA == tVaySrTJA- 1 ) tVaySrTJA=1196374430; else tVaySrTJA=151657944;long GzQSfjprv=495235939;if (GzQSfjprv == GzQSfjprv- 1 ) GzQSfjprv=1868527270; else GzQSfjprv=1636416844;if (GzQSfjprv == GzQSfjprv- 1 ) GzQSfjprv=1906829182; else GzQSfjprv=372189461;if (GzQSfjprv == GzQSfjprv- 1 ) GzQSfjprv=1321705168; else GzQSfjprv=394316313;if (GzQSfjprv == GzQSfjprv- 0 ) GzQSfjprv=1116011699; else GzQSfjprv=1416856188;if (GzQSfjprv == GzQSfjprv- 1 ) GzQSfjprv=550443527; else GzQSfjprv=1763231698;if (GzQSfjprv == GzQSfjprv- 1 ) GzQSfjprv=1167115584; else GzQSfjprv=161823240; }
 GzQSfjprvy::GzQSfjprvy()
 { this->rJsWDXMQXOII("pUuxTcgWZrJsWDXMQXOIIj", true, 407580501, 1686901633, 465516595); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class qRnZsZEghy
 { 
public: bool rpbVOxAlM; double rpbVOxAlMqRnZsZEgh; qRnZsZEghy(); void RiALhKxKXypy(string rpbVOxAlMRiALhKxKXypy, bool TwYjnNLPG, int WKCBrcyLM, float tIagYDYpA, long NHNJGcbac);
 protected: bool rpbVOxAlMo; double rpbVOxAlMqRnZsZEghf; void RiALhKxKXypyu(string rpbVOxAlMRiALhKxKXypyg, bool TwYjnNLPGe, int WKCBrcyLMr, float tIagYDYpAw, long NHNJGcbacn);
 private: bool rpbVOxAlMTwYjnNLPG; double rpbVOxAlMtIagYDYpAqRnZsZEgh;
 void RiALhKxKXypyv(string TwYjnNLPGRiALhKxKXypy, bool TwYjnNLPGWKCBrcyLM, int WKCBrcyLMrpbVOxAlM, float tIagYDYpANHNJGcbac, long NHNJGcbacTwYjnNLPG); };
 void qRnZsZEghy::RiALhKxKXypy(string rpbVOxAlMRiALhKxKXypy, bool TwYjnNLPG, int WKCBrcyLM, float tIagYDYpA, long NHNJGcbac)
 { double KJgbtQXBj=953683490.2703808;if (KJgbtQXBj == KJgbtQXBj ) KJgbtQXBj=1473900426.2593659; else KJgbtQXBj=740158835.8541812;if (KJgbtQXBj == KJgbtQXBj ) KJgbtQXBj=1240767398.3420299; else KJgbtQXBj=1470335804.8709939;if (KJgbtQXBj == KJgbtQXBj ) KJgbtQXBj=2070424956.5939805; else KJgbtQXBj=285118147.2547539;if (KJgbtQXBj == KJgbtQXBj ) KJgbtQXBj=751659438.8808179; else KJgbtQXBj=2026095417.4846204;if (KJgbtQXBj == KJgbtQXBj ) KJgbtQXBj=1911812446.9058203; else KJgbtQXBj=1362582811.7231272;if (KJgbtQXBj == KJgbtQXBj ) KJgbtQXBj=1060232196.0938611; else KJgbtQXBj=1713299129.9018702;float sPgzFPZrx=776746480.5383859f;if (sPgzFPZrx - sPgzFPZrx> 0.00000001 ) sPgzFPZrx=916308334.0983353f; else sPgzFPZrx=1836124700.7702075f;if (sPgzFPZrx - sPgzFPZrx> 0.00000001 ) sPgzFPZrx=852118743.5654186f; else sPgzFPZrx=661078693.0649026f;if (sPgzFPZrx - sPgzFPZrx> 0.00000001 ) sPgzFPZrx=1949060435.1621358f; else sPgzFPZrx=1273377508.4149767f;if (sPgzFPZrx - sPgzFPZrx> 0.00000001 ) sPgzFPZrx=740862620.9588790f; else sPgzFPZrx=1224856576.8408731f;if (sPgzFPZrx - sPgzFPZrx> 0.00000001 ) sPgzFPZrx=982166735.3444377f; else sPgzFPZrx=533749410.2828381f;if (sPgzFPZrx - sPgzFPZrx> 0.00000001 ) sPgzFPZrx=1208593109.6254301f; else sPgzFPZrx=1831630789.1724374f;int ONeJkFhwc=2087729104;if (ONeJkFhwc == ONeJkFhwc- 1 ) ONeJkFhwc=2096479382; else ONeJkFhwc=1343308394;if (ONeJkFhwc == ONeJkFhwc- 0 ) ONeJkFhwc=1333791047; else ONeJkFhwc=1575449918;if (ONeJkFhwc == ONeJkFhwc- 1 ) ONeJkFhwc=174064022; else ONeJkFhwc=810838435;if (ONeJkFhwc == ONeJkFhwc- 1 ) ONeJkFhwc=1267003689; else ONeJkFhwc=226535569;if (ONeJkFhwc == ONeJkFhwc- 0 ) ONeJkFhwc=2087688582; else ONeJkFhwc=1746702073;if (ONeJkFhwc == ONeJkFhwc- 0 ) ONeJkFhwc=788353771; else ONeJkFhwc=722455912;float ODaXyVfqk=1169160895.7534779f;if (ODaXyVfqk - ODaXyVfqk> 0.00000001 ) ODaXyVfqk=853875344.2099994f; else ODaXyVfqk=1908351966.1269462f;if (ODaXyVfqk - ODaXyVfqk> 0.00000001 ) ODaXyVfqk=1202717096.9632504f; else ODaXyVfqk=497024793.3599187f;if (ODaXyVfqk - ODaXyVfqk> 0.00000001 ) ODaXyVfqk=1728743756.0430337f; else ODaXyVfqk=549377059.0584200f;if (ODaXyVfqk - ODaXyVfqk> 0.00000001 ) ODaXyVfqk=1152106702.8255089f; else ODaXyVfqk=200522918.9022850f;if (ODaXyVfqk - ODaXyVfqk> 0.00000001 ) ODaXyVfqk=2146779862.6018182f; else ODaXyVfqk=15910822.8401450f;if (ODaXyVfqk - ODaXyVfqk> 0.00000001 ) ODaXyVfqk=488169069.1694156f; else ODaXyVfqk=1536675546.4542191f;float EmbmoVelc=707728204.6649174f;if (EmbmoVelc - EmbmoVelc> 0.00000001 ) EmbmoVelc=791555989.4717948f; else EmbmoVelc=1119986739.7691200f;if (EmbmoVelc - EmbmoVelc> 0.00000001 ) EmbmoVelc=1764303394.4547934f; else EmbmoVelc=1051079423.4841611f;if (EmbmoVelc - EmbmoVelc> 0.00000001 ) EmbmoVelc=184397039.0616269f; else EmbmoVelc=334860134.4830476f;if (EmbmoVelc - EmbmoVelc> 0.00000001 ) EmbmoVelc=602682458.6390483f; else EmbmoVelc=105469899.1122411f;if (EmbmoVelc - EmbmoVelc> 0.00000001 ) EmbmoVelc=569121011.9764488f; else EmbmoVelc=625583174.1861411f;if (EmbmoVelc - EmbmoVelc> 0.00000001 ) EmbmoVelc=720873758.8285798f; else EmbmoVelc=202358362.6622389f;float qRnZsZEgh=128972048.0518268f;if (qRnZsZEgh - qRnZsZEgh> 0.00000001 ) qRnZsZEgh=1669306434.8543030f; else qRnZsZEgh=39432214.2931564f;if (qRnZsZEgh - qRnZsZEgh> 0.00000001 ) qRnZsZEgh=977755445.1763764f; else qRnZsZEgh=1490128855.7375113f;if (qRnZsZEgh - qRnZsZEgh> 0.00000001 ) qRnZsZEgh=1367146.8351188f; else qRnZsZEgh=74002029.1051071f;if (qRnZsZEgh - qRnZsZEgh> 0.00000001 ) qRnZsZEgh=358985348.1045370f; else qRnZsZEgh=1547102323.9555151f;if (qRnZsZEgh - qRnZsZEgh> 0.00000001 ) qRnZsZEgh=191201692.2880375f; else qRnZsZEgh=1133268129.7815860f;if (qRnZsZEgh - qRnZsZEgh> 0.00000001 ) qRnZsZEgh=1576153703.7227936f; else qRnZsZEgh=158153200.4318430f; }
 qRnZsZEghy::qRnZsZEghy()
 { this->RiALhKxKXypy("rpbVOxAlMRiALhKxKXypyj", true, 322669366, 1877811790, 1150010531); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class QGUlnYIgry
 { 
public: bool fETreKiSx; double fETreKiSxQGUlnYIgr; QGUlnYIgry(); void ifPIgcnhXOwR(string fETreKiSxifPIgcnhXOwR, bool WGiaEcGwV, int zUzinhKRL, float EpbdWzdUC, long KLthYEBOV);
 protected: bool fETreKiSxo; double fETreKiSxQGUlnYIgrf; void ifPIgcnhXOwRu(string fETreKiSxifPIgcnhXOwRg, bool WGiaEcGwVe, int zUzinhKRLr, float EpbdWzdUCw, long KLthYEBOVn);
 private: bool fETreKiSxWGiaEcGwV; double fETreKiSxEpbdWzdUCQGUlnYIgr;
 void ifPIgcnhXOwRv(string WGiaEcGwVifPIgcnhXOwR, bool WGiaEcGwVzUzinhKRL, int zUzinhKRLfETreKiSx, float EpbdWzdUCKLthYEBOV, long KLthYEBOVWGiaEcGwV); };
 void QGUlnYIgry::ifPIgcnhXOwR(string fETreKiSxifPIgcnhXOwR, bool WGiaEcGwV, int zUzinhKRL, float EpbdWzdUC, long KLthYEBOV)
 { float PBaKBioqj=333073833.7929615f;if (PBaKBioqj - PBaKBioqj> 0.00000001 ) PBaKBioqj=362820603.9280948f; else PBaKBioqj=1891471527.0093767f;if (PBaKBioqj - PBaKBioqj> 0.00000001 ) PBaKBioqj=1280629986.7776340f; else PBaKBioqj=1845383700.4585708f;if (PBaKBioqj - PBaKBioqj> 0.00000001 ) PBaKBioqj=517710922.6171426f; else PBaKBioqj=124472665.3480533f;if (PBaKBioqj - PBaKBioqj> 0.00000001 ) PBaKBioqj=977077031.7673760f; else PBaKBioqj=218248059.3644766f;if (PBaKBioqj - PBaKBioqj> 0.00000001 ) PBaKBioqj=1698610386.8063405f; else PBaKBioqj=1996576526.9223415f;if (PBaKBioqj - PBaKBioqj> 0.00000001 ) PBaKBioqj=1379511556.4969288f; else PBaKBioqj=1644353326.0220494f;float QnlhEbQJm=251794140.6614667f;if (QnlhEbQJm - QnlhEbQJm> 0.00000001 ) QnlhEbQJm=314064901.0117899f; else QnlhEbQJm=1316806126.4228287f;if (QnlhEbQJm - QnlhEbQJm> 0.00000001 ) QnlhEbQJm=865868783.5415072f; else QnlhEbQJm=1011275452.6947734f;if (QnlhEbQJm - QnlhEbQJm> 0.00000001 ) QnlhEbQJm=1822087444.0791375f; else QnlhEbQJm=988378067.9575155f;if (QnlhEbQJm - QnlhEbQJm> 0.00000001 ) QnlhEbQJm=1107860791.3780511f; else QnlhEbQJm=1851380720.2007954f;if (QnlhEbQJm - QnlhEbQJm> 0.00000001 ) QnlhEbQJm=827665733.2702754f; else QnlhEbQJm=546239714.6379226f;if (QnlhEbQJm - QnlhEbQJm> 0.00000001 ) QnlhEbQJm=55011196.9519384f; else QnlhEbQJm=104464187.3783348f;int yXSLHmpiQ=1643891448;if (yXSLHmpiQ == yXSLHmpiQ- 1 ) yXSLHmpiQ=907480007; else yXSLHmpiQ=1474685135;if (yXSLHmpiQ == yXSLHmpiQ- 0 ) yXSLHmpiQ=109164676; else yXSLHmpiQ=280828340;if (yXSLHmpiQ == yXSLHmpiQ- 1 ) yXSLHmpiQ=309837765; else yXSLHmpiQ=1543672115;if (yXSLHmpiQ == yXSLHmpiQ- 1 ) yXSLHmpiQ=147777214; else yXSLHmpiQ=1533365902;if (yXSLHmpiQ == yXSLHmpiQ- 0 ) yXSLHmpiQ=482310269; else yXSLHmpiQ=304096225;if (yXSLHmpiQ == yXSLHmpiQ- 1 ) yXSLHmpiQ=1294267587; else yXSLHmpiQ=436413890;long LnLMNCRDY=1356149295;if (LnLMNCRDY == LnLMNCRDY- 0 ) LnLMNCRDY=216303383; else LnLMNCRDY=219709379;if (LnLMNCRDY == LnLMNCRDY- 1 ) LnLMNCRDY=471494464; else LnLMNCRDY=2113948469;if (LnLMNCRDY == LnLMNCRDY- 1 ) LnLMNCRDY=966074120; else LnLMNCRDY=1302411412;if (LnLMNCRDY == LnLMNCRDY- 0 ) LnLMNCRDY=658470036; else LnLMNCRDY=1521926183;if (LnLMNCRDY == LnLMNCRDY- 1 ) LnLMNCRDY=783610736; else LnLMNCRDY=1576732913;if (LnLMNCRDY == LnLMNCRDY- 0 ) LnLMNCRDY=1017717967; else LnLMNCRDY=2118954855;long EJAYpcIeL=106693790;if (EJAYpcIeL == EJAYpcIeL- 0 ) EJAYpcIeL=1866051627; else EJAYpcIeL=1883103755;if (EJAYpcIeL == EJAYpcIeL- 1 ) EJAYpcIeL=736873319; else EJAYpcIeL=1537011103;if (EJAYpcIeL == EJAYpcIeL- 0 ) EJAYpcIeL=1798885997; else EJAYpcIeL=954544714;if (EJAYpcIeL == EJAYpcIeL- 0 ) EJAYpcIeL=2089440022; else EJAYpcIeL=917876433;if (EJAYpcIeL == EJAYpcIeL- 1 ) EJAYpcIeL=1169028912; else EJAYpcIeL=1479986528;if (EJAYpcIeL == EJAYpcIeL- 1 ) EJAYpcIeL=528965183; else EJAYpcIeL=1517991219;int QGUlnYIgr=1724250664;if (QGUlnYIgr == QGUlnYIgr- 1 ) QGUlnYIgr=1087315252; else QGUlnYIgr=846345548;if (QGUlnYIgr == QGUlnYIgr- 1 ) QGUlnYIgr=2035644451; else QGUlnYIgr=1709659635;if (QGUlnYIgr == QGUlnYIgr- 0 ) QGUlnYIgr=1120422132; else QGUlnYIgr=164060077;if (QGUlnYIgr == QGUlnYIgr- 1 ) QGUlnYIgr=677817328; else QGUlnYIgr=1752552242;if (QGUlnYIgr == QGUlnYIgr- 1 ) QGUlnYIgr=816215099; else QGUlnYIgr=734722140;if (QGUlnYIgr == QGUlnYIgr- 1 ) QGUlnYIgr=1644701251; else QGUlnYIgr=880588499; }
 QGUlnYIgry::QGUlnYIgry()
 { this->ifPIgcnhXOwR("fETreKiSxifPIgcnhXOwRj", true, 525954148, 176306006, 1463904433); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class EmeYnxppoy
 { 
public: bool BXtGdonlU; double BXtGdonlUEmeYnxppo; EmeYnxppoy(); void suOLPXmdotuu(string BXtGdonlUsuOLPXmdotuu, bool NkMsQMYZC, int MzIHcIMbA, float tkQVauaUD, long KRGXatPhu);
 protected: bool BXtGdonlUo; double BXtGdonlUEmeYnxppof; void suOLPXmdotuuu(string BXtGdonlUsuOLPXmdotuug, bool NkMsQMYZCe, int MzIHcIMbAr, float tkQVauaUDw, long KRGXatPhun);
 private: bool BXtGdonlUNkMsQMYZC; double BXtGdonlUtkQVauaUDEmeYnxppo;
 void suOLPXmdotuuv(string NkMsQMYZCsuOLPXmdotuu, bool NkMsQMYZCMzIHcIMbA, int MzIHcIMbABXtGdonlU, float tkQVauaUDKRGXatPhu, long KRGXatPhuNkMsQMYZC); };
 void EmeYnxppoy::suOLPXmdotuu(string BXtGdonlUsuOLPXmdotuu, bool NkMsQMYZC, int MzIHcIMbA, float tkQVauaUD, long KRGXatPhu)
 { int HaQZJsQiK=445638621;if (HaQZJsQiK == HaQZJsQiK- 1 ) HaQZJsQiK=19212373; else HaQZJsQiK=766410438;if (HaQZJsQiK == HaQZJsQiK- 1 ) HaQZJsQiK=1955376507; else HaQZJsQiK=214232109;if (HaQZJsQiK == HaQZJsQiK- 0 ) HaQZJsQiK=1750826102; else HaQZJsQiK=1017339472;if (HaQZJsQiK == HaQZJsQiK- 0 ) HaQZJsQiK=697807006; else HaQZJsQiK=367278018;if (HaQZJsQiK == HaQZJsQiK- 0 ) HaQZJsQiK=1339539055; else HaQZJsQiK=1094317314;if (HaQZJsQiK == HaQZJsQiK- 0 ) HaQZJsQiK=231089631; else HaQZJsQiK=20082177;long VWPNdZCwE=1207878958;if (VWPNdZCwE == VWPNdZCwE- 1 ) VWPNdZCwE=1042176029; else VWPNdZCwE=1505856824;if (VWPNdZCwE == VWPNdZCwE- 1 ) VWPNdZCwE=430508429; else VWPNdZCwE=901425819;if (VWPNdZCwE == VWPNdZCwE- 1 ) VWPNdZCwE=79905804; else VWPNdZCwE=537512953;if (VWPNdZCwE == VWPNdZCwE- 0 ) VWPNdZCwE=97796602; else VWPNdZCwE=1623830903;if (VWPNdZCwE == VWPNdZCwE- 0 ) VWPNdZCwE=738535977; else VWPNdZCwE=2026508879;if (VWPNdZCwE == VWPNdZCwE- 0 ) VWPNdZCwE=1748085786; else VWPNdZCwE=1460998195;long hDeOgSqNP=1189528540;if (hDeOgSqNP == hDeOgSqNP- 0 ) hDeOgSqNP=1496679240; else hDeOgSqNP=2106739746;if (hDeOgSqNP == hDeOgSqNP- 0 ) hDeOgSqNP=58890783; else hDeOgSqNP=1327670302;if (hDeOgSqNP == hDeOgSqNP- 1 ) hDeOgSqNP=28167061; else hDeOgSqNP=1439381506;if (hDeOgSqNP == hDeOgSqNP- 1 ) hDeOgSqNP=2078218090; else hDeOgSqNP=1851613175;if (hDeOgSqNP == hDeOgSqNP- 1 ) hDeOgSqNP=263566528; else hDeOgSqNP=326440743;if (hDeOgSqNP == hDeOgSqNP- 1 ) hDeOgSqNP=1770470003; else hDeOgSqNP=52058296;long MlpUCZRRA=185875710;if (MlpUCZRRA == MlpUCZRRA- 1 ) MlpUCZRRA=135354182; else MlpUCZRRA=1216933956;if (MlpUCZRRA == MlpUCZRRA- 1 ) MlpUCZRRA=762562251; else MlpUCZRRA=1142948144;if (MlpUCZRRA == MlpUCZRRA- 0 ) MlpUCZRRA=201065725; else MlpUCZRRA=707850249;if (MlpUCZRRA == MlpUCZRRA- 1 ) MlpUCZRRA=365732817; else MlpUCZRRA=1629183067;if (MlpUCZRRA == MlpUCZRRA- 0 ) MlpUCZRRA=668613836; else MlpUCZRRA=331545604;if (MlpUCZRRA == MlpUCZRRA- 0 ) MlpUCZRRA=1623179779; else MlpUCZRRA=1871800870;int vdmInclSO=965068558;if (vdmInclSO == vdmInclSO- 1 ) vdmInclSO=1794012351; else vdmInclSO=1189044738;if (vdmInclSO == vdmInclSO- 0 ) vdmInclSO=670886584; else vdmInclSO=903160869;if (vdmInclSO == vdmInclSO- 0 ) vdmInclSO=1549403540; else vdmInclSO=1412876370;if (vdmInclSO == vdmInclSO- 1 ) vdmInclSO=1179711897; else vdmInclSO=1750278170;if (vdmInclSO == vdmInclSO- 1 ) vdmInclSO=1575122381; else vdmInclSO=726378901;if (vdmInclSO == vdmInclSO- 1 ) vdmInclSO=637859291; else vdmInclSO=1900948708;float EmeYnxppo=150313108.8918911f;if (EmeYnxppo - EmeYnxppo> 0.00000001 ) EmeYnxppo=330091021.9244023f; else EmeYnxppo=1562210076.2085390f;if (EmeYnxppo - EmeYnxppo> 0.00000001 ) EmeYnxppo=1325644013.3478759f; else EmeYnxppo=1015110264.7027525f;if (EmeYnxppo - EmeYnxppo> 0.00000001 ) EmeYnxppo=1759391893.5177939f; else EmeYnxppo=304840466.8664114f;if (EmeYnxppo - EmeYnxppo> 0.00000001 ) EmeYnxppo=988462815.9837105f; else EmeYnxppo=788828991.5513732f;if (EmeYnxppo - EmeYnxppo> 0.00000001 ) EmeYnxppo=1741006929.3385087f; else EmeYnxppo=577191363.9295716f;if (EmeYnxppo - EmeYnxppo> 0.00000001 ) EmeYnxppo=659056466.9247469f; else EmeYnxppo=1844105104.2915310f; }
 EmeYnxppoy::EmeYnxppoy()
 { this->suOLPXmdotuu("BXtGdonlUsuOLPXmdotuuj", true, 1963685374, 206417220, 434875842); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class CJPaIiVOpy
 { 
public: bool rWgaolRas; double rWgaolRasCJPaIiVOp; CJPaIiVOpy(); void WUnepiVuFtDN(string rWgaolRasWUnepiVuFtDN, bool sxfocvTzz, int UjpoIyQNS, float WZJRUmnHj, long pUPJHTfhm);
 protected: bool rWgaolRaso; double rWgaolRasCJPaIiVOpf; void WUnepiVuFtDNu(string rWgaolRasWUnepiVuFtDNg, bool sxfocvTzze, int UjpoIyQNSr, float WZJRUmnHjw, long pUPJHTfhmn);
 private: bool rWgaolRassxfocvTzz; double rWgaolRasWZJRUmnHjCJPaIiVOp;
 void WUnepiVuFtDNv(string sxfocvTzzWUnepiVuFtDN, bool sxfocvTzzUjpoIyQNS, int UjpoIyQNSrWgaolRas, float WZJRUmnHjpUPJHTfhm, long pUPJHTfhmsxfocvTzz); };
 void CJPaIiVOpy::WUnepiVuFtDN(string rWgaolRasWUnepiVuFtDN, bool sxfocvTzz, int UjpoIyQNS, float WZJRUmnHj, long pUPJHTfhm)
 { float XImTLkGeL=775737713.8202861f;if (XImTLkGeL - XImTLkGeL> 0.00000001 ) XImTLkGeL=531487726.8915646f; else XImTLkGeL=268063729.3743840f;if (XImTLkGeL - XImTLkGeL> 0.00000001 ) XImTLkGeL=1055450011.5231947f; else XImTLkGeL=1971660407.1902627f;if (XImTLkGeL - XImTLkGeL> 0.00000001 ) XImTLkGeL=1449920596.2212891f; else XImTLkGeL=287664212.0222080f;if (XImTLkGeL - XImTLkGeL> 0.00000001 ) XImTLkGeL=808048063.9604583f; else XImTLkGeL=245045571.1729248f;if (XImTLkGeL - XImTLkGeL> 0.00000001 ) XImTLkGeL=522981867.0231391f; else XImTLkGeL=82457882.5420596f;if (XImTLkGeL - XImTLkGeL> 0.00000001 ) XImTLkGeL=312702622.0190773f; else XImTLkGeL=325937973.3191542f;long sPfcSyBsE=1531512478;if (sPfcSyBsE == sPfcSyBsE- 0 ) sPfcSyBsE=1083794728; else sPfcSyBsE=1359453901;if (sPfcSyBsE == sPfcSyBsE- 1 ) sPfcSyBsE=1752707010; else sPfcSyBsE=1704081553;if (sPfcSyBsE == sPfcSyBsE- 1 ) sPfcSyBsE=2130964095; else sPfcSyBsE=1941139484;if (sPfcSyBsE == sPfcSyBsE- 0 ) sPfcSyBsE=1703158438; else sPfcSyBsE=41698333;if (sPfcSyBsE == sPfcSyBsE- 0 ) sPfcSyBsE=1536439190; else sPfcSyBsE=1690495655;if (sPfcSyBsE == sPfcSyBsE- 0 ) sPfcSyBsE=1015645430; else sPfcSyBsE=155691742;double ISeejwbmq=1954404432.4961592;if (ISeejwbmq == ISeejwbmq ) ISeejwbmq=1690047793.2994670; else ISeejwbmq=1233814076.3247814;if (ISeejwbmq == ISeejwbmq ) ISeejwbmq=2022363672.8801727; else ISeejwbmq=1133776110.4061272;if (ISeejwbmq == ISeejwbmq ) ISeejwbmq=1446389599.5992097; else ISeejwbmq=844546034.0434731;if (ISeejwbmq == ISeejwbmq ) ISeejwbmq=1963618455.9298077; else ISeejwbmq=1954619115.2609759;if (ISeejwbmq == ISeejwbmq ) ISeejwbmq=2144234851.9335099; else ISeejwbmq=212859133.3668289;if (ISeejwbmq == ISeejwbmq ) ISeejwbmq=104118629.4880075; else ISeejwbmq=1306908941.9832054;long tPMTpBFyr=134134683;if (tPMTpBFyr == tPMTpBFyr- 1 ) tPMTpBFyr=1698702418; else tPMTpBFyr=1219503817;if (tPMTpBFyr == tPMTpBFyr- 1 ) tPMTpBFyr=966827201; else tPMTpBFyr=1881003569;if (tPMTpBFyr == tPMTpBFyr- 0 ) tPMTpBFyr=1559318988; else tPMTpBFyr=1591581968;if (tPMTpBFyr == tPMTpBFyr- 0 ) tPMTpBFyr=792257265; else tPMTpBFyr=737831889;if (tPMTpBFyr == tPMTpBFyr- 0 ) tPMTpBFyr=712388938; else tPMTpBFyr=1013751678;if (tPMTpBFyr == tPMTpBFyr- 1 ) tPMTpBFyr=435221217; else tPMTpBFyr=1906908588;double bBOfDYZpL=121238227.2907063;if (bBOfDYZpL == bBOfDYZpL ) bBOfDYZpL=1646121737.6747084; else bBOfDYZpL=505781837.8069557;if (bBOfDYZpL == bBOfDYZpL ) bBOfDYZpL=783373827.5336813; else bBOfDYZpL=2109167669.8834812;if (bBOfDYZpL == bBOfDYZpL ) bBOfDYZpL=1033524318.1424960; else bBOfDYZpL=2001360989.6570411;if (bBOfDYZpL == bBOfDYZpL ) bBOfDYZpL=85122879.3934328; else bBOfDYZpL=239248694.6723618;if (bBOfDYZpL == bBOfDYZpL ) bBOfDYZpL=1543319093.9142737; else bBOfDYZpL=1945571542.7457079;if (bBOfDYZpL == bBOfDYZpL ) bBOfDYZpL=1707330349.8765025; else bBOfDYZpL=1918104962.9105955;long CJPaIiVOp=209806240;if (CJPaIiVOp == CJPaIiVOp- 1 ) CJPaIiVOp=1221817489; else CJPaIiVOp=881510747;if (CJPaIiVOp == CJPaIiVOp- 0 ) CJPaIiVOp=604472971; else CJPaIiVOp=445997800;if (CJPaIiVOp == CJPaIiVOp- 1 ) CJPaIiVOp=1582400086; else CJPaIiVOp=850299870;if (CJPaIiVOp == CJPaIiVOp- 0 ) CJPaIiVOp=395085444; else CJPaIiVOp=98465825;if (CJPaIiVOp == CJPaIiVOp- 1 ) CJPaIiVOp=441556811; else CJPaIiVOp=1284531783;if (CJPaIiVOp == CJPaIiVOp- 0 ) CJPaIiVOp=421387172; else CJPaIiVOp=432637921; }
 CJPaIiVOpy::CJPaIiVOpy()
 { this->WUnepiVuFtDN("rWgaolRasWUnepiVuFtDNj", true, 409324817, 56709867, 535116686); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class gDWztEmJey
 { 
public: bool OhABsjaUz; double OhABsjaUzgDWztEmJe; gDWztEmJey(); void FTCyNTicijdq(string OhABsjaUzFTCyNTicijdq, bool kOakTAgkD, int gvdlrEPZv, float VwsDQTTet, long DTHeYTNuo);
 protected: bool OhABsjaUzo; double OhABsjaUzgDWztEmJef; void FTCyNTicijdqu(string OhABsjaUzFTCyNTicijdqg, bool kOakTAgkDe, int gvdlrEPZvr, float VwsDQTTetw, long DTHeYTNuon);
 private: bool OhABsjaUzkOakTAgkD; double OhABsjaUzVwsDQTTetgDWztEmJe;
 void FTCyNTicijdqv(string kOakTAgkDFTCyNTicijdq, bool kOakTAgkDgvdlrEPZv, int gvdlrEPZvOhABsjaUz, float VwsDQTTetDTHeYTNuo, long DTHeYTNuokOakTAgkD); };
 void gDWztEmJey::FTCyNTicijdq(string OhABsjaUzFTCyNTicijdq, bool kOakTAgkD, int gvdlrEPZv, float VwsDQTTet, long DTHeYTNuo)
 { float NldWiVAOZ=1689092979.7086895f;if (NldWiVAOZ - NldWiVAOZ> 0.00000001 ) NldWiVAOZ=1430462155.5809531f; else NldWiVAOZ=242273470.6960669f;if (NldWiVAOZ - NldWiVAOZ> 0.00000001 ) NldWiVAOZ=2006636200.7674487f; else NldWiVAOZ=867294963.4137175f;if (NldWiVAOZ - NldWiVAOZ> 0.00000001 ) NldWiVAOZ=1230462118.2178138f; else NldWiVAOZ=409421356.2168262f;if (NldWiVAOZ - NldWiVAOZ> 0.00000001 ) NldWiVAOZ=130308269.6013430f; else NldWiVAOZ=1784147990.5135282f;if (NldWiVAOZ - NldWiVAOZ> 0.00000001 ) NldWiVAOZ=2135951773.8735675f; else NldWiVAOZ=1651254690.8025325f;if (NldWiVAOZ - NldWiVAOZ> 0.00000001 ) NldWiVAOZ=1846961962.5272258f; else NldWiVAOZ=1294579486.2347557f;long TQxWhYVOP=155126099;if (TQxWhYVOP == TQxWhYVOP- 0 ) TQxWhYVOP=1082349588; else TQxWhYVOP=1510607432;if (TQxWhYVOP == TQxWhYVOP- 0 ) TQxWhYVOP=45204984; else TQxWhYVOP=1426064502;if (TQxWhYVOP == TQxWhYVOP- 0 ) TQxWhYVOP=706532933; else TQxWhYVOP=1951899141;if (TQxWhYVOP == TQxWhYVOP- 0 ) TQxWhYVOP=298444994; else TQxWhYVOP=53967927;if (TQxWhYVOP == TQxWhYVOP- 0 ) TQxWhYVOP=1929451169; else TQxWhYVOP=1185759247;if (TQxWhYVOP == TQxWhYVOP- 1 ) TQxWhYVOP=173745290; else TQxWhYVOP=613097170;int yHOqjfdWy=73136691;if (yHOqjfdWy == yHOqjfdWy- 1 ) yHOqjfdWy=1841710618; else yHOqjfdWy=1617405273;if (yHOqjfdWy == yHOqjfdWy- 0 ) yHOqjfdWy=600765204; else yHOqjfdWy=1883905400;if (yHOqjfdWy == yHOqjfdWy- 1 ) yHOqjfdWy=370109345; else yHOqjfdWy=1385516397;if (yHOqjfdWy == yHOqjfdWy- 0 ) yHOqjfdWy=1540732959; else yHOqjfdWy=1301667209;if (yHOqjfdWy == yHOqjfdWy- 1 ) yHOqjfdWy=1765928985; else yHOqjfdWy=527892049;if (yHOqjfdWy == yHOqjfdWy- 0 ) yHOqjfdWy=456307516; else yHOqjfdWy=1813666972;float fgydWNtwO=1623863924.8628108f;if (fgydWNtwO - fgydWNtwO> 0.00000001 ) fgydWNtwO=2062424014.8833108f; else fgydWNtwO=1604690757.8071937f;if (fgydWNtwO - fgydWNtwO> 0.00000001 ) fgydWNtwO=323557404.7005330f; else fgydWNtwO=1360300200.3407812f;if (fgydWNtwO - fgydWNtwO> 0.00000001 ) fgydWNtwO=972866990.3706564f; else fgydWNtwO=2084779566.9675010f;if (fgydWNtwO - fgydWNtwO> 0.00000001 ) fgydWNtwO=982560046.2971422f; else fgydWNtwO=1626046661.7239796f;if (fgydWNtwO - fgydWNtwO> 0.00000001 ) fgydWNtwO=2091312123.4473975f; else fgydWNtwO=1952668273.3765848f;if (fgydWNtwO - fgydWNtwO> 0.00000001 ) fgydWNtwO=1085327441.5404202f; else fgydWNtwO=44702871.5365917f;float jknkpaIAJ=1352510876.1240642f;if (jknkpaIAJ - jknkpaIAJ> 0.00000001 ) jknkpaIAJ=193791059.9562832f; else jknkpaIAJ=1773825271.6010104f;if (jknkpaIAJ - jknkpaIAJ> 0.00000001 ) jknkpaIAJ=1600352515.2765226f; else jknkpaIAJ=126279385.3453902f;if (jknkpaIAJ - jknkpaIAJ> 0.00000001 ) jknkpaIAJ=247221239.2914766f; else jknkpaIAJ=222364324.2915631f;if (jknkpaIAJ - jknkpaIAJ> 0.00000001 ) jknkpaIAJ=1932500401.2051030f; else jknkpaIAJ=1844316838.6854367f;if (jknkpaIAJ - jknkpaIAJ> 0.00000001 ) jknkpaIAJ=2117358120.2199405f; else jknkpaIAJ=891021422.2064590f;if (jknkpaIAJ - jknkpaIAJ> 0.00000001 ) jknkpaIAJ=1807619164.9507961f; else jknkpaIAJ=178640884.5130837f;int gDWztEmJe=127506201;if (gDWztEmJe == gDWztEmJe- 1 ) gDWztEmJe=1434566445; else gDWztEmJe=697365013;if (gDWztEmJe == gDWztEmJe- 1 ) gDWztEmJe=698156803; else gDWztEmJe=833026025;if (gDWztEmJe == gDWztEmJe- 0 ) gDWztEmJe=459883493; else gDWztEmJe=97163431;if (gDWztEmJe == gDWztEmJe- 1 ) gDWztEmJe=1247753348; else gDWztEmJe=1904414699;if (gDWztEmJe == gDWztEmJe- 0 ) gDWztEmJe=634845227; else gDWztEmJe=1122202190;if (gDWztEmJe == gDWztEmJe- 0 ) gDWztEmJe=1940076924; else gDWztEmJe=564924719; }
 gDWztEmJey::gDWztEmJey()
 { this->FTCyNTicijdq("OhABsjaUzFTCyNTicijdqj", true, 300188956, 1496030088, 1065991143); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class iCtpLUtmOy
 { 
public: bool CdFTffuJS; double CdFTffuJSiCtpLUtmO; iCtpLUtmOy(); void LGqjKjnhxxAG(string CdFTffuJSLGqjKjnhxxAG, bool PsXwDGAkG, int ERcCWujeP, float bsflArlNY, long ZAJSzxFHK);
 protected: bool CdFTffuJSo; double CdFTffuJSiCtpLUtmOf; void LGqjKjnhxxAGu(string CdFTffuJSLGqjKjnhxxAGg, bool PsXwDGAkGe, int ERcCWujePr, float bsflArlNYw, long ZAJSzxFHKn);
 private: bool CdFTffuJSPsXwDGAkG; double CdFTffuJSbsflArlNYiCtpLUtmO;
 void LGqjKjnhxxAGv(string PsXwDGAkGLGqjKjnhxxAG, bool PsXwDGAkGERcCWujeP, int ERcCWujePCdFTffuJS, float bsflArlNYZAJSzxFHK, long ZAJSzxFHKPsXwDGAkG); };
 void iCtpLUtmOy::LGqjKjnhxxAG(string CdFTffuJSLGqjKjnhxxAG, bool PsXwDGAkG, int ERcCWujeP, float bsflArlNY, long ZAJSzxFHK)
 { long AEaULOelW=1375410797;if (AEaULOelW == AEaULOelW- 1 ) AEaULOelW=2054577794; else AEaULOelW=9760962;if (AEaULOelW == AEaULOelW- 1 ) AEaULOelW=485502297; else AEaULOelW=1099070133;if (AEaULOelW == AEaULOelW- 1 ) AEaULOelW=1530031105; else AEaULOelW=1095983752;if (AEaULOelW == AEaULOelW- 1 ) AEaULOelW=1941220995; else AEaULOelW=1427215375;if (AEaULOelW == AEaULOelW- 0 ) AEaULOelW=958814668; else AEaULOelW=794690390;if (AEaULOelW == AEaULOelW- 0 ) AEaULOelW=1516213968; else AEaULOelW=43428335;long VIPFXhkrm=1370838928;if (VIPFXhkrm == VIPFXhkrm- 0 ) VIPFXhkrm=135017387; else VIPFXhkrm=855221526;if (VIPFXhkrm == VIPFXhkrm- 0 ) VIPFXhkrm=1337649757; else VIPFXhkrm=2039103478;if (VIPFXhkrm == VIPFXhkrm- 0 ) VIPFXhkrm=982152723; else VIPFXhkrm=406693347;if (VIPFXhkrm == VIPFXhkrm- 0 ) VIPFXhkrm=1792759255; else VIPFXhkrm=985212068;if (VIPFXhkrm == VIPFXhkrm- 0 ) VIPFXhkrm=1270005463; else VIPFXhkrm=1794053050;if (VIPFXhkrm == VIPFXhkrm- 0 ) VIPFXhkrm=2102692343; else VIPFXhkrm=1144679364;double yqRxaTvYI=1759459721.2012614;if (yqRxaTvYI == yqRxaTvYI ) yqRxaTvYI=379730549.6069643; else yqRxaTvYI=357941735.8303919;if (yqRxaTvYI == yqRxaTvYI ) yqRxaTvYI=932706189.7408893; else yqRxaTvYI=281085479.5118455;if (yqRxaTvYI == yqRxaTvYI ) yqRxaTvYI=1164688391.2334985; else yqRxaTvYI=1542760126.5023749;if (yqRxaTvYI == yqRxaTvYI ) yqRxaTvYI=363045774.2395535; else yqRxaTvYI=1024118129.6248212;if (yqRxaTvYI == yqRxaTvYI ) yqRxaTvYI=1694284366.9513986; else yqRxaTvYI=63235199.0790453;if (yqRxaTvYI == yqRxaTvYI ) yqRxaTvYI=501046547.5961653; else yqRxaTvYI=1758541462.8349316;double rfkjRdWBA=1424107553.4872576;if (rfkjRdWBA == rfkjRdWBA ) rfkjRdWBA=133765430.2544859; else rfkjRdWBA=1842569465.0098207;if (rfkjRdWBA == rfkjRdWBA ) rfkjRdWBA=2003676924.1943773; else rfkjRdWBA=859310035.8602117;if (rfkjRdWBA == rfkjRdWBA ) rfkjRdWBA=738850278.5683932; else rfkjRdWBA=2058303656.5664676;if (rfkjRdWBA == rfkjRdWBA ) rfkjRdWBA=393258074.3591054; else rfkjRdWBA=1647884447.9409145;if (rfkjRdWBA == rfkjRdWBA ) rfkjRdWBA=364485354.0537525; else rfkjRdWBA=1647773876.4164757;if (rfkjRdWBA == rfkjRdWBA ) rfkjRdWBA=1976548317.4891176; else rfkjRdWBA=1883461702.1121646;float tTqxnZDSk=1953430355.9323637f;if (tTqxnZDSk - tTqxnZDSk> 0.00000001 ) tTqxnZDSk=130258690.3209414f; else tTqxnZDSk=1904237894.3769539f;if (tTqxnZDSk - tTqxnZDSk> 0.00000001 ) tTqxnZDSk=1811181433.5467595f; else tTqxnZDSk=1795685761.7118258f;if (tTqxnZDSk - tTqxnZDSk> 0.00000001 ) tTqxnZDSk=1101785027.4733309f; else tTqxnZDSk=88456116.5896265f;if (tTqxnZDSk - tTqxnZDSk> 0.00000001 ) tTqxnZDSk=206150537.1838334f; else tTqxnZDSk=739740908.9662426f;if (tTqxnZDSk - tTqxnZDSk> 0.00000001 ) tTqxnZDSk=492175752.1013769f; else tTqxnZDSk=313531628.0472410f;if (tTqxnZDSk - tTqxnZDSk> 0.00000001 ) tTqxnZDSk=344819112.6823416f; else tTqxnZDSk=918917524.4909255f;long iCtpLUtmO=985016144;if (iCtpLUtmO == iCtpLUtmO- 0 ) iCtpLUtmO=1089312006; else iCtpLUtmO=678584790;if (iCtpLUtmO == iCtpLUtmO- 1 ) iCtpLUtmO=1010913934; else iCtpLUtmO=1555049132;if (iCtpLUtmO == iCtpLUtmO- 0 ) iCtpLUtmO=1296674683; else iCtpLUtmO=1952605312;if (iCtpLUtmO == iCtpLUtmO- 0 ) iCtpLUtmO=1020609443; else iCtpLUtmO=468910540;if (iCtpLUtmO == iCtpLUtmO- 0 ) iCtpLUtmO=2112167308; else iCtpLUtmO=1432305389;if (iCtpLUtmO == iCtpLUtmO- 0 ) iCtpLUtmO=2064083772; else iCtpLUtmO=1664398162; }
 iCtpLUtmOy::iCtpLUtmOy()
 { this->LGqjKjnhxxAG("CdFTffuJSLGqjKjnhxxAGj", true, 1713695456, 627067719, 2030826720); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class NmlfEWLPoy
 { 
public: bool uYTYlIrhO; double uYTYlIrhONmlfEWLPo; NmlfEWLPoy(); void KAWobPRfIWVl(string uYTYlIrhOKAWobPRfIWVl, bool NwClOrcHu, int kfyYnEvRo, float AQucJjKIc, long HEjmYmjAQ);
 protected: bool uYTYlIrhOo; double uYTYlIrhONmlfEWLPof; void KAWobPRfIWVlu(string uYTYlIrhOKAWobPRfIWVlg, bool NwClOrcHue, int kfyYnEvRor, float AQucJjKIcw, long HEjmYmjAQn);
 private: bool uYTYlIrhONwClOrcHu; double uYTYlIrhOAQucJjKIcNmlfEWLPo;
 void KAWobPRfIWVlv(string NwClOrcHuKAWobPRfIWVl, bool NwClOrcHukfyYnEvRo, int kfyYnEvRouYTYlIrhO, float AQucJjKIcHEjmYmjAQ, long HEjmYmjAQNwClOrcHu); };
 void NmlfEWLPoy::KAWobPRfIWVl(string uYTYlIrhOKAWobPRfIWVl, bool NwClOrcHu, int kfyYnEvRo, float AQucJjKIc, long HEjmYmjAQ)
 { int NBevYPUIJ=28885741;if (NBevYPUIJ == NBevYPUIJ- 0 ) NBevYPUIJ=1742415747; else NBevYPUIJ=210396946;if (NBevYPUIJ == NBevYPUIJ- 0 ) NBevYPUIJ=730349098; else NBevYPUIJ=742876884;if (NBevYPUIJ == NBevYPUIJ- 0 ) NBevYPUIJ=448884599; else NBevYPUIJ=1313283280;if (NBevYPUIJ == NBevYPUIJ- 1 ) NBevYPUIJ=1602925842; else NBevYPUIJ=572968349;if (NBevYPUIJ == NBevYPUIJ- 0 ) NBevYPUIJ=732523194; else NBevYPUIJ=1168848118;if (NBevYPUIJ == NBevYPUIJ- 0 ) NBevYPUIJ=2008874222; else NBevYPUIJ=1972929305;long uPjZhnffR=1427057696;if (uPjZhnffR == uPjZhnffR- 1 ) uPjZhnffR=434513321; else uPjZhnffR=2090234903;if (uPjZhnffR == uPjZhnffR- 1 ) uPjZhnffR=483576775; else uPjZhnffR=1819671372;if (uPjZhnffR == uPjZhnffR- 1 ) uPjZhnffR=2127508720; else uPjZhnffR=1903474961;if (uPjZhnffR == uPjZhnffR- 0 ) uPjZhnffR=565828453; else uPjZhnffR=1222624201;if (uPjZhnffR == uPjZhnffR- 0 ) uPjZhnffR=447217161; else uPjZhnffR=146237608;if (uPjZhnffR == uPjZhnffR- 1 ) uPjZhnffR=1732345642; else uPjZhnffR=1449101948;long mwFuZwMFI=670258708;if (mwFuZwMFI == mwFuZwMFI- 0 ) mwFuZwMFI=339544547; else mwFuZwMFI=992228917;if (mwFuZwMFI == mwFuZwMFI- 1 ) mwFuZwMFI=2093204745; else mwFuZwMFI=698549892;if (mwFuZwMFI == mwFuZwMFI- 0 ) mwFuZwMFI=1496598969; else mwFuZwMFI=442757665;if (mwFuZwMFI == mwFuZwMFI- 1 ) mwFuZwMFI=1520654652; else mwFuZwMFI=709873898;if (mwFuZwMFI == mwFuZwMFI- 1 ) mwFuZwMFI=460766688; else mwFuZwMFI=65208330;if (mwFuZwMFI == mwFuZwMFI- 1 ) mwFuZwMFI=912737594; else mwFuZwMFI=55746155;long eefTPaXeO=1127510558;if (eefTPaXeO == eefTPaXeO- 1 ) eefTPaXeO=861738206; else eefTPaXeO=972742424;if (eefTPaXeO == eefTPaXeO- 1 ) eefTPaXeO=303432439; else eefTPaXeO=1344105098;if (eefTPaXeO == eefTPaXeO- 0 ) eefTPaXeO=1534168428; else eefTPaXeO=1162891955;if (eefTPaXeO == eefTPaXeO- 0 ) eefTPaXeO=48860668; else eefTPaXeO=1986424433;if (eefTPaXeO == eefTPaXeO- 0 ) eefTPaXeO=1792052140; else eefTPaXeO=1655208544;if (eefTPaXeO == eefTPaXeO- 1 ) eefTPaXeO=295659723; else eefTPaXeO=302646991;int cDcYPVJRT=1223210188;if (cDcYPVJRT == cDcYPVJRT- 0 ) cDcYPVJRT=643493417; else cDcYPVJRT=1338615514;if (cDcYPVJRT == cDcYPVJRT- 1 ) cDcYPVJRT=1633384758; else cDcYPVJRT=395712425;if (cDcYPVJRT == cDcYPVJRT- 0 ) cDcYPVJRT=1825868687; else cDcYPVJRT=1266903508;if (cDcYPVJRT == cDcYPVJRT- 0 ) cDcYPVJRT=2077942374; else cDcYPVJRT=2139239303;if (cDcYPVJRT == cDcYPVJRT- 1 ) cDcYPVJRT=569580251; else cDcYPVJRT=1921186524;if (cDcYPVJRT == cDcYPVJRT- 0 ) cDcYPVJRT=1358904684; else cDcYPVJRT=2062300390;int NmlfEWLPo=1973837482;if (NmlfEWLPo == NmlfEWLPo- 0 ) NmlfEWLPo=545908334; else NmlfEWLPo=604835084;if (NmlfEWLPo == NmlfEWLPo- 1 ) NmlfEWLPo=587363742; else NmlfEWLPo=1642299;if (NmlfEWLPo == NmlfEWLPo- 0 ) NmlfEWLPo=1353364214; else NmlfEWLPo=1328733250;if (NmlfEWLPo == NmlfEWLPo- 0 ) NmlfEWLPo=1283573927; else NmlfEWLPo=1324136239;if (NmlfEWLPo == NmlfEWLPo- 1 ) NmlfEWLPo=943368249; else NmlfEWLPo=106780312;if (NmlfEWLPo == NmlfEWLPo- 0 ) NmlfEWLPo=1053981399; else NmlfEWLPo=1988874072; }
 NmlfEWLPoy::NmlfEWLPoy()
 { this->KAWobPRfIWVl("uYTYlIrhOKAWobPRfIWVlj", true, 147097942, 1218007661, 1128936260); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class FJCkRvLTwy
 { 
public: bool CigmDiOuP; double CigmDiOuPFJCkRvLTw; FJCkRvLTwy(); void ZUXEbSnhfDUd(string CigmDiOuPZUXEbSnhfDUd, bool DBgpegpcY, int lRmhEWrdq, float biuLIqbOB, long xCwbqYGKK);
 protected: bool CigmDiOuPo; double CigmDiOuPFJCkRvLTwf; void ZUXEbSnhfDUdu(string CigmDiOuPZUXEbSnhfDUdg, bool DBgpegpcYe, int lRmhEWrdqr, float biuLIqbOBw, long xCwbqYGKKn);
 private: bool CigmDiOuPDBgpegpcY; double CigmDiOuPbiuLIqbOBFJCkRvLTw;
 void ZUXEbSnhfDUdv(string DBgpegpcYZUXEbSnhfDUd, bool DBgpegpcYlRmhEWrdq, int lRmhEWrdqCigmDiOuP, float biuLIqbOBxCwbqYGKK, long xCwbqYGKKDBgpegpcY); };
 void FJCkRvLTwy::ZUXEbSnhfDUd(string CigmDiOuPZUXEbSnhfDUd, bool DBgpegpcY, int lRmhEWrdq, float biuLIqbOB, long xCwbqYGKK)
 { int pDtrpLBAu=59316404;if (pDtrpLBAu == pDtrpLBAu- 0 ) pDtrpLBAu=2085885007; else pDtrpLBAu=16308583;if (pDtrpLBAu == pDtrpLBAu- 1 ) pDtrpLBAu=83803592; else pDtrpLBAu=2053620923;if (pDtrpLBAu == pDtrpLBAu- 1 ) pDtrpLBAu=1553092814; else pDtrpLBAu=1167857441;if (pDtrpLBAu == pDtrpLBAu- 1 ) pDtrpLBAu=1206755049; else pDtrpLBAu=1910298808;if (pDtrpLBAu == pDtrpLBAu- 0 ) pDtrpLBAu=720942370; else pDtrpLBAu=1998941434;if (pDtrpLBAu == pDtrpLBAu- 1 ) pDtrpLBAu=1446194176; else pDtrpLBAu=1756628233;int sHPqREfZk=2072234329;if (sHPqREfZk == sHPqREfZk- 0 ) sHPqREfZk=905831069; else sHPqREfZk=247633241;if (sHPqREfZk == sHPqREfZk- 1 ) sHPqREfZk=1357630874; else sHPqREfZk=1329809632;if (sHPqREfZk == sHPqREfZk- 0 ) sHPqREfZk=1285610922; else sHPqREfZk=1888255933;if (sHPqREfZk == sHPqREfZk- 1 ) sHPqREfZk=220366525; else sHPqREfZk=240069309;if (sHPqREfZk == sHPqREfZk- 1 ) sHPqREfZk=1147149024; else sHPqREfZk=1169377671;if (sHPqREfZk == sHPqREfZk- 0 ) sHPqREfZk=1547268035; else sHPqREfZk=852852848;int kXHZbNpnF=796568952;if (kXHZbNpnF == kXHZbNpnF- 0 ) kXHZbNpnF=1585422128; else kXHZbNpnF=366248190;if (kXHZbNpnF == kXHZbNpnF- 1 ) kXHZbNpnF=1764620389; else kXHZbNpnF=571436292;if (kXHZbNpnF == kXHZbNpnF- 0 ) kXHZbNpnF=2034708592; else kXHZbNpnF=2048519008;if (kXHZbNpnF == kXHZbNpnF- 0 ) kXHZbNpnF=348567490; else kXHZbNpnF=1935085254;if (kXHZbNpnF == kXHZbNpnF- 1 ) kXHZbNpnF=418712877; else kXHZbNpnF=1883207067;if (kXHZbNpnF == kXHZbNpnF- 0 ) kXHZbNpnF=1731110479; else kXHZbNpnF=1712097078;int QPjCxuatu=1769150569;if (QPjCxuatu == QPjCxuatu- 0 ) QPjCxuatu=1343373268; else QPjCxuatu=405990037;if (QPjCxuatu == QPjCxuatu- 0 ) QPjCxuatu=297107450; else QPjCxuatu=480021750;if (QPjCxuatu == QPjCxuatu- 1 ) QPjCxuatu=1771934127; else QPjCxuatu=1977576010;if (QPjCxuatu == QPjCxuatu- 0 ) QPjCxuatu=921189129; else QPjCxuatu=197629074;if (QPjCxuatu == QPjCxuatu- 0 ) QPjCxuatu=1943425705; else QPjCxuatu=1991217930;if (QPjCxuatu == QPjCxuatu- 0 ) QPjCxuatu=906471899; else QPjCxuatu=383715143;long pOlDGpFMW=507649397;if (pOlDGpFMW == pOlDGpFMW- 1 ) pOlDGpFMW=2073318632; else pOlDGpFMW=649625224;if (pOlDGpFMW == pOlDGpFMW- 0 ) pOlDGpFMW=171206105; else pOlDGpFMW=1707524893;if (pOlDGpFMW == pOlDGpFMW- 0 ) pOlDGpFMW=1463021569; else pOlDGpFMW=858907144;if (pOlDGpFMW == pOlDGpFMW- 0 ) pOlDGpFMW=37525737; else pOlDGpFMW=1004795708;if (pOlDGpFMW == pOlDGpFMW- 0 ) pOlDGpFMW=2046549398; else pOlDGpFMW=1570029267;if (pOlDGpFMW == pOlDGpFMW- 0 ) pOlDGpFMW=911096755; else pOlDGpFMW=1549887502;double FJCkRvLTw=1142909488.3069834;if (FJCkRvLTw == FJCkRvLTw ) FJCkRvLTw=1064252568.9993469; else FJCkRvLTw=1925601113.6626369;if (FJCkRvLTw == FJCkRvLTw ) FJCkRvLTw=1656963227.3424526; else FJCkRvLTw=537987054.5635958;if (FJCkRvLTw == FJCkRvLTw ) FJCkRvLTw=2063669170.2571384; else FJCkRvLTw=1593084699.4722579;if (FJCkRvLTw == FJCkRvLTw ) FJCkRvLTw=1172118472.3519970; else FJCkRvLTw=1755329765.6453294;if (FJCkRvLTw == FJCkRvLTw ) FJCkRvLTw=1592542708.4785214; else FJCkRvLTw=1566991315.2551869;if (FJCkRvLTw == FJCkRvLTw ) FJCkRvLTw=775494234.7130573; else FJCkRvLTw=43490662.1271886; }
 FJCkRvLTwy::FJCkRvLTwy()
 { this->ZUXEbSnhfDUd("CigmDiOuPZUXEbSnhfDUdj", true, 1142047109, 2112335994, 167012201); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class tyrAxhPZUy
 { 
public: bool zhnwDHCYP; double zhnwDHCYPtyrAxhPZU; tyrAxhPZUy(); void KVLldWrMsOhX(string zhnwDHCYPKVLldWrMsOhX, bool rljdgPUKY, int NbtRJuNWA, float jrjACDrkb, long tAKMUcukC);
 protected: bool zhnwDHCYPo; double zhnwDHCYPtyrAxhPZUf; void KVLldWrMsOhXu(string zhnwDHCYPKVLldWrMsOhXg, bool rljdgPUKYe, int NbtRJuNWAr, float jrjACDrkbw, long tAKMUcukCn);
 private: bool zhnwDHCYPrljdgPUKY; double zhnwDHCYPjrjACDrkbtyrAxhPZU;
 void KVLldWrMsOhXv(string rljdgPUKYKVLldWrMsOhX, bool rljdgPUKYNbtRJuNWA, int NbtRJuNWAzhnwDHCYP, float jrjACDrkbtAKMUcukC, long tAKMUcukCrljdgPUKY); };
 void tyrAxhPZUy::KVLldWrMsOhX(string zhnwDHCYPKVLldWrMsOhX, bool rljdgPUKY, int NbtRJuNWA, float jrjACDrkb, long tAKMUcukC)
 { double YyQarGruc=860274995.2464933;if (YyQarGruc == YyQarGruc ) YyQarGruc=1773722960.0472663; else YyQarGruc=216944567.9163628;if (YyQarGruc == YyQarGruc ) YyQarGruc=328650393.8532341; else YyQarGruc=1697427674.7884296;if (YyQarGruc == YyQarGruc ) YyQarGruc=471946308.0601215; else YyQarGruc=1385156969.5032981;if (YyQarGruc == YyQarGruc ) YyQarGruc=868459896.7625804; else YyQarGruc=1056051782.0326924;if (YyQarGruc == YyQarGruc ) YyQarGruc=494650896.7084770; else YyQarGruc=225615515.6634134;if (YyQarGruc == YyQarGruc ) YyQarGruc=1938854430.5015711; else YyQarGruc=1538645556.2705021;float qXPuKqBZn=2128453097.9411676f;if (qXPuKqBZn - qXPuKqBZn> 0.00000001 ) qXPuKqBZn=1205327003.0890723f; else qXPuKqBZn=1482646618.4613544f;if (qXPuKqBZn - qXPuKqBZn> 0.00000001 ) qXPuKqBZn=503557892.3050422f; else qXPuKqBZn=1110377526.8958092f;if (qXPuKqBZn - qXPuKqBZn> 0.00000001 ) qXPuKqBZn=283483272.9782777f; else qXPuKqBZn=1237553900.3945771f;if (qXPuKqBZn - qXPuKqBZn> 0.00000001 ) qXPuKqBZn=1140919370.2671386f; else qXPuKqBZn=477481442.4712543f;if (qXPuKqBZn - qXPuKqBZn> 0.00000001 ) qXPuKqBZn=324360722.9437426f; else qXPuKqBZn=1669045876.9419880f;if (qXPuKqBZn - qXPuKqBZn> 0.00000001 ) qXPuKqBZn=1176921334.1268516f; else qXPuKqBZn=1157275432.4978265f;int gAIMWUbHm=1854851586;if (gAIMWUbHm == gAIMWUbHm- 0 ) gAIMWUbHm=1545236126; else gAIMWUbHm=1000535372;if (gAIMWUbHm == gAIMWUbHm- 1 ) gAIMWUbHm=777635298; else gAIMWUbHm=988900705;if (gAIMWUbHm == gAIMWUbHm- 1 ) gAIMWUbHm=219135523; else gAIMWUbHm=948516547;if (gAIMWUbHm == gAIMWUbHm- 1 ) gAIMWUbHm=1506176368; else gAIMWUbHm=1620841023;if (gAIMWUbHm == gAIMWUbHm- 0 ) gAIMWUbHm=1332678846; else gAIMWUbHm=1885180198;if (gAIMWUbHm == gAIMWUbHm- 1 ) gAIMWUbHm=2142801526; else gAIMWUbHm=9301771;float jYmuAoWaM=1472553574.7423734f;if (jYmuAoWaM - jYmuAoWaM> 0.00000001 ) jYmuAoWaM=2071346044.3588838f; else jYmuAoWaM=1683646643.5675994f;if (jYmuAoWaM - jYmuAoWaM> 0.00000001 ) jYmuAoWaM=744346612.8406335f; else jYmuAoWaM=964816813.7435967f;if (jYmuAoWaM - jYmuAoWaM> 0.00000001 ) jYmuAoWaM=419768630.3176919f; else jYmuAoWaM=1082164309.8441323f;if (jYmuAoWaM - jYmuAoWaM> 0.00000001 ) jYmuAoWaM=576791723.2413620f; else jYmuAoWaM=536169060.1275106f;if (jYmuAoWaM - jYmuAoWaM> 0.00000001 ) jYmuAoWaM=1223508844.2639823f; else jYmuAoWaM=1998652598.5091850f;if (jYmuAoWaM - jYmuAoWaM> 0.00000001 ) jYmuAoWaM=1373066952.0760126f; else jYmuAoWaM=950384079.1224472f;long zHnGSirDK=1924912877;if (zHnGSirDK == zHnGSirDK- 0 ) zHnGSirDK=439069712; else zHnGSirDK=84002844;if (zHnGSirDK == zHnGSirDK- 0 ) zHnGSirDK=2140893077; else zHnGSirDK=307551557;if (zHnGSirDK == zHnGSirDK- 0 ) zHnGSirDK=39621582; else zHnGSirDK=2037354536;if (zHnGSirDK == zHnGSirDK- 0 ) zHnGSirDK=1909317574; else zHnGSirDK=256810456;if (zHnGSirDK == zHnGSirDK- 0 ) zHnGSirDK=2123953897; else zHnGSirDK=1030200516;if (zHnGSirDK == zHnGSirDK- 1 ) zHnGSirDK=1925182327; else zHnGSirDK=545786721;float tyrAxhPZU=2131730826.9772477f;if (tyrAxhPZU - tyrAxhPZU> 0.00000001 ) tyrAxhPZU=520848896.9778086f; else tyrAxhPZU=1851851407.2312455f;if (tyrAxhPZU - tyrAxhPZU> 0.00000001 ) tyrAxhPZU=1233413035.9118033f; else tyrAxhPZU=1132063868.2936110f;if (tyrAxhPZU - tyrAxhPZU> 0.00000001 ) tyrAxhPZU=2120358701.4611039f; else tyrAxhPZU=969212637.4674013f;if (tyrAxhPZU - tyrAxhPZU> 0.00000001 ) tyrAxhPZU=1435082956.6380301f; else tyrAxhPZU=463071817.7744447f;if (tyrAxhPZU - tyrAxhPZU> 0.00000001 ) tyrAxhPZU=423743649.9429769f; else tyrAxhPZU=241466238.7025275f;if (tyrAxhPZU - tyrAxhPZU> 0.00000001 ) tyrAxhPZU=1912875508.5451317f; else tyrAxhPZU=367966572.6669108f; }
 tyrAxhPZUy::tyrAxhPZUy()
 { this->KVLldWrMsOhX("zhnwDHCYPKVLldWrMsOhXj", true, 1722933242, 555792289, 1412605388); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class RBgpZvXyby
 { 
public: bool ZLTsWwhkI; double ZLTsWwhkIRBgpZvXyb; RBgpZvXyby(); void UDVfJWqiAQRF(string ZLTsWwhkIUDVfJWqiAQRF, bool XxwyLJQZg, int PaXIGtkxl, float ZAyiYugLw, long rNsFGUBQK);
 protected: bool ZLTsWwhkIo; double ZLTsWwhkIRBgpZvXybf; void UDVfJWqiAQRFu(string ZLTsWwhkIUDVfJWqiAQRFg, bool XxwyLJQZge, int PaXIGtkxlr, float ZAyiYugLww, long rNsFGUBQKn);
 private: bool ZLTsWwhkIXxwyLJQZg; double ZLTsWwhkIZAyiYugLwRBgpZvXyb;
 void UDVfJWqiAQRFv(string XxwyLJQZgUDVfJWqiAQRF, bool XxwyLJQZgPaXIGtkxl, int PaXIGtkxlZLTsWwhkI, float ZAyiYugLwrNsFGUBQK, long rNsFGUBQKXxwyLJQZg); };
 void RBgpZvXyby::UDVfJWqiAQRF(string ZLTsWwhkIUDVfJWqiAQRF, bool XxwyLJQZg, int PaXIGtkxl, float ZAyiYugLw, long rNsFGUBQK)
 { long WTjFCNJqI=928227254;if (WTjFCNJqI == WTjFCNJqI- 0 ) WTjFCNJqI=1286828261; else WTjFCNJqI=1795319492;if (WTjFCNJqI == WTjFCNJqI- 0 ) WTjFCNJqI=2054504041; else WTjFCNJqI=316970869;if (WTjFCNJqI == WTjFCNJqI- 0 ) WTjFCNJqI=1271365034; else WTjFCNJqI=1537353399;if (WTjFCNJqI == WTjFCNJqI- 0 ) WTjFCNJqI=1095026977; else WTjFCNJqI=295575247;if (WTjFCNJqI == WTjFCNJqI- 0 ) WTjFCNJqI=363379627; else WTjFCNJqI=39127878;if (WTjFCNJqI == WTjFCNJqI- 1 ) WTjFCNJqI=1709194958; else WTjFCNJqI=65092884;double NcmGwQiVD=944841017.9504075;if (NcmGwQiVD == NcmGwQiVD ) NcmGwQiVD=1203520578.1731085; else NcmGwQiVD=1134717620.4006196;if (NcmGwQiVD == NcmGwQiVD ) NcmGwQiVD=516663984.7917354; else NcmGwQiVD=1299727124.7782614;if (NcmGwQiVD == NcmGwQiVD ) NcmGwQiVD=1724169790.2003243; else NcmGwQiVD=1787874383.1753390;if (NcmGwQiVD == NcmGwQiVD ) NcmGwQiVD=458769375.9390302; else NcmGwQiVD=1566560258.7087325;if (NcmGwQiVD == NcmGwQiVD ) NcmGwQiVD=278754784.1504713; else NcmGwQiVD=1038125339.0139547;if (NcmGwQiVD == NcmGwQiVD ) NcmGwQiVD=124546159.3751648; else NcmGwQiVD=1729032217.4033135;long LfzMnDIar=1113879645;if (LfzMnDIar == LfzMnDIar- 0 ) LfzMnDIar=124201922; else LfzMnDIar=2016895280;if (LfzMnDIar == LfzMnDIar- 0 ) LfzMnDIar=1148120860; else LfzMnDIar=1926562304;if (LfzMnDIar == LfzMnDIar- 1 ) LfzMnDIar=2095010676; else LfzMnDIar=1087858589;if (LfzMnDIar == LfzMnDIar- 0 ) LfzMnDIar=977569498; else LfzMnDIar=804651163;if (LfzMnDIar == LfzMnDIar- 1 ) LfzMnDIar=1933538337; else LfzMnDIar=131487696;if (LfzMnDIar == LfzMnDIar- 0 ) LfzMnDIar=972424904; else LfzMnDIar=105878398;long TGiIoDrZE=1724102390;if (TGiIoDrZE == TGiIoDrZE- 0 ) TGiIoDrZE=378514392; else TGiIoDrZE=17646689;if (TGiIoDrZE == TGiIoDrZE- 0 ) TGiIoDrZE=1550872101; else TGiIoDrZE=1924550337;if (TGiIoDrZE == TGiIoDrZE- 0 ) TGiIoDrZE=1834187302; else TGiIoDrZE=1698661311;if (TGiIoDrZE == TGiIoDrZE- 1 ) TGiIoDrZE=1351541111; else TGiIoDrZE=1646437525;if (TGiIoDrZE == TGiIoDrZE- 1 ) TGiIoDrZE=1336550117; else TGiIoDrZE=487943783;if (TGiIoDrZE == TGiIoDrZE- 1 ) TGiIoDrZE=38216085; else TGiIoDrZE=233239695;float IJszoyLif=779649125.5127157f;if (IJszoyLif - IJszoyLif> 0.00000001 ) IJszoyLif=1844881835.2677097f; else IJszoyLif=595315313.3684056f;if (IJszoyLif - IJszoyLif> 0.00000001 ) IJszoyLif=2088374609.5583763f; else IJszoyLif=2123908496.7084833f;if (IJszoyLif - IJszoyLif> 0.00000001 ) IJszoyLif=1741097292.4684621f; else IJszoyLif=350479630.6449492f;if (IJszoyLif - IJszoyLif> 0.00000001 ) IJszoyLif=997313988.5953031f; else IJszoyLif=115661989.6444046f;if (IJszoyLif - IJszoyLif> 0.00000001 ) IJszoyLif=157148122.7043649f; else IJszoyLif=1859496468.1104369f;if (IJszoyLif - IJszoyLif> 0.00000001 ) IJszoyLif=1513672434.2554823f; else IJszoyLif=1592682094.2318128f;double RBgpZvXyb=1491984861.5253272;if (RBgpZvXyb == RBgpZvXyb ) RBgpZvXyb=786785037.8514135; else RBgpZvXyb=547927416.3834129;if (RBgpZvXyb == RBgpZvXyb ) RBgpZvXyb=1350517825.7494996; else RBgpZvXyb=5236396.9994994;if (RBgpZvXyb == RBgpZvXyb ) RBgpZvXyb=180342048.2490796; else RBgpZvXyb=564663000.8485473;if (RBgpZvXyb == RBgpZvXyb ) RBgpZvXyb=1427175990.1573249; else RBgpZvXyb=573024258.9793970;if (RBgpZvXyb == RBgpZvXyb ) RBgpZvXyb=665354169.7212522; else RBgpZvXyb=1649166982.4454430;if (RBgpZvXyb == RBgpZvXyb ) RBgpZvXyb=590012187.0206248; else RBgpZvXyb=1607066893.4318663; }
 RBgpZvXyby::RBgpZvXyby()
 { this->UDVfJWqiAQRF("ZLTsWwhkIUDVfJWqiAQRFj", true, 1049642504, 744329803, 1539327570); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class IUJqFCGtCy
 { 
public: bool SzksiiBGA; double SzksiiBGAIUJqFCGtC; IUJqFCGtCy(); void VdEKxEwMFDrn(string SzksiiBGAVdEKxEwMFDrn, bool yqnrEfIxK, int hxlaMvwnA, float NAnOOIBJw, long lNAasRuNs);
 protected: bool SzksiiBGAo; double SzksiiBGAIUJqFCGtCf; void VdEKxEwMFDrnu(string SzksiiBGAVdEKxEwMFDrng, bool yqnrEfIxKe, int hxlaMvwnAr, float NAnOOIBJww, long lNAasRuNsn);
 private: bool SzksiiBGAyqnrEfIxK; double SzksiiBGANAnOOIBJwIUJqFCGtC;
 void VdEKxEwMFDrnv(string yqnrEfIxKVdEKxEwMFDrn, bool yqnrEfIxKhxlaMvwnA, int hxlaMvwnASzksiiBGA, float NAnOOIBJwlNAasRuNs, long lNAasRuNsyqnrEfIxK); };
 void IUJqFCGtCy::VdEKxEwMFDrn(string SzksiiBGAVdEKxEwMFDrn, bool yqnrEfIxK, int hxlaMvwnA, float NAnOOIBJw, long lNAasRuNs)
 { float LWqmdVQnR=883782838.8665685f;if (LWqmdVQnR - LWqmdVQnR> 0.00000001 ) LWqmdVQnR=1736280733.3403620f; else LWqmdVQnR=1452636995.9327498f;if (LWqmdVQnR - LWqmdVQnR> 0.00000001 ) LWqmdVQnR=926534654.3094894f; else LWqmdVQnR=1832169906.8586921f;if (LWqmdVQnR - LWqmdVQnR> 0.00000001 ) LWqmdVQnR=1209095732.2946971f; else LWqmdVQnR=1785092213.3030081f;if (LWqmdVQnR - LWqmdVQnR> 0.00000001 ) LWqmdVQnR=1661038699.4718186f; else LWqmdVQnR=1436716561.7818026f;if (LWqmdVQnR - LWqmdVQnR> 0.00000001 ) LWqmdVQnR=540330631.0387198f; else LWqmdVQnR=805484808.4815370f;if (LWqmdVQnR - LWqmdVQnR> 0.00000001 ) LWqmdVQnR=437936400.1759134f; else LWqmdVQnR=1699883322.8799466f;double QnxcaOjZP=1193834108.9578299;if (QnxcaOjZP == QnxcaOjZP ) QnxcaOjZP=1502655227.3960800; else QnxcaOjZP=1870648468.4959443;if (QnxcaOjZP == QnxcaOjZP ) QnxcaOjZP=1383199150.1854097; else QnxcaOjZP=1547661667.3678585;if (QnxcaOjZP == QnxcaOjZP ) QnxcaOjZP=1439676173.4189528; else QnxcaOjZP=1676733176.3204848;if (QnxcaOjZP == QnxcaOjZP ) QnxcaOjZP=2101885687.2279398; else QnxcaOjZP=733297966.7252030;if (QnxcaOjZP == QnxcaOjZP ) QnxcaOjZP=1164832212.3923260; else QnxcaOjZP=1411609451.9819369;if (QnxcaOjZP == QnxcaOjZP ) QnxcaOjZP=1691208070.6613601; else QnxcaOjZP=322511.5093978;long PgYvpzRqH=1164974432;if (PgYvpzRqH == PgYvpzRqH- 0 ) PgYvpzRqH=658802538; else PgYvpzRqH=1136467526;if (PgYvpzRqH == PgYvpzRqH- 0 ) PgYvpzRqH=1953219799; else PgYvpzRqH=384075397;if (PgYvpzRqH == PgYvpzRqH- 0 ) PgYvpzRqH=1084109367; else PgYvpzRqH=1733711454;if (PgYvpzRqH == PgYvpzRqH- 1 ) PgYvpzRqH=2029457002; else PgYvpzRqH=327168948;if (PgYvpzRqH == PgYvpzRqH- 1 ) PgYvpzRqH=1679186016; else PgYvpzRqH=212219056;if (PgYvpzRqH == PgYvpzRqH- 1 ) PgYvpzRqH=2009034083; else PgYvpzRqH=140385334;int staMpGItY=189324970;if (staMpGItY == staMpGItY- 1 ) staMpGItY=1197417567; else staMpGItY=1391600024;if (staMpGItY == staMpGItY- 1 ) staMpGItY=1300422902; else staMpGItY=1742298646;if (staMpGItY == staMpGItY- 0 ) staMpGItY=335408798; else staMpGItY=926549008;if (staMpGItY == staMpGItY- 0 ) staMpGItY=1591590312; else staMpGItY=59547557;if (staMpGItY == staMpGItY- 0 ) staMpGItY=1498234955; else staMpGItY=193236688;if (staMpGItY == staMpGItY- 0 ) staMpGItY=667337694; else staMpGItY=1944969928;int AVqvUsEpQ=1967859857;if (AVqvUsEpQ == AVqvUsEpQ- 1 ) AVqvUsEpQ=921292069; else AVqvUsEpQ=1420445615;if (AVqvUsEpQ == AVqvUsEpQ- 0 ) AVqvUsEpQ=1041080784; else AVqvUsEpQ=228213089;if (AVqvUsEpQ == AVqvUsEpQ- 1 ) AVqvUsEpQ=657992447; else AVqvUsEpQ=1621048763;if (AVqvUsEpQ == AVqvUsEpQ- 0 ) AVqvUsEpQ=109724741; else AVqvUsEpQ=1916427420;if (AVqvUsEpQ == AVqvUsEpQ- 1 ) AVqvUsEpQ=1988675113; else AVqvUsEpQ=1056030202;if (AVqvUsEpQ == AVqvUsEpQ- 0 ) AVqvUsEpQ=2015959298; else AVqvUsEpQ=1227457117;double IUJqFCGtC=1923360279.8007823;if (IUJqFCGtC == IUJqFCGtC ) IUJqFCGtC=296568622.7668075; else IUJqFCGtC=1501883100.8221470;if (IUJqFCGtC == IUJqFCGtC ) IUJqFCGtC=950388591.1620117; else IUJqFCGtC=1232941184.4110420;if (IUJqFCGtC == IUJqFCGtC ) IUJqFCGtC=1567015166.4191376; else IUJqFCGtC=289377740.4982664;if (IUJqFCGtC == IUJqFCGtC ) IUJqFCGtC=829565634.8217388; else IUJqFCGtC=1879737177.4888164;if (IUJqFCGtC == IUJqFCGtC ) IUJqFCGtC=1692360861.5696554; else IUJqFCGtC=1893672242.2302058;if (IUJqFCGtC == IUJqFCGtC ) IUJqFCGtC=1033324089.8586637; else IUJqFCGtC=890872679.0142530; }
 IUJqFCGtCy::IUJqFCGtCy()
 { this->VdEKxEwMFDrn("SzksiiBGAVdEKxEwMFDrnj", true, 1066373760, 84487074, 233284805); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class HGOIPGtWQy
 { 
public: bool WeXqBAJbY; double WeXqBAJbYHGOIPGtWQ; HGOIPGtWQy(); void WPVIJAzghCEM(string WeXqBAJbYWPVIJAzghCEM, bool AqlqsAFGu, int qiGRRhCZX, float hwOYMioND, long mlMcZzmnQ);
 protected: bool WeXqBAJbYo; double WeXqBAJbYHGOIPGtWQf; void WPVIJAzghCEMu(string WeXqBAJbYWPVIJAzghCEMg, bool AqlqsAFGue, int qiGRRhCZXr, float hwOYMioNDw, long mlMcZzmnQn);
 private: bool WeXqBAJbYAqlqsAFGu; double WeXqBAJbYhwOYMioNDHGOIPGtWQ;
 void WPVIJAzghCEMv(string AqlqsAFGuWPVIJAzghCEM, bool AqlqsAFGuqiGRRhCZX, int qiGRRhCZXWeXqBAJbY, float hwOYMioNDmlMcZzmnQ, long mlMcZzmnQAqlqsAFGu); };
 void HGOIPGtWQy::WPVIJAzghCEM(string WeXqBAJbYWPVIJAzghCEM, bool AqlqsAFGu, int qiGRRhCZX, float hwOYMioND, long mlMcZzmnQ)
 { long SmzVJVERn=726941747;if (SmzVJVERn == SmzVJVERn- 1 ) SmzVJVERn=974596729; else SmzVJVERn=1336380741;if (SmzVJVERn == SmzVJVERn- 0 ) SmzVJVERn=1239709526; else SmzVJVERn=1948057491;if (SmzVJVERn == SmzVJVERn- 1 ) SmzVJVERn=285138402; else SmzVJVERn=2128373411;if (SmzVJVERn == SmzVJVERn- 1 ) SmzVJVERn=419011415; else SmzVJVERn=184508430;if (SmzVJVERn == SmzVJVERn- 0 ) SmzVJVERn=1025503902; else SmzVJVERn=377202658;if (SmzVJVERn == SmzVJVERn- 1 ) SmzVJVERn=272562403; else SmzVJVERn=565923;double ifrbpYRDC=727948699.4107981;if (ifrbpYRDC == ifrbpYRDC ) ifrbpYRDC=2102730950.4859417; else ifrbpYRDC=1542955515.6242967;if (ifrbpYRDC == ifrbpYRDC ) ifrbpYRDC=955679713.5785319; else ifrbpYRDC=1854181155.3241011;if (ifrbpYRDC == ifrbpYRDC ) ifrbpYRDC=1577486068.4192691; else ifrbpYRDC=904130279.6843521;if (ifrbpYRDC == ifrbpYRDC ) ifrbpYRDC=1775300994.9978539; else ifrbpYRDC=125178213.5327831;if (ifrbpYRDC == ifrbpYRDC ) ifrbpYRDC=835109359.6194062; else ifrbpYRDC=642014529.2604760;if (ifrbpYRDC == ifrbpYRDC ) ifrbpYRDC=1581939773.9529084; else ifrbpYRDC=266113608.4736830;int gepeyyiav=2008135947;if (gepeyyiav == gepeyyiav- 0 ) gepeyyiav=1001554327; else gepeyyiav=506735757;if (gepeyyiav == gepeyyiav- 0 ) gepeyyiav=1045448468; else gepeyyiav=656407260;if (gepeyyiav == gepeyyiav- 0 ) gepeyyiav=1481398890; else gepeyyiav=738591495;if (gepeyyiav == gepeyyiav- 1 ) gepeyyiav=366871586; else gepeyyiav=188394408;if (gepeyyiav == gepeyyiav- 1 ) gepeyyiav=569621883; else gepeyyiav=2127374278;if (gepeyyiav == gepeyyiav- 0 ) gepeyyiav=957661775; else gepeyyiav=112822579;long SxkSdlGHS=1163188608;if (SxkSdlGHS == SxkSdlGHS- 0 ) SxkSdlGHS=233088275; else SxkSdlGHS=1510539378;if (SxkSdlGHS == SxkSdlGHS- 1 ) SxkSdlGHS=2140482662; else SxkSdlGHS=418061740;if (SxkSdlGHS == SxkSdlGHS- 0 ) SxkSdlGHS=218400442; else SxkSdlGHS=913311053;if (SxkSdlGHS == SxkSdlGHS- 0 ) SxkSdlGHS=1296939326; else SxkSdlGHS=70466450;if (SxkSdlGHS == SxkSdlGHS- 0 ) SxkSdlGHS=1708563394; else SxkSdlGHS=1114531313;if (SxkSdlGHS == SxkSdlGHS- 0 ) SxkSdlGHS=1112948132; else SxkSdlGHS=1790607520;double MiDcOydHy=1194577773.1804521;if (MiDcOydHy == MiDcOydHy ) MiDcOydHy=1963267708.8217107; else MiDcOydHy=411910103.3415679;if (MiDcOydHy == MiDcOydHy ) MiDcOydHy=1146495243.2457874; else MiDcOydHy=1062916277.5603731;if (MiDcOydHy == MiDcOydHy ) MiDcOydHy=1085274341.2799997; else MiDcOydHy=1554094659.8197907;if (MiDcOydHy == MiDcOydHy ) MiDcOydHy=1394033456.3078189; else MiDcOydHy=1364139455.4578674;if (MiDcOydHy == MiDcOydHy ) MiDcOydHy=1176083929.7244762; else MiDcOydHy=767285305.8278934;if (MiDcOydHy == MiDcOydHy ) MiDcOydHy=1284559272.4700773; else MiDcOydHy=1597595437.6367638;float HGOIPGtWQ=1278373427.9866672f;if (HGOIPGtWQ - HGOIPGtWQ> 0.00000001 ) HGOIPGtWQ=1197683226.6611704f; else HGOIPGtWQ=418751165.4732276f;if (HGOIPGtWQ - HGOIPGtWQ> 0.00000001 ) HGOIPGtWQ=33025333.4721583f; else HGOIPGtWQ=520210914.5718290f;if (HGOIPGtWQ - HGOIPGtWQ> 0.00000001 ) HGOIPGtWQ=1985410761.0800463f; else HGOIPGtWQ=143356857.8439397f;if (HGOIPGtWQ - HGOIPGtWQ> 0.00000001 ) HGOIPGtWQ=1789735505.4450575f; else HGOIPGtWQ=88243274.2461901f;if (HGOIPGtWQ - HGOIPGtWQ> 0.00000001 ) HGOIPGtWQ=1357280078.0145255f; else HGOIPGtWQ=974982018.0338146f;if (HGOIPGtWQ - HGOIPGtWQ> 0.00000001 ) HGOIPGtWQ=1095327513.3033072f; else HGOIPGtWQ=366867577.3697259f; }
 HGOIPGtWQy::HGOIPGtWQy()
 { this->WPVIJAzghCEM("WeXqBAJbYWPVIJAzghCEMj", true, 1773127010, 723747713, 1789444417); }
#pragma optimize("", off)
 // <delete/>

