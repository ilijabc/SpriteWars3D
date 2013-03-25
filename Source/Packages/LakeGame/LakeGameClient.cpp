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

	mWorld = new b2World(b2Vec2(0, -1));
	mWorldUpdateTimer = 0;

	mScene = new GameScene(this);
	GLTerrain *terrain = new GLTerrain();
	terrain->init(100, 100);
	terrain->setWaterTexture(getTexture("water.jpg"));
	mScene->setTerrain(terrain);

	b2BodyDef terrainDef;
	terrainDef.type = b2_staticBody;
	b2Body *terrainBody = mWorld->CreateBody(&terrainDef);
	b2ChainShape terrainChain;
	b2Vec2 terrainPoints[5] = {
			b2Vec2(0, 0),
			b2Vec2(0, 100),
			b2Vec2(100, 100),
			b2Vec2(100, 0)
	};
	terrainChain.CreateChain(terrainPoints, 5);
	b2FixtureDef terrainFix;
	terrainFix.shape = &terrainChain;
	terrainFix.density = 0.0f;
	terrainBody->CreateFixture(&terrainFix);

	for (int i = 0; i < 10; i++)
	{
		LakeObject *obj = new LakeObject(mScene);
		obj->setPosition(randomFloat(1, 10), randomFloat(3, 10), 0);
		obj->createBody(mWorld, 2, 1);
		mScene->addObject(obj);
	}

	mPlayer = new LakeObject(mScene);
	mPlayer->setPosition(3, 3, 0);
	mPlayer->createBody(mWorld, 1, 2);
	mScene->addObject(mPlayer);

	memset(&mMouse, 0, sizeof(mMouse));
	memset(mKeyState, 0, sizeof(int) * (GLFW_KEY_LAST + 1));
}

LakeGameClient::~LakeGameClient()
{
	delete mScene;
	delete mWorld;
	delete mView;
}

void LakeGameClient::onUpdate(float dt)
{
	// player control
	if (mPlayer)
	{
		b2Vec2 v(0, 0.1);
		if (mKeyState['W'])
			mPlayer->getBody()->ApplyForce(v, b2Vec2(0, 1));
	}
	// world physics
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	mWorldUpdateTimer += dt;
	if (mWorldUpdateTimer >= timeStep)
	{
		mWorld->Step(timeStep, velocityIterations, positionIterations);
		mWorldUpdateTimer -= timeStep;
	}
	// scene update
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
	mKeyState[key] = action;
}

void LakeGameClient::onMouseMoveEvent(int x, int y)
{
	int dx = mMouse.x - x;
	int dy = mMouse.y - y;
	GLCamera *camera = mScene->getCamera();
	if (mMouse.buttonL)
	{
		camera->position.x += dx * 0.1;
		camera->position.y -= dy * 0.1;
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
