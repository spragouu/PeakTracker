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
	SkillRank skillRank = mmrw.GetPlayerRank(gameWrapper->GetUniqueID(), currentPlaylist);

	// Only want to update MMR if player had finished their placement matches
	if (skillRank.MatchesPlayed >= 10)
	{
		UpdateMMR(currentPlaylist, currentMMR, skillRank);
	}
}

void PeakTracker::GameEnd(std::string eventName)
{
	if (!gameWrapper->IsInOnlineGame()) return;

	MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
	int currentPlaylist = mmrw.GetCurrentPlaylist();
	float currentMMR = mmrw.GetPlayerMMR(gameWrapper->GetUniqueID(), currentPlaylist);
	SkillRank skillRank = mmrw.GetPlayerRank(gameWrapper->GetUniqueID(), currentPlaylist);

	// Only want to update MMR if player had finished their placement matches
	if (skillRank.MatchesPlayed >= 10)
	{
		UpdateMMR(currentPlaylist, currentMMR, skillRank);
	}
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

void PeakTracker::UpdateMMR(int playlist, float mmr, SkillRank rank) 
{
	switch (playlist)
	{
	case 10:
		if (cvarManager->getCvar("duelMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("duelMMR").setValue(mmr);
			OutputMMR(mmr, "duelMMR");
			OutputCSV("Duel", mmr, rank);
		}
		break;
	case 11:
		if (cvarManager->getCvar("doublesMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("doublesMMR").setValue(mmr);
			OutputMMR(mmr, "doublesMMR");
			OutputCSV("Doubles", mmr, rank);
		}
		break;
	case 13:
		if (cvarManager->getCvar("standardMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("standardMMR").setValue(mmr);
			OutputMMR(mmr, "standardMMR");
			OutputCSV("Standard", mmr, rank);
		}
		break;
	case 27:
		if (cvarManager->getCvar("hoopsMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("hoopsMMR").setValue(mmr);
			OutputMMR(mmr, "hoopsMMR");
			OutputCSV("Hoops", mmr, rank);
		}
		break;
	case 28:
		if (cvarManager->getCvar("rumbleMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("rumbleMMR").setValue(mmr);
			OutputMMR(mmr, "rumbleMMR");
			OutputCSV("Rumble", mmr, rank);
		}
		break;
	case 29:
		if (cvarManager->getCvar("dropshotMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("dropshotMMR").setValue(mmr);
			OutputMMR(mmr, "dropshotMMR");
			OutputCSV("Dropshot", mmr, rank);
		}
		break;
	case 30:
		if (cvarManager->getCvar("snowdayMMR").getFloatValue() < mmr)
		{
			cvarManager->getCvar("snowdayMMR").setValue(mmr);
			OutputMMR(mmr, "snowdayMMR");
			OutputCSV("SnowDay", mmr, rank);
		}
		break;
	default:
		break;
	}
}

void PeakTracker::OutputCSV(std::string gameMode, float peakMMR, SkillRank skillRank)
{
	// Get current date in the following format - DD/MM/YYYY
	const int MAXLEN = 15;
	char date[MAXLEN];
	time_t myTime = time(0);
	strftime(date, MAXLEN, "%d/%m/%Y", localtime(&myTime));
	std::string currentDate(date);

	int mmr = static_cast<int>(peakMMR);
	std::string rank = GetRank(skillRank.Tier) + " Div " + std::to_string(skillRank.Division + 1);

	std::string output = (gameMode + "," + std::to_string(mmr) + "," + rank + "," + currentDate);

	std::ofstream stream(gameWrapper->GetBakkesModPath().string() + "\\PeakTracker\\PeakTracker.csv", std::ios::out | std::ios::app);

	if (stream.is_open()) {
		stream << output << std::endl;
		stream.close();
	}
	else {
		cvarManager->log("Failed to update PeakTracker.csv");
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
		std::string csvFirstLine;
		std::ifstream stream(pluginDirectory + "\\PeakTracker.csv");
		if (stream.is_open())
		{
			std::getline(stream, csvFirstLine);
			stream.close();
			cvarManager->log("PeakTracker.csv found! Validating structure...");

			// Only call to update cvar when mmr is higher than 0 since cvar default is 0.
			if (csvFirstLine == "GameMode,PeakMMR,Rank,DateAchieved")
			{
				cvarManager->log("PeakTracker.csv successfully validated!");
			}
			else
			{
				cvarManager->log("PeakTracker.csv failed validation!");
				cvarManager->log("Expected: GameMode,PeakMMR,Rank,DateAchieved");
				cvarManager->log("Recieved: " + csvFirstLine);
			}
		}
		else
		{
			cvarManager->log("PeakTracker.csv doesn't exist - Creating it now!");
			std::ofstream outStream(pluginDirectory + "\\PeakTracker.csv");
			if (outStream.is_open()) {
				outStream << "GameMode,PeakMMR,Rank,DateAchieved" << std::endl;
				outStream.close();
				cvarManager->log("Created file: PeakTracker.csv");
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
		std::ofstream stream(pluginDirectory + "\\PeakTracker.csv");
		if (stream.is_open()) {
			stream << "GameMode,PeakMMR,Rank,DateAchieved" << std::endl;
			stream.close();
			cvarManager->log("Created file: PeakTracker.csv");
		}
		cvarManager->log("===== Create default files END =====");
	}
}

std::string PeakTracker::GetRank(int rankID)
{
	switch (rankID)
	{
	case 0:
		return "Unranked";
		break;
	case 1:
		return "Bronze I";
		break;
	case 2:
		return "Bronze II";
		break;
	case 3:
		return "Bronze III";
		break;
	case 4:
		return "Silver I";
		break;
	case 5:
		return "Silver II";
		break;
	case 6:
		return "Silver III";
		break;
	case 7:
		return "Gold I";
		break;
	case 8:
		return "Gold II";
		break;
	case 9:
		return "Gold III";
		break;
	case 10:
		return "Platinum I";
		break;
	case 11:
		return "Platinum II";
		break;
	case 12:
		return "Platinum III";
		break;
	case 13:
		return "Diamond I";
		break;
	case 14:
		return "Diamond II";
		break;
	case 15:
		return "Diamond III";
		break;
	case 16:
		return "Champion I";
		break;
	case 17:
		return "Champion II";
		break;
	case 18:
		return "Champion III";
		break;
	case 19:
		return "Grand Champion I";
		break;
	case 20:
		return "Grand Champion II";
		break;
	case 21:
		return " Grand Champion III";
		break;
	case 22:
		return "Supersonic Legend";
		break;
	default:
		return "Unknown";
		break;
	}
}