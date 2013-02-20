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
	mTerrain = new GameTerrain();
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
	mTerrain->draw();
	for (std::list<GameObject*>::iterator iobj = mGameObjectList.begin(); iobj != mGameObjectList.end(); iobj++)
	{
		GameObject* obj = *iobj;
		//GLFloat3 position = obj->getPosition();
		//float rotation = obj->getRotation();
		//glPushMatrix();
		//glTranslatef(position.x, position.y, position.z);
		//glRotatef(rotation, 0, 0, 1);
		//obj->onDraw(view, mDrawFlags);
		//glPopMatrix();
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
