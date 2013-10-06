#include "cinder/dx/rendering/ResourcePool.h"

namespace cinder { namespace dx {

ResourcePool::ResourcePool(DxDevice* device)
{
	mDevice = device;
}

RenderTarget2PoolElement* ResourcePool::LockRenderTarget2(int w, int h, DXGI_FORMAT format)
{
	for (int i = 0; i < mTarget2.size(); i++)
	{
		RenderTarget2PoolElement* elem = mTarget2.at(i);
		RenderTarget2* rt = elem->GetElement();

		if (elem->IsFree() && rt->GetWidth() == w && rt->GetHeight() && h && rt->GetDescription().Format == format)
		{
			elem->Lock();
			return elem;
		}
	}

	//Create
	RenderTarget2* rt = new RenderTarget2(mDevice,w,h,format);
	RenderTarget2PoolElement* element = new RenderTarget2PoolElement(rt);
	mTarget2.push_back(element);
	return element;
}

void ResourcePool::Unlock(RenderTarget2* element)
{
	for (int i = 0; i < mTarget2.size(); i++)
	{
		if (mTarget2.at(i)->GetElement() == element)
		{
			mTarget2.at(i)->UnLock();
			break;
		}
	}
}

} }