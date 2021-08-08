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

	int tempValue = 1587; // Will be replaced with peak MMR for specific game mode
	if (ImGui::InputInt("3v3", &standardMMR, 0, 10000))
	{
		// Set Value
	}
	if (ImGui::InputInt("2v2", &doublesMMR, 0, 10000))
	{
		// Set Value
	}
	if (ImGui::InputInt("1v1", &duelMMR, 0, 10000))
	{
		// Set Value
	}
	ImGui::Separator();
	ImGui::TextUnformatted("Extra Modes");
	if (ImGui::InputInt("Rumble", &rumbleMMR, 0, 10000))
	{
		// Set Value
	}
	if (ImGui::InputInt("Snow Day", &snowdayMMR, 0, 10000))
	{
		// Set Value
	}
	if (ImGui::InputInt("Dropshot", &dropshotMMR, 0, 10000))
	{
		// Set Value
	}
	if (ImGui::InputInt("Hoops", &hoopsMMR, 0, 10000))
	{
		// Set Value
	}
	ImGui::Separator();
	if (ImGui::InputInt("Casual", &casualMMR, 0, 10000))
	{
		// Set Value
	}
	ImGui::Separator();
	ImGui::TextUnformatted("Developed by @spragouu");
}