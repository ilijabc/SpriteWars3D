/*
 * GameScene.cpp
 *
 *  Created on: 19.10.2012.
 *      Author: idjukic
 */

#include "GameScene.h"

GameScene::GameScene(AppClient *game)
		: mGame(game)
		, mDrawFlags(0xFFFFFFFF)
{
	mCamera.position.set(50, 50, 0);
	mCamera.rotation.x = -45;
	mCamera.zoom = -20;

	mTerrain = new GLTerrain();
	mTerrain->init(100, 100);
	mTerrain->generate(200, 10, 12, 0, 1);
	mTerrain->buildNormals();
	mTerrain->setTexture(getGame()->getTexture("grass.png"));

	mSelectTexture = getGame()->getTexture("select.png");
}

GameScene::~GameScene()
{
	delete mTerrain;
}

void GameScene::update(float dt)
{
	for (std::list<GameObject*>::iterator iobj = mGameObjectList.begin(); iobj != mGameObjectList.end(); iobj++)
	{
		(*iobj)->onUpdate(dt);
	}
}

void GameScene::draw(GLView *view)
{
	mCamera.apply();
	mTerrain->render(
			mCamera.position.x - 22,
			mCamera.position.y - 9,
			mCamera.position.x + 22,
			mCamera.position.y + 21);
	mPickedPoint = glGetPoint3D(mMouseX, mMouseY);
	//shadow
	for (std::list<GameObject*>::iterator iobj = mGameObjectList.begin(); iobj != mGameObjectList.end(); iobj++)
	{
		GameObject* obj = *iobj;
		if (obj->getShadow())
			obj->drawObjectShadow(view);
	}
	//object
	for (std::list<GameObject*>::iterator iobj = mGameObjectList.begin(); iobj != mGameObjectList.end(); iobj++)
	{
		GameObject* obj = *iobj;
		obj->drawObject(view, mSceneMatrix, mDrawFlags);
	}
}

GameObject *GameScene::addObject(GameObject *obj, bool to_back)
{
	if (to_back)
		mGameObjectList.push_back(obj);
	else
		mGameObjectList.push_front(obj);
	return obj;
}

GameObject *GameScene::getObjectByName(const char *name)
{
	for (std::list<GameObject*>::iterator iobj = mGameObjectList.begin(); iobj != mGameObjectList.end(); iobj++)
	{
		if (strcmp((*iobj)->getName(), name) == 0)
			return (*iobj);
	}
	return NULL;
}
