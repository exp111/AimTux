#include "themes.h"

bool Themes::showWindow = false;

const char* ThemesList[] = { "pAste", "AimTux", "Antario" };

void Themes::RenderWindow()
{
	if (!Themes::showWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(320, 240), ImGuiSetCond_Always);
	if (ImGui::Begin("Themes", &Walk::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		ImGui::PushItemWidth(-1);
		ImGui::Combo("##THEME", (int*)&Settings::UI::Theme, ThemesList, IM_ARRAYSIZE(ThemesList));
		ImGui::PopItemWidth();
		ImGui::End();
	}
}