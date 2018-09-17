#ifndef SFMLGUI_HPP
# define SFMLGUI_HPP

# include <iostream>
# include "FL/Fl.H"
# include "FL/Fl_Window.H"
# include "FL/Fl_Box.H"
# include "SFML/Window.hpp"
# include "SFML/Graphics.hpp"
# include "IDynamicLibrary.hpp"
# include "MainGame.hpp"


class SfmlGUI : public IDynamicLibrary {

    private:
		SfmlGUI(SfmlGUI const & src);

		SfmlGUI& operator=(SfmlGUI const & rhs);

		MainGame *mainGame;
		sf::RenderWindow window;

	public:
		// class MyFLWindow : public Fl_Window {
		// public:
		// 	MyFLWindow(int a, int b);
		// 	MyFLWindow(void);
		// 	~MyFLWindow(void) {};
		// 	// int handle(int event);
		// };
		SfmlGUI(MainGame *mainGame);
		SfmlGUI(void);
		~SfmlGUI(void);

		void	get_user_input(void);
		void	refresh_window();
		void	close_window();

		bool active;
};

extern "C" {
	SfmlGUI	*getGUI(MainGame *mainGame);
	void	deleteGUI(SfmlGUI *test);
}

#endif // !SFMLGUI_HPP