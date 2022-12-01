#include "triangle.h"

Triangle::Triangle() {
	std::vector<float> v1 = 
	{ 0.0f, 0.0f, 0.0f,
	  0.0f, 0.5f, 0.0f,
	  0.5f, 0.0f, 0.0f };
	vertexData = v1;

	std::vector<unsigned int> v2 = {};
	indexData = v2;

	vertShaderPath = "./src/shaders/triangleVert.shader";
	fragShaderPath = "./src/shaders/triangleFrag.shader";
}
