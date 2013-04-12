#include "StdAfx.h"
#include "txSubdivisionTopo.h"
/**
* The PUSHFACEINDEX(0, 1, 2, 3) equal to the following code
* f0->vertices[0] = 1;
* f0->vertices[1] = 2;
* f0->vertices[2] = 3;
*/
#define PUSH_FACE_INDEX(facenum, v0, v1, v2) \
	f##facenum->vertices[0] = v0;\
	f##facenum->vertices[1] = v1;\
	f##facenum->vertices[2] = v2;

#define PUSH_ADJACENT_FACE_INDEX(facenum, f0, f1, f2) \
	f##facenum->adjacentfs[0] = f0; \
	f##facenum->adjacentfs[1] = f1; \
	f##facenum->adjacentfs[2] = f2;


void static AssignValueToVertex(txVector *v, double x, double y, double z)
{
	v->a[0] = x; v->a[1] = y, v->a[2] = z;
}

txSubdivisionTopo::txSubdivisionTopo()
{

}

txSubdivisionTopo::~txSubdivisionTopo()
{

}

void txSubdivisionTopo::ConstructSubdivision(size_t level)
{
	
}

/**
* The following numerical is calculated by Maxima 
* sin1:1;
* cos1: 0;
* sin2: -1/2;
* cos2: -sqrt(3)/2;
* sin3: -1/2;
* cos3: sqrt(3)/2;
* cosphi: 1/3;
* sinphi: 2*sqrt(2)/3;
*
* For sphere coordinate
* x = sin(theta)sin(phi)*r
* y = cos(theta)sin(phi)*r
* z = cos(phi)*r
*/
void txSubdivisionTopo::InitializeShape()
{
	// unit shpere
	double x0,y0,z0,x1,y1,z1,x2,y2,z2,x3,y3,z3;
	x0 = 0.0; y0 = 0.0; z0 = 1.0;
	x1 = 0.94280904158206;
	y1 = 0.0;
	z1 = 0.33333333333333;
	x2 = -0.47140452079103;
	y2 = -0.81649658092773;
	z2 = z1;
	x3 = -0.47140452079103;
	y3 = 0.81649658092773;
	z3 = z1;

	txVector *v0 = new txVector;
	txVector *v1 = new txVector;
	txVector *v2 = new txVector;
	txVector *v3 = new txVector;
	AssignValueToVertex(v0, x0, y0, z0);
	AssignValueToVertex(v1, x1, y1, z1);
	AssignValueToVertex(v2, x2, y2, z2);
	AssignValueToVertex(v3, x3, y3, z3);

	vertexlist.push_back(v0);
	vertexlist.push_back(v1);
	vertexlist.push_back(v2);
	vertexlist.push_back(v3);
	
	txFace *f0 = new txFace;
	txFace *f1 = new txFace;
	txFace *f2 = new txFace;
	txFace *f3 = new txFace;

	// parent face
	f0->parentf = -1;
	f1->parentf = -1;
	f2->parentf = -1;
	f3->parentf = -1;

	// face contained vertex index
	PUSH_FACE_INDEX(0, 1, 2, 3);
	PUSH_FACE_INDEX(1, 0, 1, 3);
	PUSH_FACE_INDEX(2, 1, 0, 2);
	PUSH_FACE_INDEX(3, 0, 3, 2);

	// face adjacent faces
	PUSH_ADJACENT_FACE_INDEX(0, 1, 2, 3);
	PUSH_ADJACENT_FACE_INDEX(1, 0, 2, 3);
	PUSH_ADJACENT_FACE_INDEX(2, 0, 1, 3);
	PUSH_ADJACENT_FACE_INDEX(3, 0, 1, 2);

	facelist.push_back(f0);
	facelist.push_back(f1);
	facelist.push_back(f2);
	facelist.push_back(f3);
}
