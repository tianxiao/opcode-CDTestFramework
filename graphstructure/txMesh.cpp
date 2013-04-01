#include "StdAfx.h"
#include <assert.h>
#include "txMesh.h"
#include "./lib/mesh.h"

//#include "./lib/funcs.h"


extern "C" void SolidConstructNoff( Solid **  , char *);
extern "C" void SolidDestruct( Solid * * solid );

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

void txMesh::ConstructMeshFromFile(char* filename)
{
	SolidConstructNoff(&solid,filename);

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
