#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "ClueCard.h"
#include "Psychic.h"
#include "Board.h"
#include "VisionCard.h"

class GhostBoard
{
private:
	static const size_t SIZE = 5;
	static const size_t CLUE_SET_SIZE = 12;
	static const size_t VISION_DECK_SIZE = 7;
	static const uint16_t PLAYERS_SIZE = 4;

	float m_resolutionScale;

	std::array<ClueCard, SIZE>m_suspectArray;
	std::array<ClueCard, SIZE>m_locationArray;
	std::array<ClueCard, SIZE>m_weaponArray;

	sf::Sprite m_clueSets[CLUE_SET_SIZE];
	sf::Sprite m_visionDeck[VISION_DECK_SIZE];
	sf::Sprite m_psychics[PLAYERS_SIZE];

	sf::Sprite m_crowSprite;

	uint16_t m_widthDesktop;
	uint16_t m_heightDesktop;
	uint64_t m_psychicNumber;
	int64_t m_selectedItemNumber;

	bool m_crowUsed;

	std::vector<VisionCard> m_unusedCard;
	std::vector<VisionCard> m_usedCard;
	std::vector<sf::Sprite>m_chosenCards;

	std::ofstream write;

public:
	std::string getMessage(std::array<Psychic, PLAYERS_SIZE>&);

	void Copy_Array_to_Sprite(std::array<ClueCard, SIZE>, sf::Sprite[SIZE]);
	void Copy_Array_to_Sprite(std::array<VisionCard, VISION_DECK_SIZE>, sf::Sprite[VISION_DECK_SIZE]);
	void showCards(sf::Sprite[SIZE], sf::Sprite[PLAYERS_SIZE], const float&, const float&, sf::RenderWindow&);
	void showVisionCards(sf::Sprite[VISION_DECK_SIZE], const float&, const float&, sf::RenderWindow&);
	void InitializeBoard(Board&, sf::RenderWindow&, std::array<Psychic, PLAYERS_SIZE>&, sf::Sprite&);
	void MoveLeft();
	void MoveRight();
	void setUsedCard(VisionCard&);
	void setChosenCard(sf::Sprite);
	void checkCards(std::array<Psychic, PLAYERS_SIZE>&);
	void zoomVisionCard(uint16_t&, sf::Sprite&);
	void zoomClueCard(uint16_t&, sf::Sprite&, const uint16_t&);
	void shuffleCards(std::array<ClueCard, SIZE>, std::array<ClueCard, SIZE>, std::array<ClueCard, SIZE>&);

	std::array<VisionCard, VISION_DECK_SIZE> Copy_spriteArray_to_visionArray();

	VisionCard getUnusedCard();

	GhostBoard(Board&);
	GhostBoard();
	~GhostBoard();
};
