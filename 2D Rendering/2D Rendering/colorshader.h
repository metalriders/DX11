/* Class that invoke our HSLS shaders for drawing 3D models that are on the GPU */

#ifndef _COLORSHADER_H_
#define _COLORSHADER_H_

#include <D3D11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
#include <fstream>
using namespace std;

class Colorshader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

public:
	Colorshader();
	Colorshader(const Colorshader& other);
	~Colorshader();

	bool Initialize(ID3D11Device *device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix);

private:
	bool InitializeShader(ID3D11Device *device, HWND hwnd, WCHAR *vsFilename, WCHAR *psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob *errorMessage, HWND hwnd, WCHAR *shaderFilename);
	
	bool SetShaderParameters(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix);
	void RenderShader(ID3D11DeviceContext *deviceContext, int indexCount);

	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_matrixBuffer;
};

#endif // !_COLORSHADER_H_