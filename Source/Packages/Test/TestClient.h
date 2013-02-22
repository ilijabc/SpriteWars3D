/*
 * TestClient.h
 *
 *  Created on: 22.10.2012.
 *      Author: idjukic
 */

#ifndef TESTCLIENT_H_
#define TESTCLIENT_H_

#include "App/AppClient.h"
#include "App/AppServer.h"
#include "Game/GameScene.h"
#include "Game/GameSprite.h"
#include "GUI/GUIForm.h"
#include "GUI/GUIButton.h"
#include "GUI/GUIScrollBar.h"

class TestClient : public AppClient, public GUIEventListener
{
public:
	TestClient(AppServer *server);
	virtual ~TestClient();
	//callbacks
	virtual void onUpdate(float dt);
	virtual void onDraw();
	virtual void onKeyEvent(int key, int action);
	virtual void onMouseMoveEvent(int x, int y);
	virtual void onMouseButtonEvent(int button, int press);
	virtual void onMouseWheelEvent(int wheel);
    virtual void onSize(int width, int height);
    virtual void onClickEvent(GUIControl *ctl);

private:
    void initGUI();
    void initScene();

private:
	GLView *mView;
	GLFont *mFont;
	GameScene *mScene;
	GLFloat2 mSceneSize;
	int mButtonState[8];
	int mMouseX, mMouseY, mMouseWheel;
	GLFloat3 mCameraPos;
	GUIForm *mTestForm;
	GLCamera mCamera;
	GLSprite *mSprite;
	GLTexture *mTexture2;
	vector3f mWorldPoint;
	GameObject *mCursorObjct;
};

#endif /* TESTCLIENT_H_ */
