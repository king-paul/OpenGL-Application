#pragma once
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shape3d.h"

class Mesh : public Shape3d
{
public:
	Mesh(std::string filename, ShaderProgram *shader = nullptr);
	//~Mesh();
	void Draw() override;

private:		
	std::vector<unsigned short> indices;
};


class Soulspear : public Mesh
{
public:
	Soulspear() : Mesh("soulspear.obj", new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd")) { }
};

class Bunny : public Mesh
{
public:
	Bunny() : Mesh("Bunny.obj") { }
};