#pragma once

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

class ByteAddressBuffer;
typedef std::shared_ptr<ByteAddressBuffer> ByteAddressBufferRef;

class ByteAddressBuffer
{
public:
	ByteAddressBuffer(DxDevice* device,int size);
	ByteAddressBuffer(DxDevice* device,int size, void* initial = NULL);

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

	inline int GetSize() const { return this->mSize; }
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

	UINT mSize;
};

}}