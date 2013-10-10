#include "cinder/dx/resources/IndirectIndexDrawer.h"

#include "cinder/dx/resources/StructuredBuffer.h"

using namespace std;

namespace cinder { namespace dx {

IndirectIndexDrawer::Obj::Obj()
{
	mArgBuffer = NULL;
	mSRV = NULL;
	mUAV = NULL;
}

IndirectIndexDrawer::Obj::~Obj()
{
	if (mSRV) { mSRV->Release(); }
	if (mUAV) { mUAV->Release(); }
	if (mArgBuffer) { mArgBuffer->Release(); }
}


IndirectIndexDrawer::IndirectIndexDrawer(DxDevice* device, UINT IndicesCount, UINT InstanceCount, UINT StartIndexLocation,UINT BaseVertexLocation, UINT StartInstanceLocation)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	mDevice = device;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	desc.ByteWidth = sizeof(DrawIndexedInstancedArgs);
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS | D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;
	desc.Usage = D3D11_USAGE_DEFAULT;

	DrawIndexedInstancedArgs args;
	args.InstanceCount = InstanceCount;
	args.StartInstanceLocation = StartInstanceLocation;
	args.BaseVertexLocation = BaseVertexLocation;
	args.IndicesCount = IndicesCount;
	args.StartIndexLocation = StartIndexLocation;

	D3D11_SUBRESOURCE_DATA initial;	
	initial.pSysMem = &args;
	initial.SysMemPitch = 0;
	initial.SysMemSlicePitch = 0;

	HRESULT hr = mDevice->GetDevice()->CreateBuffer(&desc,&initial,&mObj->mArgBuffer);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvdesc;
	ZeroMemory(&srvdesc,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvdesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_BUFFEREX;
	srvdesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG::D3D11_BUFFEREX_SRV_FLAG_RAW;
	srvdesc.BufferEx.NumElements = sizeof(DrawIndexedInstancedArgs) / 4;
	srvdesc.Format = DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS;
	

	hr = mDevice->GetDevice()->CreateShaderResourceView(mObj->mArgBuffer,&srvdesc,&mObj->mSRV);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavdesc;
	ZeroMemory(&uavdesc,sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
	uavdesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_BUFFER;
	uavdesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG::D3D11_BUFFER_UAV_FLAG_RAW;
	uavdesc.Buffer.NumElements = sizeof(DrawIndexedInstancedArgs) / 4;
	uavdesc.Format = DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS;

	hr = mDevice->GetDevice()->CreateUnorderedAccessView(mObj->mArgBuffer,&uavdesc,&mObj->mUAV);	
}

void IndirectIndexDrawer::CopyIndexCount(StructuredBuffer* buffer)
{
	mDevice->GetContext()->CopyStructureCount(mObj->mArgBuffer,0,buffer->GetUAV());
}

void IndirectIndexDrawer::CopyInstanceCount(StructuredBuffer* buffer)
{
	mDevice->GetContext()->CopyStructureCount(mObj->mArgBuffer,4,buffer->GetUAV());
}

void IndirectIndexDrawer::Draw()
{
	mDevice->GetContext()->DrawIndexedInstancedIndirect(mObj->mArgBuffer,0);
}

} }