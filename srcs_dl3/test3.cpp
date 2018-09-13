#include "test3.hpp"
#include "SFML/Window.hpp"
#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Box.H"

Test3::Test3(void) {

}

Test3::~Test3(void) {
	
}

void	Test3::my_func() {
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
	Fl::run();
}

Test3	*getGUI() {
	return new Test3;
}

void	deleteGUI(Test3 *test) {
	delete test;
}