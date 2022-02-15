#include "PlayerBoardPhase2.h"

PlayerBoardPhase2::PlayerBoardPhase2()
	:m_selectedItemNumber(0), m_NumberOfVotes(0), m_heightDesktop(sf::VideoMode::getDesktopMode().height),
	m_widthDesktop(sf::VideoMode::getDesktopMode().width), m_resolutionScale((float)sf::VideoMode::getDesktopMode().width / 1920)
{
}

void PlayerBoardPhase2::MoveLeft()
{
	if (m_selectedItemNumber > 0)
	{
		{
			rescaleSets(static_cast<float>(0.29));
			m_selectedItemNumber--;
			rescaleSets(static_cast<float>(0.31));
		}
	}
}

void PlayerBoardPhase2::MoveRight()
{
	if (m_selectedItemNumber + 1 < PLAYERS_SIZE)
	{
		rescaleSets(static_cast<float>(0.29));
		m_selectedItemNumber++;
		rescaleSets(static_cast<float>(0.31));
	}
}

void PlayerBoardPhase2::PositionVote(sf::Sprite& voteImage)
{
	switch (m_selectedItemNumber)
	{
	case 0:
	{
		voteImage.setPosition(sf::Vector2f(static_cast <float>(m_widthDesktop / static_cast <float>(5.5)), static_cast <float>(m_heightDesktop / 16)));
		break;
	}
	case 1:
	{
		voteImage.setPosition(sf::Vector2f(static_cast <float>(m_widthDesktop / 3), static_cast <float>(m_heightDesktop / 16)));
		break;
	}
	case 2:
	{
		voteImage.setPosition(sf::Vector2f(static_cast <float>(m_widthDesktop / static_cast <float>(2.06)), static_cast <float>(m_heightDesktop / 16)));
		break;
	}
	case 3:
	{
		voteImage.setPosition(sf::Vector2f(static_cast <float>(m_widthDesktop / static_cast <float>(1.56)), static_cast <float>(m_heightDesktop / 16)));
		break;
	}
	default:
		break;
	}
}

void PlayerBoardPhase2::Intinialize(sf::RenderWindow& gameWindow, std::array<Psychic, PLAYERS_SIZE>& psychics, GhostBoardPhase2& ghost)
{
	uint16_t nrSpace = 0;
	uint16_t nrNum = 0;

	for (uint16_t index = 0; index < PLAYERS_SIZE; index++)
	{
		m_psychics[index] = psychics[index].getPsychicImage();
		m_psychics[index].setPsychicScale(static_cast<float>(0.4 * m_resolutionScale), static_cast<float>(0.4 * m_resolutionScale));
	}

	for (uint16_t index = 0; index < NUMBER_OF_FINAL_VISIONS; index++)
		m_finalVisionSet[index] = ghost.getFinalVisions().at(index);

	for (uint16_t index = 0; index < PLAYERS_SIZE; index++)
	{
		m_clueSets[index].setCardImage(psychics[index].getClueSets().at(0));
		m_clueSets[index].setCardScale(static_cast <float>(0.29 * m_resolutionScale), static_cast <float>(0.29 * m_resolutionScale));
		m_clueSets[index + 4].setCardImage(psychics[index].getClueSets().at(1)) ;
		m_clueSets[index + 4].setCardScale(static_cast <float>(0.29 * m_resolutionScale), static_cast <float>(0.29 * m_resolutionScale));
		m_clueSets[index + 8].setCardImage(psychics[index].getClueSets().at(2)) ;
		m_clueSets[index + 8].setCardScale(static_cast <float>(0.29 * m_resolutionScale), static_cast <float>(0.29 * m_resolutionScale));
	}

	m_clueSets[0].setCardScale(static_cast <float>(0.31 * m_resolutionScale), static_cast <float>(0.31 * m_resolutionScale));
	m_clueSets[4].setCardScale(static_cast <float>(0.31 * m_resolutionScale), static_cast <float>(0.31 * m_resolutionScale));
	m_clueSets[8].setCardScale(static_cast <float>(0.31 * m_resolutionScale), static_cast <float>(0.31 * m_resolutionScale));

	sf::Texture background;
	if (!background.loadFromFile("./Backgrounds/GameBoard.jpg"))
		std::cout << "Can't load image!";


	sf::Sprite auxCard;
	sf::Sprite auxSuspect;
	sf::Sprite auxLocation;
	sf::Sprite auxWeapon;
	sf::Sprite backgroundSP;
	backgroundSP.setTexture(background);
	backgroundSP.setScale(m_resolutionScale, m_resolutionScale);

	sf::Texture vote, vote2, vote3;
	if (!vote.loadFromFile("./Buttons/VoteButton2.png"))
		std::cout << "Can't load image!";
	if (!vote2.loadFromFile("./Buttons/VoteButton.png"))
		std::cout << "Can't load image!";
	if (!vote3.loadFromFile("./Buttons/VoteButton3.png"))
		std::cout << "Can't load image!";

	sf::Sprite voteSP;
	voteSP.setTexture(vote);
	voteSP.setScale(m_resolutionScale, m_resolutionScale);

	sf::Sprite voteSP2;
	voteSP2.setTexture(vote2);
	voteSP2.setScale(m_resolutionScale, m_resolutionScale);

	sf::Sprite voteSP3;
	voteSP3.setTexture(vote3);
	voteSP3.setScale(m_resolutionScale, m_resolutionScale);

	sf::Texture resultsTexture;
	if (!resultsTexture.loadFromFile("./Buttons/ResultsButton.png"))
		std::cout << "Can't load image!";
	sf::Sprite resultButtonSP;
	resultButtonSP.setTexture(resultsTexture);
	resultButtonSP.setScale(m_resolutionScale * static_cast<float>(0.8), m_resolutionScale * static_cast<float>(0.8));
	resultButtonSP.setPosition((m_widthDesktop - (m_widthDesktop / static_cast <float>(3.7))), (float)((m_heightDesktop - (m_heightDesktop / 4))));


	bool checkDraw = false;

	sf::Font font;
	font.loadFromFile("./Buttons/ChrustyRock-ORLA.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color(218, 165, 32, 255));
	text.setPosition(390 * m_resolutionScale, m_heightDesktop / static_cast <float>(1.85));
	text.setString(getText());

	sf::Event playerBoardPhase2Event;

	std::pair<uint16_t, uint16_t>voteResult;

	while (gameWindow.isOpen())
	{
		while (gameWindow.pollEvent(playerBoardPhase2Event))
		{
			switch (playerBoardPhase2Event.type)
			{
			case sf::Event::Closed:
				gameWindow.close();
				break;
			case sf::Event::KeyPressed:
			{
				switch (playerBoardPhase2Event.key.code)
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
					auxSuspect = m_clueSets[m_selectedItemNumber].getCardImage();
					auxLocation = m_clueSets[m_selectedItemNumber + 4].getCardImage();
					auxWeapon = m_clueSets[m_selectedItemNumber + 8].getCardImage();
					zoomClueCards(nrSpace, auxSuspect, auxLocation, auxWeapon);
					break;
				}
				case sf::Keyboard::Num1:
				{
					auxCard = m_finalVisionSet[0].getCardImage();
					zoomVisionCard(nrNum, auxCard);
					break;
				}
				case sf::Keyboard::Num2:
				{
					auxCard = m_finalVisionSet[1].getCardImage();
					zoomVisionCard(nrNum, auxCard);
					break;
				}
				case sf::Keyboard::Num3:
				{
					auxCard = m_finalVisionSet[2].getCardImage();
					zoomVisionCard(nrNum, auxCard);
					break;
				}
				case sf::Keyboard::Enter:
				{
					m_NumberOfVotes++;

					if (m_NumberOfVotes == 1)
					{
						text.setString(getText());
						voteResult.first = static_cast<uint16_t>(m_selectedItemNumber);
						voteResult.second = psychics[0].getPoints() + psychics[1].getPoints();
						PositionVote(voteSP);
						rescaleSets(static_cast<float>(0.29));
						m_selectedItemNumber = 0;
						rescaleSets(static_cast<float>(0.31));
					}
					if (m_NumberOfVotes == 2)
					{
						text.setFillColor(sf::Color(0, 0, 0, 0));
						rescaleSets(static_cast<float>(0.29));
						if (voteResult.first == m_selectedItemNumber)
						{
							checkDraw = true;
							m_voteIndex = voteResult.first;
							PositionVote(voteSP3);
						}
						else
						{
							if (voteResult.second > psychics[2].getPoints() + psychics[3].getPoints())
							{
								m_voteIndex = voteResult.first;
							}
							else
							{
								m_voteIndex = static_cast<uint16_t>(m_selectedItemNumber);
							}
						}
						PositionVote(voteSP2);
					}
					if (m_NumberOfVotes == 3)
					{
						gameWindow.close();
					}
					break;
				}
				}
			}
			}
		}
		gameWindow.clear();
		gameWindow.draw(backgroundSP);
		showCards(gameWindow, m_clueSets, 0, 0);
		showVisionCards(gameWindow, m_finalVisionSet, 0, 0);
		showPsychics(gameWindow, m_psychics, 0, 0);
		gameWindow.draw(text);
		if (nrNum == 1)
		{
			gameWindow.draw(auxCard);
		}
		if (nrSpace == 1)
		{
			gameWindow.draw(auxSuspect);
			gameWindow.draw(auxLocation);
			gameWindow.draw(auxWeapon);
		}
		if (m_NumberOfVotes == 2)
		{
			if (checkDraw == false)
			{
				gameWindow.draw(voteSP);
				gameWindow.draw(voteSP2);
			}
			else
			{
				gameWindow.draw(voteSP3);
			}
			gameWindow.draw(resultButtonSP);
		}
		gameWindow.display();
	}
}

void PlayerBoardPhase2::showCards(sf::RenderWindow& gameWindow, std::array<ClueCard, CLUE_SET_SIZE>&clueSets, const float& width, const float& height)
{
	uint16_t positionHeight;
	uint16_t positionWidth = 0;
	for (int index = 0; index < PLAYERS_SIZE; index++)
	{
		positionHeight = 0;

		clueSets[index].setCardPosition(sf::Vector2f(m_widthDesktop / 5 + positionWidth + width, m_heightDesktop / 20 + height + positionHeight));
		gameWindow.draw(clueSets[index].getCardImage());
		positionHeight += static_cast<uint16_t>(clueSets[index].getCardImage().getTexture()->getSize().y * clueSets[index].getCardImage().getScale().x + 15);
		clueSets[index + 4].setCardPosition(sf::Vector2f(m_widthDesktop / 5 + positionWidth + width, m_heightDesktop / 20 + height + positionHeight));
		gameWindow.draw(clueSets[index + 4].getCardImage());
		positionHeight += static_cast<uint16_t>(clueSets[index].getCardImage().getTexture()->getSize().y * clueSets[index].getCardImage().getScale().x + 15);
		clueSets[index + 8].setCardPosition(sf::Vector2f(m_widthDesktop / static_cast <float>(4.2) + positionWidth + width, m_heightDesktop / 20 + height + positionHeight));
		gameWindow.draw(clueSets[index + 8].getCardImage());

		positionHeight += static_cast<uint16_t>(clueSets[index].getCardImage().getTexture()->getSize().y * clueSets[index].getCardImage().getScale().x + 15);
		positionWidth += static_cast<uint16_t>(clueSets[index].getCardImage().getTexture()->getSize().x * clueSets[index].getCardImage().getScale().x + 60 * m_resolutionScale);
	}
}

void PlayerBoardPhase2::showVisionCards(sf::RenderWindow& gameWindow, std::array<VisionCard, NUMBER_OF_FINAL_VISIONS>&finalVisionSet, const float& width, const float& height)
{
	uint16_t positionWidth = 0;
	for (int index = 0; index < NUMBER_OF_FINAL_VISIONS; index++)
	{
		finalVisionSet[index].setCardPosition(sf::Vector2f(m_widthDesktop / static_cast <float>(2.95) + positionWidth + width, m_heightDesktop / static_cast <float>(1.5) + height));
		gameWindow.draw(m_finalVisionSet[index].getCardImage());
		positionWidth += static_cast<uint16_t>(finalVisionSet[index].getCardImage().getTexture()->getSize().x * finalVisionSet[index].getCardImage().getScale().x + 60 * m_resolutionScale);
	}
}

void PlayerBoardPhase2::showPsychics(sf::RenderWindow& gameWindow, std::array<Psychic, PLAYERS_SIZE>&psychics, const float& width, const float& height)
{
	uint16_t positionHeight = 0;
	if (m_NumberOfVotes == 0)
	{
		psychics[0].setPsychicPosition(sf::Vector2f(m_widthDesktop / 16 + width, m_heightDesktop / static_cast <float>(1.75) + height + positionHeight));
		gameWindow.draw(m_psychics[0].getPsychicImage());
		positionHeight += static_cast<uint16_t>(230 * m_resolutionScale);
		psychics[1].setPsychicPosition(sf::Vector2f(m_widthDesktop / 16 + width, m_heightDesktop / static_cast <float>(1.75) + height + positionHeight));
		gameWindow.draw(m_psychics[1].getPsychicImage());
	}
	else
	{
		psychics[2].setPsychicPosition(sf::Vector2f(m_widthDesktop / 16 + width, m_heightDesktop / static_cast <float>(1.75) + height + positionHeight));
		gameWindow.draw(m_psychics[2].getPsychicImage());
		positionHeight += static_cast<uint16_t>(230 * m_resolutionScale);
		psychics[3].setPsychicPosition(sf::Vector2f(m_widthDesktop / 16 + width, m_heightDesktop / static_cast <float>(1.75) + height + positionHeight));
		gameWindow.draw(m_psychics[3].getPsychicImage());
	}

}

void PlayerBoardPhase2::zoomVisionCard(uint16_t& nrNum, sf::Sprite& card)
{
	nrNum++;
	if (nrNum == 1)
	{
		card.setColor(m_finalVisionSet[0].getCardImage().getColor());
		card.setScale(m_resolutionScale, m_resolutionScale);
		card.setPosition(sf::Vector2f(m_widthDesktop / 2 - static_cast<float>(card.getTexture()->getSize().x) / 2,
			m_heightDesktop / 2 - static_cast<float>(card.getTexture()->getSize().y) / 2));
	}
	if (nrNum == 2)
	{
		card.setScale(static_cast<float>(0.31) * m_resolutionScale, static_cast<float>(0.31) * m_resolutionScale);
		card.setColor(sf::Color(0, 0, 0, 0));
		nrNum = 0;
	}
}

void PlayerBoardPhase2::zoomClueCards(uint16_t& nrSpace, sf::Sprite& suspect, sf::Sprite& location, sf::Sprite& weapon)
{
	nrSpace++;
	if (nrSpace == 1)
	{
		suspect.setColor(m_finalVisionSet[0].getCardImage().getColor());
		suspect.setScale(m_resolutionScale * static_cast<float>(0.75), m_resolutionScale * static_cast<float>(0.75));
		suspect.setPosition(sf::Vector2f(m_widthDesktop / static_cast <float>(20),
			m_heightDesktop / static_cast <float>(2) - static_cast<float>(suspect.getTexture()->getSize().y) / 2));

		location.setColor(m_finalVisionSet[0].getCardImage().getColor());
		location.setScale(m_resolutionScale * static_cast<float>(0.75), m_resolutionScale * static_cast<float>(0.75));
		location.setPosition(sf::Vector2f(m_widthDesktop / static_cast<float>(2.35),
			m_heightDesktop / 2 - static_cast<float>(location.getTexture()->getSize().y) / 2));

		weapon.setColor(m_finalVisionSet[0].getCardImage().getColor());
		weapon.setScale(m_resolutionScale * static_cast<float>(0.75), m_resolutionScale * static_cast<float>(0.75));
		weapon.setPosition(sf::Vector2f(m_widthDesktop / static_cast<float>(1.239),
			m_heightDesktop / 2 - static_cast<float>(weapon.getTexture()->getSize().y) / 2));
	}
	if (nrSpace == 2)
	{
		suspect.setScale(static_cast<float>(0.31) * m_resolutionScale, static_cast<float>(0.31) * m_resolutionScale);
		suspect.setColor(sf::Color(0, 0, 0, 0));

		location.setScale(static_cast<float>(0.31) * m_resolutionScale, static_cast<float>(0.31) * m_resolutionScale);
		location.setColor(sf::Color(0, 0, 0, 0));

		weapon.setScale(static_cast<float>(0.31) * m_resolutionScale, static_cast<float>(0.31) * m_resolutionScale);
		weapon.setColor(sf::Color(0, 0, 0, 0));

		nrSpace = 0;
	}
}

void PlayerBoardPhase2::rescaleSets(const float& scale)
{
	m_clueSets[m_selectedItemNumber].setCardScale(scale * m_resolutionScale, scale * m_resolutionScale);
	m_clueSets[m_selectedItemNumber + 4].setCardScale(scale * m_resolutionScale, scale * m_resolutionScale);
	m_clueSets[m_selectedItemNumber + 8].setCardScale(scale * m_resolutionScale, scale * m_resolutionScale);
}

uint16_t PlayerBoardPhase2::getVoteIndex()
{
	return m_voteIndex;
}

std::string PlayerBoardPhase2::getText()
{
	std::map<uint64_t, std::string> mapDecision = {
		{0,"First player must choose the correct clue set."},
		{1,"Second player must choose the correct clue set."}
	};
	return mapDecision[m_NumberOfVotes];
}

PlayerBoardPhase2::~PlayerBoardPhase2()
{
}
