/* Class that encapsulates loading/unloading of a single texture resource.
   For each texture needed, an object of this class must be instanciated. */

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <d3d11.h>
#include <d3dx11tex.h>

class Texture
{
public:
	Texture();
	Texture(const Texture&);
	~Texture();

	bool Initialize(ID3D11Device *, WCHAR *);
	void Shutdown();
	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* m_texture;
};

#endif // !_TEXTURE_H_