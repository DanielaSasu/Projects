#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "ClueCard.h"
#include "Psychic.h"
#include "Board.h"
#include "VisionCard.h"

class GhostBoardPhase2
{
private:
	static const size_t SIZE = 5;
	static const size_t CLUE_SET_SIZE = 12;
	static const size_t VISION_DECK_SIZE = 7;
	static const uint16_t PLAYERS_SIZE = 4;

	std::array<ClueCard ,SIZE>m_suspectArray;
	std::array<ClueCard, SIZE> m_locationArray;
	std::array<ClueCard, SIZE> m_weaponArray;

	std::array<ClueCard, CLUE_SET_SIZE>m_clueSets;
	std::array<VisionCard, VISION_DECK_SIZE> m_visionDeck;
	std::array<Psychic, PLAYERS_SIZE> m_psychics;

	std::vector<VisionCard> m_FinalVisionSet;

	sf::Sprite m_crowSprite;

	uint16_t m_widthDesktop;
	uint16_t m_heightDesktop;
	uint64_t m_finalVisionNumber;
	int64_t m_selectedItemNumber;
	uint64_t m_selectedClueSet;
	uint16_t m_indexLine;
	uint16_t m_correctClueSetIndex;

	bool m_crowUsed;

	std::vector<VisionCard> m_unusedCard;
	std::vector<VisionCard> m_usedCard;
	std::vector<sf::Sprite>m_chosenCards;

	sf::Color m_initialColor;

	float m_resolutionScale;

public:
	std::string getMessage();
	void arrangeClueSets(std::array<ClueCard, SIZE>&);
	void showCards(std::array<ClueCard, CLUE_SET_SIZE>, std::array<Psychic, PLAYERS_SIZE>, const float&, const float&, sf::RenderWindow&);
	void showVisionCards(std::array < VisionCard, VISION_DECK_SIZE>, const float&, const float&, sf::RenderWindow&);
	void InitializeBoard(Board, sf::RenderWindow&, std::array<Psychic, PLAYERS_SIZE>&);
	void MoveLeft();
	void MoveRight();
	void setUsedCard(VisionCard&);
	VisionCard getUnusedCard();
	void setChosenCard(sf::Sprite);
	void checkCards(std::array<Psychic, PLAYERS_SIZE>&);
	void zoomVisionCards(uint16_t&, sf::Sprite&);
	void zoomClueCards(uint16_t&, sf::Sprite&);
	std::vector<VisionCard> getFinalVisions();
	uint16_t getCorrectClueSetIndex();
	GhostBoardPhase2(Board&);
	GhostBoardPhase2();
	~GhostBoardPhase2();
};