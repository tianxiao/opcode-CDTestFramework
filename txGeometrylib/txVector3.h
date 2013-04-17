#pragma once
#include "importexport.h"


class TXGEOMETRY_API txVector3
{
public:
	double x,y,z;
public:
	txVector3(void);
	~txVector3(void);

	txVector3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {};
	txVector3(double a[3]): x(a[0]), y(a[1]), z(a[2]) {};

	
};

