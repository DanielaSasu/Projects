#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cstdint>
#include <random>
#include "StartMenu.h"
#include "Board.h"

class MainWindow
{
private:
	uint16_t widthDesktop;
	uint16_t heightDesktop;

public:
	MainWindow();
	~MainWindow();
};
