#include "cinder/app/AppImplFlareRenderer.h"
#include "cinder/dx/dx.h"
#include "cinder/app/App.h"
#include "cinder/Camera.h"

#include <windows.h>
#if ! defined( CINDER_WINRT )
#include <windowsx.h>
#endif

#if defined( CINDER_WINRT )
#include "cinder/WinRTUtils.h"
using namespace Windows::UI::Core;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace cinder::winrt;
using namespace cinder::dx;
#endif

namespace cinder { namespace app {

//bool sMultisampleSupported = false;
//int sArbMultisampleFormat;

AppImplFlareRenderer::AppImplFlareRenderer( App *aApp, RendererFlare *aRenderer )
: AppImplMswRenderer( aApp ),
  mRenderer( aRenderer ),
  mDevice( NULL ),
  mSwapChain( NULL ),
  mDepthStencil( NULL ),
  mVsyncEnable( false ),
  mFullScreen( false )
{
}

void AppImplFlareRenderer::prepareToggleFullScreen()
{
	//releaseNonDeviceResources();
}

void AppImplFlareRenderer::finishToggleFullScreen()
{
	mFullScreen = !mFullScreen;
	mSwapChain->SetFullScreen(mFullScreen);
}

void AppImplFlareRenderer::getPlatformWindowDimensions(DX_WINDOW_TYPE wnd, float* width, float* height) const {

#if defined( CINDER_MSW ) 
	RECT rect;
	::GetClientRect(wnd, &rect);
	*width = static_cast<float>(rect.right - rect.left);
	*height = static_cast<float>(rect.bottom - rect.top);

#elif defined( CINDER_WINRT )
	return GetPlatformWindowDimensions(wnd.Get(), width, height);
#endif
}

void AppImplFlareRenderer::defaultResize() const
{
	if(!mSwapChain)
		return;

	float width, height;
	getPlatformWindowDimensions(mWnd, &width, &height);

	ID3D11RenderTargetView *view = NULL;
	mDevice->GetContext()->OMSetRenderTargets(1, &view, NULL);
	mDevice->GetContext()->Flush();

	mSwapChain->Resize(2,width,height,DXGI_FORMAT_R8G8B8A8_UNORM);

	cinder::CameraPersp cam( static_cast<int>(width), static_cast<int>(height), 60.0f );

	/*dx::setProjection(cam);
	dx::setModelView(cam);

	//these two lines flip the y-axis and move the origin up
	dx::multModelView(Matrix44f::createScale(Vec3f(1, -1, 1)));
	dx::multModelView(Matrix44f::createTranslation(Vec3f(0, -height, 0)));*/
}

void AppImplFlareRenderer::swapBuffers() const
{
	DXGI_PRESENT_PARAMETERS parameters = {0};
	parameters.DirtyRectsCount = 0;
	parameters.pDirtyRects = nullptr;
	parameters.pScrollRect = nullptr;
	parameters.pScrollOffset = nullptr;

	HRESULT hr;
#if defined( CINDER_WINRT ) || ( _WIN32_WINNT >= 0x0602 )
	hr = mSwapChain->Present(mVsyncEnable);
	/*( mVsyncEnable )
		hr = mSwapChain->Present(Present1( 1, 0, &parameters );
	else
		hr = mSwapChain->Present1( 0, 0, &parameters );*/
#else
	if( mVsyncEnable )
		hr = mSwapChain->Present( 1, 0 );
	else
		hr = mSwapChain->Present( 0, 0 );
#endif
	//handle device lost
	/*if(hr == DXGI_ERROR_DEVICE_REMOVED)
		const_cast<AppImplMswRendererDx*>(this)->handleLostDevice();*/
#if defined( CINDER_WINRT ) || ( _WIN32_WINNT >= 0x0602 )
	/*mDevice->GetContext()->DiscardView( mSwapChain->GetRenderTarget()->GetRTV());
	mDevice->GetContext()->DiscardView( mDepthStencil->GetDSV());*/
#endif
}

void AppImplFlareRenderer::makeCurrentContext()
{

}


#if defined( CINDER_MSW )
bool AppImplMswRendererDx::initialize( HWND wnd, HDC,  RendererRef sharedRenderer )
{
	// TODO: see if DX can do antialiasing automatically
	bool success = initializeInternal( wnd );
	if(!success)
	{
		MessageBox(wnd, L"Couldn't initialize DirectX. App will now quit.", L"Error", MB_OK);
		mApp->quit();
	}
	return success;
}
#elif defined( CINDER_WINRT )
bool AppImplFlareRenderer::initialize( DX_WINDOW_TYPE wnd)
{
	// TODO: see if DX can do antialiasing automatically
	bool success = initializeInternal( wnd );
	if(!success)
	{
		::WinRTMessageBox("Couldn't initialize DirectX.", "OK");
		return FALSE;
	}
	return success;
}
#endif

bool AppImplFlareRenderer::initializeInternal( DX_WINDOW_TYPE wnd )
{
	mWnd = wnd;

	return true;
}



/*bool AppImplFlareRenderer::createDeviceResources()
{
	try
	{
		mDevice = new ci::dx::DxDevice();
		return true;
	}
	catch (dx::DxException exc)
	{
		return false;
	}
}*/

/*bool AppImplMswRendererDx::createFramebufferResources()
{
	float width, height;
	getPlatformWindowDimensions(mWnd, &width, &height);

	HRESULT hr;
	if(mSwapChain)
	{
		if (!mSwapChain->Resize(2,width,height,DXGI_FORMAT_R8G8B8A8_UNORM))
			return false;
	}
	else
	{
		mSwapChain = new SwapChain(mDevice,reinterpret_cast<IUnknown*>(mWnd.Get()),width,height);
	}

	try
	{
		mDepthStencil = new DepthStencil(mDevice,static_cast<UINT>(width),static_cast<UINT>(height));
	}
	catch (DxException exc)
	{
		return false;
	}

	BindPrimaryBuffer();

	return true;
}*/



void AppImplFlareRenderer::kill()
{
	if (mDevice) { mDevice->GetContext()->ClearState(); }
	//releaseNonDeviceResources();

	if (mDevice) 
	{ 
		delete mDevice;
		mDevice = NULL;
	}
}



} } // namespace cinder::app
