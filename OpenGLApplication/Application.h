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
#include "Camera.h"
#include "Light.h"

class Application
{
public:
	Application();
	~Application();
	bool Startup();
	bool Update();
	void Draw();
	
private:

	// functions
	void Create2dShapes();

	// timers
	float currentFrame = 0;
	float deltaTime = 0;
	float lastFrame = 0;

	GLFWwindow* window;	//The pointer to the GLFW window that gives us a place to draw.

	// shaders
	ShaderProgram colourShader;
	ShaderProgram textureShader;

	// graphic objects
	std::vector<Shape2d*> shapes;
	std::vector<Object3d*> models;
	Plane* plane;	

	// cameras
	Camera* mainCamera;

	// textures
	Texture* faceTexture1;
	Texture* faceTexture2;

	Mesh* demolitionMan[2];
	Mesh* enemyElite[2];

	// Lights
	std::vector<Light> lights;

	float frameNum = 1;
};