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
    Shape2d(vec4 colour, ShaderProgram* shader);
    ~Shape2d() { delete shader; }
    void SetData(GLsizeiptr size, const void* data);
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
    Triangle(vec2 p1, vec2 p2, vec2 p3, vec4 colour);
    void Draw() override;
};

class Rectangle : public Shape2d
{
public:
    Rectangle(vec2 center, float width, float height, vec4 colour);
    void Draw() override;
};