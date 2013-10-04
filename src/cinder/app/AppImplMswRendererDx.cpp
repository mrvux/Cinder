// The copyright in this software is being made available under the BSD License, included below. 
// This software may be subject to other third party and contributor rights, including patent rights, 
// and no such rights are granted under this license.
//
// Copyright (c) 2013, Microsoft Open Technologies, Inc. 
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice, 
//   this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice, 
//   this list of conditions and the following disclaimer in the documentation 
//   and/or other materials provided with the distribution.
// - Neither the name of Microsoft Open Technologies, Inc. nor the names of its contributors 
//   may be used to endorse or promote products derived from this software 
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS �AS IS� AND ANY EXPRESS OR IMPLIED WARRANTIES, 
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#include "cinder/app/AppImplMswRendererDx.h"
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

namespace Shaders {

	// DirectX 9.1
	namespace Dx9_1 {
		#include "compiled_4_0_level_9_1/CompiledFixedFunctionVS.inc"
		#include "compiled_4_0_level_9_1/CompiledFixedFunctionPS.inc"
		#include "compiled_4_0_level_9_1/CompiledFixedFunctionLightingVS.inc"
		#include "compiled_4_0_level_9_1/CompiledFixedFunctionLightingPS.inc"
		#include "compiled_4_0_level_9_1/CompiledFixedFunctionTextureVS.inc"
		#include "compiled_4_0_level_9_1/CompiledFixedFunctionTexturePS.inc"
		#include "compiled_4_0_level_9_1/CompiledFixedFunctionTextureLightingVS.inc"
		#include "compiled_4_0_level_9_1/CompiledFixedFunctionTextureLightingPS.inc"

		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionNormalVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionTextureVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionColorVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionNormalTextureVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionNormalColorVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionColorTextureVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionNormalColorTextureVS.inc"

		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionLightVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionNormalLightVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionTextureLightVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionColorLightVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionNormalTextureLightVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionNormalColorLightVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionColorTextureLightVS.inc"
		#include "compiled_4_0_level_9_1/CompiledStandardVboLayoutPositionNormalColorTextureLightVS.inc"
	}

	// DirectX 9.3
	namespace Dx9_3 {
		#include "compiled_4_0_level_9_3/CompiledFixedFunctionVS.inc"
		#include "compiled_4_0_level_9_3/CompiledFixedFunctionPS.inc"
		#include "compiled_4_0_level_9_3/CompiledFixedFunctionLightingVS.inc"
		#include "compiled_4_0_level_9_3/CompiledFixedFunctionLightingPS.inc"
		#include "compiled_4_0_level_9_3/CompiledFixedFunctionTextureVS.inc"
		#include "compiled_4_0_level_9_3/CompiledFixedFunctionTexturePS.inc"
		#include "compiled_4_0_level_9_3/CompiledFixedFunctionTextureLightingVS.inc"
		#include "compiled_4_0_level_9_3/CompiledFixedFunctionTextureLightingPS.inc"

		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionNormalVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionTextureVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionColorVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionNormalTextureVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionNormalColorVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionColorTextureVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionNormalColorTextureVS.inc"

		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionLightVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionNormalLightVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionTextureLightVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionColorLightVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionNormalTextureLightVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionNormalColorLightVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionColorTextureLightVS.inc"
		#include "compiled_4_0_level_9_3/CompiledStandardVboLayoutPositionNormalColorTextureLightVS.inc"
	}

	// DirectX 10.0 and 10.1
	namespace Dx10 {
		#include "compiled_4_1/CompiledFixedFunctionVS.inc"
		#include "compiled_4_1/CompiledFixedFunctionPS.inc"
		#include "compiled_4_1/CompiledFixedFunctionLightingVS.inc"
		#include "compiled_4_1/CompiledFixedFunctionLightingPS.inc"
		#include "compiled_4_1/CompiledFixedFunctionTextureVS.inc"
		#include "compiled_4_1/CompiledFixedFunctionTexturePS.inc"
		#include "compiled_4_1/CompiledFixedFunctionTextureLightingVS.inc"
		#include "compiled_4_1/CompiledFixedFunctionTextureLightingPS.inc"

		#include "compiled_4_1/CompiledStandardVboLayoutPositionVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionNormalVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionTextureVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionColorVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionNormalTextureVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionNormalColorVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionColorTextureVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionNormalColorTextureVS.inc"

		#include "compiled_4_1/CompiledStandardVboLayoutPositionLightVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionNormalLightVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionTextureLightVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionColorLightVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionNormalTextureLightVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionNormalColorLightVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionColorTextureLightVS.inc"
		#include "compiled_4_1/CompiledStandardVboLayoutPositionNormalColorTextureLightVS.inc"
	}

	// DirectX 11.0 and 11.1
	namespace Dx11 {
		#include "compiled_5_0/CompiledFixedFunctionVS.inc"
		#include "compiled_5_0/CompiledFixedFunctionPS.inc"
		#include "compiled_5_0/CompiledFixedFunctionLightingVS.inc"
		#include "compiled_5_0/CompiledFixedFunctionLightingPS.inc"
		#include "compiled_5_0/CompiledFixedFunctionTextureVS.inc"
		#include "compiled_5_0/CompiledFixedFunctionTexturePS.inc"
		#include "compiled_5_0/CompiledFixedFunctionTextureLightingVS.inc"
		#include "compiled_5_0/CompiledFixedFunctionTextureLightingPS.inc"

		#include "compiled_5_0/CompiledStandardVboLayoutPositionVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionNormalVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionTextureVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionColorVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionNormalTextureVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionNormalColorVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionColorTextureVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionNormalColorTextureVS.inc"

		#include "compiled_5_0/CompiledStandardVboLayoutPositionLightVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionNormalLightVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionTextureLightVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionColorLightVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionNormalTextureLightVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionNormalColorLightVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionColorTextureLightVS.inc"
		#include "compiled_5_0/CompiledStandardVboLayoutPositionNormalColorTextureLightVS.inc"
	}
}

namespace cinder { namespace app {

//bool sMultisampleSupported = false;
//int sArbMultisampleFormat;

AppImplMswRendererDx::AppImplMswRendererDx( App *aApp, RendererDx *aRenderer )
: AppImplMswRenderer( aApp ),
  mCurrentBatchTexture(NULL),
  mCurrentColor(1, 1, 1, 1),
  mCurrentNormal(0, 0, 1),
  mCurrentUV(0, 0),
  mLightingEnabled(false),
  mRenderer( aRenderer ),
  mDevice( NULL ),
  mSwapChain( NULL ),
  mDepthStencil( NULL ),
  mFixedColorVertexShader( NULL ),
  mFixedColorPixelShader( NULL ),
  mFixedColorLightVertexShader( NULL ),
  mFixedColorLightPixelShader( NULL ),
  mFixedTextureVertexShader( NULL ),
  mFixedTexturePixelShader( NULL ),
  mFixedTextureLightVertexShader( NULL ),
  mFixedTextureLightPixelShader( NULL ),
  mVboPositionVS( NULL ),
  mVboPositionNormalVS( NULL ),
  mVboPositionColorVS( NULL ),
  mVboPositionTextureVS( NULL ),
  mVboPositionNormalColorVS( NULL ),
  mVboPositionNormalTextureVS( NULL ),
  mVboPositionColorTextureVS( NULL ),
  mVboPositionNormalColorTextureVS( NULL ),
  mVboPositionLightVS( NULL ),
  mVboPositionNormalLightVS( NULL ),
  mVboPositionColorLightVS( NULL ),
  mVboPositionTextureLightVS( NULL ),
  mVboPositionNormalColorLightVS( NULL ),
  mVboPositionNormalTextureLightVS( NULL ),
  mVboPositionColorTextureLightVS( NULL ),
  mVboPositionNormalColorTextureLightVS( NULL ),
  mFixedLayout( NULL ),
  mVertexBuffer( NULL ),
  mIndexBuffer( NULL ),
  mDefaultRenderState( NULL ),
  mDepthStencilState( NULL ),
  mCBMatrices( NULL ),
  mCBLights( NULL ),
  mCBFixedParameters( NULL ),
  mBlendState( NULL ),
  mStateFlags(0),
  mVsyncEnable( false ),
  mFullScreen( false )
{
}

void AppImplMswRendererDx::prepareToggleFullScreen()
{
	releaseNonDeviceResources();
}

void AppImplMswRendererDx::finishToggleFullScreen()
{
	mFullScreen = !mFullScreen;
	mSwapChain->SetFullScreen(mFullScreen);
}

void AppImplMswRendererDx::getPlatformWindowDimensions(DX_WINDOW_TYPE wnd, float* width, float* height) const {

#if defined( CINDER_MSW ) 
	RECT rect;
	::GetClientRect(wnd, &rect);
	*width = static_cast<float>(rect.right - rect.left);
	*height = static_cast<float>(rect.bottom - rect.top);

#elif defined( CINDER_WINRT )
	return GetPlatformWindowDimensions(wnd.Get(), width, height);
#endif
}

void AppImplMswRendererDx::releaseNonDeviceResources()
{
	if(mFixedColorVertexShader) mFixedColorVertexShader->Release(); mFixedColorVertexShader = NULL;
	if(mFixedColorPixelShader) mFixedColorPixelShader->Release(); mFixedColorPixelShader = NULL;
	if(mFixedColorLightVertexShader) mFixedColorLightVertexShader->Release(); mFixedColorLightVertexShader = NULL;
	if(mFixedColorLightPixelShader) mFixedColorLightPixelShader->Release(); mFixedColorLightPixelShader = NULL;
	if(mFixedTextureVertexShader) mFixedTextureVertexShader->Release(); mFixedTextureVertexShader = NULL;
	if(mFixedTexturePixelShader) mFixedTexturePixelShader->Release(); mFixedTexturePixelShader = NULL;
	if(mFixedTextureLightVertexShader) mFixedTextureLightVertexShader->Release(); mFixedTextureLightVertexShader = NULL;
	if(mFixedTextureLightPixelShader) mFixedTextureLightPixelShader->Release(); mFixedTextureLightPixelShader = NULL;
	if(mVboPositionVS) mVboPositionVS->Release(); mVboPositionVS = NULL;
	if(mVboPositionNormalVS) mVboPositionNormalVS->Release(); mVboPositionNormalVS = NULL;
	if(mVboPositionTextureVS) mVboPositionTextureVS->Release(); mVboPositionTextureVS = NULL;
	if(mVboPositionColorVS) mVboPositionColorVS->Release(); mVboPositionColorVS = NULL;
	if(mVboPositionNormalColorVS) mVboPositionNormalColorVS->Release(); mVboPositionNormalColorVS = NULL;
	if(mVboPositionNormalTextureVS) mVboPositionNormalTextureVS->Release(); mVboPositionNormalTextureVS = NULL;
	if(mVboPositionColorTextureVS) mVboPositionColorTextureVS->Release(); mVboPositionColorTextureVS = NULL;
	if(mVboPositionNormalColorTextureVS) mVboPositionNormalColorTextureVS->Release(); mVboPositionNormalColorTextureVS = NULL;
	if(mVboPositionLightVS) mVboPositionLightVS->Release(); mVboPositionLightVS = NULL;
	if(mVboPositionNormalLightVS) mVboPositionNormalLightVS->Release(); mVboPositionNormalLightVS = NULL;
	if(mVboPositionTextureLightVS) mVboPositionTextureLightVS->Release(); mVboPositionTextureLightVS = NULL;
	if(mVboPositionColorLightVS) mVboPositionColorLightVS->Release(); mVboPositionColorLightVS = NULL;
	if(mVboPositionNormalColorLightVS) mVboPositionNormalColorLightVS->Release(); mVboPositionNormalColorLightVS = NULL;
	if(mVboPositionNormalTextureLightVS) mVboPositionNormalTextureLightVS->Release(); mVboPositionNormalTextureLightVS = NULL;
	if(mVboPositionColorTextureLightVS) mVboPositionColorTextureLightVS->Release(); mVboPositionColorTextureLightVS = NULL;
	if(mVboPositionNormalColorTextureLightVS) mVboPositionNormalColorTextureLightVS->Release(); mVboPositionNormalColorTextureLightVS = NULL;
	if(mFixedLayout) mFixedLayout->Release(); mFixedLayout = NULL;
	if(mVertexBuffer) mVertexBuffer->Release(); mVertexBuffer = NULL;
	if(mIndexBuffer) mIndexBuffer->Release(); mIndexBuffer = NULL;
	if(mCBMatrices) mCBMatrices->Release(); mCBMatrices = NULL;
	if(mCBLights) mCBLights->Release(); mCBLights = NULL;
	if(mCBFixedParameters) mCBFixedParameters->Release(); mCBFixedParameters = NULL;
	if(mBlendState) mBlendState->Release(); mBlendState = NULL;
	if(mDefaultRenderState) mDefaultRenderState->Release(); mDefaultRenderState = NULL;
	if(mDepthStencilState) mDepthStencilState->Release(); mDepthStencilState = NULL;
	if(mSwapChain) delete mSwapChain; mSwapChain = NULL;
	if (mDepthStencil) delete mDepthStencil; mDepthStencil = NULL;
}

void AppImplMswRendererDx::defaultResize() const
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

	dx::setProjection(cam);
	dx::setModelView(cam);

	//these two lines flip the y-axis and move the origin up
	dx::multModelView(Matrix44f::createScale(Vec3f(1, -1, 1)));
	dx::multModelView(Matrix44f::createTranslation(Vec3f(0, -height, 0)));
}

void AppImplMswRendererDx::swapBuffers() const
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
	if(hr == DXGI_ERROR_DEVICE_REMOVED)
		const_cast<AppImplMswRendererDx*>(this)->handleLostDevice();
#if defined( CINDER_WINRT ) || ( _WIN32_WINNT >= 0x0602 )
	mDevice->GetContext()->DiscardView( mSwapChain->GetRenderTarget()->GetRTV());
	mDevice->GetContext()->DiscardView( mDepthStencil->GetDSV());
#endif
}

void AppImplMswRendererDx::makeCurrentContext()
{
	BindPrimaryBuffer();
}

void AppImplMswRendererDx::setViewport(int x, int y, int width, int height) const
{
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = (FLOAT)x;
    vp.TopLeftY = (FLOAT)y;
	mDevice->GetContext()->RSSetViewports( 1, &vp );
}

void AppImplMswRendererDx::enableDepthTesting(bool enable)
{
	mDepthStencilDesc.DepthEnable = enable == true;
	if(mDepthStencilState) mDepthStencilState->Release();
	mDevice->GetDevice()->CreateDepthStencilState(&mDepthStencilDesc, &mDepthStencilState);
	mDevice->GetContext()->OMSetDepthStencilState(mDepthStencilState, 0xff);
}

void AppImplMswRendererDx::enableAlphaBlending(bool premultiplied)
{
	if(mBlendState) mBlendState->Release();
	mBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	mBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	mBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	mBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	if(!premultiplied)
	{
		mBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		mBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	}
	else
	{
		mBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		mBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	}
	mDevice->GetDevice()->CreateBlendState(&mBlendDesc, &mBlendState);
	mDevice->GetContext()->OMSetBlendState(mBlendState, 0, 0xffffffff);
}

void AppImplMswRendererDx::disableAlphaBlending()
{
	if(mBlendState) mBlendState->Release();
	mBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	mDevice->GetDevice()->CreateBlendState(&mBlendDesc, &mBlendState);
	mDevice->GetContext()->OMSetBlendState(mBlendState, 0, 0xffffffff);
}

void AppImplMswRendererDx::enableAdditiveBlending()
{
	if(mBlendState) mBlendState->Release();
	mBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	mBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	mBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	mBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	mBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	mBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	mDevice->GetDevice()->CreateBlendState(&mBlendDesc, &mBlendState);
	mDevice->GetContext()->OMSetBlendState(mBlendState, 0, 0xffffffff);
}

void AppImplMswRendererDx::enableDepthWriting(bool enable)
{
	mDepthStencilDesc.DepthWriteMask = (enable) ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
	if(mDepthStencilState) mDepthStencilState->Release();
	mDevice->GetDevice()->CreateDepthStencilState(&mDepthStencilDesc, &mDepthStencilState);
}

void AppImplMswRendererDx::FlushContext()
{
	mDevice->GetContext()->Flush();
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
bool AppImplMswRendererDx::initialize( DX_WINDOW_TYPE wnd)
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

bool AppImplMswRendererDx::initializeInternal( DX_WINDOW_TYPE wnd )
{
	mWnd = wnd;
	
	if(!createDeviceResources())
		return false;

	if(!createFramebufferResources())
		return false;

	// create fixed function vertex shader
	HRESULT hr = E_FAIL;
	// hr = mDevice->GetDevice()->CreateVertexShader(Shaders::FixedFunctionVS, sizeof(Shaders::FixedFunctionVS), NULL, &mFixedColorVertexShader);
	if( D3D_FEATURE_LEVEL_9_1 == mDevice->GetFeatureLevel() ) {
		hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::FixedFunctionVS, sizeof(Shaders::Dx9_1::FixedFunctionVS), NULL, &mFixedColorVertexShader);
	}
	else if( D3D_FEATURE_LEVEL_9_3 == mDevice->GetFeatureLevel() ) {
		hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::FixedFunctionVS, sizeof(Shaders::Dx9_3::FixedFunctionVS), NULL, &mFixedColorVertexShader);
	}
	else if( D3D_FEATURE_LEVEL_10_1 == mDevice->GetFeatureLevel() ) {
		hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::FixedFunctionVS, sizeof(Shaders::Dx10::FixedFunctionVS), NULL, &mFixedColorVertexShader);
	}
	else if( D3D_FEATURE_LEVEL_11_0 == mDevice->GetFeatureLevel() || D3D_FEATURE_LEVEL_11_1 == mDevice->GetFeatureLevel() ) {
		hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::FixedFunctionVS, sizeof(Shaders::Dx11::FixedFunctionVS), NULL, &mFixedColorVertexShader);
	}				
	if(hr != S_OK)
		return false;

	// create the input layout for fixed functionality
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	//hr = mDevice->GetDevice()->CreateInputLayout(layout, sizeof(layout) / sizeof(layout[0]), Shaders::FixedFunctionVS, sizeof(Shaders::FixedFunctionVS), &mFixedLayout);
	if( D3D_FEATURE_LEVEL_9_1 == mDevice->GetFeatureLevel() ) {
		hr = mDevice->GetDevice()->CreateInputLayout(layout, sizeof(layout) / sizeof(layout[0]), Shaders::Dx9_1::FixedFunctionVS, sizeof(Shaders::Dx9_1::FixedFunctionVS), &mFixedLayout);
	}
	else if( D3D_FEATURE_LEVEL_9_3 == mDevice->GetFeatureLevel() ) {
		hr = mDevice->GetDevice()->CreateInputLayout(layout, sizeof(layout) / sizeof(layout[0]), Shaders::Dx9_3::FixedFunctionVS, sizeof(Shaders::Dx9_3::FixedFunctionVS), &mFixedLayout);
	}
	else if( D3D_FEATURE_LEVEL_10_1 == mDevice->GetFeatureLevel() ) {
		hr = mDevice->GetDevice()->CreateInputLayout(layout, sizeof(layout) / sizeof(layout[0]), Shaders::Dx10::FixedFunctionVS, sizeof(Shaders::Dx10::FixedFunctionVS), &mFixedLayout);
	}
	else if( D3D_FEATURE_LEVEL_11_0 == mDevice->GetFeatureLevel() || D3D_FEATURE_LEVEL_11_1 == mDevice->GetFeatureLevel() ) {
		hr = mDevice->GetDevice()->CreateInputLayout(layout, sizeof(layout) / sizeof(layout[0]), Shaders::Dx11::FixedFunctionVS, sizeof(Shaders::Dx11::FixedFunctionVS), &mFixedLayout);
	}		
	if(hr != S_OK)
		return false;
	mDevice->GetContext()->IASetInputLayout(mFixedLayout);

	// create shaders
	bool bShadersSucceeded = false;
	if( D3D_FEATURE_LEVEL_9_1 == mDevice->GetFeatureLevel() ) {
		bShadersSucceeded = createShadersFeatureLevel_9_1();	
	}
	else if( D3D_FEATURE_LEVEL_9_3 == mDevice->GetFeatureLevel() ) {
		bShadersSucceeded = createShadersFeatureLevel_9_3();	
	}
	else if( D3D_FEATURE_LEVEL_10_1 == mDevice->GetFeatureLevel() ) {
		bShadersSucceeded = createShadersFeatureLevel_10_1();
	}
	else if( D3D_FEATURE_LEVEL_11_0 == mDevice->GetFeatureLevel() ) {
		bShadersSucceeded = createShadersFeatureLevel_11_0();
	}
	else if( D3D_FEATURE_LEVEL_11_0 == mDevice->GetFeatureLevel() ) {
		bShadersSucceeded = createShadersFeatureLevel_11_1();
	}

	if( ! bShadersSucceeded ) {
		return false;
	}

	// create vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = D3D_FL9_1_IA_PRIMITIVE_MAX_COUNT * sizeof(FixedVertex) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	hr = mDevice->GetDevice()->CreateBuffer( &bd, NULL, &mVertexBuffer );
	if(hr != S_OK)
		return false;

	// create index buffer
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.ByteWidth = D3D_FL9_1_IA_PRIMITIVE_MAX_COUNT * sizeof(int);
	hr = mDevice->GetDevice()->CreateBuffer( &bd, NULL, &mIndexBuffer );
	if(hr != S_OK)
		return false;

	// create matrix cbuffer
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Matrix44f) * 2;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hr = mDevice->GetDevice()->CreateBuffer( &bd, NULL, &mCBMatrices );
	if(hr != S_OK)
		return false;

	// create fixed lighting buffer
	bd.ByteWidth = sizeof(LightData) * 8;
	hr = mDevice->GetDevice()->CreateBuffer( &bd, NULL, &mCBLights );
	if(hr != S_OK)
		return false;

	// create fixed function parameters
	bd.ByteWidth = sizeof(Vec4f) * 3;
	hr = mDevice->GetDevice()->CreateBuffer( &bd, NULL, &mCBFixedParameters );
	if(hr != S_OK)
		return false;

	// change some rendering parameters, ie. no culling, anti-aliasing, direction of forward-facing triangles
	// to mimick what the default OpenGL render state seems to be doing
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.FrontCounterClockwise = TRUE;
	rd.DepthBias = 0;
	rd.DepthBiasClamp = 0;
	rd.SlopeScaledDepthBias = 0;
	rd.DepthClipEnable = TRUE;
	rd.ScissorEnable = FALSE;
	rd.MultisampleEnable = FALSE;
	rd.AntialiasedLineEnable = FALSE;
	hr = mDevice->GetDevice()->CreateRasterizerState( &rd, &mDefaultRenderState );
	if(hr != S_OK)
		__debugbreak();
	mDevice->GetContext()->RSSetState( mDefaultRenderState );

	//copying the default OpenGL depth behavior
	mDepthStencilDesc.DepthEnable = FALSE;
	mDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	mDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	mDepthStencilDesc.StencilEnable = FALSE;
	mDepthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	mDepthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	mDepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	mDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	mDepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	mDepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	mDepthStencilDesc.BackFace = mDepthStencilDesc.FrontFace;
	hr = mDevice->GetDevice()->CreateDepthStencilState( &mDepthStencilDesc, &mDepthStencilState );
	if(hr != S_OK)
		__debugbreak();
	mDevice->GetContext()->OMSetDepthStencilState( mDepthStencilState, 0 );

	mBlendDesc.AlphaToCoverageEnable = FALSE;
	mBlendDesc.IndependentBlendEnable = FALSE;
	mBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	mBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	mBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	mBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	mBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	mBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	mBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	mBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = mDevice->GetDevice()->CreateBlendState(&mBlendDesc, &mBlendState);
	if(hr != S_OK)
		__debugbreak();
	mDevice->GetContext()->OMSetBlendState(mBlendState, 0, 0xffffffff);

	return true;									// Success
}

int AppImplMswRendererDx::initMultisample( int requestedLevelIdx )
{
	// Return failure if we hit level 0
	return 0;
}

bool AppImplMswRendererDx::createDeviceResources()
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
}

bool AppImplMswRendererDx::createFramebufferResources()
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
}

void AppImplMswRendererDx::BindPrimaryBuffer()
{
	ID3D11RenderTargetView* rtv = mSwapChain->GetRenderTarget()->GetRTV();
	mDevice->GetContext()->OMSetRenderTargets( 1, &rtv,mDepthStencil->GetDSV());

	//Could also use resource
	float width, height;
	getPlatformWindowDimensions(mWnd, &width, &height);

	//Make sure we also set viewport again, since previous render targets might be of different size
	setViewport(0, 0, static_cast<UINT>(width), static_cast<UINT>(height));
}

bool AppImplMswRendererDx::createShadersFeatureLevel_9_1()
{
	HRESULT hr;

	// create fixed function fragment shader
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx9_1::FixedFunctionPS, sizeof(Shaders::Dx9_1::FixedFunctionPS), NULL, &mFixedColorPixelShader);
	if(hr != S_OK)
		return false;

	// create the other fixed function shaders
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::FixedFunctionLightingVS, sizeof(Shaders::Dx9_1::FixedFunctionLightingVS), NULL, &mFixedColorLightVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx9_1::FixedFunctionLightingPS, sizeof(Shaders::Dx9_1::FixedFunctionLightingPS), NULL, &mFixedColorLightPixelShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::FixedFunctionTextureVS, sizeof(Shaders::Dx9_1::FixedFunctionTextureVS), NULL, &mFixedTextureVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx9_1::FixedFunctionTexturePS, sizeof(Shaders::Dx9_1::FixedFunctionTexturePS), NULL, &mFixedTexturePixelShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::FixedFunctionTextureLightingVS, sizeof(Shaders::Dx9_1::FixedFunctionTextureLightingVS), NULL, &mFixedTextureLightVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx9_1::FixedFunctionTextureLightingPS, sizeof(Shaders::Dx9_1::FixedFunctionTextureLightingPS), NULL, &mFixedTextureLightPixelShader);
	if(hr != S_OK)
		return false;

	// create the vbo shaders
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionVS), NULL, &mVboPositionVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionNormalVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionNormalVS), NULL, &mVboPositionNormalVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionColorVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionColorVS), NULL, &mVboPositionColorVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionTextureVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionTextureVS), NULL, &mVboPositionTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionNormalColorVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionNormalColorVS), NULL, &mVboPositionNormalColorVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionNormalTextureVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionNormalTextureVS), NULL, &mVboPositionNormalTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionColorTextureVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionColorTextureVS), NULL, &mVboPositionColorTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionNormalColorTextureVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionNormalColorTextureVS), NULL, &mVboPositionNormalColorTextureVS);
	if(hr != S_OK)
		return false;

	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionLightVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionLightVS), NULL, &mVboPositionLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionNormalLightVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionNormalLightVS), NULL, &mVboPositionNormalLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionColorLightVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionColorLightVS), NULL, &mVboPositionColorLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionTextureLightVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionTextureLightVS), NULL, &mVboPositionTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionNormalColorLightVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionNormalColorLightVS), NULL, &mVboPositionNormalColorLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionNormalTextureLightVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionNormalTextureLightVS), NULL, &mVboPositionNormalTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionColorTextureLightVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionColorTextureLightVS), NULL, &mVboPositionColorTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_1::StandardVboLayoutPositionNormalColorTextureLightVS, sizeof(Shaders::Dx9_1::StandardVboLayoutPositionNormalColorTextureLightVS), NULL, &mVboPositionNormalColorTextureLightVS);
	if(hr != S_OK)
		return false;

	return true;
}

bool AppImplMswRendererDx::createShadersFeatureLevel_9_3()
{
	HRESULT hr;

	// create fixed function fragment shader
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx9_3::FixedFunctionPS, sizeof(Shaders::Dx9_3::FixedFunctionPS), NULL, &mFixedColorPixelShader);
	if(hr != S_OK)
		return false;

	// create the other fixed function shaders
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::FixedFunctionLightingVS, sizeof(Shaders::Dx9_3::FixedFunctionLightingVS), NULL, &mFixedColorLightVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx9_3::FixedFunctionLightingPS, sizeof(Shaders::Dx9_3::FixedFunctionLightingPS), NULL, &mFixedColorLightPixelShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::FixedFunctionTextureVS, sizeof(Shaders::Dx9_3::FixedFunctionTextureVS), NULL, &mFixedTextureVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx9_3::FixedFunctionTexturePS, sizeof(Shaders::Dx9_3::FixedFunctionTexturePS), NULL, &mFixedTexturePixelShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::FixedFunctionTextureLightingVS, sizeof(Shaders::Dx9_3::FixedFunctionTextureLightingVS), NULL, &mFixedTextureLightVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx9_3::FixedFunctionTextureLightingPS, sizeof(Shaders::Dx9_3::FixedFunctionTextureLightingPS), NULL, &mFixedTextureLightPixelShader);
	if(hr != S_OK)
		return false;

	// create the vbo shaders
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionVS), NULL, &mVboPositionVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionNormalVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionNormalVS), NULL, &mVboPositionNormalVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionColorVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionColorVS), NULL, &mVboPositionColorVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionTextureVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionTextureVS), NULL, &mVboPositionTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionNormalColorVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionNormalColorVS), NULL, &mVboPositionNormalColorVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionNormalTextureVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionNormalTextureVS), NULL, &mVboPositionNormalTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionColorTextureVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionColorTextureVS), NULL, &mVboPositionColorTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionNormalColorTextureVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionNormalColorTextureVS), NULL, &mVboPositionNormalColorTextureVS);
	if(hr != S_OK)
		return false;

	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionLightVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionLightVS), NULL, &mVboPositionLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionNormalLightVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionNormalLightVS), NULL, &mVboPositionNormalLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionColorLightVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionColorLightVS), NULL, &mVboPositionColorLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionTextureLightVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionTextureLightVS), NULL, &mVboPositionTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionNormalColorLightVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionNormalColorLightVS), NULL, &mVboPositionNormalColorLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionNormalTextureLightVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionNormalTextureLightVS), NULL, &mVboPositionNormalTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionColorTextureLightVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionColorTextureLightVS), NULL, &mVboPositionColorTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx9_3::StandardVboLayoutPositionNormalColorTextureLightVS, sizeof(Shaders::Dx9_3::StandardVboLayoutPositionNormalColorTextureLightVS), NULL, &mVboPositionNormalColorTextureLightVS);
	if(hr != S_OK)
		return false;

	return true;
}

bool AppImplMswRendererDx::createShadersFeatureLevel_10_1()
{
	HRESULT hr;

	// create fixed function fragment shader
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx10::FixedFunctionPS, sizeof(Shaders::Dx10::FixedFunctionPS), NULL, &mFixedColorPixelShader);
	if(hr != S_OK)
		return false;

	// create the other fixed function shaders
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::FixedFunctionLightingVS, sizeof(Shaders::Dx10::FixedFunctionLightingVS), NULL, &mFixedColorLightVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx10::FixedFunctionLightingPS, sizeof(Shaders::Dx10::FixedFunctionLightingPS), NULL, &mFixedColorLightPixelShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::FixedFunctionTextureVS, sizeof(Shaders::Dx10::FixedFunctionTextureVS), NULL, &mFixedTextureVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx10::FixedFunctionTexturePS, sizeof(Shaders::Dx10::FixedFunctionTexturePS), NULL, &mFixedTexturePixelShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::FixedFunctionTextureLightingVS, sizeof(Shaders::Dx10::FixedFunctionTextureLightingVS), NULL, &mFixedTextureLightVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx10::FixedFunctionTextureLightingPS, sizeof(Shaders::Dx10::FixedFunctionTextureLightingPS), NULL, &mFixedTextureLightPixelShader);
	if(hr != S_OK)
		return false;

	// create the vbo shaders
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionVS), NULL, &mVboPositionVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionNormalVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionNormalVS), NULL, &mVboPositionNormalVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionColorVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionColorVS), NULL, &mVboPositionColorVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionTextureVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionTextureVS), NULL, &mVboPositionTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionNormalColorVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionNormalColorVS), NULL, &mVboPositionNormalColorVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionNormalTextureVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionNormalTextureVS), NULL, &mVboPositionNormalTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionColorTextureVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionColorTextureVS), NULL, &mVboPositionColorTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionNormalColorTextureVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionNormalColorTextureVS), NULL, &mVboPositionNormalColorTextureVS);
	if(hr != S_OK)
		return false;

	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionLightVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionLightVS), NULL, &mVboPositionLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionNormalLightVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionNormalLightVS), NULL, &mVboPositionNormalLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionColorLightVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionColorLightVS), NULL, &mVboPositionColorLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionTextureLightVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionTextureLightVS), NULL, &mVboPositionTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionNormalColorLightVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionNormalColorLightVS), NULL, &mVboPositionNormalColorLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionNormalTextureLightVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionNormalTextureLightVS), NULL, &mVboPositionNormalTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionColorTextureLightVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionColorTextureLightVS), NULL, &mVboPositionColorTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx10::StandardVboLayoutPositionNormalColorTextureLightVS, sizeof(Shaders::Dx10::StandardVboLayoutPositionNormalColorTextureLightVS), NULL, &mVboPositionNormalColorTextureLightVS);
	if(hr != S_OK)
		return false;

	return true;
}

bool AppImplMswRendererDx::createShadersFeatureLevel_11_0()
{
	HRESULT hr;

	// create fixed function fragment shader
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx11::FixedFunctionPS, sizeof(Shaders::Dx11::FixedFunctionPS), NULL, &mFixedColorPixelShader);
	if(hr != S_OK)
		return false;

	// create the other fixed function shaders
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::FixedFunctionLightingVS, sizeof(Shaders::Dx11::FixedFunctionLightingVS), NULL, &mFixedColorLightVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx11::FixedFunctionLightingPS, sizeof(Shaders::Dx11::FixedFunctionLightingPS), NULL, &mFixedColorLightPixelShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::FixedFunctionTextureVS, sizeof(Shaders::Dx11::FixedFunctionTextureVS), NULL, &mFixedTextureVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx11::FixedFunctionTexturePS, sizeof(Shaders::Dx11::FixedFunctionTexturePS), NULL, &mFixedTexturePixelShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::FixedFunctionTextureLightingVS, sizeof(Shaders::Dx11::FixedFunctionTextureLightingVS), NULL, &mFixedTextureLightVertexShader);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreatePixelShader(Shaders::Dx11::FixedFunctionTextureLightingPS, sizeof(Shaders::Dx11::FixedFunctionTextureLightingPS), NULL, &mFixedTextureLightPixelShader);
	if(hr != S_OK)
		return false;

	// create the vbo shaders
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionVS), NULL, &mVboPositionVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionNormalVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionNormalVS), NULL, &mVboPositionNormalVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionColorVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionColorVS), NULL, &mVboPositionColorVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionTextureVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionTextureVS), NULL, &mVboPositionTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionNormalColorVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionNormalColorVS), NULL, &mVboPositionNormalColorVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionNormalTextureVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionNormalTextureVS), NULL, &mVboPositionNormalTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionColorTextureVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionColorTextureVS), NULL, &mVboPositionColorTextureVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionNormalColorTextureVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionNormalColorTextureVS), NULL, &mVboPositionNormalColorTextureVS);
	if(hr != S_OK)
		return false;

	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionLightVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionLightVS), NULL, &mVboPositionLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionNormalLightVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionNormalLightVS), NULL, &mVboPositionNormalLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionColorLightVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionColorLightVS), NULL, &mVboPositionColorLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionTextureLightVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionTextureLightVS), NULL, &mVboPositionTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionNormalColorLightVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionNormalColorLightVS), NULL, &mVboPositionNormalColorLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionNormalTextureLightVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionNormalTextureLightVS), NULL, &mVboPositionNormalTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionColorTextureLightVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionColorTextureLightVS), NULL, &mVboPositionColorTextureLightVS);
	if(hr != S_OK)
		return false;
	hr = mDevice->GetDevice()->CreateVertexShader(Shaders::Dx11::StandardVboLayoutPositionNormalColorTextureLightVS, sizeof(Shaders::Dx11::StandardVboLayoutPositionNormalColorTextureLightVS), NULL, &mVboPositionNormalColorTextureLightVS);
	if(hr != S_OK)
		return false;

	return true;
}

bool AppImplMswRendererDx::createShadersFeatureLevel_11_1()
{
	return createShadersFeatureLevel_11_0();
}

void AppImplMswRendererDx::handleLostDevice()
{
	delete mSwapChain;
	mSwapChain = NULL;

	createDeviceResources();
	defaultResize();
}

void AppImplMswRendererDx::kill()
{
	if (mDevice) { mDevice->GetContext()->ClearState(); }
	releaseNonDeviceResources();

	if (mDevice) 
	{ 
		delete mDevice;
		mDevice = NULL;
	}
}



} } // namespace cinder::app
