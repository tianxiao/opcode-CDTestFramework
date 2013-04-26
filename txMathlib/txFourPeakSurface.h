#pragma once
#include "importexport.h"


class TXMATH_API txFourPeakSurfaceFun
{
public:
	txFourPeakSurfaceFun(void);
	~txFourPeakSurfaceFun(void);
};

double TXMATH_API txFourPeakFunO(double x, double y);

// See the functor here I cannot pass in a parameter
// just hard code the z into this function
/**
* Empty funciton return zero!
*/
double TXMATH_API txPlaneSurfaceFun(double x, double y);

