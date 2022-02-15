#pragma once
#include <cstdint>
#include <iostream>
#include <string>

class Player
{
private: 
	uint16_t m_phase;
	uint16_t m_points;
	uint16_t m_playerID;

public:
	Player();
	Player(const Player&);
	Player(Player&&);
	Player& operator=(const Player&);
	Player& operator=(Player&&);

	uint16_t getPlayerPhase() const;
	uint16_t getPlayerPoints() const;
	uint16_t getPlayerID() const;

	void IncreasePhase();
	void addPoints(const uint16_t&);
	void setPlayerID(const uint16_t&);

	std::string getPlayerInfo() const;  
	~Player();

};

