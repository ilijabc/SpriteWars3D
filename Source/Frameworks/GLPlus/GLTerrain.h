#ifndef GLTERRAIN_H
#define GLTERRAIN_H

#include "GLTexture.h"

#include "Common/vector3.h"
#include "Common/Color.h"
#include "Common/rect.h"

const int TERRAIN_MAX_SIZE = 500;

class GLTerrain
{
public:
	struct STerrainVertex
	{
		float 		height;
		Color		color;
		vector3f	normal;
	};


	struct STerrainFace
	{
		vector3f	normal1;
		vector3f 	normal2;
		rectf       texsrc;
		int 		flags;
	};

public:
	GLTerrain() :
		mTexture(0),
		mSizeX(0),
		mSizeY(0)
	{ }

	void init(int sizeX, int sizeY);
	void generate(int steps, float size_min, float size_max, float h_min, float h_max);

    void fillColor(Color c);

	void addHeight(float x, float y, float bsize, float dh);
	void addColor(float x, float y, float bsize, float r, float g, float b);

	float pickHeight(float x, float y);

	inline void setTexture(GLTexture* tex) { mTexture = tex; }

	inline STerrainVertex& getVertex(int ix, int iy) { return mVertexMap[ix][iy]; }
	inline STerrainFace& getFace(int ix, int iy) { return mFaceMap[ix][iy]; }

    inline int getWidth() const { return mSizeX; }
    inline int getHeight() const { return mSizeY; }

	void render();
	void render(float x1, float y1, float x2, float y2);

	void buildNormals();

private:
	void computeVerticeNormal(int vx, int vy);

private:
	STerrainVertex 	mVertexMap[TERRAIN_MAX_SIZE + 1][TERRAIN_MAX_SIZE + 1];
	STerrainFace	mFaceMap[TERRAIN_MAX_SIZE][TERRAIN_MAX_SIZE];

	GLTexture*	mTexture;
	int 		mSizeX;
	int 		mSizeY;
};

#endif // GLTERRAIN_H
