#pragma once
#include "importexport.h"
#include <vector>
#include "../txGeometrylib/txVector3.h"

#pragma warning (disable:4251)

/**
* OFF format mesh CCW is the ther outer direction
**/
class TXSHAPE_API txTriSurfaceData
{
public:
	txTriSurfaceData(void);
	txTriSurfaceData(txVector3 *v,int numv, int *i,int numi);
	~txTriSurfaceData(void);

	std::vector<txVector3> & GetVerts() { return verts; };
	std::vector<int> & GetIndexes() { return indexes; };

private:
	std::vector<txVector3> verts;
	std::vector<int> indexes;
};

