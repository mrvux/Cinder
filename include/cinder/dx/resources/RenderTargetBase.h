#pragma once

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

class RenderTargetBase
{
public:
	void Clear(const ci::ColorAf& color);

	virtual ID3D11RenderTargetView* GetRTV() = 0;
	virtual D3D11_RENDER_TARGET_VIEW_DESC GetDescription() = 0;
	
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
protected:
	RenderTargetBase(DxDevice* device);
	DxDevice* mDevice;
};

} }