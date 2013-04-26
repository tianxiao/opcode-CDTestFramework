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

	/*float */mVB = new float[4*3];
	/*size_t */mFB = new size_t[2*3];

	mAlpha = 0.0;
	mBeta = 0.0;
	mGamma = 0.0;
	mZ = 0.0;
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
	SRenderSurace();
	const Model *TM2 = GetTerrainModel();
	const Model *TM = GetSurfaceModel();

	Opcode::AABBTreeCollider collider;
	collider.SetFirstContact(false);
	collider.SetFullPrimBoxTest(false);

	Opcode::BVTCache cache;
	cache.Model0 = &mPlane;
	//cache.Model1 = TM2;
	cache.Model1 = TM;

	//Opcode::BVTCache cache2;
	//cache2.mo

	Matrix4x4 matplane;
	matplane.Set(
		1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,mZ,1.0
		);
	//matplane.RotZ(mGamma);
	//matplane.RotX(mAlpha);
	//matplane.RotY(mBeta);


	assert(collider.ValidateSettings()==0);

	//Pair cdpair;

	if (collider.Collide(cache,&matplane,null))
	{
		if (collider.GetContactStatus())
		{
			//udword NbTris = collider.GetNbTouchedPrimitives();
			//const udword* Indices = collider.GetTouchedPrimitives();
			size_t *indexes = new size_t[collider.GetNbPairs()];
			size_t *indexes2 = new size_t[collider.GetNbPairs()];
			int numcollider = collider.GetNbPairs();
			const Pair *opcpairs = collider.GetPairs();
			for (size_t i=0; i<collider.GetNbPairs(); i++)
			{
				//indexes[i]  = opcpairs[i].id0;
				indexes2[i] = opcpairs[i].id1;
				//indexes[i+1] = opcpairs[i].id1+1;
				//indexes[i+2] = opcpairs[i].id1+2;
			}

			//RenderTerrainTriangles(collider.GetNbPairs(), indexes2);
			Point color(1.0,0.0,0.0);
			RenderSurfaceTriangles(GetSurface(),collider.GetNbPairs(),indexes2,&color);
			delete [] indexes;
			indexes = NULL;
			delete [] indexes2;
			indexes2 = NULL;
		}
	}

	//if (mVB!=NULL)
	//{
	//	delete mVB;
	//	mVB = NULL;
	//}
	//if (mFB!=NULL)
	//{
	//	delete mFB;
	//	mFB = NULL;
	//}

}

void MeshMeshQuery::Select()
{
	{
		mBar = TwNewBar("Z distance");
		TwAddVarRW(mBar,"Z", TW_TYPE_FLOAT, &mZ, "min=-60.0 max=60.0 step=0.05");
		TwAddVarRW(mBar,"rotate Z", TW_TYPE_FLOAT, &mGamma, "min=-7.0 max=7.0 step=0.05");
		TwAddVarRW(mBar,"rotate X", TW_TYPE_FLOAT, &mAlpha, "min=-7.0 max=7.0 step=0.05");
		TwAddVarRW(mBar,"rotate y", TW_TYPE_FLOAT, &mBeta, "min=-7.0 max=7.0 step=0.05");

		// mAlpha mBeta
		mSettings.AddToTweakBar(mBar);
	}
}

void MeshMeshQuery::Deselect()
{
	if (mBar)
	{
		TwDeleteBar(mBar);
		mBar = null;
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