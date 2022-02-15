#pragma once
#include <array>
#include <vector>
#include <fstream>
#include "ClueCard.h"
#include "VisionCard.h"

class Board
{
private:
	static const size_t NUMBER_OF_CLUE_CARDS = 90;
	static const size_t NUMBER_OF_VISION_CARDS = 168;
	static const size_t SIZE = 5;
	static const size_t NUMBER_OF_PSYCHICS = 2;
	static const size_t NUMBER_OF_VISIONS = 7;
	static const size_t NUMBER_OF_CARD_TEXTURE = NUMBER_OF_CLUE_CARDS + NUMBER_OF_VISION_CARDS;
	static const size_t NUMBER_OF_UNUSED_VISIONS = NUMBER_OF_VISION_CARDS - NUMBER_OF_VISIONS;

	float m_resolutionScale;

	std::array<ClueCard, NUMBER_OF_CLUE_CARDS>m_deckClue;
	std::array<ClueCard, SIZE>m_deck_suspects;
	std::array<ClueCard, SIZE>m_deck_locations;
	std::array<ClueCard, SIZE>m_deck_weapons;
	std::array<VisionCard, NUMBER_OF_VISION_CARDS>m_deckVision;
	std::array<VisionCard, NUMBER_OF_VISIONS>m_Visions;

	sf::Texture m_cardsTextures[NUMBER_OF_CARD_TEXTURE];

	std::vector<VisionCard> m_unusedCardVector;

	std::ofstream write;

public:
	Board();
	Board(const Board&);
	Board(Board&&);
	Board& operator=(const Board&);
	Board& operator=(Board&&);

	void shuffleDecks();
	void copyDecks();
	void initializeClueDeck(const uint16_t& , const uint16_t& , const std::string& , const ClueCard::ClueType& , const int16_t&, sf::Sprite[NUMBER_OF_CARD_TEXTURE]);
	void initializeVisionDeck(sf::Sprite[NUMBER_OF_CARD_TEXTURE]);
	void InitializeDecks();
	void setUsedCards(std::array<VisionCard, NUMBER_OF_VISIONS>);
	void setUnusedCards(std::vector<VisionCard>);
	
	std::array<ClueCard, SIZE> getSustepects() const;
	std::array<ClueCard, SIZE> getLocations() const;
	std::array<ClueCard, SIZE> getWeapons() const;
	std::array<VisionCard, NUMBER_OF_VISIONS> getVisions() const;
	std::vector<VisionCard> getUnusedCard() const;
	
	~Board();
};