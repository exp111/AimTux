#include "pnazi.h"

bool Settings::Memes::pNazi::ESP::enabled = false;
bool Settings::Memes::pNazi::ESP::enemies = true;
bool Settings::Memes::pNazi::ESP::allies = false;
bool Settings::Memes::pNazi::ESP::legit = false;
bool Settings::Memes::pNazi::Crosshair::enabled = false;
bool Settings::Memes::pNazi::Crosshair::disablerc = false;
bool Settings::Memes::pNazi::Crosshair::spinning = true;
int Settings::Memes::pNazi::Crosshair::speed = 1;

int Drehwinkel = 90;

float BOG_TO_GRD(float BOG) {
	return (180 / M_PI) * BOG;
}
 
float GRD_TO_BOG(float GRD) {
	return (M_PI / 180) * GRD;
}

void pNazi::DrawStar(int x,int y)
{
	//uplooking
	Draw::Line(x+20, y, x-20, y, Color(0, 0, 255, 255));
	Draw::Line(x+20, y, x, y-30, Color(0, 0, 255, 255));
	Draw::Line(x-20, y, x, y-30, Color(0, 0, 255, 255));
	//downlooking
	Draw::Line(x+20, y-22.5, x-20, y-22.5, Color(0, 0, 255, 255));
	Draw::Line(x+20, y-22.5, x, y+7.5, Color(0, 0, 255, 255));
	Draw::Line(x-20, y-22.5, x, y+7.5, Color(0, 0, 255, 255));
}

void pNazi::DrawSwastika(int x, int y)
{
	//down
	Draw::Line(x, y, x, y+20, Color(255, 0, 0, 255));
	Draw::Line(x, y+20, x-20, y+20, Color(255, 0, 0, 255));
	//left
	Draw::Line(x, y, x+20, y, Color(255, 0, 0, 255));
	Draw::Line(x+20, y, x+20, y+20, Color(255, 0, 0, 255));
	//top
	Draw::Line(x, y, x, y-20, Color(255, 0, 0, 255));
	Draw::Line(x, y-20, x+20, y-20, Color(255, 0, 0, 255));
	//right
	Draw::Line(x, y, x-20, y, Color(255, 0, 0, 255));
	Draw::Line(x-20, y, x-20, y-20, Color(255, 0, 0, 255));
}

void pNazi::DrawRotatingSwastika(int x, int y)
{
	int ax = (y / 30);
	float gamma = atan(ax / ax);
 
	int Drehungswinkel = Drehwinkel;

	if (Settings::Memes::pNazi::Crosshair::spinning)
	{
		if (Drehwinkel > 89)
			Drehwinkel = 0;

		Drehwinkel = Drehwinkel + Settings::Memes::pNazi::Crosshair::speed;
 	}

	int i = 0;
	while (i < 4)
	{
		std::vector <int> p;
		p.push_back(ax * sin(GRD_TO_BOG(Drehungswinkel + (i * 90))));									//p[0]		p0_A.x
		p.push_back(ax * cos(GRD_TO_BOG(Drehungswinkel + (i * 90))));									//p[1]		p0_A.y
		p.push_back((ax / cos(gamma)) * sin(GRD_TO_BOG(Drehungswinkel + (i * 90) + BOG_TO_GRD(gamma))));	//p[2]		p0_B.x
		p.push_back((ax / cos(gamma)) * cos(GRD_TO_BOG(Drehungswinkel + (i * 90) + BOG_TO_GRD(gamma))));	//p[3]		p0_B.y
		
		Draw::Line(x, y, x + p[0], y - p[1], Color(255, 0, 0, 255));
		Draw::Line(x + p[0], y - p[1], x + p[2], y - p[3], Color(255, 0, 0, 255));
 
		i++;
	}
}

void pNazi::Crosshair()
{
	//crosshair
	cvar->FindVar("crosshair")->SetValue(0);

	//Middle POINT
	int Screenx, Screeny; engine->GetScreenSize(Screenx, Screeny);
	int x = (int)(Screenx / 2); int y = (int)(Screeny / 2);
	
	DrawRotatingSwastika(x,y);
}

void pNazi::NaziESP()
{
	//swastika+jews
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	for (int a = 1; a < entityList->GetHighestEntityIndex(); a++)
	{
		C_BaseEntity* entity = entityList->GetClientEntity(a);
		if (!entity)
			continue;

		ClientClass* client = entity->GetClientClass();

		if (client->m_ClassID == EClassIds::CCSPlayer)
		{
			C_BasePlayer* player = (C_BasePlayer*) entity;

			if (player == localplayer
				|| player->GetDormant()
				|| !player->GetAlive())
				continue;

			IEngineClient::player_info_t playerInfo;
			if (engine->GetPlayerInfo(a, &playerInfo)) 
			{
				if (!localplayer)
				return;

				//VISIBLE CHECK
				bool bIsVisible = false;
				if (Settings::Memes::pNazi::ESP::legit)
				{
					bIsVisible = Entity::IsVisible(player, Bone::BONE_HEAD, 180.f, false);
					if (!bIsVisible)
					continue;
				}

				int x, y, w, h;
				if (!ESP::GetBox(player, x, y, w, h))
					continue;

				int midx = x+(w/2);

				//jews
				if (player->GetTeam() != localplayer->GetTeam() && Settings::Memes::pNazi::ESP::enemies)
					DrawStar(midx,y);

				//nazis
				if (player->GetTeam() == localplayer->GetTeam() && Settings::Memes::pNazi::ESP::allies)
					DrawSwastika(midx,y);
			}
		}
	}
}



void pNazi::Paint()
{
	if (!Settings::Memes::pNazi::Crosshair::enabled)
		cvar->FindVar("crosshair")->SetValue(1);

	if (!engine->IsInGame())
		return;

	//ESP
	if (Settings::Memes::pNazi::ESP::enabled)
	{
		if (Settings::Memes::pNazi::ESP::enemies || Settings::Memes::pNazi::ESP::allies)
			NaziESP();
	}
	
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	//crosshair
	if (Settings::Memes::pNazi::Crosshair::enabled) {
		Crosshair();
	}
}