/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwGUI.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:46:17 by jichen-m          #+#    #+#             */
/*   Updated: 2018/09/13 15:16:17 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFWGUI_HPP
# define GLFWGUI_HPP

# include <iostream>
# include "IDynamicLibrary.hpp"
#include "GLFW/glfw3.h"


class GlfwGUI: public IDynamicLibrary
{
    private:
		GlfwGUI(GlfwGUI const & src);

		GlfwGUI& operator=(GlfwGUI const & rhs);

		GLFWwindow*	window;

    public:
        GlfwGUI(void);
        ~GlfwGUI(void);

		void	refresh_window();
		void	close_window();

        bool    active;
};

extern "C"
{
	GlfwGUI	*getGUI(void);
	void	deleteGUI(GlfwGUI *test);
}

#endif