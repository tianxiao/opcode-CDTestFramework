#pragma once
#include "importsymble.h"

class txTriSurfaceData;

// TODO current radius is default 1.0
SUBDIVISIONTESSELL_API int txTessellateSphere(const double radius, const int refinement_level, int is_solid_inside, txTriSurfaceData *&surf);
SUBDIVISIONTESSELL_API int txTessellateSphereRelease(txTriSurfaceData *surf);