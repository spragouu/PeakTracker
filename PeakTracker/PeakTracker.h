#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class PeakTracker: public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow
{
	virtual void onLoad();
	virtual void onUnload();

	void RenderSettings() override;
	std::string GetPluginName() override;
	void SetImGuiContext(uintptr_t ctx) override;

	void GameStart(std::string eventName);
	void GameEnd(std::string eventName);
	void OutputMMR(float mmr, std::string outputFile);
	void UpdateMMR(int playlist, float mmr);
	void LoadExistingMMR();

	std::string mmrFiles[7] = {
		"duelMMR",
		"doublesMMR",
		"standardMMR",
		"rumbleMMR",
		"dropshotMMR",
		"snowdayMMR",
		"hoopsMMR"
	};
};

