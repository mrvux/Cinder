#include "cinder/dx/resources/Effect.h"



namespace cinder { namespace dx {



Effect::Effect(DxDevice* device, cinder::fs::path filepath)
{
	mDevice = device;

	ID3DBlob* pShader = NULL;
	ID3DBlob* pErrors = NULL;

	UINT flags= D3DCOMPILE_OPTIMIZATION_LEVEL1 | D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR;
	D3DCompileFromFile((LPCWSTR)filepath.string().c_str(),NULL,NULL,NULL,"fx_5_0",flags,0,&pShader,&pErrors);

	D3DX11CreateEffectFromMemory(pShader->GetBufferPointer(),pShader->GetBufferSize(),flags,mDevice->GetDevice(),&mEffect);

	this->SelectTechnique(0);
	this->SelectPass(0);
}

Effect::Effect(DxDevice* device, ci::DataSourceRef datasource)
{
	mDevice = device;

	ID3DBlob* pShader = NULL;
	ID3DBlob* pErrors = NULL;

	UINT flags= D3DCOMPILE_OPTIMIZATION_LEVEL1 | D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR;
	HRESULT hr = D3DCompile(datasource->getBuffer().getData(),datasource->getBuffer().getDataSize(),NULL,NULL,NULL,NULL,"fx_5_0",flags,0,&pShader,&pErrors);
	
	D3DX11CreateEffectFromMemory(pShader->GetBufferPointer(),pShader->GetBufferSize(),flags,mDevice->GetDevice(),&mEffect);

	this->SelectTechnique(0);
	this->SelectPass(0);
}


Effect::~Effect(void)
{
	if (mEffect) { mEffect->Release(); }
}

void Effect::SelectTechnique(int index)
{
	mCurrentTechnique = this->mEffect->GetTechniqueByIndex(index);
	this->SelectPass(0);
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