#pragma once
#include "GraphicsCard.h"
#include <string>
class VisionCard: public GraphicsCard
{
public:
	VisionCard();
	VisionCard(VisionCard&&);
	VisionCard( const sf::Sprite&);
	VisionCard(const VisionCard&);
	VisionCard& operator=(const VisionCard&);
	VisionCard& operator=(VisionCard&&);
	~VisionCard();
};

