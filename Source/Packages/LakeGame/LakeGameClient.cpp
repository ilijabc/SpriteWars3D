/*
 * LakeGameClient.cpp
 *
 *  Created on: 22.03.2013.
 *      Author: idjukic
 */

#include "LakeGameClient.h"

LakeGameClient::LakeGameClient(AppServer *server) : AppClient(server)
{
	mView = new GLView();
	mView->setup();
	mScene = new GameScene(this);

	//mScene->addObject(new GameObject(mScene, 0));
	memset(&mMouse, 0, sizeof(mMouse));
}

LakeGameClient::~LakeGameClient()
{
	delete mScene;
	delete mView;
}

void LakeGameClient::onUpdate(float dt)
{
	mScene->update(dt);
}

void LakeGameClient::onDraw()
{
	mView->beginScene3D();
	mScene->draw(mView);
	mView->endScene3D();
}

void LakeGameClient::onKeyEvent(int key, int action)
{
}

void LakeGameClient::onMouseMoveEvent(int x, int y)
{
	int dx = mMouse.x - x;
	int dy = mMouse.y - y;
	GLCamera *camera = mScene->getCamera();
	if (mMouse.buttonL)
	{
		camera->position.x += dx;
		camera->position.y -= dy;
	}
	mMouse.x = x;
	mMouse.y = y;
}

void LakeGameClient::onMouseButtonEvent(int button, int press)
{
	if (button == 0)
		mMouse.buttonL = press;
	if (button == 1)
		mMouse.buttonR = press;
}

void LakeGameClient::onMouseWheelEvent(int wheel)
{
	int dw = mMouse.wheel - wheel;
	GLCamera *camera = mScene->getCamera();
	camera->zoom -= dw;
	mMouse.wheel = wheel;
}

void LakeGameClient::onSize(int width, int height)
{
	mView->setSize(width, height);
}
