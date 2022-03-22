#include "Graphics.h"

#include <math.h>
#include "Utilities.h"
#include "ShaderProgram.h"

#include <iostream>

#include "glm.hpp"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"



int main()
{
	GLFWwindow* window;	//The pointer to the GLFW window that gives us a place to draw.


	if (!glfwInit())
		return -1;	//glfw failed to initialise.

	//Can choose resolution here.
	window = glfwCreateWindow(1280, 720, "GPU Graphics", nullptr, nullptr);

	if (!window)
	{
		//If the window failed to create for some reason, abandon ship.
		glfwTerminate();
		return -1;
	}

	//We have to tell glfw to use the OpenGL context from the window.
	//This stuff can be relevant if you have multiple windows - you're
	//telling OpenGL which one to apply render commands to.
	//But if we only have one window we just do this once at the start.
	glfwMakeContextCurrent(window);

	//This is where GLAD gets set up. After this point we can use openGL functions.
	if (!gladLoadGL())
		return -1;

	ShaderProgram theShader("SimpleShader.vsd", "SimpleShader.fsd");


	GLuint triangleID;
	glGenBuffers(1, &triangleID);

	float aBunchOfFloats[] = {	0.0f, 0.0f, 
								1.0f, 0.0f,
							    0.0f, 1.0f };

	glBindBuffer(GL_ARRAY_BUFFER, triangleID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, aBunchOfFloats, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);


	while (!glfwWindowShouldClose(window))
	{
	

		//Your game goes here.

		glBindBuffer(GL_ARRAY_BUFFER, triangleID);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		theShader.UseShader();

		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);

		



		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}