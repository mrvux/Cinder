#include "cinder/dx/IndexBuffer.h"

using namespace std;

namespace cinder { namespace dx {

IndexBuffer::Obj::Obj()
{
	mBuffer = 0;
}

IndexBuffer::Obj::~Obj()
{
	if (mBuffer) { mBuffer->Release(); }
}

IndexBuffer::IndexBuffer(DxDevice* device,const D3D11_BUFFER_DESC* desc, void* data,int indicescount, bool largeformat)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	mDevice = device;
	mIndicesCount = indicescount;
	mFormat = largeformat ? DXGI_FORMAT::DXGI_FORMAT_R32_UINT : DXGI_FORMAT::DXGI_FORMAT_R16_UINT;

	D3D11_SUBRESOURCE_DATA initialData;
	initialData.pSysMem = data;
	initialData.SysMemPitch = 0;
	initialData.SysMemSlicePitch = 0;
	
	HRESULT hr = mDevice->GetDevice()->CreateBuffer(desc,data ? &initialData : NULL,&mObj->mBuffer);

	if (FAILED(hr))
	{
		DxException exc("Failed to create Index Buffer");
		throw exc;
	}
}

IndexBuffer* IndexBuffer::CreateImmutable(DxDevice* device, void* data,int indicescount, bool largeformat)
{
	if (!data)
	{
		DxException exc("Immutable resource must have initial data");
		throw exc;
	}

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	UINT indexsize = largeformat ? sizeof(int) : sizeof(short);

	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = indicescount * indexsize;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;

	return new IndexBuffer(device,&desc,data,indicescount,largeformat);
}

IndexBuffer* IndexBuffer::CreateDynamic(DxDevice* device, void* data,int indicescount, bool largeformat)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	UINT indexsize = largeformat ? sizeof(int) : sizeof(short);

	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	desc.ByteWidth = indicescount * indexsize;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

	return new IndexBuffer(device,&desc,data,indicescount,largeformat);
}


void IndexBuffer::Bind()
{
	mDevice->GetContext()->IASetIndexBuffer(mObj->mBuffer,mFormat,0);
}


}}