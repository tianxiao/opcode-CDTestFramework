#pragma once

class SurfaceImporter;

class TXSurfaceDrawer
{
public:
	TXSurfaceDrawer(SurfaceImporter *surface);
	~TXSurfaceDrawer(void);

	void Draw(bool addWireframe);

private:
	void _RenderSurfaceUtil(bool addWireframe);
	void _BuildRenderData();
private:
	SurfaceImporter *surface;

	float* pVertList;
	float* pNormList;
	float* pColorList;
	int nbFaces_;
};

