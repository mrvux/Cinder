#pragma once

#include <string>

#include "cinder/DataSource.h"
#include "cinder/FileSystem.h"
#include "cinder/dx/DxDevice.h"


namespace cinder { namespace dx {

class Effect;
typedef std::shared_ptr<Effect> EffectRef;

class Effect
{
public:
	Effect(DxDevice* device, cinder::fs::path filepath);
	Effect(DxDevice* device, ci::DataSourceRef datasource);
	~Effect(void);

	void SelectTechnique(int index);
	void SelectPass(int index);

	template <typename T> 
	void SetByName(LPCSTR name,T& value)
	{
		mEffect->GetVariableByName(name)->SetRawValue(&value,0,sizeof(T));
	}

	template <typename T> 
	void SetBySemantic(LPCSTR semantic,T& value)
	{
		mEffect->GetVariableBySemantic(semantic)->SetRawValue(&value,0,sizeof(T));
	}

	void SetSRV(LPCSTR name,ID3D11ShaderResourceView* srv)
	{
		mEffect->GetVariableByName(name)->AsShaderResource()->SetResource(srv);
	}

	void SetUAV(LPCSTR name,ID3D11UnorderedAccessView* uav)
	{
		mEffect->GetVariableByName(name)->AsUnorderedAccessView()->SetUnorderedAccessView(uav);
	}

	void Apply();

	inline ID3DX11EffectPass* GetCurrentPass() { return this->mCurrentPass; }
	inline ID3DX11EffectTechnique* GetCurrentTechnique() { return this->mCurrentTechnique; }
private:
	DxDevice* mDevice;

	ID3DX11Effect* mEffect;

	ID3DX11EffectTechnique* mCurrentTechnique;
	ID3DX11EffectPass* mCurrentPass;
};

}}