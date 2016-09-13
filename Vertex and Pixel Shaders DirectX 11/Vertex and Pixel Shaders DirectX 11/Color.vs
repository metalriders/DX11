cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
}

struct PixelInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
}

