#include "cinder/dx/rendering/IndexedGeometry.h"

namespace cinder { namespace dx {

IndexedGeometry::IndexedGeometry(DxDevice* device)
{
	mDevice = device;
	mIndexBuffer = 0;
	mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

IndexedGeometry::~IndexedGeometry(void)
{
	if (mIndexBuffer) { delete mIndexBuffer; }

	for (UINT i = 0; i < mVertexBuffers.size();i++)
	{
		delete mVertexBuffers.at(i);
	}
}

void IndexedGeometry::AddVertexBuffer(VertexBuffer* vbo)
{
	for (UINT i = 0; i < vbo->GetInputElements().size(); i++)
	{
		D3D11_INPUT_ELEMENT_DESC d = vbo->GetInputElements().at(i);
		d.InputSlot = this->mVertexBuffers.size();
		mVertexElements.push_back(d);
	}

	this->mVertexBuffers.push_back(vbo);
}

void IndexedGeometry::SetIndexBuffer(IndexBuffer* ibo)
{
	this->mIndexBuffer = ibo;
}

void IndexedGeometry::Draw()
{
	mDevice->GetContext()->DrawIndexed(this->mIndexBuffer->GetIndicesCount(),0,0);
}

void IndexedGeometry::DrawInstanced(UINT instancecount)
{
	mDevice->GetContext()->DrawIndexedInstanced(mIndexBuffer->GetIndicesCount(),instancecount,0,0,0);
}

bool IndexedGeometry::ValidateLayout(ID3DX11EffectPass* pass,ID3D11InputLayout** pLayout)
{
	D3DX11_PASS_DESC pdesc;

	pass->GetDesc(&pdesc);
	pdesc.pIAInputSignature;

	HRESULT result = mDevice->GetDevice()->CreateInputLayout(&mVertexElements.at(0),
		mVertexElements.size(),pdesc.pIAInputSignature,pdesc.IAInputSignatureSize,pLayout);

	return result == S_OK;
}

void IndexedGeometry::Bind(ID3D11InputLayout* layout)
{
	mDevice->GetContext()->IASetPrimitiveTopology(mTopology);
	mIndexBuffer->Bind();

	if (mVertexBuffers.size() > 0)
	{
		ID3D11Buffer* buffer[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
		UINT vertexsize[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
		UINT offsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
		
		for (UINT i = 0; i < this->mVertexBuffers.size();i++)
		{
			buffer[i] = mVertexBuffers.at(i)->GetBuffer();
			vertexsize[i] = mVertexBuffers.at(i)->GetVertexSize();
			offsets[i] = 0;
		}
		
		
		mDevice->GetContext()->IASetVertexBuffers(0,mVertexBuffers.size(),buffer,vertexsize,offsets);
	}
	else
	{
		mDevice->GetContext()->IASetVertexBuffers(0,0,NULL,NULL,NULL);
	}

	mDevice->GetContext()->IASetInputLayout(layout);
}

}}
