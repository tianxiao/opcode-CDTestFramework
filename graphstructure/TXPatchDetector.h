#pragma once
#include <vector>
#include "importsymble.h"

#pragma warning (disable:4251)
class txMesh;

enum GRAPHSTRUCTURE_API FaceState
{
	PATCH0,
	PATCH1,
	RINGPACTH,
	INITIAL
};

enum PatchType 
{
	TOUCH,			// 2 parts `1 The ring patch `2 The outside patch
	PENETRATION		// 3 parts `1 The outside patch `2 The ring patch `3 The penetration patch
};
/**
* This detector must be called if their is collied occure
* (by the Opcode collision!)
*/
class GRAPHSTRUCTURE_API TXPatchDetector
{
public:
	TXPatchDetector(txMesh *mesh);
	~TXPatchDetector(void);

	void InputRing(size_t nbTri, size_t *indices);

	PatchType DetectPath();

	// to compatible with the render function
	size_t PatchCount1() { return patchcount1; };
	size_t *PatchIndeces1();

	size_t PatchCount2() { return patchcount2; };
	size_t *PatchIndeces2();

private:
	/**
	* This is private, the first patch determine by the initially picked face
	* This initialization can be accelerated and the first patch can be quickly
	* interated by given the right initialized faceId (whih this face on the 
	* collisioned side, we can use the coherence between sequence motion!)
	*/
	int RandomFindFaceOnPatch();
	std::vector<int> DetectValidFaceAroundFace(int faceId);

private:
	txMesh *mesh;
	std::vector<FaceState> facestate;
	// Ring Patch info
	size_t numringtri;

	// detect patch1
	size_t patchcount1;
	size_t *indecies1;

	// detect patch2
	size_t patchcount2;
	size_t *indecies2;
};

