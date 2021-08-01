#include "pch.h"
#include "PeakTracker.h"


BAKKESMOD_PLUGIN(PeakTracker, "Track Peak MMR across various game-modes", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void PeakTracker::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("PeakTracker loaded!");
}

void PeakTracker::onUnload()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("PeakTracker unloaded!");
}