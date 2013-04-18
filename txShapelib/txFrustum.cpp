#include "StdAfx.h"
#include "txFrustum.h"


txFrustum::txFrustum(double topRadius, double bottomRadius, double height)
{
	this->topRadius = topRadius;
	this->bottomRadius = bottomRadius;
	this->height = height;
}


txFrustum::~txFrustum(void)
{
}
