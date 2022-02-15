#include "GhostBoard.h"
#include "../Logger/Logger/GhostLogger.h"
#include "../Logger/Logger/GhostLogger.cpp"

std::string GhostBoard::getMessage(std::array<Psychic, PLAYERS_SIZE>& psychics)
{
	std::map<uint16_t, std::string> mapDecision;
	if (psychics[m_psychicNumber].getPhase() == 4)
	{
		mapDecision = {
			{0,"The first psychic has finished!  Press ENTER."},
			{1,"The second psychic has finished!  Press ENTER."},
			{2,"The third psychic has finished!  Press ENTER."},
			{3,"The fourth psychic has finished!  Press ENTER."},
		};
	}
	else
	{
		mapDecision = {
			{0,"Choose a card for the first psychic. "},
			{1,"Choose a card for the second psychic. "},
			{2,"Choose a card for the third psychic. "},
			{3,"Choose a card for the fourth psychic. "},
		};
	}
	return mapDecision[static_cast<unsigned short>(m_psychicNumber)];
}

void GhostBoard::Copy_Array_to_Sprite(std::array<ClueCard, SIZE>clueCardArray, sf::Sprite spriteArray[SIZE])
{
	for (int index = 0; index < SIZE - 1; index++)
	{
		spriteArray[index] = clueCardArray[index].getCardImage();
		spriteArray[index].setScale(static_cast <float>(0.28) * m_resolutionScale, static_cast <float>(0.28) * m_resolutionScale);
		spriteArray[index].setColor(sf::Color(128, 128, 128, 190));
	}
}

void GhostBoard::Copy_Array_to_Sprite(std::array<VisionCard, VISION_DECK_SIZE>visionCardArray, sf::Sprite spriteArray[VISION_DECK_SIZE])
{
	for (int index = 0; index < VISION_DECK_SIZE; index++)
	{
		spriteArray[index] = visionCardArray[index].getCardImage();
		spriteArray[index].setScale(static_cast <float>(0.45) * m_resolutionScale, static_cast <float>(0.45) * m_resolutionScale);
	}
}

std::array<VisionCard, GhostBoard::VISION_DECK_SIZE> GhostBoard::Copy_spriteArray_to_visionArray()
{
	std::array<VisionCard, GhostBoard::VISION_DECK_SIZE> auxArray;
	for (uint16_t index = 0; index < GhostBoard::VISION_DECK_SIZE; index++)
	{
		VisionCard auxCard(m_visionDeck[index]);
		auxArray[index] = std::move(auxCard);
	}
	return auxArray;
}

void GhostBoard::showCards(sf::Sprite clueSetArray[SIZE], sf::Sprite psychicsArray[PLAYERS_SIZE], const float& width,
	const float& height, sf::RenderWindow& gameWindow)
{
	uint16_t positionHeight;
	uint16_t positionWidth = 0;
	for (int index = 0; index < SIZE - 1; index++)
	{
		positionHeight = 0;

		psychicsArray[index].setPosition(sf::Vector2f(m_widthDesktop / 31 + positionWidth + width, m_heightDesktop / static_cast <float>(5.8) + height + positionHeight));
		gameWindow.draw(psychicsArray[index]);

		clueSetArray[index].setPosition(sf::Vector2f(m_widthDesktop / static_cast <float>(6.88) + positionWidth + width, m_heightDesktop / 20 + height + positionHeight));
		gameWindow.draw(clueSetArray[index]);
		positionHeight += static_cast<uint16_t>(clueSetArray[index].getTexture()->getSize().y * clueSetArray[index].getScale().x + 15);
		clueSetArray[index + 4].setPosition(sf::Vector2f(m_widthDesktop / static_cast <float>(6.88) + positionWidth + width, m_heightDesktop / 20 + height + positionHeight));
		gameWindow.draw(clueSetArray[index + 4]);
		positionHeight += static_cast<uint16_t>(clueSetArray[index].getTexture()->getSize().y * clueSetArray[index].getScale().x + 15);
		clueSetArray[index + 8].setPosition(sf::Vector2f(m_widthDesktop / static_cast <float>(5.7) + positionWidth + width, m_heightDesktop / 20 + height + positionHeight));
		gameWindow.draw(clueSetArray[index + 8]);
		positionHeight += static_cast<uint16_t>(clueSetArray[index].getTexture()->getSize().y * clueSetArray[index].getScale().x + 15);
		positionWidth += static_cast<uint16_t>(clueSetArray[index].getTexture()->getSize().x * clueSetArray[index].getScale().x + (400 * static_cast <float>(0.55) * m_resolutionScale) + 15);
	}
}

void GhostBoard::showVisionCards(sf::Sprite visionArray[VISION_DECK_SIZE], const float& width, const float& height,
	sf::RenderWindow& gameWindow)
{
	uint16_t positionIndex = 0;
	for (int index = 0; index < VISION_DECK_SIZE; index++)
	{
		visionArray[index].setPosition(sf::Vector2f(m_widthDesktop / static_cast <float>(5.15) + positionIndex + width, m_heightDesktop / static_cast <float>(1.5) + height));
		gameWindow.draw(visionArray[index]);
		positionIndex += static_cast<uint16_t>(visionArray[index].getTexture()->getSize().x * visionArray[index].getScale().x + 15);
	}
}

void GhostBoard::InitializeBoard(Board& board, sf::RenderWindow& gameWindow, std::array<Psychic, PLAYERS_SIZE>& psychics,
	sf::Sprite& clock)
{
	write.open("GhostLog.txt", std::ios::app);

	GhostLogger ghostLogger(write);

	m_crowUsed = false;
	m_psychicNumber = 0;
	sf::Color initialColor;
	sf::Event eventGhostBoard;

	sf::Music crowEffect;
	crowEffect.openFromFile("./Audio/crowSound.ogg");
	crowEffect.setVolume(15);

	sf::Sprite auxCard, auxCard2;
	uint16_t nrSpace = 0, nrNum = 0;

	sf::Texture background;
	if (!background.loadFromFile("./Backgrounds/GameBoard.jpg"))
		std::cout << "Can't load image!";
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(background);

	initialColor = backgroundSprite.getColor();

	std::array<ClueCard, SIZE>auxArray;

	shuffleCards(auxArray, board.getSustepects(), m_suspectArray);
	shuffleCards(auxArray, board.getLocations(), m_locationArray);
	shuffleCards(auxArray, board.getWeapons(), m_weaponArray);

	for (uint16_t index = 0; index < PLAYERS_SIZE; index++)
	{
		m_psychics[index] = psychics[index].getPsychicImage();
		m_psychics[index].setScale(static_cast <float>(0.37) * m_resolutionScale, static_cast <float>(0.37) * m_resolutionScale);
	}

	for (int index = 0; index < SIZE - 1; index++)
	{
		m_clueSets[index] = m_suspectArray[index].getCardImage();
		m_clueSets[index + 4] = m_locationArray[index].getCardImage();
		m_clueSets[index + 8] = m_weaponArray[index].getCardImage();
	}

	sf::Texture crowTexture;
	if (!crowTexture.loadFromFile("./Buttons/CrowToken.png"))
		std::cout << "Can't load image!";
	m_crowSprite.setTexture(crowTexture);
	m_crowSprite.setPosition(static_cast<float>(m_widthDesktop - (m_widthDesktop / static_cast <float>(1.05))), static_cast<float>((m_heightDesktop - (m_heightDesktop / static_cast <float>(3.17)))));
	m_crowSprite.setScale(static_cast <float>(0.475) * m_resolutionScale, static_cast <float>(0.475) * m_resolutionScale);

	clock.setPosition((float)m_widthDesktop - (clock.getTexture()->getSize().x) * (static_cast <float>(0.31) * m_resolutionScale) - 10, static_cast<float>((m_heightDesktop - (m_heightDesktop / (static_cast <float>(3.5) * m_resolutionScale)))));

	m_visionDeck[m_selectedItemNumber].setScale(static_cast <float>(0.475) * m_resolutionScale, static_cast <float>(0.475) * m_resolutionScale);

	for (uint16_t index = 0; index < PLAYERS_SIZE; index++)
	{
		m_clueSets[(4 * (psychics[index].getPhase() - 1)) + index].setColor(initialColor);
	}

	sf::Font font;
	font.loadFromFile("./Buttons/ChrustyRock-ORLA.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString(getMessage(psychics));
	text.setPosition(390 * m_resolutionScale, static_cast<float>(m_heightDesktop) / static_cast <float>(1.85));
	text.setCharacterSize(40);
	text.setFillColor(sf::Color(218, 165, 32, 255));

	while (gameWindow.isOpen())
	{
		while (gameWindow.pollEvent(eventGhostBoard))
		{
			switch (eventGhostBoard.type)
			{
			case sf::Event::Closed:
				gameWindow.close();
				break;
			case sf::Event::KeyPressed:
			{
				switch (eventGhostBoard.key.code)
				{
				case sf::Keyboard::Escape:
				{
					gameWindow.close();
					break;
				}
				case sf::Keyboard::Left:
				{
					MoveLeft();
					break;
				}
				case sf::Keyboard::Right:
				{
					MoveRight();
					break;
				}
				case sf::Keyboard::A:
				{
					MoveLeft();
					break;
				}
				case sf::Keyboard::D:
				{
					MoveRight();
					break;
				}
				case sf::Keyboard::Space:
				{
					if (m_selectedItemNumber >= 0)
					{
						zoomVisionCard(nrSpace, auxCard);
					}
					break;
				}
				case sf::Keyboard::Num1:
				{
					zoomClueCard(nrNum, auxCard, 4 * (psychics[0].getPhase() - 1));
					break;
				}
				case sf::Keyboard::Num2:
				{
					zoomClueCard(nrNum, auxCard, 4 * (psychics[1].getPhase() - 1) + 1);
					break;
				}
				case sf::Keyboard::Num3:
				{
					zoomClueCard(nrNum, auxCard, 4 * (psychics[2].getPhase() - 1) + 2);
					break;
				}
				case sf::Keyboard::Num4:
				{
					zoomClueCard(nrNum, auxCard, 4 * (psychics[3].getPhase() - 1) + 3);
					break;
				}
				case sf::Keyboard::Enter:
				{
					if (psychics[m_psychicNumber].getPhase() != 4)
					{
						if (m_selectedItemNumber >= 0)
						{
							VisionCard auxCard(m_visionDeck[m_selectedItemNumber]);
							setUsedCard(auxCard);
							psychics[m_psychicNumber].setVisionCard(auxCard);
							ghostLogger.log("Vision card " + std::to_string(m_selectedItemNumber + 1) +
								" for player " + std::to_string(m_psychicNumber + 1), GhostLogger::Level::Info);
							m_visionDeck[m_selectedItemNumber] = getUnusedCard().getCardImage();
							m_visionDeck[m_selectedItemNumber].setScale(static_cast <float>(0.475) * m_resolutionScale, static_cast <float>(0.475) * m_resolutionScale);
							m_psychicNumber++;

							if (m_psychicNumber < 4)
							{
								text.setString(getMessage(psychics));
							}

							if (m_psychicNumber == 4)
							{
								m_visionDeck[m_selectedItemNumber].setScale(static_cast <float>(0.45) * m_resolutionScale, static_cast <float>(0.45) * m_resolutionScale);
								m_selectedItemNumber = 0;
								board.setUsedCards(Copy_spriteArray_to_visionArray());
								board.setUnusedCards(m_unusedCard);
								if (m_crowUsed == false)
								{
									ghostLogger.log("The crow wasn't used! Don't forgot to use your advantage.", GhostLogger::Level::Warning);
								}
								gameWindow.close();
							}
						}
						else
						{
							if (m_crowUsed == false)
							{
								crowEffect.play();
								for (int index = 0; index < 7; index++)
								{
									VisionCard auxCard(m_visionDeck[index]);
									setUsedCard(auxCard);
									m_visionDeck[index] = getUnusedCard().getCardImage();
									m_visionDeck[index].setScale(static_cast <float>(0.45) * m_resolutionScale, static_cast <float>(0.45) * m_resolutionScale);
								}
								m_crowUsed = true;
								ghostLogger.log("The crow was used!", GhostLogger::Level::Info);
								m_visionDeck[++m_selectedItemNumber].setScale(static_cast <float>(0.475) * m_resolutionScale, static_cast <float>(0.475) * m_resolutionScale);
							}
						}
					}
					else
					{
						m_psychicNumber++;
						if (m_psychicNumber < 4)
						{
							text.setString(getMessage(psychics));
						}
						if (m_psychicNumber == 4)
						{
							board.setUsedCards(Copy_spriteArray_to_visionArray());
							board.setUnusedCards(m_unusedCard);
							gameWindow.close();
						}
					}
					break;
				}
				}
				break;
			}
			}
			gameWindow.clear();
			gameWindow.draw(backgroundSprite);
			gameWindow.draw(text);
			showCards(m_clueSets, m_psychics, 0, 0, gameWindow);
			showVisionCards(m_visionDeck, 10, 0, gameWindow);
			gameWindow.draw(m_crowSprite);
			gameWindow.draw(clock);
			if (nrSpace == 1 || nrNum == 1)
			{
				gameWindow.draw(auxCard);
			}
			gameWindow.display();
		}
	}
	write << std::endl;
	write.close();
}

void GhostBoard::MoveLeft()
{
	if (m_selectedItemNumber != -1)
	{
		if (m_crowUsed == false)
		{
			if (m_selectedItemNumber != 0)
			{
				m_visionDeck[m_selectedItemNumber].setScale(static_cast <float>(0.45) * m_resolutionScale, static_cast <float>(0.45) * m_resolutionScale);
				m_selectedItemNumber--;
				m_visionDeck[m_selectedItemNumber].setScale(static_cast <float>(0.475) * m_resolutionScale, static_cast <float>(0.475) * m_resolutionScale);
			}
			else
				if (m_selectedItemNumber == 0)
				{
					m_visionDeck[m_selectedItemNumber].setScale(static_cast <float>(0.45) * m_resolutionScale, static_cast <float>(0.45) * m_resolutionScale);
					m_selectedItemNumber--;
					m_crowSprite.setScale(static_cast <float>(0.5) * m_resolutionScale, static_cast <float>(0.5) * m_resolutionScale);
				}
		}
		else
		{
			if (m_selectedItemNumber != 0)
			{
				m_visionDeck[m_selectedItemNumber].setScale(static_cast <float>(0.45) * m_resolutionScale, static_cast <float>(0.45) * m_resolutionScale);
				m_selectedItemNumber--;
				m_visionDeck[m_selectedItemNumber].setScale(static_cast <float>(0.475) * m_resolutionScale, static_cast <float>(0.475) * m_resolutionScale);
			}
		}
	}
}

void GhostBoard::MoveRight()
{
	if (m_selectedItemNumber == -1)
	{
		m_crowSprite.setScale(static_cast <float>(0.475) * m_resolutionScale, static_cast <float>(0.475) * m_resolutionScale);
		m_selectedItemNumber++;
		m_visionDeck[m_selectedItemNumber].setScale(static_cast <float>(0.475) * m_resolutionScale, static_cast <float>(0.475) * m_resolutionScale);
	}
	else
		if (m_selectedItemNumber + 1 < VISION_DECK_SIZE)
		{
			m_visionDeck[m_selectedItemNumber].setScale(static_cast <float>(0.45) * m_resolutionScale, static_cast <float>(0.45) * m_resolutionScale);
			m_selectedItemNumber++;
			m_visionDeck[m_selectedItemNumber].setScale(static_cast <float>(0.475) * m_resolutionScale, static_cast <float>(0.475) * m_resolutionScale);
		}

}

GhostBoard::GhostBoard(Board& board)
	:m_heightDesktop(sf::VideoMode::getDesktopMode().height), m_widthDesktop(sf::VideoMode::getDesktopMode().width),
	m_resolutionScale(static_cast<float>(sf::VideoMode::getDesktopMode().width) / 1920)
{
	static const float resolutionScale = static_cast<float>(sf::VideoMode::getDesktopMode().width) / 1920;
	m_selectedItemNumber = 0;
	std::array<VisionCard, VISION_DECK_SIZE> auxVision;
	auxVision = board.getVisions();
	Copy_Array_to_Sprite(board.getVisions(), m_visionDeck);

	m_unusedCard = board.getUnusedCard();
}

GhostBoard::GhostBoard()
	:m_crowUsed(false),m_psychicNumber(0),m_resolutionScale(static_cast<float>(sf::VideoMode::getDesktopMode().width) / 1920),
	m_heightDesktop(sf::VideoMode::getDesktopMode().height), m_widthDesktop(sf::VideoMode::getDesktopMode().width),m_selectedItemNumber(0)
{
}

GhostBoard::~GhostBoard()
{
}

VisionCard GhostBoard::getUnusedCard()
{
	VisionCard auxCard = m_unusedCard[0];
	m_unusedCard.erase(m_unusedCard.begin());
	return auxCard;
}

void GhostBoard::setChosenCard(sf::Sprite image)
{
	m_chosenCards.push_back(image);
}

void GhostBoard::checkCards(std::array<Psychic, PLAYERS_SIZE>& psychics)
{
	for (int index = 0; index < PLAYERS_SIZE; index++)
	{
		int position = (4 * (psychics[index].getPhase() - 1)) + index;

		if (m_clueSets[position].getTexture() == m_chosenCards[index].getTexture())
		{
			psychics[index].IncreasePhase();
			psychics[index].clearVisions();
			psychics[index].addInClueSet(m_chosenCards[index]);
			psychics[index].addPoints(1);
		}
	}
	m_chosenCards.clear();
}

void GhostBoard::zoomVisionCard(uint16_t& nrSpace, sf::Sprite& card)
{
	nrSpace++;
	if (nrSpace == 1)
	{
		card = m_visionDeck[m_selectedItemNumber];
		card.setColor(m_visionDeck[m_selectedItemNumber].getColor());
		card.setScale(m_resolutionScale, m_resolutionScale);
		card.setPosition(sf::Vector2f(m_widthDesktop / 2 - static_cast<float>(card.getTexture()->getSize().x) / 2,
			m_heightDesktop / 2 - static_cast<float>(card.getTexture()->getSize().y) / 2));
	}
	if (nrSpace == 2)
	{
		m_visionDeck[m_selectedItemNumber].setScale(static_cast<float>(0.475) * m_resolutionScale, static_cast<float>(0.475) * m_resolutionScale);
		card.setColor(sf::Color(0, 0, 0, 0));
		nrSpace = 0;
	}
}

void GhostBoard::zoomClueCard(uint16_t& nrNum, sf::Sprite& card, const uint16_t& position)
{
	if (position < 12)
	{
		nrNum++;
		if (nrNum == 1)
		{
			card = m_clueSets[position];
			card.setColor(m_clueSets[position].getColor());
			card.setScale(m_resolutionScale, m_resolutionScale);
			card.setPosition(sf::Vector2f(m_widthDesktop / 2 - static_cast<float>(card.getTexture()->getSize().x) / 2,
				m_heightDesktop / 2 - static_cast<float>(card.getTexture()->getSize().y) / 2));
		}
		if (nrNum == 2)
		{
			m_clueSets[position].setScale(static_cast<float>(0.28) * m_resolutionScale, static_cast<float>(0.28) * m_resolutionScale);
			card.setColor(sf::Color(0, 0, 0, 0));
			nrNum = 0;
		}
	}
}

void GhostBoard::shuffleCards(std::array<ClueCard, SIZE>auxArray, std::array<ClueCard, SIZE>clueDeck, std::array<ClueCard,SIZE>&spriteDeck)
{
	auxArray = clueDeck;
	std::random_shuffle(auxArray.begin(), auxArray.end());
	for (int index = 0; index < SIZE - 1; index++)
	{
		spriteDeck[index] = clueDeck[index];
		spriteDeck[index].setCardScale(static_cast <float>(0.28) * m_resolutionScale, static_cast <float>(0.28) * m_resolutionScale);
		spriteDeck[index].setCardColor(sf::Color(128, 128, 128, 190));
	}
}

void GhostBoard::setUsedCard(VisionCard& card)
{
	m_usedCard.push_back(card);
	if (m_unusedCard.size() == 0)
	{
		std::random_shuffle(m_usedCard.begin(), m_usedCard.end());
		m_unusedCard = m_usedCard;
		m_usedCard.clear();
	}
}
