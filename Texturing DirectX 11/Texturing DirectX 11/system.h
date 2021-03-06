/*  This is our little system to connect the other modules used in this tutorial.
	It's going to be instanciated once and will be doing the run/shutdown of our DX program.
*/

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "input.h"
#include "graphics.h"

class System
{
public:
	System();
	System(const System&);
	~System();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	Input* m_Input;
	Graphics* m_Graphics;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static System *ApplicationHandle;

#endif // !_SYSTEM_H_