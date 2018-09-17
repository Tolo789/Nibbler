#ifndef SDLGUI_HPP
# define SDLGUI_HPP

# include <iostream>
# include <thread>
# include "SDL2/SDL.h"
# include "IDynamicLibrary.hpp"
# include "MainGame.hpp"


class SdlGUI : public IDynamicLibrary {
    private:
		SdlGUI(SdlGUI const & src);

		SdlGUI& operator=(SdlGUI const & rhs);


		SDL_Window *screen;
		// SDL_Surface* screenSurface;
		// bool quit;
		int counter;

		SDL_Renderer	*renderer;
		SDL_Rect		pos;


	public:
		SdlGUI(MainGame *mainGame);
		SdlGUI(void);
		~SdlGUI(void);

		void	get_user_input(void);
		void	refresh_window(std::vector<std::tuple<int, int>>);
		void	close_window();

        bool    active;
		MainGame *mainGame;
};

extern "C" {
	SdlGUI	*getGUI(MainGame *mainGame);
	void	deleteGUI(SdlGUI *test);
}

#endif // !SDLGUI_HPP