#pragma once

#include "cinder/app/App.h"
#include "cinder/app/AppImplMswRenderer.h"
#include "cinder/app/RendererFlare.h"

#include "cinder/dx/DxAPI.h"

#include "cinder/dx/dx.h"
#include <d3dcompiler.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <dxgi.h>
#include <dxgi1_2.h>


namespace cinder { namespace app {

class AppImplFlareRenderer : public AppImplMswRenderer {
 public:
	AppImplFlareRenderer( App *aApp, RendererFlare *aRenderer );
	
#if defined( CINDER_MSW )
	virtual bool	initialize( HWND wnd, HDC dc,  RendererRef sharedRenderer );
#elif defined( CINDER_WINRT)
	virtual bool	initialize( DX_WINDOW_TYPE wnd );
#endif

	virtual void	prepareToggleFullScreen();
	virtual void	finishToggleFullScreen();
	virtual void	kill();
	virtual void	defaultResize() const;
	virtual void	swapBuffers() const;
	virtual void	makeCurrentContext();

	void enableVsync(bool enable = true) { mVsyncEnable = enable; }
	bool vsyncEnabled() const { return mVsyncEnable; }

	RendererFlare	*mRenderer;

	/*inline ci::dx::IDXContext* GetContext() { return mDevice->GetContext(); }
	inline ci::dx::IDXDevice* GetDevice() { return mDevice->GetDevice(); }
	inline D3D_FEATURE_LEVEL GetFeatureLevel() { return mDevice->GetFeatureLevel(); }
	inline ci::dx::DxDevice* GetDxDevice() { return mDevice; }*/

	inline ci::dx::RenderContext* GetRenderContext() { return mRenderContext; }

	inline ci::dx::SwapChain* GetPrimarySwapChain() { return mSwapChain; }
	inline ci::dx::DepthStencil* GetDepthStencil() { return mDepthStencil; }
 protected:
	bool	initializeInternal( DX_WINDOW_TYPE wnd );
	void	getPlatformWindowDimensions(DX_WINDOW_TYPE wnd, float* width, float* height) const;
	
	bool mFullScreen;
	bool mVsyncEnable;

	ci::dx::DxDevice* mDevice;
	ci::dx::RenderContext* mRenderContext;

	ci::dx::SwapChain* mSwapChain;
	ci::dx::DepthStencil* mDepthStencil;
};

} } // namespace cinder::app
