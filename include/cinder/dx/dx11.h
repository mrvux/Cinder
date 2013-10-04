#include <d3d11.h>

//TODO: in winrt it's always set to true
#define USE_D3D11_1 1// ISWIN8 _WIN32_WINNT >= 0x0602

#if USE_D3D11_1
	#include <d3d11_1.h>
#endif

#include "cinder/Exception.h"

namespace cinder { namespace dx {

//Typedef for device in case we use DirectX 11 or DirectX 11.1
#if USE_D3D11_1
	typedef ID3D11Device1 IDxDevice;
	typedef ID3D11DeviceContext1 IDxContext;
#else
	typedef ID3D11Device IDxDevice;
	typedef ID3D11DeviceContext IDxContext;
#endif
		

class DxException : public Exception  {
  public:
	DxException() : Exception() { mMessage[0] = 0; }

	DxException( const std::string &message ) throw() : Exception()
	{
		strncpy( mMessage, message.c_str(), 255 );
	}
	virtual const char * what() const throw() { return mMessage; }	
  private:	
	char	mMessage[256];
};

} }