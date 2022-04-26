#include "Graphics.h"
#include <iostream>

using namespace std;

void CheckOpenGLError()
{
	auto errorCode = glGetError();
	if (errorCode != GL_NO_ERROR)
	{
		cout << "Something's broken." << endl;
	}

	switch (errorCode)
	{
		case GL_NO_ERROR:
			cout << "There were no errors" << endl;
			break;

		case GL_INVALID_ENUM:
			cout << "Invalid Enum" << endl;
			break;

		case GL_INVALID_VALUE:
			cout << "Invalid Value" << endl;
			break;

		case GL_INVALID_OPERATION:
			cout << "Invalid Operation" << endl;
			break;

		case GL_INVALID_FRAMEBUFFER_OPERATION:
			cout << "Invalid Framebuffer Operation" << endl;
			break;

		case GL_OUT_OF_MEMORY:
			cout << "Out of Memory" << endl;
			break;

		case GL_STACK_UNDERFLOW:
			cout << "Stack Undeflow" << endl;
			break;

		case GL_STACK_OVERFLOW:
			cout << "Stack Overflow" << endl;
			break;

		default:
			cout << "Something else is wrong" << endl;
	}
}
