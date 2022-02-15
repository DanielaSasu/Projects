#pragma once
#include "GraphicsCard.h"

class ClueCard: public GraphicsCard
{
public:
	enum class ClueType : uint8_t
	{
		Suspect,
		Location,
		Weapon
	};
	ClueCard();
	ClueCard( ClueType,const sf::Sprite&);
	ClueCard& operator=(const ClueCard&);
	ClueCard& operator=(ClueCard&&);
	ClueCard(const ClueCard&);
	ClueCard(ClueCard&&);
	~ClueCard();

private:
	ClueType m_clueType:2;
};

