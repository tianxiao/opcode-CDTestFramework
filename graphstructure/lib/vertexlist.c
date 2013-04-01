#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mesh.h"
#include "funcs.h"

#pragma warning (disable:4996) 

void  VertexListConstruct(Solid ** solid ,int vertex_number,FILE *fp)
{
  int i;
  double x,y,z;
  char Line[1024];
  VertexIDReset();
  for( i = 0; i < vertex_number && !feof(fp); i ++ ){

		 fgets(Line,1024,fp);
		 sscanf(Line,"%lf %lf %lf", &x,&y,&z);
		 VertexConstruct(solid,x,y,z);

		}

}
void  VertexListConstructNoff(Solid ** solid ,int vertex_number,FILE *fp)
{
  int i;
  double x,y,z,nx,ny,nz;
  char Line[1024];
  VertexIDReset();
  for( i = 0; i < vertex_number && !feof(fp); i ++ ){

		 fgets(Line,1024,fp);
		 sscanf(Line,"%lf %lf %lf %lf %lf %lf", &x,&y,&z,&nx,&ny,&nz);
		 VertexConstructN(solid,x,y,z,nx,ny,nz);

		}

}

Vertex *VertexListIndex(Solid * solid, int no)
{  Vertex * tv;

	tv = solid->sverts;
	do{
	 if( tv->vertexno == no ) return tv;
	tv = tv->next;
	}while( tv != solid->sverts );
	return NIL;

}



void  VertexListDestruct(Solid ** solid )
{
	 Vertex * tv;


	 while( (*solid)->sverts ){
	 tv = (*solid)->sverts;
	 VertexDestruct( &tv);
	 }

}

void VertexListIndexConstruct(Solid **sp)
{
	Vertex *vhp = (*sp)->sverts;
	Vertex *vp = vhp;
	int vertexId=0;
	// If I added the following code there will be a error 
	// error C2143:syntax error : missing ';' before 'type'
	// The following is the reason,
	// Visual Studio only supports C89. That means that all of your variables must be declared before anything else at the top of a function.
	// from this link="http://stackoverflow.com/questions/15697190/error-c2143-syntax-error-missing-before-type"
	assert(	(*sp)!=NULL );
	assert( (*sp)->sverts!=NULL );

	do 
	{
		vp->vertexno = vertexId;
		vertexId++;
		vp = vp->next;
	}while(vp!=vhp);
}

