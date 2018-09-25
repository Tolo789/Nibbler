#include "SfmlGUI.hpp"

// === CONSTRUCTOR =============================================================

SfmlGUI::SfmlGUI(MainGame *mainGame) : mainGame(mainGame), window(sf::VideoMode(WINDOW_W, WINDOW_H), "Nibbler SFML", sf::Style::Titlebar) {
	window.setKeyRepeatEnabled(false);
	window.setPosition(sf::Vector2i(
		(sf::VideoMode::getDesktopMode().width / 2) - (WINDOW_W / 2),
		(sf::VideoMode::getDesktopMode().height / 2) - (WINDOW_H / 2))
	);

	square_size = mainGame->get_square_size();
	x_offset = mainGame->get_x_offset();
	y_offset = mainGame->get_y_offset();

	// if (!font.loadFromFile("fonts/Snake Chan.ttf"))
	if (!fontEnd.loadFromFile("fonts/Kasnake.ttf"))
	{
		std::cerr << "Error while loading font" << std::endl;
		throw new IDynamicLibrary::DynamicLibraryException();
	}
	if (!fontScore.loadFromFile("fonts/Montague.ttf"))
	{
		std::cerr << "Error while loading font" << std::endl;
		throw new IDynamicLibrary::DynamicLibraryException();
	}

	// Load Texture
	if (!grass.loadFromFile("./Textures/Grass.png") || !apple.loadFromFile("./Textures/Apple1.png") ||
		!meat.loadFromFile("./Textures/Meat.png") || !rock.loadFromFile("./Textures/Rock.png") ||
		!head_down.loadFromFile("./Textures/HeadDOWN.png") || !head_down2.loadFromFile("./Textures/HeadDOWN2.png") ||
		!head_up.loadFromFile("./Textures/HeadUP.png") || !head_up2.loadFromFile("./Textures/HeadUP2.png") ||
		!head_left.loadFromFile("./Textures/HeadLEFT.png") || !head_left2.loadFromFile("./Textures/HeadLEFT2.png") ||
		!head_right.loadFromFile("./Textures/HeadRIGHT.png") || !head_right2.loadFromFile("./Textures/HeadRIGHT2.png") ||
		!snake_body.loadFromFile("./Textures/SnakeBody.png") || !snake_body2.loadFromFile("./Textures/SnakeBody2.png")
		)
	{
		std::cout << "Failed to load Texture in Sfml" << std::endl;
		return ;
	}
	apple.setSmooth(true);
	rock.setSmooth(true);
	meat.setSmooth(true);

	head_down.setSmooth(true);
	head_up.setSmooth(true);
	head_left.setSmooth(true);
	head_right.setSmooth(true);
	snake_body.setSmooth(true);

	head_down2.setSmooth(true);
	head_up2.setSmooth(true);
	head_left2.setSmooth(true);
	head_right2.setSmooth(true);
	snake_body2.setSmooth(true);
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

// === PRIVATE FUNCS ===========================================================
void	SfmlGUI::draw_end_text(void) {
	sf::Text text;
	text.setFont(fontEnd); // font is a sf::Font
	text.setString("Game Over");
	text.setCharacterSize(WINDOW_MIN_Y_OFFSET / 2); // in pixels, not points!
	text.setFillColor(sf::Color::Green);
	text.setPosition(WINDOW_W / 3, WINDOW_H - y_offset + (y_offset / 4));
	// text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	// Must be between window.clear() and window.display()
	window.draw(text);
}

void	SfmlGUI::draw_score(int score, std::string player)
{
	sf::Text text;
	text.setFont(fontScore); // font is a sf::Font
	text.setString(std::string("Player ") + player + ": " + std::to_string(score));
	text.setCharacterSize(WINDOW_MIN_Y_OFFSET / 4); // in pixels
	text.setFillColor(sf::Color::White);
	text.setPosition(x_offset + 10, (player.compare("1") == 0) ? y_offset - (3 * WINDOW_MIN_Y_OFFSET / 4) : y_offset - (2 * WINDOW_MIN_Y_OFFSET / 4));
	// text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	// Must be between window.clear() and window.display()
	window.draw(text);
}

void	SfmlGUI::draw_special_timer(std::string toprint)
{
	if (toprint.empty())
		return ;
	sf::Text text;
	text.setFont(fontScore); // font is a sf::Font
	text.setString(toprint);
	text.setCharacterSize(WINDOW_MIN_Y_OFFSET / 3); // in pixels, not points!
	text.setFillColor(sf::Color::White);
	text.setPosition(WINDOW_W - x_offset - 70, y_offset - (2 * WINDOW_MIN_Y_OFFSET / 3));
	// text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	// Must be between window.clear() and window.display()
	window.draw(text);
}

void	SfmlGUI::draw_map_outline(void)
{
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
}

void	SfmlGUI::set_background_texture(void)
{
	grass.setRepeated(true);
	sprite.setTexture(grass);
	sprite.setTextureRect(sf::IntRect(0, 0, square_size * mainGame->get_map_w(), square_size * mainGame->get_map_h()));
	sprite.setPosition(x_offset , y_offset);
	window.draw(sprite);
}

void	SfmlGUI::add_fruits(sf::RectangleShape &rectangle)
{
	rectangle.setTexture(&apple, true);
	rectangle.setFillColor(sf::Color::White);
	rectangle.setPosition(x_offset + std::get<0>(mainGame->get_fruit_pos()) * square_size,
					y_offset + std::get<1>(mainGame->get_fruit_pos()) * square_size);
	window.draw(rectangle);

	//add special fruit
	if (std::get<0>(mainGame->get_special_fruit_pos()) >= 0 && std::get<1>(mainGame->get_special_fruit_pos()) >= 0)
	{
		rectangle.setTexture(&meat, true);
		rectangle.setFillColor(sf::Color::White);
		rectangle.setPosition(x_offset + std::get<0>(mainGame->get_special_fruit_pos()) * square_size,
							y_offset + std::get<1>(mainGame->get_special_fruit_pos()) * square_size);
		window.draw(rectangle);
		draw_special_timer(mainGame->get_special_fruit_timer());
	}
}

void	SfmlGUI::add_snakes(sf::RectangleShape &rectangle)
{
	bool	snake_head = true;
	int snake_direction;

	snake_direction = mainGame->get_snake1_direction();
	for (std::tuple<int, int> &body_part : mainGame->get_snake1_body()) // access by reference to avoid copying
	{
		if (snake_head)
		{
			switch(snake_direction)
			{
				case UP:
					rectangle.setTexture(&head_up, true);
					break ;
				case DOWN:
					rectangle.setTexture(&head_down, true);
					break ;
				case LEFT:
					rectangle.setTexture(&head_left, true);
					break ;
				default:
					rectangle.setTexture(&head_right, true);
					break ;
			}
			snake_head = false;
		}
		else
			rectangle.setTexture(&snake_body, true);
		rectangle.setFillColor(sf::Color::White);
		rectangle.setPosition(x_offset + std::get<0>(body_part) * square_size, y_offset + std::get<1>(body_part) * square_size);
		window.draw(rectangle);
	}
	if (mainGame->is_two_player_game()) {
		snake_direction = mainGame->get_snake2_direction();
		snake_head = true;
		for (std::tuple<int, int> &body_part : mainGame->get_snake2_body()) // access by reference to avoid copying
		{
			if (snake_head)
			{
				switch(snake_direction)
				{
					case UP:
						rectangle.setTexture(&head_up2, true);
						break ;
					case DOWN:
						rectangle.setTexture(&head_down2, true);
						break ;
					case LEFT:
						rectangle.setTexture(&head_left2, true);
						break ;
					default:
						rectangle.setTexture(&head_right2, true);
						break ;
				}
				snake_head = false;
			}
			else
				rectangle.setTexture(&snake_body2, true);
			rectangle.setPosition(x_offset + std::get<0>(body_part) * square_size, y_offset + std::get<1>(body_part) * square_size);
			window.draw(rectangle);
		}
		// Draw score for Player 2
		draw_score(mainGame->get_score2(), "2");
	}
}

void	SfmlGUI::add_obstacles(sf::RectangleShape &rectangle)
{
	for (std::tuple<int, int> &obstacle : mainGame->get_obstacles()) // access by reference to avoid copying
	{
		rectangle.setTexture(&rock, true);
		rectangle.setFillColor(sf::Color::White);
		rectangle.setPosition(x_offset + std::get<0>(obstacle) * square_size, y_offset + std::get<1>(obstacle) * square_size);
		window.draw(rectangle);
	}
}

// === END PRIVATE FUNCS =======================================================

// === OVERRIDES ===============================================================

void	SfmlGUI::get_user_input(void) {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed) {
			std::string str;
			// SFML doesnt have any internal func to convert KeyCode to string
			if (event.key.code == sf::Keyboard::Escape)
				mainGame->button_pressed(NULL);
			else {
				if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z)
					str = std::string(1, 'A' + (event.key.code - sf::Keyboard::A));
				else if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9)
					str = std::string(1, '0' + (event.key.code - sf::Keyboard::Num0));
				else if (event.key.code >= sf::Keyboard::Numpad0 && event.key.code <= sf::Keyboard::Numpad9)
					str = std::string(1, '0' + (event.key.code - sf::Keyboard::Numpad0));

				else if (event.key.code == sf::Keyboard::Left)
					str = std::string(KEY_LEFT);
				else if (event.key.code == sf::Keyboard::Up)
					str = std::string(KEY_UP);
				else if (event.key.code == sf::Keyboard::Right)
					str = std::string(KEY_RIGHT);
				else if (event.key.code == sf::Keyboard::Down)
					str = std::string(KEY_DOWN);
				mainGame->button_pressed(str.c_str());
			}
		}
	}
}

void	SfmlGUI::refresh_window(void) {
	window.clear(sf::Color::Black); // Can set background color here
	if (!mainGame->get_if_is_snake_alive())
		draw_end_text();

	// Draw score for Player 1
	draw_score(mainGame->get_score(), "1");

	// Add map outlines
	draw_map_outline();

	// Set background with Texture
	set_background_texture();
	
	sf::RectangleShape rectangle(sf::Vector2f(square_size, square_size));
	// Add snake
	add_snakes(rectangle);

	// Add fruit
	add_fruits(rectangle);

	// Add obstacles
	if (mainGame->get_obstacles_available())
		add_obstacles(rectangle);

	//put everyting to screen
	window.display();
}

void	SfmlGUI::close_window() {
	// std::cout << "Destroing SFML window" << std::endl;
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
