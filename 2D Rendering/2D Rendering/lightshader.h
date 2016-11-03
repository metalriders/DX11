/* Class that invoke our HSLS shaders for drawing 3D models that are on the GPU */

#ifndef _LIGHTSHADERS_H_
#define _LIGHTSHADERS_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

class LightShader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct CameraBufferType
	{
		D3DXVECTOR3 cameraPosition;
		float padding;
	};

	struct LightBufferType
	{
		D3DXVECTOR4 ambientColor;
		D3DXVECTOR4 diffuseColor;
		D3DXVECTOR3 lightDirection;
		float specularPower;
		D3DXVECTOR4 specularColor;
	};

public:
	LightShader();
	LightShader(const LightShader& other);
	~LightShader();

	bool Initialize(ID3D11Device *device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView*, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientLight, D3DXVECTOR4 diffuseColor, D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specularColor, float specularPower);

private:
	bool InitializeShader(ID3D11Device *device, HWND hwnd, WCHAR *vsFilename, WCHAR *psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob *errorMessage, HWND hwnd, WCHAR *shaderFilename);
	
	bool SetShaderParameters(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView*, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientLight, D3DXVECTOR4 diffuseColor, D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specularColor, float specularPower);
	void RenderShader(ID3D11DeviceContext *deviceContext, int indexCount);

	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11SamplerState *m_sampleState;
	ID3D11Buffer *m_matrixBuffer;
	ID3D11Buffer *m_lightBuffer;	
	ID3D11Buffer *m_cameraBuffer;
};

#endif // !_LIGHTSHADERS_H_
