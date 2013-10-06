#include "cinder/dx/resources/RenderTarget2.h"

using namespace std;

namespace cinder { namespace dx {

RenderTarget2::Obj::Obj()
{
	mRTV = 0;
}

RenderTarget2::Obj::~Obj()
{
	if (mRTV) { mRTV->Release(); }
}

RenderTarget2::RenderTarget2(DxDevice* device, Texture2* texture) 
	 : RenderTargetBase(device) , mObj( shared_ptr<Obj>( new Obj() ) )
{
	//Resource not allowed as render target
	if (texture->GetResourceDesc().BindFlags && D3D11_BIND_RENDER_TARGET != D3D11_BIND_RENDER_TARGET) 
	{
		DxException exc("Texture doesn't have RenderTarget Flag");
		throw exc;
	}

	D3D11_RENDER_TARGET_VIEW_DESC rtvd;
	ZeroMemory(&rtvd,sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	rtvd.Format = texture->GetResourceDesc().Format;
	rtvd.ViewDimension = texture->GetResourceDesc().SampleDesc.Count > 1 ? D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;

	HRESULT hr = mDevice->GetDevice()->CreateRenderTargetView(texture->GetTexture(),&rtvd,&mObj->mRTV);

	if (FAILED(hr))
	{
		DxException exc("Failed to create RenderTargetView");
		throw exc;
	}

	mObj->mTexture = texture;
}

RenderTarget2::RenderTarget2(DxDevice* device, int w, int h, DXGI_FORMAT format, int samplecount) 
	 : RenderTargetBase(device) , mObj( shared_ptr<Obj>( new Obj() ) )
{
	D3D11_TEXTURE2D_DESC resourceDesc;
	ZeroMemory(&resourceDesc,sizeof(D3D11_TEXTURE2D_DESC));
	resourceDesc.ArraySize = 1;
	resourceDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	resourceDesc.CPUAccessFlags = 0;
	resourceDesc.Format = format;
	resourceDesc.Height = h;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count= samplecount;
	resourceDesc.Usage = D3D11_USAGE_DEFAULT;
	resourceDesc.Width = w;

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderViewDesc;
	ZeroMemory(&shaderViewDesc,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	shaderViewDesc.Format = format;
	shaderViewDesc.ViewDimension = samplecount > 1 ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderViewDesc.Texture2D.MipLevels = 1;
	shaderViewDesc.Texture2D.MostDetailedMip = 0;

	mObj->mTexture = new Texture2(mDevice,resourceDesc,shaderViewDesc);

	D3D11_RENDER_TARGET_VIEW_DESC renderViewDesc;
	ZeroMemory(&renderViewDesc,sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	renderViewDesc.Format = format;
	renderViewDesc.ViewDimension = samplecount > 1 ? D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;
	renderViewDesc.Texture2D.MipSlice = 0;

	HRESULT res = mDevice->GetDevice()->CreateRenderTargetView(mObj->mTexture->GetTexture(),&renderViewDesc,&mObj->mRTV);

	mRenderViewDesc = renderViewDesc;

}


}}