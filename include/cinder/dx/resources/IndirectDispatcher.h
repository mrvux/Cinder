#pragma once

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

struct DispatchArgs
{
	UINT TGX;
    UINT TGY;
    UINT TGZ;
};

class StructuredBuffer;

class IndirectDispatcher
{
public:
	IndirectDispatcher(DxDevice* device, UINT TX = 1, UINT TY = 1, UINT TZ = 1);

	void CopyCounter(StructuredBuffer* buffer);
	void Dispatch();

	inline ID3D11ShaderResourceView* GetCounterView() { return mObj->mSRV; }
	inline ID3D11UnorderedAccessView* GetUAV() { return mObj->mUAV; }

private:
	struct Obj 
	{
		Obj();
		~Obj();
		ID3D11Buffer* mCountBuffer;
		ID3D11Buffer* mArgBuffer;
		ID3D11ShaderResourceView* mSRV;
		ID3D11UnorderedAccessView* mUAV;
	};

	std::shared_ptr<Obj> mObj;
	DxDevice* mDevice;
};

} }