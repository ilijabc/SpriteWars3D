/*
 * LakeGameClient.h
 *
 *  Created on: 22.03.2013.
 *      Author: idjukic
 */

#ifndef LAKEGAMECLIENT_H_
#define LAKEGAMECLIENT_H_

#include "App/AppClient.h"
#include "App/AppServer.h"
#include "Game/GameScene.h"
#include "Game/GameObject.h"
#include "LakeObject.h"

#include <Box2D/Box2D.h>
#include <GL/glfw.h>

class LakeGameClient : public AppClient
{
public:
	LakeGameClient(AppServer *server);
	virtual ~LakeGameClient();
	//callbacks
	virtual void onUpdate(float dt);
	virtual void onDraw();
	virtual void onKeyEvent(int key, int action);
	virtual void onMouseMoveEvent(int x, int y);
	virtual void onMouseButtonEvent(int button, int press);
	virtual void onMouseWheelEvent(int wheel);
    virtual void onSize(int width, int height);

private:
    GLView *mView;
    GameScene *mScene;
    struct
    {
    	int buttonL;
    	int buttonR;
    	int x;
    	int y;
    	int wheel;
    } mMouse;
    int mKeyState[GLFW_KEY_LAST + 1];
    b2World *mWorld;
    float mWorldUpdateTimer;
    LakeObject *mPlayer;
};

#endif /* LAKEGAMECLIENT_H_ */
