#pragma once

#include "cinder/Cinder.h"
#include "cinder/dx/DxDevice.h"
#include "Texture2.h"

namespace cinder { namespace dx {

DXGI_FORMAT GetDepthResourceFormat(DXGI_FORMAT depthformat);
DXGI_FORMAT GetDepthSRVFormat(DXGI_FORMAT depthformat);

class DepthStencil;
typedef std::shared_ptr<DepthStencil> DepthStencilRef;

class DepthStencil
{
public:
	DepthStencil(DxDevice* device, int w, int h,DXGI_FORMAT format = DXGI_FORMAT_D24_UNORM_S8_UINT, int samplecount = 1, bool readonly=false);
	~DepthStencil(void);

	void Clear(bool depth = true, bool stencil = true, float depthvalue = 1.0f,BYTE stencilvalue = 0);

	inline ID3D11DepthStencilView* GetDSV() { return mObj->mDSV; }
	inline ID3D11DepthStencilView* GetReadOnlyDSV() { return mObj->mReadOnlyDSV; }
	inline ID3D11ShaderResourceView* GetSRV() { return mObj->mSRV; }
	inline int GetWidth() { return mWidth; }
	inline int GetHeight() { return mHeight; }
private:

	void Initialize(DxDevice* device, int w, int h,DXGI_FORMAT format = DXGI_FORMAT_D24_UNORM_S8_UINT, int samplecount = 1, bool readonly=false);

	struct Obj 
	{
		Obj();
		~Obj();
		ID3D11Texture2D* mResource;
		ID3D11ShaderResourceView* mSRV;
		ID3D11DepthStencilView* mDSV;
		ID3D11DepthStencilView* mReadOnlyDSV;
	};

	DxDevice* mDevice;
	int mWidth,mHeight;

	std::shared_ptr<Obj>	mObj;
};

}}