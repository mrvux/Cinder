#include "cinder/dx/BlendStates.h"


namespace cinder { namespace dx {

BlendStates::BlendStates(DxDevice* device)
{
	mDevice = device;
	this->CreateAdditive();
	this->CreateAlphaBlend();
	this->CreateMultiply();
	this->CreateNoBlend();
	this->CreateAlphaAdd();
}

void BlendStates::CreateNoBlend()
{
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable=false;
	desc.IndependentBlendEnable = false;
	
	for (int i =0; i < 8 ; i++)
	{
		desc.RenderTarget[i].BlendEnable = false;
		desc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[i].DestBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		desc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
	}

	mDevice->GetDevice()->CreateBlendState(&desc,&mNoBlend);
}

void BlendStates::CreateAdditive()
{
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable=false;
	desc.IndependentBlendEnable = false;
	
	for (int i =0; i < 8 ; i++)
	{
		desc.RenderTarget[i].BlendEnable = true;
		desc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[i].DestBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		desc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
	}

	mDevice->GetDevice()->CreateBlendState(&desc,&mAdditiveBlend);
}

void BlendStates::CreateMultiply()
{
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable=false;
	desc.IndependentBlendEnable = false;
	
	for (int i =0; i < 8 ; i++)
	{
		desc.RenderTarget[i].BlendEnable = true;
		desc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_MIN;
		desc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		desc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
	}

	mDevice->GetDevice()->CreateBlendState(&desc,&mMultiply);
}

void BlendStates::CreateAlphaBlend()
{
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable=false;
	desc.IndependentBlendEnable = false;
	
	for (int i =0; i < 8 ; i++)
	{
		desc.RenderTarget[i].BlendEnable = true;
		desc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		desc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
	}

	mDevice->GetDevice()->CreateBlendState(&desc,&mAlphaBlend);
}

void BlendStates::CreateAlphaAdd()
{
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable=false;
	desc.IndependentBlendEnable = false;
	
	for (int i =0; i < 8 ; i++)
	{
		desc.RenderTarget[i].BlendEnable = true;
		desc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[i].DestBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		desc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ZERO;
	}

	mDevice->GetDevice()->CreateBlendState(&desc,&mAlphaBlend);
}


}}