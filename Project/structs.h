#pragma once
#include  <vector>
#include  <glm.hpp>
#include <gtc/matrix_transform.hpp>
struct Vertex {

	std::vector < glm::vec3 > position;
	std::vector < glm::vec2 > uv;
	std::vector < glm::vec3 > normals;
};


struct Joint {


}; 
struct Light {
	float power;
	glm::vec3 direction;
	glm::vec3 color;
};
/*
struct Material {
	GLuint diffusetexture;
	GLuint spectexture;
};*/