#pragma once

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

class BlendStates
{
public:
	BlendStates(DxDevice* device);

	inline ID3D11BlendState* NoBlend() { return mNoBlend; }
	inline ID3D11BlendState* Additive() { return mAdditiveBlend; }
	inline ID3D11BlendState* Multiply() { return mMultiply; }
	inline ID3D11BlendState* AlphaBlend() { return mAlphaBlend; }
	inline ID3D11BlendState* AlphaAdd() { return mAlphaAdd; }

	inline void SetDisabled() { mDevice->GetContext()->OMSetBlendState(mNoBlend,0,0); }
	inline void SetAlphaBlend() { mDevice->GetContext()->OMSetBlendState(mAlphaBlend,0,0); }
	inline void SetAlphaAdd() { mDevice->GetContext()->OMSetBlendState(mAlphaAdd,0,0); }
	inline void SetAdditive() { mDevice->GetContext()->OMSetBlendState(mAdditiveBlend,0,0); }
	inline void SetMultiply() { mDevice->GetContext()->OMSetBlendState(mMultiply,0,0); }
private:
	DxDevice* mDevice;
	void CreateNoBlend();
	void CreateAdditive();
	void CreateMultiply();
	void CreateAlphaBlend();
	void CreateAlphaAdd();

	ID3D11BlendState* mNoBlend;
	ID3D11BlendState* mAdditiveBlend;
	ID3D11BlendState* mMultiply;
	ID3D11BlendState* mAlphaBlend;
	ID3D11BlendState* mAlphaAdd;

};

} }