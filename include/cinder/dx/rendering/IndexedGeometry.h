#pragma once

#include "cinder/dx/DxDevice.h"
#include "cinder/dx/resources/VertexBuffer.h"
#include "cinder/dx/resources/IndexBuffer.h"

#include "msw/effects11/d3dx11effect.h"

#include <vector>

namespace cinder { namespace dx {

class IndexedGeometry
{
public:
	IndexedGeometry(DxDevice* device);
	~IndexedGeometry(void);

	void AddVertexBuffer(VertexBuffer* vbo);
	void SetIndexBuffer(IndexBuffer* ibo);
	void Draw();
	void DrawInstanced(UINT instancecount = 1);

	inline VertexBuffer* GetVertexBuffer(int idx) { return this->mVertexBuffers.at(idx); }

	bool ValidateLayout(ID3DX11EffectPass* pass,ID3D11InputLayout** pLayout);
	void Bind(ID3D11InputLayout* layout);
private:
	IndexBuffer* mIndexBuffer;
	DxDevice* mDevice;

	D3D11_PRIMITIVE_TOPOLOGY mTopology;

	std::vector<VertexBuffer*> mVertexBuffers;
	std::vector<D3D11_INPUT_ELEMENT_DESC> mVertexElements;



};

}}

