#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw3.h>
#include <glm.hpp>
#include "Graphics.h"
#include "ShaderProgram.h"
#include <vector>

#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include "Texture.h"

using namespace glm;

struct Vertex
{
	Vertex(vec3 position, vec3 colour) : position(position) , colour(colour) {}
	Vertex(vec3 position, vec2 uv) : position(position), uv(uv) {}

	vec3 position;
	vec3 colour;
	vec2 uv;
};

class Shape3d
{
public:
	Shape3d(ShaderProgram*);
	Shape3d(ShaderProgram*, Texture*);
	Shape3d(ShaderProgram*, Texture*, Texture*);
	Shape3d(ShaderProgram*, Texture* diiffuse, Texture* normal, Texture* specular);
	~Shape3d();
	void SetData(unsigned int bufferSize, const void* data);
	virtual void Update(float deltaTime);
	virtual void Draw();
	void SetRotateMotion(vec3 axis, float speed);

protected:
	GLuint triangleID;
	ShaderProgram* shader;
	std::vector<Vertex[3]> polygons;
	vec3 position;

	// matrices
	mat4 rotation, view, projection;
	mat4 transform;

	// rotation
	vec3 rotateAxis;
	float rotateSpeed;

	// textures
	Texture *mainTexture, *blendedTexture;
	Texture *diffuse, *normal, *specular;
};

class Cube : public Shape3d
{
public:
	Cube(Texture* texture);
	Cube(Texture* mainTexture, Texture* blendedTexture);
	Cube(vec3 position, std::vector<vec3> colours);
	Cube(vec3 position, Texture* texture);
};