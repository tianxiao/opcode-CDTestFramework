#include "StdAfx.h"
#include "MeshMeshQuery.h"
#include "Terrain.h"
#include "RenderingHelpers.h"


MeshMeshQuery::MeshMeshQuery(void)
{
}


MeshMeshQuery::~MeshMeshQuery(void)
{
}

void MeshMeshQuery::Release()
{
}

void MeshMeshQuery::Init()
{
	float z = 0.0;
	float pscale = 100.0;
	Point p0(-pscale,-pscale,z);
	Point p1(pscale,-pscale,z);
	Point p2(pscale,pscale,z);
	Point p3(-pscale,pscale,z);

	mVB[0] = p0.x; mVB[1] = p0.y; mVB[2] = p0.z;
	mVB[3] = p1.x; mVB[4] = p1.y; mVB[5] = p1.z;
	mVB[6] = p2.x; mVB[7] = p2.y; mVB[8] = p2.z;
	mVB[9] = p3.x; mVB[10] = p3.y; mVB[11] = p3.z;

	mFB[0] = 0; mFB[1] = 2; mFB[2] = 3;
	mFB[3] = 0; mFB[4] = 1; mFB[5] = 2;

	mMeshI.SetNbVertices(6);
	mMeshI.SetNbTriangles(2);

	mMeshI.SetPointers(
		(IceMaths::IndexedTriangle*)mFB,
		(IceMaths::Point*)mVB
		);

	Opcode::OPCODECREATE buildInfo;
	buildInfo.mIMesh = &mMeshI;
	buildInfo.mSettings.mLimit = 1;
	buildInfo.mSettings.mRules = Opcode::SPLIT_BALANCED | Opcode::SPLIT_GEOM_CENTER;
	buildInfo.mNoLeaf = true;
	buildInfo.mQuantized = true;
	buildInfo.mKeepOriginal = false;
	buildInfo.mCanRemap = false;

	mPlane.Build(buildInfo);


}


void MeshMeshQuery::PerformTest()
{
	RenderTerrain();
	const Model *TM = GetTerrainModel();

	Opcode::AABBTreeCollider collider;
	collider.SetFirstContact(false);
	collider.SetFullPrimBoxTest(false);

	Opcode::BVTCache cache;
	cache.Model0 = &mPlane;
	cache.Model1 = TM;

	assert(collider.ValidateSettings()==0);

	//Pair cdpair;

	if (collider.Collide(cache,null,null))
	{
		if (collider.GetContactStatus())
		{
			//udword NbTris = collider.GetNbTouchedPrimitives();
			//const udword* Indices = collider.GetTouchedPrimitives();
			size_t *indexes = new size_t[collider.GetNbPairs()];
			const Pair *opcpairs = collider.GetPairs();
			for (size_t i=0; i<collider.GetNbPairs(); i++)
			{
				indexes[i]  = opcpairs[i].id1;
				//indexes[i+1] = opcpairs[i].id1+1;
				//indexes[i+2] = opcpairs[i].id1+2;
			}

			RenderTerrainTriangles(collider.GetNbPairs(), indexes);
		}
	}

}

void MeshMeshQuery::KeyboardCallback(unsigned char key, int x, int y)
{
}

void MeshMeshQuery::MouseCallback(int button, int state, int x, int y)
{
}

void MeshMeshQuery::MotionCallback(int x, int y)
{
}