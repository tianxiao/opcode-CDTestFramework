#include "StdAfx.h"
#include "PlaneMeshQuery.h"
#include "RenderingHelpers.h"
#include "Terrain.h"
#include "OPC_PlanesCollider.h"


PlaneMeshQuery::PlaneMeshQuery(void)
{
}


PlaneMeshQuery::~PlaneMeshQuery(void)
{
}

void PlaneMeshQuery::Release()
{
	delete []mPlanes;
}

void PlaneMeshQuery::Init()
{
	Plane p0;
	p0.n.x = 0.0;
	p0.n.y = 1.0;
	p0.n.z = 1.0;
	p0.d = 0.0;
	mPlanes = new Plane[1];
	mPlanes[0] = p0;
}

void PlaneMeshQuery::PerformTest()
{
	//mValidHit = false;
	RenderTerrain();

	PlanesCache cache;

	DrawPlane(&mPlanes[0]);

	const Model *TM = GetTerrainModel();
	if (TM)
	{
		PlanesCollider collider;
		
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

void PlaneMeshQuery::KeyboardCallback(unsigned char key, int x, int y)
{

}

void PlaneMeshQuery::MouseCallback(int button, int state, int x, int y)
{

}

void PlaneMeshQuery::MotionCallback(int x, int y)
{

}
