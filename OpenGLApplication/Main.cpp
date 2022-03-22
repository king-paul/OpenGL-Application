#include "Application.h"

int main()
{
	Application* theApp = new Application();

	if (theApp)
	{
		//if (theApp->Startup() == true) {
			while (theApp->Update() == true)
				theApp->Draw();
		//}

		delete theApp;
	}

	return 0;
}