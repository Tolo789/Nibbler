#include "test3.hpp"
#include "SFML/Window.hpp"

Test3::Test3(void) {

}

Test3::~Test3(void) {
	
}

void	Test3::my_func() {
	std::cout << "SFML window" << std::endl;
	
    sf::Window window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
	}
}

Test3	*getTest() {
	return new Test3;
}

void	deleteTest(Test3 *test) {
	delete test;
}