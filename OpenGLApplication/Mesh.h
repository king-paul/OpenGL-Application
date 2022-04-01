#pragma once
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shape3d.h"

class Mesh : public Shape3d
{
public:
	Mesh(std::string filename, ShaderProgram* shader, vec3 position, Texture* texture = nullptr);
	void Draw() override;

private:
	void SetData(unsigned int bufferSize, const void* data) override;

	std::vector<unsigned short> indices;
};


class Soulspear : public Mesh
{
public:
	Soulspear(vec3 position = { 0, 0, 0 }) :
		Mesh("soulspear.obj", new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd"),
			position, new Texture("soulspear_diffuse.tga")) { }
};

class Bunny : public Mesh
{
public:
	Bunny(vec3 position = { 0, 0, 0 }) :
		Mesh("Bunny.obj", new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd"), position) { }
};