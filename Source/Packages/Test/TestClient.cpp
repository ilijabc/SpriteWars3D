/*
 * TestClient.cpp
 *
 *  Created on: 22.10.2012.
 *      Author: idjukic
 */

#include "TestClient.h"
#include <GL/glfw.h>

static void colorTexFilter(unsigned char *data, int w, int h, int bpp, void *param)
{
	//AABBGGRR
	unsigned int in_colors[] = {
			0xFFCC480C,
			0xFFA02804,
			0xFF741400,
			0xFF4C0400
	};
	unsigned int out_colors[] = {
			0xFF808080,
			0xFF606060,
			0xFF404040,
			0xFF202020
	};
	unsigned int *pix = (unsigned int*)data;
	unsigned int *end_pix = (unsigned int*)data + w * h;
	while (pix < end_pix)
	{
		for (int i = 0; i < 4; i++)
		{
			if (*pix == in_colors[i])
				*pix = out_colors[i];
		}
		pix++;
	}
}


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

	mSprite = new GLSprite("Modules/War2/archer.anim");
	mTexture2 = new GLTexture(mSprite->getTexture()->getFileName(), GLPLUS_TEXTURE_NEAREST, colorTexFilter);

	initGUI();
	initScene();
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

	vector3f obj1_pos(3, 3, 0);
	obj1_pos.z = mScene->getTerrain()->getHeight(obj1_pos.x, obj1_pos.y);
	GameObject *obj1 = new GameObject(mScene, 0);
	obj1->setPosition(obj1_pos);
	mScene->addObject(obj1);

	vector3f obj2_pos(0, 0, 0);
	obj2_pos.z = mScene->getTerrain()->getHeight(obj2_pos.x, obj2_pos.y);
	GameSprite *obj2 = new GameSprite(mScene);
	obj2->setPosition(obj2_pos);
	obj2->setTexture(mTexture2);
	mScene->addObject(obj2);

	mCursorObjct = obj2;
}

TestClient::~TestClient()
{
	delete mTexture2;
	delete mSprite;
	delete mTestForm;
	delete mScene;
	delete mView;
}

void TestClient::onUpdate(float dt)
{
	mWorldPoint = mScene->getWorldPoint(mMouseX, mMouseY);
	mCursorObjct->setPosition(mWorldPoint);
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
	glTranslatef(100, 100, 0);
	mSprite->drawFrame(0);
	glTranslatef(100, 0, 0);
	mSprite->drawFrame(mTexture2, 0, 0);
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
	float dx = x - mMouseX;
	float dy = y - mMouseY;
	if (mButtonState[GLFW_MOUSE_BUTTON_RIGHT] == GLFW_PRESS)
	{
		float fx = mSceneSize.x / (float)mView->getWidth();
		float fy = mSceneSize.y / (float)mView->getHeight();
		mCameraPos.x += dx * fx;
		mCameraPos.y -= dy * fy;
		mCamera.rotation.z += dx;
		mCamera.rotation.x += dy;
	}
	mMouseX = x;
	mMouseY = y;
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
	float dz = wheel - mMouseWheel;
	mCameraPos.z -= dz * 5;
	if (mCameraPos.z < 5)
		mCameraPos.z = 5;
	mMouseWheel = wheel;
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
