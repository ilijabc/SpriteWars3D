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
};

#endif /* LAKEGAMECLIENT_H_ */
