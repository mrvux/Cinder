#include "cinder/dx/resources/StructuredBuffer.h"

using namespace std;

namespace cinder { namespace dx {

StructuredBuffer::Obj::Obj()
{
	mBuffer = 0;
	mSRV= 0;
	mSRV = 0;
}

StructuredBuffer::Obj::~Obj()
{
	if (mBuffer) { mBuffer->Release(); }
	if (mSRV) { mSRV->Release(); }
	if (mUAV) { mUAV->Release(); }

}

StructuredBuffer::StructuredBuffer(DxDevice* device,int numelements,int stride, eStructuredBufferMode mode)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	mDevice = device;
	mElementCount = numelements;
	mStride = stride;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS;
	desc.ByteWidth = numelements * stride;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	desc.StructureByteStride = stride;
	
	mDevice->GetDevice()->CreateBuffer(&desc,NULL,&mObj->mBuffer);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
	ZeroMemory(&uavd,sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
	uavd.Format = DXGI_FORMAT_UNKNOWN;
	uavd.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_BUFFER;
	uavd.Buffer.NumElements = numelements;
	uavd.Buffer.Flags =  mode;

	mDevice->GetDevice()->CreateUnorderedAccessView(mObj->mBuffer,&uavd,&mObj->mUAV);
	mDevice->GetDevice()->CreateShaderResourceView(mObj->mBuffer,NULL,&mObj->mSRV);
}

StructuredBuffer::StructuredBuffer(DxDevice* device,int numelements,int stride, void* initial)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	this->mDevice = device;
	this->mElementCount = numelements;
	this->mStride = stride;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
	desc.ByteWidth = numelements * stride;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	desc.StructureByteStride = stride;

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

void* StructuredBuffer::LockForWrite()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = mDevice->GetContext()->Map(mObj->mBuffer,0,D3D11_MAP::D3D11_MAP_WRITE_DISCARD,0,&mappedResource);

	if (FAILED(hr))
	{
		return NULL;
	}

	return mappedResource.pData;
}

void* StructuredBuffer::LockForRead()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = mDevice->GetContext()->Map(mObj->mBuffer,0,D3D11_MAP::D3D11_MAP_READ,0,&mappedResource);

	if (FAILED(hr))
	{
		return NULL;
	}


	return mappedResource.pData;
}

void StructuredBuffer::Unlock()
{
	mDevice->GetContext()->Unmap(mObj->mBuffer,0);
}

void StructuredBuffer::WriteData(void* data, UINT length)
{
	void* ptr = this->LockForWrite();
	memcpy(ptr,data,length);
	this->Unlock();
}

}}