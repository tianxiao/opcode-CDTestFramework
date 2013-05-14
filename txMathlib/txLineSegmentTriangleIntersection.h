#pragma once
#include "importexport.h"


// ray triangle intersect
int TXMATH_API IntersectTriangle(double orig[3], double dir[3],
	double vert0[3], double vert1[3], double vert2[3],
	double *t, double *u, double *v);

// segment triangle intersect
int TXMATH_API SegmentTriangleIntersection(
	double start[3], double end[3], double v0[3], double v1[3], double v2[3],
	double *u, double *v);

// brutal force traingle triangle intersection point routine
// the opc detect which two triangle have been collide, this triangle give 
// the interferene segment
void TXMATH_API TriangleTriangleIntersection(
	double vert00[3], double vert01[3], double vert02[3],
	double vert10[3], double vert11[3], double vert12[3],
	double s[3], double e[3]);

/**
* Second version that use the line plane intersection then compare thoese 
* four intersection points by projecting to the same axis the two triangles
* determined plane intersection direction L
*/
void TXMATH_API TriangleTriangleIntersectionM2(
	double vert00[3], double vert01[3], double vert02[3],
	double vert10[3], double vert11[3], double vert12[3],
	double s[3], double e[3]);

int TXMATH_API SegmentPlaneIntersection(
	double orig[3], double dest[3],
	double vert0[3], double vert1[3], double vert2[3],
	double p[3]
	);

int TXMATH_API SegmentPlaneIntersection(
	double orig[3], double dest[3],
	double vert0[3], double vert1[3], double vert2[3],
	double *u, double *v
	);


