#pragma once

// 8 triangles

size_t num_op_8 = 6;
txPoint3 op_8[] = {
	{ 0.0,  0.0,  1.0},
	{ 0.0,  0.0, -1.0},
	{-1.0,  0.0,  0.0},
	{ 0.0, -1.0,  0.0},
	{ 1.0,  0.0,  0.0},
	{ 0.0,  1.0,  0.0},
};

size_t num_ov_8 = 6;
txVertex ov_8[] = {
	{0, 4, {0,1,2,3}},
	{1, 4, {4,7,6,5}},
	{2, 4, {3,1,7,8}},
	{3, 4, {8,4,9,0}},
	{4, 4, {9,5,0,1}},
	{5, 4, {2,10,6,11}},
};

size_t num_edge_8 = 12;
txEdge edge_8[] = {
	{{0,1},{0,3}},
	{{1,2},{0,4}},
	{{2,3},{0,5}},
	{{0,3},{0,2}},
	{{4,7},{1,3}},
	{{6,7},{1,4}},
	{{5,6},{1,5}},
	{{4,5},{1,2}},
	{{4,0},{2,3}},
	{{7,1},{3,4}},
	{{6,2},{4,5}},
	{{3,5},{5,2}},
};

size_t num_tri_8 = 8;
txTriangle tri_8[] = {
	{{2,3,0},{0,3,8},{1,3,4}},
	{{3,4,0},{9,1,0},{7,2,0}},
	{{4,5,0},{10,2,1},{6,3,1}},
	{{5,2,0},{2,11,3},{2,5,0}},
	{{1,3,2},{4,8,7},{7,0,5}},
	{{1,2,5},{7,11,6},{4,3,6}},
	{{1,4,5},{6,5,10},{5,7,2}},
	{{4,1,3},{5,4,9},{6,4,1}},
};



// tetra
double tetrax0 = 0.0; 
double tetray0 = 0.0;
double tetraz0 = 1.0;
double tetrax1 = 0.94280904158206;
double tetray1 = 0.0;
double tetraz1 = 0.33333333333333;
double tetrax2 = -0.47140452079103;
double tetray2 = -0.81649658092773;
double tetraz2 = tetraz1;
double tetrax3 = -0.47140452079103;
double tetray3 = 0.81649658092773;
double tetraz3 = tetraz1;

size_t num_p_4 = 4;
txPoint3 p_4[] = {
	{tetrax0, tetray0, tetraz0},
	{tetrax1, tetray1, tetraz1},
	{tetrax2, tetray2, tetraz2},
	{tetrax3, tetray3, tetraz3},
};

size_t num_v_4 = 4;
txVertex v_4[] = {
	{0, 3, {0, 1, 2}},
	{1, 3, {3, 0, 5}},
	{2, 3, {4, 1, 3}},
	{3, 3, {2, 4, 5}},
};

size_t num_e_4 = 6;
txEdge e_4[] = {
	{{0,2},{0,1}},
	{{0,1},{0,2}},
	{{1,2},{0,3}},
	{{0,3},{1,2}},
	{{1,3},{2,3}},
	{{2,3},{1,3}},
};

size_t num_t_4 = 4;
txTriangle t_4[] = {
	{{1,2,0},{3,1,0},{3,1,2}},
	{{2,3,0},{4,2,1},{3,2,0}},
	{{3,1,0},{5,0,2},{3,0,1}},
	{{1,3,2},{5,4,3},{2,1,0}},
};