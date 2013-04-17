#include "StdAfx.h"
#include "txBasicMesh.h"

#include <assert.h>
#include <math.h>


txBasicMesh::txBasicMesh(void)
{
	AllocatePVET();
	// After teh CopyO2N is called.
	// The original only use for cache and will strictly not used in the algorithm
	// for consice!
	CopyO2N();

}

txBasicMesh::txBasicMesh(MeshData* meshdata) {
	this->meshdata = meshdata;
	oV = meshdata->oV;
	oE = meshdata->oE;
	oT = meshdata->oT;

	AllocatePVET();
	// After teh CopyO2N is called.
	// The original only use for cache and will strictly not used in the algorithm
	// for consice!
	CopyO2N();
}


txBasicMesh::~txBasicMesh(void)
{
	DeallocatePVET();
}

void txBasicMesh::SubdivsionMesh()
{
	IterateOEdgesCreateNewMiddleVertex();
	IterateOTrianglesCreateNewTrisEdges();
	UpdateOuter3TriConnectivity();
	UpdateOuterSplitEdgesConnectivity();
	UpdateMiddleTriConnectivity();
	UpdateOVertexValances();
}

void txBasicMesh::AllocatePVET()
{
	nT = 4*oT; 
	nE = 2*oE + 3*oT;
	nV = oV + oE;

	txPoint3 d;
	npoints.reserve(nV);
	nvertices.reserve(nV);
	for (size_t i=0; i<nV; i++)
	{
		npoints.push_back(d);
		txVertex *pv = new txVertex;
		pv->numEdges = 0;
		nvertices.push_back(pv);
	}

	nedges.reserve(nE);
	for (size_t i=0; i<nE; i++)
	{
		txEdge *pe = new txEdge;
		nedges.push_back(pe);
	}

	ntriangles.reserve(nT);
	for (size_t i=0; i<nT; i++)
	{
		txTriangle *pt = new txTriangle;
		ntriangles.push_back(pt);
	}

	triCfg = new txQuaterTriCfg(oV, oE, oT, nvertices,nedges,ntriangles);

}

void txBasicMesh::DeallocatePVET()
{
	// delete the txVertex, txEdge, txTriangle => both originally and the subdivision!
	for (size_t i=0; i<nvertices.size(); i++) {
		if (nvertices[i]!=NULL) {
			delete nvertices[i];
			nvertices[i] = NULL;
		}
	}
	for (size_t i=0; i<nedges.size(); i++) {
		if (nedges[i]!=NULL) {
			delete nedges[i];
			nedges[i] = NULL;
		}
	}
	for (size_t i=0; i<ntriangles.size(); i++) {
		if (ntriangles[i]!=NULL) {
			delete ntriangles[i]; 
			ntriangles[i] = NULL;
		}
	}
	// delete Traingle Configure
	if (triCfg!=NULL) {
		delete triCfg;
		triCfg = NULL;
	}
	

	// delete new meshdata
	if (newMeshData!=NULL) {
		delete newMeshData;
		newMeshData = NULL;
	}
}

void txBasicMesh::CopyO2N()
{
	std::vector<txPoint3> &opoints = meshdata->opoints;
	std::vector<txVertex*> &overtices = meshdata->overtices;
	std::vector<txEdge*> &oedges = meshdata->oedges;
	std::vector<txTriangle*> &otriangles = meshdata->otriangles;

	this->oV = meshdata->oV;
	this->oE = meshdata->oE;
	this->oT = meshdata->oT;

	// assign points
	for (size_t i=0; i<opoints.size(); i++)	{
		npoints[i] = opoints[i];
	}

	// assign vertex
	txVertex *ov, *nv;
	for (size_t i=0; i<overtices.size(); i++) {
		ov = overtices[i];
		nv = nvertices[i];
		nv->numEdges = ov->numEdges;
		for (size_t j=0; j<ov->numEdges; j++) {
			nv->edgeIds[j] = ov->edgeIds[j];
		}
		
		nv->pointId = ov->pointId;
	}

	// assign edges
	txEdge *oe, *ne;
	for (size_t i=0; i<oedges.size(); i++) {
		oe = oedges[i];
		ne = nedges[i];
		for (size_t j=0; j<2; j++) {
			ne->T[j] = oe->T[j];
			ne->V[j] = oe->V[j];
		}
	}

	// assign triangle info
	txTriangle *ot, *nt;
	for (size_t i=0; i<otriangles.size(); i++) {
		ot = otriangles[i];
		nt = ntriangles[i];
		for (size_t j=0; j<3; j++) {
			nt->A[j] = ot->A[j];
			nt->E[j] = ot->E[j];
			nt->V[j] = ot->V[j];
		}
	}
}

void txBasicMesh::IterateOEdgesCreateNewMiddleVertex()
{
	for (size_t i=0; i<oE; i++)
	{
		// get original edges
		txEdge *e = nedges[i];
		// get new edge postion to be updateed
		txEdge *ne = nedges[oE + i];
		// get original two vertex of e
		txVertex *v0 = nvertices[e->V[0]];
		txVertex *v1 = nvertices[e->V[1]];
		// get new middle point position to be updated
		size_t mIndex = oV + i;
		txVertex *M  = nvertices[mIndex];
		// assign this middle vertex's valence to Zero 
		// and use this ZERO as a logic to update it later!
		M->numEdges = 0;
		// calculate the geometry position of the middle points 
		txPoint3 mp = CalculateMiddlePoint(npoints[v0->pointId],npoints[v1->pointId]);
		M->pointId = mIndex;
		// upate the new points list
		npoints[mIndex] = mp;
		// update the new create split edge
		ne->V[0] = M->pointId;
		ne->V[1] = e->V[1];
		e->V[1] = M->pointId;
	}
}

void txBasicMesh::IterateOTrianglesCreateNewTrisEdges()
{
	for (size_t i=0; i<oT; i++)
	{
		triCfg->ConstructInternalVETIndex(i);
		triCfg->UpdateNewTrianglesNewVerticesInOTriangle();
	}
}

void txBasicMesh::UpdateOuter3TriConnectivity()
{
	txQuaterTriCfg *a0Cfg, *a1Cfg, *a2Cfg;
	a0Cfg = triCfg->DeepCopy();
	a1Cfg = triCfg->DeepCopy();
	a2Cfg = triCfg->DeepCopy();

	for (size_t i=0; i<oT; i++)
	{
		triCfg->ConstructInternalVETIndex(i);

		size_t a0 = triCfg->T0->A[0];
		a0Cfg->ConstructInternalVETIndex(a0);
		txQuaterTriCfg::UpdateOuter3TriConnectivity(triCfg,a0Cfg);

		size_t a1 = triCfg->T0->A[1];
		a1Cfg->ConstructInternalVETIndex(a1);
		txQuaterTriCfg::UpdateOuter3TriConnectivity(triCfg,a1Cfg);

		size_t a2 = triCfg->T0->A[2];
		a2Cfg->ConstructInternalVETIndex(a2);
		txQuaterTriCfg::UpdateOuter3TriConnectivity(triCfg,a2Cfg);


		txQuaterTriCfg::UpdateMiddleVertexValances(triCfg);
	}

	delete a0Cfg;
	delete a1Cfg;
	delete a2Cfg;
}

void txBasicMesh::UpdateOVertexValances()
{
	// update the original vertex velance due to the edge spliting
	// only one spliting edge is right, the other one is newly created!
	for (size_t i=0; i<oV; i++) {
		txVertex *v = nvertices[i];
		for (size_t j=0; j<v->numEdges; j++) {
			txEdge *e = nedges[v->edgeIds[j]];
			if (e->V[0]!=i && e->V[1]!=i) {
				// update the edge Id to the edge create by spliting!
				v->edgeIds[j] = oV + v->edgeIds[j];
			}
		}
	}
}

txPoint3 txBasicMesh::CalculateMiddlePoint(txPoint3 &p0, txPoint3 &p1)
{
	txPoint3 p;
	p.x = (p0.x+p1.x)/2.0;
	p.y = (p0.y+p1.y)/2.0;
	p.z = (p0.z+p1.z)/2.0;
	double l = sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
	// cause the raduis is default set to 1.0;
	double rl = 1.0/l;
	
	p.x = rl*p.x;
	p.y = rl*p.y;
	p.z = rl*p.z;

	return p;
}

void txBasicMesh::UpdateMiddleTriConnectivity()
{
	for (size_t i=0; i<oT; i++) {
		triCfg->ConstructInternalVETIndex(i);
		UpdateMiddleTriConnectivity(triCfg,i);
	}
}

void txBasicMesh::UpdateMiddleTriConnectivity(txQuaterTriCfg *t, size_t i)
{
	txTriangle *T0 = ntriangles[i]; // TODO! This can be replaced!
	T0->V[0] = t->m0;   T0->V[1] = t->m1;   T0->V[2] = t->m2;
	T0->E[0] = t->e1__; T0->E[1] = t->e2__; T0->E[2] = t->e0__;
	T0->A[0] = t->t2;   T0->A[1] = t->t3;   T0->A[2] = t->t1;
}

void txBasicMesh::UpdateOuterSplitEdgesConnectivity()
{
	for (size_t i=0; i<oT; i++) {
		triCfg->ConstructInternalVETIndex(i);
		txQuaterTriCfg::UpdateOuterSplitEdgesConnectivity(triCfg);
	}
}

MeshData* txBasicMesh::GetSubdivsionMeshData()
{
	newMeshData = new MeshData;
	newMeshData->oV = nV;
	newMeshData->oE = nE;
	newMeshData->oT = nT;
	newMeshData->opoints = npoints;
	newMeshData->overtices = nvertices;
	newMeshData->oedges = nedges;
	newMeshData->otriangles = ntriangles;

	return newMeshData;
}




