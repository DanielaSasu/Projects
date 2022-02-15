#include "Psychic.h"

Psychic::Psychic()
	: Player()
{
}

Psychic::Psychic(sf::Sprite psychicImage)
	: m_psychicImage(psychicImage), Player()
{
}

Psychic::Psychic(std::vector<VisionCard>visionRecieved, std::vector<sf::Sprite>clueSet, sf::Sprite psychicImage)
	: m_visionsRecieved(visionRecieved), m_clueSet(clueSet), m_psychicImage(psychicImage), Player()
{
}

Psychic::Psychic(const Psychic& oldPsychic) 
{
	*this = oldPsychic;
}

Psychic::Psychic(Psychic&& oldPsychic)
{
	*this = std::move(oldPsychic);
}

Psychic& Psychic::operator=(const Psychic& oldPsychic)
{
	if (this != &oldPsychic)
	{
		Player::operator=(oldPsychic);
		this->m_clueSet = oldPsychic.m_clueSet;
		this->m_visionsRecieved = oldPsychic.m_visionsRecieved;
		this->m_psychicImage = oldPsychic.m_psychicImage;
	}
	return *this;
}

Psychic& Psychic::operator=(Psychic&& oldPsychic)
{
	if (this != &oldPsychic)
	{
		Player::operator=(oldPsychic);
		this->m_clueSet = oldPsychic.m_clueSet;
		this->m_visionsRecieved = oldPsychic.m_visionsRecieved;
		this->m_psychicImage = oldPsychic.m_psychicImage;
	}
	new(&oldPsychic)Psychic;
	return *this;
}

sf::Sprite Psychic::getPsychicImage()
{
	return m_psychicImage;
}

void Psychic::setVisionCard(const VisionCard& oldVisionCard)
{
	this->m_visionsRecieved.push_back(oldVisionCard);
}

uint16_t Psychic::getPhase() const
{
	return Player::getPlayerPhase();
}

std::vector<VisionCard> Psychic::getVisionCards()
{
	return m_visionsRecieved;
}

void Psychic::clearVisions()
{
	m_visionsRecieved.clear();
}

uint16_t Psychic::getVisionsNumber() const
{
	return (uint16_t)m_visionsRecieved.size();
}

void Psychic::IncreasePhase()
{
	Player::IncreasePhase();
}

void Psychic::addInClueSet(sf::Sprite& card)
{
	m_clueSet.push_back(card);
}

void Psychic::addPoints(const uint16_t& number)
{
	Player::addPoints(number);
}

void Psychic::setPsychicID(const uint16_t& orderNumber)
{
	Player::setPlayerID(orderNumber);
}

void Psychic::setPsychicScale(const float& value1, const float&value2)
{
	m_psychicImage.setScale(value1, value2);
}

void Psychic::setPsychicPosition(const sf::Vector2f& position)
{
	m_psychicImage.setPosition(position);
}

std::vector<sf::Sprite> Psychic::getClueSets()
{
	return m_clueSet;
}

uint16_t Psychic::getPoints() const
{
	return Player::getPlayerPoints();
}

Psychic::~Psychic()
{
}

uint16_t Psychic::getPsychicID() const
{
	return Player::getPlayerID();
}

