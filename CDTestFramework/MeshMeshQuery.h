#pragma once
#include "collisiontest.h"
class MeshMeshQuery :
	public CollisionTest
{
public:
	MeshMeshQuery(void);
	~MeshMeshQuery(void);

	virtual	void			Init();
	virtual	void			Release();
	virtual	void			PerformTest();
	virtual	void			KeyboardCallback(unsigned char key, int x, int y);
	virtual	void			MouseCallback(int button, int state, int x, int y);
	virtual	void			MotionCallback(int x, int y);


	Model mPlane;
	MeshInterface mMeshI;
	float mVB[4*3];
	size_t mFB[2*3];

};

