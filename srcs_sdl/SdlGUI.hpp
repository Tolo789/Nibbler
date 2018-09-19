#ifndef SDLGUI_HPP
# define SDLGUI_HPP

# include <iostream>
# include <thread>
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"
# include "IDynamicLibrary.hpp"
# include "MainGame.hpp"

class SdlGUI : public IDynamicLibrary {
    private:
		SdlGUI(SdlGUI const & src);

		SdlGUI& operator=(SdlGUI const & rhs);

		void	draw_end_text(void);

		SDL_Window *screen;
		// SDL_Surface* screenSurface;
		// bool quit;
		int counter;

		SDL_Renderer	*renderer;
		SDL_Rect		pos;

		int		x_offset;
		int		y_offset;
		int		square_size;

	public:
		SdlGUI(MainGame *mainGame);
		SdlGUI(void);
		~SdlGUI(void);

		void	get_user_input(void);
		void	refresh_window(void);
		void	close_window(void);

        bool    active;
		MainGame *mainGame;
};

extern "C" {
	SdlGUI	*getGUI(MainGame *mainGame);
	void	deleteGUI(SdlGUI *test);
}

#endif // !SDLGUI_HPP