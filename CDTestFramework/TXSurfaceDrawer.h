#pragma once

class SurfaceImporter;

class TXSurfaceDrawer
{
public:
	TXSurfaceDrawer(SurfaceImporter *surface);
	~TXSurfaceDrawer(void);

	void Draw(bool addWireframe, bool defulatt=true);

private:
	void _RenderSurfaceUtil(bool addWireframe, bool defaultt=true);
	void _BuildRenderData();
private:
	SurfaceImporter *surface;

	float* pVertList;
	float* pNormList;
	float* pColorList;
	int nbFaces_;
};

