#pragma once
#include <string>
#include <iostream>
#include <map>
#include <ctime>

#ifdef LOGGING_EXPORTS
	#define CARD_LOGGING_API _declspec(dllexport)
#else
	#define CARD_LOGGING_API _declspec(dllimport)
#endif


class CARD_LOGGING_API CardLogger
{
public:
	enum class Level
	{
		Info,
		Error
	};

public:
	CardLogger(std::ostream& os, Level minimumLevel = Level::Info);
	void log(const std::string& message, Level level);
	void setMinimumLogLevel(Level minimumLevel);
	std::string getCardLoggerLevel();

private:
	std::string convertLevel(Level&);
	std::string localTime();
	std::ostream& os;
	Level minimumLevel;
};