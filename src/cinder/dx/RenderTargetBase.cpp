#include "cinder/dx/RenderTargetBase.h"

namespace cinder { namespace dx {

	RenderTargetBase::RenderTargetBase(DxDevice* device)
{
	mDevice = device;
}

void RenderTargetBase::Clear(const ci::ColorAf& color)
{
	mDevice->GetContext()->ClearRenderTargetView(this->GetRTV(),&color[0]);
}

}}