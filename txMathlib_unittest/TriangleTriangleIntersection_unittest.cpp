#include "stdafx.h"

#include <gtest/gtest.h>

#include "../txMathlib/txLineSegmentTriangleIntersection.h"

TEST(INTERSECTIONTEST, TriangleTriangleIntersection0){
	// two triangle edge intersect
	double v00[] = {0,1,0};
	double v01[] = {1,0,0};
	double v02[] = {1,0,2};

	double v10[] = {0,0,0};
	double v11[] = {1,1,0};
	double v12[] = {1,1,2};

	double s[3], e[3];

	TriangleTriangleIntersection(v00,v01,v02,v10,v11,v12,s,e);
	printf("S&E value:\n");
	printf("%f\t%f\t%f\n",s[0],s[1],s[2]);
	printf("%f\t%f\t%f\n",e[0],e[1],e[2]);


	EXPECT_TRUE(s[0]==0.5);
	EXPECT_TRUE(s[1]==0.5);
	EXPECT_TRUE(s[2]==0.0);
	EXPECT_TRUE(e[0]==0.5);
	EXPECT_TRUE(e[1]==0.5);
	EXPECT_TRUE(e[2]==1.0);

}


TEST(INTERSECTIONTEST, TriangleTriangleIntersection1){
	// one of each triangle edge intersect
	double v00[] = {0,1,0};
	double v01[] = {1,0,0};
	double v02[] = {1,0,3};

	double v10[] = {0,0,0};
	double v11[] = {1,1,0};
	double v12[] = {1,1,2};

	double s[3], e[3];

	TriangleTriangleIntersection(v00,v01,v02,v10,v11,v12,s,e);
	printf("S&E value:\n");
	printf("%f\t%f\t%f\n",s[0],s[1],s[2]);
	printf("%f\t%f\t%f\n",e[0],e[1],e[2]);

	/**
	* The TriangleTriangleIntersection can not handle some degenerating situation!
	* like one triangle edge intersection with another!
	*/

	EXPECT_TRUE(s[0]==0.5);
	EXPECT_TRUE(s[1]==0.5);
	EXPECT_TRUE(s[2]==0.0);
	EXPECT_TRUE(e[0]==0.5);
	EXPECT_TRUE(e[1]==0.5);
	EXPECT_TRUE(e[2]==1.0);

}

TEST(INTERSECTIONTEST, TriangleTriangleIntersection2){
	// 0 triangle's two edge intersect the 1 triangle
	double v00[] = {0,1,0};
	double v01[] = {1,0,-1.0};
	double v02[] = {1,0,3};

	double v10[] = {0,0,0};
	double v11[] = {1,1,0};
	double v12[] = {1,1,2};

	double s[3], e[3];

	TriangleTriangleIntersection(v00,v01,v02,v10,v11,v12,s,e);
	printf("S&E value:\n");
	printf("%f\t%f\t%f\n",s[0],s[1],s[2]);
	printf("%f\t%f\t%f\n",e[0],e[1],e[2]);

	/**
	* The TriangleTriangleIntersection can not handle some degenerating situation!
	* like one triangle edge intersection with another!
	*/

	EXPECT_TRUE(s[0]==0.5);
	EXPECT_TRUE(s[1]==0.5);
	EXPECT_TRUE(s[2]==0.0);
	EXPECT_TRUE(e[0]==0.5);
	EXPECT_TRUE(e[1]==0.5);
	EXPECT_TRUE(e[2]==1.0);

}


// M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2
// M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2M2
TEST(INTERSECTIONTEST, TriangleTriangleIntersectionM20){
	// two triangle edge intersect
	double v00[] = {0,1,0};
	double v01[] = {1,0,0};
	double v02[] = {1,0,2};

	double v10[] = {0,0,0};
	double v11[] = {1,1,0};
	double v12[] = {1,1,2};

	double s[3], e[3];

	TriangleTriangleIntersectionM2(v00,v01,v02,v10,v11,v12,s,e);
	printf("S&E value:\n");
	printf("%f\t%f\t%f\n",s[0],s[1],s[2]);
	printf("%f\t%f\t%f\n",e[0],e[1],e[2]);


	EXPECT_TRUE(s[0]==0.5);
	EXPECT_TRUE(s[1]==0.5);
	EXPECT_TRUE(s[2]==0.0);
	EXPECT_TRUE(e[0]==0.5);
	EXPECT_TRUE(e[1]==0.5);
	EXPECT_TRUE(e[2]==1.0);

}


TEST(INTERSECTIONTEST, TriangleTriangleIntersectionM21){
	// one of each triangle edge intersect
	double v00[] = {0,1,0};
	double v01[] = {1,0,0};
	double v02[] = {1,0,3};

	double v10[] = {0,0,0};
	double v11[] = {1,1,0};
	double v12[] = {1,1,2};

	double s[3], e[3];

	TriangleTriangleIntersectionM2(v00,v01,v02,v10,v11,v12,s,e);
	printf("S&E value:\n");
	printf("%f\t%f\t%f\n",s[0],s[1],s[2]);
	printf("%f\t%f\t%f\n",e[0],e[1],e[2]);

	/**
	* The TriangleTriangleIntersection can not handle some degenerating situation!
	* like one triangle edge intersection with another!
	*/

	EXPECT_TRUE(s[0]==0.5);
	EXPECT_TRUE(s[1]==0.5);
	EXPECT_TRUE(s[2]==0.0);
	EXPECT_TRUE(e[0]==0.5);
	EXPECT_TRUE(e[1]==0.5);
	EXPECT_TRUE(e[2]==1.0);

}

TEST(INTERSECTIONTEST, TriangleTriangleIntersectionM22){
	// 0 triangle's two edge intersect the 1 triangle
	double v00[] = {0,1,0};
	double v01[] = {1,0,-1.0};
	double v02[] = {1,0,3};

	double v10[] = {0,0,0};
	double v11[] = {1,1,0};
	double v12[] = {1,1,2};

	double s[3], e[3];

	TriangleTriangleIntersectionM2(v00,v01,v02,v10,v11,v12,s,e);
	printf("S&E value:\n");
	printf("%f\t%f\t%f\n",s[0],s[1],s[2]);
	printf("%f\t%f\t%f\n",e[0],e[1],e[2]);

	/**
	* The TriangleTriangleIntersection can not handle some degenerating situation!
	* like one triangle edge intersection with another!
	*/

	EXPECT_TRUE(s[0]==0.5);
	EXPECT_TRUE(s[1]==0.5);
	EXPECT_TRUE(s[2]==0.0);
	EXPECT_TRUE(e[0]==0.5);
	EXPECT_TRUE(e[1]==0.5);
	EXPECT_TRUE(e[2]==1.0);

}


