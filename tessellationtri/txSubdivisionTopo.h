#pragma once
#include <vector>

typedef struct 
{
	double a[3];
} txVector;

typedef struct
{
	size_t parentf;
	size_t childfs[4];

	size_t adjacentfs[3];

	size_t vertices[3];
	
	// face complete
} txFace;

class txSubdivisionTopo
{
	txSubdivisionTopo();
	~txSubdivisionTopo();

	void InitializeShape();

	void ConstructSubdivision(size_t level);


private:
	std::vector<txVector*> vertexlist;
	std::vector<txFace*> facelist;
	std::vector<txFace*> nfacelist;
};

