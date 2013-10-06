#pragma once

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

class IndexBuffer
{
public:
	void Bind();
	inline int GetIndicesCount() { return mIndicesCount; }

	static IndexBuffer* CreateImmutable(DxDevice* device, void* data,int indicescount, bool largeformat = true);
	static IndexBuffer* CreateDynamic(DxDevice* device, void* data,int indicescount, bool largeformat = true);
private:
	IndexBuffer(DxDevice* device,const D3D11_BUFFER_DESC* desc,void* data, int indicescount, bool largeformat = true);

	struct Obj 
	{
		Obj();
		~Obj();
		ID3D11Buffer* mBuffer;
	};

	DxDevice* mDevice;

	std::shared_ptr<Obj> mObj;
	int mIndicesCount;
	DXGI_FORMAT mFormat;
};

}}