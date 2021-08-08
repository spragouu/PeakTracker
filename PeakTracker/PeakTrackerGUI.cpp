#include "pch.h"
#include "PeakTracker.h"

void PeakTracker::SetImGuiContext(uintptr_t ctx) 
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

std::string PeakTracker::GetPluginName() 
{
	return "PeakTracker";
}

void PeakTracker::RenderSettings() 
{
	int standardMMR = cvarManager->getCvar("standardMMR").getIntValue();
	int doublesMMR = cvarManager->getCvar("doublesMMR").getIntValue();
	int duelMMR = cvarManager->getCvar("duelMMR").getIntValue();
	int rumbleMMR = cvarManager->getCvar("rumbleMMR").getIntValue();
	int dropshotMMR = cvarManager->getCvar("dropshotMMR").getIntValue();
	int hoopsMMR = cvarManager->getCvar("hoopsMMR").getIntValue();
	int snowdayMMR = cvarManager->getCvar("snowdayMMR").getIntValue();
	int casualMMR = cvarManager->getCvar("casualMMR").getIntValue();

	ImGui::TextUnformatted("Standard Modes");
	if (ImGui::InputInt("3v3", &standardMMR, 0, 10000))
	{
		cvarManager->getCvar("standardMMR").setValue(standardMMR);
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip("Manually update 3v3 peak");
	}

	if (ImGui::InputInt("2v2", &doublesMMR, 0, 10000))
	{
		cvarManager->getCvar("doublesMMR").setValue(doublesMMR);
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip("Manually update 2v2 peak");
	}

	if (ImGui::InputInt("1v1", &duelMMR, 0, 10000))
	{
		cvarManager->getCvar("duelMMR").setValue(duelMMR);
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip("Manually update 1v1 peak");
	}

	ImGui::Separator();
	ImGui::TextUnformatted("Extra Modes");
	if (ImGui::InputInt("Rumble", &rumbleMMR, 0, 10000))
	{
		cvarManager->getCvar("rumbleMMR").setValue(rumbleMMR);
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip("Manually update Rumble peak");
	}

	if (ImGui::InputInt("Snow Day", &snowdayMMR, 0, 10000))
	{
		cvarManager->getCvar("snowdayMMR").setValue(snowdayMMR);
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip("Manually update Snow Day peak");
	}

	if (ImGui::InputInt("Dropshot", &dropshotMMR, 0, 10000))
	{
		cvarManager->getCvar("dropshotMMR").setValue(dropshotMMR);
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip("Manually update Dropshot peak");
	}

	if (ImGui::InputInt("Hoops", &hoopsMMR, 0, 10000))
	{
		cvarManager->getCvar("hoopsMMR").setValue(hoopsMMR);
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip("Manually update Hoops peak");
	}

	ImGui::Separator();
	if (ImGui::InputInt("Casual", &casualMMR, 0, 10000))
	{
		cvarManager->getCvar("casualMMR").setValue(casualMMR);
	}
	ImGui::Separator();
	ImGui::TextUnformatted("Developed by @spragouu");
}