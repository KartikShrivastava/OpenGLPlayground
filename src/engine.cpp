#include "engine.h"
#include "shape.h"

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <string>

Engine::Engine() {
	// keep track of shaders using this shaderProgram id
	shaderProgram = glCreateProgram();
	shapeVAO = -1;
	posVBO = -1;
}

Engine::~Engine() {
	// delete shader program
	glDeleteBuffers(1, &posVBO);
	glDeleteVertexArrays(1, &shapeVAO);
	glDeleteProgram(shaderProgram);
}

void Engine::SetupGPUBuffers(Shape *shape) {
	glGenVertexArrays(1, &shapeVAO);
	glGenBuffers(1, &posVBO);

	// vertex array should be binded before buffer object (as VAO holds several VBO, so like a parent)
	glBindVertexArray(shapeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);

	// put the vertex date into vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * shape->vertexData.size(), &shape->vertexData[0], GL_STATIC_DRAW);

	// again, stride is how much to jump to find next data of same sort
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// enabling is important for vertex attributes
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
 
void Engine::SetupVertexShader(std::string &path) {
	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

	SetupShaderHelper(path, vertexShaderId);

	glAttachShader(shaderProgram, vertexShaderId);
	glDeleteShader(vertexShaderId);
}

void Engine::SetupFragmentShader(std::string& path) {
	unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	SetupShaderHelper(path, fragmentShaderId);

	glAttachShader(shaderProgram, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

void Engine::SetupShaderHelper(std::string& path, unsigned int shaderId) {
	std::ifstream finput(path);
	std::string shaderCode = "";
	std::string line;
	while (std::getline(finput, line)) {
		shaderCode += line;
		shaderCode += '\n';
	}
	const char* sources[] = { shaderCode.c_str() };
	glShaderSource(shaderId, 1, sources, NULL);
	glCompileShader(shaderId);

	// debugging, check if there is any error
	const int bufSize = 256;
	int length;
	char infoLog[bufSize];
	glGetShaderInfoLog(shaderId, bufSize, &length, infoLog);
	if (length) {
		std::cout << "LOG: Fragment shader(" << length << ")" << std::endl << infoLog << std::endl;
		exit(1);
	}
}

void Engine::LinkShaders() {
	glLinkProgram(shaderProgram);
}
