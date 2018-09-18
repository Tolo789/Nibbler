#include "MainGame.hpp"

// === CONSTRUCTOR =============================================================

MainGame::MainGame(void) {
	return ;
}

MainGame::MainGame(int ac, char **av) {
	// TODO set message if smth is wrong
	canRun = false;
	if (ac < MIN_ARGC) {
		std::cerr << "Not enough arguments ! (Usage: ./nibbler map_width map_height)" << std::endl;
		return ;
	}
	map_w = atoi(av[1]);
	map_h = atoi(av[2]);
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
	running = false;
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

void	MainGame::change_library_request(std::string key_code) {
	int		requested_index = std::stoi(key_code);

	std::cout << "Change index of library to: " << requested_index << std::endl;
	if (requested_index >= 0 && requested_index <= DL_COUNT) {
		dl_index = requested_index;
	}
}

void	MainGame::update_game_state(void) {
	// TODO: snake movement, collision detection, food spawn, etc
	std::cout << "Updating with user input" << dl_index << std::endl;
	if (currentLibrary) {
		currentLibrary->GET_USER_INPUT_FUNC();
	}
	if (dl_index == 0) {
		std::cout << "Need to close.." << std::endl;
		running = false;
	}

	//snake moving forward
	// for (std::vector<std::tuple<int, int>>::iterator it = snake_body.end() ; it != snake_body.begin(); --it)
	// {
	// 	if (it == snake_body.begin())
	// 	{
	// 		std::get<0>(*(it)) = std::get<0>(*(it)) + 1;
	// 	}
	// 	else
	// 	{
	// 		std::get<0>(*(it)) = std::get<0>(*(--it));
	// 		std::get<1>(*(it)) = std::get<1>(*(--it));
	// 	}
		
	// }
}

int		MainGame::update_gui(void) {
	if (dl_index < 0 || dl_index > DL_COUNT)
		std::cout << "Wrong number given..!" << std::endl;
	else if (dl_pastIndex != dl_index) {
		if (dl_pastIndex > 0) {
			std::cout << "Closing old GUI" << std::endl;
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
			std::cout << "Opening new GUI" << std::endl;

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
	if (currentLibrary)
		currentLibrary->REFRESH_WINDOW_FUNC(snake_body); // TODO: give new snake pos + other infos

	return EXIT_SUCCESS; 
}

void	MainGame::regulate_frame_sleep(void) {
	// Timer logic, make thread sleep if needed
	past_frame_length = difftime(timer, time(NULL));
	if (past_frame_length < FRAME_TIME) {
		std::this_thread::sleep_for (std::chrono::milliseconds(static_cast<int>((FRAME_TIME - past_frame_length) * 1000)));
	}
	// std::cout << "frame" << std::endl;
	timer = time(NULL);
}

void	MainGame::init_snake(void)
{
	snake_body = std::vector<std::tuple<int, int>>();
	snake_body.push_back(std::make_tuple(map_w / 2, map_h / 2));
	snake_body.push_back(std::make_tuple(map_w / 2, (map_h / 2) - 1));
	snake_body.push_back(std::make_tuple(map_w / 2, (map_h / 2) - 2));
	snake_body.push_back(std::make_tuple(map_w / 2, (map_h / 2) - 3));

}

// === END PRIVATE FUNCS =======================================================


// === PUBLIC FUNCS ============================================================
int		MainGame::run(void) {
	if (!canRun)
		return EXIT_FAILURE;
	int gui_ret;

	// init vars
	currentLibrary = NULL;
	running = true;
	dl_index = 2; // TODO let choose starting library with argv
	dl_pastIndex = -1;
	timer = time(NULL);

	//init snake
	init_snake();

	// Start game loop
	while (running) {
		std::cout << "-- Frame --" << std::endl;
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

	std::list<std::string>::const_iterator iter = std::find(change_library_keys.begin(), change_library_keys.end(), key);
	if (iter != change_library_keys.end()) {
		change_library_request(key);
	}
	else {
		std::cout << "value not useful.." << std::endl;

		// iter = change_direction_keys.find(button_pressed);
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

// === END STATICVARS ==========================================================

// === OTHERS ==================================================================
// Entry point of the program
int		main(int ac, char **av) {
	int	ret = 0;

	try {
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
