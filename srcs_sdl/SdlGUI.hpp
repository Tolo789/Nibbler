#ifndef SDLGUI_HPP
# define SDLGUI_HPP

# include <iostream>
# include "IDynamicLibrary.hpp"


class SdlGUI : public IDynamicLibrary {
    private:
		SdlGUI(SdlGUI const & src);

		SdlGUI& operator=(SdlGUI const & rhs);

	public:
		SdlGUI(void);
		~SdlGUI(void);

		void	my_func();

        bool    active;
};

extern "C" {
	SdlGUI	*getGUI(void);
	void	deleteGUI(SdlGUI *test);
}

#endif // !SDLGUI_HPP