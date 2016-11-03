#include "graphics.h"

Graphics::Graphics()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Bitmap = 0;
	m_LightShader = 0;
	m_Light = 0;
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

	// Create the camera object.
	m_Camera = new Camera;
	if (!m_Camera)
	{
		return false;
	}
	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -500.0f);

	// Create the Bitmap object.
	m_Bitmap = new Bitmap;
	if (!m_Bitmap)
	{
		return false;
	}
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/mei.dds", 300, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object", L"Error",MB_OK);
		return false;
	}

	//Create the Light shader object.
	m_LightShader = new LightShader;
	if (!m_LightShader)
	{
		return false;
	}
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object", L"ERORR", MB_OK);
		return false;
	}

	//Create the color shader object.
	m_Light = new Light;
	if (!m_Light)
	{
		return false;
	}
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	return true;
}

// Release the D3d object.
void Graphics::Shutdown()
{
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	
}

bool Graphics::Frame()
{
	static float rotation = 0.0f;
	
	// Update the rotation variable each frame
	rotation += (float)D3DX_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	if (!Render(rotation))
	{
		return false;
	}

	return true;
}

bool Graphics::Render(float rotation)
{
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, orthoMatrix;
	bool result;

	// Clear buffers
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix base on the camera's position.
	m_Camera->Render();

	// Get the world, view and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 250, 170);
	if (FAILED(result))
	{
		return false;
	}
	// Rotate the world matrix by the rotation value so that the cube will spin.
	//D3DXMatrixRotationYawPitchRoll(&worldMatrix, rotation, rotation / 2, 0);
	
	// Render the bitmap twith the texture shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Bitmap->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present frame
	m_D3D->EndScene();

	return true;
}
