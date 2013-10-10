#include "cinder/dx/rendering/RenderContext.h"

namespace cinder { namespace dx {

RenderContext::RenderContext(DxDevice* device)
{
	mDevice = device;
	mBlendStates = new BlendStates(device);
	mRasterizerStates = new RasterizerStates(device);
	mDepthStencilStates = new DepthStencilStates(device);
	#if USE_D3D11_1
	mLogicalBlendStates = new BlendStatesLogical(device);
	#endif
	
	mTargetStack = new RenderTargetStack(device);

	mBlendStates->SetDisabled();
	mRasterizerStates->SetWireframe();
	mDepthStencilStates->SetDisabled();

	for (int i = 0; i < 128; i++) { mNullSRVs[i] = NULL; }
}

void RenderContext::SetPrimaryBuffer(SwapChain* swapchain,DepthStencil* depth)
{
	RenderBuffer* b = new RenderBuffer(swapchain->GetRenderTarget(),depth);
	mTargetStack->Push(b);
}

void RenderContext::CleanShaderStages()
{
	mDevice->GetContext()->VSSetShader(NULL,NULL,0);
	mDevice->GetContext()->HSSetShader(NULL,NULL,0);
	mDevice->GetContext()->DSSetShader(NULL,NULL,0);
	mDevice->GetContext()->GSSetShader(NULL,NULL,0);
	mDevice->GetContext()->PSSetShader(NULL,NULL,0);

	mDevice->GetContext()->CSSetShader(NULL,NULL,0);
}

void RenderContext::CleanUpSRV()
{
	mDevice->GetContext()->VSSetShaderResources(0,128,mNullSRVs);
	mDevice->GetContext()->HSSetShaderResources(0,128,mNullSRVs);
	mDevice->GetContext()->DSSetShaderResources(0,128,mNullSRVs);
	mDevice->GetContext()->GSSetShaderResources(0,128,mNullSRVs);
	mDevice->GetContext()->PSSetShaderResources(0,128,mNullSRVs);

	mDevice->GetContext()->CSSetShaderResources(0,128,mNullSRVs);
}

void RenderContext::CleanUpCS()
{
	mDevice->GetContext()->CSSetShaderResources(0,128,mNullSRVs);
}

} }