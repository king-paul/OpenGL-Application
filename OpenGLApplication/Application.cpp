#include "Application.h"

Application::Application()
{
	bool sucess = Startup();

	if (!sucess)
		false;

	// create shaders
	shader1 = ShaderProgram("TriangleShader.vsd", "SimpleShader.fsd");
	shader2 = ShaderProgram("TriangleShader.vsd", "RedShader.fsd");
	shader3 = ShaderProgram("SquareShader.vsd", "RedShader.fsd");

	// create triangles
	triangle1 = new Triangle({ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, &shader1);
	triangle2 = new Triangle({ 0.0f, 0.0f }, { -1.0f, 0.0f }, { 0.0f, -1.0f }, &shader1);
	triangle3 = new Triangle({ 0.0f, 0.0f }, { -1.0f, 0.0f }, { 0.0f, 1.0f }, &shader2);
	triangle4 = new Triangle({ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, -1.0f }, &shader2);

	// create square
	square = new Rectangle({ 0,0 }, 1, 1, &shader1);

	// apply rotation
	square->SetRotateMotion(0.1, true);
	//triangle1->SetRotateMotion(0.1, true);
	//triangle2->SetRotateMotion(0.1, true);
	//triangle3->SetRotateMotion(0.1, false);
	//triangle4->SetRotateMotion(0.1, false);
}

Application::~Application()
{
	glfwTerminate();

	delete triangle1;
	delete triangle2;
	delete triangle3;
	delete triangle4;
	delete square;
}

bool Application::Startup()
{
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

	return true;
}

bool Application::Update()
{
	if (glfwWindowShouldClose(window))
		return false;

	// calculate deltaTime
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	square->Update(deltaTime);
	//triangle1->Update(deltaTime);
	//triangle3->Update(deltaTime);

	glfwSwapBuffers(window);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

void Application::Draw()
{
	triangle1->Draw();
	triangle2->Draw();
	triangle3->Draw();
	triangle4->Draw();
	square->Draw();
}