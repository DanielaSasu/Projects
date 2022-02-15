#include "GhostLogger.h"

GhostLogger::GhostLogger(std::ostream& os, Level minimumLevel)
	: os(os), minimumLevel(minimumLevel)
{
}

std::string GhostLogger::convertLevel(Level& level)
{
	std::map<Level, std::string> mapDecision =
	{
		{Level::Info,"Info"},
		{Level::Warning,"Warning"}
	};
	return mapDecision[level];
}

std::string GhostLogger::localTime()
{
	time_t timeVariable;
	struct tm* timeStructure;
	time(&timeVariable);
	timeStructure = localtime(&timeVariable);

	if (asctime(timeStructure) != 0)
		return  asctime(timeStructure);
	return "Default Date!";
}

void GhostLogger::log(const std::string& message, Level level)
{
	if (level >= minimumLevel)
		os << convertLevel(level) << " : " << message << " Date: " + localTime() << std::endl;
}

void GhostLogger::setMinimumLogLevel(Level minimumLevel)
{
	this->minimumLevel = minimumLevel;
}


