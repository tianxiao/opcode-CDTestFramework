#include "StdAfx.h"
#include "TXOpcodeModelBuilder.h"
#include "Terrain.h"


TXOpcodeModelBuilder::TXOpcodeModelBuilder(SurfaceImporter *surface)
{
 	assert(surface);
	this->surface = surface;

	// Build Opcode model
	
		
	meshInterface.SetNbTriangles(surface->NBFaces());
	meshInterface.SetNbVertices(surface->NBVerts());
	meshInterface.SetPointers(
		(const IndexedTriangle *) surface->Faces(),
		surface->Verts()
		);

	OPCODECREATE Create;
	Create.mIMesh			= &meshInterface;
	Create.mSettings.mLimit	= 1;
	Create.mSettings.mRules	= SPLIT_SPLATTER_POINTS|SPLIT_GEOM_CENTER;
	Create.mNoLeaf			= true;
	Create.mQuantized		= true;
	Create.mKeepOriginal	= false;
	Create.mCanRemap		= false;

	model = new Model;
	if (!model->Build(Create))
	{
		
	}
}


TXOpcodeModelBuilder::~TXOpcodeModelBuilder(void)
{
}


