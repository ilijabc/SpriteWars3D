#include "GameObject.h"
#include "GameScene.h"

#include "poly2tri/poly2tri.h"

//#define ENABLE_GAME_OBJECT_DRAW_DEBUG

GameObject::GameObject(GameScene *scene, int type)
		: mScene(scene)
		, mType(type)
		, mPosition(0, 0, 0)
		, mRotation(0, 0, 0)
		, mScale(1, 1, 1)
{
	strcpy(mName, "");
}

GameObject::~GameObject()
{
}

void GameObject::drawObject(GLView *view, const matrix4f &modelMatrix, unsigned int flags)
{
    matrix4f m(eMatrixTranslate, mPosition.x, mPosition.y, mPosition.z);
    m.rotateX(mRotation.x);
    m.rotateY(mRotation.y);
    m.rotateZ(mRotation.z);
    //m.scale(mScale.x, mScale.y, mScale.z);
    mModelMatrix = m * modelMatrix;
    //gl draw
    glPushMatrix();
    glMultMatrix(m);
    onDraw(view, flags);
    glPopMatrix();
}

void GameObject::onUpdate(float dt)
{
}

void GameObject::onDraw(GLView *view, unsigned int flags)
{
	view->drawCube(1, 1, 1);
}

