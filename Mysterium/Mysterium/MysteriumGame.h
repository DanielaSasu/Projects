#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <fstream>
#include "Psychic.h"
#include "GhostBoard.h"
#include "PlayerBoard.h"
#include "GhostBoardPhase2.h"
#include "PlayerBoardPhase2.h"
#include "FinalScreen.h"

class MysteriumGame
{
private:
	static const uint16_t PLAYERS_SIZE = 4;
	static const uint16_t NUMBER_OF_ROUNDS = 7;

	const float m_resolutionScale;

	std::ofstream write;

public:
	MysteriumGame();
	MysteriumGame(sf::RenderWindow&, std::array<Psychic, PLAYERS_SIZE>, Board&);
	~MysteriumGame();
};
