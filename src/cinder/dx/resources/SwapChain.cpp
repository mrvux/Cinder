#include "cinder/dx/resources/SwapChain.h"

using namespace std;

namespace cinder { namespace dx {

SwapChain::Obj::Obj()
{
	mSwapChain = NULL;
	mTexture = NULL;
	mRenderTarget = NULL;
}

SwapChain::Obj::~Obj()
{
	if (mSwapChain) { mSwapChain->Release(); }
	if (mTexture) { delete mTexture; }
	if (mRenderTarget) { delete mRenderTarget; }
}

SwapChain::SwapChain(DxDevice* device, IUnknown* window,UINT width, UINT height)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	mDevice = device;

	DXGI_SWAP_CHAIN_DESC1 desc;
	ZeroMemory(&desc,sizeof(DXGI_SWAP_CHAIN_DESC1));
	desc.BufferCount = 2; //Set to 1 for windows phone
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	desc.Scaling = DXGI_SCALING_STRETCH;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; //Windows phone and desktop, prefer DXGI_SWAP_EFFECT_DISCARD
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	desc.Width = width;
	desc.Height = height;
	
	HRESULT hr = mDevice->GetFactory()->CreateSwapChainForCoreWindow( mDevice->GetDevice(), window, &desc, nullptr, &mObj->mSwapChain);

	if (FAILED(hr))
	{
		DxException exc("Failed to create SwapChain");
		throw exc;
	}

	BuildResources();
}

void SwapChain::BuildResources()
{
	ID3D11Texture2D* texture;
	mObj->mSwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(void**)(&texture));
	//Get Buffer does an AddRef on top so we release
	texture->Release();

	ID3D11ShaderResourceView* view;
	mDevice->GetDevice()->CreateShaderResourceView(texture,NULL,&view);

	mObj->mTexture = new Texture2(mDevice,texture,view,false);
	mObj->mRenderTarget = new RenderTarget2(this->mDevice,mObj->mTexture);
}

bool SwapChain::Resize()
{
	return mObj->mSwapChain->ResizeBuffers(0,0,0,DXGI_FORMAT_UNKNOWN,0) == S_OK;
}

bool SwapChain::Resize(UINT count,UINT width,UINT height,DXGI_FORMAT format)
{
	delete mObj->mRenderTarget;
	delete mObj->mTexture;

	HRESULT hr = mObj->mSwapChain->ResizeBuffers(count,width,height,format,0);

	//if (SUCCEEDED(hr))
	//{
		BuildResources();
	//}

	return hr == S_OK;
}


void SwapChain::Clear(const ci::ColorAf& color)
{
	mObj->mRenderTarget->Clear(color);
}

HRESULT SwapChain::Present(bool vsync)
{
	return mObj->mSwapChain->Present(vsync ? 1 : 0,0);
}

void SwapChain::SetFullScreen(bool enabled)
{
	mObj->mSwapChain->SetFullscreenState(enabled,NULL);
}

}}