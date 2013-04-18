#include "StdAfx.h"
#include <assert.h>
#include "txFrustumSubdivision.h"
#include "../txShapelib/txFrustum.h"
#include "../txShapelib/txTriSurfaceData.h"
#include "../txGeometrylib/txVector3.h"
#include "../txMathlib/txMathConstant.h"
#include "../txCore/txMemoryUtil.h"

void SubdividCircle(double radius, double height, size_t num, std::vector<txVector3> &verts){
	//const double dtheta = txMathConstant::M_PI/(this->level*this->initialmeshsize);
	const double dtheta = 2*txMathConstant::M_PI/num;
	double theta = 0;
	for (size_t i=0; i<num; i++) {
		txVector3 point;
		point.x = radius * cos(theta);
		point.y = radius * sin(theta);
		point.z = height;
		verts.push_back(point);
		theta+=dtheta;
	}
}



txFrustumSubdivision::txFrustumSubdivision(txFrustum* frustum, size_t level, size_t initialLevel)
	:initialmeshsize(initialLevel)
{
	assert(frustum);
	this->frustum = frustum;
	this->surf = new txTriSurfaceData;
	this->level = level;
}


txFrustumSubdivision::~txFrustumSubdivision(void)
{
	txMemoryUtil::txDelete(surf);
}

/**
* Here is just a simple implementation, If we going to 
* consider equal size tri need more work. 
* It is just a OFF version of the tesselate
**/
void txFrustumSubdivision::Subdivision()
{
	size_t topPointsNum, bottomPointsNum;
	topPointsNum = bottomPointsNum = this->level*this->initialmeshsize + 1;
	size_t topTriNum = topPointsNum - 1;
	size_t bottomTriNum  = bottomPointsNum - 1;
	size_t beltTriNum = 2*topTriNum;
	size_t trinum = topTriNum + beltTriNum + bottomTriNum;

	surf->AllocateVerts(topPointsNum + bottomPointsNum);
	surf->AllocateIndexes(trinum*3);
	std::vector<txVector3> &verts = surf->GetVerts();
	std::vector<int> &indexes = surf->GetIndexes();

	txVector3 topCenterPoint(0.0, 0.0, this->frustum->Height());
	verts.push_back(topCenterPoint);
	SubdividCircle(frustum->TopRadius(), frustum->Height(),this->level*this->initialmeshsize, verts);
	
	txVector3 bottomCenterPoint(0.0, 0.0, 0.0);
	verts.push_back(bottomCenterPoint);
	SubdividCircle(frustum->BottomRadius(), 0.0, this->level*this->initialmeshsize, verts);

	// contruct OFF format indexes;
	for (size_t i=0; i<topTriNum-1; i++) {
		indexes.push_back(0);
		indexes.push_back(i+1);
		indexes.push_back(i+2);
	}
	indexes.push_back(0);
	indexes.push_back(topPointsNum-1);
	indexes.push_back(1);


	/**
	*   i0------i3
	*    | t1 ' |
	*    |  ' t2|
	*   i1------i2
	**/
	for (size_t i=0; i<topTriNum-1; i++) {
		size_t i0, i1, i2, i3;
		i0 = i+1; // 1 for the top center point
		i1 = i+topPointsNum+1; // 1 for the bottom center point
		i2 = i+topPointsNum+2;
		i3 = i+2;
		indexes.push_back(i0); indexes.push_back(i1); indexes.push_back(i3);
		indexes.push_back(i1); indexes.push_back(i2); indexes.push_back(i3);
	}
	size_t i0, i1, i2, i3;
	i0 = topPointsNum-1;					// last  point index of top circle
	i1 = topPointsNum+bottomPointsNum-1;	// last  point index of bottom circle
	i2 = topPointsNum+1;					// first point index of bottom circle;
	i3 = 1;									// first point index of top circle
	indexes.push_back(i0); indexes.push_back(i1); indexes.push_back(i3);
	indexes.push_back(i1); indexes.push_back(i2); indexes.push_back(i3);


	for (size_t i=0; i<bottomTriNum-1; i++) {
		indexes.push_back(topPointsNum);
		// surface out! 
		indexes.push_back(topPointsNum+i+2);
		indexes.push_back(topPointsNum+i+1); // 1 same as top
	}
	// the last bit the head
	indexes.push_back(topPointsNum);
	indexes.push_back(topPointsNum+1);
	indexes.push_back(topPointsNum+bottomPointsNum-1);
}