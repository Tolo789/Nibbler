/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfwGUI.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:46:10 by jichen-m          #+#    #+#             */
/*   Updated: 2018/09/12 20:27:35 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glfwGUI.hpp"
#include "GLFW/glfw3.h"

GlfwGUI::GlfwGUI(void){}

GlfwGUI::~GlfwGUI(void){}

void	GlfwGUI::my_func()
{
	GLFWwindow*	window;

	std::cout << "DL2 (class) func called" << std::endl;
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		// return (-1);	//throw exception
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(640, 480, "Nibbler GLFW", NULL, NULL);	// size of screen will change
	if (!window)
	{
		glfwTerminate();
		std::cout << "Failed to create windows GLFW" << std::endl;
		// return (-1);	//throw exception
	}
	glfwMakeContextCurrent(window);
	while(!glfwWindowShouldClose(window))
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	// return (0);
}

GlfwGUI	*getTest() {
	return new GlfwGUI;
}

void	deleteTest(GlfwGUI *test) {
	delete test;
}