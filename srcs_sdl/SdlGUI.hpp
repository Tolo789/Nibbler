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

		void	events_thread(void);

		SDL_Window *screen;
		std::thread	slave_thread;
		bool quit;

	public:
		SdlGUI(void);
		~SdlGUI(void);

		void	refresh_window();
		void	close_window();

        bool    active;
};

extern "C" {
	SdlGUI	*getGUI(void);
	void	deleteGUI(SdlGUI *test);
}

#endif // !SDLGUI_HPP