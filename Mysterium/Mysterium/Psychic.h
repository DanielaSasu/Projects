#pragma once
#include "Player.h"
#include "VisionCard.h"
#include "ClueCard.h"
#include <Vector>
#include <array>
#include <SFML/Graphics.hpp>

class Psychic : public Player
{
private:
	
	std::vector<VisionCard> m_visionsRecieved;
	std::vector<sf::Sprite>m_clueSet;

	sf::Sprite m_psychicImage;

public:
	Psychic();
	Psychic(sf::Sprite);
	Psychic(std::vector<VisionCard>, std::vector<sf::Sprite>, sf::Sprite);
	Psychic(const Psychic&);
	Psychic(Psychic&&);

	Psychic& operator=(const Psychic&);
	Psychic& operator=(Psychic&&);

	sf::Sprite getPsychicImage();

	uint16_t getPoints() const;
	uint16_t getVisionsNumber() const;
	uint16_t getPhase() const;
	uint16_t getPsychicID() const;

	std::vector<VisionCard> getVisionCards();
	std::vector<sf::Sprite> getClueSets();

	void setVisionCard(const VisionCard&);
	void clearVisions();
	void IncreasePhase();
	void addInClueSet(sf::Sprite&);
	void addPoints(const uint16_t&);
	void setPsychicID(const uint16_t&);
	void setPsychicScale(const float&, const float&);
	void setPsychicPosition(const sf::Vector2f&);

	~Psychic();
};

