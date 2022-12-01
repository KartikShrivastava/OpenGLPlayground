#include "engine.h"
#include "shape.h"
#include "triangle.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <memory>

void GlfwErrorCallback(int error, const char* description);

int main(int argc, char** argv) {
	// initialize glfw
	if (!glfwInit())
		std::cout << "ERR: Could not load glfw successfully" << std::endl;

	// set error callback to catch any glfw function call errors
	glfwSetErrorCallback(GlfwErrorCallback);

	// create window and context using glfw (OpenGL 4.6 API supported by Intel driver right now)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int viewportWidth = 640, viewportHeight = 480;
	GLFWwindow* window = glfwCreateWindow(viewportWidth, viewportHeight, "OpenGL Playground", NULL, NULL);
	if (!window)
		std::cout << "ERR: Failed to create gflw window" << std::endl;

	glfwMakeContextCurrent(window);
	// load opengl functions using glad
	gladLoadGL();

	// window coordinates from bottom left to top right
	glViewport(0, 0, viewportWidth, viewportHeight);

	std::unique_ptr<Shape> shape = std::make_unique<Triangle>();

	Engine engine;
	engine.SetupVertexShader(shape.get()->vertShaderPath);
	engine.SetupFragmentShader(shape.get()->fragShaderPath);
	engine.LinkShaders();
	engine.SetupGPUBuffers(shape.get());

	while (!glfwWindowShouldClose(window)) {
		glViewport(0, 0, viewportWidth, viewportHeight);
		glClearColor(0.01f, 0.01f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(engine.shaderProgram);
		glBindVertexArray(engine.shapeVAO);

		// DrawArrays method is used when we dont use indices for drawing triangles
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		// to make window interactable
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void GlfwErrorCallback(int error, const char* description) {
	std::cout << "ERR: Glfw: " << description << std::endl;
}