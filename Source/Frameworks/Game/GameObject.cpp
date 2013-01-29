#include "GameObject.h"
#include "GameScene.h"

#include "poly2tri/poly2tri.h"

//#define ENABLE_GAME_OBJECT_DRAW_DEBUG

GameObject::GameObject(GameScene *scene, int type)
		: mScene(scene)
		, mType(type)
		, mPosition(0, 0, 0)
		, mRotation(0)
{
	strcpy(mName, "");
}

GameObject::~GameObject()
{
}

void GameObject::onUpdate(float dt)
{
}

void GameObject::onDraw(GLView *view, unsigned int flags)
{
}

