#include "FinalScreen.h"

void FinalScreen::displayScreen(sf::Sprite& background, sf::Music& bgMusic)
{
	bgMusic.play();
	uint16_t widthDesktop = sf::VideoMode::getDesktopMode().width;
	uint16_t heightDesktop = sf::VideoMode::getDesktopMode().height;
	static const float resolutionScale = static_cast<float>(sf::VideoMode::getDesktopMode().width) / 1920;

	sf::RenderWindow winScreenWindow(sf::VideoMode(widthDesktop, heightDesktop), "Loose Screen", sf::Style::Fullscreen);

	sf::Event winScreenEvent;

	sf::Texture button;
	if (!button.loadFromFile("./Buttons/ExitButton.png"))
		std::cout << "Can't loat image!" << std::endl;

	m_buttonSP.setTexture(button);
	m_buttonSP.setScale(static_cast <float>(0.9) * resolutionScale, static_cast <float>(0.9) * resolutionScale);


	m_buttonSP.setPosition(sf::Vector2f(widthDesktop / 2 - (button.getSize().x * resolutionScale) / 2, (heightDesktop / 4 + 300 * resolutionScale)));

	while (winScreenWindow.isOpen())
	{
		while (winScreenWindow.pollEvent(winScreenEvent))
		{
			switch (winScreenEvent.type)
			{
			case sf::Event::KeyPressed:
				switch (winScreenEvent.key.code)
				{
				case sf::Keyboard::Enter:
				{
					bgMusic.stop();
					winScreenWindow.close();
					break;
				}
				}
				break;
			}
		}
		winScreenWindow.clear();
		winScreenWindow.draw(background);
		winScreenWindow.draw(m_buttonSP);
		winScreenWindow.display();
	}
}