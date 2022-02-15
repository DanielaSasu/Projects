#include "Player.h"

Player::Player()
	:m_phase(1), m_points(0), m_playerID(1)
{
}

Player::Player(const Player& oldPlayer)
{
	*this = oldPlayer;
}

Player::Player(Player&& oldPlayer)
{
	*this = std::move(oldPlayer);
}

Player& Player::operator=(const Player& oldPlayer)
{
	this->m_phase = oldPlayer.m_phase;
	this->m_playerID = oldPlayer.m_playerID;
	this->m_points = oldPlayer.m_points;
	return *this;
}

Player& Player::operator=(Player&& oldPlayer)
{
	if (this != &oldPlayer)
	{
		this->m_phase = oldPlayer.m_phase;
		this->m_playerID = oldPlayer.m_playerID;
		this->m_points = oldPlayer.m_points;
	}
	new(&oldPlayer)Player;
	return *this;
}

uint16_t Player::getPlayerPhase() const
{
	return m_phase;
}

uint16_t Player::getPlayerPoints() const
{
	return m_points;
}

uint16_t Player::getPlayerID() const
{
	return m_playerID;
}

void Player::IncreasePhase()
{
	if (m_phase <= 3)
	{
		m_phase++;
	}
}

void Player::addPoints(const uint16_t& number)
{
	m_points += number;
}

void Player::setPlayerID(const uint16_t& orderNumber)
{
	m_playerID = orderNumber;
}

std::string Player::getPlayerInfo() const
{
	return "Player" + std::to_string(m_playerID) + " has " + std::to_string(m_points) + " points in phase " + std::to_string(m_phase) + ".\n";
}

Player::~Player()
{
}
