//These includes are specific to the way we’ve set up GLFW and GLAD.
#define GLFW_INCLUDE_NONE

#include "glfw3.h"
#include "glad.h"
#include "glm.hpp"

using namespace glm;

int main(void)
{
    GLFWwindow* window;

    //Initialise GLFW, make sure it works. Put an error message here if you like.
    if (!glfwInit())
        return -1;

    //Set resolution here, and give your window a different title.
    window = glfwCreateWindow(1280, 720, "Don't just copy this!", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate(); //Again, you can put a real error message here.
        return -1;
    }

    //This tells GLFW that the window we created is the one we should render to.
    glfwMakeContextCurrent(window);

    //Tell GLAD to load all its OpenGL functions.
    if (!gladLoadGL())
        return -1;

    //The main ‘game’ loop.
    while (!glfwWindowShouldClose(window))
    {
        //Clear the screen – eventually do rendering code here.
        glClear(GL_COLOR_BUFFER_BIT);

        //Swapping the buffers – this means this frame is over.
        glfwSwapBuffers(window);
        //Tell GLFW to check if anything is going on with input, etc.
        glfwPollEvents();
                
    }

    //If we get to this point, the window has closed, so clean up GLFW and exit.
    glfwTerminate();
    return 0;
}