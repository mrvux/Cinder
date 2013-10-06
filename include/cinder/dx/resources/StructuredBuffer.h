#pragma once

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

typedef enum eStructuredBufferMode
{	
	None	= 0,
	Append = D3D11_BUFFER_UAV_FLAG_APPEND,
	Counter = D3D11_BUFFER_UAV_FLAG_COUNTER
} eStructuredBufferMode;

class StructuredBuffer;
typedef std::shared_ptr<StructuredBuffer> StructuredBufferRef;

class StructuredBuffer
{
public:
	StructuredBuffer(DxDevice* device,int numelements,int stride, eStructuredBufferMode mode = eStructuredBufferMode::None);
	StructuredBuffer(DxDevice* device,int numelements,int stride, void* initial = NULL);

	void* LockForWrite();
	void* LockForRead();
	void Unlock();

	void WriteData(void* data, UINT length);

	template <typename T> 
	void WriteElements(T* elements, UINT elementcount)
	{
		void* ptr = this->LockForWrite();

		if (ptr)
		{
			memcpy(ptr,elements, elementcount*sizeof(T));
			this->Unlock();
		}
	}

	inline ID3D11Buffer* GetBuffer() { return mObj->mBuffer; }
	inline ID3D11UnorderedAccessView* GetUAV() { return mObj->mUAV; }
	inline ID3D11ShaderResourceView* GetSRV() { return mObj->mSRV; }

	inline int GetElementCount() const { return this->mElementCount; }
	inline int GetStride() const { return this->mStride; }
private:
	DxDevice* mDevice;

	struct Obj 
	{
		Obj();
		~Obj();
		ID3D11Buffer* mBuffer;
		ID3D11ShaderResourceView* mSRV;
		ID3D11UnorderedAccessView* mUAV;
	};

	std::shared_ptr<Obj> mObj;

	UINT mStride;
	UINT mElementCount;
};

}}