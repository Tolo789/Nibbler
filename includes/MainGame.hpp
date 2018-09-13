#ifndef MAIN_GAME_HPP
# define MAIN_GAME_HPP

# include <dlfcn.h>
# include <iostream>
# include "IDynamicLibrary.hpp"

# define DL_COUNT 3
# define DL1_NAME "dl_sdl.so"
# define DL2_NAME "dl_glfw.so"
# define DL3_NAME "dl3.so" // TODO

# define GUI_CREATOR_FUNC "getGUI"
# define GUI_DESTRUCTOR_FUNC "deleteGUI"
# define REFRESH_WINDOW_FUNC refresh_window
# define CLOSE_WINDOW_FUNC close_window

class MainGame {
	private:
		MainGame(void);
		MainGame(MainGame const & src);

		MainGame& operator=(MainGame const & rhs);

		int		dlerror_wrapper();

	public:
		static const std::string *dlNames;

		MainGame(int ac, char **av);
		~MainGame(void);

		int	run();

		bool	running;
};

#endif // !MAIN_GAME_HPP