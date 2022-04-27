#pragma once
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Object3d.h"

class Mesh : public Object3d
{
public:
	Mesh(std::string filename, ShaderProgram* shader, vec3 colour = {1, 1, 1}, vec3 position = {0,0,0}, unsigned int meshIndex = 0);
	Mesh(std::string filename, ShaderProgram* shader, vec3 position, Texture* texture, unsigned int meshIndex = 0);
	Mesh(std::string filename, ShaderProgram* shader, vec3 position, Texture*, Texture*, Texture*, float specularPower = 1, unsigned int meshIndex = 0);

	void Draw() override;

private:
	void SetData(unsigned int bufferSize, const void* data) override;

	std::vector<unsigned short> indices;
};


class Soulspear : public Mesh
{
public:
	Soulspear(ShaderProgram* shader, vec3 position = { 0, 0, 0 }) :
		Mesh("soulspear.obj", shader,
			position, new Texture("soulspear_diffuse.tga"), new Texture("soulspear_normal.tga"), new Texture("soulspear_specular.tga"), 5) 
	{

	}
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
	Bunny(ShaderProgram* shader, vec3 position = { 0, 0, 0 }, vec3 colour = {1, 1, 1}) :
		Mesh("Bunny.obj", shader, position, colour) 
	{
		//SetScale(2, 2, 2);
	}
};

class Dragon : public Mesh
{
public:
	Dragon(ShaderProgram* shader, vec3 position = {0, 0, 0}, vec3 colour = { 1, 1, 1 }) :
		Mesh("Dragon.obj", shader, position, colour) { }
};

class Statue : public Mesh
{
public:
	Statue(ShaderProgram* shader, vec3 position = { 0, 0, 0 }, vec3 colour = { 1, 1, 1 }) :
		Mesh("Lucy.obj", shader, position, colour) { }
};

class Demolition : public Mesh
{
public:
	Demolition(ShaderProgram* shader, vec3 position = { 0, 0, 0 }, vec3 colour = { 1, 1, 1 }) :
		Mesh("demolition.fbx", shader, position,
			new Texture("demolition_d.tga"), new Texture("demolition_n.tga"), new Texture("demolition_s.tga"), 1, 1)
	{ 
		SetScale(0.01, 0.01, 0.01);
	}
};


class EnemyElite : public Mesh
{
public:
	EnemyElite(ShaderProgram* shader, vec3 position = { 0, 0, 0 }, vec3 colour = { 1, 1, 1 }) :
		Mesh("EnemyElite.fbx", shader, position,
			new Texture("EnemyElite1_D.tga"), new Texture("EnemyElite_N.tga"), new Texture("EnemyElite_S.tga"), 1, 1)
	{
		SetScale(0.01, 0.01, 0.01);
	}
};

class EnemyEliteGun : public Mesh
{
public:
	EnemyEliteGun(ShaderProgram* shader, vec3 position = { 0, 0, 0 }, vec3 colour = { 1, 1, 1 }) :
		Mesh("EnemyElite.fbx", new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd"), position,
			new Texture("EnemyElite1_D.tga"), new Texture("EnemyElite_N.tga"), new Texture("EnemyElite_S.tga"), 1, 2)
	{
		SetScale(0.01, 0.01, 0.01);
	}
};

class Mannequin : public Mesh
{
public:
	Mannequin(ShaderProgram* shader, vec3 position = { 0, 0, 0 }, vec3 colour = { 1, 1, 1 }) :
		Mesh("mannequin.fbx", shader, position, colour) 
	{ 
		SetScale(0.1, 0.1, 0.1);
	}
};

class Plane : public Mesh
{
public:
	Plane(ShaderProgram* shader, vec3 scale = { 1, 1, 1 }, vec3 position = { 0, 0, 0 }, vec3 colour = { 1, 1, 1 }) :
		Mesh("Plane.obj", shader, position, colour)
	{
		SetScale(scale.x, scale.y, scale.z);
	}

	Plane(ShaderProgram* shader, Texture* texture, vec3 scale = { 1, 1, 1 }, vec3 position = { 0, 0, 0 }) :
		Mesh("Plane.obj", shader, position, texture)
	{
		SetScale(scale.x, scale.y, scale.z);
	}

	Plane(ShaderProgram* shader, Texture* diffuse, Texture* normal, Texture* specular, 
		vec3 scale = { 1, 1, 1 }, vec3 position = { 0, 0, 0 }) :
		Mesh("Plane.obj", shader, position, diffuse, normal, specular, 3)
	{
		SetScale(scale.x, scale.y, scale.z);
	}

};