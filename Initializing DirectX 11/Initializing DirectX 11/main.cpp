/*	DX 11 tutorial - Initializing a DX window
	This project will help you to understand the basics of DirectX
	credits: http://www.rastertek.com/
*/
#include "system.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) 
{
	System* system = new System;

	if (system->Initialize())
	{
		system->Run();
	}

	system->Shutdown();
	delete system;
	system = 0;

	return 0;
}