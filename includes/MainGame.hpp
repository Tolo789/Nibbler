#ifndef MAIN_GAME_HPP
# define MAIN_GAME_HPP

# include <dlfcn.h>
# include <iostream>
# include <list>
# include "IDynamicLibrary.hpp"

# define DL_COUNT 3
# define DL1_NAME "dl_sdl.so"
# define DL2_NAME "dl_glfw.so"
# define DL3_NAME "dl3.so" // TODO

# define GUI_CREATOR_FUNC "getGUI"
# define GUI_DESTRUCTOR_FUNC "deleteGUI"
# define REFRESH_WINDOW_FUNC refresh_window
# define CLOSE_WINDOW_FUNC close_window

# define KEY_1 "1"
# define KEY_2 "2"
# define KEY_3 "3"
# define KEY_W "W"
# define KEY_A "A"
# define KEY_S "S"
# define KEY_D "D"
# define KEY_ESCAPE "Escape"

class MainGame {
	private:
		static MainGame		instance;
		static const std::string 	*dlNames;
		static const std::list<std::string> change_library_keys;

		MainGame(void);
		MainGame(MainGame const & src);

		MainGame& operator=(MainGame const & rhs);

		int		dlerror_wrapper();
		void	change_library_request(std::string key_code);

		// std::list<std::string> change_snake_keys;

	public:
		static MainGame				get_instance(void);

		MainGame(int ac, char **av);
		~MainGame(void);

		int		run();
		void	button_pressed(const char *button);
		bool	running;
};

#endif // !MAIN_GAME_HPP