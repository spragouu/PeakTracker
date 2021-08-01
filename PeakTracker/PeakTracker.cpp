#include "pch.h"
#include "PeakTracker.h"


BAKKESMOD_PLUGIN(PeakTracker, "Track Peak MMR across various game-modes", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void PeakTracker::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("PeakTracker loaded!");

	cvarManager->registerCvar("standardMMR", "0", "3v3 MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("doublesMMR", "0", "2v2 MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("duelMMR", "0", "1v1 MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("rumbleMMR", "0", "Rumble MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("dropshotMMR", "0", "Dropshot MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("hoopsMMR", "0", "Hoops MMR", true, true, 0, true, 10000, true);
	cvarManager->registerCvar("snowdayMMR", "0", "Snowday MMR", true, true, 0, true, 10000, true);
}

void PeakTracker::onUnload()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("PeakTracker unloaded!");
}