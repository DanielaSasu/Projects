#include "Board.h"
#include "../Logger/Logger/CardLogger.h"
#include "../Logger/Logger/cardLogger.cpp"

Board::Board()
	:m_resolutionScale(static_cast<float>(sf::VideoMode::getDesktopMode().width) / 1920)
{
}

Board::Board(const Board& oldBoard)
{
	*this = oldBoard;
}

Board::Board(Board&& oldBoard)
{
	*this = std::move(oldBoard);
}

Board& Board::operator=(const Board& oldBoard)
{
	if (this != &oldBoard)
	{
		this->m_deckClue = oldBoard.m_deckClue;
		this->m_deck_suspects = oldBoard.m_deck_suspects;
		this->m_deck_locations = oldBoard.m_deck_locations;
		this->m_deck_weapons = oldBoard.m_deck_weapons;
		this->m_deckVision = oldBoard.m_deckVision;
		this->m_Visions = oldBoard.m_Visions;
		this->m_unusedCardVector = oldBoard.m_unusedCardVector;
		this->m_resolutionScale = oldBoard.m_resolutionScale;
	}
	return *this;
}

Board& Board::operator=(Board&& oldBoard)
{
	if (this != &oldBoard)
	{
		this->m_deckClue = oldBoard.m_deckClue;
		this->m_deck_suspects = oldBoard.m_deck_suspects;
		this->m_deck_locations = oldBoard.m_deck_locations;
		this->m_deck_weapons = oldBoard.m_deck_weapons;
		this->m_deckVision = oldBoard.m_deckVision;
		this->m_Visions = oldBoard.m_Visions;
		this->m_unusedCardVector = oldBoard.m_unusedCardVector;
		this->m_resolutionScale = oldBoard.m_resolutionScale;
	}
	new (&oldBoard) Board;
	return *this;
}

void Board::shuffleDecks()
{
	std::random_shuffle(m_deckVision.begin(), m_deckVision.end());
	std::random_shuffle(m_deckClue.begin(), m_deckClue.begin() + 30);
	std::random_shuffle(m_deckClue.begin() + 30, m_deckClue.begin() + 60);
	std::random_shuffle(m_deckClue.begin() + 60, m_deckClue.begin() + 90);
}

void Board::copyDecks()
{
	std::copy(m_deckClue.begin(), m_deckClue.begin() + 5, std::begin(m_deck_suspects));
	std::copy(m_deckClue.begin() + 30, m_deckClue.begin() + 35, std::begin(m_deck_locations));
	std::copy(m_deckClue.begin() + 60, m_deckClue.begin() + 65, std::begin(m_deck_weapons));
	std::copy(m_deckVision.begin(), m_deckVision.begin() + 7, std::begin(m_Visions));
}

void Board::initializeClueDeck(const uint16_t& begin, const uint16_t& end, const std::string& clueType, const ClueCard::ClueType& type, const int16_t& position, sf::Sprite cardsSprites[NUMBER_OF_CARD_TEXTURE])
{
	write.open("Board_Cards_Logger.txt", std::ios::app);
	CardLogger cardLogger(write);

	for (int index = begin; index < end; index++)
	{
		std::string imageName = "./ClueCards/" + clueType + std::to_string(index + position) + ".png";
		if (!m_cardsTextures[index].loadFromFile(imageName))
		{
			cardLogger.log("Can't load texture " + imageName, CardLogger::Level::Error);
		}
		cardsSprites[index].setTexture(m_cardsTextures[index]);
		cardsSprites[index].setScale(m_resolutionScale, m_resolutionScale);
		ClueCard card(type, cardsSprites[index]);
		m_deckClue[index] = std::move(card);
		cardLogger.log("Loaded texture " + imageName, CardLogger::Level::Info);
	}
	write << std::endl;
	write.close();
}

void Board::initializeVisionDeck(sf::Sprite cardsSprites[NUMBER_OF_CARD_TEXTURE])
{
	write.open("Board_Cards_Logger.txt", std::ios::app);
	CardLogger cardLogger(write);

	for (int index = 0; index < NUMBER_OF_VISION_CARDS; index++)
	{
		std::string imageName = "./VisionCards/Vision" + std::to_string(index + 1) + ".png";
		if (!m_cardsTextures[index + NUMBER_OF_CLUE_CARDS].loadFromFile(imageName))
		{
			cardLogger.log("Can't load texture " + imageName, CardLogger::Level::Error);
		}
		cardsSprites[index + NUMBER_OF_CLUE_CARDS].setTexture(m_cardsTextures[index + NUMBER_OF_CLUE_CARDS]);
		cardsSprites[index + NUMBER_OF_CLUE_CARDS].setScale(m_resolutionScale, m_resolutionScale);
		VisionCard card(cardsSprites[index + NUMBER_OF_CLUE_CARDS]);
		m_deckVision[index] = std::move(card);
		cardLogger.log("Loaded texture " + imageName, CardLogger::Level::Info);
	}
	write << std::endl;
	write.close();
}

void Board::InitializeDecks()
{
	sf::Sprite cardsSprites[NUMBER_OF_CARD_TEXTURE];

	initializeClueDeck(0, 30, "Suspect", ClueCard::ClueType::Suspect, 1, cardsSprites);
	initializeClueDeck(30, 60, "Location", ClueCard::ClueType::Location, -29, cardsSprites);
	initializeClueDeck(60, 90, "Weapon", ClueCard::ClueType::Weapon, -59, cardsSprites);

	initializeVisionDeck(cardsSprites);

	shuffleDecks();
	copyDecks();

	for (int index = 0; index < NUMBER_OF_UNUSED_VISIONS; index++)
	{
		m_unusedCardVector.push_back(m_deckVision[index + 7]);
	}
}

std::array<ClueCard, Board::SIZE> Board::getSustepects() const
{
	return this->m_deck_suspects;
}

std::array<ClueCard, Board::SIZE> Board::getLocations() const
{
	return this->m_deck_locations;
}

std::array<ClueCard, Board::SIZE> Board::getWeapons() const
{
	return this->m_deck_weapons;
}

std::array<VisionCard, Board::NUMBER_OF_VISIONS> Board::getVisions() const
{
	return this->m_Visions;
}

std::vector<VisionCard> Board::getUnusedCard() const
{
	return m_unusedCardVector;
}

void Board::setUsedCards(std::array<VisionCard, NUMBER_OF_VISIONS> usedVector)
{
	m_Visions = usedVector;
}

void Board::setUnusedCards(std::vector<VisionCard> unusedCards)
{
	m_unusedCardVector = unusedCards;
}

Board::~Board()
{
}