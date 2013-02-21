/*
 * TestClient.cpp
 *
 *  Created on: 22.10.2012.
 *      Author: idjukic
 */

#include "TestClient.h"
#include <GL/glfw.h>

TestClient::TestClient(AppServer *server)
		: AppClient(server)
{
	AppServer::Settings settings = getServer()->getSettings();
	mView = new GLView();
	mView->setup();
	mView->setSize(settings.width, settings.height);
	mFont = new GLFont("Data/Arial.fnt");
	mSceneSize.set(settings.width, settings.height);
	for (int i = 0; i < 8; i++)
		mButtonState[i] = GLFW_RELEASE;
	mCameraPos.set(0, 0, 100);
	mCamera.zoom = -10;
	//mCamera.position.set(20, 20, 0);

	initGUI();
	initScene();

	mSprite = new GLSprite("Modules/War2/archer.anim");
}

void TestClient::initGUI()
{
	mTestForm = new GUIForm(50, 50, 250, 300);
	mTestForm->setFont(mFont);
	mTestForm->setEventListener(this);
	GUIButton *button1 = mTestForm->addControl<GUIButton>(20, 20, 150, 50, "Button 1");
	GUIButton *button2 = mTestForm->addControl<GUIButton>(20, 80, 150, 50, "very, very long button text...");
	GUIButton *button3 = mTestForm->addControl<GUIButton>(20, 220, 150, 50, "Button 3");
	GUIScrollBar *scroll1 = mTestForm->addControl<GUIScrollBar>(200, 0, 50, 300);
	GUIScrollBar *scroll2 = mTestForm->addControl<GUIScrollBar>(0, 130, 100, 20);
	scroll2->setOrientation(GUIScrollBar::e_horizontalOrientation);
}

void TestClient::initScene()
{
	mScene = new GameScene(this);

	vector3f obj1_pos(0, 0, 0);
	obj1_pos.z = mScene->getTerrain()->getHeight(obj1_pos.x, obj1_pos.y);
	GameObject *obj1 = new GameObject(mScene, 0);
	obj1->setPosition(obj1_pos);
	mScene->addObject(obj1);

	vector3f obj2_pos(0, 0, 0);
	obj2_pos.z = mScene->getTerrain()->getHeight(obj2_pos.x, obj2_pos.y);
	GameObject *obj2 = new GameObject(mScene, 0);
	obj2->setPosition(obj2_pos);
	mScene->addObject(obj2);

}

TestClient::~TestClient()
{
	delete mSprite;
	delete mTestForm;
	delete mScene;
	delete mView;
}

void TestClient::onUpdate(float dt)
{
	mScene->update(dt);
	mTestForm->doEvents();
}

void TestClient::onDraw()
{
#if 0
	mSceneSize = mView->beginScene2DWide(mCameraPos.z);
	glPushMatrix();
	//grid
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(-mSceneSize.x / 2, mCameraPos.y);
	glVertex2f(mSceneSize.x / 2, mCameraPos.y);
	glVertex2f(mCameraPos.x, -mSceneSize.y / 2);
	glVertex2f(mCameraPos.x, mSceneSize.y / 2);
	glEnd();
	//scene
	glTranslatef(mCameraPos.x, mCameraPos.y, 0);
	//mScene->draw(mView);
	glPopMatrix();
	mView->endScene2D();
#else
	mView->beginScene3D();
	mCamera.apply();
	//float color[4] = { 1,1,0,1 };
	//glColor3f(1,1,0);
	//mView->drawCube(1, 1, 1);
	//glColor3f(0, 1, 0);
	//mTerrain->render();
	//glColor3f(1,1,1);
	mScene->draw(mView);
	mView->endScene3D();
#endif
	//gui
	mView->beginGui();
	mSprite->drawFrame(0, 0);
	//mTestForm->draw(mView);
	mView->endGui();
}

void TestClient::onKeyEvent(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		if (mTestForm)
		{
			mTestForm->sendKeyPress(key);
		}
	}
}

void TestClient::onMouseMoveEvent(int x, int y)
{
	float dx = x - mMousePos.x;
	float dy = y - mMousePos.y;
	if (mButtonState[GLFW_MOUSE_BUTTON_RIGHT] == GLFW_PRESS)
	{
		float fx = mSceneSize.x / (float)mView->getWidth();
		float fy = mSceneSize.y / (float)mView->getHeight();
		mCameraPos.x += dx * fx;
		mCameraPos.y -= dy * fy;
		mCamera.rotation.z += dx;
		mCamera.rotation.x += dy;
	}
	mMousePos.x = x;
	mMousePos.y = y;
	if (mTestForm)
	{
		mTestForm->sendMouseMove(x, y);
	}
}

void TestClient::onMouseButtonEvent(int button, int press)
{
	bool gui_event = false;
	if (mTestForm)
	{
		if (press == GLFW_PRESS)
			gui_event = mTestForm->sendMouseDown();
		else
			mTestForm->sendMouseUp();
	}
	if (!gui_event)
		mButtonState[button] = press;
}

void TestClient::onMouseWheelEvent(int wheel)
{
	float dz = wheel - mMousePos.z;
	mCameraPos.z -= dz * 5;
	if (mCameraPos.z < 5)
		mCameraPos.z = 5;
	mMousePos.z = wheel;
	mCamera.zoom += dz;
}

void TestClient::onSize(int width, int height)
{
	mView->setSize(width, height);
}

void TestClient::onClickEvent(GUIControl *ctl)
{
	//ctl->setPosition(ctl->getLeft() + 10, ctl->getTop());
}
