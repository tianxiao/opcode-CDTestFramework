#include "stdafx.h"
#include "txBasicMesh.h"
#include "initialmesh.h"
#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable:4996) 

void MeshDataConfig(
	MeshData *md, size_t oV, size_t oE, size_t oT, 
	txPoint3 P[], txVertex V[], txEdge E[], txTriangle T[]
	)
{
	assert(oV);
	assert(oE);
	assert(oT);
	assert(md);

	md->oV = oV;
	md->oE = oE;
	md->oT = oT;

	md->opoints.reserve(oV);
	md->overtices.reserve(oV);
	for (size_t i=0; i<oV; i++) {
		md->opoints.push_back(P[i]);

		txVertex *v = new txVertex;
		v->numEdges = V[i].numEdges;
		v->pointId = V[i].pointId;
		for (size_t j=0; j<V[i].numEdges; j++) {
			v->edgeIds[j] = V[i].edgeIds[j];
		}
		md->overtices.push_back(v);
	}

	md->oedges.reserve(oE);
	for (size_t i=0; i<oE; i++) {
		txEdge *e = new txEdge;
		for (size_t j=0; j<2; j++) {
			e->T[j] = E[i].T[j];
			e->V[j] = E[i].V[j];
		}
		md->oedges.push_back(e);
	}

	md->otriangles.reserve(oT);
	for (size_t i=0; i<oT; i++) {
		txTriangle *t = new txTriangle;
		for (size_t j=0; j<3; j++) {
			t->A[j] = T[i].A[j];
			t->E[j] = T[i].E[j];
			t->V[j] = T[i].V[j];
		}
		md->otriangles.push_back(t);
	}
}


void MeshDataConfigOct(MeshData *meshdata)
{
	size_t &oV = (meshdata->oV);
	size_t &oE = (meshdata->oE);
	size_t &oT = (meshdata->oT);

	std::vector<txPoint3> &opoints = (meshdata->opoints);
	std::vector<txVertex*> &overtices = (meshdata->overtices);
	std::vector<txEdge*> &oedges  = (meshdata->oedges);
	std::vector<txTriangle*> &otriangles = (meshdata->otriangles);

	oV = num_ov_8; oE = num_edge_8; oT = num_tri_8;
	opoints.reserve(oV);
	overtices.reserve(oV);
	for (size_t i=0; i<oV; i++) {
		opoints.push_back(op_8[i]);

		txVertex *v = new txVertex;
		v->pointId = ov_8[i].pointId;
		v->numEdges = ov_8[i].numEdges;
		for (size_t j=0; j<ov_8[i].numEdges; j++) {
			v->edgeIds[j] = ov_8[i].edgeIds[j];
		}
		overtices.push_back(v);
	}

	oedges.reserve(oE);
	for (size_t i=0; i<oE; i++) {
		txEdge *e = new txEdge;
		for (size_t j=0; j<2; j++) {
			e->T[j] = edge_8[i].T[j];
			e->V[j] = edge_8[i].V[j];
		}
		oedges.push_back(e);
	}

	otriangles.reserve(oT);
	for (size_t i=0; i<oT; i++) {
		txTriangle *t = new txTriangle;
		for (size_t j=0; j<3; j++) {
			t->A[j] = tri_8[i].A[j];
			t->E[j] = tri_8[i].E[j];
			t->V[j] = tri_8[i].V[j];
		}
		otriangles.push_back(t);
	}
}

void MeshDataReleaseOct()
{
	assert(true);
	exit(1);
}

void MeshDataConfigTetra(MeshData *meshdata)
{
	MeshDataConfig(meshdata,num_v_4, num_e_4, num_t_4,p_4, v_4, e_4, t_4);
}

void MeshDataReleaseTetra(MeshData *meshdata)
{

}

void MeshDataOuputOFF(MeshData *meshdata, char *filename)
{
	FILE *f = fopen(filename, "w");

	fprintf(f,"OFF\n");

	fprintf(f,"%d\t%d\t%d\n",meshdata->oV,meshdata->oT,0);

	for (size_t i=0; i<meshdata->oV; i++) {
		fprintf(f,"%f\t%f\t%f\n",meshdata->opoints[i].x,meshdata->opoints[i].y,meshdata->opoints[i].z);
	}

	for (size_t i=0; i<meshdata->oT; i++) {
		fprintf(f,"%d\t%d\t%d\t%d\n",3,
			meshdata->otriangles[i]->V[0],
			meshdata->otriangles[i]->V[1],
			meshdata->otriangles[i]->V[2]);
	}


	fclose(f);
}

void MeshDataDump(MeshData *md, char *filename)
{
	FILE *f = fopen(filename,"w");

	fprintf(f,"#VET INFO:\n\n");

	fprintf(f,"#Vertex INFO:\n");
	for (size_t i=0; i<md->oV; i++) {
		fprintf(f,"   V[%2d]",i);
	}
	fprintf(f,"\n");
	for (size_t i=0; i<md->oV; i++) {
		fprintf(f,"%8d",md->overtices[i]->numEdges);
	}
	fprintf(f,"\n");
	for (size_t i=0; i<6; i++) {
		for (size_t j=0; j<md->oV; j++) {
			if (i<md->overtices[j]->numEdges) {
				fprintf(f,"%8d",md->overtices[j]->edgeIds[i]);
			} else {
				fprintf(f,"       -");
			}
		}
		fprintf(f,"\n");
	}
	fprintf(f,"\n");

	fprintf(f,"#Edge INFO:\n");
	for (size_t i=0; i<2; i++) {
		for (size_t j=0; j<md->oE; j++) {
			fprintf(f,"%8d",md->oedges[j]->T[i]);
		}
		fprintf(f,"\n");
	}
	for (size_t i=0; i<2; i++) {
		for (size_t j=0; j<md->oE; j++) {
			fprintf(f,"%8d",md->oedges[j]->V[i]);
		}
		fprintf(f,"\n");
	}

	fprintf(f,"\n");
	fprintf(f,"#Triangle Info: \n");

	for (size_t i=0; i<3; i++) {
		for (size_t j=0; j<md->oT; j++) {
			fprintf(f,"%8d",md->otriangles[j]->V[i]);
		}
		fprintf(f,"\n");
	}
	for (size_t i=0; i<3; i++) {
		for (size_t j=0; j<md->oT; j++) {
			fprintf(f,"%8d",md->otriangles[j]->E[i]);
		}
		fprintf(f,"\n");
	}
	for (size_t i=0; i<3; i++) {
		for (size_t j=0; j<md->oT; j++) {
			fprintf(f,"%8d",md->otriangles[j]->A[i]);
		}
		fprintf(f,"\n");
	}
	
	fclose(f);
}