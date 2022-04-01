#include "Application.h"

Application::Application()
{
	if (Startup())
	{
		// load textures
		faceTexture1 = new Texture("face.png");
		faceTexture2 = new Texture("face_sad.png");

		std::vector<vec3> colours = { {1, 0, 0} , { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 1, 0 }, {1, 0, 1} };

		//shapes3d.push_back(new Cube(colours));
		//shapes3d.push_back(new Cube(vec3(0, 0, 0), colours));
		//shapes3d.push_back(new Cube(vec3(0, 0, 0), faceTexture1, faceTexture2));
		
		//meshShader = new ShaderProgram("3dVertexShader.vsd", "ColourShader.fsd");
		//plane = new Mesh(meshShader);
		//plane->InitialiseQuad();
		//shapes3d.push_back(plane);

		//shapes3d[0]->SetRotateMotion(vec3(0, 1, 0), 1);
		
		//faceTexture->PrintAsciiImage();

		//shapes3d.push_back(new Plane({0, 0, 0}, 5, 5));

		shapes3d.push_back(new Soulspear(vec3(0, -5, 0)));
		//shapes3d[0]->SetRotateMotion(vec3(0, 1, 0), 1);
		
		//int winWidth, winHeight;
		//glfwGetWindowSize(window, &winWidth, &winHeight);

		//mainCamera = new Camera(winWidth, winHeight);
	}
}

Application::~Application()
{
	glfwTerminate();

	for (Shape2d* shape : shapes)
	{
		delete shape;
	}

	for (Shape3d* shape : shapes3d)
	{
		delete shape;
	}

	delete faceTexture1;
	delete faceTexture2;
	delete mainCamera;
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

	glEnable(GL_DEPTH_TEST);

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

	// update shapes
	for (Shape2d* shape : shapes)
	{
		shape->Update(deltaTime);
	}
	for (Shape3d* shape : shapes3d)
	{
		shape->Update(deltaTime);
	}

	//mainCamera->Update(deltaTime);

	glfwSwapBuffers(window);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

void Application::Draw()
{
	glClearColor(0.25f, 0.25f, 0.25f, 1);	

	// draw shapes
	for (Shape2d* shape : shapes)
	{
		shape->Draw();
	}
	for (Shape3d* shape : shapes3d)
	{
		shape->Draw();
	}

}

void Application::Create2dShapes()
{
	// create triangles
	shapes.push_back(new Triangle({0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, vec4(0.5, 0, 0, 1)));
	shapes.push_back(new Triangle({ 0.0f, 0.0f }, { -1.0f, 0.0f }, { 0.0f, -1.0f }, vec4(0.5, 0, 0, 1)));
	shapes.push_back(new Triangle({ 0.0f, 0.0f }, { -1.0f, 0.0f }, { 0.0f, 1.0f }, vec4(0.5, 0.5, 0.5, 1)));
	shapes.push_back(new Triangle({ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, -1.0f }, vec4(0.5, 0.5, 0.5, 1)));
	shapes.push_back(new Rectangle({ 0,0 }, 1, 1, vec4(1.0, 0, 0, 1)));

	// apply rotation
	shapes[0]->SetRotateMotion(0.1, false);
	shapes[1]->SetRotateMotion(0.1, false);
	shapes[2]->SetRotateMotion(0.1, false);
	shapes[3]->SetRotateMotion(0.1, false);
	shapes[4]->SetRotateMotion(0.1, true);
}