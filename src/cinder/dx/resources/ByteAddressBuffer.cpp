#include "cinder/dx/resources/ByteAddressBuffer.h"

using namespace std;

namespace cinder { namespace dx {

ByteAddressBuffer::Obj::Obj()
{
	mBuffer = 0;
	mSRV= 0;
	mSRV = 0;
}

ByteAddressBuffer::Obj::~Obj()
{
	if (mBuffer) { mBuffer->Release(); }
	if (mSRV) { mSRV->Release(); }
	if (mUAV) { mUAV->Release(); }

}

ByteAddressBuffer::ByteAddressBuffer(DxDevice* device,int size)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	mDevice = device;
	mSize = size;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS;
	desc.ByteWidth = mSize;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	mDevice->GetDevice()->CreateBuffer(&desc,NULL,&mObj->mBuffer);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
	ZeroMemory(&uavd,sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
	uavd.Format = DXGI_FORMAT_UNKNOWN;
	uavd.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_BUFFER;
	uavd.Buffer.Flags = D3D11_BUFFER_UAV_FLAG::D3D11_BUFFER_UAV_FLAG_RAW;

	mDevice->GetDevice()->CreateUnorderedAccessView(mObj->mBuffer,&uavd,&mObj->mUAV);
	mDevice->GetDevice()->CreateShaderResourceView(mObj->mBuffer,NULL,&mObj->mSRV);
}

ByteAddressBuffer::ByteAddressBuffer(DxDevice* device,int size, void* initial)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	mDevice = device;
	mSize = size;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
	desc.ByteWidth = size;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA pInit;	
	if (initial)
	{
		pInit.pSysMem = initial;
		pInit.SysMemPitch = 0;
		pInit.SysMemSlicePitch = 0;
	}

	mDevice->GetDevice()->CreateBuffer(&desc,initial ? &pInit : NULL,&mObj->mBuffer);

	mDevice->GetDevice()->CreateShaderResourceView(mObj->mBuffer,NULL,&mObj->mSRV);
}

void* ByteAddressBuffer::LockForWrite()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = mDevice->GetContext()->Map(mObj->mBuffer,0,D3D11_MAP::D3D11_MAP_WRITE_DISCARD,0,&mappedResource);

	if (FAILED(hr))
	{
		return NULL;
	}

	return mappedResource.pData;
}

void* ByteAddressBuffer::LockForRead()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = mDevice->GetContext()->Map(mObj->mBuffer,0,D3D11_MAP::D3D11_MAP_READ,0,&mappedResource);

	if (FAILED(hr))
	{
		return NULL;
	}


	return mappedResource.pData;
}

void ByteAddressBuffer::Unlock()
{
	mDevice->GetContext()->Unmap(mObj->mBuffer,0);
}

void ByteAddressBuffer::WriteData(void* data, UINT length)
{
	void* ptr = this->LockForWrite();
	memcpy(ptr,data,length);
	this->Unlock();
}

}}