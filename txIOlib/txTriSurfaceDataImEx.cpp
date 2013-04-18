#include "StdAfx.h"
#include <stdlib.h>
#include <stdio.h>
#include "txTriSurfaceDataImEx.h"
#include "../txGeometrylib/txVector3.h"
#include "../txShapelib/txTriSurfaceData.h"

#pragma warning (disable:4996) 

txTriSurfaceDataImEx::txTriSurfaceDataImEx(void)
{
}


txTriSurfaceDataImEx::~txTriSurfaceDataImEx(void)
{
}

void txTriSurfaceDataImEx::ExportToOFFFile(txTriSurfaceData *surf, char *filename)
{
	std::vector<txVector3> &verts = surf->GetVerts();
	std::vector<int> &indexes = surf->GetIndexes();

	FILE *f = fopen(filename, "w");

	fprintf(f,"OFF\n");

	fprintf(f,"%d\t%d\t%d\n",verts.size(), indexes.size()/3,0);

	for (size_t i=0; i<verts.size(); i++) {
		fprintf(f,"%f\t%f\t%f\n",verts[i].x,verts[i].y,verts[i].z);
	}

	for (size_t i=0; i<indexes.size(); ) {
		fprintf(f,"%d\t%d\t%d\t%d\n",3,
			indexes[i++],
			indexes[i++],
			indexes[i++]);
	}


	fclose(f);
}
