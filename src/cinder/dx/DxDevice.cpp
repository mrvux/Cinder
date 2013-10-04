#include "cinder/dx/DxDevice.h"

using namespace std;

namespace cinder { namespace dx {

DxDevice::Obj::Obj()
{
	mDevice = NULL;
	mContext = NULL;
	mAdapter = NULL;
	mFactory = NULL;
}

DxDevice::Obj::~Obj()
{
	if (mDevice) { mDevice->Release(); }
	if (mContext) { mContext->Release(); }
	if (mAdapter) { mAdapter->Release(); }
	if (mFactory) { mFactory->Release(); }
}

DxDevice::DxDevice()
	: mObj(shared_ptr<Obj>( new Obj() ) )
{
	UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	#ifdef _DEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	Initialize(flags);
}

DxDevice::DxDevice(UINT flags)
	: mObj(shared_ptr<Obj>( new Obj() ) )
{
	Initialize(flags);
}

DxDevice::~DxDevice()
{

}

void DxDevice::Initialize(UINT flags)
{


	D3D_FEATURE_LEVEL featureLevels[] =
    {
	#if (USE_D3D11_1)
		// This requires Windows 8.
		D3D_FEATURE_LEVEL_11_1,
	#endif
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
    };
	mFeatureLevel = D3D_FEATURE_LEVEL_11_1;

	ID3D11Device* device;
	ID3D11DeviceContext* context;

	HRESULT hr = D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_HARDWARE ,NULL,flags, featureLevels,ARRAYSIZE(featureLevels),D3D11_SDK_VERSION,&device,&mFeatureLevel,&context);

	if (FAILED(hr))
	{
		DxException exc("Failed to create Device");
		throw exc;
	}

	#if USE_D3D11_1
	device->QueryInterface(__uuidof(ID3D11Device1), (void**)&mObj->mDevice);
	context->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)&mObj->mContext);
	#else
	mObj->mDevice = device;
	mObj->mContext = context;
	#endif

	mBufferSupport = true;
	
	//TODO: Implement Buffer support flag
	if (!IsFeatureLevel11())
	{
		/*Here flag is only reported properly on win8, on win7 it returns true,
		only option is to create a small buffer instead */
		mBufferSupport = false;
	}


	//Get adapter and factory
	IDXGIDevice1* dxgidevice;
	mObj->mDevice->QueryInterface(__uuidof(IDXGIDevice1),(void**)(&dxgidevice));

	IDXGIAdapter* adapter;
	dxgidevice->GetAdapter(&adapter);

	mObj->mAdapter = (IDXGIAdapter1*)adapter;
	mObj->mAdapter->GetParent(__uuidof(IDXGIFactory1),(void**)(&mObj->mFactory));
}

} }