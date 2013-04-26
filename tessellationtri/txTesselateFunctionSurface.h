#pragma once
#include "importsymble.h"

class txTriSurfaceData;

/**
* This is a rectangle region and the function z=f(x,y)
* give the unified grid x, y, calculate the z.
*/
class SUBDIVISIONTESSELL_API txRectangleAreaTesselate
{
public:
	txRectangleAreaTesselate(int numxgrid=30, int numygrid=30, double xscale=1.0, double yscale=1.0);
	~txRectangleAreaTesselate(void);

	txTriSurfaceData *GetTriSurfData() { return  meshdata; };


private:
	void TesselateRectangleRegion();
	int GetVertsIndexFromXYIndex(int xIndex, int yIndex) { 
		int vertIndex = 0;
		vertIndex = yIndex*numx + xIndex;
		return vertIndex;
	};

	

	void AssignVerts();
	void AssignFaces();


private:
	double xl;
	double yl;
	int numx; // number of x nodes
	int numy; // number of y nodes

	txTriSurfaceData *meshdata;
};

