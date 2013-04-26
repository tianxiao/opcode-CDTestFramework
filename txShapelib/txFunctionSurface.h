#pragma once
#include "importexport.h"

#include <tuple>

typedef double (*SurFun) (double x, double y);
class txTriSurfaceData;

#pragma warning (disable:4251)

/**
* This function surface class re-assign the mesh area z value
* lift the plannar polygon into spacial surface.
* @para input a specific functor.
*/
class TXSHAPE_API txFunctionSurface
{
public:
	explicit txFunctionSurface(
		std::tuple<double, double> &xrange, 
		std::tuple<double, double> &yrange,
		SurFun f) 
		: f(f)
		, xrange(xrange)
		, yrange(yrange)
 {};
	~txFunctionSurface(void);

	void operator()(txTriSurfaceData *meshdata);

private:
	std::tuple<double, double> xrange;
	std::tuple<double, double> yrange;
	SurFun f;
	txTriSurfaceData *meshdata;
};

