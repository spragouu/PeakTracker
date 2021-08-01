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
	ImGui::TextUnformatted("Standard Modes");

	int tempValue = 1587; // Will be replaced with peak MMR for specific game mode
	if (ImGui::InputInt("3v3", &tempValue, 0, 10000))
	{
		// Set Value
	}
	if (ImGui::InputInt("2v2", &tempValue, 0, 10000))
	{
		// Set Value
	}
	if (ImGui::InputInt("1v1", &tempValue, 0, 10000))
	{
		// Set Value
	}
	ImGui::Separator();
	ImGui::TextUnformatted("Extra Modes");
	if (ImGui::InputInt("Rumble", &tempValue, 0, 10000))
	{
		// Set Value
	}
	if (ImGui::InputInt("Snow Day", &tempValue, 0, 10000))
	{
		// Set Value
	}
	if (ImGui::InputInt("Dropshot", &tempValue, 0, 10000))
	{
		// Set Value
	}
	if (ImGui::InputInt("Hoops", &tempValue, 0, 10000))
	{
		// Set Value
	}
	ImGui::Separator();
	ImGui::TextUnformatted("Developed by @spragouu");
}