#include "Application.h"

Application::Application()
{
	if (Startup())
	{
		// load textures
		faceTexture1 = new Texture("face.png");
		faceTexture2 = new Texture("face_sad.png");

		// set up shader programs
		colourShader = ShaderProgram("3dVertexShader.vsd", "ColourShader.fsd");
		textureShader = ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd");
		multiLightTextureShader = ShaderProgram("3dVertexShader.vsd", "MultiLightTextureShader.fsd");
		ShaderProgram simpleTextureShader("3dVertexShader.vsd", "BasicTextureShader.fsd");

		std::vector<vec3> colours = { { 1, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 1, 0 }, { 1, 0, 1 } };

		//models.push_back(new Cube(colours));
		//models.push_back(new Cube(vec3(0, 0, 0), colours));
		//models.push_back(new Cube(vec3(0, 0, 0), faceTexture1, faceTexture2));

		//models[0]->SetRotateMotion(vec3(0, 1, 0), 1);

		//models.push_back(new PlaneOld{0, 0, 0}, 5, 5));
		//plane = (new PlaneOld({ 0, 0, 0 }, 5, 5));

		//models.push_back(new Plane(&simpleTextureShader,
			//new Texture("four_shapes/four_diffuse.tga"), {10, 1, 10}, {0, 0, -1}));

		//models.push_back(new Plane(&colourShader, {10, 1, 10}, {0, 0, 0}));
		//models[0]->SetRotation(vec3(1, 0, 1), 45);

		models.push_back(new Soulspear(&textureShader, vec3(0, 0, 0)));
		models[0]->SetRotateMotion(vec3(0, 1, 0), 1);

		models.push_back(new Bunny(&colourShader, vec3(-5, 0, -5), {0.5, 0.5, 0.5}));

		models.push_back(new Dragon(&colourShader, {5, 0, -5}, {0.5, 0.5, 0.5}));
		models.push_back(new Statue(&colourShader, { 10, 0, 5 }, {0.5, 0.5, 0.5}));

		// place fbx models and rotate them
		models.push_back(new Demolition(&textureShader, { -10, -5, 20 }));
		models.back()->SetRotation({ 0, 1, 0 }, PI);
		models.push_back(new EnemyElite(&textureShader, { 0, 0, 20 }));
		models.back()->SetRotation({ 0, 1, 0 }, PI);
		models.push_back(new EnemyEliteGun(&textureShader, { 5, 0, 20 }));
		models.back()->SetRotation({ 0, 1, 0 }, PI);		
		
		// load earth globe and have it orbit
		models.push_back(new Globe(new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd"), { 20, 20, 20 }, { 0, 0, -10 }));
		models.back()->SetRotateMotion({ 0, 1, 0 }, 1);
		
		// add lights to scene
		// main white lights
		lights.push_back(Light(glm::normalize(vec3(1, 0, -1)), { 1, 1, 1}, 1)); 
		//lights.push_back(Light(glm::normalize(vec3(1, 0, 1)), { 1, 1, 1}, 5));

		lights.push_back(Light(glm::normalize(vec3(1, 0, -1)), { 1, 0, 0 }, 2)); // red
		lights.push_back(Light(glm::normalize(vec3(-1, 0, -1)), { 0, 1, 0 }, 2)); // green
		lights.push_back(Light(glm::normalize(vec3(1, 0, 1)), { 0, 0, 1 }, 2)); // blue
		lights.push_back(Light(glm::normalize(vec3(-1, 0, 1)), { 1, 1, 0 }, 2)); // yellow

		// initialize camera		
		int winWidth, winHeight;
		glfwGetWindowSize(window, &winWidth, &winHeight);

		mainCamera = new Camera(window, {0, 4, 10});
	}
}

Application::~Application()
{
	glfwTerminate();

	for (Shape2d* shape : shapes)
	{
		delete shape;
	}

	for (Object3d* object : models)
	{
		delete object;
	}

	//delete plane;
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
	for (Object3d* object : models)
	{
		object->Update(deltaTime, mainCamera, lights);
	}

	//plane->Update(deltaTime);
	mainCamera->Update(deltaTime);

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
	for (Object3d* object : models)
	{
		object->Draw();
	}

	//plane->Draw();

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