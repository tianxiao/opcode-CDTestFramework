#pragma once
#include "importexport.h"
/**
* http://stackoverflow.com/questions/10900141/fast-plane-fitting-to-many-points
* normal [a,b,c] distance from original -d
*/
void TXMATH_API txFittingPlane(double ptns[], int nPtns, double &a, double &b, double &c, double &d);