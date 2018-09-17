#include "test3.hpp"

// === CONSTRUCTOR =============================================================


// Test3::MyFLWindow::MyFLWindow(int a, int b) : Fl_Window(a, b) {
// 	return ;
// }

// Test3::MyFLWindow::MyFLWindow(void) : Fl_Window(300, 500) {
// 	return ;
// }

Test3::Test3(MainGame *mainGame) : mainGame(mainGame), window(sf::VideoMode(200, 200), "SFML works!") {
    // window.create(sf::VideoMode(300, 500), "Test");
	// window = new Test3::MyFLWindow(300,180);
	// Fl_Box *box = new Fl_Box(20,40,260,100,"Hello, World!");
	// box->box(FL_UP_BOX);
	// box->labelsize(36);
	// box->labelfont(FL_BOLD+FL_ITALIC);
	// box->labeltype(FL_SHADOW_LABEL);
	// window->end();
	// char **str;
	// str = (char**)malloc(sizeof(char**) * 4);
	// *str = (char*)malloc(sizeof(char*) * 4);
	// str[0][1] = 'a';
	// str[0][1] = 0;
	// window->show(0, str);
    // Fl::run();

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
	std::cout << "Key '" << "" << "' was pressed" << std::endl;
    mainGame->button_pressed("");
}


// int Test3::MyFLWindow::handle(int event) {
//    switch (event)
//    {
// 		std::cout << "Handling event '" << event << "'" << std::endl;
//       case FL_FOCUS:
//       case FL_UNFOCUS:
//          return 1;

//       case FL_KEYBOARD:
//          int key = Fl::event_key();
// 		std::cout << "Key '" << key << "' was pressed: " << Fl::event_text() << std::endl;
//          switch (key)
//          {
//             case FL_Left:
//                redraw();
//                return 1;

//             case FL_Right:
//                redraw();
//                return 1;
//          }
//    }

//    return Fl_Window::handle(event);
// }

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
    

    // while (window.isOpen())
    // {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        window.draw(shape);
        window.display();
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
