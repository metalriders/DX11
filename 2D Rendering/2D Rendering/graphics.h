/* This class has a D3D object that uses to do rendering of the scene */

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "d3d.h"
#include "camera.h"
#include "bitmap.h"
#include "lightshader.h"
#include "light.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render(float rotation);
	
	// should we use smart pointers?
	D3D* m_D3D;	
	Camera* m_Camera;
	Bitmap* m_Bitmap;
	LightShader* m_LightShader;
	Light *m_Light;
};

#endif //! _GRAPHICS_H_