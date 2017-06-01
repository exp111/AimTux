#pragma once

#include <math.h>
#include "../settings.h"
#include "../SDK/SDK.h"
#include "../Hooks/hooks.h"
#include "../Utils/draw.h"
#include "../interfaces.h"
#include "../Utils/pstring.h"
#include "../Utils/entity.h"

namespace pNazi
{
	void DrawStar(int x, int y);
	void DrawSwastika(int x, int y);
	void DrawRotatingSwastika(int x, int y);
	void Crosshair();
	void NaziESP();
	void Paint();
};