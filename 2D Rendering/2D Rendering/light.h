/* This class purpose is only to maintain the direction and color of lights. */
#ifndef _LIGHTClass_H_
#define _LIGHTClass_H_

#include <D3DX10math.h>

class Light
{
public:
	Light();
	Light(const Light&);
	~Light();

	void SetAmbientColor(float r, float g, float b, float a);
	void SetDiffuseColor(float r, float g, float b, float a);
	void SetDirection(float x, float y, float z);
	void SetSpecularColor(float r, float g, float b, float a);
	void SetSpecularPower(float power);

	D3DXVECTOR4 GetAmbientColor();
	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR3 GetDirection();
	D3DXVECTOR4 GetSpecularColor();
	float GetSpecularPower();

private:
	D3DXVECTOR4 m_ambientColor;
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR3 m_direction;
	D3DXVECTOR4 m_specularColor;
	float m_specularPower;
};

#endif // !_LIGHT_H_