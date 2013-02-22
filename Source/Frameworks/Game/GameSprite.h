/*
 * GameSprite.h
 *
 *  Created on: 22.02.2013.
 *      Author: idjukic
 */

#ifndef GAMESPRITE_H_
#define GAMESPRITE_H_

#include "GameObject.h"

class GameSprite: public GameObject
{
public:
	GameSprite(GameScene *scene);
	virtual ~GameSprite();
	//events
	virtual void onUpdate(float dt);
	virtual void onDraw(GLView *view, unsigned int flags);
	//setters
	inline void setTexture(GLTexture *tex) { mTexture = tex; }
	//getters
	inline GLTexture *getTexture() const { return mTexture; }

private:
	GLSprite *mSprite;
	GLTexture *mTexture;
	GLSprite::Animation *mCurrentAnimation;
	int mFrameIndex;
	float mFrameTimer;
};

#endif /* GAMESPRITE_H_ */
