#include "glew/include/GL/glew.h"
#include "glfw/include/GLFW/glfw3.h"
#include "json/single_include/nlohmann/json.hpp"
#include "glm/glm/glm.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

struct vertex {

};

void LoadModel(float &positions, unsigned int &indices, const std::string &path) {
	// TODO
}

void LoadShader(std::string &shader, const std::string &path) {
	std::ifstream file(path);
	std::stringstream buffer;
	buffer << file.rdbuf();

	shader = buffer.str();
}

static unsigned int CompileShader(unsigned int type, const std::string &source) {
	// pointer?
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	// specifying the source of our shader
	glShaderSource(id, 1, &src, nullptr);
	//
	glCompileShader(id);
	// TODO compilation error handling
	return id;
}

void AddShader(const std::string &shaderSource, unsigned int type, unsigned int program) {
	// pointer?
	unsigned int shader = CompileShader(type, shaderSource);

	glAttachShader(program, shader);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(shader);
}

int main()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "OpenGL Project", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << "\n";

	std::cout << glGetString(GL_VERSION) << "\n";

	float positions[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0,
		 0.5f,  0.5f, 0.21f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	// size is component count
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, static_cast<const void*>(0));

	unsigned int indexBufferObject;
	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	std::string vertexShader;
	std::string fragmentShader;
	LoadShader(vertexShader, "shaders/basic_vertex.glsl");
	LoadShader(fragmentShader, "shaders/basic_fragment.glsl");
	unsigned int shaderProgram = glCreateProgram();
	AddShader(vertexShader, GL_VERTEX_SHADER, shaderProgram);
	AddShader(fragmentShader, GL_FRAGMENT_SHADER, shaderProgram);
	glUseProgram(shaderProgram);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Drawcall
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}