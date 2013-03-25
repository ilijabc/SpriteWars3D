/*
 * LakeObject.cpp
 *
 *  Created on: 25.03.2013.
 *      Author: idjukic
 */

#include "LakeObject.h"

LakeObject::LakeObject(GameScene *scene) : GameObject(scene, 0)
{
	mBody = NULL;
}

LakeObject::~LakeObject()
{
}

void LakeObject::createBody(b2World *world, float w, float h)
{
	float density = 1.0f;
	float friction = 0.3f;
	float restitution = 0.5f;
	b2BodyDef bodyDef;
	bodyDef.position.Set(getPosition().x, getPosition().y);
	bodyDef.type = b2_dynamicBody;
	mBody = world->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(w / 2, h / 2);
	b2FixtureDef fixDef;
	fixDef.shape = &shape;
	fixDef.density = density;
	fixDef.friction = friction;
	fixDef.restitution = restitution;
	mBody->CreateFixture(&fixDef);
	mSize.set(w, h);
}

void LakeObject::onUpdate(float td)
{
	if (mBody)
	{
		b2Vec2 pos = mBody->GetPosition();
		float rot = mBody->GetAngle() * GLPLUS_TODEG;
		setPosition(pos.x, pos.y, 0);
		setRotation(rot);
	}
}

void LakeObject::onDraw(GLView* view, unsigned int flags)
{
	view->drawCube(mSize.x, mSize.y, 1);
}


