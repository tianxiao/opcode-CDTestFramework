#include "stdafx.h"
#include "txBasicMesh.h"
#include "subdivisionlevel.h"
#include "../txShapelib/txTriSurfaceData.h"
#include "../txGeometrylib/txVector3.h"
#include "../txCore/txMemoryUtil.h"

void AllocateMeshData(MeshData *md, txVector3 *verts, int *indexes) {
	assert(md!=NULL && verts!=NULL && indexes!=NULL);
	for (size_t i=0; i<md->oV; i++) {
		verts[i].x = md->opoints[i].x;
		verts[i].y = md->opoints[i].y;
		verts[i].z = md->opoints[i].z;
	}

	for (size_t i=0; i<md->oT; i++) {
		for (size_t j=0; j<3; j++) {
			indexes[i*3+j] = md->otriangles[i]->V[j];
		}
	}
}


int txTessellateSphere(const double radius, const int refinement_level, int is_solid_inside, txTriSurfaceData *&surf)
{
	// For win32 the refinement level need not to dense! other wise OUT OF MEMORY!
	assert(refinement_level>0);
	assert(refinement_level<7);

	MeshData *meshdata = MeshDataConfigOct();
	txBasicMesh *recur = new txBasicMesh(meshdata);
	MeshDataReleaseOct(meshdata);

	for (int i=0; i<refinement_level; i++) {
		recur->SubdivsionMesh();
		txBasicMesh *inter = new txBasicMesh(recur->GetSubdivsionMeshData());
		delete recur;
		recur = inter;
	}
	recur->SubdivsionMesh();

	MeshData *rtnmeshdata = recur->GetSubdivsionMeshData();
	
	// TODO these data adapter will combine to one!!!
	int numVerts = rtnmeshdata->oV;
	int numIndexes = rtnmeshdata->oT*3;
	txVector3 *verts = new txVector3[numVerts];
	int *indexes = new int[numIndexes];

	AllocateMeshData(rtnmeshdata, verts, indexes);
	surf = new txTriSurfaceData(verts,numVerts,indexes,numIndexes);
	
	txMemoryUtil::txDeleteArray(indexes);
	txMemoryUtil::txDeleteArray(verts);
	txMemoryUtil::txDelete(recur);
	return rtnmeshdata->oT; 
}