#include "model.h"

Model::Model()
{
	m_vertexBuffer = 0;
	m_indexBufer = 0;
}

Model::Model(const Model &)
{
}


Model::~Model()
{
}

bool Model::Initialize(ID3D11Device * device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}

	return true;
}

void Model::Shutdown()
{
	ShutdownBuffers();
	return;
}

void Model::Render(ID3D11DeviceContext * deviceContext)
{
	RenderBuffers(deviceContext);
	return;
}

int Model::GetIndexCount()
{
	return m_indexCount;
}

// Here you either read a model and create the buffers from that data file or create them manually as in this time.
bool Model::InitializeBuffers(ID3D11Device * device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBuferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set number of vertices and indices in respective array.
	m_vertexCount = 4;
	m_indexCount = 4;

	//Create vertex array
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	//Create index array
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return	false;
	}

	/* NOTE: remember to load the vectors clockwise, otherwise it will  be recognized as a back face and could not be
	drawn since back face culling */

	//Load vertex array with data
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);	// Bottom left.
	vertices[0].color = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);
	
	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);	// Top left.
	vertices[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);	// Bottom right.
	vertices[2].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);	// Top right.
	vertices[3].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);


	//Load index array with data
	indices[0] = 0; // Bottom left.
	indices[1] = 1; // Top left.
	indices[2] = 2; // Top right.
	indices[3] = 3; // Bottom right.

	//Set up the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) *m_vertexCount;	// size of buffer
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// type of buffer
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//Create vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result)) 
	{
		return false;
	}

	//Set up the description of the static index buffer.
	indexBuferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBuferDesc.ByteWidth = sizeof(unsigned long) *m_indexCount; // size of buffer
	indexBuferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;	// type of buffer
	indexBuferDesc.CPUAccessFlags = 0;
	indexBuferDesc.MiscFlags = 0;
	indexBuferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//Create index buffer.
	result = device->CreateBuffer(&indexBuferDesc, &indexData, &m_indexBufer);
	if (FAILED(result))
	{
		return false;
	}
	
	//Release arrays after buffers have been created and loaded.
	delete[]vertices;
	vertices = 0;
	delete[]indices;
	indices = 0;
	
	return true;
}

void Model::ShutdownBuffers()
{
	if (m_indexBufer) 
	{
		m_indexBufer->Release();
		m_indexBufer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	return;
}

// Activate vertex and input buffers on the input assembler and define how buffers should be drawn 
void Model::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	//Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	//Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	//Set the index buffer to active in the input assembler so it can be renderede.
	deviceContext->IASetIndexBuffer(m_indexBufer, DXGI_FORMAT_R32_UINT, 0);

	//Set the type of primitive that should be rendered from this vertex, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	return;
}
