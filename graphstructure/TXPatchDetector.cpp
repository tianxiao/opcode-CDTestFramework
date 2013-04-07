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

	patchcount=0;
}


TXPatchDetector::~TXPatchDetector(void)
{
	if (indecies!=NULL)
	{
		delete indecies;
	}
}


void TXPatchDetector::InputRing(size_t nbTri, size_t *indices)
{
	for (size_t i=0; i<nbTri; i++)
	{
		facestate[indices[i]] = RINGPACTH;
	}
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
		patchcount++;
		int id = q.front();
		q.pop();

		std::vector<int> validface = DetectValidFaceAroundFace(id);
		for (size_t i=0; i<validface.size(); i++)
		{
			q.push(validface[i]);
		}
	}

	// iterator the facedetectedlist find the 1

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

size_t *TXPatchDetector::PatchIndeces()
{
	indecies = new size_t[patchcount];
	size_t counter = 0;
	for (size_t i=0; i<facestate.size(); i++)
	{
		if (facestate[i]==PATCH0)
		{
			indecies[counter++] = i;
		}
	}
	return indecies;
}
