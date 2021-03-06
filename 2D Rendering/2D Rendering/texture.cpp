#include "Texture.h"

Texture::Texture()
{
	m_texture = 0;
}

Texture::Texture(const Texture &)
{
}


Texture::~Texture()
{
}

bool Texture::Initialize(ID3D11Device *device, WCHAR *filename)
{
	HRESULT result;
	
	D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, &result);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Texture::Shutdown()
{
	// Release the Texture resource.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
	return;
}

ID3D11ShaderResourceView * Texture::GetTexture()
{
	return m_texture;
}
