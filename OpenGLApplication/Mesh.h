#pragma once
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Object3d.h"

class Mesh : public Object3d
{
public:
	Mesh(std::string filename, ShaderProgram* shader, vec3 colour = {1, 1, 1}, vec3 position = {0,0,0});
	Mesh(std::string filename, ShaderProgram* shader, vec3 position, Texture* texture);
	Mesh(std::string filename, ShaderProgram* shader, vec3 position, Texture*, Texture*, Texture*, float specularPower);

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
			position, new Texture("soulspear_diffuse.tga"), new Texture("soulspear_normal.tga"), new Texture("soulspear_specular.tga"), 5) 
	{}
};

class SimpleSoulspear : public Mesh
{
public:
	SimpleSoulspear(vec3 position = { 0, 0, 0 }) :
		Mesh("soulspear.obj", new ShaderProgram("3dVertexShader.vsd", "BasicTextureShader.fsd"),
			position, new Texture("soulspear_diffuse.tga")) { }
};

class Bunny : public Mesh
{
public:
	Bunny(vec3 position = { 0, 0, 0 }, vec3 colour = {1, 1, 1}) :
		Mesh("Bunny.obj", new ShaderProgram("3dVertexShader.vsd", "ColourShader.fsd"), position, colour) { }
};

class Dragon : public Mesh
{
public:
	Dragon(vec3 position = {0, 0, 0}, vec3 colour = { 1, 1, 1 }) :
		Mesh("Dragon.obj", new ShaderProgram("3dVertexShader.vsd", "ColourShader.fsd"), position, colour) { }
};

class Statue : public Mesh
{
public:
	Statue(vec3 position = { 0, 0, 0 }, vec3 colour = { 1, 1, 1 }) :
		Mesh("Lucy.obj", new ShaderProgram("3dVertexShader.vsd", "ColourShader.fsd"), position, colour) { }
};

class Demolition : public Mesh
{
public:
	Demolition(vec3 position = { 0, 0, 0 }, vec3 colour = { 1, 1, 1 }) :
		Mesh("demolition.fbx", new ShaderProgram("3dVertexShader.vsd", "BasicTextureShader.fsd"), position,
			new Texture("EnemyElite1_D.tga"))
	{ 
		SetScale(0.001, 0.001, 0.001);
	}
};

class EnemyElite : public Mesh
{
public:
	EnemyElite(vec3 position = { 0, 0, 0 }, vec3 colour = { 1, 1, 1 }) :
		Mesh("demolition.fbx", new ShaderProgram("3dVertexShader.vsd", "BasicTextureShader.fsd"), position,
			new Texture("EnemyElite1_D.tga"))
	{
		
	}
};