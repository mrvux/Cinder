/*  
 Copyright (c) 2012, The Cinder Project, All rights reserved.
 Copyright (c) Microsoft Open Technologies, Inc. All rights reserved.

 This code is intended for use with the Cinder C++ library: http://libcinder.org

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and
	the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
	the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "cinder/app/Renderer.h"

namespace cinder { namespace app {

typedef std::shared_ptr<class RendererFlare>	RendererFlareRef;
class RendererFlare : public Renderer {
  public:
	RendererFlare( int aAntiAliasing = AA_MSAA_16 );
	~RendererFlare();
	
	static RendererFlareRef	create( int antiAliasing = AA_MSAA_16  ) { return RendererFlareRef( new RendererFlare( antiAliasing ) ); }
	virtual RendererRef		clone() const { return RendererFlareRef( new RendererFlare( *this ) ); }
	virtual RendererType	getRendererType() const override { return RENDERER_DX; }

#if defined ( CINDER_MSW )
	virtual void setup( App *aApp, HWND wnd, HDC dc, RendererRef sharedRenderer );
	virtual HWND	getHwnd() { return mWnd; }
#elif defined( CINDER_WINRT )
	virtual void	setup( App *aApp, DX_WINDOW_TYPE wnd);
#endif

	virtual void	kill();
	virtual void	prepareToggleFullScreen();
	virtual void	finishToggleFullScreen();

	enum	{ AA_NONE = 0, AA_MSAA_2, AA_MSAA_4, AA_MSAA_6, AA_MSAA_8, AA_MSAA_16, AA_MSAA_32 };
	static const int	sAntiAliasingSamples[];
	void				setAntiAliasing( int aAntiAliasing );
	int					getAntiAliasing() const { return mAntiAliasing; }

	virtual void	startDraw();
	virtual void	finishDraw();
	virtual void	defaultResize();
	virtual Surface	copyWindowSurface( const Area &area );
	virtual void	makeCurrentContext();

	class AppImplFlareRenderer	*mImpl;
	
 protected:
	RendererFlare( const RendererFlare &renderer );

	int				mAntiAliasing;
	DX_WINDOW_TYPE	mWnd;
};

} } // namespace cinder::app