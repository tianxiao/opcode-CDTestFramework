#include "StdAfx.h"
#include <assert.h>
#include <queue>
#include "TXPatchDetector.h"
#include "../graphstructure/txMesh.h"


TXPatchDetector::TXPatchDetector(txMesh *mesh)
{
	assert(mesh);
	this->mesh = mesh;
	facestate.reserve(mesh->FaceCount());
	for (int i=0; i<mesh->FaceCount(); i++)
	{
		facestate.push_back(INITIAL);
	}

	patchcount1=0;

	indecies1 = NULL;
	indecies2 = NULL;
}


TXPatchDetector::~TXPatchDetector(void)
{
	if (indecies1!=NULL)
	{
		delete indecies1;
	}

	if (indecies2!=NULL)
	{
		delete indecies2;
	}
}


void TXPatchDetector::InputRing(size_t nbTri, size_t *indices)
{
	for (size_t i=0; i<nbTri; i++)
	{
		facestate[indices[i]] = RINGPACTH;
	}
	numringtri = nbTri;
}

void TXPatchDetector::DetectPath()
{
	// Pick one that is not on the Opcode detected ring patch
	int startfaceid = RandomFindFaceOnPatch();
	facestate[startfaceid] = PATCH0;
	
	std::queue<int> q;
	q.push(startfaceid);
	while (!q.empty())
	{
		patchcount1++;
		int id = q.front();
		q.pop();

		std::vector<int> validface = DetectValidFaceAroundFace(id);
		for (size_t i=0; i<validface.size(); i++)
		{
			q.push(validface[i]);
		}
	}

	// iterator the facedetectedlist find the 1
	patchcount2 = mesh->FaceCount() - numringtri - patchcount1;
}

/**
* Qusi random, iterator the facestate list find the one face that
* on the ring patch
*/
int TXPatchDetector::RandomFindFaceOnPatch()
{
	size_t i=0;
	for ( ; i<facestate.size(); i++)
	{
		if ( facestate[i] != RINGPACTH)
			break;
	}
	assert(i<facestate.size());
	return i--;
}

/**
* Valid faceId:
* `1 FaceState is not ringpatch
* `2 Face is not finded in the already detected list
* And this function also set the face state to be PATCH0; 
*/
std::vector<int> TXPatchDetector::DetectValidFaceAroundFace( int faceId)
{
	std::vector<int> rst;
	rst.reserve(3);
	int face1, face2, face3;
	// here is a defficiency when tri-mesh have the boundary the adjacent face return
	// by the CircleFacesFace is not tree! it's 2 or only 1
	mesh->CircleFacesFace(faceId, face1, face2, face3);
	if (facestate[face1]!=PATCH0&&facestate[face1]!=RINGPACTH) 
	{
		rst.push_back(face1);
		facestate[face1] = PATCH0;
	} 

	if (facestate[face2]!=PATCH0&&facestate[face2]!=RINGPACTH) 
	{
		rst.push_back(face2);
		facestate[face2] = PATCH0;
	} 

	if (facestate[face3]!=PATCH0&&facestate[face3]!=RINGPACTH) 
	{
		rst.push_back(face3);
		facestate[face3] = PATCH0;
	} 
	return rst;
}

size_t *TXPatchDetector::PatchIndeces1()
{
	indecies1 = new size_t[patchcount1];
	size_t counter = 0;
	for (size_t i=0; i<facestate.size(); i++)
	{
		if (facestate[i]==PATCH0)
		{
			indecies1[counter++] = i;
		}
	}
	assert(counter==patchcount1);
	return indecies1;
}

size_t *TXPatchDetector::PatchIndeces2()
{
	indecies2 = new size_t[patchcount2];
	size_t counter = 0;
	for (size_t i=0; i<facestate.size(); i++)
	{
		if (facestate[i]==INITIAL)
		{
			indecies2[counter++] = i;
		}
	}
	return indecies2;
}
