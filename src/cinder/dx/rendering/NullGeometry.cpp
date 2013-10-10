#include "cinder/dx/rendering/NullGeometry.h"

namespace cinder { namespace dx {

NullGeometry::NullGeometry(DxDevice* device,D3D11_PRIMITIVE_TOPOLOGY topology, UINT vertexcount)
{
	mDevice = device;
	mTopology = topology;
	mVertexCount = vertexcount;
}

NullGeometry::~NullGeometry(void)
{

}

void NullGeometry::Draw()
{
	mDevice->GetContext()->Draw(mVertexCount,0);
}

void NullGeometry::DrawInstanced(UINT instancecount)
{
	mDevice->GetContext()->DrawInstanced(mVertexCount,instancecount,0,0);
}

void NullGeometry::Bind()
{
	//Set IA stage to have no buffer (yes this is perfectly valid!)
	mDevice->GetContext()->IASetPrimitiveTopology(mTopology);
	mDevice->GetContext()->IASetIndexBuffer(NULL,DXGI_FORMAT_UNKNOWN,0);
	mDevice->GetContext()->IASetVertexBuffers(0,0,NULL,NULL,NULL);
	mDevice->GetContext()->IASetInputLayout(NULL);
}

}}
