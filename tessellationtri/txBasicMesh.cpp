#include "StdAfx.h"
#include "txBasicMesh.h"

#include <assert.h>


txBasicMesh::txBasicMesh(void)
{
}


txBasicMesh::~txBasicMesh(void)
{
}

void txBasicMesh::SubdivsionMesh()
{
	IterateOEdgesCreateNewMiddleVertex();
	IterateOTrianglesCreateNewTrisEdges();
	UpdateOuter3TriConnectivity();
	UpdateMiddleVertexValances();
	UpdateT0();
	UpdateOVertexValances();
}

void txBasicMesh::AllocatePVET()
{
	nT = 4*oT; 
	nE = 2*oE + 3*nT;
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


}

void txBasicMesh::DeallocatePVET()
{
	
}

void txBasicMesh::IterateOEdgesCreateNewMiddleVertex()
{
	for (size_t i=0; i<oE; i++)
	{
		// get original edges
		txEdge *e = oedges[i];
		// get new edge postion to be updateed
		txEdge *ne = nedges[oE + i];
		// get original two vertex of e
		txVertex *v0 = overtices[e->V[0]];
		txVertex *v1 = overtices[e->V[1]];
		// get new middle point position to be updated
		size_t mIndex = oV + i;
		txVertex *M  = nvertices[mIndex];
		// calculate the geometry position of the middle points 
		txPoint3 mp = CalculateMiddlePoint(opoints[v0->pointId],opoints[v1->pointId]);
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
		//***************************************

		txTriangle * T0 = otriangles[i];
		size_t v0, v1, v2;
		v0 = T0->V[0]; v1 = T0->V[1]; v2 = T0->V[2];
		txVertex *V0 = overtices[v0];
		txVertex *V1 = overtices[v1];
		txVertex *V2 = overtices[v2];

		size_t e0, e1, e2;
		e0 = T0->E[0]; e1 = T0->E[1]; e2 = T0->E[2];
		txEdge *E0 = oedges[e0];
		txEdge *E1 = oedges[e1];
		txEdge *E2 = oedges[e2];

		size_t m0, m1, m2;
		m0 = oV + e0; m1 = oV + e1; m2 = oV + e2;
		txVertex *M0 = nvertices[m0];
		txVertex *M1 = nvertices[m1];
		txVertex *M2 = nvertices[m2];

		size_t e0_, e1_, e2_;
		e0_ = oE + e0; e1_ = oE + e1; e2_ = oE + e2;
		txEdge *E0_ = nedges[e0_];
		txEdge *E1_ = nedges[e1_];
		txEdge *E2_ = nedges[e2_];
		
		//---------------------------------------
		size_t t1, t2, t3;
		t1 = oT + i; t2 = oT*2 + i; t3 = oT*3 + i;
		txTriangle *T1 = ntriangles[t1];
		txTriangle *T2 = ntriangles[t2];
		txTriangle *T3 = ntriangles[t3];

		size_t e0__, e1__, e2__;
		e0__ = 2*oE +i; e1__ = 2*oE + oT + i; e2__ = 2*oE + 2*oT + i;
		txEdge *E0__ = nedges[e0__];
		txEdge *E1__ = nedges[e1__];
		txEdge *E2__ = nedges[e2__];

		//***************************************

		E0__->V[0] = m2; E0__->V[1] = m0;
		E0__->T[0] = i;  E0__->T[1] = t1;
		E1__->V[0] = m0; E1__->V[1] = m1;
		E1__->T[0] = i;  E1__->T[1] = t2;
		E2__->V[0] = m1; E2__->V[1] = m2;
		E2__->T[0] = i;  E2__->T[1] = t3;

		T1->E[0] = e0__;   T1->E[1] = e2_;   T1->E[2] = e0;   T1->A[0] = i;
		T1->V[0] = m0;     T1->V[1] = m2;    T1->V[2] = v0;
		T2->E[0] = e1__;   T2->E[1] = e0_;   T2->E[2] = e1;   T2->A[0] = i;
		T2->V[0] = m0;     T2->V[1] = m1;    T2->V[2] = v1;
		T3->E[0] = e2__;   T3->E[1] = e1_;   T3->E[2] = e2;   T3->A[0] = i;
		T3->V[0] = m2;     T3->V[1] = m1;    T3->V[2] = v2;

	}
}

void txBasicMesh::UpdateOuter3TriConnectivity()
{
	for (size_t i=0; i<oT; i++)
	{

	}
}

void txBasicMesh::UpdateMiddleVertexValances()
{

}

void txBasicMesh::UpdateT0()
{

}

void txBasicMesh::UpdateOVertexValances()
{

}

txPoint3 txBasicMesh::CalculateMiddlePoint(txPoint3 &p0, txPoint3 &p1)
{
	txPoint3 p;

	assert(true);
	return p;
}
