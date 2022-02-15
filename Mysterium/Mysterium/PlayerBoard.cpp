#include "PlayerBoard.h"
#include "../Logger/Logger/PlayerLogger.h"
#include "../Logger/Logger/PlayerLogger.cpp"

std::string PlayerBoard::setMessage(Psychic& psychic)
{
	std::map <uint16_t, std::string> mapDecision = {
		{1,"Choose a suspect."},
		{2,"Choose a location."},
		{3,"Choose a weapon."}
	};
	return mapDecision[psychic.getPhase()];
}

void PlayerBoard::ArrangeClueCards(std::array<ClueCard, SIZE> clueCardArray, std::array<ClueCard,SIZE>& spriteArray)
{
	for (int index = 0; index < PlayerBoard::SIZE; index++)
	{
		spriteArray[index] = clueCardArray[index];
		spriteArray[index].setCardScale(static_cast <float>(0.29) * m_resolutionScale, static_cast <float>(0.29) * m_resolutionScale);
	}
}

void PlayerBoard::ArrangeVisionsCards(std::vector<VisionCard> visionCardVector, std::array<VisionCard,NUMBER_OF_VISIONS>&spriteArray)
{
	for (int index = 0; index < visionCardVector.size(); index++)
	{
		spriteArray[index] = visionCardVector[index];
		spriteArray[index].setCardScale(static_cast <float>(0.5) * m_resolutionScale, static_cast <float>(0.5) * m_resolutionScale);
	}
}

void PlayerBoard::showCards(std::array<ClueCard,SIZE>&array, const float& width, const float& height, sf::RenderWindow& gameWindow)
{
	uint16_t positionIndex = 0;
	for (int index = 0; index < PlayerBoard::SIZE; index++)
	{
		array[index].setCardPosition(sf::Vector2f(m_widthDesktop / static_cast <float>(5.4) + positionIndex + width, m_heightDesktop / 20 + height));
		gameWindow.draw(array[index].getCardImage());
		positionIndex += static_cast<uint16_t>(array[index].getCardImage().getTexture()->getSize().x * array[index].getCardImage().getScale().x + 15);
	}
}

void PlayerBoard::showCards(std::array<VisionCard, NUMBER_OF_VISIONS>&array, const float& width, const float& height, sf::RenderWindow& gameWindow, Psychic& psychic)
{
	uint64_t positionIndex1 = 0;
	for (int index = 0; index < psychic.getVisionsNumber(); index++)
	{
		array[index].setCardPosition(sf::Vector2f(m_widthDesktop / 5 + positionIndex1 + width, m_heightDesktop / static_cast <float>(5.20) + height));
		gameWindow.draw(array[index].getCardImage());
		positionIndex1 += static_cast<uint16_t>(static_cast <float>(0.5) * m_resolutionScale * 400 + 10);
	}
}

void PlayerBoard::MoveLeft(Psychic& psychic)
{
	if (m_selectedItemNumber - 1 >= 0)
	{
		if (m_selectedItemNumber != 0)
		{
			switch (psychic.getPhase())
			{
			case 1:
			{
				m_suspectArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.29) * m_resolutionScale, static_cast <float>(0.29) * m_resolutionScale);
				m_selectedItemNumber--;
				m_suspectArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.31) * m_resolutionScale, static_cast <float>(0.31) * m_resolutionScale);
				break;
			}
			case 2:
			{
				m_locationArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.29) * m_resolutionScale, static_cast <float>(0.29) * m_resolutionScale);
				m_selectedItemNumber--;
				m_locationArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.31) * m_resolutionScale, static_cast <float>(0.31) * m_resolutionScale);
				break;
			}
			case 3:
			{
				m_weaponArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.29) * m_resolutionScale, static_cast <float>(0.29) * m_resolutionScale);
				m_selectedItemNumber--;
				m_weaponArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.31) * m_resolutionScale, static_cast <float>(0.31) * m_resolutionScale);
				break;
			}
			}
		}

	}
}

void PlayerBoard::MoveRight(Psychic& psychic)
{
	if (m_selectedItemNumber + 1 < PlayerBoard::SIZE)
	{
		switch (psychic.getPhase())
		{
		case 1:
		{
			m_suspectArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.29) * m_resolutionScale, static_cast <float>(0.29) * m_resolutionScale);
			m_selectedItemNumber++;
			m_suspectArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.31) * m_resolutionScale, static_cast <float>(0.31) * m_resolutionScale);
			break;
		}
		case 2:
		{
			m_locationArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.29) * m_resolutionScale, static_cast <float>(0.29) * m_resolutionScale);
			m_selectedItemNumber++;
			m_locationArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.31) * m_resolutionScale, static_cast <float>(0.31) * m_resolutionScale);
			break;
		}
		case 3:
		{
			m_weaponArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.29) * m_resolutionScale, static_cast <float>(0.29) * m_resolutionScale);
			m_selectedItemNumber++;
			m_weaponArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.31) * m_resolutionScale, static_cast <float>(0.31) * m_resolutionScale);
			break;
		}
		}
	}
}

void PlayerBoard::InitializeBoard(Board board, GhostBoard& auxGhost, sf::RenderWindow& gameWindow, Psychic& psychic, sf::Sprite& clock)
{
	write.open("PlayerLog.txt", std::ios::app);
	PlayerLogger playerLogger(write);

	sf::Music clockMusic;
	clockMusic.openFromFile("./Audio/ClockSound.ogg");
	clockMusic.setVolume(10);

	sf::Sprite aux;

	sf::Sprite player;
	player = psychic.getPsychicImage();

	player.setScale(static_cast <float>(0.48) * m_resolutionScale, static_cast <float>(0.48) * m_resolutionScale);
	player.setPosition(static_cast <float>(m_widthDesktop / 24), m_heightDesktop / static_cast <float>(1.52));

	sf::Event eventPlayerBoard;

	sf::Texture background;
	if (!background.loadFromFile("./Backgrounds/GameBoard.jpg"))
		std::cout << "Can't load image!";
	sf::Sprite backgroundSp;
	backgroundSp.setTexture(background);

	aux.setTexture(background);

	clock.setPosition(m_widthDesktop - m_widthDesktop / static_cast <float>(1.06), static_cast <float>((m_heightDesktop - (m_heightDesktop / 2))));

	ArrangeVisionsCards(psychic.getVisionCards(), m_visionsPlayer);
	ChangeCardPhase(static_cast <float>(0.31), psychic);

	sf::Font font;
	sf::Font font1;
	font.loadFromFile("./Buttons/ChrustyRock-ORLA.ttf");
	font1.loadFromFile("./Buttons/Clutter Street.ttf");
	sf::Text message;
	message.setFont(font);
	message.setFillColor(sf::Color(218, 165, 32, 255));
	message.setCharacterSize(40);
	message.setString(setMessage(psychic));
	message.setPosition(800 * m_resolutionScale, static_cast <float>(m_heightDesktop) / static_cast <float>(1.8));

	sf::Clock clock1;
	sf::Text timer;

	timer.setFont(font1);
	timer.setCharacterSize(90);
	timer.setFillColor(sf::Color(218, 165, 32, 255));
	timer.setPosition(160 * m_resolutionScale, 20 * m_resolutionScale);

	uint16_t spaceNr = 0;
	uint16_t numNr = 0;
	sf::Sprite auxCard;

	while (gameWindow.isOpen())
	{
		timer.setString(std::to_string(120 - (int)(clock1.getElapsedTime().asSeconds())));
		if (clock1.getElapsedTime().asSeconds() >= 90)
		{
			clockMusic.play();
			timer.setFillColor(sf::Color::Red);
		}
		if (clock1.getElapsedTime().asSeconds() >= ROUND_TIME)
		{
			if (psychic.getPhase() == 1)
			{
				auxGhost.setChosenCard(m_suspectArray[m_selectedItemNumber].getCardImage());
				m_suspectArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.29) * m_resolutionScale, static_cast <float>(0.29) * m_resolutionScale);
				playerLogger.log("The time has run out! Default choice is: Suspect" + std::to_string(m_selectedItemNumber + 1), PlayerLogger::Level::Warning);
			}

			if (psychic.getPhase() == 2)
			{
				auxGhost.setChosenCard(m_locationArray[m_selectedItemNumber].getCardImage());
				m_locationArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.29) * m_resolutionScale, static_cast <float>(0.29) * m_resolutionScale);
				playerLogger.log("The time has run out! Default choice is: Location" + std::to_string(m_selectedItemNumber + 1), PlayerLogger::Level::Warning);
			}

			if (psychic.getPhase() == 3)
			{
				auxGhost.setChosenCard(m_weaponArray[m_selectedItemNumber].getCardImage());
				m_weaponArray[m_selectedItemNumber].setCardScale(static_cast <float>(0.29) * m_resolutionScale, static_cast <float>(0.29) * m_resolutionScale);
				playerLogger.log("The time has run out! Default choice is: Weapon" + std::to_string(m_selectedItemNumber + 1), PlayerLogger::Level::Warning);
			}
			m_selectedItemNumber = 0;
			gameWindow.close();
		}

		while (gameWindow.pollEvent(eventPlayerBoard))
		{
			switch (eventPlayerBoard.type)
			{
			case sf::Event::Closed:
				clockMusic.stop();
				gameWindow.close();
				break;
			case sf::Event::KeyPressed:
			{
				switch (eventPlayerBoard.key.code)
				{
				case sf::Keyboard::Escape:
				{
					m_selectedItemNumber = 0;
					clockMusic.stop();
					gameWindow.close();
					break;
				}
				case sf::Keyboard::Left:
				{
					MoveLeft(psychic);
					break;
				}
				case sf::Keyboard::Right:
				{
					MoveRight(psychic);
					break;
				}
				case sf::Keyboard::A:
				{
					MoveLeft(psychic);
					break;
				}
				case sf::Keyboard::D:
				{
					MoveRight(psychic);
					break;
				}

				case sf::Keyboard::Space:
				{
					if (psychic.getPhase() == 1)
					{
						auxCard = m_suspectArray[m_selectedItemNumber].getCardImage();
						zoomClueCards(spaceNr, auxCard, m_suspectArray[m_selectedItemNumber]);
					}

					if (psychic.getPhase() == 2)
					{
						auxCard = m_locationArray[m_selectedItemNumber].getCardImage();
						zoomClueCards(spaceNr, auxCard, m_locationArray[m_selectedItemNumber]);
					}

					if (psychic.getPhase() == 3)
					{
						auxCard = m_weaponArray[m_selectedItemNumber].getCardImage();
						zoomClueCards(spaceNr, auxCard, m_weaponArray[m_selectedItemNumber]);
					}
					break;
				}
				case sf::Keyboard::Num1:
				{
					if (psychic.getVisionsNumber() >= 1)
					{
						auxCard = m_visionsPlayer[0].getCardImage();
						zoomVisionCards(numNr, auxCard);
					}
					break;
				}
				case sf::Keyboard::Num2:
				{
					if (psychic.getVisionsNumber() >= 2)
					{
						auxCard = m_visionsPlayer[1].getCardImage();
						zoomVisionCards(numNr, auxCard);
					}
					break;
				}
				case sf::Keyboard::Num3:
				{
					if (psychic.getVisionsNumber() >= 3)
					{
						auxCard = m_visionsPlayer[2].getCardImage();
						zoomVisionCards(numNr, auxCard);
					}
					break;
				}case sf::Keyboard::Num4:
				{
					if (psychic.getVisionsNumber() >= 4)
					{
						auxCard = m_visionsPlayer[3].getCardImage();
						zoomVisionCards(numNr, auxCard);
					}
					break;
				}case sf::Keyboard::Num5:
				{
					if (psychic.getVisionsNumber() >= 5)
					{
						auxCard = m_visionsPlayer[4].getCardImage();
						zoomVisionCards(numNr, auxCard);
					}
					break;
				}case sf::Keyboard::Num6:
				{
					if (psychic.getVisionsNumber() >= 6)
					{
						auxCard = m_visionsPlayer[5].getCardImage();
						zoomVisionCards(numNr, auxCard);
					}
					break;
				}case sf::Keyboard::Num7:
				{
					if (psychic.getVisionsNumber() >= 7)
					{
						auxCard = m_visionsPlayer[6].getCardImage();
						zoomVisionCards(numNr, auxCard);
					}
					break;
				}
				case sf::Keyboard::Enter:
				{
					if (psychic.getPhase() == 1)
					{
						auxGhost.setChosenCard(m_suspectArray[m_selectedItemNumber].getCardImage());
						playerLogger.log("Psychihc" + std::to_string(psychic.getPsychicID()) 
							+ " chose Suspect" + std::to_string(m_selectedItemNumber + 1), PlayerLogger::Level::Info);
					}

					if (psychic.getPhase() == 2)
					{
						auxGhost.setChosenCard(m_locationArray[m_selectedItemNumber].getCardImage());
						playerLogger.log("Psychihc" + std::to_string(psychic.getPsychicID())
							+ " chose Location" + std::to_string(m_selectedItemNumber + 1), PlayerLogger::Level::Info);
					}

					if (psychic.getPhase() == 3)
					{
						auxGhost.setChosenCard(m_weaponArray[m_selectedItemNumber].getCardImage());
						playerLogger.log("Psychihc" + std::to_string(psychic.getPsychicID())
							+ " chose Weapon" + std::to_string(m_selectedItemNumber + 1), PlayerLogger::Level::Info);
					}

					ChangeCardPhase(static_cast <float>(0.29), psychic);

					m_selectedItemNumber = 0;
					clockMusic.stop();
					gameWindow.close();
					break;
				}
				}
				break;
			}
			}
		}
		gameWindow.clear();
		gameWindow.draw(backgroundSp);
		showCards(m_suspectArray, 0, 0, gameWindow);
		showCards(m_locationArray, 0, 185 * m_resolutionScale, gameWindow);
		showCards(m_weaponArray, 340 * m_resolutionScale, 360 * m_resolutionScale, gameWindow);
		showCards(m_visionsPlayer, 0, m_heightDesktop / static_cast <float>(2.2), gameWindow, psychic);
		gameWindow.draw(player);
		gameWindow.draw(message);
		gameWindow.draw(clock);
		gameWindow.draw(timer);
		if (spaceNr == 1 || numNr == 1)
			gameWindow.draw(auxCard);
		gameWindow.display();
	}
	write.close();
}

void PlayerBoard::ChangeCardPhase(const float& scale, Psychic& psychic)
{
	switch (psychic.getPhase())
	{
	case 1:
	{
		m_suspectArray[m_selectedItemNumber].setCardScale(scale * m_resolutionScale, scale * m_resolutionScale);
		break;
	}
	case 2:
	{
		m_locationArray[m_selectedItemNumber].setCardScale(scale * m_resolutionScale, scale * m_resolutionScale);
		break;
	}
	case 3:
	{
		m_weaponArray[m_selectedItemNumber].setCardScale(scale * m_resolutionScale, scale * m_resolutionScale);
		break;
	}
	}
}

void PlayerBoard::zoomClueCards(uint16_t& spaceNr, sf::Sprite& card, ClueCard& originalCard)
{
	spaceNr++;
	if (spaceNr == 1)
	{
		card.setColor(originalCard.getCardImage().getColor());
		card.setScale(m_resolutionScale, m_resolutionScale);
		card.setPosition(sf::Vector2f(m_widthDesktop / 2 - static_cast<float>(card.getTexture()->getSize().x) / 2,
			m_heightDesktop / 2 - static_cast<float>(card.getTexture()->getSize().y) / 2));
	}
	if (spaceNr == 2)
	{
		originalCard.setCardScale(static_cast<float>(0.31) * m_resolutionScale, static_cast<float>(0.31) * m_resolutionScale);
		card.setColor(sf::Color(0, 0, 0, 0));
		spaceNr = 0;
	}
}

void PlayerBoard::zoomVisionCards(uint16_t& numNr, sf::Sprite& card)
{
	numNr++;
	if (numNr == 1)
	{
		card.setColor(m_visionsPlayer[0].getCardImage().getColor());
		card.setScale(m_resolutionScale, m_resolutionScale);
		card.setPosition(sf::Vector2f(m_widthDesktop / 2 - static_cast<float>(card.getTexture()->getSize().x) / 2,
			m_heightDesktop / 2 - static_cast<float>(card.getTexture()->getSize().y) / 2));
	}
	if (numNr == 2)
	{
		card.setScale(static_cast<float>(0.31) * m_resolutionScale, static_cast<float>(0.31) * m_resolutionScale);
		card.setColor(sf::Color(0, 0, 0, 0));
		numNr = 0;
	}
}

PlayerBoard::PlayerBoard()
	:m_widthDesktop(sf::VideoMode::getDesktopMode().width), m_heightDesktop(sf::VideoMode::getDesktopMode().height), m_resolutionScale(static_cast <float>(sf::VideoMode::getDesktopMode().width) / 1920)
{
	m_selectedItemNumber = 0;
}

PlayerBoard::PlayerBoard(Board& board)
	: m_widthDesktop(sf::VideoMode::getDesktopMode().width), m_heightDesktop(sf::VideoMode::getDesktopMode().height), m_resolutionScale(static_cast <float>(sf::VideoMode::getDesktopMode().width) / 1920)
{
	m_selectedItemNumber = 0;

	std::array<ClueCard, SIZE>auxArray;
	auxArray = board.getSustepects();
	std::random_shuffle(auxArray.begin(), auxArray.end());
	ArrangeClueCards(auxArray, m_suspectArray);

	auxArray = board.getLocations();
	std::random_shuffle(auxArray.begin(), auxArray.end());
	ArrangeClueCards(auxArray, m_locationArray);

	auxArray = board.getWeapons();
	std::random_shuffle(auxArray.begin(), auxArray.end());
	ArrangeClueCards(auxArray, m_weaponArray);
}

PlayerBoard::~PlayerBoard()
{
}
