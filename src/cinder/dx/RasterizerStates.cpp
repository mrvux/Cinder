#include "cinder/dx/RasterizerStates.h"

namespace cinder { namespace dx {

	RasterizerStates::RasterizerStates(DxDevice* device)
{
	mDevice = device;

	this->CreateWireFrame();
	this->CreateBackCull();
	this->CreateFrontCull();
	this->CreateNoCull();
}

void RasterizerStates::CreateWireFrame()
{
	D3D11_RASTERIZER_DESC desc;
	desc.AntialiasedLineEnable = false;
	desc.CullMode = D3D11_CULL_NONE;
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0.0f;
	desc.DepthClipEnable = false;
	desc.FillMode = D3D11_FILL_WIREFRAME;
	desc.FrontCounterClockwise = false;
	desc.MultisampleEnable = false;
	desc.ScissorEnable = false;
	desc.SlopeScaledDepthBias = 0.0f;

	mDevice->GetDevice()->CreateRasterizerState(&desc,&mWireFrame);

}

void RasterizerStates::CreateBackCull()
{
	D3D11_RASTERIZER_DESC desc;
	desc.AntialiasedLineEnable = false;
	desc.CullMode = D3D11_CULL_BACK;
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0.0f;
	desc.DepthClipEnable = false;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.FrontCounterClockwise = false;
	desc.MultisampleEnable = false;
	desc.ScissorEnable = false;
	desc.SlopeScaledDepthBias = 0.0f;

	mDevice->GetDevice()->CreateRasterizerState(&desc,&mBackCull);

}

void RasterizerStates::CreateFrontCull()
{
	D3D11_RASTERIZER_DESC desc;
	desc.AntialiasedLineEnable = false;
	desc.CullMode = D3D11_CULL_FRONT;
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0.0f;
	desc.DepthClipEnable = false;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.FrontCounterClockwise = false;
	desc.MultisampleEnable = false;
	desc.ScissorEnable = false;
	desc.SlopeScaledDepthBias = 0.0f;

	mDevice->GetDevice()->CreateRasterizerState(&desc,&mFrontCull);
}

void RasterizerStates::CreateNoCull()
{
	D3D11_RASTERIZER_DESC desc;
	desc.AntialiasedLineEnable = false;
	desc.CullMode = D3D11_CULL_NONE;
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0.0f;
	desc.DepthClipEnable = false;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.FrontCounterClockwise = false;
	desc.MultisampleEnable = false;
	desc.ScissorEnable = false;
	desc.SlopeScaledDepthBias = 0.0f;

	mDevice->GetDevice()->CreateRasterizerState(&desc,&mNoCull);
}


}}