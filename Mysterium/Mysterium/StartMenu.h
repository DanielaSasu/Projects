#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cstdint>
#include <iostream>
#include <string>
#include <array>
#include "ChoosePlayer.h"
#include "Tutorial.h"

class StartMenu
{
private:
	static const size_t m_buttonNumber = 3;
	uint16_t m_widthDesktop;
	uint16_t m_heightDesktop;
	uint64_t m_selectedItemNumber;

	std::array<sf::Sprite, m_buttonNumber> m_menuButtons;
	
	const float m_resolutionScale;

public:
	sf::Texture setImage(const std::string&);
	sf::Sprite setSprite( const sf::Texture&, const float&, const float& , const float&);
	void MoveUp();
	void MoveDown();
	StartMenu(sf::RenderWindow&, Board& board);
	~StartMenu();
};



