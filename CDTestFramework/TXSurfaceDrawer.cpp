#include "StdAfx.h"
#include "TXSurfaceDrawer.h"
#include "Terrain.h"


TXSurfaceDrawer::TXSurfaceDrawer(SurfaceImporter *surface)
{
	assert(surface);
	this->surface = surface;
	this->pVertList = NULL;
	this->pNormList = NULL;
	this->pColorList = NULL;
	nbFaces_ = surface->NBFaces();

	_BuildRenderData();
}


TXSurfaceDrawer::~TXSurfaceDrawer(void)
{

}


void TXSurfaceDrawer::Draw(bool addWireframe,bool defaultt)
{
	_RenderSurfaceUtil(addWireframe, defaultt);
}

void TXSurfaceDrawer::_BuildRenderData()
{

	pVertList = new float[nbFaces_*3*3];
	pNormList = new float[nbFaces_*3*3];
	pColorList = new float[nbFaces_*4*3];

	const udword* faces = surface->Faces();
	const Point* colors = surface->Colors();
	const Point* normals = surface->Normals();
	const Point* verts = surface->Verts();

	int vertIndex = 0;
	int normIndex = 0;
	int colorIndex = 0;
	for(int i=0;i<(int)nbFaces_;i++)
	{
		for(int j=0;j<3;j++)
		{
			pVertList[vertIndex++] = verts[faces[i*3+j]].x;
			pVertList[vertIndex++] = verts[faces[i*3+j]].y;
			pVertList[vertIndex++] = verts[faces[i*3+j]].z;

			pNormList[normIndex++] = normals[faces[i*3+j]].x;
			pNormList[normIndex++] = normals[faces[i*3+j]].y;
			pNormList[normIndex++] = normals[faces[i*3+j]].z;

			pColorList[colorIndex++] = colors[faces[i*3+j]].x;
			pColorList[colorIndex++] = colors[faces[i*3+j]].y;
			pColorList[colorIndex++] = colors[faces[i*3+j]].z;
			pColorList[colorIndex++] = 1.0f;
		}
	}
}


void TXSurfaceDrawer::_RenderSurfaceUtil(bool addWireframe, bool defaultt)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	if (defaultt) {
		
		glVertexPointer(3,GL_FLOAT, 0, pVertList);
		
		glNormalPointer(GL_FLOAT, 0, pNormList);
		glColorPointer(4,GL_FLOAT, 0, pColorList);
		
		glDrawArrays(GL_TRIANGLES, 0, nbFaces_*3);
	}



	if(addWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glVertexPointer(3,GL_FLOAT, 0, pVertList);
		glNormalPointer(GL_FLOAT, 0, pNormList);

		glDisableClientState(GL_COLOR_ARRAY);

		glLineWidth(2.0f);

		glColor4f(0.2f, 0.2f, 0.6f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, nbFaces_*3);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
	}

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

	//delete[] pVertList;
	//delete[] pNormList;
	//delete[] pColorList;
}
