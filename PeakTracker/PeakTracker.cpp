#include "pch.h"
#include "PeakTracker.h"
#include <fstream>


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
	// Causal MMR for testing
	cvarManager->registerCvar("casualMMR", "0", "Casual MMR", true, true, 0, true, 10000, true);
}

void PeakTracker::onUnload()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("PeakTracker unloaded!");
}

void PeakTracker::GameStart(std::string eventName)
{
	if (!gameWrapper->IsInOnlineGame()) return;

	MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
	int currentPlaylist = mmrw.GetCurrentPlaylist();
	float currentMMR = mmrw.GetPlayerMMR(gameWrapper->GetUniqueID(), currentPlaylist);

	/*cvarManager->getCvar("casualMMR").setValue(mmrw.GetPlayerMMR(gameWrapper->GetUniqueID(), mmrw.GetCurrentPlaylist()));
	cvarManager->log(std::to_string(mmrw.GetPlayerMMR(gameWrapper->GetUniqueID(), mmrw.GetCurrentPlaylist())));*/

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

void PeakTracker::OutputMMR(float mmr)
{
	std::string output;
	output = std::to_string(mmr);

	std::ofstream stream(gameWrapper->GetBakkesModPath().string() + "\\PeakTracker\\" + "MMR.txt", std::ios::out | std::ios::app);
	

	if (stream.is_open()) {
		stream << output;
		stream.close();
	}
	else {
		cvarManager->log("Can't write to file: MMR.txt");
		cvarManager->log("Value to write was: " + output);
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
			OutputMMR(mmr);
		}
		break;
	case 11:
		if (cvarManager->getCvar("doublesMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("doublesMMR").setValue(mmr);
			OutputMMR(mmr);
		}
		break;
	case 13:
		if (cvarManager->getCvar("standardMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("standardMMR").setValue(mmr);
			OutputMMR(mmr);
		}
		break;
	case 27:
		if (cvarManager->getCvar("hoopsMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("hoopsMMR").setValue(mmr);
			OutputMMR(mmr);
		}
		break;
	case 28:
		if (cvarManager->getCvar("rumbleMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("rumbleMMR").setValue(mmr);
			OutputMMR(mmr);
		}
		break;
	case 29:
		if (cvarManager->getCvar("dropshotMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("dropshotMMR").setValue(mmr);
			OutputMMR(mmr);
		}
		break;
	case 30:
		if (cvarManager->getCvar("snowdayMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("snowdayMMR").setValue(mmr);
			OutputMMR(mmr);
		}
		break;
	// Following cases are for testing. Remove before publishing.
	case 6:
	case 1:
	case 2:
	case 3:
		if (cvarManager->getCvar("casualMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("casualMMR").setValue(mmr);
			OutputMMR(mmr);
		}
		break;
	default:
		break;
	}
}