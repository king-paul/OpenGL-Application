#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string filename)
{

	imageData = stbi_load(filename.c_str(), &width, &height, &channelCount, 0);	
	// FIXME this needs proper error handling. 
	// For now we're just going to assume the load worked, and if it doesn't, we'll probably crash.

	if (imageData)
		successfullyLoaded = true;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	//Bind();
	
	if(channelCount == 3) // red, green and blue values
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else if(channelCount == 4) // red, green, blue and alpha values
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	else
	{
		std::cout << "We're not set up to deal with this component count (" << channelCount << ") for image " << filename;
		glDeleteTextures(1, &textureID);
		successfullyLoaded = false;
	}
	
	if(successfullyLoaded)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//Unbind();

	stbi_image_free(imageData);
}

Texture::~Texture()
{	
	if(successfullyLoaded)
	{
		glDeleteTextures(1, &textureID);
	}
}

Texture::Texture(Texture&& otherTexture)
{
	if (&otherTexture == this)
	{
		return;
	}
	if (successfullyLoaded)
	{
		glDeleteTextures(1, &textureID);
	}
	this->textureID = otherTexture.textureID;
	this->height = otherTexture.height;
	this->width = otherTexture.width;
	this->channelCount = otherTexture.channelCount;

	otherTexture.successfullyLoaded = false;
}

Texture& Texture::operator=(Texture&& otherTexture)
{
	if (&otherTexture == this)
	{
		return *this;
	}
	if (successfullyLoaded)
	{
		glDeleteTextures(1, &textureID);
	}

	this->textureID = otherTexture.textureID;
	this->height = otherTexture.height;
	this->width = otherTexture.width;
	this->channelCount = otherTexture.channelCount;

	otherTexture.successfullyLoaded = false;

	return *this;
}

void Texture::Bind(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::PrintAsciiImage()
{	
	for(int y =0; y < height; y++)
	{
		for(int x=0; x < width; x++)
		{
			if(imageData[(x + y * width) * channelCount + 1] > 127)
			{
				std::cout << " ";
			}
			else
			{
				std::cout << "*";
			}
		}
		std::cout << std::endl;
	}
}