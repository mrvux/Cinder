#include "cinder/dx/DepthStencilStates.h"

namespace cinder { namespace dx {

DepthStencilStates::DepthStencilStates(DxDevice* device)
{
	mDevice = device;
	this->CreateDisabled();
	this->CreateReadLess();
	this->CreateReadWriteLess();
	this->CreateWriteOnly();
	this->CreateReadLessEqual();
	this->CreateReadWriteLessEqual();
}

void DepthStencilStates::CreateDisabled()
{
	D3D11_DEPTH_STENCIL_DESC desc;
	desc.DepthEnable = false;
	desc.StencilEnable = false;
	desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	mDevice->GetDevice()->CreateDepthStencilState(&desc,&mDisabled);
}

void DepthStencilStates::CreateReadLess()
{
	D3D11_DEPTH_STENCIL_DESC desc;
	desc.DepthEnable = true;
	desc.StencilEnable = false;
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	mDevice->GetDevice()->CreateDepthStencilState(&desc,&mReadLess);
}

 void DepthStencilStates::CreateReadWriteLess()
{
	D3D11_DEPTH_STENCIL_DESC desc;
	desc.DepthEnable = true;
	desc.StencilEnable = false;
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	mDevice->GetDevice()->CreateDepthStencilState(&desc,&mReadWriteLess);
}


 void DepthStencilStates::CreateReadLessEqual()
{
	D3D11_DEPTH_STENCIL_DESC desc;
	desc.DepthEnable = true;
	desc.StencilEnable = false;
	desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	mDevice->GetDevice()->CreateDepthStencilState(&desc,&mReadLessEqual);
}

 void DepthStencilStates::CreateReadWriteLessEqual()
{
	D3D11_DEPTH_STENCIL_DESC desc;
	desc.DepthEnable = true;
	desc.StencilEnable = false;
	desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	mDevice->GetDevice()->CreateDepthStencilState(&desc,&mReadWriteLessEqual);
}

 
void DepthStencilStates::CreateWriteOnly()
{
	D3D11_DEPTH_STENCIL_DESC desc;
	desc.DepthEnable = true;
	desc.StencilEnable = false;
	desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	mDevice->GetDevice()->CreateDepthStencilState(&desc,&mWriteOnly);
}

}}