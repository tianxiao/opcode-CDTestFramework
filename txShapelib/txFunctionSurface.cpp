#include "StdAfx.h"
#include "txFunctionSurface.h"
#include <vector>
#include "txTriSurfaceData.h"
#include "../txGeometrylib/txVector3.h"




txFunctionSurface::~txFunctionSurface(void)
{
}

void txFunctionSurface::operator()(txTriSurfaceData *meshdata)
{
	double scalex = std::get<1>(xrange) - std::get<0>(xrange);
	double scaley = std::get<1>(yrange) - std::get<0>(yrange);

	double centerx = scalex/2.0;
	double centery = scaley/2.0;

	std::vector<txVector3> &verts = meshdata->GetVerts();
	for (size_t i=0; i<verts.size(); i++) {
		txVector3 &v = verts[i];
		v.x = v.x*scalex-centerx;
		v.y = v.y*scaley-centery;
		v.z = this->f(v.x, v.y);
	}
}
