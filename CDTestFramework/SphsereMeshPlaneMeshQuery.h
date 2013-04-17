#pragma once
#include "collisiontest.h"

class SurfaceImporter;
class TXSurfaceDrawer;
class TXOpcodeModelBuilder;
class txMesh;
class txTriSurfaceData;

enum SphereAppState
{
	WITHPATCHFINDER,
	WITHOUTPATCHFINDER,
	NUM_PF_STATES
};

class SphsereMeshPlaneMeshQuery :
	public CollisionTest
{
public:
	SphsereMeshPlaneMeshQuery(void);
	~SphsereMeshPlaneMeshQuery(void);

	virtual	void			Init();
	virtual	void			Release();
	virtual	void			PerformTest();
	virtual	void			Select();
	virtual	void			Deselect();
	virtual	void			KeyboardCallback(unsigned char key, int x, int y);
	virtual	void			MouseCallback(int button, int state, int x, int y);
	virtual	void			MotionCallback(int x, int y);

	TwBar *mBar;
	int pfappset;

	float mZ;
	OpcodeSettings mSettings;
	float mGamma;
	float mAlpha;
	float mBeta;

	Model mPlane;
	MeshInterface mMeshI;
	//float mVB[4*3];
	//size_t mFB[2*3];
	float *mVB;
	size_t *mFB;

	// Mesh from the surface
	SurfaceImporter *surface;
	txMesh *mesh;
	TXSurfaceDrawer *drawer;
	TXOpcodeModelBuilder *modelbuilder;


	// Initial from surf
	txTriSurfaceData *surf;
	
};

