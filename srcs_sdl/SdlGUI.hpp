#ifndef SDLGUI_HPP
# define SDLGUI_HPP

# include <iostream>
# include "IDynamicLibrary.hpp"


class SdlGUI : public IDynamicLibrary {
	public:
		SdlGUI(void);
		~SdlGUI(void);

		void	my_func();
};

extern "C" {
	SdlGUI	*getGUI(void);
	void	deleteGUI(SdlGUI *test);
}

#endif // !SDLGUI_HPP