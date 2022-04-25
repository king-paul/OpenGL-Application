#pragma once

#include "Graphics.h"
#include "glm.hpp"
#include <string>
#include <vector>
#include "Light.h"

class ShaderProgram
{
private:
	//Remember, OpenGL manages its resources itself and gives you handles to them.
	//That's what all this 'GLuint' business is about.
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

	bool everythingIsOkay = false;

public:
	ShaderProgram() {}
	ShaderProgram(std::string vertexFilename);
	ShaderProgram(std::string vertexFilename, std::string fragmentFilename);

	~ShaderProgram() {}	//TODO this should free the resources of shader.

	bool IsEverythingOkay() const { return everythingIsOkay; }

	void UseShader();

	GLuint GetUniformLocation(std::string varName);

	void SetUniform(std::string varName, float value);
	void SetUniform(std::string varName, int value);
	void SetUniform(std::string varName, glm::mat4 value);
	void SetUniform(std::string varName, glm::vec3 value);
	void SetLights(std::string arrayName, std::vector<Light> &lights);
};

class ColourShader
{
	static ShaderProgram* shader;

public:
	static ShaderProgram* GetInstance()
	{
		if(shader == nullptr)
			shader = new ShaderProgram("3dVertexShader.vsd", "ColourShader.fsd");

		return shader;
	}

	static void Unload()
	{
		delete shader;
	}
};

class TextureShader
{
	static ShaderProgram* shader;

public:
	static ShaderProgram* GetInstance()
	{
		if (shader == nullptr)
			shader = new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd");

		return shader;
	}

	static void Unload()
	{
		delete shader;
	}
};