#pragma once
#include <string>
#include <iostream>
#include <map>
#include <ctime>

#ifdef LOGGING_EXPORTS
	#define GAME_EVENT_LOGGING_API _declspec(dllexport)
#else
	#define GAME_EVENT_LOGGING_API _declspec(dllimport)
#endif


class GAME_EVENT_LOGGING_API GameEventLogger
{
public:
	enum class Level
	{
		Info,
		Warning
	};

public:
	GameEventLogger(std::ostream& os, Level minimumLevel = Level::Info);
	void log(const std::string& message, Level level);
	void setMinimumLogLevel(Level minimumLevel);

private:
	std::string convertLevel(Level&);
	std::string localTime();
	std::ostream& os;
	Level minimumLevel;
};