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
	Vertex() : position(0, 0, 0), colour(NULL) ,uv(NULL) {}
	Vertex(vec3 position, vec3 colour) : position(position), colour(colour) , uv(NULL) {}
	Vertex(vec3 position, vec2 uv) : position(position), colour(NULL), uv(uv) {}

	vec3 position;
	vec3 colour;
	vec2 uv;
};

struct Polygon
{
	Vertex p1, p2, p3;
};

class Shape3d
{
public:
	Shape3d(ShaderProgram*, Texture* mainTexture = nullptr, Texture* blendedTexture = nullptr);
	Shape3d(ShaderProgram*, Texture* diiffuse, Texture* normal, Texture* specular);
	~Shape3d();
	void SetData(unsigned int bufferSize, const void* data);
	virtual void Update(float deltaTime);
	virtual void Draw();
	void SetRotateMotion(vec3 axis, float speed);

	// matrix setters
	void SetPosition(float x, float y, float z);
	void SetRotation(vec3 axis, float angle);
	void SetScale(float x, float y, float z);

protected:
	GLuint triangleID;
	ShaderProgram* shader;
	std::vector<Polygon> polygons;
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
	Cube(std::vector<vec3> colours);
	Cube(Texture* mainTexture, Texture* blendedTexture = nullptr);
	Cube(vec3 position, std::vector<vec3> colours);
	Cube(vec3 position, Texture* main, Texture* blended = nullptr);
};


class Plane : public Shape3d
{
public:
	Plane(vec3 position = { 0, 0, 0 }, float scaleX = 1, float scaleY = 1,
		vec3 colour = {1, 1, 1});
	Plane(Texture* texture, vec3 position = { 0, 0, 0 }, float scaleX = 1, float scaleY = 1);

private:
	vec3 normal;
};