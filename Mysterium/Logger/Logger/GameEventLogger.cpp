#include "GameEventLogger.h"

GameEventLogger::GameEventLogger(std::ostream& os, Level minimumLevel)
	: os(os), minimumLevel(minimumLevel)
{
}

std::string GameEventLogger::convertLevel(Level& level)
{
	std::map<Level, std::string> mapDecision =
	{
		{Level::Info,"Info"},
		{Level::Warning,"Warning"}
	};
	return mapDecision[level];
}

std::string GameEventLogger::localTime()
{
	time_t timeVariable;
	struct tm* timeStructure;
	time(&timeVariable);
	timeStructure = localtime(&timeVariable);

	if (asctime(timeStructure) != 0)
		return  asctime(timeStructure);
	return "Default Date!";
}

void GameEventLogger::log(const std::string& message, Level level)
{
	if (level >= minimumLevel)
		os << convertLevel(level) << " : " << message << "Date: " + localTime() << std::endl;
}

void GameEventLogger::setMinimumLogLevel(Level minimumLevel)
{
	this->minimumLevel = minimumLevel;
}


