/*
 * GameTerrain.cpp
 *
 *  Created on: 20.02.2013.
 *      Author: idjukic
 */

#include "GameTerrain.h"

GameTerrain::GameTerrain()
{
	mTerrain = new GLTerrain();
	mTerrain->init(100, 100);
	mTerrain->generate(200, 10, 2, 0, 3);
	mTerrain->buildNormals();
}

GameTerrain::~GameTerrain()
{
	delete mTerrain;
}

void GameTerrain::draw()
{
	glPushMatrix();
	glTranslatef(-50, -50, 0);
	mTerrain->render();
	glPopMatrix();
}
