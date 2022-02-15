#pragma once
#include <cstdint>
#include "GhostBoardPhase2.h"
#include "Psychic.h"

class PlayerBoardPhase2
{
private:
	uint16_t m_widthDesktop;
	uint16_t m_heightDesktop;

	static const uint16_t PLAYERS_SIZE = 4;
	static const size_t CLUE_SET_SIZE = 12;
	static const uint16_t NUMBER_OF_FINAL_VISIONS = 3;

	std::array<ClueCard, CLUE_SET_SIZE>m_clueSets;
	std::array<Psychic, PLAYERS_SIZE>m_psychics;
	std::array<VisionCard, NUMBER_OF_FINAL_VISIONS> m_finalVisionSet;

	int64_t m_selectedItemNumber;
	int64_t m_NumberOfVotes;
	uint16_t m_voteIndex;

     float m_resolutionScale;

public:
	PlayerBoardPhase2();
	void Intinialize(sf::RenderWindow&, std::array<Psychic, PLAYERS_SIZE>&, GhostBoardPhase2&);
	void showCards(sf::RenderWindow&, std::array<ClueCard, CLUE_SET_SIZE>&, const float&, const float&);
	void showVisionCards(sf::RenderWindow&, std::array<VisionCard, NUMBER_OF_FINAL_VISIONS>&, const float&, const float&);
	void showPsychics(sf::RenderWindow&, std::array<Psychic, PLAYERS_SIZE>&, const float&, const float&);
	void zoomVisionCard(uint16_t&, sf::Sprite&);
	void zoomClueCards(uint16_t&, sf::Sprite&, sf::Sprite&, sf::Sprite&);
	void rescaleSets(const float&);
	void MoveLeft();
	void MoveRight();
	void PositionVote(sf::Sprite&);
	uint16_t getVoteIndex();
	std::string getText();
	~PlayerBoardPhase2();
};

