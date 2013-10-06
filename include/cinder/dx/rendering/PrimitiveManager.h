#pragma once

#include "cinder/Vector.h"
/*#include "cinder/Trimesh.h"*/

#include "IndexedGeometry.h"
#include "cinder/dx/utils/VertexElements.h"

namespace cinder { namespace dx {

class GeometricPrimitives
{
public:
	static IndexedGeometry* Quad(DxDevice* device);
	static IndexedGeometry* Box(DxDevice* device);
	static IndexedGeometry* Segment(DxDevice* device,float phase, float cycles, float inner, UINT res, bool flat);
	/*static IndexedGeometry* TriMesh(RenderContext* context, ci::TriMesh* mesh);
	static IndexedGeometry* TriMesh2(RenderContext* context, ci::TriMesh2d* mesh);*/
};

}}