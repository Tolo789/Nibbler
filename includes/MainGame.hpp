#ifndef MAIN_GAME_HPP
# define MAIN_GAME_HPP

# include <stdlib.h>
# include <dlfcn.h>
# include <time.h>
# include <iostream>
# include <list>
# include <thread>
# include <iostream>
# include <chrono>
# include "IDynamicLibrary.hpp"

# define MIN_ARGC 3
# define MAX_ARGC 5
# define NO_WALL_OPTION "-w"
# define TWO_PLAYER_OPTION "-p"

# define DL_COUNT 3
# define DL1_NAME "glfw"
# define DL2_NAME "sdl"
# define DL3_NAME "sfml"
# define DL_PREFIX "dl_"
# define DL_POSTFIX ".so"

# define MIN_MAP_W 40
# define MIN_MAP_H 40
# define MAX_MAP_W 100
# define MAX_MAP_H 100

# define WINDOW_W 1100
# define WINDOW_H 1200
# define WINDOW_MIN_X_OFFSET 50
# define WINDOW_MIN_Y_OFFSET 100
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
# define KEY_W_LOWER "w"
# define KEY_A_LOWER "a"
# define KEY_S_LOWER "s"
# define KEY_D_LOWER "d"
# define KEY_LEFT "Left"
# define KEY_UP "Up"
# define KEY_RIGHT "Right"
# define KEY_DOWN "Down"

# define KEY_ESCAPE "Escape"

# define UP 1
# define DOWN 2
# define LEFT 3
# define RIGHT 4

# define FRAME_TIME	0.1f

class MainGame {
	private:
		static const std::string 	*dlArgvNames;
		static const std::string 	*dlNames;
		static const std::list<std::string> change_library_keys;
		static const std::vector<std::tuple<std::string, int>> change_direction_keys;
		static const std::vector<std::tuple<std::string, int>> change_direction_keys2;

		MainGame(void);
		MainGame(MainGame const & src);

		MainGame& operator=(MainGame const & rhs);

		int		dlerror_wrapper(void);
		void	print_usage(void);
		void	change_library_request(std::string key_code);
		void	update_game_state(void);
		int		update_gui(void);
		void	regulate_frame_sleep(void);
		void	change_direction_to(int &snake_direction, int &snake_direction_requested, int newDir);

		void	init_snakes(void);
		bool	will_snake_be_alive(void);
		void	move_snake(std::vector<std::tuple<int, int>> &snake_body, int &snake_dir);
		void	set_fruit_pos(void);

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
		bool	collide_with_walls;
		int		map_h;
		int		map_w;
		bool	two_player_game;
		int		score1;
		int		score2;
		bool	is_snake_alive;
		bool	has_shown_death;
		int		snake1_direction;
		int		snake1_direction_requested;
		int		snake2_direction;
		int		snake2_direction_requested;
		std::vector<std::tuple<int, int>>	snake1_body;
		std::vector<std::tuple<int, int>>	snake2_body;
		std::tuple<int, int>	fruit_pos;

	public:
		MainGame(int ac, char **av);
		~MainGame(void);

		int		run();
		void	button_pressed(const char *button);

		int		get_square_size(void);
		int		get_x_offset(void);
		int		get_y_offset(void);
		int		get_map_w(void);
		int		get_map_h(void);
		bool	is_two_player_game();
		int		get_score(void);
		bool	get_if_is_snake_alive(void);
		std::vector<std::tuple<int, int>>		&get_snake1_body(void);
		std::vector<std::tuple<int, int>>		&get_snake2_body(void);
		std::tuple<int, int>		&get_fruit_pos(void);
	

		bool	canRun;
};

#endif // !MAIN_GAME_HPP