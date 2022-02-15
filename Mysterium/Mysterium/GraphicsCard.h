#pragma once
#include <string>
#include <cstdint>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GraphicsCard
{
public:
	enum class Type : uint8_t
	{
		Vision,
		Clue,
	};
	GraphicsCard();
	GraphicsCard(const Type&,const sf::Sprite&);
	GraphicsCard(const GraphicsCard&);
	GraphicsCard(GraphicsCard&&);
	GraphicsCard& operator=(const GraphicsCard&);
	GraphicsCard& operator=(GraphicsCard&&);
	sf::Sprite getCardImage();
	void setCardScale(const float&,const float& );
	void setCardColor(const sf::Color&);
	void setCardPosition(const sf::Vector2f&);
	void setCardImage(const sf::Sprite&);
	~GraphicsCard();
	
private:
	sf::Sprite m_cardImage;
	Type m_type : 1;
};

