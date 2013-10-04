#pragma once

#include "dx11.h"

namespace cinder { namespace dx {

class DxDevice;
typedef std::shared_ptr<DxDevice> DxDeviceRef;

class DxDevice
{
public:
	DxDevice();
	DxDevice(UINT flags);
	~DxDevice();

	inline IDXDevice* GetDevice() { return mObj->mDevice; }
	inline IDXContext* GetContext() { return mObj->mContext; }
	inline IDXFactory* GetFactory() { return mObj->mFactory; }

	inline bool IsFeatureLevel11() { return mFeatureLevel >= D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0; }
	inline bool HasBufferSupport() { return mBufferSupport; }
	inline D3D_FEATURE_LEVEL GetFeatureLevel() { return mFeatureLevel; }
private:
	void Initialize(UINT flags);
	struct Obj 
	{
		Obj();
		~Obj();
		IDXFactory* mFactory;
		IDXAdapter* mAdapter;
		IDXDevice* mDevice;
		IDXContext* mContext;

	};

	std::shared_ptr<Obj> mObj;
	D3D_FEATURE_LEVEL mFeatureLevel;
	bool mBufferSupport;
};

} }