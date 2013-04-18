#pragma once
#include "importexport.h"

class TXSHAPE_API txFrustum
{
public:
	txFrustum(double topRadius, double bottomRadius, double height);
	~txFrustum(void);

	double Height() { return height; };
	double TopRadius() { return topRadius; };
	double BottomRadius() { return bottomRadius; };

private:
	double topRadius;
	double bottomRadius;
	double height;
};

