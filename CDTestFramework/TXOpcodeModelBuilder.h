#pragma once

class SurfaceImporter;

class TXOpcodeModelBuilder
{
public:
	TXOpcodeModelBuilder(SurfaceImporter *surface);
	~TXOpcodeModelBuilder(void);

	Model *GetModel() { return model; };

private:
	SurfaceImporter *surface;
	Model *model;

	MeshInterface meshInterface;
};

