#pragma once
#include <iostream>
#include "time.h"
#include "MysteriumGame.h"

class ChoosePlayer
{
private: 
	static const size_t ARRAY_SIZE = 8;
	static const size_t PSYCHICS_NUMBER = 6;
	static const uint16_t PLAYERS_SIZE = 4;

	float m_resolutionScale;

	uint64_t m_selectedItemNumber;
	uint64_t m_psychicNumber;
	uint16_t m_widthDesktop;
	uint16_t m_heightDesktop;
	uint16_t m_playersSelected;

	std::array<sf::Texture, ARRAY_SIZE> m_textureArray;
	std::array<sf::Texture, PSYCHICS_NUMBER> m_informationTexture;

	sf::Sprite m_psychicInformation[PSYCHICS_NUMBER];
	sf::Sprite m_spriteArray[ARRAY_SIZE];
	
public:
	void MoveLeft();
	void MoveRight();
	void readPsychics();
	void readButtons();
	void readPsychicsInformation();
	void SelectPsychic(uint16_t&);
	void zoomPsychics(uint16_t&, sf::Sprite&);
	ChoosePlayer(sf::RenderWindow& , Board& board);
	~ChoosePlayer();
};

