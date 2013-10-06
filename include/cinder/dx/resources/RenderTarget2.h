#pragma once

#include "cinder/Color.h"

#include "cinder/dx/DxDevice.h"
#include "RenderTargetBase.h"
#include "Texture2.h"

namespace cinder { namespace dx {

class RenderTarget2;
typedef std::shared_ptr<RenderTarget2> RenderTarget2Ref;

class RenderTarget2 : public RenderTargetBase
{
public:
	RenderTarget2(DxDevice* device, Texture2* texture);
	RenderTarget2(DxDevice* context, int w, int h, DXGI_FORMAT format, int samplecount = 1);

	virtual ID3D11RenderTargetView* GetRTV() { return mObj->mRTV; }
	virtual D3D11_RENDER_TARGET_VIEW_DESC GetDescription() { return mRenderViewDesc; }

	virtual int GetWidth() { return mObj->mTexture->GetResourceDesc().Width; }
	virtual int GetHeight() { return mObj->mTexture->GetResourceDesc().Height; }

	inline Texture2* GetTexture() { return mObj->mTexture; }
private:
	void Initialize(DxDevice* device, int w, int h, DXGI_FORMAT format, int samplecount = 1);

	struct Obj 
	{
		Obj();
		~Obj();
		ID3D11RenderTargetView* mRTV;
		Texture2* mTexture;
	};

	D3D11_RENDER_TARGET_VIEW_DESC mRenderViewDesc;

	std::shared_ptr<Obj> mObj;
	
};

}}