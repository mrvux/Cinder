#pragma once

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

struct DrawInstancedArgs
{
	UINT VertexCount;
    UINT InstanceCount;
    UINT StartVertexLocation;
    UINT StartInstanceLocation;
};

class StructuredBuffer;

class IndirectDrawer
{
public:
	IndirectDrawer(DxDevice* device, UINT VertexCount = 1, UINT InstanceCount = 1, UINT StartVertexLocation = 0, UINT StartInstanceLocation = 0);

	void Draw();
	void CopyVertexCount(StructuredBuffer* buffer);
	void CopyInstanceCount(StructuredBuffer* buffer);

	//For debug purposes
	DrawInstancedArgs RetrieveArgs();

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
		ID3D11Buffer* mStaging;
	};

	std::shared_ptr<Obj> mObj;
	DxDevice* mDevice;
};

} }