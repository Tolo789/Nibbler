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
	Test3	*getTest(void);
	void	deleteTest(Test3 *test);
}

#endif // !TEST3_HPP