#include "SdlGUI.hpp"

// === CONSTRUCTOR =============================================================

SdlGUI::SdlGUI(void) {
	return ;
}

SdlGUI::SdlGUI(SdlGUI const & src) {
	*this = src;
	return ;
}

SdlGUI::~SdlGUI(void) {
	return ;
}

// === ENDCONSTRUCTOR ==========================================================

// === OPERATORS ===============================================================

SdlGUI& SdlGUI::operator=(SdlGUI const & rhs) {
    this->active = rhs.active;
	return *this;
}

// === ENDOPERATORS ============================================================

// === OVERRIDES ===============================================================
void	SdlGUI::refresh_window() {
	std::cout << "SDL window" << std::endl;

	// bool quit = false;
    // SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    screen = SDL_CreateWindow("My SDL Empty Window",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    
 
<<<<<<< HEAD
    while (!quit)
    {
       /* Poll for events */
        while( SDL_PollEvent( &event ) )
        {
            switch( event.type )
            {
                /* Keyboard event */
                /* Pass the event data onto PrintKeyInfo() */
                case SDL_KEYDOWN:
                    std::cout << "Key pressed" << std::endl;
                    break;

                /* SDL_QUIT event (window close) */
                case SDL_QUIT:
                    quit = 1;
                    break;

                default:
                    break;
            }
        }
    } 
=======
    // while (!quit)
    // {
    //     SDL_WaitEvent(&event);
 
    //     switch (event.type)
    //     {
    //         case SDL_QUIT:
    //             quit = true;
    //             break;
    //     }
	// } 
>>>>>>> 7019c87deea48529d9f870304ff8c7db913d7142
}

void	SdlGUI::close_window() {
    std::cout << "Destroing SDL window" << std::endl;
	SDL_DestroyWindow(screen);
    SDL_Quit();
}

// === END OVERRIDES ===========================================================

// === OTHERS ==================================================================
SdlGUI	*getGUI() {
	return new SdlGUI;
}

void	deleteGUI(SdlGUI *test) {
	delete test;
}
// === END OTHERS ==============================================================
