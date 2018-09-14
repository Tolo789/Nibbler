#include "MainGame.hpp"

// === CONSTRUCTOR =============================================================

MainGame::MainGame(void) {
	return ;
}

MainGame::MainGame(int ac, char **av) {
	// TODO parse options
	ac = 0;
	if (!av)
		return ;
	running = false;
}

MainGame::MainGame(MainGame const & src) {
	*this = src;
	return ;
}

MainGame::~MainGame(void) {
	return ;
}

// === ENDCONSTRUCTOR ==========================================================

// === GETTER ===============================================================

MainGame	MainGame::get_instance()
{
	return (instance);
}

// === OPERATORS ===============================================================

MainGame& MainGame::operator=(MainGame const & rhs) {
	this->running = rhs.running;
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
	int		requested_index = std::stoi(key_code) - 1;

	std::cout << "Change index of library to: " << requested_index << std::endl;
	if (requested_index > 0 && requested_index < DL_COUNT)
		dl_index = requested_index;
}

void	MainGame::update_game_state(void) {
	// TODO: snake movement, collision detection, food spawn, etc
	if (dl_index == 0)
		running = false;
}

int		MainGame::update_gui(void) {
	// GUI logic
	// std::cout << "Enter library choice (1 / 2 / 3): ";
	// std::cin >> dl_index;
	if (dl_index < 0 || dl_index > DL_COUNT)
		std::cout << "Wrong number given..!" << std::endl;
	else if (dl_pastIndex != dl_index) {
		if (dl_pastIndex != -1) {
			// Close previous window
			currentLibrary->CLOSE_WINDOW_FUNC();
			void	*(*LibraryDestructor)(IDynamicLibrary *);
			LibraryDestructor = (void *(*)(IDynamicLibrary*)) dlsym(dl_handle, GUI_DESTRUCTOR_FUNC);
			if (!LibraryDestructor)
				return dlerror_wrapper();

			LibraryDestructor(currentLibrary);

			dlclose(dl_handle);
		}
		dl_pastIndex = dl_index;

		// Open dynamic library
		dl_handle = dlopen(dlNames[dl_index - 1].c_str(), RTLD_LAZY | RTLD_LOCAL);
		if (!dl_handle)
			return dlerror_wrapper();

		// Create interface class
		IDynamicLibrary	*(*LibraryCreator)(void);
		LibraryCreator = (IDynamicLibrary *(*)(void)) dlsym(dl_handle, GUI_CREATOR_FUNC);
		if (!LibraryCreator)
			return dlerror_wrapper();
		currentLibrary = LibraryCreator();

	}

	// Draw window with game infos
	currentLibrary->REFRESH_WINDOW_FUNC(); // TODO: give new snake pos + other infos

	return EXIT_SUCCESS;
}

void	MainGame::regulate_frame_sleep(void) {
	// Timer logic, make thread sleep if needed
	past_frame_length = difftime(timer, time(NULL));
	if (past_frame_length < FRAME_TIME) {
		std::this_thread::sleep_for (std::chrono::milliseconds(static_cast<int>((FRAME_TIME - past_frame_length) * 1000)));
	}
	std::cout << "frame" << std::endl;
	timer = time(NULL);
}

// === END PRIVATE FUNCS =======================================================


// === PUBLIC FUNCS ============================================================
int		MainGame::run(void) {
	// init vars
	running = true;
	dl_index = 1; // TODO let choose starting library with argv
	dl_pastIndex = -1;
	timer = time(NULL);

	// Start game loop
	while (running) {
		update_game_state();

		int gui_ret = update_gui();
		if (gui_ret != EXIT_SUCCESS)
			return gui_ret;

		regulate_frame_sleep();
	}
	return EXIT_SUCCESS;
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

static std::string *generate_dlNames() {	// static here is "internal linkage"
   std::string *p = new std::string[DL_COUNT];
   p[0] = DL1_NAME;
   p[1] = DL2_NAME;
   p[2] = DL3_NAME;
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

MainGame MainGame::instance = MainGame();

// === END STATICVARS ==========================================================

// === OTHERS ==================================================================
// Entry point of the program
int		main(int ac, char **av) {
	int	ret;

	(void)ac;
	(void)av;
	ret = MainGame::get_instance().run();
	return ret;
}

// === END OTHERS ==============================================================
