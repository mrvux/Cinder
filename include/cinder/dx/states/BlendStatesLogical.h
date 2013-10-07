#pragma once

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

class BlendStatesLogical
{
public:
	BlendStatesLogical(DxDevice* device);

	inline ID3D11BlendState* Xor() { return mXor; }
	/*inline ID3D11BlendState* Additive() { return mAdditiveBlend; }
	inline ID3D11BlendState* Multiply() { return mMultiply; }
	inline ID3D11BlendState* AlphaBlend() { return mAlphaBlend; }
	inline ID3D11BlendState* AlphaAdd() { return mAlphaAdd; }*/

	inline void SetXor() { mDevice->GetContext()->OMSetBlendState(mXor,0,0xffffffff); }

private:
	DxDevice* mDevice;
	void CreateXor();
	/*void CreateAdditive();
	void CreateMultiply();
	void CreateAlphaBlend();
	void CreateAlphaAdd();*/

	ID3D11BlendState1* mXor;
	/*ID3D11BlendState* mAdditiveBlend;
	ID3D11BlendState* mMultiply;
	ID3D11BlendState* mAlphaBlend;
	ID3D11BlendState* mAlphaAdd;*/
};

} }