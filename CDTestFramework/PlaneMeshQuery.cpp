#include "StdAfx.h"
#include "PlaneMeshQuery.h"
#include "RenderingHelpers.h"
#include "Terrain.h"
#include "OPC_PlanesCollider.h"
#include <math.h>


PlaneMeshQuery::PlaneMeshQuery(void)
{
}


PlaneMeshQuery::~PlaneMeshQuery(void)
{
}

void PlaneMeshQuery::Release()
{
	delete []mPlanes;
	Deselect();
}

void PlaneMeshQuery::Init()
{
	Plane p0;
	p0.n.x = 0.0;
	p0.n.y = 0.0;
	p0.n.z = 1.0;
	p0.d = -0.1;

	Plane p1;
	p1.n.x = 0.0;
	p1.n.y = 0.0;
	p1.n.z = 1.0;
	p1.d = 0.1;
	mPlanes = new Plane[1];
	mPlanes[0] = p0;
	//mPlanes[1] = p1;

	mDis = 0.0;
	mNx = 0.0;
	mNy = 0.0;
	mNz = 1.0;
}

void PlaneMeshQuery::PerformTest()
{
	//mValidHit = false;
	//RenderTerrain();

	PlanesCache cache;

	
	float l = sqrt(mNx*mNx + mNy*mNy + mNz*mNz);
	if (l<0.000001)
	{
		mNx = 0.0;
		mNy = 0.0;
		mNz = 1.0;
		
	} else
	{
		mNx = mNx/l;
		mNy = mNy/l;
		mNz = mNz/l;
	}

	mPlanes[0].n.x = mNx;
	mPlanes[0].n.y = mNy;
	mPlanes[0].n.z = mNz;
	mPlanes[0].d = mDis;
	const Model *TM = GetTerrainModel();


	DrawPlane(&mPlanes[0]);
	if (TM)
	{
		PlanesCollider collider;
		collider.SetFirstContact(false);
		collider.SetPrimitiveTests(true);
		
		mSetting.SetupCollider(collider);
		
		bool status = collider.Collide(cache, mPlanes,1,*TM,null);

		if (status)
		{
			if(collider.GetContactStatus())
			{
				udword NbTris = collider.GetNbTouchedPrimitives();
				const udword* Indices = collider.GetTouchedPrimitives();

				RenderTerrainTriangles(NbTris, Indices);
			}
		}
	}
}

void PlaneMeshQuery::Select()
{
	{
		mBar = TwNewBar("PlaneMeshQuery");
		TwAddVarRW(mBar, "distance", TW_TYPE_FLOAT,&mDis,"min=-200.0 max=200.0 step=0.05");
		TwAddVarRW(mBar, "Nx", TW_TYPE_FLOAT,&mNx,"min=-1.0 max=1.0 step=0.05");
		TwAddVarRW(mBar, "Ny", TW_TYPE_FLOAT,&mNy,"min=-1.0 max=1.0 step=0.05");
		TwAddVarRW(mBar, "Nz", TW_TYPE_FLOAT,&mNz,"min=-1.0 max=1.0 step=0.05");

		mSetting.AddToTweakBar(mBar);
	}
}

void PlaneMeshQuery::Deselect()
{
	if(mBar)
	{
		TwDeleteBar(mBar);
		mBar = null;
	}
}

void PlaneMeshQuery::KeyboardCallback(unsigned char key, int x, int y)
{

}

void PlaneMeshQuery::MouseCallback(int button, int state, int x, int y)
{

}

void PlaneMeshQuery::MotionCallback(int x, int y)
{

}
