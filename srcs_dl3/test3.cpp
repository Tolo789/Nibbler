#include "test3.hpp"
// #include "SFML/Window.hpp"
#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Box.H"

// === CONSTRUCTOR =============================================================

Test3::Test3(MainGame *mainGame) : mainGame(mainGame) {
	Fl_Window *window = new Fl_Window(300,180);
	Fl_Box *box = new Fl_Box(20,40,260,100,"Hello, World!");
	box->box(FL_UP_BOX);
	box->labelsize(36);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	char **str;
	str = (char**)malloc(sizeof(char**) * 4);
	*str = (char*)malloc(sizeof(char*) * 4);
	str[0][1] = 'a';
	str[0][1] = 0;
	window->show(0, str);
	Fl::ready();
	return ;
}
Test3::Test3(void) {
	return ;
}

Test3::Test3(Test3 const & src) {
	*this = src;
	return ;
}

Test3::~Test3(void) {
	return ;
}

// === ENDCONSTRUCTOR ==========================================================

// === OPERATORS ===============================================================

Test3& Test3::operator=(Test3 const & rhs) {
    this->active = rhs.active;
	return *this;
}

// === ENDOPERATORS ============================================================

// === OVERRIDES ===============================================================

void	Test3::get_user_input(void) {
	std::cout << "Key '" <<  Fl::event_text() << "' was pressed" << std::endl;
}

void	Test3::refresh_window() {
	std::cout << "DL func called" << std::endl;
	
    // sf::Window window(sf::VideoMode(800, 600), "My window");

    // // run the program as long as the window is open
    // while (window.isOpen())
    // {
    //     // check all the window's events that were triggered since the last iteration of the loop
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         // "close requested" event: we close the window
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }
	// }


	// Fl::run();e
	// Fl::redraw();
}

void	Test3::close_window() {
    std::cout << "Destroing Test3 window" << std::endl;
	// SDL_DestroyWindow(screen);
    // SDL_Quit();
}
// === END OVERRIDES ===========================================================

// === OTHERS ==================================================================
Test3	*getGUI(MainGame *mainGame) {
	return new Test3(mainGame);
}

void	deleteGUI(Test3 *test) {
	delete test;
}
// === END OTHERS ==============================================================
