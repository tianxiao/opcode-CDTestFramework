#include "StdAfx.h"
#include <assert.h>
#include "txMesh.h"
#include "./lib/mesh.h"
#include "../txShapelib/txTriSurfaceData.h"
#include "../txGeometrylib/txVector3.h"

//#include "./lib/funcs.h"


extern "C" void SolidConstructNoff( Solid **  , char *);
extern "C" void SolidDestruct( Solid * * solid );
extern "C" void SolidConstruct( Solid * * solid , char *FileName);
extern "C" Solid *SolidNew();
extern "C" {
	void VertexConstructN( Solid ** , double , double , double ,double , double , double );
	void VertexListIndexConstruct(Solid **);
	void  EdgeListConstruct(Solid ** );
	Vertex *VertexListIndex(Solid * ,int );
	void FaceConstruct( Solid **, Vertex *, Vertex *,Vertex *);
};

void VertexListConstrcutFromSurface(Solid * * solid, txTriSurfaceData *surf)
{
	std::vector<txVector3> &verts = surf->GetVerts();
	for (size_t i=0; i<verts.size(); i++) {
		VertexConstructN(solid,verts[i].x, verts[i].y, verts[i].z, 0.0, 0.0, 0.0);
	}
}

void FaceListConstructFromSurface(Solid * * solid, txTriSurfaceData *surf)
{
	int a, b, c;
	Vertex *va, *vb, *vc;
	std::vector<int> &indexes = surf->GetIndexes();
	for (size_t i=0; i<indexes.size()/3; i++) {
		a = indexes[i*3];
		b = indexes[i*3+1];
		c = indexes[i*3+2];
		va = VertexListIndex(*solid, a);
		vb = VertexListIndex(*solid, b);
		vc = VertexListIndex(*solid, c);
		FaceConstruct( solid, va, vb, vc);
	}
}

void SolidConstrcutFromSurface(Solid * * solid, txTriSurfaceData *surf)
{
	Solid * s;
	s = SolidNew();

	VertexListConstrcutFromSurface(&s, surf);
	VertexListIndexConstruct(&s);
	FaceListConstructFromSurface(&s,surf);
	EdgeListConstruct(&s);

	*solid = s;
}

txMesh::txMesh(void)
{
	this->solid = NULL;
}


txMesh::~txMesh(void)
{
	if (solid) {
		SolidDestruct(&solid);
	}
}

void txMesh::ConstructMeshFromFile(char* filename, FileFormat f/*=NOFF*/)
{
	if (NOFF == f) {
		SolidConstructNoff(&solid,filename);
	}

	if (OFF == f) {
		SolidConstruct(&solid, filename);
	}
	

	ConstructFVEIndex();
}

void txMesh::ConstructMeshFromOFFTriSurface(txTriSurfaceData *surf)
{
	SolidConstrcutFromSurface(&solid, surf);
	ConstructFVEIndex();
}


void txMesh::ConstructMeshFromSolid(Solid *s)
{
	this->solid = s;

	ConstructFVEIndex();
}


void txMesh::ConstructFVEIndex()
{
	face *facehead = solid->sfaces;
	face *facecur = facehead;
	assert(facehead);
	// It's OK
	int faceId = 0;
	do {
		facelist.push_back(facecur);
		// set face ID use this ID to do the hash in the graph search
		// The previous method is set this id by static method 
		// which is thread unsafty!
		facecur->faceno = faceId;
		faceId++;
		facecur = facecur->next;
	}while(facecur!=facehead);

	vertex *vertexhead = solid->sverts;
	vertex *vertexcur = vertexhead;
	assert(vertexhead);
	int vertexId=0;
	do {
		vertexlist.push_back(vertexcur);
		// set vertex ID same reason as the face
		// The same modification as the faceno
		// cause the vertexId has been set when 
		// the file reading! assert here is a double check
		assert(vertexcur->vertexno==vertexId);
		vertexcur->vertexno = vertexId;
		vertexId++;
		vertexcur = vertexcur->next;
	}while (vertexcur!=vertexhead);

	// edge do not have the Id number so I add one
	edge *edgehead = solid->sedges;
	edge *edgecur = edgehead;
	int edgeId = 0;
	do {
		edgelist.push_back(edgecur);
		// set edge ID
		edgecur->edgeno = edgeId;
		edgeId++;
		edgecur = edgecur->next;
	}while(edgecur != edgehead);
	
}

void txMesh::GetFaceVertexIdListByFId(const int faceno, int &a, int &b, int &c)
{
	std::vector<int> faceverticeslist;
	Face *fp = facelist[faceno];
	Loop *lp = fp->floop;
	HalfEdge *hep = lp->ledges;
	HalfEdge *hehp = hep;
	faceverticeslist.reserve(3);
	do 
	{
		faceverticeslist.push_back(hep->hvert->vertexno);
		hep = hep->next;
	} while(hep!=hehp);
	// Only Implement the Tri-Mesh
	assert(faceverticeslist.size()==3);
	a = faceverticeslist[0];
	b = faceverticeslist[1];
	c = faceverticeslist[2];
}

void txMesh::CircleFacesFace(int faceId, int &face1, int &face2, int &face3)
{
	face *face0 = facelist[faceId];
	loop *loop = face0->floop;
	halfedge *hfhead = loop->ledges;
	halfedge *hfcur = hfhead;
	std::vector<halfedge*> halfedgelist;
	halfedgelist.reserve(3);// only efficient for Tri-Mesh
	do 
	{
		halfedgelist.push_back(hfcur);
		hfcur = hfcur->next;
	} while (hfcur!=hfhead);

	assert(halfedgelist.size()==3);
	face1 = FaceIdReverseHalfedge(halfedgelist[0]);
	face2 = FaceIdReverseHalfedge(halfedgelist[1]);
	face3 = FaceIdReverseHalfedge(halfedgelist[2]);
}

halfedge *txMesh::HalfedgeHalfedge(halfedge *hf)
{
	edge *commonedge = hf->hedge;
	if ( commonedge->he1 == hf ) {
		return commonedge->he2;
	} else {
		return commonedge->he1;
	}
}

int txMesh::FaceIdHalfedge(halfedge *hf)
{
	int faceId = hf->hloop->lface->faceno;
	return faceId;
}

int txMesh::FaceIdReverseHalfedge(halfedge *hf)
{
	halfedge *rhf = HalfedgeHalfedge(hf);
	return FaceIdHalfedge(rhf);
}

