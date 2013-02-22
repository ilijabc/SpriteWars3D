/*
 * GameSprite.cpp
 *
 *  Created on: 22.02.2013.
 *      Author: idjukic
 */

#include "GameSprite.h"

GameSprite::GameSprite(GameScene *scene)
		: GameObject(scene, eGameSpriteType)
{
	mSprite = new GLSprite("Modules/War2/archer.anim");
	mTexture = NULL;
	mCurrentAnimation = mSprite->getAnimation(mSprite->findAnimationIndex("walk_N"));
	mFrameIndex = 0;
	mFrameTimer = mCurrentAnimation->frames[0].delay / 50.0f;
	//scale by first frame
	float scale = 1.0f / (float)mSprite->getSpriteInfo()->getFrameByIndex(0)->w;
	setScale(scale);
}

GameSprite::~GameSprite()
{
	delete mSprite;
}

void GameSprite::onUpdate(float dt)
{
	mFrameTimer -= dt;
	if (mFrameTimer <= 0)
	{
		mFrameIndex++;
		if (mFrameIndex == mCurrentAnimation->framesCount)
			mFrameIndex = 0;
		mFrameTimer += mCurrentAnimation->frames[mFrameIndex].delay / 50.0f;
	}
}

void GameSprite::onDraw(GLView* view, unsigned int flags)
{
	GLTexture *tex = mTexture;
	if (tex == NULL)
		tex = mSprite->getTexture();
	//glDisable(GL_CULL_FACE);
	//glScalef(0.1, 0.1, 0.1);
	glRotatef(90, 1, 0, 0);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	mSprite->drawFrame(tex, mCurrentAnimation->index, mFrameIndex);
	//glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}


