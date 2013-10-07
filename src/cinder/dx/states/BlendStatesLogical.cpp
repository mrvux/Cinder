#include "cinder/dx/states/BlendStatesLogical.h"


namespace cinder { namespace dx {

BlendStatesLogical::BlendStatesLogical(DxDevice* device)
{
	mDevice = device;
	//D3D11_BLEND_DESC1 bd;
	//bd.RenderTarget[0].
	this->CreateXor();
	/*this->CreateAlphaBlend();
	this->CreateMultiply();
	this->CreateNoBlend();
	this->CreateAlphaAdd();*/
}

void BlendStatesLogical::CreateXor()
{
	D3D11_BLEND_DESC1 desc;
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
		desc.RenderTarget[i].LogicOpEnable = true;
		desc.RenderTarget[i].LogicOp = D3D11_LOGIC_OP::D3D11_LOGIC_OP_XOR;
	}

	mDevice->GetDevice()->CreateBlendState1(&desc,&mXor);
}

}}