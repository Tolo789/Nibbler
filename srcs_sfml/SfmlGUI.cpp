#include "SfmlGUI.hpp"

// === CONSTRUCTOR =============================================================

SfmlGUI::SfmlGUI(MainGame *mainGame) : mainGame(mainGame), window(sf::VideoMode(WINDOW_W, WINDOW_H), "Nibbler SFML", sf::Style::Titlebar) {
	window.setKeyRepeatEnabled(false);
	window.setPosition(sf::Vector2i(
		(sf::VideoMode::getDesktopMode().width/2) - (WINDOW_W / 2),
		(sf::VideoMode::getDesktopMode().height/2)- (WINDOW_H / 2))
	);

	square_size = mainGame->get_square_size();
	x_offset = mainGame->get_x_offset();
	y_offset = mainGame->get_y_offset();

	return ;
}

SfmlGUI::SfmlGUI(void) {
	return ;
}

SfmlGUI::SfmlGUI(SfmlGUI const & src) {
	*this = src;
	return ;
}

SfmlGUI::~SfmlGUI(void) {
	return ;
}

// === ENDCONSTRUCTOR ==========================================================

// === OPERATORS ===============================================================

SfmlGUI& SfmlGUI::operator=(SfmlGUI const & rhs) {
	this->active = rhs.active;
	return *this;
}

// === ENDOPERATORS ============================================================

// === OVERRIDES ===============================================================

void	SfmlGUI::get_user_input(void) {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed) {
			char str[2];
			str[0] = 0;
			str[1] = 0;
			// SFML doesnt have any internal func to convert KeyCode to string
			if (event.key.code == sf::Keyboard::Escape)
				mainGame->button_pressed(NULL);
			else {
				if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z)
					str[0] = 'A' + (event.key.code - sf::Keyboard::A);
				else if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9)
					str[0] = '0' + (event.key.code - sf::Keyboard::Num0);
				else if (event.key.code >= sf::Keyboard::Numpad0 && event.key.code <= sf::Keyboard::Numpad9)
					str[0] = '0' + (event.key.code - sf::Keyboard::Numpad0);
				mainGame->button_pressed(str);
			}
		}
	}
}

void	SfmlGUI::refresh_window(std::vector<std::tuple<int, int>> &snake_body, std::tuple<int, int> &fruit_pos) {
	(void) fruit_pos;

	window.clear(sf::Color::Black); // Can set background color here
	
	// Add map outlines
	sf::RectangleShape lineUp(sf::Vector2f(WINDOW_W - 2 * x_offset, OUTLINE_TICKNESS));
	lineUp.setFillColor(sf::Color::White);
	lineUp.setPosition(x_offset, y_offset - OUTLINE_TICKNESS);
	window.draw(lineUp);
	sf::RectangleShape lineDown(sf::Vector2f(WINDOW_W - 2 * x_offset, OUTLINE_TICKNESS));
	lineDown.setFillColor(sf::Color::White);
	lineDown.setPosition(x_offset, WINDOW_H - y_offset);
	window.draw(lineDown);
	sf::RectangleShape lineLeft(sf::Vector2f(OUTLINE_TICKNESS, WINDOW_H - 2 * y_offset));
	lineLeft.setFillColor(sf::Color::White);
	lineLeft.setPosition(x_offset - OUTLINE_TICKNESS, y_offset);
	window.draw(lineLeft);
	sf::RectangleShape lineRight(sf::Vector2f(OUTLINE_TICKNESS, WINDOW_H - 2 * y_offset));
	lineRight.setFillColor(sf::Color::White);
	lineRight.setPosition(WINDOW_W - x_offset, y_offset);
	window.draw(lineRight);

	// TODO: Add map inlines (?)
	// sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x, y)), sf::Vertex(sf::Vector2f(x2, y2))};
	// window.draw(line, 2, sf::Lines);

	// Add snake
	for (std::tuple<int, int> &body_part : snake_body) // access by reference to avoid copying
	{
		sf::RectangleShape rectangle(sf::Vector2f(square_size, square_size));
		rectangle.setFillColor(sf::Color::Green);
		rectangle.setPosition(x_offset + std::get<0>(body_part) * square_size, y_offset + std::get<1>(body_part) * square_size);
		window.draw(rectangle);
	}

	// Add fruit
	sf::RectangleShape rectangle(sf::Vector2f(square_size, square_size));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(x_offset + std::get<0>(fruit_pos) * square_size, y_offset + std::get<1>(fruit_pos) * square_size);
	window.draw(rectangle);


	window.display();
}

void	SfmlGUI::close_window() {
	std::cout << "Destroing SFML window" << std::endl;
	window.close();
}
// === END OVERRIDES ===========================================================

// === OTHERS ==================================================================
SfmlGUI	*getGUI(MainGame *mainGame) {
	return new SfmlGUI(mainGame);
}

void	deleteGUI(SfmlGUI *test) {
	delete test;
}
// === END OTHERS ==============================================================
