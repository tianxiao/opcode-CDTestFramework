#include "StdAfx.h"
#include "txTriSurfaceData.h"
#include <assert.h>


txTriSurfaceData::txTriSurfaceData(void)
{
}


txTriSurfaceData::~txTriSurfaceData(void)
{
}

txTriSurfaceData::txTriSurfaceData(txTriSurfaceData *md)
{
	this->verts = md->verts;
	this->indexes = md->indexes;
}

txTriSurfaceData::txTriSurfaceData(txVector3 *v,int numv, int *indexes,int numi)
{
	assert(v!=NULL && indexes!=NULL && numv>0 && numi>0);
	this->verts.reserve(numv);
	this->indexes.reserve(numi);

	this->verts.assign(v,v+numv);
	this->indexes.assign(indexes,indexes+numi);
}

void txTriSurfaceData::DumpFile(char *filename)
{
	FILE *f = fopen(filename, "w");

	fprintf(f,"OFF\n");

	fprintf(f,"%d\t%d\t%d\n",verts.size(),indexes.size()/3,0);

	for (size_t i=0; i<verts.size(); i++) {
		fprintf(f,"%f\t%f\t%f\n",verts[i].x,verts[i].y,verts[i].z);
	}

	for (size_t i=0; i<indexes.size()/3; i++) {
		fprintf(f,"%d\t%d\t%d\t%d\n",3,
			indexes[i*3],
			indexes[i*3+1],
			indexes[i*3+2]);
	}


	fclose(f);
}