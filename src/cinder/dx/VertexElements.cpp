#include "cinder/dx/VertexElements.h"

namespace cinder { namespace dx {

D3D11_INPUT_ELEMENT_DESC VertexElements::Position2(int slot)
{
	D3D11_INPUT_ELEMENT_DESC elem;
	elem.AlignedByteOffset = 0;
	elem.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
	elem.InputSlot = slot;
	elem.InstanceDataStepRate = 0;
	elem.SemanticIndex = 0;
	elem.SemanticName = "POSITION";
	elem.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	return elem;
}

D3D11_INPUT_ELEMENT_DESC VertexElements::Position3(int slot)
{
	D3D11_INPUT_ELEMENT_DESC elem;
	elem.AlignedByteOffset = 0;
	elem.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
	elem.InputSlot = slot;
	elem.InstanceDataStepRate = 0;
	elem.SemanticIndex = 0;
	elem.SemanticName = "POSITION";
	elem.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	return elem;
}

D3D11_INPUT_ELEMENT_DESC VertexElements::Position4(int slot)
{
	D3D11_INPUT_ELEMENT_DESC elem;
	elem.AlignedByteOffset = 0;
	elem.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
	elem.InputSlot = slot;
	elem.InstanceDataStepRate = 0;
	elem.SemanticIndex = 0;
	elem.SemanticName = "POSITION";
	elem.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	return elem;
}

D3D11_INPUT_ELEMENT_DESC VertexElements::Color3(int slot)
{
	D3D11_INPUT_ELEMENT_DESC elem;
	elem.AlignedByteOffset = 0;
	elem.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
	elem.InputSlot = slot;
	elem.InstanceDataStepRate = 0;
	elem.SemanticIndex = 0;
	elem.SemanticName = "COLOR";
	elem.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	return elem;
}

D3D11_INPUT_ELEMENT_DESC VertexElements::Color4(int slot)
{
	D3D11_INPUT_ELEMENT_DESC elem;
	elem.AlignedByteOffset = 0;
	elem.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
	elem.InputSlot = slot;
	elem.InstanceDataStepRate = 0;
	elem.SemanticIndex = 0;
	elem.SemanticName = "COLOR";
	elem.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	return elem;
}


D3D11_INPUT_ELEMENT_DESC VertexElements::Normal3(int slot)
{
	D3D11_INPUT_ELEMENT_DESC elem;
	elem.AlignedByteOffset = 0;
	elem.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
	elem.InputSlot = slot;
	elem.InstanceDataStepRate = 0;
	elem.SemanticIndex = 0;
	elem.SemanticName = "NORMAL";
	elem.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	return elem;
}

D3D11_INPUT_ELEMENT_DESC VertexElements::TexCoord2(int slot,int index)
{
	D3D11_INPUT_ELEMENT_DESC elem;
	elem.AlignedByteOffset = 0;
	elem.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
	elem.InputSlot = slot;
	elem.InstanceDataStepRate = 0;
	elem.SemanticIndex = index;
	elem.SemanticName = "TEXCOORD";
	elem.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	return elem;
}

} }

