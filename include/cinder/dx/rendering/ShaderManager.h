#pragma once

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

class ShaderManager
{
public:
	ShaderManager(DxDevice* device) { mDevice = device; }
private:
	DxDevice* mDevice;

};

}}