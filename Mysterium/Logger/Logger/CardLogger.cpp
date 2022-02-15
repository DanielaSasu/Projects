#include "CardLogger.h"

CardLogger::CardLogger(std::ostream& os, Level minimumLevel)
	: os(os), minimumLevel(minimumLevel)
{
}

std::string CardLogger::convertLevel(Level& level)
{
	std::map<Level, std::string> mapDecision =
	{
		{Level::Info,"Info"},
		{Level::Error,"Error"}
	};
	return mapDecision[level];
}

std::string CardLogger::localTime()
{
	time_t timeVariable;
	struct tm* timeStructure;
	time(&timeVariable);
	timeStructure = localtime(&timeVariable);

	if (asctime(timeStructure) != 0)
		return  asctime(timeStructure);
	return "Default Date!";
}

void CardLogger::log(const std::string& message, Level level)
{
	if (level >= minimumLevel)
	{
		os << convertLevel(level) << " : " << message << std::endl;
		os << "Date: " + localTime() << std::endl;
	}
}

void CardLogger::setMinimumLogLevel(Level minimumLevel)
{
	this->minimumLevel = minimumLevel;
}

std::string CardLogger::getCardLoggerLevel() 
{
	return convertLevel(this->minimumLevel);
}


