#pragma once

#include "DxDevice.h"

namespace cinder { namespace dx {

class DepthStencilStates
{
public:
	DepthStencilStates(DxDevice* device);
	inline ID3D11DepthStencilState* Disabled() { return mDisabled; }
	inline ID3D11DepthStencilState* ReadLess() { return mReadLess; }
	inline ID3D11DepthStencilState* ReadWriteLess() { return mReadWriteLess; }
	inline ID3D11DepthStencilState* ReadLessEqual() { return mReadLessEqual; }
	inline ID3D11DepthStencilState* ReadWriteLessEqual() { return mReadWriteLessEqual; }
	inline ID3D11DepthStencilState* WriteOnly() { return mWriteOnly; }
private:
	DxDevice* mDevice;

	void CreateDisabled();
	void CreateReadLess();
	void CreateReadWriteLess();
	void CreateReadLessEqual();
	void CreateReadWriteLessEqual();
	void CreateWriteOnly();

	ID3D11DepthStencilState* mDisabled;
	ID3D11DepthStencilState* mReadLess;
	ID3D11DepthStencilState* mReadWriteLess;
	ID3D11DepthStencilState* mReadLessEqual;
	ID3D11DepthStencilState* mReadWriteLessEqual;
	ID3D11DepthStencilState* mWriteOnly;
};

}}