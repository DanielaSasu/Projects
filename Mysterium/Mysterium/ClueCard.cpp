#include "ClueCard.h"

ClueCard::ClueCard()
	:m_clueType{ClueType::Suspect}
{
}

ClueCard::ClueCard(ClueType clueType, const sf::Sprite& cardImage)
	: m_clueType{ clueType }, GraphicsCard(Type::Clue,cardImage)
{
}

ClueCard& ClueCard::operator=(const ClueCard& oldClueCard)
{
	if (this != &oldClueCard)
	{
		GraphicsCard::operator=(oldClueCard);
		this->m_clueType = oldClueCard.m_clueType;
	}
	return *this;
}

ClueCard& ClueCard::operator=(ClueCard&& oldClueCard)
{
	if (this != &oldClueCard)
	{
		GraphicsCard::operator=(oldClueCard);
		this->m_clueType = oldClueCard.m_clueType;
	}
	new(&oldClueCard) ClueCard;
	return *this;
}

ClueCard::ClueCard(const ClueCard& oldClueCard) :GraphicsCard(oldClueCard)
{
	*this = oldClueCard;
}

ClueCard::ClueCard(ClueCard&& oldClueCard) :GraphicsCard(oldClueCard)
{
	*this = std::move(oldClueCard);
}

ClueCard::~ClueCard()
{
}

