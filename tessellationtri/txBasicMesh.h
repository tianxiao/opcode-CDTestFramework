#pragma once
#include <vector>
#include <assert.h>
#include "importsymble.h"

#pragma warning (disable:4251)

typedef SUBDIVISIONTESSELL_API struct
{
	double x,y,z;
}txPoint3;

typedef SUBDIVISIONTESSELL_API struct
{
	size_t pointId;
	size_t numEdges;
	size_t edgeIds[6]; // The initial mesh only have the necessary valances
}txVertex;

typedef SUBDIVISIONTESSELL_API struct
{
	size_t T[2];
	size_t V[2];
}txEdge;

typedef SUBDIVISIONTESSELL_API struct
{
	size_t V[3];
	size_t E[3];  // e0=<v0,v1>, e1=<v1,v2>, e2=<v2,v2>
	size_t A[3];  // ajd[i] shares e[i] with the triangle
} txTriangle;

class SUBDIVISIONTESSELL_API txQuaterTriCfg
{
public:
	txQuaterTriCfg(	
		size_t oV_,
		size_t oE_,
		size_t oT_,
		std::vector<txVertex*> &nvertices_,
		std::vector<txEdge*> &nedges_,
		std::vector<txTriangle*> &ntriangles_)
		:oV(oV_)
		,oE(oE_)
		,oT(oT_)
		,nvertices(nvertices_)
		,nedges(nedges_)
		,ntriangles(ntriangles_)
	{}


	txQuaterTriCfg* DeepCopy()
	{
		return new txQuaterTriCfg(
			this->oV,
			this->oE,
			this->oT,
			this->nvertices,
			this->nedges,
			this->ntriangles);
	}


public:
	/**
	* It's a query API, it does not update(change) the triangle connectivity!
	**/
	void ConstructInternalVETIndex(size_t i);

	void UpdateNewTrianglesNewVerticesInOTriangle();

//// only for debug
//private:
//	static size_t outerupdatecount;

public:
	void static UpdateOuter3TriConnectivity(txQuaterTriCfg *t, txQuaterTriCfg *a);

	/**
	* This function should be called after the UpdateOuter3TriConnectivity is called,
	* UpdateOuter3TriConnectivity construct the full triangle adjacent triangles which
	* need in this function.
	*/
	void static UpdateOuterSplitEdgesConnectivity(txQuaterTriCfg *t);

	void static UpdateMiddleVertexValances(txQuaterTriCfg *t) ;

private:
	bool static UpdateOuter3Tri23Connectivity(txQuaterTriCfg *t, txQuaterTriCfg *a);

	bool static UpdateOuter3Tri31Connectivity(txQuaterTriCfg *t, txQuaterTriCfg *a);

	bool static UpdateOuter3Tri12Connectivity(txQuaterTriCfg *t, txQuaterTriCfg *a);

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


	// next level
	size_t nV;
	size_t nE;
	size_t nT;

	std::vector<txVertex*> &nvertices;
	std::vector<txEdge*> &nedges;
	std::vector<txTriangle*> &ntriangles;

	size_t i;// original triangle index

};

typedef SUBDIVISIONTESSELL_API struct {
	size_t oV;
	size_t oE;
	size_t oT;

	std::vector<txPoint3> opoints;
	std::vector<txVertex*> overtices;
	std::vector<txEdge*> oedges;
	std::vector<txTriangle*> otriangles;

} MeshData;

void SUBDIVISIONTESSELL_API MeshDataConfigOct(MeshData *meshdata);
void SUBDIVISIONTESSELL_API MeshDataReleaseOct(MeshData *meshdata);

void SUBDIVISIONTESSELL_API MeshDataConfigTetra(MeshData *meshdata);
void SUBDIVISIONTESSELL_API MeshDataReleaseTetra(MeshData *meshdata);


class SUBDIVISIONTESSELL_API txBasicMesh
{
public:
	txBasicMesh(void);
	~txBasicMesh(void);

	txBasicMesh(MeshData* meshdata) ;

	void SubdivsionMesh();

private:
	void AllocatePVET();
	void DeallocatePVET();

	// Assign the original mesh info to the subdivision mesh
	void CopyO2N();

	void IterateOEdgesCreateNewMiddleVertex();
	void IterateOTrianglesCreateNewTrisEdges();
	void UpdateOuter3TriConnectivity();
	void UpdateOuterSplitEdgesConnectivity();
	void UpdateMiddleTriConnectivity();
	void UpdateMiddleTriConnectivity(txQuaterTriCfg *t, size_t i);
	void UpdateOVertexValances();

	txPoint3 CalculateMiddlePoint(txPoint3 &p0, txPoint3 &p1);

private:
	// TODO need to be a struct wrapper will replace by txQuaterTriCfg
	size_t oV;
	size_t oE;
	size_t oT;
	MeshData *meshdata;

	// next level
	size_t nV;
	size_t nE;
	size_t nT;

	std::vector<txPoint3> npoints;
	std::vector<txVertex*> nvertices;
	std::vector<txEdge*> nedges;
	std::vector<txTriangle*> ntriangles;

	txQuaterTriCfg *triCfg;
};




