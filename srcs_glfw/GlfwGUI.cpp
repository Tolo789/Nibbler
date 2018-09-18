/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwGUI.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:46:10 by jichen-m          #+#    #+#             */
/*   Updated: 2018/09/18 18:33:56 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GlfwGUI.hpp"

// === CONSTRUCTOR =============================================================

GlfwGUI::GlfwGUI(MainGame *_mainGame)
{
	this->mainGame = _mainGame;
	std::cout << "GLFW window" << std::endl;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		throw new IDynamicLibrary::DynamicLibraryException();
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	this->window = glfwCreateWindow(WINDOW_W, WINDOW_H, "Nibbler GLFW", NULL, NULL);	// size of screen will change
	if (!this->window)
	{
		glfwTerminate();
		std::cout << "Failed to create windows GLFW" << std::endl;
		throw new IDynamicLibrary::DynamicLibraryException();
	}
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(window, (mode->width / 2) - (WINDOW_W / 2), (mode->height / 2) - (WINDOW_H / 2));
	glfwMakeContextCurrent(this->window);
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
	glfwPollEvents();

	square_size = mainGame->get_square_size();
	x_offset = mainGame->get_x_offset();
	y_offset = mainGame->get_y_offset();

	//get top left of game screen
	start_x = -((WINDOW_W / 2.0f) - x_offset) / (WINDOW_W / 2.0f);
	start_y = ((WINDOW_H / 2.0f) - y_offset) / (WINDOW_H / 2.0f);

	//get the size of each square in the game screen
	square_percent_y = start_y / (_mainGame->get_map_h() / 2.0f);
	square_percent_x = (-start_x) / (_mainGame->get_map_w() / 2.0f);

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

// === PRIVATE FUNCS ===========================================================

void	GlfwGUI::init_buffer(int x, int y)
{
	float start_coor_X = start_x + (x * square_percent_x);
	float start_coor_Y = start_y - (y * square_percent_y);

	//POINTS
	float points[] = {
	start_coor_X, start_coor_Y,  0.0f,
	start_coor_X, start_coor_Y - square_percent_y,  0.0f,
	start_coor_X + square_percent_x, start_coor_Y,  0.0f,
	
	start_coor_X + square_percent_x, start_coor_Y,  0.0f,
	start_coor_X + square_percent_x, start_coor_Y - square_percent_y, 0.0f,
	start_coor_X, start_coor_Y - square_percent_y,  0.0f
	};

	 //BUFFER
	vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void	GlfwGUI::init_shaders(void)
{
	//shader pour les vertex
	vertex_shader =
	"#version 400\n"
	"in vec3 vp;"
	"void main() {"
	"  gl_Position = vec4(vp, 1.0);"
	"}";

	//shader pour dessiner ce qu'il y a entre les vertex
	fragment_shader =
	"#version 400\n"
	"out vec4 frag_colour;"
	"void main() {"
	"  frag_colour = vec4(1.0, 1.0, 1.0, 1.0);"
	"}";

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	//check if shaders compile fail
	GLint status;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
		std::cout << "Vertex Shader compile failed" << std::endl;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
		std::cout << "Fragment Shader compile failed" << std::endl;
}

void	GlfwGUI::init_programme(void)
{
	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
}

void	GlfwGUI::create_border(void)
{
	float vertex_border[] = 
	{
		start_x, start_y, 0.0f,
		-(start_x), start_y, 0.0f,

		-(start_x), start_y, 0.0f,
		-(start_x), -(start_y), 0.0f,

		-(start_x), -(start_y), 0.0f,
		start_x, -(start_y), 0.0f,
				
		start_x, -(start_y), 0.0f,
		start_x, start_y, 0.0f
	};

	 //BUFFER
	vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_border), vertex_border, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	init_shaders();
	init_programme();
	glUseProgram(shader_programme);
	glBindVertexArray(vao);
	//drawing all the vertex of the triangle
	glDrawArrays(GL_LINE_LOOP, 0, 8);

}

// === END PRIVATE FUNCS =======================================================

// === OVERRIDES ===============================================================
void	GlfwGUI::get_user_input(void)
{
	glfwPollEvents();
}

void	GlfwGUI::refresh_window(std::vector<std::tuple<int, int>> snake_body)
{
	(void) snake_body;
	//only for test to see if each frame change color
	// this->counter = this->counter + 0.2f;
	if (this->counter == 1.0f)
		this->counter = 0.0f;
	glClearColor(this->counter, this->counter, this->counter,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	create_border();

	for (std::tuple<int, int> &body_part : snake_body) // access by reference to avoid copying
	{  
		init_buffer(std::get<0>(body_part), std::get<1>(body_part));
		init_shaders();
		init_programme();
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		//drawing all the vertex of the triangle
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
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

void GlfwGUI::error_callback(int error, const char* description)
{
	std::cerr << "Error n." << error << ": " << description << std::endl;
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
