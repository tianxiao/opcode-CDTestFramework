#ifndef TERRAIN_H
#define TERRAIN_H

	class TerrainData
	{
		public:
					TerrainData();
					~TerrainData();

		void		init(udword size, float offset, float width, float chaos, bool flat=false, const Point* pos=NULL);
		void		release();

		udword		size;
		udword		nbVerts;
		udword		nbFaces;
		float		offset;
		float		width;
		float		chaos;
		Point*		verts;
		Point*		colors;
		Point*		normals;
		udword*		faces;
	};

	void			CreateTerrain();
	void			ReleaseTerrain();

	void			RenderTerrain();
	void			RenderTerrainTriangles(udword nbTriangles, const udword* indices);

	const Model*	GetTerrainModel();


	class SurfaceImporter
	{

	public:
		SurfaceImporter();
		~SurfaceImporter();

		void InitializeFromFile(char *filename);
		void InitializeFromFunction();

		

	public:
		Point  * Verts()	{ return verts; }
		Point  * Colors()	{ return colors; }
		Point  * Normals()	{ return normals; }
		udword * Faces()	{ return faces; }
		udword NBVerts()	{ return nbVerts; }
		udword NBFaces()	{ return nbFaces; }
			
	private:
		void ImportVertexes(char *filename);
		void InitializeColors();
		void InitialzieFaces();
		void BuildVertexNormals();

		udword nbVerts;
		udword nbFaces;
		int numrow;
		int numcolumn;

		Point *verts;
		Point *colors;
		Point *normals;
		udword*faces;
		

	};

	void CreateSurface();

	const Model* GetSurfaceModel();
	SurfaceImporter* GetSurface();

	void ReleaseSurface();

	// static method to render the surface & surface intersect with the collider
	void SRenderSurace();

	void RenderCollidePatch(udword nbTri_, udword *indices_);

	static void _RenderSurface(udword *faces_, Point *colors_, Point *normals_, Point *verts_, udword nbFaces_, bool addWireframe);

	void RenderSurface(SurfaceImporter *surface, bool addWireframe=true);

	static void _RenderSurfaceTriangles(udword *faces_, Point *normals_, Point *verts_, udword nbTri_, udword *indices_);

	void RenderSurfaceTriangles(SurfaceImporter *surface, udword nbTri_, udword *indices_);

#endif
