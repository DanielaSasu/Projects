#include "GhostBoardPhase2.h"

std::string GhostBoardPhase2::getMessage()
{
	std::map<uint64_t, std::string> mapDecision = {
		{0,"Choose a vision card for the suspect."},
		{1,"Choose a vision card for the location."},
		{2,"Choose a vision card for the weapon."}
	};
	return mapDecision[m_finalVisionNumber];
}

void GhostBoardPhase2::arrangeClueSets(std::array<ClueCard, SIZE>&clueSet)
{
	for (uint16_t index = 0; index < SIZE; index++)
	{
		clueSet[index].setCardScale(static_cast<float>(0.28) * m_resolutionScale, static_cast<float>(0.28) * m_resolutionScale);
		clueSet[index].setCardColor(sf::Color(128, 128, 128, 190));
	}
}

void GhostBoardPhase2::showCards(std::array<ClueCard, CLUE_SET_SIZE>clueSetArray, std::array<Psychic,PLAYERS_SIZE>psychicArray, const float& width, const float& height, sf::RenderWindow& gameWindow)
{
	uint16_t positionHeight;
	uint16_t positionWidth = 0;
	for (int index = 0; index < SIZE - 1; index++)
	{
		positionHeight = 0;

		psychicArray[index].setPsychicPosition(sf::Vector2f(m_widthDesktop / 31 + positionWidth + width, m_heightDesktop / static_cast <float>(5.8) + height + positionHeight));
		gameWindow.draw(psychicArray[index].getPsychicImage());

		clueSetArray[index].setCardPosition(sf::Vector2f(m_widthDesktop / static_cast <float>(6.88) + positionWidth + width, m_heightDesktop / 20 + height + positionHeight));
		gameWindow.draw(clueSetArray[index].getCardImage());
		positionHeight += static_cast<uint16_t>(clueSetArray[index].getCardImage().getTexture()->getSize().y * clueSetArray[index].getCardImage().getScale().x + 15);
		clueSetArray[index + 4].setCardPosition(sf::Vector2f(m_widthDesktop / static_cast <float>(6.88) + positionWidth + width, m_heightDesktop / 20 + height + positionHeight));
		gameWindow.draw(clueSetArray[index + 4].getCardImage());
		positionHeight += static_cast<uint16_t>(clueSetArray[index].getCardImage().getTexture()->getSize().y * clueSetArray[index].getCardImage().getScale().x + 15);
		clueSetArray[index + 8].setCardPosition(sf::Vector2f(m_widthDesktop / static_cast <float>(5.7) + positionWidth + width, m_heightDesktop / 20 + height + positionHeight));
		gameWindow.draw(clueSetArray[index + 8].getCardImage());
		positionHeight += static_cast<uint16_t>(clueSetArray[index].getCardImage().getTexture()->getSize().y * clueSetArray[index].getCardImage().getScale().x + 15);
		positionWidth += static_cast<uint16_t>(clueSetArray[index].getCardImage().getTexture()->getSize().x * clueSetArray[index].getCardImage().getScale().x + (400 * static_cast <float>(0.55)* m_resolutionScale) + 15);
	}
}

void GhostBoardPhase2::showVisionCards(std::array<VisionCard,VISION_DECK_SIZE>visionCardArray, const float& width, const float& height, sf::RenderWindow& gameWindow)
{
	uint16_t positionIndex = 0;
	for (int index = 0; index < VISION_DECK_SIZE; index++)
	{
		visionCardArray[index].setCardPosition(sf::Vector2f(m_widthDesktop / (float)5.15 + positionIndex + width, m_heightDesktop / static_cast <float>(1.5) + height));
		gameWindow.draw(visionCardArray[index].getCardImage());
		positionIndex += static_cast<uint16_t>(visionCardArray[index].getCardImage().getTexture()->getSize().x * visionCardArray[index].getCardImage().getScale().x + 15);
	}
}

void GhostBoardPhase2::InitializeBoard(Board board, sf::RenderWindow& gameWindow, std::array<Psychic, PLAYERS_SIZE>& psychics)
{
	m_crowUsed = false;
	m_finalVisionNumber = 0;
	m_selectedClueSet = 0;
	sf::Event eventGhostBoard;

	sf::Music crowEffect;
	crowEffect.openFromFile("./Audio/crowSound.ogg");
	crowEffect.setVolume(15);

	sf::Sprite auxCard;
	uint16_t nrSpace = 0;
	uint16_t nrNum = 0;

	sf::Texture background;
	if (!background.loadFromFile("./Backgrounds/GameBoard.jpg"))
		std::cout << "Can't load image!";
	sf::Sprite backgroundSp;
	backgroundSp.setTexture(background);

	m_initialColor = backgroundSp.getColor();

	m_suspectArray = board.getSustepects();
	m_locationArray = board.getLocations();
	m_weaponArray = board.getWeapons();

	arrangeClueSets(m_suspectArray);
	arrangeClueSets(m_locationArray);
	arrangeClueSets(m_weaponArray);

	for (uint16_t index = 0; index < PLAYERS_SIZE; index++)
	{
		m_psychics[index] = psychics[index];
		m_psychics[index].setPsychicScale(static_cast <float>(0.37)* m_resolutionScale, static_cast <float>(0.37)* m_resolutionScale);
	}

	for (int index = 0; index < SIZE - 1; index++)
	{
		m_clueSets[index] = m_suspectArray[index];
		m_clueSets[index + 4] = m_locationArray[index];
		m_clueSets[index + 8] = m_weaponArray[index];
	}

	sf::Texture crowTexture;
	if (!crowTexture.loadFromFile("./Buttons/CrowToken.png"))
		std::cout << "Can't load image!";
	m_crowSprite.setTexture(crowTexture);
	m_crowSprite.setPosition(static_cast <float>(m_widthDesktop - (m_widthDesktop / static_cast <float>(1.05))), static_cast <float>((m_heightDesktop - (m_heightDesktop / static_cast <float>(3.17)))));
	m_crowSprite.setScale(static_cast <float>(0.475)* m_resolutionScale, static_cast <float>(0.475)* m_resolutionScale);

	m_clueSets[m_selectedClueSet].setCardColor(m_initialColor);
	m_clueSets[m_selectedClueSet + 4].setCardColor(m_initialColor);
	m_clueSets[m_selectedClueSet + 8].setCardColor(m_initialColor);

	sf::Font font;
	font.loadFromFile("./Buttons/ChrustyRock-ORLA.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Choose the correct clue set.");
	text.setPosition(390 * m_resolutionScale, static_cast <float>(m_heightDesktop / static_cast <float>(1.85)));
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
					if (m_selectedItemNumber >= 0 && m_indexLine > 0)
					{
						auxCard = m_visionDeck[m_selectedItemNumber].getCardImage();
						zoomVisionCards(nrSpace, auxCard);
					}
					break;
				}
				case sf::Keyboard::Num1:
				{
					auxCard = m_suspectArray[m_selectedClueSet].getCardImage();
					zoomClueCards(nrNum, auxCard);
					break;
				}
				case sf::Keyboard::Num2:
				{
					auxCard = m_locationArray[m_selectedClueSet].getCardImage();
					zoomClueCards(nrNum, auxCard);
					break;
				}
				case sf::Keyboard::Num3:
				{
					auxCard = m_weaponArray[m_selectedClueSet].getCardImage();
					zoomClueCards(nrNum, auxCard);
					break;
				}
				case sf::Keyboard::Enter:
				{
					if (m_indexLine == 0)
					{
						m_correctClueSetIndex = static_cast<uint16_t>(m_selectedClueSet);
						m_indexLine++;
						m_visionDeck[m_selectedItemNumber].setCardScale(static_cast <float>(0.475)* m_resolutionScale, static_cast <float>(0.475)* m_resolutionScale);
						text.setString(getMessage());
					}
					else
					{

						if (m_selectedItemNumber >= 0) {
							VisionCard auxCard(m_visionDeck[m_selectedItemNumber]);
							setUsedCard(auxCard);
							m_FinalVisionSet.push_back(m_visionDeck[m_selectedItemNumber].getCardImage());

							m_visionDeck[m_selectedItemNumber] = getUnusedCard().getCardImage();
							m_visionDeck[m_selectedItemNumber].setCardScale(static_cast <float>(0.475)* m_resolutionScale, static_cast <float>(0.475)* m_resolutionScale);

							m_finalVisionNumber++;
							if (m_finalVisionNumber < 3)
							{
								text.setString(getMessage());
							}

							if (m_finalVisionNumber == 3)
								gameWindow.close();
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
									m_visionDeck[index].setCardScale(static_cast <float>(0.45)* m_resolutionScale, static_cast <float>(0.45)* m_resolutionScale);
								}
								m_crowUsed = true;
								m_visionDeck[++m_selectedItemNumber].setCardScale(static_cast <float>(0.475)* m_resolutionScale, static_cast <float>(0.475)* m_resolutionScale);
							}
						}
					}
					break;
				}
				}
				break;
			}
			}
			gameWindow.clear();
			gameWindow.draw(backgroundSp);
			gameWindow.draw(text);
			showCards(m_clueSets, m_psychics, 0, 0, gameWindow);
			showVisionCards(m_visionDeck, 10, 0, gameWindow);
			gameWindow.draw(m_crowSprite);
			if (nrSpace == 1 || nrNum == 1)
			{
				gameWindow.draw(auxCard);
			}
			gameWindow.display();
		}
	}
}

void GhostBoardPhase2::MoveLeft()
{
	if (m_indexLine == 0)
	{
		if (m_selectedClueSet != 0)
		{
			m_clueSets[m_selectedClueSet].setCardColor(sf::Color(128, 128, 128, 190));
			m_clueSets[m_selectedClueSet + 4].setCardColor(sf::Color(128, 128, 128, 190));
			m_clueSets[m_selectedClueSet + 8].setCardColor(sf::Color(128, 128, 128, 190));
			m_selectedClueSet--;
			m_clueSets[m_selectedClueSet].setCardColor(m_initialColor);
			m_clueSets[m_selectedClueSet + 4].setCardColor(m_initialColor);
			m_clueSets[m_selectedClueSet + 8].setCardColor(m_initialColor);
		}
	}
	else
	{
		if (m_selectedItemNumber != -1)
		{
			if (m_crowUsed == false)
			{
				if (m_selectedItemNumber != 0)
				{
					m_visionDeck[m_selectedItemNumber].setCardScale(static_cast <float>(0.45)* m_resolutionScale, static_cast <float>(0.45)* m_resolutionScale);
					m_selectedItemNumber--;
					m_visionDeck[m_selectedItemNumber].setCardScale(static_cast <float>(0.475)* m_resolutionScale, static_cast <float>(0.475)* m_resolutionScale);
				}
				else
					if (m_selectedItemNumber == 0)
					{
						m_visionDeck[m_selectedItemNumber].setCardScale(static_cast <float>(0.45)* m_resolutionScale, static_cast <float>(0.45)* m_resolutionScale);
						m_selectedItemNumber--;
						m_crowSprite.setScale(static_cast <float>(0.5)* m_resolutionScale, static_cast <float>(0.5)* m_resolutionScale);
					}
			}
			else
			{
				if (m_selectedItemNumber != 0)
				{
					m_visionDeck[m_selectedItemNumber].setCardScale(static_cast <float>(0.45)* m_resolutionScale, static_cast <float>(0.45)* m_resolutionScale);
					m_selectedItemNumber--;
					m_visionDeck[m_selectedItemNumber].setCardScale(static_cast <float>(0.475)* m_resolutionScale, static_cast <float>(0.475)* m_resolutionScale);
				}
			}
		}
	}
}

void GhostBoardPhase2::MoveRight()
{
	if (m_indexLine == 0)
	{
		if (m_selectedClueSet < PLAYERS_SIZE - 1)
		{
			m_clueSets[m_selectedClueSet].setCardColor(sf::Color(128, 128, 128, 190));
			m_clueSets[m_selectedClueSet + 4].setCardColor(sf::Color(128, 128, 128, 190));
			m_clueSets[m_selectedClueSet + 8].setCardColor(sf::Color(128, 128, 128, 190));
			m_selectedClueSet++;
			m_clueSets[m_selectedClueSet].setCardColor(m_initialColor);
			m_clueSets[m_selectedClueSet + 4].setCardColor(m_initialColor);
			m_clueSets[m_selectedClueSet + 8].setCardColor(m_initialColor);
		}
	}
	else
	{
		if (m_selectedItemNumber == -1)
		{
			m_crowSprite.setScale(static_cast <float>(0.475)* m_resolutionScale, static_cast <float>(0.475)* m_resolutionScale);
			m_selectedItemNumber++;
			m_visionDeck[m_selectedItemNumber].setCardScale(static_cast <float>(0.475)* m_resolutionScale, static_cast <float>(0.475)* m_resolutionScale);
		}
		else
			if (m_selectedItemNumber + 1 < VISION_DECK_SIZE)
			{
				m_visionDeck[m_selectedItemNumber].setCardScale(static_cast <float>(0.45)* m_resolutionScale, static_cast <float>(0.45)* m_resolutionScale);
				m_selectedItemNumber++;
				m_visionDeck[m_selectedItemNumber].setCardScale(static_cast <float>(0.475)* m_resolutionScale, static_cast <float>(0.475)* m_resolutionScale);
			}
	}
}

std::vector<VisionCard> GhostBoardPhase2::getFinalVisions()
{
	return m_FinalVisionSet;
}

uint16_t GhostBoardPhase2::getCorrectClueSetIndex()
{
	return m_correctClueSetIndex;
}

GhostBoardPhase2::GhostBoardPhase2(Board& board)
	:m_heightDesktop(sf::VideoMode::getDesktopMode().height), m_widthDesktop(sf::VideoMode::getDesktopMode().width), m_resolutionScale(static_cast <float>(sf::VideoMode::getDesktopMode().width) / 1920)
{
	m_selectedItemNumber = 0;
	std::array<VisionCard, VISION_DECK_SIZE> auxVis;
	auxVis = board.getVisions();
	m_visionDeck = auxVis;
	m_unusedCard = board.getUnusedCard();
}

GhostBoardPhase2::GhostBoardPhase2()
	:m_indexLine(0), m_heightDesktop(sf::VideoMode::getDesktopMode().height), m_widthDesktop(sf::VideoMode::getDesktopMode().width), 
	m_resolutionScale(static_cast <float>(sf::VideoMode::getDesktopMode().width) / 1920),m_correctClueSetIndex(1),m_crowUsed(false),
	m_finalVisionNumber(0),m_selectedItemNumber(0),m_selectedClueSet(0)
{
}

GhostBoardPhase2::~GhostBoardPhase2()
{
}

VisionCard GhostBoardPhase2::getUnusedCard()
{
	VisionCard auxCard = std::move(m_unusedCard[0]);
	m_unusedCard.erase(m_unusedCard.begin());
	return auxCard;
}

void GhostBoardPhase2::setChosenCard(sf::Sprite image)
{
	m_chosenCards.push_back(image);
}

void GhostBoardPhase2::checkCards(std::array<Psychic, PLAYERS_SIZE>& psychics)
{
	for (int index = 0; index < PLAYERS_SIZE; index++)
	{
		int position = (4 * (psychics[index].getPhase() - 1)) + index;

		if (m_clueSets[position].getCardImage().getTexture() == m_chosenCards[index].getTexture())
		{
			psychics[index].IncreasePhase();
			psychics[index].clearVisions();
			psychics[index].addInClueSet(m_chosenCards[index]);
		}
	}
	m_chosenCards.clear();
}

void GhostBoardPhase2::zoomVisionCards(uint16_t& nrSpace, sf::Sprite& card)
{
	nrSpace++;
	if (nrSpace == 1)
	{
		card = m_visionDeck[m_selectedItemNumber].getCardImage();
		card.setColor(m_visionDeck[m_selectedItemNumber].getCardImage().getColor());
		card.setScale(m_resolutionScale, m_resolutionScale);
		card.setPosition(sf::Vector2f(m_widthDesktop / 2 - static_cast<float>(card.getTexture()->getSize().x) / 2,
			m_heightDesktop / 2 - static_cast<float>(card.getTexture()->getSize().y) / 2));
	}
	if (nrSpace == 2)
	{
		m_visionDeck[m_selectedItemNumber].setCardScale(static_cast<float>(0.475)* m_resolutionScale, static_cast<float>(0.475)* m_resolutionScale);
		card.setColor(sf::Color(0, 0, 0, 0));
		nrSpace = 0;
	}
}

void GhostBoardPhase2::zoomClueCards(uint16_t& nrNum, sf::Sprite& card)
{
	nrNum++;
	if (nrNum == 1)
	{
		card.setColor(m_visionDeck[0].getCardImage().getColor());
		card.setScale(m_resolutionScale, m_resolutionScale);
		card.setPosition(sf::Vector2f(m_widthDesktop / 2 - static_cast<float>(card.getTexture()->getSize().x) / 2,
			m_heightDesktop / 2 - static_cast<float>(card.getTexture()->getSize().y) / 2));
	}
	if (nrNum == 2)
	{
		card.setScale(static_cast<float>(0.31)* m_resolutionScale, static_cast<float>(0.31)* m_resolutionScale);
		card.setColor(sf::Color(0, 0, 0, 0));
		nrNum = 0;
	}
}

void GhostBoardPhase2::setUsedCard(VisionCard& card)
{
	m_usedCard.push_back(card);
	if (m_unusedCard.size() == 0)
	{
		std::random_shuffle(m_usedCard.begin(), m_usedCard.end());
		m_unusedCard = m_usedCard;
		m_usedCard.clear();
	}
}
