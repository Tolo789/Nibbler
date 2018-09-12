#ifndef TEST1_HPP
# define TEST1_HPP

# include <iostream>
# include "IDynamicLibrary.hpp"


class Test1 : public IDynamicLibrary {
	public:
		Test1(void);
		~Test1(void);

		void	my_func();
};

extern "C" {
	Test1	*getTest(void);
	void	deleteTest(Test1 *test);
}

#endif // !TEST1_HPP