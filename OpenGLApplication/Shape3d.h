#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw3.h>
#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include <vector>

#include "ShaderProgram.h"
#include "Object3d.h"

using namespace glm;

class Shape3d : public Object3d
{
public:	
	Shape3d(ShaderProgram* shader, vec3 position = { 0, 0, 0 }, Texture* mainTexture = nullptr, Texture* blendedTexture = nullptr);
	Shape3d(ShaderProgram* shader, vec3 position, Texture* diiffuse, Texture* normal, Texture* specular);
	~Shape3d();	
	virtual void Update(float deltaTime);
	virtual void Draw();

	// matrix setters
	void SetPosition(float x, float y, float z);
	void SetRotation(vec3 axis, float angle);
	void SetScale(float x, float y, float z);

protected:
	virtual void SetData(unsigned int bufferSize, const void* data);

	GLuint indexBufferID;
	GLuint vertexBufferID;
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

	// lighting

};

class Cube : public Shape3d
{
public:
	Cube(std::vector<vec3> colours);
	Cube(vec3 position, std::vector<vec3> colours);
	Cube(vec3 position, Texture* main, Texture* blended = nullptr);
};


class PlaneOld : public Shape3d
{
public:
	PlaneOld(vec3 position = { 0, 0, 0 }, float scaleX = 1, float scaleY = 1,vec3 colour = {1, 1, 1});
	PlaneOld(Texture* texture, vec3 position = { 0, 0, 0 }, float scaleX = 1, float scaleY = 1);

private:
	vec3 normal;
};