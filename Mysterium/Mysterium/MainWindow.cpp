#include "MainWindow.h"

MainWindow::MainWindow()
	:widthDesktop(sf::VideoMode::getDesktopMode().width), heightDesktop(sf::VideoMode::getDesktopMode().height)
{
	std::random_device randDevice;
	std::mt19937 mersenneTwister(randDevice());
	std::uniform_real_distribution<double> disttribution(0.1, RAND_MAX);

	srand(static_cast<uint16_t>(disttribution(mersenneTwister)));

	Board board;
	board.InitializeDecks();
	sf::RenderWindow m_gameWindow(sf::VideoMode(widthDesktop, heightDesktop), "Mysterium", sf::Style::Fullscreen);
	StartMenu startmenu(m_gameWindow, board);
}

MainWindow::~MainWindow()
{
}
