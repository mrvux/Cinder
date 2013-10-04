#pragma once

#include "DxDevice.h"

namespace cinder { namespace dx {

class RasterizerStates
{
public:
	RasterizerStates(DxDevice* device);
	inline ID3D11RasterizerState* WireFrame() { return mWireFrame; }
	inline ID3D11RasterizerState* BackCull() { return mBackCull; }
	inline ID3D11RasterizerState* FrontCull() { return mFrontCull; }
	inline ID3D11RasterizerState* NoCull() { return mNoCull; }
private:
	DxDevice* mDevice;

	void CreateWireFrame();
	void CreateBackCull();
	void CreateFrontCull();
	void CreateNoCull();

	ID3D11RasterizerState* mWireFrame;
	ID3D11RasterizerState* mBackCull;
	ID3D11RasterizerState* mFrontCull;
	ID3D11RasterizerState* mNoCull;
};

}}