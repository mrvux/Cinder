#pragma once

#include "cinder/Cinder.h"
#include "cinder/Color.h"

#define INITGUID 
#include <d3d11.h>
#include <d3dcompiler.h>
#include "msw/effects11/d3dx11effect.h"

#if defined( CINDER_WINRT )
	#define USE_D3D11_1 1 //Don't change here
#else
	//We can specify here otherwise
	#define USE_D3D11_1 1
#endif

#if USE_D3D11_1
	#include <d3d11_1.h>
#endif

#include "cinder/Exception.h"

namespace cinder { namespace dx {

//Typedef for device in case we use DirectX 11 or DirectX 11.1
#if USE_D3D11_1
	typedef ID3D11Device1 IDXDevice;
	typedef ID3D11DeviceContext1 IDXContext;
	typedef IDXGIFactory2 IDXFactory;
	typedef IDXGIAdapter2 IDXAdapter;
#else
	typedef ID3D11Device IDXDevice;
	typedef ID3D11DeviceContext IDXContext;
	typedef IDXGIFactory IDXFactory;
	typedef IDXGIAdapter IDXAdapter;
#endif
		

class DxException : public Exception  {
  public:
	DxException() : Exception() { mMessage[0] = 0; }

	DxException( const std::string &message ) throw() : Exception()
	{
		strncpy_s( mMessage, message.c_str(), 255 );
	}
	virtual const char * what() const throw() { return mMessage; }	
  private:	
	char	mMessage[256];
};

} }