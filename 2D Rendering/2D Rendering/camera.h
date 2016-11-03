/* Class to keep track of where camera is and its current rotation.
It will use the position and rotation info to generate a view matrix which will be passed into the HLSL shader for rendering. */

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <D3DX10math.h>

class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void GetViewMatrix(D3DXMATRIX& viewMatrix);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix;
};

#endif // !_CAMERA_H_
