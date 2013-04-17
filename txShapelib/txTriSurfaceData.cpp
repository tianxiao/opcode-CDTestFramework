#include "StdAfx.h"
#include "txTriSurfaceData.h"
#include <assert.h>


txTriSurfaceData::txTriSurfaceData(void)
{
}


txTriSurfaceData::~txTriSurfaceData(void)
{
}

txTriSurfaceData::txTriSurfaceData(txVector3 *v,int numv, int *indexes,int numi)
{
	assert(v!=NULL && indexes!=NULL && numv>0 && numi>0);
	this->verts.reserve(numv);
	this->indexes.reserve(numi);

	this->verts.assign(v,v+numv);
	this->indexes.assign(indexes,indexes+numi);
}
