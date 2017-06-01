#include "memes.h"

bool Memes::showWindow = false;

void Memes::RenderWindow()
{
	if(!Memes::showWindow)
		return;

	static int page = 0;
	ImGui::SetNextWindowSize(ImVec2(700, 500), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Hitler did nothing wrong", &Memes::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		const char* tabs[] = {
				"pNazi",
				"weeb stuff",
		};

		for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
		{
			int distance = i == page ? 0 : i > page ? i - page : page - i;

			ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(
					Settings::UI::mainColor.Color().Value.x - (distance * 0.035f),
					Settings::UI::mainColor.Color().Value.y - (distance * 0.035f),
					Settings::UI::mainColor.Color().Value.z - (distance * 0.035f),
					Settings::UI::mainColor.Color().Value.w
			);

			if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
				page = i;

			ImGui::GetStyle().Colors[ImGuiCol_Button] = Settings::UI::mainColor.Color();

			if (i < IM_ARRAYSIZE(tabs) - 1)
				ImGui::SameLine();
		}

		ImGui::Separator();

		switch (page)
		{
			case 0:
				//pNazi
				ImGui::Checkbox("Enable Quality ESP", &Settings::Memes::pNazi::ESP::enabled);
				SetTooltip("Turn On/Off the Nazi Visuals");

				ImGui::Separator();

				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Enemies", &Settings::Memes::pNazi::ESP::enemies);
					ImGui::Checkbox("Legit", &Settings::Memes::pNazi::ESP::legit);
					SetTooltip("Only show visible enemies");
				}
				ImGui::NextColumn();
				{
					ImGui::Checkbox("Allies", &Settings::Memes::pNazi::ESP::allies);
				}
				ImGui::Columns(1);

				ImGui::Separator();
				ImGui::Text("Crosshair");
				ImGui::Separator();

				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Enabled", &Settings::Memes::pNazi::Crosshair::enabled);
					SetTooltip("Enables the valve developer crosshair");
					ImGui::Checkbox("Disable RC", &Settings::Memes::pNazi::Crosshair::disablerc);
					SetTooltip("Disables the Recoil Crosshair while the Nazi crosshair is active");
				}
				ImGui::NextColumn();
				{
					ImGui::Checkbox("Spinning", &Settings::Memes::pNazi::Crosshair::spinning);
					ImGui::PushItemWidth(-1);
					ImGui::SliderInt("##NAZISPEED", &Settings::Memes::pNazi::Crosshair::speed, 1, 10, "Speed: %0.f");
					SetTooltip("Change the speed the Crosshair rotates");
					ImGui::PopItemWidth();
				}
				//pNazi End
				break;
			case 1:
				break;
		}

		ImGui::End();
	}
}