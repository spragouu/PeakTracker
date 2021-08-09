#include "pch.h"
#include "PeakTracker.h"
#include <fstream>
#include <direct.h>


BAKKESMOD_PLUGIN(PeakTracker, "Track Peak MMR across various game-modes", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void PeakTracker::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("PeakTracker loaded!");

	// Hooks
	gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", bind(&PeakTracker::GameStart, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", bind(&PeakTracker::GameEnd, this, std::placeholders::_1));

	// Cvars
	cvarManager->registerCvar("standardMMR", "0", "3v3 MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("doublesMMR", "0", "2v2 MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("duelMMR", "0", "1v1 MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("rumbleMMR", "0", "Rumble MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("dropshotMMR", "0", "Dropshot MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("hoopsMMR", "0", "Hoops MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("snowdayMMR", "0", "Snowday MMR", true, true, 0, true, 10000, true);

	LoadExistingMMR();
}

void PeakTracker::onUnload(){}

void PeakTracker::GameStart(std::string eventName)
{
	if (!gameWrapper->IsInOnlineGame()) return;

	MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
	int currentPlaylist = mmrw.GetCurrentPlaylist();
	float currentMMR = mmrw.GetPlayerMMR(gameWrapper->GetUniqueID(), currentPlaylist);

	UpdateMMR(currentPlaylist, currentMMR);
}

void PeakTracker::GameEnd(std::string eventName)
{
	if (!gameWrapper->IsInOnlineGame()) return;

	MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
	int currentPlaylist = mmrw.GetCurrentPlaylist();
	float currentMMR = mmrw.GetPlayerMMR(gameWrapper->GetUniqueID(), currentPlaylist);

	UpdateMMR(currentPlaylist, currentMMR);
}

void PeakTracker::OutputMMR(float mmr, std::string outputFile)
{
	std::string output;
	output = std::to_string(static_cast<int>(mmr));

	std::ofstream stream(gameWrapper->GetBakkesModPath().string() + "\\PeakTracker\\" + outputFile + ".txt", std::ios::out | std::ios::trunc);

	if (stream.is_open()) {
		stream << output;
		stream.close();
	}
	else {
		cvarManager->log("Failed to updated MMR in: " + outputFile + ".txt");
	}
}

void PeakTracker::UpdateMMR(int playlist, float mmr) 
{
	switch (playlist)
	{
	case 10:
		if (cvarManager->getCvar("duelMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("duelMMR").setValue(mmr);
			OutputMMR(mmr, "duelMMR");
		}
		break;
	case 11:
		if (cvarManager->getCvar("doublesMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("doublesMMR").setValue(mmr);
			OutputMMR(mmr, "doublesMMR");
		}
		break;
	case 13:
		if (cvarManager->getCvar("standardMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("standardMMR").setValue(mmr);
			OutputMMR(mmr, "standardMMR");
		}
		break;
	case 27:
		if (cvarManager->getCvar("hoopsMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("hoopsMMR").setValue(mmr);
			OutputMMR(mmr, "hoopsMMR");
		}
		break;
	case 28:
		if (cvarManager->getCvar("rumbleMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("rumbleMMR").setValue(mmr);
			OutputMMR(mmr, "rumbleMMR");
		}
		break;
	case 29:
		if (cvarManager->getCvar("dropshotMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("dropshotMMR").setValue(mmr);
			OutputMMR(mmr, "dropshotMMR");
		}
		break;
	case 30:
		if (cvarManager->getCvar("snowdayMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("snowdayMMR").setValue(mmr);
			OutputMMR(mmr, "snowdayMMR");
		}
		break;
	default:
		break;
	}
}

void PeakTracker::LoadExistingMMR()
{
	// Try to create PeakTracker directory.
	std::string pluginDirectory = gameWrapper->GetBakkesModPath().string() + "\\PeakTracker";
	if (_mkdir(pluginDirectory.c_str()) != 0)
	{
		cvarManager->log("PeakTracker directory found!");
		cvarManager->log("===== Loading saved MMR START =====");
		for (std::string mmrFile : mmrFiles)
		{
			cvarManager->log("Attempting to pull mmr from: " + mmrFile + ".txt");
			int mmr = 0;
			std::ifstream stream(pluginDirectory + "\\" + mmrFile + ".txt");
			if (stream.is_open())
			{
				stream >> mmr;
				stream.close();
				cvarManager->log("MMR value found: " + std::to_string(mmr));

				// Only call to update cvar when mmr is higher than 0 since cvar default is 0.
				if (mmr > 0)
				{
					cvarManager->getCvar(mmrFile).setValue(mmr);
				}
			}
			else
			{
				cvarManager->log(mmrFile + ".txt doesn't exist - Creating it now!");
				std::ofstream outStream(pluginDirectory + "\\" + mmrFile + ".txt");
				if (outStream.is_open()) {
					outStream << cvarManager->getCvar(mmrFile).getIntValue();
					outStream.close();
					cvarManager->log("Created file: " + mmrFile + ".txt");
				}
			}
		}
		cvarManager->log("===== Loading saved MMR END =====");
	}
	else
	{
		cvarManager->log("PeakTracker directory created!");
		cvarManager->log("===== Create default files START =====");
		for (std::string mmrFile : mmrFiles)
		{
			std::ofstream stream(pluginDirectory + "\\" + mmrFile + ".txt");
			if (stream.is_open()) {
				stream << cvarManager->getCvar(mmrFile).getIntValue();
				stream.close();
				cvarManager->log("Created file: " + mmrFile + ".txt");
			}
		}
		cvarManager->log("===== Create default files END =====");
	}
}