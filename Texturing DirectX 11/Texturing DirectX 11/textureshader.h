/* Class that invoke our HSLS shaders for drawing 3D models that are on the GPU */

#ifndef _TEXTURESHADERS_H_
#define _TEXTURESHADERS_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

class TextureShader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

public:
	TextureShader();
	TextureShader(const TextureShader& other);
	~TextureShader();

	bool Initialize(ID3D11Device *device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView*);

private:
	bool InitializeShader(ID3D11Device *device, HWND hwnd, WCHAR *vsFilename, WCHAR *psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob *errorMessage, HWND hwnd, WCHAR *shaderFilename);
	
	bool SetShaderParameters(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView*);
	void RenderShader(ID3D11DeviceContext *deviceContext, int indexCount);

	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_matrixBuffer;

	ID3D11SamplerState *m_sampleState;
};

#endif // !_TEXTURESHADERS_H_