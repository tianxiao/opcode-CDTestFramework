// tessell_main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../tessellationtri/txBasicMesh.h"

MeshData meshdata;



int _tmain(int argc, _TCHAR* argv[])
{
	MeshDataConfigTetra(&meshdata);
	MeshDataOuputOFF(&meshdata,"m1.off");
	MeshDataDump(&meshdata,"m1dump.txt");


	txBasicMesh bm(&meshdata);
	bm.SubdivsionMesh();
	MeshData *m2 = bm.GetSubdivsionMeshData();
	MeshDataOuputOFF(m2,"m2.off");
	MeshDataDump(m2,"m2dump.txt");

	txBasicMesh bm2(m2);
	bm2.SubdivsionMesh();
	MeshData *m3 = bm2.GetSubdivsionMeshData();
	MeshDataOuputOFF(m3, "m3.off");

	txBasicMesh bm3(m3);
	bm3.SubdivsionMesh();
	MeshData *m4 = bm3.GetSubdivsionMeshData();

	//MeshDataConfigOct(&meshdata);
	//MeshDataDump(&meshdata,"m28dump.txt");
	//
	//txBasicMesh om0(&meshdata);
	//om0.SubdivsionMesh();
	//MeshDataOuputOFF(om0.GetSubdivsionMeshData(),"mOct0.off");

	//txBasicMesh om1(om0.GetSubdivsionMeshData());
	//om1.SubdivsionMesh();
	//MeshDataOuputOFF(om1.GetSubdivsionMeshData(),"mOct1.off");

	return 0;
}

