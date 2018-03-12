#pragma once

#include <vector>

#include "Entities.h"
#include "Interfaces.h"

class cbullet_tracer
{
public:
	void log(IGameEvent * event);
	void render();
private:
	class cbullet_tracer_info
	{
	public:
		cbullet_tracer_info(Vector src, Vector dst, float time, Color color)
		{
			this->src = src;
			this->dst = dst;
			this->time = time;
			this->color = color;
		}

		Vector src, dst;
		float time;
		Color color;
	};

	std::vector<cbullet_tracer_info> logs;
};