#pragma once

#include <vector>
#include <string>

class Shape {
public:
	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;

	std::string vertShaderPath;
	std::string fragShaderPath;
};