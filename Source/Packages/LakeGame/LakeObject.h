/*
 * LakeObject.h
 *
 *  Created on: 25.03.2013.
 *      Author: idjukic
 */

#ifndef LAKEOBJECT_H_
#define LAKEOBJECT_H_

#include "Game/GameObject.h"

#include <Box2D/Box2D.h>

class LakeObject: public GameObject
{
public:
	LakeObject(GameScene *scene);
	virtual ~LakeObject();
	void createBody(b2World *world, float w, float h);
	// callbacks
	virtual void onUpdate(float td);
	virtual void onDraw(GLView *view, unsigned int flags);
	// getters
	inline b2Body *getBody() const { return mBody; }

private:
	b2Body *mBody;
	vector2f mSize;
};

#endif /* LAKEOBJECT_H_ */
