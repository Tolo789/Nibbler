#include "SdlGUI.hpp"
#include "SDL2/SDL.h"

SdlGUI::SdlGUI(void) {

}

SdlGUI::~SdlGUI(void) {
	
}

void	SdlGUI::my_func() {
	std::cout << "SDL window" << std::endl;

	bool quit = false;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window * screen = SDL_CreateWindow("My SDL Empty Window",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
 
    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }
	}
	
	SDL_DestroyWindow(screen);
 
    SDL_Quit();
}

SdlGUI	*getGUI() {
	return new SdlGUI;
}

void	deleteGUI(SdlGUI *test) {
	delete test;
}