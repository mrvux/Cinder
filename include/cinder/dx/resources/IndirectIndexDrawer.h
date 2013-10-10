#pragma once

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

struct DrawIndexedInstancedArgs
{
	UINT IndicesCount;
	UINT InstanceCount;
	UINT StartIndexLocation;
	UINT BaseVertexLocation;
	UINT StartInstanceLocation;
};

class StructuredBuffer;

class IndirectIndexDrawer
{
public:
	IndirectIndexDrawer(DxDevice* device, UINT IndicesCount = 1, UINT InstanceCount = 1, UINT StartIndexLocation = 0,UINT BaseVertexLocation = 0, UINT StartInstanceLocation = 0);

	void Draw();
	void CopyIndexCount(StructuredBuffer* buffer);
	void CopyInstanceCount(StructuredBuffer* buffer);

	inline ID3D11ShaderResourceView* GetCounterView() { return mObj->mSRV; }
	inline ID3D11UnorderedAccessView* GetUAV() { return mObj->mUAV; }

private:
	struct Obj 
	{
		Obj();
		~Obj();
		ID3D11Buffer* mArgBuffer;
		ID3D11ShaderResourceView* mSRV;
		ID3D11UnorderedAccessView* mUAV;
	};

	std::shared_ptr<Obj> mObj;
	DxDevice* mDevice;
};

} }