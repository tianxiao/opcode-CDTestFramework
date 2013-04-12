#pragma once
#include <vector>

typedef struct
{
	double x,y,z;
}txPoint3;

typedef struct
{
	size_t pointId;
	size_t numEdges;
	size_t edgeIds[6]; // The initial mesh only have the necessary valances
}txVertex;

typedef struct
{
	size_t V[2];
	size_t T[2];
}txEdge;

typedef struct
{
	size_t V[3];
	size_t E[3];  // e0=<v0,v1>, e1=<v1,v2>, e2=<v2,v2>
	size_t A[3];  // ajd[i] shares e[i] with the triangle
} txTriangle;

class txQuaterTriCfg
{
public:
	txQuaterTriCfg(	
		std::vector<txVertex*> &overtices_,
		std::vector<txEdge*> &oedges_,
		std::vector<txTriangle*> &otriangles_,
		std::vector<txVertex*> &nvertices_,
		std::vector<txEdge*> &nedges_,
		std::vector<txTriangle*> &ntriangles_)
		:overtices(overtices_)
		,oedges(oedges_)
		,otriangles(otriangles_)
		,nvertices(nvertices_)
		,nedges(nedges_)
		,ntriangles(ntriangles_)
	{}


public:
	void ConstructInternalVETIndex(size_t i){
		this->i = i;

		//***************************************

		T0 = otriangles[i];
		
		v0 = T0->V[0]; v1 = T0->V[1]; v2 = T0->V[2];
		
		V0 = overtices[v0];
		V1 = overtices[v1];
		V2 = overtices[v2];

		
		e0 = T0->E[0]; e1 = T0->E[1]; e2 = T0->E[2];
		
		E0= oedges[e0];
		E1 = oedges[e1];
		E2 = oedges[e2];

		
		m0 = oV + e0; m1 = oV + e1; m2 = oV + e2;
		
		M0= nvertices[m0];
		M1 = nvertices[m1];
		M2 = nvertices[m2];

		
		e0_ = oE + e0; e1_ = oE + e1; e2_ = oE + e2;
		
		E0_= nedges[e0_];
		E1_ = nedges[e1_];
		E2_ = nedges[e2_];
		
		//---------------------------------------
		
		t1 = oT + i; t2 = oT*2 + i; t3 = oT*3 + i;
		
		T1= ntriangles[t1];
		T2 = ntriangles[t2];
		T3 = ntriangles[t3];

		
		e0__ = 2*oE +i; e1__ = 2*oE + oT + i; e2__ = 2*oE + 2*oT + i;
		
		E0__ = nedges[e0__];
		E1__ = nedges[e1__];
		E2__ = nedges[e2__];

		//***************************************
	}

	void UpdateNewTrianglesNewVerticesInOTriangle(){
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

public:
	// The following parameter should be sequenced in the construct
	// And they are construct cascaded
	txTriangle * T0, *T1, *T2, *T3;

	size_t v0, v1, v2;
	txVertex *V0, *V1, *V2;

	size_t e0, e1, e2;
	txEdge *E0, *E1, *E2;

	size_t m0, m1, m2;
	txVertex *M0, *M1, *M2;

	size_t e0_, e1_, e2_;
	txEdge *E0_, *E1_, *E2_;

	size_t t1, t2, t3;

	size_t e0__, e1__, e2__;
	txEdge *E0__, *E1__, *E2__;

public:
	// original level
	size_t oV;
	size_t oE;
	size_t oT;

	std::vector<txVertex*> &overtices;
	std::vector<txEdge*> &oedges;
	std::vector<txTriangle*> &otriangles;

	// next level
	size_t nV;
	size_t nE;
	size_t nT;

	std::vector<txVertex*> &nvertices;
	std::vector<txEdge*> &nedges;
	std::vector<txTriangle*> &ntriangles;

	size_t i;// original triangle index

};

class txBasicMesh
{
public:
	txBasicMesh(void);
	~txBasicMesh(void);

	void SubdivsionMesh();

private:
	void AllocatePVET();
	void DeallocatePVET();

	void IterateOEdgesCreateNewMiddleVertex();
	void IterateOTrianglesCreateNewTrisEdges();
	void UpdateOuter3TriConnectivity();
	void UpdateMiddleVertexValances();
	void UpdateT0();
	void UpdateOVertexValances();

	txPoint3 CalculateMiddlePoint(txPoint3 &p0, txPoint3 &p1);

private:
	// TODO need to be a struct wrapper will replace by txQuaterTriCfg
	size_t oV;
	size_t oE;
	size_t oT;

	std::vector<txPoint3> opoints;
	std::vector<txVertex*> overtices;
	std::vector<txEdge*> oedges;
	std::vector<txTriangle*> otriangles;

	// next level
	size_t nV;
	size_t nE;
	size_t nT;

	std::vector<txPoint3> npoints;
	std::vector<txVertex*> nvertices;
	std::vector<txEdge*> nedges;
	std::vector<txTriangle*> ntriangles;
};

