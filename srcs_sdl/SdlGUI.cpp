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

	bool quit = false;
	SDL_Event	event;
 
	SDL_Init(SDL_INIT_VIDEO);
 
	screen = SDL_CreateWindow("My SDL Empty Window",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	
 
	while (!quit)
	{
	   /* Poll for events */
		while( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
				case SDL_KEYDOWN:
					std::cout << SDL_GetKeyName( event.key.keysym.sym ) << std::endl;
					MainGame::get_instance().button_pressed(SDL_GetKeyName(event.key.keysym.sym));
					if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "Escape") == 0) //tmp
						quit = true;
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
	SDL_DestroyWindow(screen);
	SDL_Quit(); 
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
