#pragma once
#include "stdafx.h"
#include "txBasicMesh.h"

/**
* It's a query API, it does not update(change) the triangle connectivity!
**/
void txQuaterTriCfg::ConstructInternalVETIndex(size_t i){
	this->i = i;

	//***************************************

	T0 = ntriangles[i];
		
	v0 = T0->V[0]; v1 = T0->V[1]; v2 = T0->V[2];
		
	V0 = nvertices[v0];
	V1 = nvertices[v1];
	V2 = nvertices[v2];

		
	e0 = T0->E[0]; e1 = T0->E[1]; e2 = T0->E[2];
		
	E0 = nedges[e0];
	E1 = nedges[e1];
	E2 = nedges[e2];

		
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

void txQuaterTriCfg::UpdateNewTrianglesNewVerticesInOTriangle(){
	E0__->V[0] = m2; E0__->V[1] = m0;
	E0__->T[0] = i;  E0__->T[1] = t1;
	E1__->V[0] = m0; E1__->V[1] = m1;
	E1__->T[0] = i;  E1__->T[1] = t2;
	E2__->V[0] = m1; E2__->V[1] = m2;
	E2__->T[0] = i;  E2__->T[1] = t3;

	T1->E[0] = e0__;   T1->E[1] = e2_;   T1->E[2] = e0;   T1->A[0] = i;
	T1->V[0] = m0;     T1->V[1] = m2;    T1->V[2] = v0;
	T2->E[0] = e1__;   T2->E[1] = e0_;   T2->E[2] = e1;   T2->A[0] = i;
	T2->V[0] = m0;     T2->V[1] = v1;    T2->V[2] = m1;
	T3->E[0] = e2__;   T3->E[1] = e1_;   T3->E[2] = e2;   T3->A[0] = i;
	T3->V[0] = m2;     T3->V[1] = m1;    T3->V[2] = v2;
}


void txQuaterTriCfg::UpdateOuter3TriConnectivity(txQuaterTriCfg *t, txQuaterTriCfg *a){
	//outerupdatecount=0;
	size_t counter = 0;
	if (UpdateOuter3Tri23Connectivity(t,a)) {
		counter++;
	}
	if (UpdateOuter3Tri31Connectivity(t,a)) {
		counter++;
	}
	if (UpdateOuter3Tri12Connectivity(t,a)) {
		counter++;
	}
	// The configure must and only have one match
	// So the outerupdatecount will alway be one after update!
	assert(counter!=2);
	assert(counter!=3);
	assert(counter!=0);
}

/**
* This function should be called after the UpdateOuter3TriConnectivity is called,
* UpdateOuter3TriConnectivity construct the full triangle adjacent triangles which
* need in this function.
*/
void txQuaterTriCfg::UpdateOuterSplitEdgesConnectivity(txQuaterTriCfg *t){
	//// TODO!!!
	//assert(false);
	t->E2_->T[0] = t->t1;
	t->E2_->T[1] = t->T1->A[1];
	t->E2->T[0]  = t->t3;
	t->E2->T[1]  = t->T3->A[2];

	t->E1_->T[0] = t->t3;
	t->E1_->T[1] = t->T3->A[1];
	t->E1->T[0]  = t->t2;
	t->E1->T[1]  = t->T2->A[2];

	t->E0->T[0]  = t->t1;
	t->E0->T[1]  = t->T1->A[2];
	t->E0_->T[0] = t->t2;
	t->E0_->T[1] = t->T2->A[1];
}

void txQuaterTriCfg::UpdateMiddleVertexValances(txQuaterTriCfg *t) {
	//txVertex *M[] = {t->M0, t->M1, t->M2};
	//for (size_t i=0; i<3; i++) {
	//	if (M[i]->numEdges == 0) {
	//		M[i]->numEdges = 4;
	//	}
	//}
	txVertex *M0, *M1, *M2;
	M0 = t->M0; M1 = t->M1; M2 = t->M2;

	if (M0->numEdges==0) {
		M0->numEdges = 4;
		M0->edgeIds[0] = t->e0_;
		M0->edgeIds[1] = t->e1__;
		M0->edgeIds[2] = t->e0__;
		M0->edgeIds[3] = t->e0;
	} else if (M0->numEdges==4) {
		M0->numEdges = 6;
		M0->edgeIds[4] = t->e0__;
		M0->edgeIds[5] = t->e1__;
	}

	if (M2->numEdges==0) {
		M2->numEdges = 4;
		M2->edgeIds[0] = t->e2_;
		M2->edgeIds[1] = t->e0__;
		M2->edgeIds[2] = t->e2__;
		M2->edgeIds[3] = t->e2;
	} else if (M2->numEdges==4){
		M2->numEdges = 6;
		M2->edgeIds[4] = t->e2__;
		M2->edgeIds[5] = t->e0__;
	}

	if (M1->numEdges==0) {
		M1->numEdges = 4;
		M1->edgeIds[0] = t->e1_;
		M1->edgeIds[1] = t->e2__;
		M1->edgeIds[2] = t->e1__;
		M1->edgeIds[3] = t->e1;
	} else if (M1->numEdges==4) {
		M1->numEdges = 6;
		M1->edgeIds[4] = t->e1__;
		M1->edgeIds[5] = t->e2__;
	}
}

bool txQuaterTriCfg::UpdateOuter3Tri23Connectivity(txQuaterTriCfg *t, txQuaterTriCfg *a){
		
	if(t->v2==a->v0 && t->v1==a->v1) {
		t->T2->A[2] = a->t2;
		t->T3->A[1] = a->t1;
		a->T2->A[1] = t->t2;
		a->T1->A[2] = t->t3;
		//outerupdatecount++;
		return true;
	}

	if(t->v2==a->v1 && t->v1==a->v2 ) {
		t->T2->A[2] = a->t3;
		t->T3->A[1] = a->t2;
		a->T3->A[1] = t->t2;
		a->T2->A[2] = t->t3;
		//outerupdatecount++;
		return true;
	}

	if(t->v2==a->v2 && t->v1==a->v0 ) {
		t->T2->A[2] = a->t1;
		t->T3->A[1] = a->t3;
		a->T1->A[1] = t->t2;
		a->T3->A[2] = t->t3;
		//outerupdatecount++;
		return true;
	}
	return false;

}

bool txQuaterTriCfg::UpdateOuter3Tri31Connectivity(txQuaterTriCfg *t, txQuaterTriCfg *a){
	//assert(false);
	//// TODO!!!	
	if(t->v0==a->v0 && t->v2==a->v1) {
		t->T1->A[1] = a->t1;
		t->T3->A[2] = a->t2;
		a->T1->A[2] = t->t1;
		a->T2->A[1] = t->t3;
		return true;
	}

	if(t->v0==a->v1 && t->v2==a->v2) {
		t->T1->A[1] = a->t2;
		t->T3->A[2] = a->t3;
		a->T2->A[2] = t->t1;
		a->T3->A[1] = t->t3;
		return true;
	}

	if(t->v0==a->v2 && t->v2==a->v0) {
		t->T1->A[1] = a->t3;
		t->T3->A[2] = a->t1;
		a->T1->A[1] = t->t3;
		a->T3->A[2] = t->t1;
		return true;
	}
	return false;
}

bool txQuaterTriCfg::UpdateOuter3Tri12Connectivity(txQuaterTriCfg *t, txQuaterTriCfg *a){
	//assert(false);
	//// TODO!!!
	if(t->v0==a->v1 && t->v1==a->v0) {
		t->T1->A[2] = a->t2;
		t->T2->A[1] = a->t1;
		a->T2->A[1] = t->t1;
		a->T1->A[2] = t->t2;
		return true;
	}

	if(t->v0==a->v2 && t->v1==a->v1) {
		t->T1->A[2] = a->t3;
		t->T2->A[1] = a->t2;
		a->T3->A[1] = t->t1;
		a->T2->A[2] = t->t2;
		return true;
	}

	if(t->v0==a->v0 && t->v1==a->v2) {
		t->T1->A[2] = a->t1;
		t->T2->A[1] = a->t3;
		a->T1->A[2] = t->t1;
		a->T3->A[1] = t->t2;
		return true;
	}

	return false;
}