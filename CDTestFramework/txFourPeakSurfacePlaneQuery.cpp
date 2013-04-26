#include "StdAfx.h"
#include "txFourPeakSurfacePlaneQuery.h"
#include <tuple>
#include "Terrain.h"
#include "../tessellationtri/txTesselateFunctionSurface.h"
#include "../txShapelib/txTriSurfaceData.h"
#include "../txShapelib/txFunctionSurface.h"
#include "../txMathlib/txFourPeakSurface.h"
#include "../txIOlib/txTriSurfaceDataImEx.h"

#include "TXSurfaceDrawer.h"
#include "TXOpcodeModelBuilder.h"




txFourPeakSurfacePlaneQuery::txFourPeakSurfacePlaneQuery(void)
{
}


txFourPeakSurfacePlaneQuery::~txFourPeakSurfacePlaneQuery(void)
{
}

void txFourPeakSurfacePlaneQuery::Init()
{
	std::tuple<double, double> xrange(-2,2);
	std::tuple<double, double> yrange(-2,2);

	this->surface = new SurfaceImporter();
	assert(surface);
	txRectangleAreaTesselate recttess;
	surf = recttess.GetTriSurfData()->DeepCopy();
	txFunctionSurface fpeakfs0(xrange, yrange, txPlaneSurfaceFun);
	fpeakfs0(surf);
	surface->InitializeFromOFFSurfaceWitoutMesh(surf);
	drawer = new TXSurfaceDrawer(surface);
	txTriSurfaceDataImEx::ExportToOFFFile(surf,"fourpeaksurf0.OFF");
	modelbuilder = new TXOpcodeModelBuilder(surface);

	
	this->surface2 = new SurfaceImporter();
	assert(surface);
	txRectangleAreaTesselate recttess2;
	surf2 = recttess2.GetTriSurfData()->DeepCopy();

	txFunctionSurface fpeakfs2(xrange, yrange, txFourPeakFunO);
	fpeakfs2(surf2);
	surface2->InitializeFromOFFSurfaceWitoutMesh(surf2);
	drawer2 = new TXSurfaceDrawer(surface2);
	txTriSurfaceDataImEx::ExportToOFFFile(surf2,"fourpeaksurf1.OFF");
	modelbuilder2 = new TXOpcodeModelBuilder(surface2);



}

void txFourPeakSurfacePlaneQuery::Release()
{
	delete surface;
	surface = NULL;
	delete surf;
	surf = NULL;
	delete drawer;
	drawer = NULL;
}

void txFourPeakSurfacePlaneQuery::PerformTest()
{
	drawer->Draw(true);
	drawer2->Draw(true);

	// set collider which will be move to the class
	Opcode::AABBTreeCollider collider;
	collider.SetFirstContact(false);
	collider.SetFullPrimBoxTest(false);

	Opcode::BVTCache cache;
	cache.Model0 = modelbuilder->GetModel();
	//cache.Model1 = TM2;
	cache.Model1 = modelbuilder2->GetModel();

	if (collider.Collide(cache,null,null))
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
				indexes[i]  = opcpairs[i].id0;
				indexes2[i] = opcpairs[i].id1;
				//indexes[i+1] = opcpairs[i].id1+1;
				//indexes[i+2] = opcpairs[i].id1+2;
			}

			// RenderTerrainTriangles(collider.GetNbPairs(), indexes2);
			Point color(1.0,0.0,0.0);
			RenderSurfaceTriangles(surface2,collider.GetNbPairs(),indexes2, &color);
			Point color2(0.0,1.0,0.0);
			RenderSurfaceTriangles(surface,collider.GetNbPairs(),indexes, &color2);

			//if (pfappset==WITHPATCHFINDER) 
			//{
			//	// detect the missing triangle
			//	TXPatchDetector patchdetector(mesh);
			//	patchdetector.InputRing(collider.GetNbPairs(), indexes);
			//	patchdetector.DetectPath();
			//	size_t *patchindices = patchdetector.PatchIndeces1();
			//	// Rnder the patch face patch
			//	RenderSurfaceTriangles(surface, patchdetector.PatchCount1(), patchindices);

			//} else {
			//
			//}

			delete [] indexes;
			indexes = NULL;
			delete [] indexes2;
			indexes2 = NULL;
		}
	}

}

void txFourPeakSurfacePlaneQuery::Select()
{

}

void txFourPeakSurfacePlaneQuery::Deselect()
{

}

void txFourPeakSurfacePlaneQuery::KeyboardCallback(unsigned char key, int x, int y)
{
}

void txFourPeakSurfacePlaneQuery::MouseCallback(int button, int state, int x, int y)
{
}

void txFourPeakSurfacePlaneQuery::MotionCallback(int x, int y)
{
}


