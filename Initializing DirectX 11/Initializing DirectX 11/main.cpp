#include "system.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) 
{
	System* system;
	bool result;

	// Create the SystemClass object.
	system = new System;
	if (!system)
	{
		return 0;
	}

	// Initialize and run the SystemClass object.
	result = system->Initialize();
	if (result)
	{
		system->Run();
	}

	// Shutdown and release the SystemClass object.
	system->Shutdown();
	delete system;
	system = 0;

	return 0;
}