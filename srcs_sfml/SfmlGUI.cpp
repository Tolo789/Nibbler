#include "SfmlGUI.hpp"

// === CONSTRUCTOR =============================================================

SfmlGUI::SfmlGUI(MainGame *mainGame) : mainGame(mainGame), window(sf::VideoMode(600, 600), "SFML works!") {
	window.setKeyRepeatEnabled(false);

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

void	SfmlGUI::refresh_window(std::vector<std::tuple<int, int>> snake_body) {
	(void) snake_body;
	std::cout << "SFML func called" << std::endl;

	window.clear(sf::Color::Black); // Can set background color here
	

	for (std::tuple<int, int> &body_part : snake_body) // access by reference to avoid copying
	{
		sf::RectangleShape rectangle(sf::Vector2f(20, 20));
		rectangle.setFillColor(sf::Color::Green);
		rectangle.setPosition(std::get<0>(body_part) * 20, std::get<1>(body_part) * 20);
		window.draw(rectangle);
	}

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
