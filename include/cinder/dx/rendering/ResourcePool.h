#pragma once

#include "cinder/dx/DxDevice.h"
#include "cinder/dx/resources/RenderTarget2.h"

#include <vector>

namespace cinder { namespace dx {

class ResourcePool;

template<class T>
class ResourcePoolElement
{
	friend class ResourcePool;
public:

	ResourcePoolElement(T* element) 
	{
		mElement = element;
		mLocked = true;
	}
	inline void UnLock() { mLocked = false; }
	inline bool IsLocked() { return mLocked; }
	inline bool IsFree() { return !mLocked; }
	inline T* GetElement() { return mElement; }
protected:
	inline void Lock() { mLocked = true; }
private:
	T* mElement;
	bool mLocked;
};

typedef ResourcePoolElement<RenderTarget2> RenderTarget2PoolElement;

class ResourcePool
{
public:
	ResourcePool(DxDevice* device);
	RenderTarget2PoolElement* LockRenderTarget2(int w, int h, DXGI_FORMAT format);

	void Unlock(RenderTarget2* element);
private:
	DxDevice* mDevice;
	std::vector<RenderTarget2PoolElement*> mTarget2;
};

} }