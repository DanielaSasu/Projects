#include "StartMenu.h"

sf::Texture StartMenu::setImage(const std::string& name)
{
	sf::Texture image;
	if (!image.loadFromFile(name))
		std::cout << "Can't find the image!" << std::endl;
	return image;
}

sf::Sprite StartMenu::setSprite(const sf::Texture& texture, const float& value, const float& dimension, const float& heightPos)
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(dimension * m_resolutionScale, dimension * m_resolutionScale);
	sprite.setPosition(sf::Vector2f(m_widthDesktop / 2 - (texture.getSize().x * dimension * m_resolutionScale) / 2, ((m_heightDesktop / 4 - (texture.getSize().y * dimension * m_resolutionScale) / 2) * value) + heightPos));
	return sprite;
}

void StartMenu::MoveUp()
{
	if (m_selectedItemNumber > 0)
	{
		m_menuButtons[m_selectedItemNumber].setScale(static_cast <float>(0.9)* m_resolutionScale, static_cast <float>(0.9)* m_resolutionScale);
		m_selectedItemNumber--;
		m_menuButtons[m_selectedItemNumber].setScale(static_cast <float>(0.95)* m_resolutionScale, static_cast <float>(0.95)* m_resolutionScale);

	}
}

void StartMenu::MoveDown()
{
	if (m_selectedItemNumber + 1 < StartMenu::m_buttonNumber)
	{
		m_menuButtons[m_selectedItemNumber].setScale(static_cast <float>(0.9)* m_resolutionScale, static_cast <float>(0.9)* m_resolutionScale);
		m_selectedItemNumber++;
		m_menuButtons[m_selectedItemNumber].setScale(static_cast <float>(0.95)* m_resolutionScale, static_cast <float>(0.95)* m_resolutionScale);
	}
}

StartMenu::StartMenu(sf::RenderWindow& gameWindow, Board& board)
	:m_widthDesktop(sf::VideoMode::getDesktopMode().width), m_heightDesktop(sf::VideoMode::getDesktopMode().height), m_resolutionScale(static_cast<float>(sf::VideoMode::getDesktopMode().width / 1920))
{
	sf::Music menuTheme;
	menuTheme.openFromFile("./Audio/MenuTheme.ogg");
	menuTheme.setVolume(15);
	menuTheme.setLoop(true);
	menuTheme.play();

	sf::Event eventStartMenu;

	sf::Texture background = setImage("./Backgrounds/Menu.png");
	sf::Texture playButton = setImage("./Buttons/PlayButton.png");
	sf::Texture tutorialButton = setImage("./Buttons/TutorialButton.png");
	sf::Texture exitButton = setImage("./Buttons/ExitButton.png");
	sf::Texture title = setImage("./Buttons/Title.png");

	sf::Sprite backgroundSp, titleSp;
	backgroundSp.setTexture(background);
	backgroundSp.setScale(m_resolutionScale, m_resolutionScale);

	titleSp = setSprite(title, static_cast <float>(0.55), 1, 0);

	m_menuButtons[0] = setSprite(playButton, 2, static_cast <float>(0.9), 0);
	m_menuButtons[0].setScale(static_cast <float>(0.95)* m_resolutionScale, static_cast <float>(0.95)* m_resolutionScale);
	m_menuButtons[1] = setSprite(tutorialButton, 3, static_cast <float>(0.9), 50);
	m_menuButtons[2] = setSprite(exitButton, 4, static_cast <float>(0.9), 100);

	m_selectedItemNumber = 0;

	while (gameWindow.isOpen())
	{
		while (gameWindow.pollEvent(eventStartMenu))
		{
			switch (eventStartMenu.type)
			{
			case sf::Event::KeyPressed:
				switch (eventStartMenu.key.code)
				{
				case sf::Keyboard::Escape:
				{
					gameWindow.close();
					break;
				}
				case sf::Keyboard::Up:
				{
					MoveUp();
					break;
				}
				case sf::Keyboard::Down:
				{
					MoveDown();
					break;
				}
				case sf::Keyboard::W:
				{
					MoveUp();
					break;
				}
				case sf::Keyboard::S:
				{
					MoveDown();
					break;
				}
				case sf::Keyboard::Enter:
				{
					if (m_selectedItemNumber == 0)
					{
						menuTheme.stop();
						ChoosePlayer CPboard(gameWindow, board);
					}
					if (m_selectedItemNumber == 1)
					{
						Tutorial tutorial(gameWindow, board);
					}
					if (m_selectedItemNumber == 2)
					{
						menuTheme.stop();
						gameWindow.close();
					}
					break;
				}
				}
				break;
			}
		}
		gameWindow.clear();
		gameWindow.draw(backgroundSp);
		gameWindow.draw(titleSp);
		gameWindow.draw(m_menuButtons[0]);
		gameWindow.draw(m_menuButtons[1]);
		gameWindow.draw(m_menuButtons[2]);
		gameWindow.display();
	}
}

StartMenu::~StartMenu()
{
}
