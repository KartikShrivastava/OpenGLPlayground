#pragma once

#include "shape.h"

#include <string>

class Engine {
public:
	unsigned int shaderProgram;
	unsigned int shapeVAO;
	unsigned int posVBO;

	Engine();
	~Engine();

	void SetupVertexShader(std::string& path);
	void SetupFragmentShader(std::string& path);
	void SetupShaderHelper(std::string& path, unsigned int shaderId);
	void LinkShaders();

	void SetupGPUBuffers(Shape* shape);
};