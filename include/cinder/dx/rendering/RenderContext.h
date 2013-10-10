#pragma once

#include "cinder/dx/DxDevice.h"

#include "cinder/dx/states/BlendStates.h"
#include "cinder/dx/states/RasterizerStates.h"
#include "cinder/dx/states/DepthStencilStates.h"

#include "cinder/dx/rendering/RenderTargetStack.h"
#include "cinder/dx/rendering/PrimitiveManager.h"
#include "cinder/dx/rendering/ResourcePool.h"
#include "cinder/dx/rendering/ShaderManager.h"

#include "cinder/dx/resources/SwapChain.h"
#include "cinder/dx/resources/DepthStencil.h"



#if USE_D3D11_1
#include "cinder/dx/states/BlendStatesLogical.h"
#endif

namespace cinder { namespace dx {

class RenderContext
{
public:
	RenderContext(DxDevice* device);

	inline DxDevice* GetDevice() { return mDevice; }
	inline BlendStates* GetBlendStates() { return mBlendStates; }
	inline RasterizerStates* GetRasterizerStates() { return mRasterizerStates; }
	inline DepthStencilStates* GetDepthStencilStates() { return mDepthStencilStates; }
	#if USE_D3D11_1
	inline BlendStatesLogical* GetLogicalBlendStates() { return mLogicalBlendStates; }
	#endif

	inline RenderTargetStack* GetRenderTargetStack() { return mTargetStack; }
	inline GeometricPrimitives* Geometry() { return mGeom; }
	inline ResourcePool* GetResourcePool() { return mResourcePool; }
	inline ShaderManager* GetShaderManager() { return mShaderManager; }

	void SetPrimaryBuffer(SwapChain* swapchain,DepthStencil* depth);

	inline void CleanShaderStages();

	void CleanUpSRV();
	void CleanUpCS();
private:
	DxDevice* mDevice;
	BlendStates* mBlendStates;
	RasterizerStates* mRasterizerStates;
	DepthStencilStates* mDepthStencilStates;
	#if USE_D3D11_1
	BlendStatesLogical* mLogicalBlendStates;
	#endif

	RenderTargetStack* mTargetStack;
	GeometricPrimitives* mGeom;
	ResourcePool* mResourcePool;
	ShaderManager* mShaderManager;

	ID3D11ShaderResourceView* mNullSRVs[128];
	
};

} }
