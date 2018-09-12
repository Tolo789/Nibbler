#include "test1.hpp"
#include "SDL2/SDL.h"

Test1::Test1(void) {

}

Test1::~Test1(void) {
	
}

void	Test1::my_func() {
	std::cout << "DL1 (class) func called" << std::endl;

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

Test1	*getTest() {
	return new Test1;
}

void	deleteTest(Test1 *test) {
	delete test;
}