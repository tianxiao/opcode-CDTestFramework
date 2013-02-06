#pragma once
#include "collisiontest.h"
#include "Profiling.h"

class PlaneMeshQuery :
	public CollisionTest
{
public:
	PlaneMeshQuery(void);
	~PlaneMeshQuery(void);

	virtual	void			Init();
	virtual	void			Release();
	virtual	void			PerformTest();
	virtual	void			Select();
	virtual	void			Deselect();
	virtual	void			KeyboardCallback(unsigned char key, int x, int y);
	virtual	void			MouseCallback(int button, int state, int x, int y);
	virtual	void			MotionCallback(int x, int y);

	TwBar* mBar;
	Profiler mProfiler;
	OpcodeSettings mSetting;
	
	Plane * mPlanes;

	float mDis;
	float mNx;
	float mNy;
	float mNz;
};

