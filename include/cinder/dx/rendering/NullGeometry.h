#pragma once

#include "cinder/dx/DxDevice.h"
#include "cinder/dx/resources/VertexBuffer.h"
#include "cinder/dx/resources/IndexBuffer.h"

#include "msw/effects11/d3dx11effect.h"

#include <vector>

namespace cinder { namespace dx {

class NullGeometry
{
public:
	NullGeometry(DxDevice* device,D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, UINT vertexcount = 1);
	~NullGeometry(void);

	void Draw();
	void DrawInstanced(UINT instancecount = 1);

	inline void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { mTopology = topology; }
	inline void SetVertexCount(UINT vertexcount) { mVertexCount = vertexcount; }

	void Bind();
private:
	DxDevice* mDevice;
	D3D11_PRIMITIVE_TOPOLOGY mTopology;
	UINT mVertexCount;

};

}}

