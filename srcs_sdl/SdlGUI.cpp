#include "SdlGUI.hpp"

// === CONSTRUCTOR =============================================================

SdlGUI::SdlGUI(MainGame *mainGame) : mainGame(mainGame) {
	std::cout << "SDL window" << std::endl;

	renderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_CreateWindow("Nibbler SDL",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);
	if (!screen) {
		std::cout << "Failed to initialize SDL" << std::endl;
		throw new IDynamicLibrary::DynamicLibraryException();
	}
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	// screenSurface = SDL_GetWindowSurface( screen );

	square_size = mainGame->get_square_size();
	x_offset = mainGame->get_x_offset();
	y_offset = mainGame->get_y_offset();

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
	// counter = (counter + 30) % 255;
	//set background color
	SDL_SetRenderDrawColor( renderer, counter, counter, counter, 255 );
	SDL_RenderClear(renderer);

	// Add map outlines
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	pos.x = x_offset;
	pos.y = y_offset - OUTLINE_TICKNESS;
	pos.w = WINDOW_W - 2 * x_offset;
	pos.h = OUTLINE_TICKNESS;
	SDL_RenderFillRect(renderer, &pos); // upLine
	pos.x = x_offset;
	pos.y = WINDOW_H - y_offset;
	pos.w = WINDOW_W - 2 * x_offset;
	pos.h = OUTLINE_TICKNESS;
	SDL_RenderFillRect(renderer, &pos); // downLine
	pos.x = x_offset - OUTLINE_TICKNESS;
	pos.y = y_offset;
	pos.w = OUTLINE_TICKNESS;
	pos.h = WINDOW_H - 2 * y_offset;
	SDL_RenderFillRect(renderer, &pos); // leftLine
	pos.x = WINDOW_W - x_offset;
	pos.y = y_offset;
	pos.w = OUTLINE_TICKNESS;
	pos.h = WINDOW_H - 2 * y_offset;
	SDL_RenderFillRect(renderer, &pos); // rightLine

	// Draw snake
	for (std::tuple<int, int> &body_part : snake_body) // access by reference to avoid copying
	{  
		//create a rect at pos 50,50 with a W=50/H=50
		pos.x = x_offset + std::get<0>(body_part) * square_size;
		pos.y = y_offset + std::get<1>(body_part) * square_size;
		pos.w = square_size;
		pos.h = square_size;
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
