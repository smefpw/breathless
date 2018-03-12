#pragma once
#include "Hooks.h"

class CFakeLag
{
public:
	void run(CUserCmd* m_pcmd, bool& send_packet);
};
extern CFakeLag fakelag;