#pragma once

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

class DepthStencilBase
{
public:
	virtual ID3D11DepthStencilView* GetDSV() = 0;
	virtual ID3D11DepthStencilView* GetReadOnlyDSV() = 0;
	virtual D3D11_DEPTH_STENCIL_VIEW_DESC GetDescription() = 0;
	
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
protected:
	DepthStencilBase(DxDevice* device);
	DxDevice* mDevice;
};

} }