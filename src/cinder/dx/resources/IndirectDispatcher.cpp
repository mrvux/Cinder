#include "cinder/dx/resources/IndirectDispatcher.h"

#include "cinder/dx/resources/StructuredBuffer.h"

using namespace std;

namespace cinder { namespace dx {

IndirectDispatcher::Obj::Obj()
{
	mArgBuffer = NULL;
	mSRV = NULL;
	mUAV = NULL;
}

IndirectDispatcher::Obj::~Obj()
{
	if (mSRV) { mSRV->Release(); }
	if (mUAV) { mUAV->Release(); }
	if (mArgBuffer) { mArgBuffer->Release(); }
}


IndirectDispatcher::IndirectDispatcher(DxDevice* device, UINT TX, UINT TY, UINT TZ)
	: mObj( shared_ptr<Obj>( new Obj() ) )
{
	mDevice = device;

	//Create Arg buffer and UAV
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
	desc.ByteWidth = sizeof(DispatchArgs);
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS | D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;
	desc.Usage = D3D11_USAGE_DEFAULT;

	DispatchArgs args;
	args.TGX = TX;
	args.TGY = TY;
	args.TGZ = TZ;

	D3D11_SUBRESOURCE_DATA initial;	
	initial.pSysMem = &args;
	initial.SysMemPitch = 0;
	initial.SysMemSlicePitch = 0;

	HRESULT hr = mDevice->GetDevice()->CreateBuffer(&desc,&initial,&mObj->mArgBuffer);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavdesc;
	ZeroMemory(&uavdesc,sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
	uavdesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_BUFFER;
	uavdesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG::D3D11_BUFFER_UAV_FLAG_RAW;
	uavdesc.Buffer.NumElements = sizeof(DispatchArgs) / 4;
	uavdesc.Format = DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS;

	hr = mDevice->GetDevice()->CreateUnorderedAccessView(mObj->mArgBuffer,&uavdesc,&mObj->mUAV);

	//Create simple count buffer and SRV
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.ByteWidth = 16;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
	desc.Usage = D3D11_USAGE_DEFAULT;	

	hr = mDevice->GetDevice()->CreateBuffer(&desc,NULL,&mObj->mCountBuffer);

	//Shader view is created from count buffer
	D3D11_SHADER_RESOURCE_VIEW_DESC srvdesc;
	ZeroMemory(&srvdesc,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvdesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_BUFFEREX;
	srvdesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG::D3D11_BUFFEREX_SRV_FLAG_RAW;
	srvdesc.BufferEx.NumElements = sizeof(DispatchArgs) / 4;
	srvdesc.Format = DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS;
	

	hr = mDevice->GetDevice()->CreateShaderResourceView(mObj->mCountBuffer,&srvdesc,&mObj->mSRV);


}

void IndirectDispatcher::CopyCounter(StructuredBuffer* buffer)
{
	//Here we copy to Counter Buffer, args need to be generated in compute
	mDevice->GetContext()->CopyStructureCount(mObj->mCountBuffer,0,buffer->GetUAV());
}

void IndirectDispatcher::Dispatch()
{
	mDevice->GetContext()->DispatchIndirect(mObj->mArgBuffer,0);
}


} }