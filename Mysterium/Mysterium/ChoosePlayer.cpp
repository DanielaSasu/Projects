#include "ChoosePlayer.h"

void ChoosePlayer::MoveLeft()
{
	if (m_selectedItemNumber > 1 &&	m_selectedItemNumber < 7)
	{
		m_spriteArray[m_selectedItemNumber].setScale(static_cast<float>(0.63) * m_resolutionScale, static_cast <float>(0.63) * m_resolutionScale);
		m_selectedItemNumber--;
		m_spriteArray[m_selectedItemNumber].setScale(static_cast <float>(0.66) * m_resolutionScale, static_cast <float>(0.66) * m_resolutionScale);
	}
}

void ChoosePlayer::MoveRight()
{
	if ( m_selectedItemNumber < 6)
	{
		m_spriteArray[m_selectedItemNumber].setScale(static_cast <float>(0.63) * m_resolutionScale, static_cast <float>(0.63) * m_resolutionScale);
		m_selectedItemNumber++;
		m_spriteArray[m_selectedItemNumber].setScale(static_cast <float>(0.66) * m_resolutionScale, static_cast <float>(0.66) * m_resolutionScale);
	}
}

void ChoosePlayer::readPsychics()
{
	float indexPosition = 0, indexPosition1 = 0;
	for (int index = 1; index < ARRAY_SIZE - 1; index++)
	{
		std::string imageName = "./Psychics/Psychic" + std::to_string(index) + ".png";

		if (!m_textureArray[index].loadFromFile(imageName))
			std::cout << "Can't load image!";
		m_spriteArray[index].setTexture(m_textureArray[index]);
		m_spriteArray[index].setScale(static_cast <float>(0.63)* m_resolutionScale, static_cast <float>(0.63)* m_resolutionScale);
		if (index <= 3)
		{
			m_spriteArray[index].setPosition(sf::Vector2f((m_widthDesktop / static_cast <float>(2.875) - (m_textureArray[index].getSize().x * m_resolutionScale) / 2)
				+ indexPosition, ((m_heightDesktop / 2 - (m_textureArray[index].getSize().y * m_resolutionScale) / 5) * static_cast <float>(0.70))));
			indexPosition = indexPosition + m_spriteArray[index].getTexture()->getSize().x * m_spriteArray[index].getScale().y + 25;
		}
		else
		{
			m_spriteArray[index].setPosition(sf::Vector2f((m_widthDesktop / static_cast <float>(2.875) - (m_textureArray[index].getSize().x * m_resolutionScale) / 2)
				+ indexPosition1, ((m_heightDesktop / 2 - (m_textureArray[index].getSize().y * m_resolutionScale) / 5) * static_cast <float>(0.70))
				+ m_spriteArray[1].getTexture()->getSize().y * m_spriteArray[index].getScale().y + 25));
			indexPosition1 = indexPosition1 + m_spriteArray[index].getTexture()->getSize().x * m_spriteArray[index].getScale().y + 25;
		}
	}
}

void ChoosePlayer::readButtons()
{
	if (!m_textureArray[0].loadFromFile("./Buttons/ChooseButton.png"))
		std::cout << "Can't load image!";
	m_spriteArray[0].setTexture(m_textureArray[0]);
	m_spriteArray[0].setScale(static_cast <float>(0.9)* m_resolutionScale, static_cast <float>(0.9)* m_resolutionScale);
	m_spriteArray[0].setPosition(sf::Vector2f(m_widthDesktop / 2 - (m_textureArray[0].getSize().x * static_cast <float>(0.95)* m_resolutionScale) / 2,
		(m_heightDesktop / static_cast <float>(5.5) - (m_textureArray[0].getSize().y * m_resolutionScale) / 2)* static_cast <float>(0.70)));

	if (!m_textureArray[ARRAY_SIZE - 1].loadFromFile("./Buttons/arrowButton.png"))
		std::cout << "Can't load image!";
	m_spriteArray[ARRAY_SIZE - 1].setTexture(m_textureArray[ARRAY_SIZE - 1]);
	m_spriteArray[ARRAY_SIZE - 1].setPosition(static_cast<float>(m_widthDesktop - (m_widthDesktop / 5)), static_cast<float>((m_heightDesktop - (m_heightDesktop / static_cast <float>(3.8)))));

}

void ChoosePlayer::readPsychicsInformation()
{
	for (uint16_t index = 0; index < PSYCHICS_NUMBER; index++)
	{
		std::string imageName = "./Psychics/PsychicId" + std::to_string(index + 1) + ".png";
		if (!m_informationTexture[index].loadFromFile(imageName))
			std::cout << "Can't load image!";
		m_psychicInformation[index].setTexture(m_informationTexture[index]);
		m_psychicInformation[index].setColor(sf::Color(0, 0, 0, 0));
	}
}

void ChoosePlayer::SelectPsychic(uint16_t& selectedPsychic)
{
	if (m_spriteArray[m_selectedItemNumber].getColor() != sf::Color(30, 0, 245, 255) && m_spriteArray[m_selectedItemNumber].getColor() != sf::Color::Red)
	{
		if (selectedPsychic < 2)
			m_spriteArray[m_selectedItemNumber].setColor(sf::Color(30, 0, 245, 255));
		else
			m_spriteArray[m_selectedItemNumber].setColor(sf::Color::Red);
		m_playersSelected++;
	}
}

void ChoosePlayer::zoomPsychics(uint16_t& nrSpace, sf::Sprite& card)
{
	if (m_playersSelected < 4)
	{
		nrSpace++;
		if (nrSpace == 1)
		{
			card = m_psychicInformation[m_selectedItemNumber - 1];
			card.setColor(m_spriteArray[0].getColor());
			card.setScale(static_cast<float>(0.95)* m_resolutionScale, static_cast<float>(0.95)* m_resolutionScale);
			card.setPosition(sf::Vector2f(m_widthDesktop / 2 - static_cast<float>(card.getTexture()->getSize().x) / 2,
				m_heightDesktop / 2 - static_cast<float>(card.getTexture()->getSize().y) / 2 + 130));
		}
		if (nrSpace == 2)
		{
			m_psychicInformation[m_selectedItemNumber - 1].setScale(static_cast<float>(0.475)* m_resolutionScale, static_cast<float>(0.475)* m_resolutionScale);
			card.setColor(sf::Color(0, 0, 0, 0));
			nrSpace = 0;
		}
	}
}

ChoosePlayer::ChoosePlayer(sf::RenderWindow& gameWindow, Board& board)
	:m_widthDesktop(sf::VideoMode::getDesktopMode().width), m_heightDesktop(sf::VideoMode::getDesktopMode().height), m_resolutionScale(static_cast<float>(sf::VideoMode::getDesktopMode().width) / 1920)
{
	m_psychicNumber = 1;
	sf::Music choosePlayerTheme;
	choosePlayerTheme.openFromFile("./Audio/MenuTheme.ogg");
	choosePlayerTheme.setVolume(15);
	choosePlayerTheme.setLoop(true);
	choosePlayerTheme.play();

	sf::Texture bgTexture;
	if (!bgTexture.loadFromFile("./Backgrounds/GameBoard.jpg"))
		std::cout << "Can't load image!";
	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);

	sf::Event eventChoosePlayer;

	readPsychics();
	readButtons();
	readPsychicsInformation();

	uint16_t nrSpace = 0;
	m_selectedItemNumber = 1;
	m_playersSelected = 0;
	m_spriteArray[m_selectedItemNumber].setScale(m_resolutionScale * static_cast <float>(0.66), m_resolutionScale* static_cast <float>(0.66));

	std::array<Psychic, PLAYERS_SIZE> psychics;
	uint16_t psychicNumber = 0;

	while (gameWindow.isOpen())
	{
		while (gameWindow.pollEvent(eventChoosePlayer))
		{
			switch (eventChoosePlayer.type)
			{
			case sf::Event::KeyPressed:
				switch (eventChoosePlayer.key.code)
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
					zoomPsychics(nrSpace, m_psychicInformation[m_selectedItemNumber - 1]);
					break;
				}
				case sf::Keyboard::Enter:
				{
					if (m_playersSelected <= 4)
					{
						if (psychicNumber < 4)
						{
							if (m_spriteArray[m_selectedItemNumber].getColor() != sf::Color(30, 0, 245, 255)
								&& m_spriteArray[m_selectedItemNumber].getColor() != sf::Color::Red)
							{
								Psychic psychic(m_spriteArray[m_selectedItemNumber]);
								psychics[psychicNumber] = std::move(psychic);
								psychicNumber++;
							}
						}
						SelectPsychic(m_playersSelected);
						if (m_playersSelected == 4)
						{
							m_spriteArray[ARRAY_SIZE - 1].setScale(m_resolutionScale * static_cast <float>(0.45), m_resolutionScale* static_cast <float>(0.45));
							m_spriteArray[m_selectedItemNumber].setScale(static_cast<float>(0.63) * m_resolutionScale, static_cast <float>(0.63) * m_resolutionScale);
							m_selectedItemNumber = 7;
						}
						if (m_playersSelected == 5)
						{
							choosePlayerTheme.stop();
							MysteriumGame game(gameWindow, psychics, board);
						}
					}
					break;
				}
				}
				break;
			}
			gameWindow.clear();
			gameWindow.draw(bgSprite);
			gameWindow.draw(m_spriteArray[0]);
			for (uint16_t index = 1; index < ARRAY_SIZE - 1; index++)
				gameWindow.draw(m_spriteArray[index]);
			gameWindow.draw(m_psychicInformation[m_selectedItemNumber - 1]);
			if (m_playersSelected == 4)
				gameWindow.draw(m_spriteArray[ARRAY_SIZE - 1]);
			gameWindow.display();
		}
	}
}

ChoosePlayer::~ChoosePlayer()
{
}
