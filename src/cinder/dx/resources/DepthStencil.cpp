#include "cinder/dx/resources/DepthStencil.h"

using namespace std;

namespace cinder { namespace dx {

DepthStencil::Obj::Obj()
{
	mDSV = 0;
	mReadOnlyDSV = 0;
	mResource = 0;
	mSRV = 0;
}

DepthStencil::Obj::~Obj()
{
	if (mDSV) { mDSV->Release(); }
	if (mReadOnlyDSV) { mReadOnlyDSV->Release(); }
	if (mSRV) { mSRV->Release(); }
	if (mResource) { mResource->Release(); }
}

DepthStencil::DepthStencil(DxDevice* device, int w, int h,DXGI_FORMAT format, int samplecount,bool readonly)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	mDevice = device;
	mWidth = w;
	mHeight = h;
	Initialize(mDevice,w,h,format,samplecount,readonly);
}


DepthStencil::~DepthStencil(void)
{

}

void DepthStencil::Clear(bool depth, bool stencil, float depthvalue,BYTE stencilvalue)
{
	if (!depth && !stencil) { return; }

	UINT flag = 0;
	if (depth) { flag = flag | D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH; }
	if (stencil) { flag = flag | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL; }

	mDevice->GetContext()->ClearDepthStencilView(mObj->mDSV,flag,depth,stencilvalue);
}

void DepthStencil::Initialize(DxDevice* device, int w, int h,DXGI_FORMAT format, int samplecount,bool readonly)
{
	HRESULT hr;

	DXGI_FORMAT resformat = GetDepthResourceFormat(format);
	DXGI_FORMAT srvformat = GetDepthSRVFormat(format);

	D3D11_TEXTURE2D_DESC desc;
	desc.ArraySize = 1;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.Format = resformat;
	desc.Height = h;
	desc.MipLevels = 1;
	desc.MiscFlags = 0;
	desc.SampleDesc.Count = samplecount;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	desc.Width = w;

	hr = mDevice->GetDevice()->CreateTexture2D(&desc,NULL,&mObj->mResource);

	if (FAILED(hr))
	{
		DxException exc("Failed to create DepthStencil resource");
		throw exc;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC ddesc;
	ZeroMemory(&ddesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	ddesc.Format = format;
	ddesc.ViewDimension = samplecount > 1 ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
	ddesc.Texture2D.MipSlice = 0;

	hr = mDevice->GetDevice()->CreateDepthStencilView(mObj->mResource,&ddesc,&mObj->mDSV);

	if (FAILED(hr))
	{
		DxException exc("Failed to create DepthStencil View");
		throw exc;
	}

	if (readonly)
	{
		ddesc.Flags = D3D11_DSV_READ_ONLY_DEPTH;
		hr = mDevice->GetDevice()->CreateDepthStencilView(mObj->mResource,&ddesc,&mObj->mReadOnlyDSV);

		if (FAILED(hr))
		{
			DxException exc("Failed to create DepthStencil ReadOnlyView");
			throw exc;
		}
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvd.Format = srvformat;
	srvd.ViewDimension = samplecount > 1 ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = 1;

	hr = mDevice->GetDevice()->CreateShaderResourceView(mObj->mResource,&srvd,&mObj->mSRV);

	if (FAILED(hr))
	{
		DxException exc("Failed to create DepthStencil Shader View");
		throw exc;
	}
}

}}