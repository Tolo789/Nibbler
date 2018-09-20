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
		void	draw_score(int score, std::string player);
		void	draw_special_timer(std::string toprint);

		MainGame *mainGame;
		sf::RenderWindow window;
		sf::Font fontEnd;
		sf::Font fontScore;

		int		x_offset;
		int		y_offset;
		int		square_size;

	public:
		SfmlGUI(MainGame *mainGame);
		SfmlGUI(void);
		~SfmlGUI(void);

		void	get_user_input(void);
		void	refresh_window(void);
		void	close_window(void);

		bool active;
};

extern "C" {
	SfmlGUI	*getGUI(MainGame *mainGame);
	void	deleteGUI(SfmlGUI *test);
}

#endif // !SFMLGUI_HPP