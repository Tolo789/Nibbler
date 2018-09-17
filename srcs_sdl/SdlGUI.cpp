#include "SdlGUI.hpp"

// === CONSTRUCTOR =============================================================

SdlGUI::SdlGUI(MainGame *mainGame) : mainGame(mainGame) {
	std::cout << "SDL window" << std::endl;

	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_CreateWindow("My SDL Empty Window",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	if (!screen) {
		std::cout << "Failed to initialize SDL" << std::endl;
		throw new IDynamicLibrary::DynamicLibraryException();
	}
	screenSurface = SDL_GetWindowSurface( screen );
	counter = 0;

	return ;
}

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

// === PRIVATE FUNCS ===========================================================
void	SdlGUI::get_user_input(void) {
	SDL_Event	event;

	/* Poll for events */
	while( SDL_PollEvent( &event ) )
	{
		switch( event.type )
		{
			case SDL_KEYDOWN:
				std::cout << SDL_GetKeyName( event.key.keysym.sym ) << std::endl;
				mainGame->button_pressed(SDL_GetKeyName(event.key.keysym.sym));
				break;
			default:
				break;
		}
	}
}
// === END PRIVATE FUNCS =======================================================

// === OVERRIDES ===============================================================
void	SdlGUI::refresh_window() {
	// add/update/remove elems (snake, fruits, points) from window
	counter = (counter + 30) % 255;
	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, counter, counter, counter ) );
	
	//Update the surface
	SDL_UpdateWindowSurface( screen );
}

void	SdlGUI::close_window() {
	std::cout << "Destroing SDL window" << std::endl;
	if (screen)
		SDL_DestroyWindow(screen);
	SDL_Quit();
}

// === END OVERRIDES ===========================================================

// === OTHERS ==================================================================
SdlGUI	*getGUI(MainGame *mainGame) {
	return new SdlGUI(mainGame);
}

void	deleteGUI(SdlGUI *test) {
	delete test;
}
// === END OTHERS ==============================================================
