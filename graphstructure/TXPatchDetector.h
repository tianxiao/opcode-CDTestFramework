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

	void DetectPath();

	// to compatible with the render function
	size_t PatchCount() { return patchcount; };
	size_t *PatchIndeces();

private:
	int RandomFindFaceOnPatch();
	std::vector<int> DetectValidFaceAroundFace(int faceId);

private:
	txMesh *mesh;
	std::vector<FaceState> facestate;
	// detect patch
	size_t patchcount;
	size_t *indecies;
};

