#pragma once
#include <string>
#include <iostream>
#include <map> 
#include <ctime>

#ifdef LOGGING_EXPORTS
#define GHOST_LOGGING_API _declspec(dllexport)
#else
#define GHOST_LOGGING_API _declspec(dllimport)
#endif


class GHOST_LOGGING_API GhostLogger
{
public:
	enum class Level
	{
		Info,
		Warning
	};

public:
	GhostLogger(std::ostream& os, Level minimumLevel = Level::Info);
	void log(const std::string& message, Level level);
	void setMinimumLogLevel(Level minimumLevel);

private:
	std::string convertLevel(Level&);
	std::string localTime();
	std::ostream& os;
	Level minimumLevel;
};