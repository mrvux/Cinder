#pragma once

#include "dx11.h"

namespace cinder { namespace dx {

class VertexElements
{
public:
	static D3D11_INPUT_ELEMENT_DESC Position2(int slot = 0);
	static D3D11_INPUT_ELEMENT_DESC Position3(int slot = 0);
	static D3D11_INPUT_ELEMENT_DESC Position4(int slot = 0);

	static D3D11_INPUT_ELEMENT_DESC Color3(int slot = 0);
	static D3D11_INPUT_ELEMENT_DESC Color4(int slot = 0);

	static D3D11_INPUT_ELEMENT_DESC Normal3(int slot = 0);

	static D3D11_INPUT_ELEMENT_DESC TexCoord2(int slot = 0,int index = 0);
};

} }