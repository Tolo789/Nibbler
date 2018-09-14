#include <dlfcn.h>
#include <iostream>
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

// === END PRIVATE FUNCS =======================================================


// === PUBLIC FUNCS ============================================================
int		MainGame::run(void) {
	IDynamicLibrary	*(*LibraryCreator)(void);
	void	*(*LibraryDestructor)(IDynamicLibrary *);
	IDynamicLibrary	*currentLibrary;
	int		dl_index;
	void	*dl_handle;
	int		pastIndex = -1;

	running = true;
	while (running) {
		std::cout << "Enter library choice (1 / 2 / 3): ";
		std::cin >> dl_index;
		if (dl_index == 0)
			running = false;
		else if (dl_index < 0 || dl_index > DL_COUNT)
			std::cout << "Wrong number given..!" << std::endl;
		else if (pastIndex != dl_index) {
			if (pastIndex != -1) {
				// Close previous window
				currentLibrary->CLOSE_WINDOW_FUNC();
				LibraryDestructor = (void *(*)(IDynamicLibrary*)) dlsym(dl_handle, GUI_DESTRUCTOR_FUNC);
				if (!LibraryDestructor)
					return dlerror_wrapper();

				LibraryDestructor(currentLibrary);

				dlclose(dl_handle);
			}
			std::cout << pastIndex << std::endl;
			pastIndex = dl_index;

			// Open dynamic library
			dl_handle = dlopen(dlNames[dl_index - 1].c_str(), RTLD_LAZY | RTLD_LOCAL);
			if (!dl_handle)
				return dlerror_wrapper();

			// Create interface class
			LibraryCreator = (IDynamicLibrary *(*)(void)) dlsym(dl_handle, GUI_CREATOR_FUNC);
			if (!LibraryCreator)
				return dlerror_wrapper();
			currentLibrary = LibraryCreator();

			// Draw window with game infos
			currentLibrary->REFRESH_WINDOW_FUNC();
		}
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

void	MainGame::change_library_request(std::string key_code)
{
	int		requested_index = std::stoi(key_code);
	
	std::cout << "Change index of library to: " << requested_index << std::endl;
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
