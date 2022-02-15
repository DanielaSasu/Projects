#pragma once
#include <string>
#include <iostream>
#include <map>
#include <ctime>

#ifdef LOGGING_EXPORTS
	#define PLAYER_LOGGING_API _declspec(dllexport)
#else
	#define PLAYER_LOGGING_API _declspec(dllimport)
#endif

class PLAYER_LOGGING_API PlayerLogger
{
public:
	enum class Level
	{
		Info,
		Warning
	};

public:
	PlayerLogger(std::ostream& os, Level minimumLevel = Level::Info);
	void log(const std::string& message, Level level);
	void setMinimumLogLevel(Level minimumLevel);

private:
	std::string convertLevel(Level&);
	std::string localTime();
	std::ostream& os;
	Level minimumLevel;
};