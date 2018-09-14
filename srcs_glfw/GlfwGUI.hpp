/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwGUI.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:46:17 by jichen-m          #+#    #+#             */
/*   Updated: 2018/09/13 17:10:09 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFWGUI_HPP
# define GLFWGUI_HPP

# include <iostream>
# include "IDynamicLibrary.hpp"
# include "MainGame.hpp"
# include "GLFW/glfw3.h"


class GlfwGUI: public IDynamicLibrary
{
    private:
		static void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		GlfwGUI(GlfwGUI const & src);

		GlfwGUI& operator=(GlfwGUI const & rhs);

		GLFWwindow*	window;

    public:
        GlfwGUI(MainGame *mainGame);
        GlfwGUI(void);
        ~GlfwGUI(void);

		void	get_user_input(void);
		void	refresh_window();
		void	close_window();

		MainGame *mainGame;
        bool    active;
};

extern "C"
{
	GlfwGUI	*getGUI(MainGame *mainGame);
	void	deleteGUI(GlfwGUI *test);
}

#endif