#include "test1.hpp"
#include <SDL.h>

Test1::Test1(void) {

}

Test1::~Test1(void) {
	
}

void	Test1::my_func() {
	std::cout << "DL1 (class) func called" << std::endl;
	SDL_Init(SDL_INIT_VIDEO);
}

Test1	*getTest() {
	return new Test1;
}

void	deleteTest(Test1 *test) {
	delete test;
}