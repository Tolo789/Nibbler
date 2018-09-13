#ifndef TEST3_HPP
# define TEST3_HPP

# include <iostream>
# include "IDynamicLibrary.hpp"


class Test3 : public IDynamicLibrary {
	public:
		Test3(void);
		~Test3(void);

		void	my_func();
};

extern "C" {
	Test3	*getGUI(void);
	void	deleteGUI(Test3 *test);
}

#endif // !TEST3_HPP