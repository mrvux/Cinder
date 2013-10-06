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

#include "cinder/app/RendererFlare.h"
#include "cinder/Exception.h"
#include "cinder/app/AppImplFlareRenderer.h"
#include "cinder/ip/Flip.h"

namespace cinder { namespace app {

RendererFlare::RendererFlare( int aAntiAliasing )
	: Renderer(), mImpl( 0 ), mAntiAliasing( aAntiAliasing )
{
}

RendererFlare::RendererFlare( const RendererFlare &renderer ) : mImpl(0), mWnd(renderer.mWnd)
{
}

RendererFlare::~RendererFlare()
{
	delete mImpl;
}


#if defined( CINDER_MSW )
void RendererFlare::setup( App *aApp, HWND wnd, HDC dc,  RendererRef sharedRenderer)
{
	mWnd = wnd;
	mApp = aApp;
	if( ! mImpl )
		mImpl = new AppImplFlareRenderer( mApp, this );
	mImpl->initialize( wnd, dc, sharedRenderer );
}
#elif defined( CINDER_WINRT )
void RendererFlare::setup( App *aApp, DX_WINDOW_TYPE wnd)
{
	mWnd = wnd;
	mApp = aApp;
	if( ! mImpl )
		mImpl = new AppImplFlareRenderer( mApp, this );
	mImpl->initialize( wnd);

	// enable Vertical Sync drawing on WinRT
	mImpl->enableVsync(TRUE);
}
#endif

void RendererFlare::kill()
{
	mImpl->kill();
}

void RendererFlare::prepareToggleFullScreen()
{
	mImpl->prepareToggleFullScreen();
}

void RendererFlare::finishToggleFullScreen()
{
	mImpl->finishToggleFullScreen();
}

void RendererFlare::startDraw()
{
	mImpl->makeCurrentContext();
}

void RendererFlare::finishDraw()
{
	mImpl->swapBuffers();
}

void RendererFlare::defaultResize()
{
	mImpl->defaultResize();
}

Surface	RendererFlare::copyWindowSurface( const Area &area )
{
	/*Surface s( area.getWidth(), area.getHeight(), true );
	//glFlush(); // there is some disagreement about whether this is necessary, but ideally performance-conscious users will use FBOs anyway
	mImpl->FlushContext();
	//GLint oldPackAlignment;
	//glGetIntegerv( GL_PACK_ALIGNMENT, &oldPackAlignment ); 
	//glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	//glReadPixels( area.x1, mApp->getWindowHeight() - area.y2, area.getWidth(), area.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, s.getData() );
	//glPixelStorei( GL_PACK_ALIGNMENT, oldPackAlignment );	
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = area.getWidth();
	desc.Height = area.getHeight();
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.MiscFlags = 0;

	ID3D11Texture2D *texture;
	mImpl->GetDevice()->CreateTexture2D(&desc, NULL, &texture);

	D3D11_BOX box;
	box.front = 0;
	box.back = 1;
	box.left = area.x1;
	box.right = area.x2;
	box.top = area.y1;
	box.bottom = area.y2;

	ID3D11Texture2D *framebuffer = mImpl->GetPrimarySwapChain()->GetResource()->GetTexture();
	mImpl->GetContext()->CopySubresourceRegion(texture, 0, 0, 0, 0, framebuffer, 0, &box);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	mImpl->GetContext()->Map(texture, 0, D3D11_MAP_READ, 0, &mappedResource);
	memcpy(s.getData(), mappedResource.pData, area.calcArea() * 4);
	mImpl->GetContext()->Unmap(texture, 0);

	texture->Release();
	framebuffer->Release();*/

	//ip::flipVertical( &s );
	return NULL;
}

void RendererFlare::makeCurrentContext()
{
	mImpl->makeCurrentContext();
}

} } //namespace cinder::app