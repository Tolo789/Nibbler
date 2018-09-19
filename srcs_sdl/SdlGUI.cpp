#include "SdlGUI.hpp"

// === CONSTRUCTOR =============================================================

SdlGUI::SdlGUI(MainGame *mainGame) : mainGame(mainGame) {
	std::cout << "SDL window" << std::endl;

	renderer = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) == -1 || TTF_Init() == -1) {
		std::cout << "Failed to initialize SDL" << std::endl;
		throw new IDynamicLibrary::DynamicLibraryException();
	}

	screen = SDL_CreateWindow("Nibbler SDL",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);
	if (!screen) {
		std::cout << "Failed to create SDL window" << std::endl;
		throw new IDynamicLibrary::DynamicLibraryException();
	}
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

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
void	SdlGUI::draw_end_text(void) {
	// TTF_Font* font = TTF_OpenFont("fonts/Kasnake.ttf", 24); //this opens a font style and sets a size
	TTF_Font* font = TTF_OpenFont("fonts/Snake Chan.ttf", 24); //this opens a font style and sets a size
	if (!font) {
		std::cerr << TTF_GetError() << std::endl;
		return;
	}
	SDL_Color White = {0, 255, 0, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Game Over", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect Message_rect; // Draw the text inside this rect
	Message_rect.w = (WINDOW_W - 2 * WINDOW_MIN_X_OFFSET) / 2;
	Message_rect.h = (WINDOW_MIN_Y_OFFSET - 0) / 2;
	Message_rect.x = (WINDOW_W - Message_rect.w) / 2;
	Message_rect.y = (WINDOW_MIN_Y_OFFSET - Message_rect.h) / 2;

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

	//Don't forget too free your font, surface and texture
	TTF_CloseFont(font);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}
// === END PRIVATE FUNCS =======================================================

// === OVERRIDES ===============================================================
void	SdlGUI::get_user_input(void) {
	SDL_Event	event;

	/* Poll for events */
	while( SDL_PollEvent( &event ) )
	{
		switch( event.type )
		{
			case SDL_KEYDOWN:
				// std::cout << SDL_GetKeyName( event.key.keysym.sym ) << std::endl;
				mainGame->button_pressed(SDL_GetKeyName(event.key.keysym.sym));
				break;
			default:
				break;
		}
	}
}

void	SdlGUI::refresh_window(void) {
	//set background color
	SDL_SetRenderDrawColor( renderer, counter, counter, counter, 255 );
	SDL_RenderClear(renderer);

	if (!mainGame->get_if_is_snake_alive())
		draw_end_text();

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
	pos.w = square_size;	// set van only once since it wont change
	pos.h = square_size;	// set van only once since it wont change
	for (std::tuple<int, int> &body_part : mainGame->get_snake_body()) // access by reference to avoid copying
	{
		//create a rect at pos 50,50 with a W=50/H=50
		pos.x = x_offset + std::get<0>(body_part) * square_size;
		pos.y = y_offset + std::get<1>(body_part) * square_size;
		//set background color for the "Snake"
		SDL_SetRenderDrawColor( renderer, 255, 55, 255, 255 );
		//render Rect
		SDL_RenderFillRect(renderer, &pos);
	}

	// Add fruit
	pos.x = x_offset + std::get<0>(mainGame->get_fruit_pos()) * square_size;
	pos.y = y_offset + std::get<1>(mainGame->get_fruit_pos()) * square_size;
	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
	SDL_RenderFillRect(renderer, &pos);
	
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
