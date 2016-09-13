#include "graphics.h"

Graphics::Graphics()
{
	m_D3D = 0;
}

Graphics::Graphics(const Graphics& other)
{
}

Graphics::~Graphics()
{
}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Create the Direct3D object.
	m_D3D = new D3D;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	return true;
}

// Release the D3d object.
void Graphics::Shutdown()
{

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
}

bool Graphics::Frame()
{
	if (!Render())
	{
		return false;
	}

	return true;
}

bool Graphics::Render()
{
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);
	m_D3D->EndScene();

	return true;
}