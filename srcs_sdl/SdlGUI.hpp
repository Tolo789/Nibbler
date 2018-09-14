#ifndef SDLGUI_HPP
# define SDLGUI_HPP

# include <iostream>
# include "SDL2/SDL.h"
# include "IDynamicLibrary.hpp"


class SdlGUI : public IDynamicLibrary {
    private:
		SdlGUI(SdlGUI const & src);

		SdlGUI& operator=(SdlGUI const & rhs);

		SDL_Window *screen;
		bool quit = false;

	public:
		SdlGUI(void);
		~SdlGUI(void);

		void	refresh_window();
		void	close_window();
		void	set_quit_loop();

        bool    active;
};

extern "C" {
	SdlGUI	*getGUI(void);
	void	deleteGUI(SdlGUI *test);
}

#endif // !SDLGUI_HPP