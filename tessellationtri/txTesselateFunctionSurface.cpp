#include "StdAfx.h"
#include "txTesselateFunctionSurface.h"

#include <assert.h>

#include "../txShapelib/txTriSurfaceData.h"
#include "../txCore/txMemoryUtil.h"
#include "../txGeometrylib/txVector3.h"


txRectangleAreaTesselate::txRectangleAreaTesselate(int numxgrid/*=40*/, int numygrid/*=40*/,double xscale/*=1.0*/, double yscale/*=1.0*/)
{
	assert(xscale>0.0);
	assert(yscale>0.0);
	xl = 1.0*xscale;
	yl = 1.0*yscale;
	this->numx = numxgrid;
	this->numy = numygrid;

	this->meshdata = new txTriSurfaceData();

	TesselateRectangleRegion();
}


txRectangleAreaTesselate::~txRectangleAreaTesselate(void)
{
	txMemoryUtil::txDelete(this->meshdata);
}

void txRectangleAreaTesselate::TesselateRectangleRegion()
{
	assert(this->meshdata);
	int numverts = this->numx*this->numy;
	int numfaces = (this->numx-1)*(this->numy-1)*2;
	this->meshdata->AllocateVerts(numverts);
	this->meshdata->AllocateIndexes(numfaces*3);

	AssignVerts();
	AssignFaces();
}



void txRectangleAreaTesselate::AssignVerts()
{
	double xInterval = (1.0*xl)/(numx-1);
	double yInterval = (1.0*yl)/(numy-1);

	for (int j=0; j<numy; j++) {
		for (int i=0; i<numx; i++) {
			txVector3 v;
			v.x = xInterval*i;
			v.y = yInterval*j;
			v.z = 0.0;
			this->meshdata->GetVerts().push_back(v);
		}
	}
}

void txRectangleAreaTesselate::AssignFaces()
{
	int tl, bl, tr, br;
	for (int j=0; j<numy-1; j++) {
		for (int i=0; i<numx-1; i++) {
			bl = GetVertsIndexFromXYIndex(i,j);
			br = GetVertsIndexFromXYIndex(i+1,j);
			tl = GetVertsIndexFromXYIndex(i,j+1);
			tr = GetVertsIndexFromXYIndex(i+1,j+1);
			
			this->meshdata->GetIndexes().push_back(bl);
			this->meshdata->GetIndexes().push_back(tr);
			this->meshdata->GetIndexes().push_back(tl);

			this->meshdata->GetIndexes().push_back(bl);
			this->meshdata->GetIndexes().push_back(br);
			this->meshdata->GetIndexes().push_back(tr);
		}
	}
}
