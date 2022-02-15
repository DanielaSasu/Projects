#pragma once
#include <array>
#include <vector>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ClueCard.h"
#include "Psychic.h"
#include "Board.h"
#include "GhostBoard.h"

class PlayerBoard
{
private:
	static const size_t SIZE = 5;
	static const size_t NUMBER_OF_VISIONS = 7;
	static const size_t ROUND_TIME = 120;

	 const float m_resolutionScale; 

	std::array<ClueCard, SIZE> m_suspectArray;
	std::array<ClueCard, SIZE> m_locationArray;
	std::array<ClueCard, SIZE> m_weaponArray;
	std::array<VisionCard, NUMBER_OF_VISIONS> m_visionsPlayer;

	uint16_t m_widthDesktop;
	uint16_t m_heightDesktop;
	uint64_t m_selectedItemNumber;

	std::ofstream write;

public:
	std::string setMessage(Psychic&);

	void ArrangeClueCards(std::array<ClueCard, SIZE>, std::array<ClueCard, SIZE>&);
	void ArrangeVisionsCards(std::vector<VisionCard>, std::array<VisionCard, NUMBER_OF_VISIONS>&);
	void showCards(std::array<ClueCard, SIZE>&, const float&, const float&, sf::RenderWindow&);
	void showCards(std::array<VisionCard, NUMBER_OF_VISIONS>&, const float&, const float&, sf::RenderWindow&, Psychic&);
	void MoveLeft( Psychic&);
	void MoveRight( Psychic&);
	void InitializeBoard(Board, GhostBoard&, sf::RenderWindow&, Psychic&, sf::Sprite&);
	void ChangeCardPhase( const float&, Psychic&);
	void zoomClueCards(uint16_t&, sf::Sprite&, ClueCard&);
	void zoomVisionCards(uint16_t&, sf::Sprite&);

	PlayerBoard();
	PlayerBoard(Board&);
	~PlayerBoard();
};