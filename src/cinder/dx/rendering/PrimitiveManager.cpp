#include "cinder/dx/rendering/PrimitiveManager.h"

using namespace ci;

namespace cinder { namespace dx {

IndexedGeometry* GeometricPrimitives::Quad(DxDevice* device)
{
	IndexedGeometry* geom = new IndexedGeometry(device);

	Vec4f v[4] = 
	{ 
		Vec4f(-0.5f,-0.5f,0.0f,1.0f),
		Vec4f(0.5f,-0.5f,0.0f,1.0f),
		Vec4f(0.5f,0.5f,0.0f,1.0f),
		Vec4f(-0.5f,0.5f,0.0f,1.0f)
	};

	Vec2f uv[4] = 
	{ 
		Vec2f(0.0f,1.0f),
		Vec2f(1.0f,1.0f),
		Vec2f(1.0f,0.0f),
		Vec2f(0.0f,0.0f)
	};
	
	UINT indices[6] = {  0, 2,1, 0,3,2};

	std::vector<D3D11_INPUT_ELEMENT_DESC> elems;
	elems.clear();
	elems.push_back(VertexElements::Position4());

	VertexBuffer* vb = VertexBuffer::CreateImmutable(device,&v[0],4,4*sizeof(float),elems); // new VertexBuffer(device,4,4*sizeof(float),v,elems);
	geom->AddVertexBuffer(vb);

	elems.clear();
	elems.push_back(VertexElements::TexCoord2());
	
	VertexBuffer* vbuv =VertexBuffer::CreateImmutable(device,&uv[0],4,2*sizeof(float),elems);  //new VertexBuffer(device,4,2*sizeof(float),uv,elems);
	geom->AddVertexBuffer(vbuv);
	 
	IndexBuffer* ib = IndexBuffer::CreateImmutable(device,&indices[0],6); //new IndexBuffer(device,6,&indices[0]);
	geom->SetIndexBuffer(ib);

	return geom;
}

IndexedGeometry* GeometricPrimitives::Box(DxDevice* device)
{
	Vec4f BottomLeftFront(-1.0f, -1.0f, 1.0f, 1.0f);
    Vec4f BottomRightFront(1.0f, -1.0f, 1.0f, 1.0f);
    Vec4f TopRightFront(1.0f, 1.0f, 1.0f, 1.0f);
    Vec4f TopLeftFront(-1.0f, 1.0f, 1.0f, 1.0f);

    Vec4f BottomLeftBack(-1.0f, -1.0f, -1.0f, 1.0f);
    Vec4f BottomRightBack(1.0f, -1.0f, -1.0f, 1.0f);
    Vec4f TopRightBack(1.0f, 1.0f, -1.0f, 1.0f);
    Vec4f TopLeftBack(-1.0f, 1.0f, -1.0f, 1.0f);

	Vec2f QuadUvLayout[] = 
    {
		Vec2f(1.0f,1.0f),
        Vec2f(0.0f,1.0f),
        Vec2f(0.0f,0.0f),
        Vec2f(1.0f,0.0f),
    };

	IndexedGeometry* geom = new IndexedGeometry(device);

	UINT verticescount = 24;
	UINT indicescount = 36;

	Vec4f vpos[24];	
	Vec3f vnorm[24];	
	Vec2f vuv[24];

	//Front
	vpos[0] = BottomLeftFront; vpos[1] = BottomRightFront; vpos[2] =TopRightFront; vpos[3] = TopLeftFront;
	vnorm[0] = vnorm[1] = vnorm[2] = vnorm[3] = -Vec3f::zAxis();
	vuv[0] = QuadUvLayout[0]; vuv[1] = QuadUvLayout[1]; vuv[2] = QuadUvLayout[2]; vuv[3] = QuadUvLayout[3];

	//Back
	vpos[4] = BottomRightBack; vpos[5] = BottomLeftBack; vpos[6] =TopLeftBack; vpos[7] = TopRightBack;
	vnorm[4] = vnorm[5] = vnorm[6] = vnorm[7] =  Vec3f::zAxis();
	vuv[4] = QuadUvLayout[0]; vuv[5] = QuadUvLayout[1]; vuv[6] = QuadUvLayout[2]; vuv[7] = QuadUvLayout[3];

	//Right
	vpos[8] = BottomRightFront; vpos[9] = BottomRightBack; vpos[10] =TopRightBack; vpos[11] = TopRightFront;
	vnorm[8] = vnorm[9] = vnorm[10] = vnorm[11] =  Vec3f::xAxis();
	vuv[8] = QuadUvLayout[0]; vuv[9] = QuadUvLayout[1]; vuv[10] = QuadUvLayout[2]; vuv[11] = QuadUvLayout[3];

	//Left
	vpos[12] = BottomLeftBack; vpos[13] = BottomLeftFront; vpos[14] =TopLeftFront; vpos[15] = TopLeftBack;
	vnorm[12] = vnorm[13] = vnorm[14] = vnorm[15] =  -Vec3f::xAxis();
	vuv[12] = QuadUvLayout[0]; vuv[13] = QuadUvLayout[1]; vuv[14] = QuadUvLayout[2]; vuv[15] = QuadUvLayout[3];

	//Top
	vpos[16] = TopLeftFront; vpos[17] = TopRightFront; vpos[18] =TopRightBack; vpos[19] = TopLeftBack;
	vnorm[16] = vnorm[17] = vnorm[18] = vnorm[19] =  Vec3f::yAxis();
	vuv[16] = QuadUvLayout[2]; vuv[17] = QuadUvLayout[3]; vuv[18] = QuadUvLayout[0]; vuv[19] = QuadUvLayout[1];

	//Bottom
	vpos[20] = BottomLeftBack; vpos[21] = BottomRightBack; vpos[22] =BottomRightFront; vpos[23] = BottomLeftFront;
	vnorm[20] = vnorm[21] = vnorm[22] = vnorm[23] =  -Vec3f::yAxis();
	vuv[20] = QuadUvLayout[0]; vuv[21] = QuadUvLayout[1]; vuv[22] = QuadUvLayout[2]; vuv[23] = QuadUvLayout[3];

	UINT indices[36] = {  0, 1, 2, 2, 3, 0,4, 5, 6, 6, 7, 4,8, 9, 10, 10, 11, 8 ,
		12, 13, 14, 14, 15, 12,16, 17, 18, 18, 19, 16,20, 21, 22, 22, 23, 20 };

	std::vector<D3D11_INPUT_ELEMENT_DESC> elems;
	elems.clear();
	elems.push_back(VertexElements::Position4());

	VertexBuffer* vbpos = VertexBuffer::CreateImmutable(device,&vpos,24,4*sizeof(float),elems);
	geom->AddVertexBuffer(vbpos);

	elems.clear();
	elems.push_back(VertexElements::Normal3());
		 
	VertexBuffer* vbnorm = VertexBuffer::CreateImmutable(device,&vnorm,24,3*sizeof(float),elems);
	geom->AddVertexBuffer(vbnorm);

		elems.clear();
	elems.push_back(VertexElements::TexCoord2());

	VertexBuffer* vbuv = VertexBuffer::CreateImmutable(device,&vuv,24,2*sizeof(float),elems);
	geom->AddVertexBuffer(vbuv);

	IndexBuffer* ib = IndexBuffer::CreateImmutable(device,&indices,36);
	geom->SetIndexBuffer(ib);

	return geom;
}

IndexedGeometry* GeometricPrimitives::Segment(DxDevice* device,float phase, float cycles, float inner, UINT res, bool flat)
{
	IndexedGeometry* geom = new IndexedGeometry(context);

	D3D11_INPUT_ELEMENT_DESC poselem = VertexElements::Position4();
	D3D11_INPUT_ELEMENT_DESC uvelem = VertexElements::TexCoord2();

	UINT vcount = res * 2;
    UINT icount = (res - 1) * 6;

	Vec4f* vpos = new Vec4f[vcount];
	Vec2f* uvs = new Vec2f[vcount];


	float inc = (3.14159265358979323846f * 2.0f * cycles) / (res - 1.0f);
    float phi = phase * (3.14159265358979323846f * 2.0f);

	for (int i = 0; i < res; i++)
    {
        float x = 0.5f * inner * cos(phi);
        float y = 0.5f * inner * sin(phi);

		Vec4f innerpos(x, y, 0.0f, 1.0f);
		Vec2f inneruv;

        if (flat)
        {
			inneruv = Vec2f(0.5f - x, 0.5f - y);
        }
        else
        {
			inneruv = Vec2f((1.0f * (float)i) / ((float)res - 1.0f), 0.0f);
        }

        x = 0.5f * cos(phi);
        y = 0.5f * sin(phi);

		Vec4f outerpos = Vec4f(x, y, 0.0f, 1.0f);
		Vec2f outeruv;

        if (flat)
        {
            outeruv = Vec2f(0.5f - x, 0.5f - y);
        }
        else
        {
            outeruv = Vec2f((1.0f * (float)i) / ((float)res - 1.0f), 1.0f);
        }

        vpos[i] = innerpos;
        vpos[i + res] = outerpos;
		uvs[i] = inneruv;
		uvs[i + res] = outeruv;
        phi += inc;
    }

	UINT indstep = 0;
    UINT* indices = new UINT[icount];
    for (UINT i = 0; i < res - 1; i++)
    {
        //Triangle from low to high
        indices[indstep] = i;
        indices[indstep + 2] = i + 1;
        indices[indstep + 1] = res + i;

        //Triangle from high to low
        indices[indstep + 3] = i + 1;
        indices[indstep + 4] = res + i;
        indices[indstep + 5] = res + i + 1;

        indstep += 6;
    }

	std::vector<D3D11_INPUT_ELEMENT_DESC> elems;
	elems.clear();
	elems.push_back(VertexElements::Position4());

	VertexBuffer* vb = new VertexBuffer(context,vcount,4*sizeof(float),vpos,elems);
	geom->AddVertexBuffer(vb);

	elems.clear();
	elems.push_back(VertexElements::TexCoord2());
	
	VertexBuffer* vbuv = new VertexBuffer(context,vcount,2*sizeof(float),uvs,elems);
	geom->AddVertexBuffer(vbuv);

	 
	IndexBuffer* ib = new IndexBuffer(context,icount,indices);
	geom->SetIndexBuffer(ib);

	/*delete indices;
	delete vpos;
	delete uvs;*/

	return geom;
}

}}