#include "StdAfx.h"
#include <assert.h>
#include "txMesh.h"
#include "./lib/mesh.h"

//#include "./lib/funcs.h"


extern "C" void SolidConstructNoff( Solid **  , char *);

txMesh::txMesh(void)
{
	this->solid = NULL;
}


txMesh::~txMesh(void)
{
}

void txMesh::ConstructMeshFromFile(std::string filename)
{
	SolidConstructNoff(&solid,const_cast<char *>(filename.c_str()));

	ConstructFVEIndex();
}

void txMesh::ConstructFVEIndex()
{
	face *facehead = solid->sfaces;
	face *facecur = facehead;
	assert(facehead);
	do {
		facelist.push_back(facecur);
		//TODO set face ID use this ID to do the hash in the graph search
		facecur = facecur->next;
	}while(facecur!=facehead);

	vertex *vertexhead = solid->sverts;
	vertex *vertexcur = vertexhead;
	assert(vertexhead);
	do {
		vertexlist.push_back(vertexcur);
		//TODO set vertex ID same reason as the face
		vertexcur = vertexcur->next;
	}while (vertexcur!=vertexhead);

	edge *edgehead = solid->sedges;
	edge *edgecur = edgehead;
	do {
		edgelist.push_back(edgecur);
		//TODO set edge ID
		edgecur = edgecur->next;
	}while(edgecur != edgehead);
	
}
