#include "ShaderProgram.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>

ShaderProgram::ShaderProgram(std::string vertexFilename)
{
	everythingIsOkay = true;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();

	std::string vertexSource = LoadFileAsString("Shaders/" + vertexFilename);

	const char* vertexSourceC = vertexSource.c_str();

	glShaderSource(vertexShader, 1, &vertexSourceC, nullptr);
	glCompileShader(vertexShader);

	GLchar errorLog[512];
	GLint success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		//Something failed with the vertex shader compilation
		std::cout << "Vertex shader " << vertexFilename << " failed because..." << std::endl;
		glGetShaderInfoLog(vertexShader, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}
	else
	{
		std::cout << "Everything is okay (with the vertex shader at least)" << std::endl;
	}

	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		std::cout << "The linking is busted or something" << std::endl;
		glGetProgramInfoLog(shaderProgram, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}

	if (everythingIsOkay)
	{
		std::cout << "The Vertex shader was loaded successfully" << std::endl;
	}
}

ShaderProgram::ShaderProgram(std::string vertexFilename, std::string fragmentFilename)
{
	everythingIsOkay = true;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	shaderProgram = glCreateProgram();
	
	std::string vertexSource = LoadFileAsString("Shaders/" + vertexFilename);
	std::string fragmentSource = LoadFileAsString("Shaders/" + fragmentFilename);
	
	const char* vertexSourceC = vertexSource.c_str();

	glShaderSource(vertexShader, 1, &vertexSourceC, nullptr);
	glCompileShader(vertexShader);

	GLchar errorLog[512];
	GLint success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		//Something failed with the vertex shader compilation
		std::cout << "Vertex shader " << vertexFilename << " failed because..." << std::endl;
		glGetShaderInfoLog(vertexShader, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}
	else
	{
		std::cout << "Everything is okay (with the vertex shader at least)" << std::endl;
	}

	const char* fragmentSourceC = fragmentSource.c_str();

	glShaderSource(fragmentShader, 1, &fragmentSourceC, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		//Something failed with the fragment shader compilation
		std::cout << "Fragment shader " << fragmentFilename << " failed because..." << std::endl;
		glGetShaderInfoLog(fragmentShader, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}
	else
	{
		std::cout << "Everything is okay (with the fragment shader at least)" << std::endl;
	}

	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		std::cout << "The linking is busted or something" << std::endl;
		glGetProgramInfoLog(shaderProgram, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}


	if (everythingIsOkay)
	{
		std::cout << "It appears that things are pretty okay" << std::endl;
	}

}

void ShaderProgram::UseShader()
{
	glUseProgram(shaderProgram);
}

GLuint ShaderProgram::GetUniformLocation(std::string varName)
{
	return glGetUniformLocation(shaderProgram, varName.c_str());
}

void ShaderProgram::SetUniform(std::string varName, float value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform1f(varLoc, value);
}


void ShaderProgram::SetUniform(std::string varName, int value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform1i(varLoc, value);
}

void ShaderProgram::SetUniform(std::string varName, glm::mat4 value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniformMatrix4fv(varLoc, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::SetUniform(std::string varName, glm::vec3 value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform3f(varLoc, value.x, value.y, value.z);

	//std::cout << "Value: (" << value.x << ", " << value.y << ", " << value.z << ")" << std::endl;

}

void ShaderProgram::SetLights(std::string arrayName, std::vector<Light>& lights)
{
	GLuint varLoc;

	std::string setValue;

	for (int i=0; i< lights.size(); i++)
	{
		
		setValue = arrayName + "[";
		setValue += std::to_string(i) + "].direction";
		varLoc = glGetUniformLocation(shaderProgram, setValue.c_str());
		glUniform3f(varLoc, lights[i].m_direction.x, lights[i].m_direction.y, lights[i].m_direction.z);

		setValue = arrayName + "[";
		setValue += std::to_string(i) + "].colour";
		varLoc = glGetUniformLocation(shaderProgram, setValue.c_str());
		glUniform3f(varLoc, lights[i].m_colour.r, lights[i].m_colour.g, lights[i].m_colour.b);

		setValue = arrayName + "[";
		setValue += std::to_string(i) + "].intensity";
		varLoc = glGetUniformLocation(shaderProgram, setValue.c_str());
		glUniform1f(varLoc, lights[i].m_intensity);
	}

	UseShader();
}