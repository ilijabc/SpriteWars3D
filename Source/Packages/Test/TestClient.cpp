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

	mSprite = new GLSprite("Modules/War2/archer.anim");
	mTexture2 = new GLTexture(mSprite->getTexture()->getFileName(), GLPLUS_TEXTURE_NEAREST, colorTexFilter);

	mSkyTexture = getTexture("sky.png");

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

	//units
	for (int i = 0; i < 50; i++)
	{
		vector3f obj_pos;
		obj_pos.x = 50 + (i / 6);
		obj_pos.y = 50 + (i % 6);
		obj_pos.z = mScene->getTerrain()->pickHeight(obj_pos.x, obj_pos.y);
		GameSprite *obj = new GameSprite(mScene);
		obj->setPosition(obj_pos);
		obj->setSprite(mSprite);
		obj->setTexture(mTexture2);
		obj->setSelected(true);
		mScene->addObject(obj);
		//last
		mCursorObjct = obj;
	}

	//trees
	GLTexture *treeTexture = getTexture("tree.png");
	for (int i = 0; i < 100; i++)
	{
		vector3f obj_pos;
		obj_pos.x = randomFloat(mScene->getTerrain()->getWidth());
		obj_pos.y = randomFloat(mScene->getTerrain()->getHeight());
		obj_pos.z = mScene->getTerrain()->pickHeight(obj_pos.x, obj_pos.y);
		GameSprite *obj = new GameSprite(mScene);
		obj->setPosition(obj_pos);
		obj->setTexture(treeTexture);
		obj->setShadow(true);
		mScene->addObject(obj);
	}
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
	mScene->update(dt);
	mTestForm->doEvents();
}

void TestClient::onDraw()
{
	//sky
	mView->beginGui();
	mSkyTexture->drawImage(0, 0, mView->getWidth(), mView->getHeight(), 0, 0, 1, 1);
	mView->endGui();
	// draw game
	mView->beginScene3D();
	mScene->draw(mView);
	mView->endScene3D();
	//draw gui
	mView->beginGui();
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
	GLCamera *camera = mScene->getCamera();
	if (mButtonState[GLFW_MOUSE_BUTTON_LEFT] == GLFW_PRESS)
	{
		mCursorObjct->setPosition(mWorldPoint);
	}
	if (mButtonState[GLFW_MOUSE_BUTTON_MIDDLE] == GLFW_PRESS)
	{
		float fx = mSceneSize.x / (float)mView->getWidth();
		float fy = mSceneSize.y / (float)mView->getHeight();
		camera->rotation.z += dx;
		camera->rotation.x += dy;
		camera->rotation.x = CLAMP(camera->rotation.x, -80, -40);
	}
	if (mButtonState[GLFW_MOUSE_BUTTON_RIGHT] == GLFW_PRESS)
	{
		//camera->position.x -= dx * 0.1;
		//camera->position.y += dy * 0.1;
		camera->translate2D(-dx * 0.1, dy * 0.1);
	}
	if (mTestForm)
	{
		mTestForm->sendMouseMove(x, y);
	}
	//store status
	mMouseX = x;
	mMouseY = y;
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
	GLCamera *camera = mScene->getCamera();
	camera->zoom += dz;
	//store status
	mMouseWheel = wheel;
}

void TestClient::onSize(int width, int height)
{
	mView->setSize(width, height);
}

void TestClient::onClickEvent(GUIControl *ctl)
{
	//ctl->setPosition(ctl->getLeft() + 10, ctl->getTop());
}
