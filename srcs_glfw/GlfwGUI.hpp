/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwGUI.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:46:17 by jichen-m          #+#    #+#             */
/*   Updated: 2018/09/18 18:22:02 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFWGUI_HPP
# define GLFWGUI_HPP

# define GLFW_INCLUDE_GLCOREARB

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

		void	init_buffer(int x, int y);
		void	init_shaders(void);
		void	init_programme(void);
		void	create_border(void);

		GLFWwindow*	window;
		float		counter;
		int		x_offset;
		int		y_offset;
		int		square_size;
		float	start_x;
		float	start_y;
		float	square_percent_y;
		float	square_percent_x;


		GLuint		vbo;
		GLuint		vao;
		const char	*vertex_shader;
		const char	*fragment_shader;
		GLuint		vs;
		GLuint		fs;
		GLuint		shader_programme;




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