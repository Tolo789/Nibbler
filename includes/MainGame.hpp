#ifndef MAIN_GAME_HPP
# define MAIN_GAME_HPP

# include <dlfcn.h>
# include <iostream>
# include <list>
# include <thread>
# include <dlfcn.h>
# include <iostream>
# include <time.h>
# include <chrono>
# include "IDynamicLibrary.hpp"

# define MIN_ARGC 3

# define DL_COUNT 3
# define DL1_NAME "sdl"
# define DL2_NAME "glfw"
# define DL3_NAME "sfml"
# define DL_PREFIX "dl_"
# define DL_POSTFIX ".so"

# define MIN_MAP_W 44
# define MIN_MAP_H 36
# define MAX_MAP_W 110
# define MAX_MAP_H 90

# define WINDOW_W 1200
# define WINDOW_H 1000
# define WINDOW_MIN_X_OFFSET 50
# define WINDOW_MIN_Y_OFFSET 50
# define MIN_SQUARE_SIZE 10
# define MAX_SQUARE_SIZE 25
# define OUTLINE_TICKNESS 2

# define GUI_CREATOR_FUNC "getGUI"
# define GUI_DESTRUCTOR_FUNC "deleteGUI"
# define GET_USER_INPUT_FUNC get_user_input
# define REFRESH_WINDOW_FUNC refresh_window
# define CLOSE_WINDOW_FUNC close_window

# define KEY_0 "0"
# define KEY_1 "1"
# define KEY_2 "2"
# define KEY_3 "3"
# define KEY_W "W"
# define KEY_A "A"
# define KEY_S "S"
# define KEY_D "D"
# define KEY_ESCAPE "Escape"

# define FRAME_TIME	1.0

typedef int intCustom;

class MainGame {
	private:
		static const std::string 	*dlArgvNames;
		static const std::string 	*dlNames;
		static const std::list<std::string> change_library_keys;
		// static const std::list<std::string> change_direction_keys;

		MainGame(void);
		MainGame(MainGame const & src);

		MainGame& operator=(MainGame const & rhs);

		int		dlerror_wrapper();
		void	change_library_request(std::string key_code);
		void	update_game_state(void);
		int		update_gui(void);
		void	regulate_frame_sleep(void);

		void	init_snake(void);

		// Graphic libraries vars
		int		square_size;
		int		x_offset;
		int		y_offset;
		IDynamicLibrary	*currentLibrary;
		void	*dl_handle;
		int		dl_index;
		int		dl_pastIndex;
		time_t	timer;
		double	past_frame_length;

		// Game model vars
		bool	running;
		int		map_w;
		int		map_h;
		std::vector<std::tuple<int, int>>	snake_body;

	public:
		MainGame(int ac, char **av);
		~MainGame(void);

		int		run();
		void	button_pressed(const char *button);

		int		get_square_size(void);
		int		get_x_offset(void);
		int		get_y_offset(void);

		bool	canRun;
};

#endif // !MAIN_GAME_HPP