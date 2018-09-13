#ifndef TEST3_HPP
# define TEST3_HPP

# include <iostream>
# include "IDynamicLibrary.hpp"


class Test3 : public IDynamicLibrary {
    private:
		Test3(Test3 const & src);

		Test3& operator=(Test3 const & rhs);

	public:
		Test3(void);
		~Test3(void);

		void	refresh_window();
		void	close_window();

        bool    active;
};

extern "C" {
	Test3	*getGUI(void);
	void	deleteGUI(Test3 *test);
}

#endif // !TEST3_HPP