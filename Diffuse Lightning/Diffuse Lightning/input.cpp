#include "input.h"

Input::Input()
{
}

Input::Input(const Input& other)
{
}

Input::~Input()
{
}

// Initialize all the keys to being released.
void Input::Initialize()
{
	int i;
	
	for (i = 0; i<256; i++)
	{
		m_keys[i] = false;
	}
	return;
}

// Save state when a key has been pressed.
void Input::KeyDown(unsigned int input)
{
	m_keys[input] = true;
	return;
}

// Clear state when a key has been released.
void Input::KeyUp(unsigned int input)
{
	m_keys[input] = false;
	return;
}

bool Input::IsKeyDown(unsigned int key)
{
	return m_keys[key];
}