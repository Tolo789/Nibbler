/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwGUI.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:46:17 by jichen-m          #+#    #+#             */
/*   Updated: 2018/09/17 17:31:42 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFWGUI_HPP
# define GLFWGUI_HPP

# include <iostream>
# include "GLFW/glfw3.h"
# include "IDynamicLibrary.hpp"
# include "MainGame.hpp"


class GlfwGUI: public IDynamicLibrary
{
    private:
		static void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void error_callback(int error, const char* description);

		GlfwGUI(GlfwGUI const & src);

		GlfwGUI& operator=(GlfwGUI const & rhs);

		GLFWwindow*	window;
		float		counter;

    public:
		static MainGame *mainGame;

        GlfwGUI(MainGame *mainGame);
        GlfwGUI(void);
        ~GlfwGUI(void);

		void	get_user_input(void);
		void	refresh_window(std::vector<std::tuple<int, int>>);
		void	close_window();

        bool    active;
};

extern "C"
{
	GlfwGUI	*getGUI(MainGame *mainGame);
	void	deleteGUI(GlfwGUI *test);
}

#endif