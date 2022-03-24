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
#include <vector>

#include "Shape2d.h"
#include "Shape3d.h"
#include "Mesh.h"

struct Light { 
	glm::vec3 direction; 
	glm::vec3 colour;
};

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

	// graphic objects
	std::vector<Shape2d*> shapes;
	std::vector<Shape3d*> shapes3d;
	Mesh* plane;
	ShaderProgram* meshShader;

	// Lights
	Light light;
};