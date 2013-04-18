#pragma once
#include "importsymble.h"

class txFrustum;
class txTriSurfaceData;

class SUBDIVISIONTESSELL_API txFrustumSubdivision
{
public:
	txFrustumSubdivision(txFrustum* frustum, size_t level, size_t initialLevel=4);
	~txFrustumSubdivision(void);

	void Subdivision();

	txTriSurfaceData *GetTriSurfData() { return surf; };

private:
	const size_t initialmeshsize; // The top or bottom circle will be divided!
	size_t level;
	txFrustum* frustum;
	txTriSurfaceData *surf;
};

