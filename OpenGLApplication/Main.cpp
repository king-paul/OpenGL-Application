#include "Application.h"

int main()
{
	Application* theApp = new Application();

	while (theApp->Update() == true)
			theApp->Draw();

	if(theApp)
		delete theApp;

	return 0;
}