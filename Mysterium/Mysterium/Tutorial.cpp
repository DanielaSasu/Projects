#include "Tutorial.h"

Tutorial::Tutorial()
	:m_widthDesktop(sf::VideoMode::getDesktopMode().width), m_heightDesktop(sf::VideoMode::getDesktopMode().height),m_selectedItemNumber(0), m_resolutionScale(static_cast<float>(sf::VideoMode::getDesktopMode().width) / 1920)
{
}

Tutorial::Tutorial(sf::RenderWindow& gameWindow, Board& board )
	:m_widthDesktop(sf::VideoMode::getDesktopMode().width), m_heightDesktop(sf::VideoMode::getDesktopMode().height),m_selectedItemNumber(0), m_resolutionScale(static_cast<float>(sf::VideoMode::getDesktopMode().width) / 1920)
{
	sf::Event tutorialWindowEvent;

	sf::Texture bgTexture;
	if (!bgTexture.loadFromFile("./Backgrounds/TutorialBg.jpg"))
		std::cout << "Can't load image!";
	sf::Sprite bg;
	bg.setTexture(bgTexture);
	bg.setScale(m_resolutionScale, static_cast<float> (0.9) * m_resolutionScale);

	initializeText();
	initializeTutorialImages();
	m_selectedItemNumber = 0;
	m_menu[m_selectedItemNumber].setFillColor(sf::Color::Red);
	while (gameWindow.isOpen())
	{
		while (gameWindow.pollEvent(tutorialWindowEvent))
		{
			switch (tutorialWindowEvent.type)
			{
			case sf::Event::KeyPressed:
				switch (tutorialWindowEvent.key.code)
				{
				case sf::Keyboard::Escape:
				{
					gameWindow.close();
					break;
				}
				
				case sf::Keyboard::Enter:
				{
					if (m_selectedItemNumber == 8)
					{
						StartMenu startMenu(gameWindow, board);
					}
					break;
				}
				case sf::Keyboard::Up:
				{
					moveUp();
					break;
				}
				case sf::Keyboard::W:
				{
					moveUp();
					break;
				}
				case sf::Keyboard::Down:
				{
					moveDown();
					break;
				}
				case sf::Keyboard::S:
				{
					moveDown();
					break;
				}
				}
				break;
			}
		}
		gameWindow.clear();
		gameWindow.draw(bg);
		if (m_selectedItemNumber<8)
		  gameWindow.draw(m_tutorialSpriteArray[m_selectedItemNumber]);
		printMenu(gameWindow);
		gameWindow.display();
	}
}

void Tutorial::initializeText()
{
	std::array<std::string, NUMBER_OF_TUTORIALS> menuStrings = {"Game Rules","Psychic Menu","Ghost Board" ,"Player Board" ,"Moving through Cards" ,"Ghost Choice" 
		,"Player Vote" ,"Vote Explanation" ,"Back to menu" };
	m_font.loadFromFile("./Buttons/ChrustyRock-ORLA.ttf");
	uint64_t positionIndex = 0;
	for (uint16_t index = 0; index < NUMBER_OF_TUTORIALS; index++)
	{
		m_menu[index].setFont(m_font);
		m_menu[index].setFillColor(sf::Color(218, 165, 32, 255));
		m_menu[index].setCharacterSize(42);
		m_menu[index].setString(menuStrings[index]);
		m_menu[index].setPosition(static_cast<float>(m_widthDesktop / 16), static_cast<float>(m_heightDesktop / 7) + positionIndex);
		positionIndex += 90;
	}
}

void Tutorial::initializeTutorialImages()
{
	for (uint16_t index = 0; index < NUMBER_OF_TUTORIALS - 1; index++)
	{
		std::string imageName = "./Tutorials/Tutorial" + std::to_string(index + 1) + ".png";
		if (!m_textures[index].loadFromFile(imageName))
			std::cout << "Can't load image";
		m_tutorialSpriteArray[index].setTexture(m_textures[index]);
		m_tutorialSpriteArray[index].setScale(m_resolutionScale, static_cast<float>(0.9)*m_resolutionScale);
		m_tutorialSpriteArray[index].setPosition((m_widthDesktop / 180) * m_resolutionScale, m_resolutionScale);
	}
}

void Tutorial::printMenu(sf::RenderWindow& gameWindow)
{
	for (uint16_t index = 0; index < NUMBER_OF_TUTORIALS; index++)
	{
		gameWindow.draw(m_menu[index]);
	}
}

void Tutorial::moveUp()
{
	if (m_selectedItemNumber - 1 >= 0)
	{
		if (m_selectedItemNumber != 0)
		{
			m_menu[m_selectedItemNumber].setFillColor(sf::Color(218, 165, 32, 255));
			m_selectedItemNumber--;
			m_menu[m_selectedItemNumber].setFillColor(sf::Color::Red);
		}
	}
}

void Tutorial::moveDown()
{
	if (m_selectedItemNumber + 1 < Tutorial::NUMBER_OF_TUTORIALS)
	{
		m_menu[m_selectedItemNumber].setFillColor(sf::Color(218, 165, 32, 255));
		m_selectedItemNumber++;
		m_menu[m_selectedItemNumber].setFillColor(sf::Color::Red);
	}
}

Tutorial::~Tutorial()
{
}
