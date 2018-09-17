#ifndef TEST3_HPP
# define TEST3_HPP

# include <iostream>
#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Box.H"
# include "IDynamicLibrary.hpp"
# include "MainGame.hpp"


class Test3 : public IDynamicLibrary {

    private:
		Test3(Test3 const & src);

		Test3& operator=(Test3 const & rhs);

	public:
		class MyFLWindow : public Fl_Window {
		public:
			MyFLWindow(int a, int b);
			MyFLWindow(void);
			~MyFLWindow(void) {};
			int handle(int event);
		};
		Test3(MainGame *mainGame);
		Test3(void);
		~Test3(void);

		void	get_user_input(void);
		void	refresh_window();
		void	close_window();

		MainGame *mainGame;
		MyFLWindow *window;
		bool active;
};

extern "C" {
	Test3	*getGUI(MainGame *mainGame);
	void	deleteGUI(Test3 *test);
}

#endif // !TEST3_HPP