#pragma once
#include <vector>
#include <string>
#include "importsymble.h"

#pragma warning (disable:4251)
struct solid;
struct face;
struct vertex;
struct edge;

class GRAPHSTRUCTURE_API txMesh
{
public:
	txMesh(void);
	~txMesh(void);

	void ConstructMeshFromFile(std::string filename);
	std::vector<face*> &GetFaceList() { return facelist; };
	std::vector<vertex*> &GetVertexList() { return vertexlist; };
	std::vector<edge*> &GetEdgeList() { return edgelist; };

private:
	void ConstructFVEIndex();

private:
	solid *solid;
	std::vector<face*> facelist;
	std::vector<vertex*> vertexlist;
	std::vector<edge*> edgelist;
	
};

