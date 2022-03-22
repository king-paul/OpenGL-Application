#pragma once

#include "Graphics.h"

#include <math.h>
#include "Utilities.h"
#include "ShaderProgram.h"

#include <iostream>

#include "glm.hpp"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

#include <glfw3.h>

#include "Shape2d.h"
#include <vector>

class Application
{
public:
	Application();
	~Application();
	bool Startup();
	bool Update();
	void Draw();
	
private:
	// timers
	float currentFrame = 0;
	float deltaTime = 0;
	float lastFrame = 0;

	GLFWwindow* window;	//The pointer to the GLFW window that gives us a place to draw.

	std::vector<Shape2d*> shapes;
};