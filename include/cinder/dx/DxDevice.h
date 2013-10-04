#pragma once

#include "dx11.h"

namespace cinder { namespace dx {

class DxDevice
{
public:
	DxDevice();
	DxDevice(UINT flags);
	~DxDevice();

	inline IDxDevice* GetDevice() { return mObj->mDevice; }
	inline IDxContext* GetContext() { return mObj->mContext; }

	inline bool IsFeatureLevel11() { return mFeatureLevel >= D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0; }
	inline bool HasBufferSupport() { return mBufferSupport; }
private:
	void Initialize(UINT flags);
	struct Obj 
	{
		Obj();
		~Obj();
		IDXGIFactory1* mFactory;
		IDXGIAdapter1* mAdapter;
		IDxDevice* mDevice;
		IDxContext* mContext;

	};

	std::shared_ptr<Obj> mObj;
	D3D_FEATURE_LEVEL mFeatureLevel;
	bool mBufferSupport;
};

} }