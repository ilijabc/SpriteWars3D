/*
 * GLSprite.h
 *
 *  Created on: 21.02.2013.
 *      Author: idjukic
 */

#ifndef GLSPRITE_H_
#define GLSPRITE_H_

#define GLSPRITE_IMMEDIATE_MODE 0

#include "GLTexture.h"
#include "Utils/DFSprite.h"
#include "Common/vector2.h"

class GLSprite
{

public:
	struct AnimFrame
	{
		float delay;
		vector2f *verticesPos;
		vector2f *verticesTex;
		int verticesCount;
		AnimFrame();
		~AnimFrame();
	};

	struct Animation
	{
		std::string name;
		int index;
		AnimFrame *frames;
		int framesCount;
		Animation();
		~Animation();
	};

public:
	GLSprite(const char *animFile);
	virtual ~GLSprite();

	void drawFrame(int singleFrameIndex);
	void drawFrame(int animIndex, int frameIndex);
	int findAnimationIndex(const char *name);

	inline int getAnimationsCount() const { return mAnimationsCount; }
	Animation* getAnimation(int index) const { return &(mAnimations[index]); }
	inline DFSprite *getSpriteInfo() { return &mSpriteInfo; }

private:
	void parseDFSpriteCell(AnimFrame *frame, const DFSprite::Cell *cell);

private:
	DFSprite mSpriteInfo;
	GLTexture *mTexture;
	Animation *mAnimations;
	int mAnimationsCount;
};

#endif /* GLSPRITE_H_ */
