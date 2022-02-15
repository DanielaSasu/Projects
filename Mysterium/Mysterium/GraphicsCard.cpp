#include "GraphicsCard.h"

GraphicsCard::GraphicsCard()
{
}

GraphicsCard::GraphicsCard(const Type& type, const sf::Sprite& cardImage)
	: m_type(type), m_cardImage(cardImage)
{
}

GraphicsCard::GraphicsCard(const GraphicsCard& oldObj)
{
	*this = oldObj;
}

GraphicsCard::GraphicsCard(GraphicsCard&& oldObj)
{
	*this = std::move(oldObj);
}

GraphicsCard& GraphicsCard::operator=(const GraphicsCard& oldObj)
{
	if (this != &oldObj)
	{
		this->m_type = oldObj.m_type;
		this->m_cardImage = oldObj.m_cardImage;
	}
	return *this;
}

GraphicsCard& GraphicsCard::operator=(GraphicsCard&& oldObj)
{
	if (this != &oldObj)
	{
		this->m_type = oldObj.m_type;
		this->m_cardImage = oldObj.m_cardImage;
	}
	new(&oldObj) GraphicsCard;
	return *this;
}

sf::Sprite GraphicsCard::getCardImage()
{
	return m_cardImage;
}

void GraphicsCard::setCardScale(const float& value1, const float& value2)
{
	m_cardImage.setScale(value1, value2);
}

void GraphicsCard::setCardColor(const sf::Color& color)
{
	m_cardImage.setColor(color);
}

void GraphicsCard::setCardPosition(const sf::Vector2f& position)
{
	m_cardImage.setPosition(position);
}

void GraphicsCard::setCardImage(const sf::Sprite& image)
{
	m_cardImage = image;
}

GraphicsCard::~GraphicsCard()
{
}