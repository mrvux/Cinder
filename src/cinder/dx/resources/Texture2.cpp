#include "cinder/dx/resources/Texture2.h"

using namespace std;

namespace cinder { namespace dx {

Texture2::Obj::Obj()
{
	mTexture = NULL;
	mSRV = NULL;
}

Texture2::Obj::~Obj()
{
	if (mTexture) { mTexture->Release(); mTexture= 0; }
	if (mSRV) { mSRV->Release(); mSRV = 0; }
}

Texture2::Texture2(DxDevice* device,const D3D11_TEXTURE2D_DESC& description)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	mDevice = device;

	mDevice->GetDevice()->CreateTexture2D(&description,NULL,&mObj->mTexture);

	if (mResourceDesc.BindFlags && D3D11_BIND_SHADER_RESOURCE == D3D11_BIND_SHADER_RESOURCE)
	{
		mDevice->GetDevice()->CreateShaderResourceView(mObj->mTexture,NULL,&mObj->mSRV);
		mObj->mSRV->GetDesc(&mViewDesc);
	}
}

Texture2::Texture2(DxDevice* device,const D3D11_TEXTURE2D_DESC& resourcedesc,const D3D11_SHADER_RESOURCE_VIEW_DESC& viewdesc)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	HRESULT hr;
	mDevice = device;
	
	hr = mDevice->GetDevice()->CreateTexture2D(&resourcedesc,NULL,&mObj->mTexture);

	hr = mDevice->GetDevice()->CreateShaderResourceView(mObj->mTexture,&viewdesc,&mObj->mSRV);

	mObj->mTexture->GetDesc(&mResourceDesc);
	mObj->mSRV->GetDesc(&mViewDesc);
}

Texture2::Texture2(DxDevice* device,ID3D11Texture2D* texture,ID3D11ShaderResourceView* view, bool addref)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	mDevice = device;

	mObj->mTexture = texture;
	mObj->mTexture->GetDesc(&mResourceDesc);
	mObj->mSRV = view;

	if (view)
	{
		mObj->mSRV->GetDesc(&mViewDesc);
		if (addref)
		{
			mObj->mSRV->AddRef();
		}
	} 
	
	if (addref)
	{
		mObj->mTexture->AddRef();
	}
}

void* Texture2::LockForWrite()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	mDevice->GetContext()->Map(mObj->mTexture,0,D3D11_MAP::D3D11_MAP_WRITE_DISCARD,0,&mappedResource);
	return mappedResource.pData;
}

void* Texture2::LockForRead()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	mDevice->GetContext()->Map(mObj->mTexture,0,D3D11_MAP::D3D11_MAP_READ,0,&mappedResource);
	return mappedResource.pData;
}

void Texture2::Unlock()
{
	mDevice->GetContext()->Unmap(mObj->mTexture,0);
}

void Texture2::WriteData(void* data, UINT length)
{
	void* ptr = this->LockForWrite();
	memcpy(ptr,data,length);
	this->Unlock();
}


} }