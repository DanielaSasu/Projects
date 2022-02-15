#include "VisionCard.h"

VisionCard::VisionCard()
{
}

VisionCard::VisionCard(const sf::Sprite& cardImage)
	: GraphicsCard(Type::Vision,cardImage)
{
}

VisionCard& VisionCard::operator=(const VisionCard& oldVisionCard)
{
	if (this != &oldVisionCard)
	{
		GraphicsCard::operator=(oldVisionCard);
	}
	return *this;
}

VisionCard& VisionCard::operator=(VisionCard&& oldVisionCard)
{
	if (this != &oldVisionCard)
	{
		GraphicsCard::operator=(oldVisionCard);
	}
	new(&oldVisionCard) VisionCard;
	return *this;
}

VisionCard::VisionCard(const VisionCard& oldVisionCard) :GraphicsCard(oldVisionCard)
{
	*this = oldVisionCard;
}

VisionCard::VisionCard(VisionCard&& oldVisionCard) :GraphicsCard(oldVisionCard)
{
	*this = std::move(oldVisionCard);
}

VisionCard::~VisionCard()
{
}
