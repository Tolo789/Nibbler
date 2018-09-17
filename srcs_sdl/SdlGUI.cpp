#include "SdlGUI.hpp"

// === CONSTRUCTOR =============================================================

SdlGUI::SdlGUI(MainGame *mainGame) : mainGame(mainGame) {
	std::cout << "SDL window" << std::endl;

	renderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_CreateWindow("My SDL Empty Window",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	if (!screen) {
		std::cout << "Failed to initialize SDL" << std::endl;
		throw new IDynamicLibrary::DynamicLibraryException();
	}
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	// screenSurface = SDL_GetWindowSurface( screen );
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
void	SdlGUI::refresh_window(std::vector<std::tuple<int, int>> snake_body) {
	//add/update/remove elems (snake, fruits, points) from window
	counter = (counter + 30) % 255;
	//set background color
	SDL_SetRenderDrawColor( renderer, counter, counter, counter, 255 );
	SDL_RenderClear(renderer);

	for (std::tuple<int, int> &body_part : snake_body) // access by reference to avoid copying
	{  
		//create a rect at pos 50,50 with a W=50/H=50
		pos.x = std::get<0>(body_part) * SQUARE_SIZE;
		pos.y = std::get<1>(body_part) * SQUARE_SIZE;
		pos.w = SQUARE_SIZE;
		pos.h = SQUARE_SIZE;
		//set background color for the "Snake"
		SDL_SetRenderDrawColor( renderer, 255, 55, 255, 255 );
		//render Rect
		SDL_RenderFillRect(renderer, &pos);
	}
	
	//render Rect to the screen
	SDL_RenderPresent(renderer);	
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
