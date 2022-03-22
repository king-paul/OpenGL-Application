#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw3.h>
#include <glm.hpp>
#include "Graphics.h"
#include "ShaderProgram.h"
#include <vector>

#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>

using namespace glm;

struct vertex
{
	vec3 position;
	vec3 colour;
};

class Shape3d
{
public:
	Shape3d(ShaderProgram*);
	~Shape3d();
	void SetData(const void* data);
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	GLuint triangleID;
	ShaderProgram* shader;
	std::vector<vertex[3]> faces;
	vec3 position;

	// matrices
	mat4 rotation, view, projection;
};

class Cube : public Shape3d
{
public:
	Cube();
	Cube(vec3 position, std::vector<vec3> colours);
};