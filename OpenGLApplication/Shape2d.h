#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw3.h>
#include <glm.hpp>
#include "Graphics.h"
#include "ShaderProgram.h"

using namespace glm;

class Shape2d
{
protected:
	GLuint id;
    ShaderProgram* shader;
    float rotation;
    float rotationSpeed;
    bool clockwiseRotation;

public:
	void Init(GLsizeiptr size, const void* data, ShaderProgram* shader);
	virtual void Draw();
    virtual void Update(float deltaTime);

    void SetRotateMotion(float speed, bool clockwise);
};

//------------//
// Subclasses //
//------------//
class Triangle : public Shape2d
{
public:
    Triangle(vec2 p1, vec2 p2, vec2 p3, ShaderProgram* shader);
    void Draw() override;
};

class Rectangle : public Shape2d
{
public:
    Rectangle(vec2 center, float width, float height, ShaderProgram* shader);
    void Draw() override;
};