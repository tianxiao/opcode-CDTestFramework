// tessell_main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../tessellationtri/txBasicMesh.h"
#include "../tessellationtri/txFrustumSubdivision.h"
#include "../txShapelib/txFrustum.h"
#include "../txShapelib/txTriSurfaceData.h"
#include "../txIOlib/txTriSurfaceDataImEx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//MeshDataConfigTetra(&meshdata);
	//MeshDataOuputOFF(&meshdata,"m1.off");
	//MeshDataDump(&meshdata,"m1dump.txt");


	//txBasicMesh bm(&meshdata);
	//bm.SubdivsionMesh();
	//MeshData *m2 = bm.GetSubdivsionMeshData();
	//MeshDataOuputOFF(m2,"m2.off");
	//MeshDataDump(m2,"m2dump.txt");

	//txBasicMesh bm2(m2);
	//bm2.SubdivsionMesh();
	//MeshData *m3 = bm2.GetSubdivsionMeshData();
	//MeshDataOuputOFF(m3, "m3.off");

	//txBasicMesh bm3(m3);
	//bm3.SubdivsionMesh();
	//MeshData *m4 = bm3.GetSubdivsionMeshData();

	//-------------------OCT

	MeshData *meshdata = MeshDataConfigOct();
	MeshDataDump(meshdata,"m28dump.txt");
	
	//txBasicMesh om0(&meshdata);
	//om0.SubdivsionMesh();
	//MeshDataOuputOFF(om0.GetSubdivsionMeshData(),"mOct0.off");

	//txBasicMesh om1(om0.GetSubdivsionMeshData());
	//om1.SubdivsionMesh();
	//MeshDataOuputOFF(om1.GetSubdivsionMeshData(),"mOct1.off");

	//txBasicMesh om2(om1.GetSubdivsionMeshData());
	//om2.SubdivsionMesh();
	//MeshDataOuputOFF(om2.GetSubdivsionMeshData(),"mOct2.off");

	//txBasicMesh om3(om2.GetSubdivsionMeshData());
	//om3.SubdivsionMesh();
	//MeshDataOuputOFF(om3.GetSubdivsionMeshData(),"mOct3.off");

	//txBasicMesh om4(om3.GetSubdivsionMeshData());
	//om4.SubdivsionMesh();
	//MeshDataOuputOFF(om4.GetSubdivsionMeshData(),"mOct4.off");

	//txBasicMesh om5(om4.GetSubdivsionMeshData());
	//om5.SubdivsionMesh();
	//MeshDataOuputOFF(om5.GetSubdivsionMeshData(),"mOct5.off");

	//txBasicMesh om6(om5.GetSubdivsionMeshData());
	//om6.SubdivsionMesh();
	//MeshDataOuputOFF(om6.GetSubdivsionMeshData(),"mOct6.off");

	txBasicMesh *recur = new txBasicMesh(meshdata);
	MeshDataReleaseOct(meshdata);
	for (size_t i=0; i<3/*9*/; i++) {
		recur->SubdivsionMesh();
		txBasicMesh *inter = new txBasicMesh(recur->GetSubdivsionMeshData());
		delete recur;
		recur = inter;
	}
	recur->SubdivsionMesh();
	MeshDataOuputOFF(recur->GetSubdivsionMeshData(),"MOct90.off");
	delete recur;

	{
		txFrustum frustum(1.0, 1.0, 0.2);
		txFrustumSubdivision subfrustum(&frustum,30);
		subfrustum.Subdivision();
		txTriSurfaceData surf2(*subfrustum.GetTriSurfData());
		txTriSurfaceDataImEx::ExportToOFFFile(&surf2,"Frustrum.off");
	}

	return 0;
}

