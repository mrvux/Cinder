#pragma once

#include "cinder/dx/dx11.h"

namespace cinder { namespace dx {

DXGI_FORMAT GetDepthResourceFormat(DXGI_FORMAT depthformat);
DXGI_FORMAT GetDepthSRVFormat(DXGI_FORMAT depthformat);

} }