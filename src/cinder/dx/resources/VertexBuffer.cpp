#include "cinder/dx/resources/VertexBuffer.h"

using namespace std;

namespace cinder { namespace dx {

VertexBuffer::Obj::Obj()
{
	mBuffer = 0;
}

VertexBuffer::Obj::~Obj()
{
	if (mBuffer) { mBuffer->Release(); }
}

VertexBuffer::VertexBuffer(DxDevice* device,const D3D11_BUFFER_DESC* desc,void* data, int verticescount,int stride, std::vector<D3D11_INPUT_ELEMENT_DESC> elements)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	mDevice = device;
	mVertexCount = verticescount;
	mVertexSize = stride;

	for (int i = 0; i < elements.size(); i++)
	{
		mElements.push_back(elements.at(i));
	}

	D3D11_SUBRESOURCE_DATA initialData;
	initialData.pSysMem = data;
	initialData.SysMemPitch = 0;
	initialData.SysMemSlicePitch = 0;

	HRESULT hr = mDevice->GetDevice()->CreateBuffer(desc,data ? &initialData : NULL,&mObj->mBuffer);

	if (FAILED(hr))
	{
		DxException exc("Failed to create Vertex Buffer");
		throw exc;
	}
}

VertexBuffer* VertexBuffer::CreateImmutable(DxDevice* device,void* data, int verticescount,int stride, std::vector<D3D11_INPUT_ELEMENT_DESC> elements)
{
	if (!data)
	{
		DxException exc("Immutable resource must have initial data");
		throw exc;
	}

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = verticescount * stride;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;

	return new VertexBuffer(device,&desc,data,verticescount,stride,elements);
}

VertexBuffer* VertexBuffer::CreateDynamic(DxDevice* device,void* data, int verticescount,int stride, std::vector<D3D11_INPUT_ELEMENT_DESC> elements)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = verticescount * stride;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

	return new VertexBuffer(device,&desc,data,verticescount,stride,elements);
}

void VertexBuffer::Bind(ID3D11InputLayout* layout, int slot)
{
	UINT i = 0;
	mDevice->GetContext()->IASetVertexBuffers(slot,1,&mObj->mBuffer, &mVertexSize,&i);
	mDevice->GetContext()->IASetInputLayout(layout);
}



}}