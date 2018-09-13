/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwGUI.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:46:10 by jichen-m          #+#    #+#             */
/*   Updated: 2018/09/13 15:26:58 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GlfwGUI.hpp"

// === CONSTRUCTOR =============================================================

GlfwGUI::GlfwGUI(void) {
	return ;
}

GlfwGUI::GlfwGUI(GlfwGUI const & src) {
	*this = src;
	return ;
}

GlfwGUI::~GlfwGUI(void) {
	return ;
}

// === ENDCONSTRUCTOR ==========================================================

// === OPERATORS ===============================================================

GlfwGUI& GlfwGUI::operator=(GlfwGUI const & rhs) {
    this->active = rhs.active;
	return *this;
}

// === ENDOPERATORS ============================================================

// === OVERRIDES ===============================================================

void	GlfwGUI::refresh_window()
{
	std::cout << "GLFW window" << std::endl;
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		// return (-1);	//throw exception
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	this->window = glfwCreateWindow(640, 480, "Nibbler GLFW", NULL, NULL);	// size of screen will change
	if (!this->window)
	{
		glfwTerminate();
		std::cout << "Failed to create windows GLFW" << std::endl;
		// return (-1);	//throw exception
	}

	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(this->window);
	while(!glfwWindowShouldClose(this->window))
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// update other events like input handling 
		glfwPollEvents();
		// glfwSetKeyCallback(window, key_callback);

		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(this->window);
	}
	// glfwTerminate();
	// return (0);
}

void GlfwGUI::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		std::cout << "Key1 pressed" << std::endl;
	window = NULL;
	scancode = 0;
	mods = 0;
}

void	GlfwGUI::close_window() {
    std::cout << "Destroing Glfw window" << std::endl;
	glfwDestroyWindow(this->window);
	glfwTerminate();
	// SDL_DestroyWindow(screen);
    // SDL_Quit();
}
// === END OVERRIDES ===========================================================

// === OTHERS ==================================================================
GlfwGUI	*getGUI() {
	return new GlfwGUI;
}

void	deleteGUI(GlfwGUI *test) {
	delete test;
}
// === END OTHERS ==============================================================
