#pragma once
#include <vector>
#include <string>
#include "importsymble.h"

#pragma warning (disable:4251)
struct solid;
struct face;
struct vertex;
struct edge;
struct halfedge;

class GRAPHSTRUCTURE_API txMesh
{
public:
	txMesh(void);
	~txMesh(void);

	void ConstructMeshFromFile(char* filename, int state=0);
	std::vector<face*> &GetFaceList() { return facelist; };
	void GetFaceVertexIdListByFId(const int faceno, int &a, int &b, int &c);
	std::vector<vertex*> &GetVertexList() { return vertexlist; };
	std::vector<edge*> &GetEdgeList() { return edgelist; };
	int FaceCount() { return facelist.size(); };
	int VertexCount() { return vertexlist.size(); };
	int EdgeCount() { return edgelist.size(); };

	// Adjacent info (traversal)
public:
	void CircleFacesFace(int faceId, int &face1, int &face2, int &face3);
	static halfedge *HalfedgeHalfedge(halfedge *hf);
	static int FaceIdHalfedge(halfedge *hf);
	static int FaceIdReverseHalfedge(halfedge *hf);

private:
	void ConstructFVEIndex();

private:
	solid *solid;
	// The following pointer vector is actually a 
	// int(Key):pointer(value) array hash 
	// Look up the id to locate the vertex
	// The most usefull case is when do traversal checking if the 
	// The current vertex have been visted.
	std::vector<face*> facelist;
	std::vector<vertex*> vertexlist;
	std::vector<edge*> edgelist;
	
};

