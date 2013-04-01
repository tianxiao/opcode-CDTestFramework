#include "StdAfx.h"
#include "SphsereMeshPlaneMeshQuery.h"
#include "Terrain.h"


SphsereMeshPlaneMeshQuery::SphsereMeshPlaneMeshQuery(void)
{
}


SphsereMeshPlaneMeshQuery::~SphsereMeshPlaneMeshQuery(void)
{
}

void SphsereMeshPlaneMeshQuery::Init()
{
	surface = new SurfaceImporter();
	assert(surface);
	char *filename = "E:\\motionsolve\\ProjectTime\\20130326\\meshlib\\meshes\\bunny_nf500.noff";
	surface->InitializeFromOFF(filename);
}

void SphsereMeshPlaneMeshQuery::Release()
{
	delete surface;
	surface = NULL;
}

void SphsereMeshPlaneMeshQuery::PerformTest()
{
	// Draw the Tri-Mesh
	RenderSurface(surface);
}

void SphsereMeshPlaneMeshQuery::Select()
{
}

void SphsereMeshPlaneMeshQuery::Deselect()
{
}

void SphsereMeshPlaneMeshQuery::KeyboardCallback(unsigned char key, int x, int y)
{
}

void SphsereMeshPlaneMeshQuery::MouseCallback(int button, int state, int x, int y)
{
}

void SphsereMeshPlaneMeshQuery::MotionCallback(int x, int y)
{
}

