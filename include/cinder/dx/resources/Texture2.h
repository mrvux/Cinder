#pragma once


#include "cinder/FileSystem.h"
#include "cinder/DataSource.h"

#include "cinder/dx/DxDevice.h"

namespace cinder { namespace dx {

typedef std::shared_ptr<class Texture2>	Texture2Ref;

class Texture2
{
	friend class RenderTarget2;
	friend class SwapChain;
public:
	inline ID3D11Texture2D* GetTexture() { return mObj->mTexture; }
	inline ID3D11ShaderResourceView* GetSRV() { return mObj->mSRV; }
	inline D3D11_TEXTURE2D_DESC GetResourceDesc() { return mResourceDesc; }

	void* LockForWrite();
	void* LockForRead();
	void Unlock();

	void WriteData(void* data, UINT length);
protected:
	Texture2(DxDevice* device,ID3D11Texture2D* texture,ID3D11ShaderResourceView* view, bool addref);
	Texture2(DxDevice* device,const D3D11_TEXTURE2D_DESC& description);
	Texture2(DxDevice* device,const D3D11_TEXTURE2D_DESC& resourcedesc,const D3D11_SHADER_RESOURCE_VIEW_DESC& viewdesc);
private:
	struct Obj 
	{
		Obj();
		~Obj();
		ID3D11Texture2D* mTexture;
		ID3D11ShaderResourceView* mSRV;
	};

	DxDevice* mDevice;	
	D3D11_TEXTURE2D_DESC mResourceDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC mViewDesc;
	

	std::shared_ptr<Obj> mObj;
};

}}