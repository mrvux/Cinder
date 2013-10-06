#pragma once

#include "cinder/Color.h"

#include "cinder/dx/DxDevice.h"
#include "RenderTarget2.h"
#include "Texture2.h"

namespace cinder { namespace dx {

class SwapChain
{
public:
	#if defined( CINDER_WINRT )
	SwapChain(DxDevice* device, IUnknown* window,UINT width, UINT height);
	#else
	SwapChain(DxDevice* device, HWND handle);
	#endif

	HRESULT Present(bool vsync = false);
	void Clear(const ci::ColorAf& color);
	bool Resize();
	bool Resize(UINT count,UINT width,UINT height,DXGI_FORMAT format);

	void SetFullScreen(bool enabled);

	inline Texture2* GetResource() const { return mObj->mTexture; }
	inline RenderTarget2* GetRenderTarget() const { return mObj->mRenderTarget; }

private:
	void BuildResources();
	struct Obj 
	{
		Obj();
		~Obj();
		#if USE_D3D11_1
		IDXGISwapChain1* mSwapChain;
		#else
		IDXGISwapChain* mSwapChain;
		#endif
		
		Texture2* mTexture;
		RenderTarget2* mRenderTarget;
	};

	HWND mHandle;
	DxDevice* mDevice;

	std::shared_ptr<Obj> mObj;
};

}}