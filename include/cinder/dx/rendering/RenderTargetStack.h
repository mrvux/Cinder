#pragma once

#include "cinder/dx/DxDevice.h"
#include "cinder/dx/resources/RenderTargetBase.h"
#include "cinder/dx/resources/DepthStencilBase.h"

#include <stack>

namespace cinder { namespace dx {

class RenderTargetStack;

class RenderBuffer
{
	friend class RenderTargetStack;
public:
	//Constructors bit ugly but having c# params argument style is quite useful
	RenderBuffer(RenderTargetBase* target, DepthStencilBase* depth = NULL, bool readonlydepth = false);
	RenderBuffer(RenderTargetBase* target1,RenderTargetBase* target2, DepthStencilBase* depth = NULL, bool readonlydepth = false);
	RenderBuffer(RenderTargetBase* target1,RenderTargetBase* target2,RenderTargetBase* target3, DepthStencilBase* depth = NULL, bool readonlydepth = false);
	RenderBuffer(RenderTargetBase* target1,RenderTargetBase* target2,RenderTargetBase* target3,RenderTargetBase* target4, DepthStencilBase* depth = NULL, bool readonlydepth = false);
protected:
	void Init(RenderTargetBase* target1,RenderTargetBase* target2,RenderTargetBase* target3,RenderTargetBase* target4, 
				RenderTargetBase* target5,RenderTargetBase* target6,RenderTargetBase* target7,RenderTargetBase* target8, 
				UINT targetcount,DepthStencilBase* depth = NULL, bool readonlydepth = false);
	void Apply(DxDevice* mDevice);
private:
	ID3D11RenderTargetView* mRTVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	UINT mRTVCount;
	ID3D11DepthStencilView* mDepth;
	UINT mWidth;
	UINT mHeight;
};

class RenderTargetStack
{
public:
	RenderTargetStack(DxDevice* device);

	void Push(RenderBuffer* renderbuffer);
	void Pop();
	void ApplyTop();
private:
	DxDevice* mDevice;
	std::stack<RenderBuffer*> mStack;
};

} }