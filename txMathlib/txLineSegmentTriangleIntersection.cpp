#include "StdAfx.h"
#include "txLineSegmentTriangleIntersection.h"

#include <math.h>
#include <assert.h>

/**
* The following code is from the 
* Fast, minimum storage ray-triangle intersection.
* Tomas Möller and Ben Trumbore. 
* http://www.graphics.cornell.edu/pubs/1997/MT97.html
*/

#define txSEGMENTTRIANGLE_EPSILON 0.000001

#define txCROSS(dest, v1, v2) \
	dest[0] = v1[1]*v2[2] - v1[2]*v2[1]; \
	dest[1] = v1[2]*v2[0] - v1[0]*v2[2]; \
	dest[2] = v1[0]*v2[1] - v1[1]*v2[0];

#define txDOT(v1, v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])

#define txSUB(dest, v1, v2)  \
	dest[0] = v1[0] - v2[0]; \
	dest[1] = v1[1] - v2[1]; \
	dest[2] = v1[2] - v2[2];

#define txVecDiv(ori,scale) \
	ori[0] = ori[0]/scale; \
	ori[1] = ori[1]/scale; \
	ori[2] = ori[2]/scale;

#define txCOPYVEC(to, from) \
	to[0] = from[0]; \
	to[1] = from[1]; \
	to[2] = from[2];

#define txSWAPVEC(v1, v2) \
	{ \
		double temp[3];\
		txCOPYVEC(temp,v1);\
		txCOPYVEC(v1,v2);\
		txCOPYVEC(v2,temp);\
	}

#define txSWAPSCALAR(a,b) \
	{\
		double temp = a;\
		a = b;\
		b = temp;\
	}


#define txBARYCENTRICVEC(V,v0,v1,v2,u,v) \
	for (int i=0; i<3; i++) { \
		V[i] = (1-u-v)*v0[i] + u*v1[i] + v*v2[i]; \
	}

#define txCHANGE(count,s,e,vs,ve,v0,v1,v2,u,v) \
	if(SegmentTriangleIntersection(vs,ve,v0,v1,v2,&u,&v)) {\
		if(count==0) {\
			txBARYCENTRICVEC(s,v0,v1,v2,u,v); \
			count++;\
		} else if (count==1){ \
			txBARYCENTRICVEC(e,v0,v1,v2,u,v); \
			count++;\
		}\
	}


int IntersectTriangle(
	double orig[3], double dir[3],
	double vert0[3], double vert1[3], double vert2[3],
	double *t, double *u, double *v)
{
	double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	double det, inv_det;

	// the triangle two edge
	txSUB(edge1,vert1,vert0);
	txSUB(edge2,vert2,vert0);

	txCROSS(pvec, dir,edge2);

	// If the det is zero then the ray is lay on the triangle
	det = txDOT(edge1, pvec);

	// The orignial code implement the triangle edge culling when 
	// the ray is on the triangle 

	if (det > -txSEGMENTTRIANGLE_EPSILON && det < txSEGMENTTRIANGLE_EPSILON) {
		return 0;
	}

	inv_det = 1.0/det;

	txSUB(tvec, orig, vert0);

	*u = txDOT(tvec, pvec)*inv_det;
	if (*u<0.0 || *u>1.0) return 0;

	txCROSS(qvec, tvec, edge1);

	*v = txDOT(dir, qvec)*inv_det;
	if (*v<0.0 || *u+*v>1.0) return 0;

	*t = txDOT(edge2, qvec)*inv_det;

	return 1;

}

int SegmentTriangleIntersection(double start[3], double end[3], double v0[3], double v1[3], double v2[3], double *u, double *v)
{
	double dir[3];
	txSUB(dir, start,end);
	double l = sqrt(txDOT(dir,dir));

	txVecDiv(dir,l);
	double t;
	int state = IntersectTriangle(start,dir,v0,v1,v2,&t,u,v);

	if (l>t && state) {
		return 1;
	}

	return 0;
}

void TriangleTriangleIntersection(
	double vert00[3], double vert01[3], double vert02[3],
	double vert10[3], double vert11[3], double vert12[3],
	double s[3], double e[3])
{
	int count = 0;
	double u, v;

	txCHANGE(count,s,e,vert00,vert01,vert10,vert11,vert12,u,v);
	txCHANGE(count,s,e,vert00,vert02,vert10,vert11,vert12,u,v);
	txCHANGE(count,s,e,vert02,vert01,vert10,vert11,vert12,u,v);

	txCHANGE(count, s, e, vert10, vert11, vert00, vert01, vert02, u, v);
	txCHANGE(count, s, e, vert10, vert12, vert00, vert01, vert02, u, v);
	txCHANGE(count, s, e, vert12, vert11, vert00, vert01, vert02, u, v);

	assert(count==2);
}

int SegmentPlaneIntersection(
	double orig[3], double dest[3],
	double vert0[3], double vert1[3], double vert2[3],
	double p[3]
	)
{
	double u,v;

	if (SegmentPlaneIntersection(orig,dest,vert0,vert1,vert2,&u,&v)) {
		txBARYCENTRICVEC(p,vert0,vert1,vert2,u,v);
		return 1;
	}

	return 0;
}


bool CheckVVLargeThanZero(double vv[3])
{
	if (vv[0]>0.0 || vv[1]>0.0 || vv[2]>0.0) return true;

	return false;
}

/**
* This version of ray plane intersection didn't like the SegmentTriangleIntersection test
* Which do not delay the intersection test, it calculate the u,v 
*/
int TXMATH_API SegmentPlaneIntersection(
	double orig[3], double dest[3],
	double vert0[3], double vert1[3], double vert2[3],
	double *u, double *v
	)
{
	double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	double det, inv_det;

	double dir[3];
	txSUB(dir, dest, orig);
	double l = sqrt(txDOT(dir,dir));

	txVecDiv(dir,l);
	double t;

	// the triangle two edge
	txSUB(edge1,vert1,vert0);
	txSUB(edge2,vert2,vert0);

	txCROSS(pvec, dir,edge2);

	// If the det is zero then the ray is lay on the triangle
	det = txDOT(edge1, pvec);

	// The orignial code implement the triangle edge culling when 
	// the ray is on the triangle 

	if (det > -txSEGMENTTRIANGLE_EPSILON && det < txSEGMENTTRIANGLE_EPSILON) {
		return 0;
	}

	inv_det = 1.0/det;

	txSUB(tvec, orig, vert0);

	*u = txDOT(tvec, pvec)*inv_det;
	//if (*u<0.0 || *u>1.0) return 0;

	txCROSS(qvec, tvec, edge1);


	*v = txDOT(dir, qvec)*inv_det;
	//if (*v<0.0 || *u+*v>1.0) return 0;

	t = txDOT(edge2, qvec)*inv_det;

	if (l<t) return 0;

	return 1;
}

void TXMATH_API TriangleTriangleIntersectionM2(
	double vert00[3], double vert01[3], double vert02[3],
	double vert10[3], double vert11[3], double vert12[3],
	double s[3], double e[3])
{
	// degenerating case like the two triangle lay in the same plannar
	// TODO!!!
	double p00[3], p01[3], p02[3], p10[3], p11[3], p12[3];
	int i00,i01,i02,i10,i11,i12;
	i00=i01=i02=i10=i11=i12=0;

	double edge00[3], edge01[3], edge10[3], edge11[3];
	txSUB(edge00,vert01,vert00);
	txSUB(edge01,vert02,vert00);
	txSUB(edge10,vert11,vert10);
	txSUB(edge11,vert12,vert10);
	double n0[3], n1[3], l[3];
	txCROSS(n0,edge00,edge01);
	txCROSS(n1,edge10,edge11);
	txCROSS(l,n0,n1);
	txVecDiv(l,sqrt(txDOT(l,l)));

	if (SegmentPlaneIntersection(vert00,vert01,vert10,vert11,vert12,p00)) {
		i00=1;
	}

	if (SegmentPlaneIntersection(vert00,vert02,vert10,vert11,vert12,p01)) {
		i01=1;
	}

	if (SegmentPlaneIntersection(vert02,vert01,vert10,vert11,vert12,p02)) {
		i02=1;
	}

	if (SegmentPlaneIntersection(vert10,vert11,vert00,vert01,vert02,p10)) {
		i10 = 1;
	}

	if (SegmentPlaneIntersection(vert10,vert12,vert00,vert01,vert02,p11)) {
		i11 = 1;
	}

	if (SegmentPlaneIntersection(vert12,vert11,vert00,vert01,vert02,p12)) {
		i12 = 1;
	}

	assert(i00+i01+i02+i10+i11+i12==4);

	double tp00[3], tp01[3], tp10[3], tp11[3];

	if (!i00) {
			txCOPYVEC(tp00,p01);
			txCOPYVEC(tp01,p02);
	} else if (!i01) {
			txCOPYVEC(tp00,p00);
			txCOPYVEC(tp01,p02);
	} else if (!i02) {
			txCOPYVEC(tp00,p00);
			txCOPYVEC(tp01,p01);			
	}

	if (!i10) {
			txCOPYVEC(tp10,p11);
			txCOPYVEC(tp11,p12);			
	} else if(!i11) {
			txCOPYVEC(tp10,p12);
			txCOPYVEC(tp11,p10);

	} else if(!i12) {
			txCOPYVEC(tp10,p10);
			txCOPYVEC(tp11,p11);			
	}

	double la00, la01, la10, la11;
	la00 = txDOT(l,tp00);
	la01 = txDOT(l,tp01);
	la10 = txDOT(l,tp10);
	la11 = txDOT(l,tp11);

	if (la00>la01) {
		txSWAPVEC(tp00,tp01);
		txSWAPSCALAR(la00,la01);
	}
	if (la10>la11) {
		txSWAPVEC(tp10,tp11);
		txSWAPSCALAR(la10,la11);
	}

	if ( la00>la10 ) {
		// assert means the input triangle pair must be intesected!!!
		assert( la01<la10 );

		if ( la11>la01 ) {
			txCOPYVEC(s,tp00);
			txCOPYVEC(e,tp01);
		} else {
			txCOPYVEC(s,tp00);
			txCOPYVEC(e,tp11);
		}
	} else {
		// assert means the input triangle pair must be intesected!!!
		assert( la00<la11 );

		if ( la11>la01 ) {
			txCOPYVEC(s,tp10);
			txCOPYVEC(e,tp01);
		} else {
			txCOPYVEC(s,tp10);
			txCOPYVEC(e,tp11);
		}
		
	}

}