#include "atgui.h"

bool UI::isVisible = false;
bool Settings::Watermark::enabled = true;
bool Settings::Watermark::enableInGame = true;
int Settings::Watermark::x = 1;
int Settings::Watermark::y = 1;
char* Settings::Watermark::text = strdup("pAste");
ColorVar Settings::Watermark::color = ImColor(255, 255, 255, 255);
bool Settings::BombTimer::enabled = true;
int Settings::BombTimer::x = 1;
int Settings::BombTimer::y = 4;

bool Settings::ScreenshotCleaner::enabled = false;

ColorVar Settings::UI::mainColor = ImColor(40, 40, 40, 180);
ColorVar Settings::UI::bodyColor = ImColor(0, 0, 2, 220);
ColorVar Settings::UI::fontColor = ImColor(0, 200, 255, 255);

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

void SetupMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8 * 2.0f, 4 * 2.0f));

		ImGui::Selectable("Main Window", &Main::showWindow, 0, ImVec2(ImGui::CalcTextSize("Main Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		if (ModSupport::current_mod != ModType::CSCO)
		{
			ImGui::Selectable("Skin & Model Changer Window", &SkinModelChanger::showWindow, 0, ImVec2(ImGui::CalcTextSize("Skin & Model Changer Window", NULL, true).x, 0.0f));
			ImGui::SameLine();
		}

		ImGui::Selectable("Config Window", &Configs::showWindow, 0, ImVec2(ImGui::CalcTextSize("Config Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Spectators Window", &Settings::ShowSpectators::enabled, 0, ImVec2(ImGui::CalcTextSize("Spectators Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Colors Window", &Colors::showWindow, 0, ImVec2(ImGui::CalcTextSize("Colors Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Player List Window", &PlayerList::showWindow, 0, ImVec2(ImGui::CalcTextSize("Player List Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Walk Bot Window", &Walk::showWindow, 0, ImVec2(ImGui::CalcTextSize("Walk Bot Window", NULL, true).x, 0.0f));

		ImGui::PopStyleVar();
		ImGui::EndMainMenuBar();
	}
}

void UI::SwapWindow()
{
	if (UI::isVisible)
		return;

	if (Settings::BombTimer::enabled)
	{
		ESP::DisplayBombInfo(Settings::BombTimer::x, Settings::BombTimer::y);
	}

	if (Settings::Watermark::enabled)
	{
		if (engine->IsInGame() && !Settings::Watermark::enableInGame)
		{
			return;
		}
		else
		{
			float xcord = Settings::Watermark::x * 4.f;
			float ycord = Settings::Watermark::y * 4.f;
			Draw::ImDrawText(ImVec2(xcord, ycord), Settings::Watermark::color.Color(), Settings::Watermark::text, NULL, 0.0f, NULL, ImFontFlags_Outline);
		}
	}
}


void UI::SetVisible(bool visible)
{
	UI::isVisible = visible;
	cvar->FindVar("cl_mouseenable")->SetValue(!UI::isVisible);
}

void UI::SetupWindows()
{
	if (UI::isVisible)
	{
		SetupMainMenuBar();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(960, 645));
			Main::RenderWindow();
		ImGui::PopStyleVar();

		if (ModSupport::current_mod != ModType::CSCO)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1050, 645));
				SkinModelChanger::RenderWindow();
			ImGui::PopStyleVar();
		}

		Configs::RenderWindow();
		Colors::RenderWindow();
		PlayerList::RenderWindow();
		Walk::RenderWindow();
	}

	ShowSpectators::RenderWindow();
	Radar::RenderWindow();
}
