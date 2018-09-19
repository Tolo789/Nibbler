#ifndef SFMLGUI_HPP
# define SFMLGUI_HPP

# include <iostream>
# include "SFML/Window.hpp"
# include "SFML/Graphics.hpp"
# include "IDynamicLibrary.hpp"
# include "MainGame.hpp"


class SfmlGUI : public IDynamicLibrary {

    private:
		SfmlGUI(SfmlGUI const & src);

		SfmlGUI& operator=(SfmlGUI const & rhs);

		void	draw_end_text(void);

		MainGame *mainGame;
		sf::RenderWindow window;
		sf::Font font;

		int		x_offset;
		int		y_offset;
		int		square_size;

	public:
		SfmlGUI(MainGame *mainGame);
		SfmlGUI(void);
		~SfmlGUI(void);

		void	get_user_input(void);
		void	refresh_window(std::vector<std::tuple<int, int>> &snake_body, std::tuple<int, int> &fruit_pos);
		void	close_window();

		bool active;
};

extern "C" {
	SfmlGUI	*getGUI(MainGame *mainGame);
	void	deleteGUI(SfmlGUI *test);
}

#endif // !SFMLGUI_HPP