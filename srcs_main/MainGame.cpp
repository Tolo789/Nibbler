#include "MainGame.hpp"

// === CONSTRUCTOR =============================================================

MainGame::MainGame(void) {
	return ;
}

MainGame::MainGame(int ac, char **av) {
	canRun = false;
	running = false;

	// First basic check
	if (ac < MIN_ARGC || ac > MAX_ARGC) {
		std::cerr << "Wrong number of arguments !" << std::endl;
		print_usage();
		return ;
	}

	// Options parsing
	collide_with_walls = true;
	two_player_game = false;
	int	i = 1;
	while (i < ac - 2) {
		if (std::string(NO_WALL_OPTION).compare(av[i]) == 0)
			collide_with_walls = false;
		else if (std::string(TWO_PLAYER_OPTION).compare(av[i]) == 0)
			two_player_game = true;
		else {
			std::cerr << "Unknown option given! (" << av[i] << ")" << std::endl;
			print_usage();
			return;
		}
		i++;
	}

	// Map size parsing
	map_w = atoi(av[i]);
	map_h = atoi(av[i + 1]);
	if (map_w < MIN_MAP_W || map_w > MAX_MAP_W) {
		std::cerr << "Map Width must be between " << MIN_MAP_W << " and " << MAX_MAP_W << " squares" << std::endl;
		return ;
	}
	if (map_h < MIN_MAP_H || map_h > MAX_MAP_H) {
		std::cerr << "Map Height must be between " << MIN_MAP_H << " and " << MAX_MAP_H << " squares" << std::endl;
		return ;
	}
	int maxSizeW = (WINDOW_W - 2 * WINDOW_MIN_X_OFFSET) / map_w;
	int maxSizeH = (WINDOW_H - 2 * WINDOW_MIN_Y_OFFSET) / map_h;
	square_size = (maxSizeH < maxSizeW) ? maxSizeH : maxSizeW;
	x_offset = (WINDOW_W - square_size * map_w) / 2;
	y_offset = (WINDOW_H - square_size * map_h) / 2;
	// Everything good
	canRun = true;
}

MainGame::MainGame(MainGame const & src) {
	*this = src;
	return ;
}

MainGame::~MainGame(void) {
	return ;
}

// === ENDCONSTRUCTOR ==========================================================

// === GETTER ==================================================================
int		MainGame::get_square_size(void) {
	return square_size;
}

int		MainGame::get_x_offset(void) {
	return x_offset;
}

int		MainGame::get_y_offset(void) {
	return y_offset;
}

int		MainGame::get_map_w(void) {
	return map_w;
}

int		MainGame::get_map_h(void) {
	return map_h;
}

bool	MainGame::is_two_player_game(void) {
	return two_player_game;
}

int		MainGame::get_score(void) {
	return score1;
}

int		MainGame::get_score2(void) {
	return score2;
}

bool	MainGame::get_if_is_snake_alive(void) {
	return is_snake_alive;
}

std::vector<std::tuple<int, int>>		&MainGame::get_snake1_body(void) {
	return snake1_body;
}

std::vector<std::tuple<int, int>>		&MainGame::get_snake2_body(void) {
	return snake2_body;
}

std::tuple<int, int>		&MainGame::get_fruit_pos(void) {
	return fruit_pos;
}

std::tuple<int, int>		&MainGame::get_special_fruit_pos(void) {
	return special_fruit_pos;
}

std::string		MainGame::get_special_fruit_timer(void)
{
	if (std::get<0>(special_fruit_pos) < 0 || !is_snake_alive)
		return "";
	else
	{
		std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - creation_precise_time);
		return (std::to_string((LIFE_TIME - time_span.count())).substr(0, 4));
	}
}

// === END GETTER ==============================================================


// === OPERATORS ===============================================================

MainGame& MainGame::operator=(MainGame const & rhs) {
	this->canRun = rhs.canRun;
	return *this;
}

// === ENDOPERATORS ============================================================

// === PRIVATE FUNCS ===========================================================

int		MainGame::dlerror_wrapper() {
	std::cerr << "My Custom Error: " << dlerror() << std::endl;
	running = false;
	return EXIT_FAILURE;
}

void	MainGame::print_usage(void) {
	std::cout << "Usage: ./nibbler [-option1] [-option2] map_width map_height" << std::endl;
	std::cout << "Available options:" << std::endl << "\t" << NO_WALL_OPTION << " -> disable wall collision" << std::endl;
	std::cout  << "\t" << TWO_PLAYER_OPTION << " -> two player game" << std::endl;
}

void	MainGame::change_library_request(std::string key_code) {
	int		requested_index = std::stoi(key_code);

	// std::cout << "Change index of library to: " << requested_index << std::endl;
	if (requested_index >= 0 && requested_index <= DL_COUNT) {
		dl_index = requested_index;
	}
}

void	MainGame::update_game_state(void) {
	// Get all pool events in library
	if (currentLibrary) {
		currentLibrary->GET_USER_INPUT_FUNC();
	}

	// Check if we want to close window, in this case no need to do further calculations
	if (dl_index == 0) {
		// std::cout << "Need to close.." << std::endl;
		running = false;
	}

	if (is_snake_alive && running) {
		if (snake1_direction_requested > 0) {
			snake1_direction = snake1_direction_requested;
			snake1_direction_requested = -1;
		}
		if (snake2_direction_requested > 0) {
			snake2_direction = snake2_direction_requested;
			snake2_direction_requested = -1;
		}
		is_snake_alive = will_snake_be_alive();
		if (!is_snake_alive) {
			std::cout << "Game Over !" << std::endl;
			return;
		}
		//snakes actual moving
		move_snake(snake1_body, snake1_direction, score1);
		if (two_player_game) {
			move_snake(snake2_body, snake2_direction, score2);
		}
		set_special_fruit_pos();
	}
}

int		MainGame::update_gui(void) {
	if (dl_index < 0 || dl_index > DL_COUNT) {
		std::cerr << "Wrong number given..!" << std::endl;
		return EXIT_FAILURE;
	}
	else if (dl_pastIndex != dl_index) {
		if (dl_pastIndex > 0) {
			// std::cout << "Closing old GUI" << std::endl;
			// Close previous window
			currentLibrary->CLOSE_WINDOW_FUNC();
			void	*(*LibraryDestructor)(IDynamicLibrary *);
			LibraryDestructor = (void *(*)(IDynamicLibrary*)) dlsym(dl_handle, GUI_DESTRUCTOR_FUNC);
			if (!LibraryDestructor)
				return dlerror_wrapper();

			LibraryDestructor(currentLibrary);
			currentLibrary = NULL;

			dlclose(dl_handle);
		}
		if (dl_index != 0) {
			// std::cout << "Opening new GUI" << std::endl;
			has_shown_death = false;

			// Open dynamic library
			dl_handle = dlopen(dlNames[dl_index - 1].c_str(), RTLD_LAZY | RTLD_LOCAL);
			if (!dl_handle)
				return dlerror_wrapper();

			// Create interface class
			IDynamicLibrary	*(*LibraryCreator)(MainGame*);
			LibraryCreator = (IDynamicLibrary *(*)(MainGame*)) dlsym(dl_handle, GUI_CREATOR_FUNC);
			if (!LibraryCreator)
				return dlerror_wrapper();
			try {
				currentLibrary = LibraryCreator(this);
			}
			catch (IDynamicLibrary::DynamicLibraryException e) {
				std::cerr << "Error while constructing Library" << std::endl;
				running = false;
				return EXIT_FAILURE;
			}
		}
		dl_pastIndex = dl_index;
	}

	// Draw window with game infos
	if (currentLibrary && !has_shown_death) {
		currentLibrary->REFRESH_WINDOW_FUNC();
		if (!is_snake_alive)
			has_shown_death = true;
	}

	return EXIT_SUCCESS;
}

void	MainGame::regulate_frame_sleep(void) {
	// Timer logic, make thread sleep if needed
	past_frame_length = difftime(timer, time(NULL));
	if (past_frame_length < frame_time) {
		std::this_thread::sleep_for (std::chrono::milliseconds(static_cast<int>((frame_time - past_frame_length) * 1000)));
	}
	// std::cout << "frame" << std::endl;
	timer = time(NULL);
}

void	MainGame::init_snakes(void)
{
	is_snake_alive = true;
	has_shown_death = false;

	snake1_body = std::vector<std::tuple<int, int>>();
	snake2_body = std::vector<std::tuple<int, int>>();

	if (two_player_game) {
		snake1_body.push_back(std::make_tuple(0, 3));
		snake1_body.push_back(std::make_tuple(0, 2));
		snake1_body.push_back(std::make_tuple(0, 1));
		snake1_body.push_back(std::make_tuple(0, 0));

		snake1_direction = DOWN;
		snake1_direction_requested = -1;

		snake2_body.push_back(std::make_tuple(map_w - 1, map_h - 4));
		snake2_body.push_back(std::make_tuple(map_w - 1, map_h - 3));
		snake2_body.push_back(std::make_tuple(map_w - 1, map_h - 2));
		snake2_body.push_back(std::make_tuple(map_w - 1, map_h - 1));

		snake2_direction = UP;
		snake2_direction_requested = -1;
	}
	else {
		snake1_body.push_back(std::make_tuple(map_w / 2, map_h / 2));
		snake1_body.push_back(std::make_tuple(map_w / 2, (map_h / 2) - 1));
		snake1_body.push_back(std::make_tuple(map_w / 2, (map_h / 2) - 2));
		snake1_body.push_back(std::make_tuple(map_w / 2, (map_h / 2) - 3));

		snake1_direction = (map_w > map_h) ? LEFT : DOWN;
		snake1_direction_requested = -1;
	}
	std::get<0>(special_fruit_pos) = -1;
	std::get<1>(special_fruit_pos) = -1;
	spawntime = time(NULL) + SPAWN_DELAY;
	set_fruit_pos();
}

bool	MainGame::will_snake_be_alive(void) {
	// Check for snake1
	int	headX = std::get<0>(snake1_body[0]);
	int	headY = std::get<1>(snake1_body[0]);
	int	head2X;
	int	head2Y;
	if (snake1_direction == UP)
		headY -= 1;
	else if (snake1_direction == DOWN)
		headY += 1;
	else if (snake1_direction == LEFT)
		headX -= 1;
	else if (snake1_direction == RIGHT)
		headX += 1;
	if (two_player_game) {
		head2X = std::get<0>(snake2_body[0]);
		head2Y = std::get<1>(snake2_body[0]);
		if (snake2_direction == UP)
			head2Y -= 1;
		else if (snake2_direction == DOWN)
			head2Y += 1;
		else if (snake2_direction == LEFT)
			head2X -= 1;
		else if (snake2_direction == RIGHT)
			head2X += 1;
	}

	// Check if he goes outside the map
	if (collide_with_walls) {
		if (headX == map_w || headY == map_h ||
			headX < 0 || headY < 0) {
			return false;
		}
		if (two_player_game && (head2X == map_w || head2Y == map_h ||
			head2X < 0 || head2Y < 0)) {
			return false;
		}
	}
	else {
		headX %= map_w;
		headY %= map_h;
		if (headX < 0)
			headX = map_w - 1;
		if (headY < 0)
			headY = map_h -1;
		if (two_player_game) {
			head2X %= map_w;
			head2Y %= map_h;
			if (head2X < 0)
				head2X = map_w - 1;
			if (head2Y < 0)
				head2Y = map_h -1;
		}
	}

	// Check self collision
	std::vector<std::tuple<int, int>>::iterator it;
	for (it = snake1_body.begin(); it != snake1_body.end() - 1; ++it ) {
		if (headX == std::get<0>(*it) && headY == std::get<1>(*it)) {
			return false;
		}
	}

	if (two_player_game) {
		if (headX == head2X && headY == head2Y)
			return false;
		// Check other snake collision
		for (it = snake2_body.begin(); it != snake2_body.end() - 1; ++it ) {
			if (headX == std::get<0>(*it) && headY == std::get<1>(*it)) {
				return false;
			}
		}

		// Check snake2 self collision
		for (it = snake2_body.begin(); it != snake2_body.end() - 1; ++it ) {
			if (head2X == std::get<0>(*it) && head2Y == std::get<1>(*it)) {
				return false;
			}
		}
		// Check snake2 other collision
		for (it = snake1_body.begin(); it != snake1_body.end() - 1; ++it ) {
			if (head2X == std::get<0>(*it) && head2Y == std::get<1>(*it)) {
				return false;
			}
		}
	}

	return true;
}

void	MainGame::move_snake(std::vector<std::tuple<int, int>> &snake_body, int &snake_dir, int &score) {
	bool	hasEat = false;
	bool	hasEatSpecial = false;
	int		tailX;
	int		tailY;

	std::vector<std::tuple<int, int>>::reverse_iterator prevIt;
	for (std::vector<std::tuple<int, int>>::reverse_iterator it = snake_body.rbegin(); it != snake_body.rend(); ++it ) {
		prevIt = it + 1;
		if (prevIt != snake_body.rend()) {
			if (it == snake_body.rbegin()) {
				tailX = std::get<0>(*(it));
				tailY = std::get<1>(*(it));
			}
			std::get<0>(*(it)) = std::get<0>(*(prevIt));
			std::get<1>(*(it)) = std::get<1>(*(prevIt));
		}
		else {
			// Advance based on direction
			if (snake_dir == UP)
				std::get<1>(*(it)) = std::get<1>(*(it)) - 1;
			else if (snake_dir == DOWN)
				std::get<1>(*(it)) = std::get<1>(*(it)) + 1;
			else if (snake_dir == LEFT)
				std::get<0>(*(it)) = std::get<0>(*(it)) - 1;
			else if (snake_dir == RIGHT)
				std::get<0>(*(it)) = std::get<0>(*(it)) + 1;

			// Teleport snake to other side of the map
			if (!collide_with_walls) {
				std::get<0>(*(it)) %= map_w;
				std::get<1>(*(it)) %= map_h;
				if (std::get<0>(*(it)) < 0)
					std::get<0>(*(it)) = map_w - 1;
				if (std::get<1>(*(it)) < 0)
					std::get<1>(*(it)) = map_h -1;
			}

			// Check if fruit has been ate
			if (std::get<0>(*(it)) == std::get<0>(fruit_pos) && std::get<1>(*(it)) == std::get<1>(fruit_pos)) {
				hasEat = true;
			}
			if (std::get<0>(*(it)) == std::get<0>(special_fruit_pos) && std::get<1>(*(it)) == std::get<1>(special_fruit_pos)){
				hasEatSpecial = true;
			}
		}
	}
	if (hasEat) {
		snake_body.push_back(std::make_tuple(tailX, tailY));
		// If no room is available, do not spawn new fruit
		if (snake1_body.size() + snake2_body.size() < (size_t) map_w * map_h)
			set_fruit_pos();
		else {
			std::get<0>(fruit_pos) = -1;
			std::get<1>(fruit_pos) = -1;
		}
		score += FRUIT_POINT;
	}
	if (hasEatSpecial) {
		snake_body.push_back(std::make_tuple(tailX, tailY));
		spawntime = time(NULL) + SPAWN_DELAY;
		std::get<0>(special_fruit_pos) = -1;
		std::get<1>(special_fruit_pos) = -1;
		score += SPECIAL_FRUIT_POINT;
	}

	// Update frame time
	if ((hasEat || hasEatSpecial) && frame_time > MIN_FRAME_TIME) {
		frame_time = INITIAL_FRAME_TIME - (FRAME_DECREASE_DELTA * ((score1 + score2) / POINT_DELTA_FRAME_DECRASE));
		// std::cout << frame_time << " -> " << (frame_time < MIN_FRAME_TIME ? MIN_FRAME_TIME : frame_time) << '\n';
		if (frame_time < MIN_FRAME_TIME)
			frame_time = MIN_FRAME_TIME;
	}
}

void	MainGame::change_direction_to(int &snake_direction, int &snake_direction_requested, int newDir) {
	if ((newDir == UP || newDir == DOWN) && (snake_direction == LEFT || snake_direction == RIGHT)) {
		snake_direction_requested = newDir;
	}
	else if ((newDir == LEFT || newDir == RIGHT) && (snake_direction == UP || snake_direction == DOWN)) {
		snake_direction_requested = newDir;
	}
}

void	MainGame::set_fruit_pos(void) {
	bool	is_good_pos;
	int		tmpX;
	int		tmpY;

	if (!is_snake_alive)
		return;
	do {
		is_good_pos = true;
		// generate random pos
		tmpX = rand() % map_w;
		tmpY = rand() % map_h;

		// check that newPos doesnt collide with other game objs
		std::vector<std::tuple<int, int>>::iterator it;
		for (it = snake1_body.begin(); it != snake1_body.end(); ++it ) {
			if (std::get<0>(*it) == tmpX && std::get<1>(*it) == tmpY) {
				is_good_pos = false;
				break;
			}
		}
		if (is_good_pos) {
			for (it = snake2_body.begin(); it != snake2_body.end(); ++it ) {
				if (std::get<0>(*it) == tmpX && std::get<1>(*it) == tmpY) {
					is_good_pos = false;
					break;
				}
			}
		}

	} while (!is_good_pos);
	std::get<0>(fruit_pos) = tmpX;
	std::get<1>(fruit_pos) = tmpY;
}

void	MainGame::set_special_fruit_pos(void)
{
	bool	is_good_pos;
	int		tmpX;
	int		tmpY;

	tmpX = 0;
	tmpY = 0;
	if (!is_snake_alive)
		return;
	if (std::get<0>(special_fruit_pos) >= 0)
	{
		//if fruit exist more than 5 seconds kill it
		if (time(NULL) >= deletetime)
		{
			std::get<0>(special_fruit_pos) = -1;
			std::get<1>(special_fruit_pos) = -1;
			spawntime = time(NULL) + SPAWN_DELAY;
		}
	}
	else
	{
		//if fruit doen't exist more than 10 seconds create one
		if (time(NULL) >= spawntime && snake1_body.size() + snake2_body.size() + 1 < (size_t) map_w * map_h)
		{
			do {
				is_good_pos = true;
				// generate random pos
				tmpX = rand() % map_w;
				tmpY = rand() % map_h;

				// check that newPos doesnt collide with other game objs
				std::vector<std::tuple<int, int>>::iterator it;
				for (it = snake1_body.begin(); it != snake1_body.end(); ++it ) {
					if (std::get<0>(*it) == tmpX && std::get<1>(*it) == tmpY) {
						is_good_pos = false;
						break;
					}
				}
				if (is_good_pos && two_player_game) {
					for (it = snake2_body.begin(); it != snake2_body.end(); ++it ) {
						if (std::get<0>(*it) == tmpX && std::get<1>(*it) == tmpY) {
							is_good_pos = false;
							break;
						}
					}
				}
			} while (!is_good_pos);
			std::get<0>(special_fruit_pos) = tmpX;
			std::get<1>(special_fruit_pos) = tmpY;
			deletetime = time(NULL) + LIFE_TIME;
			creation_precise_time = std::chrono::high_resolution_clock::now();
		}
	}
}

// === END PRIVATE FUNCS =======================================================


// === PUBLIC FUNCS ============================================================
int		MainGame::run(void) {
	if (!canRun)
		return EXIT_FAILURE;
	int gui_ret;

	// init vars
	frame_time = INITIAL_FRAME_TIME;
	currentLibrary = NULL;
	running = true;
	dl_index = 1; // TODO let choose starting library with argv
	dl_pastIndex = -1;
	timer = time(NULL);
	score1 = 0;
	score2 = 0;
	fruit_pos = std::make_tuple(0, 0);

	//init snake
	init_snakes();

	// Start game loop
	while (running) {
		// std::cout << "-- Frame --" << std::endl;
		update_game_state();

		gui_ret = update_gui();
		if (gui_ret != EXIT_SUCCESS || !running)
			return gui_ret;

		regulate_frame_sleep();
	}
	return gui_ret;
}

void	MainGame::button_pressed(const char *button)
{
	std::string key = !button ? KEY_ESCAPE : std::string(button); // GLFW sends NULL pointer for Escape key..

	// std::cout << "key '" << key << "' was pressed" << std::endl;
	std::list<std::string>::const_iterator iter = std::find(change_library_keys.begin(), change_library_keys.end(), key);
	if (iter != change_library_keys.end()) {
		change_library_request(key);
	}
	else {
		for (const std::tuple<std::string, int> &change_direction_pair : change_direction_keys) // access by reference to avoid copying
		{
			if (std::get<0>(change_direction_pair).compare(key) == 0) {
				change_direction_to(snake1_direction, snake1_direction_requested, std::get<1>(change_direction_pair));
				return ;
			}
		}
		for (const std::tuple<std::string, int> &change_direction_pair : change_direction_keys2) // access by reference to avoid copying
		{
			if (std::get<0>(change_direction_pair).compare(key) == 0) {
				change_direction_to(snake2_direction, snake2_direction_requested, std::get<1>(change_direction_pair));
				return ;
			}
		}
		// std::cout << "value not useful.." << std::endl;
	}
}

// === END PUBLIC FUNCS ========================================================

// === STATICVARS ==============================================================

static std::string *generate_dlArgvNames() {	// static here is "internal linkage"
   std::string *p = new std::string[DL_COUNT];
   p[0] = DL1_NAME;
   p[1] = DL2_NAME;
   p[2] = DL3_NAME;
   return p;
}
const std::string *MainGame::dlArgvNames = generate_dlArgvNames();

static std::string *generate_dlNames() {	// static here is "internal linkage"
   std::string *p = new std::string[DL_COUNT];
   p[0] = std::string(DL_PREFIX) + DL1_NAME + DL_POSTFIX;
   p[1] = std::string(DL_PREFIX) + DL2_NAME + DL_POSTFIX;
   p[2] = std::string(DL_PREFIX) + DL3_NAME + DL_POSTFIX;
   return p;
}
const std::string *MainGame::dlNames = generate_dlNames();

static std::list<std::string> generate_library_keys() {	// static here is "internal linkage"
	std::list<std::string> p;
	p.push_front(KEY_0);
	p.push_front(KEY_1);
	p.push_front(KEY_2);
	p.push_front(KEY_3);
	return p;
}
const std::list<std::string> MainGame::change_library_keys = generate_library_keys();

static std::vector<std::tuple<std::string, int>> generate_direction_keys() {	// static here is "internal linkage"
	std::vector<std::tuple<std::string, int>> p;
	p.push_back(std::make_tuple(KEY_W, UP));
	p.push_back(std::make_tuple(KEY_A, LEFT));
	p.push_back(std::make_tuple(KEY_S, DOWN));
	p.push_back(std::make_tuple(KEY_D, RIGHT));
	p.push_back(std::make_tuple(KEY_W_LOWER, UP));
	p.push_back(std::make_tuple(KEY_A_LOWER, LEFT));
	p.push_back(std::make_tuple(KEY_S_LOWER, DOWN));
	p.push_back(std::make_tuple(KEY_D_LOWER, RIGHT));
	return p;
}
const std::vector<std::tuple<std::string, int>> MainGame::change_direction_keys = generate_direction_keys();

static std::vector<std::tuple<std::string, int>> generate_direction_keys2() {	// static here is "internal linkage"
	std::vector<std::tuple<std::string, int>> p;
	p.push_back(std::make_tuple(KEY_UP, UP));
	p.push_back(std::make_tuple(KEY_LEFT, LEFT));
	p.push_back(std::make_tuple(KEY_DOWN, DOWN));
	p.push_back(std::make_tuple(KEY_RIGHT, RIGHT));
	return p;
}
const std::vector<std::tuple<std::string, int>> MainGame::change_direction_keys2 = generate_direction_keys2();
// === END STATICVARS ==========================================================

// === OTHERS ==================================================================
// Entry point of the program
int		main(int ac, char **av) {
	int	ret = 0;

	try {
		/* initialize random seed: */
		srand (time(NULL));
		MainGame mainGame(ac, av);
		ret = mainGame.run();
	}
	catch (...) {
		std::cerr << "Unkown error occurred when running game" << std::endl;
		return EXIT_FAILURE;

	}
	return ret;
}

// === END OTHERS ==============================================================
