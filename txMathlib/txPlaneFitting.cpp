#include "StdAfx.h"
#include "txPlaneFitting.h"

#include <assert.h>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

/**
* Algorithm based on the Matlab code:
* http://stackoverflow.com/questions/10900141/fast-plane-fitting-to-many-points
* SVD Description from wiki
* http://en.wikipedia.org/wiki/Singular_value_decomposition
* I use the Eigen's SVD 
* http://eigen.tuxfamily.org/dox/classEigen_1_1JacobiSVD.html#details
* And here is another C implementation in case needed!
* http://www.public.iastate.edu/~dicook/JSS/paper/code.html
*/
void txFittingPlane(double ptns[], int nPtns, double &a, double &b, double &c, double &d)
{
	assert(nPtns>=3);
	MatrixXd A(nPtns,4);
	int base;
	for (int i=0; i<nPtns; i++) {
		base = i*3;
		A(i,0) = ptns[base];
		A(i,1) = ptns[base+1];
		A(i,2) = ptns[base+2];
		A(i,3) = 1.0;
	}

	MatrixXd r = A.jacobiSvd(ComputeThinU | ComputeThinV).matrixV();
	a = r(0,3);
	b = r(1,3);
	c = r(2,3);
	d = r(3,3);
}