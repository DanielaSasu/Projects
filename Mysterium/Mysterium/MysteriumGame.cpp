#include "MysteriumGame.h"
#include "../Logger/Logger/GameEventLogger.h"
#include "../Logger/Logger/GameEventLogger.cpp"

MysteriumGame::MysteriumGame()
	:m_resolutionScale(static_cast <float>(sf::VideoMode::getDesktopMode().width) / 1920)
{
}

MysteriumGame::MysteriumGame(sf::RenderWindow& gameWindow, std::array<Psychic, PLAYERS_SIZE>psychics, Board& board)
	: m_resolutionScale(static_cast <float>(sf::VideoMode::getDesktopMode().width) / 1920)
{
	write.open("GameEventLog.txt", std::ios::app);
	GameEventLogger gameEventLogger(write);

	GhostBoard ghost(board);
	PlayerBoard player1(board);
	PlayerBoardPhase2 playerPh2;

	sf::Music bgMusic, finalMusic;
	bgMusic.openFromFile("./Audio/MenuTheme.ogg");
	bgMusic.setVolume(12);
	bgMusic.setLoop(true);
	finalMusic.setLoop(true);
	finalMusic.setVolume(15);

	sf::Texture dummy, turn;
	sf::Sprite dummyCard, turnImage;
	if (!dummy.loadFromFile("./ClueCards/DummyCard.png"))
	{
		std::cout << "Can't load dummy image" << std::endl;
	}
	dummyCard.setTexture(dummy);

	uint16_t widthDesktop = sf::VideoMode::getDesktopMode().width;
	uint16_t heightDesktop = sf::VideoMode::getDesktopMode().height;

	gameWindow.close();
	sf::RenderWindow auxWindow;
	int counter;

	std::array<bool, PLAYERS_SIZE>endPhase;
	endPhase.fill(false);

	sf::Texture loseBg;
	if (!loseBg.loadFromFile("./Backgrounds/LoseScreen.jpg"))
		std::cout << "Can't loat image!" << std::endl;

	sf::Sprite loseBgSP;
	loseBgSP.setScale(static_cast <float>(0.75) * m_resolutionScale, static_cast <float>(0.75) * m_resolutionScale);
	loseBgSP.setTexture(loseBg);

	sf::Texture winBg;
	if (!winBg.loadFromFile("./Backgrounds/WinScreen.jpg"))
		std::cout << "Can't loat image!" << std::endl;

	sf::Sprite winBgSP;
	winBgSP.setScale(static_cast <float>(0.75) * m_resolutionScale, static_cast <float>(0.75) * m_resolutionScale);
	winBgSP.setTexture(winBg);
	bgMusic.play();

	gameEventLogger.log("Game Phase 1: ", GameEventLogger::Level::Info);
	for (int index = 0; index < NUMBER_OF_ROUNDS; index++)
	{
		gameEventLogger.log("Round " + std::to_string(index + 1) + ":", GameEventLogger::Level::Info);
		turn.loadFromFile("./Clock/Clock" + std::to_string(index + 1) + ".png");
		turnImage.setTexture(turn);
		turnImage.setScale(static_cast <float>(m_resolutionScale * 0.29), static_cast <float>(m_resolutionScale * 0.29));
		counter = 0;
		auxWindow.create(sf::VideoMode(widthDesktop, heightDesktop), "Mysterium", sf::Style::Fullscreen);
		ghost.InitializeBoard(board, auxWindow, psychics, turnImage);
		for (int index2 = 0; index2 < PLAYERS_SIZE; index2++)
		{
			psychics[index2].setPsychicID(index2 + 1);
			auxWindow.create(sf::VideoMode(widthDesktop, heightDesktop), "Mysterium", sf::Style::Fullscreen);
			if (psychics[index2].getPhase() < 4)
			{
				gameEventLogger.log(psychics[index2].getPlayerInfo(), GameEventLogger::Level::Info);
				player1.InitializeBoard(board, ghost, auxWindow, psychics[index2], turnImage);
			}
			else
			{
				ghost.setChosenCard(dummyCard);
			}
		}
		ghost.checkCards(psychics);
		for (int index2 = 0; index2 < PLAYERS_SIZE; index2++)
		{
			if (psychics[index2].getPhase() == 4)
			{
				if (endPhase[index2] == false)
				{
					psychics[index2].addPoints(NUMBER_OF_ROUNDS - index - 1);
					gameEventLogger.log("Psychic" + std::to_string(index2 + 1) + " guesed his clue set! His score is: "
						+ std::to_string(psychics[index2].getPoints()), GameEventLogger::Level::Info);
					endPhase[index2] = true;
				}
				counter++;
			}
		}
		if (counter == 4)
		{
			break;
		}
	}
	
	GhostBoardPhase2 ghost2(board);

	if (counter != 4)
	{
		gameEventLogger.log("The psychics lost!", GameEventLogger::Level::Info);
		bgMusic.stop();

		FinalScreen finalScreen;
		finalMusic.openFromFile("./Audio/loseSound.ogg");
		finalScreen.displayScreen(loseBgSP, finalMusic);
	}
	else
	{
		gameEventLogger.log("Game Phase 2: ", GameEventLogger::Level::Info);
		auxWindow.create(sf::VideoMode(widthDesktop, heightDesktop), "Mysterium", sf::Style::Fullscreen);
		ghost2.InitializeBoard(board, auxWindow, psychics);
		auxWindow.create(sf::VideoMode(widthDesktop, heightDesktop), "Mysterium", sf::Style::Fullscreen);
		playerPh2.Intinialize(auxWindow, psychics, ghost2);
		if (ghost2.getCorrectClueSetIndex() == playerPh2.getVoteIndex())
		{
			gameEventLogger.log("The psychics won!", GameEventLogger::Level::Info);
			bgMusic.stop();

			FinalScreen finalScreen;
			finalMusic.openFromFile("./Audio/winSound.ogg");
			finalScreen.displayScreen(winBgSP, finalMusic);
		}
		else
		{
			gameEventLogger.log("The psychics lost!", GameEventLogger::Level::Info);
			bgMusic.stop();

			FinalScreen finalScreen;
			finalMusic.openFromFile("./Audio/loseSound.ogg");
			finalScreen.displayScreen(loseBgSP, finalMusic);
		}
	}
	write << std::endl;
	write.close();
}

MysteriumGame::~MysteriumGame()
{
}