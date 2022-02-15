#pragma once
#include "MainWindow.h"
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class FinalScreen
{
private:
	sf::Sprite m_buttonSP;

public:
	void displayScreen(sf::Sprite&, sf::Music&);
};

