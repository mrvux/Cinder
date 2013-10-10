#include "cinder/dx/resources/Effect.h"

#include "cinder/dx/resources/Texture2.h"

namespace cinder { namespace dx {

Effect::Effect(DxDevice* device, void* bytecode, UINT length)
{
	mDevice = device;

	D3DX11CreateEffectFromMemory(bytecode,length,0,mDevice->GetDevice(),&mEffect);

	this->SelectTechnique(0);
	this->SelectPass(0);
}

Effect* Effect::CreateCompiled(DxDevice* device, void* bytecode, UINT length)
{
	return new Effect(device,bytecode,length);
}

Effect* Effect::CreateCompiled(DxDevice* device, ci::DataSourceRef datasource)
{
	return new Effect(device,datasource->getBuffer().getData(),datasource->getBuffer().getDataSize());
}

Effect* Effect::Compile(DxDevice* device, ci::DataSourceRef datasource)
{
	ID3DBlob* pShader = NULL;
	ID3DBlob* pErrors = NULL;

	UINT flags= D3DCOMPILE_OPTIMIZATION_LEVEL1 | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
	HRESULT hr = D3DCompile(datasource->getBuffer().getData(),datasource->getBuffer().getDataSize(),NULL,NULL,NULL,NULL,"fx_5_0",flags,0,&pShader,&pErrors);

	return new Effect(device,pShader->GetBufferPointer(),pShader->GetBufferSize());
}

void Effect::SetByName(LPCSTR name, Texture2* texture)
{
	mEffect->GetVariableByName(name)->AsShaderResource()->SetResource(texture->GetSRV());
}

void Effect::SetByName(LPCSTR name,ID3D11ShaderResourceView* srv)
{
	mEffect->GetVariableByName(name)->AsShaderResource()->SetResource(srv);
}

void Effect::SetByName(LPCSTR name,ID3D11UnorderedAccessView* uav)
{
	mEffect->GetVariableByName(name)->AsUnorderedAccessView()->SetUnorderedAccessView(uav);
}


void Effect::SetBySemantic(LPCSTR semantic, Texture2* texture)
{
	mEffect->GetVariableBySemantic(semantic)->AsShaderResource()->SetResource(texture->GetSRV());
}

void Effect::SetBySemantic(LPCSTR semantic,ID3D11ShaderResourceView* srv)
{
	mEffect->GetVariableBySemantic(semantic)->AsShaderResource()->SetResource(srv);
}

void Effect::SetBySemantic(LPCSTR semantic,ID3D11UnorderedAccessView* uav)
{
	mEffect->GetVariableBySemantic(semantic)->AsUnorderedAccessView()->SetUnorderedAccessView(uav);
}


Effect::~Effect(void)
{
	if (mEffect) { mEffect->Release(); }
}

void Effect::SelectTechnique(LPCSTR name, UINT passindex)
{
	mCurrentTechnique = this->mEffect->GetTechniqueByName(name);
	this->SelectPass(passindex);
}

void Effect::SelectTechnique(int index, UINT passindex)
{
	mCurrentTechnique = this->mEffect->GetTechniqueByIndex(index);
	this->SelectPass(passindex);
}

void Effect::SelectPass(int index)
{
	mCurrentPass = mCurrentTechnique->GetPassByIndex(index);
}

void Effect::Apply()
{
	mCurrentPass->Apply(0,mDevice->GetContext());
}

}}