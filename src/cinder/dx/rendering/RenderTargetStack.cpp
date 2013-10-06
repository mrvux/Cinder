#include "cinder/dx/rendering/RenderTargetStack.h"

namespace cinder { namespace dx {

RenderBuffer::RenderBuffer(RenderTargetBase* target, DepthStencilBase* depth, bool readonlydepth)
{
	Init(target,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,depth,readonlydepth);
}

RenderBuffer::RenderBuffer(RenderTargetBase* target1,RenderTargetBase* target2, DepthStencilBase* depth, bool readonlydepth)
{
	Init(target1,target2,NULL,NULL,NULL,NULL,NULL,NULL,2,depth,readonlydepth);
}

RenderBuffer::RenderBuffer(RenderTargetBase* target1,RenderTargetBase* target2, 
						   RenderTargetBase* target3,DepthStencilBase* depth, bool readonlydepth)
{
	Init(target1,target2,target3,NULL,NULL,NULL,NULL,NULL,3,depth,readonlydepth);
}

RenderBuffer::RenderBuffer(RenderTargetBase* target1,RenderTargetBase* target2, RenderTargetBase* target3,RenderTargetBase* target4, DepthStencilBase* depth, bool readonlydepth)
{
	Init(target1,target2,target3,target4,NULL,NULL,NULL,NULL,4,depth,readonlydepth);
}

void RenderBuffer::Init(RenderTargetBase* target1,RenderTargetBase* target2,RenderTargetBase* target3,RenderTargetBase* target4, 
				RenderTargetBase* target5,RenderTargetBase* target6,RenderTargetBase* target7,RenderTargetBase* target8, 
				UINT targetcount,DepthStencilBase* depth, bool readonlydepth)
{
	mRTVs[0] = target1 ? target1->GetRTV() : NULL; 
	mRTVs[1] = target2 ? target2->GetRTV() : NULL; 
	mRTVs[2] = target3 ? target3->GetRTV() : NULL; 
	mRTVs[3] = target4 ? target4->GetRTV() : NULL; 

	mRTVs[4] = target5 ? target5->GetRTV() : NULL; 
	mRTVs[5] = target6 ? target6->GetRTV() : NULL; 
	mRTVs[6] = target7 ? target7->GetRTV() : NULL; 
	mRTVs[7] = target8 ? target8->GetRTV() : NULL; 

	// TODO : Replace later as we can bind depth only / buffer only
	mWidth = target1->GetWidth();
	mHeight = target1->GetHeight();

	mRTVCount = targetcount;
	mDepth = NULL;
	if (depth) { mDepth = readonlydepth ? depth->GetReadOnlyDSV() : depth->GetDSV(); }
}

void RenderBuffer::Apply(DxDevice* mDevice)
{
	mDevice->GetContext()->OMSetRenderTargets(mRTVCount,mRTVs,mDepth);

	D3D11_VIEWPORT vp;
	vp.Width = mWidth;
	vp.Height = mHeight;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	mDevice->GetContext()->RSSetViewports(1,&vp);
}

RenderTargetStack::RenderTargetStack(DxDevice* device)
{
	mDevice = device;
}

void RenderTargetStack::Push(RenderBuffer* renderbuffer)
{
	mStack.push(renderbuffer);
	ApplyTop();
}

void RenderTargetStack::Pop()
{
	mStack.pop();
	ApplyTop();
}

void RenderTargetStack::ApplyTop()
{
	mStack.top()->Apply(mDevice);
}


} }