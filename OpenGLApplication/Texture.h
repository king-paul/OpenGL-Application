#include "glad.h"
#include <string>
#include <iostream>

class Texture
{
	GLuint textureID;

	int width;
	int height;
	int channelCount;	

	bool successfullyLoaded = false;

	unsigned char* imageData;

public:

	Texture() {}
	Texture(std::string filename);
	~Texture();

	//We don't want to be copying our textures around.
	Texture(const Texture& otherTexture) = delete;
	Texture& operator=(const Texture& otherTexture) = delete;


	//But moving them is legit and useful.
	Texture(Texture&& otherTexture);
	Texture& operator=(Texture&& otherTexture);


	void Bind();

	static void Unbind();

	void PrintAsciiImage();
};