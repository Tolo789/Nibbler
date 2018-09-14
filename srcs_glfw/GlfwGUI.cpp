/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwGUI.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:46:10 by jichen-m          #+#    #+#             */
/*   Updated: 2018/09/14 11:31:02 by jichen-m         ###   ########.fr       */
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
	this->window = glfwCreateWindow(400, 400, "Nibbler GLFW", NULL, NULL);	// size of screen will change
	if (!this->window)
	{
		glfwTerminate();
		std::cout << "Failed to create windows GLFW" << std::endl;
		// return (-1);	//throw exception
	}
	glfwMakeContextCurrent(this->window);
	while(!glfwWindowShouldClose(this->window))
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// // update other events like input handling 
		glfwSetWindowUserPointer(window, this);
		glfwSetKeyCallback(window, key_callback);
		glfwPollEvents();
		// // put the stuff we've been drawing onto the display
		glfwSwapBuffers(this->window);
	}
	glfwDestroyWindow(this->window);
	glfwTerminate();
	// return (0);
}

void GlfwGUI::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_ESCAPE)
	        glfwSetWindowShouldClose(window, GL_TRUE);
		MainGame::get_instance().button_pressed(glfwGetKeyName(key, scancode));
	}
	(void)key;
	(void)scancode;
	(void)action;
	(void)window;
	(void)mods;
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
