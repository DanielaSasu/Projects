#include "pch.h"
#include "CppUnitTest.h"
#include "../Logger/Logger/CardLogger.h"
#include "../Logger/Logger/CardLogger.cpp"
#include "../Mysterium/Player.h"
#include "../Mysterium/Player.cpp"
#include "../Logger/Logger/GameEventLogger.h"
#include "../Logger/Logger/GameEventLogger.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		TEST_METHOD(TestCardLoggerLog)
		{
			std::stringstream outputStream;
			CardLogger cardLoggerTest(outputStream,CardLogger::Level::Info);
			cardLoggerTest.log("This is a test!", CardLogger::Level::Info);
			std::string result;
			std::getline(outputStream, result);
			std::string aux("Info : This is a test!");
			Assert::AreEqual(result, aux);
		}
		TEST_METHOD(TestCardLoggerMinimumLevel)
		{
			std::stringstream outputStream;
			CardLogger cardLoggerTest(outputStream, CardLogger::Level::Info);
			cardLoggerTest.setMinimumLogLevel(CardLogger::Level::Error);
			std::string level = "Error";
			Assert::AreEqual(level,cardLoggerTest.getCardLoggerLevel());
		}
		TEST_METHOD(TestCardLoggerConstructor)
		{
			std::stringstream outputStream;
			CardLogger cardLoggerTest(outputStream);
			std::string level = "Info";
			Assert::AreEqual(level, cardLoggerTest.getCardLoggerLevel());
		}
		TEST_METHOD(TestGameEventLoggerLog)
		{
			std::stringstream outputStream;
			GameEventLogger gameEventLoggerTest(outputStream);
			Player testPlayer;
		
			uint16_t playerID = 1;
			uint16_t points = 3;

			testPlayer.setPlayerID(playerID);
			testPlayer.addPoints(points);
			testPlayer.IncreasePhase();

			gameEventLoggerTest.log(testPlayer.getPlayerInfo(), GameEventLogger::Level::Info);

			std::string aux;
			std::getline(outputStream, aux);
			std::string result("Info : Player1 has 3 points in phase 2.");

			Assert::AreEqual(aux,result);
		}
		TEST_METHOD(TestPlayerConstructor)
		{
			Player testPlayer;

			uint16_t phase = 1;
			uint16_t playerID = 1;
			uint16_t points = 0;

			Assert::IsTrue(testPlayer.getPlayerPhase() == phase);
			Assert::IsTrue(testPlayer.getPlayerID() == playerID);
			Assert::IsTrue(testPlayer.getPlayerPoints() == points);
		}
		TEST_METHOD(TestPlayerCopyConstructor)
		{
			Player testPlayer;
			Player copyPlayer(testPlayer);

			uint16_t phase = 1;
			uint16_t playerID = 1;
			uint16_t points = 0;

			Assert::IsTrue(copyPlayer.getPlayerPhase() == phase);
			Assert::IsTrue(copyPlayer.getPlayerID() == playerID);
			Assert::IsTrue(copyPlayer.getPlayerPoints() == points);
		}
		TEST_METHOD(TestPlayerAttributionOperator)
		{
			Player testPlayer;
			
			uint16_t phase = 1;
			uint16_t playerID = 1;
			uint16_t points = 0;
			
			Player otherPlayer = testPlayer;

			Assert::IsTrue(otherPlayer.getPlayerID() == testPlayer.getPlayerID());
			Assert::IsTrue(otherPlayer.getPlayerPhase() == testPlayer.getPlayerPhase());
			Assert::IsTrue(otherPlayer.getPlayerPoints() == testPlayer.getPlayerPoints());
		}
		TEST_METHOD(TestPlayerSetters)
		{
			Player testPlayer;
			Player otherPlayer;

			uint16_t playerID = 3;
			uint16_t points = 4;

			otherPlayer.setPlayerID(playerID);
			otherPlayer.addPoints(points);
			otherPlayer.IncreasePhase();

			Assert::IsFalse(testPlayer.getPlayerID() == otherPlayer.getPlayerID());
			Assert::IsFalse(testPlayer.getPlayerPoints() == otherPlayer.getPlayerPoints());
			Assert::IsFalse(testPlayer.getPlayerPhase() == otherPlayer.getPlayerPhase());
		}
		TEST_METHOD(TestPlayerInformation)
		{
			Player testPlayer;
			
			testPlayer.setPlayerID(2);
			testPlayer.addPoints(3);
			testPlayer.IncreasePhase();
			testPlayer.IncreasePhase();

			std::string testString = "Player2 has 3 points in phase 3.\n";

			Assert::AreEqual(testPlayer.getPlayerInfo(), testString);
		}
	};
}
