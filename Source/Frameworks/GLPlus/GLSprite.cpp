/*
 * GLSprite.cpp
 *
 *  Created on: 21.02.2013.
 *      Author: idjukic
 */

#include "GLSprite.h"



GLSprite::GLSprite(const char *animFile)
{
	mTexture = NULL;
	mAnimations = NULL;
	mAnimationsCount = 0;

	if (mSpriteInfo.parseAnimFile(animFile))
	{
		mTexture = new GLTexture(mSpriteInfo.imageName.c_str(), GLPLUS_TEXTURE_NEAREST);
#if !GLSPRITE_IMMEDIATE_MODE
		mAnimationsCount = mSpriteInfo.animations.size();
		mAnimations = new Animation [mAnimationsCount];
		for (int animIndex = 0; animIndex < mAnimationsCount; animIndex++)
		{
			mAnimations[animIndex].name = mSpriteInfo.animations[animIndex].name;
			mAnimations[animIndex].index = animIndex;
			mAnimations[animIndex].framesCount = mSpriteInfo.animations[animIndex].cells.size();
			mAnimations[animIndex].frames = new AnimFrame [mAnimations[animIndex].framesCount];
			for (int frameIndex = 0; frameIndex < mAnimations[animIndex].framesCount; frameIndex++)
			{
				parseDFSpriteCell(
						&(mAnimations[animIndex].frames[frameIndex]),
						&(mSpriteInfo.animations[animIndex].cells[frameIndex]));
			}
		}
#endif
	}

}

GLSprite::~GLSprite()
{
	delete mTexture;
	delete mAnimations;
}

void GLSprite::drawFrame(int singleFrameIndex)
{
	// immediate mode only!
	DFSprite::Frame *pframe = mSpriteInfo.getFrameByIndex(singleFrameIndex);
	if (pframe)
	{
		float imgW = (float)mTexture->getWidth();
		float imgH = (float)mTexture->getHeight();
		float u1 = (float)pframe->x / imgW;
		float v1 = (float)pframe->y / imgH;
		float u2 = (float)(pframe->x + pframe->w) / imgW;
		float v2 = (float)(pframe->y + pframe->h) / imgH;
		float x1 = 0;
		float y1 = 0;
		float x2 = (float)pframe->w;
		float y2 = (float)pframe->h;
		mTexture->push();
		glBegin(GL_QUADS);
		glTexCoord2f(u1, v1);
		glVertex2f(x1, y1);
		glTexCoord2f(u2, v1);
		glVertex2f(x2, y1);
		glTexCoord2f(u2, v2);
		glVertex2f(x2, y2);
		glTexCoord2f(u1, v2);
		glVertex2f(x1, y2);
		glEnd();
		mTexture->pop();
	}
}

void GLSprite::drawFrame(int animIndex, int frameIndex)
{
	drawFrame(mTexture, animIndex, frameIndex);
}

void GLSprite::drawFrame(GLTexture *tex, int animIndex, int frameIndex)
{
#if GLSPRITE_IMMEDIATE_MODE
#else
	AnimFrame *frame = &(mAnimations[animIndex].frames[frameIndex]);
	tex->push();
	glColor3f(1, 1, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, frame->verticesPos);
	glTexCoordPointer(2, GL_FLOAT, 0, frame->verticesTex);
	glDrawArrays(GL_TRIANGLES, 0, frame->verticesCount);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	tex->pop();
#endif
}

void GLSprite::parseDFSpriteCell(AnimFrame* frame, const DFSprite::Cell* cell)
{
	frame->delay = (float)cell->delay;
	frame->verticesCount = cell->sprites.size() * 6;
	frame->verticesPos = new vector2f [frame->verticesCount];
	frame->verticesTex = new vector2f [frame->verticesCount];
	float imgW = (float)mTexture->getWidth();
	float imgH = (float)mTexture->getHeight();
	for (int i = 0; i < cell->sprites.size(); i++)
	{
		const DFSprite::Sprite *psprite = &(cell->sprites[i]);
		const DFSprite::Frame *pframe = cell->sprites[i].frame;
		float u1 = (float)pframe->x / imgW;
		float v1 = (float)(pframe->y + pframe->h) / imgH;
		float u2 = (float)(pframe->x + pframe->w) / imgW;
		float v2 = (float)pframe->y / imgH;
		float x1 = (float)(psprite->x - pframe->w / 2);
		float y1 = (float)(-psprite->y - pframe->h / 2);
		float x2 = (float)(psprite->x + pframe->w / 2);
		float y2 = (float)(-psprite->y + pframe->h / 2);
		//make vertices
		//pos
		frame->verticesPos[0].set(x1, y1);
		frame->verticesPos[1].set(x2, y1);
		frame->verticesPos[2].set(x2, y2);
		frame->verticesPos[3].set(x2, y2);
		frame->verticesPos[4].set(x1, y2);
		frame->verticesPos[5].set(x1, y1);
		//tex
		frame->verticesTex[0].set(u1, v1);
		frame->verticesTex[1].set(u2, v1);
		frame->verticesTex[2].set(u2, v2);
		frame->verticesTex[3].set(u2, v2);
		frame->verticesTex[4].set(u1, v2);
		frame->verticesTex[5].set(u1, v1);
	}
}

int GLSprite::findAnimationIndex(const char *name)
{
	for (int i = 0; i < mAnimationsCount; i++)
	{
		if (mAnimations[i].name == name)
			return i;
	}
	return -1;
}

//
// sub classes
//

GLSprite::AnimFrame::AnimFrame()
{
	delay = 0.0f;
	verticesPos = NULL;
	verticesTex = NULL;
	verticesCount = 0;
}

GLSprite::AnimFrame::~AnimFrame()
{
	delete verticesPos;
	delete verticesTex;
}

GLSprite::Animation::Animation()
{
	index = 0;
	frames = NULL;
	framesCount = 0;
}

GLSprite::Animation::~Animation()
{
	delete frames;
}
