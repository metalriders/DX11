/* Class that encapsulates the geometry for 3D models */
#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include "texture.h"
#include <fstream>
using namespace std;

class Bitmap
{
private:
	struct VertexType 
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

public:
	Bitmap();
	Bitmap(const Bitmap&);
	~Bitmap();

	bool Initialize(ID3D11Device * device, int screenWidth, int screenHeight, WCHAR *textureFilename, int bitmapWidth, int bitmapHeight);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int x, int y);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device *device);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext *deviceContext, int x, int y);
	void RenderBuffers(ID3D11DeviceContext *deviceContext);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	Texture* m_Texture;

	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;
};

#endif // !_BITMAP_H_
