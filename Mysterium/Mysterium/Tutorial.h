#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cstdint>
#include "Board.h"
#include "StartMenu.h"
class Tutorial
{
private:
	static const uint16_t NUMBER_OF_TUTORIALS = 9;
	uint64_t m_selectedItemNumber;
	std::array<sf::Sprite, NUMBER_OF_TUTORIALS - 1> m_tutorialSpriteArray;
	std::array<sf::Texture, NUMBER_OF_TUTORIALS - 1> m_textures;

	sf::Font m_font;
	std::array<sf::Text, NUMBER_OF_TUTORIALS>m_menu;

	uint16_t m_widthDesktop;
	uint16_t m_heightDesktop;
	float m_resolutionScale;

public:
	Tutorial();
	Tutorial(sf::RenderWindow&, Board&);
	void initializeText();
	void initializeTutorialImages();
	void printMenu(sf::RenderWindow&);
	void moveUp();
	void moveDown();
	~Tutorial();
};

