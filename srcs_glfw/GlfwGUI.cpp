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

GlfwGUI::GlfwGUI(MainGame *_mainGame) //: tmpMainGame(_mainGame)
{
	this->mainGame = _mainGame;
	std::cout << "GLFW window" << std::endl;
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		throw new IDynamicLibrary::DynamicLibraryException();
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
		throw new IDynamicLibrary::DynamicLibraryException();
	}
	glfwMakeContextCurrent(this->window);
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
	glfwPollEvents();
	this->counter = 0.0f;
	return ;
}
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
void	GlfwGUI::get_user_input(void)
{
	glfwPollEvents();
}

void	GlfwGUI::refresh_window()
{
	//only for test to see if each frame change color
	this->counter = this->counter + 0.2f;
	if (this->counter == 1.0f)
		this->counter = 0.0f;
	glClearColor(this->counter, this->counter, this->counter,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(this->window);
}

void GlfwGUI::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE)
	{
		std::cout << "key was pressed" << std::endl;
		mainGame->button_pressed(glfwGetKeyName(key, scancode));
	}
	(void)key;
	(void)scancode;
	(void)action;
	(void)window;
	(void)mods;
}

void	GlfwGUI::close_window()
{
    std::cout << "Destroing Glfw window" << std::endl;
	if (window)
		glfwDestroyWindow(this->window);
	glfwTerminate();
}
// === END OVERRIDES ===========================================================

// === OTHERS ==================================================================
GlfwGUI	*getGUI(MainGame *mainGame) {
	return new GlfwGUI(mainGame);
}

void	deleteGUI(GlfwGUI *test) {
	delete test;
}
// === END OTHERS ==============================================================

MainGame *GlfwGUI::mainGame = NULL;
