#pragma once

#include "cinder/Vector.h"
/*#include "cinder/Trimesh.h"*/

#include "IndexedGeometry.h"
#include "NullGeometry.h"
#include "cinder/dx/utils/VertexElements.h"

namespace cinder { namespace dx {

class GeometricPrimitives
{
public:
	GeometricPrimitives(DxDevice* device) { mDevice = device; }
	IndexedGeometry* Quad();
	IndexedGeometry* Box();
	IndexedGeometry* Segment(float phase, float cycles, float inner, UINT res, bool flat);

	NullGeometry* FullScreenTriangle();
	/*static IndexedGeometry* TriMesh(RenderContext* context, ci::TriMesh* mesh);
	static IndexedGeometry* TriMesh2(RenderContext* context, ci::TriMesh2d* mesh);*/
private:
	DxDevice* mDevice;
};

}}