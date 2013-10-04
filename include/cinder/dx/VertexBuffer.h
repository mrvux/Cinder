#pragma once

#include "DxDevice.h"
#include <vector>

namespace cinder { namespace dx {

class VertexBuffer
{
public:
	void Bind(ID3D11InputLayout* layout, int slot);

	inline const std::vector<D3D11_INPUT_ELEMENT_DESC>& GetInputElements() { return mElements; }
	inline int GetVertexCount() { return mVertexCount; }
	inline int GetVertexSize() { return this->mVertexSize; }
	inline ID3D11Buffer* GetBuffer() { return mObj->mBuffer; }

	static VertexBuffer* CreateImmutable(DxDevice* device,void* data, int verticescount,int stride, std::vector<D3D11_INPUT_ELEMENT_DESC> elements);
	static VertexBuffer* CreateDynamic(DxDevice* device,void* data, int verticescount,int stride, std::vector<D3D11_INPUT_ELEMENT_DESC> elements);
private:
	VertexBuffer(DxDevice* device,const D3D11_BUFFER_DESC* desc,void* data, int verticescount,int stride, std::vector<D3D11_INPUT_ELEMENT_DESC> elements);

	struct Obj 
	{
		Obj();
		~Obj();
		ID3D11Buffer* mBuffer;
	};

	DxDevice* mDevice;
	std::vector<D3D11_INPUT_ELEMENT_DESC> mElements;
	UINT mVertexCount;
	UINT mVertexSize;

	std::shared_ptr<Obj> mObj;
};

}}