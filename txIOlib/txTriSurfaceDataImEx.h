#pragma once
#include "importexport.h"

class txTriSurfaceData;

class TXSIO_API txTriSurfaceDataImEx
{
public:
	txTriSurfaceDataImEx(void);
	~txTriSurfaceDataImEx(void);

	static void ExportToOFFFile(txTriSurfaceData *surf, char *filename);

private:
	txTriSurfaceData *surf;
};

