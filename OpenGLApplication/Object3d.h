#pragma once
#include "glad.h"
#include "ShaderProgram.h"
#include <glm.hpp>
#include <vector>
#include "Texture.h"

using namespace glm;

struct Vertex
{
	Vertex() : position(0, 0, 0), colour(NULL), uv(NULL) {}
	Vertex(vec3 position, vec3 colour) : position(position), colour(colour), uv(NULL) {}
	Vertex(vec3 position, vec2 uv) : position(position), colour(NULL), uv(uv) {}

	vec3 position;
	vec3 colour;
	vec2 uv;

	vec3 normal;
	vec3 tangeant;
	vec3 bitangeant;
};

struct Polygon
{
	Vertex p1, p2, p3;
};

class Object3d
{
protected:
	GLuint indexBufferID;
	GLuint vertexBufferID;
	ShaderProgram* shader;
	std::vector<Polygon> polygons;

	// matrices
	mat4 rotation, view, projection;
	mat4 transform;

	// rotation
	vec3 rotateAxis;
	float rotateSpeed;

	// colour and textures
	vec3 colour;
	Texture *texDiffuse, *texNormal, *texSpecular;

	virtual void SetData(unsigned int bufferSize, const void* data) = 0;

public:
	Object3d(ShaderProgram* shader, vec3 position = { 0, 0, 0 }, vec3 colour = {0, 0, 0});
	Object3d(ShaderProgram* shader, vec3 position, Texture* diiffuse, Texture* normal = nullptr, Texture* specular = nullptr);
	~Object3d();
	virtual void Update(float deltaTime);
	virtual void Draw() = 0;

	// getters
	vec3 GetRotationX() { return transform[0]; }
	vec3 GetRotationY() { return transform[1]; }
	vec3 GetRotationZ() { return transform[2]; }
	vec3 getPosition()  { return transform[3]; }

	void SetRotateMotion(vec3 axis, float speed);

	// Translate, rotate and scale
	void SetPosition(float x, float y, float z);
	void SetRotation(vec3 axis, float angle);
	void SetScale(float x, float y, float z);
};