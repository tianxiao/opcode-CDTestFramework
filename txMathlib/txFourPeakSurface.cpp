#include "StdAfx.h"
#include "txFourPeakSurface.h"
#include <math.h>


txFourPeakSurfaceFun::txFourPeakSurfaceFun(void)
{
}


txFourPeakSurfaceFun::~txFourPeakSurfaceFun(void)
{
}

/**
Input the following cmd into gunplot you got a visualized surface
set xrange [-2:2]
set yrange [-2:2]
set pm3d at b
set ticslevel 0.8
set isosample 40, 40
splot -x*x*exp(-x*x)*y*y*exp(-y*y)
*/
double txFourPeakFunO(double x, double y)
{
	double rtn = -10*x*x*exp(-x*x)*y*y*exp(-y*y)+1;
	return rtn;
}

double txPlaneSurfaceFun(double x, double y)
{
	return 0.0;
}
