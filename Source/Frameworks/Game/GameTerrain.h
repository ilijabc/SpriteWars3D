/*
 * GameTerrain.h
 *
 *  Created on: 20.02.2013.
 *      Author: idjukic
 */

#ifndef GAMETERRAIN_H_
#define GAMETERRAIN_H_

#include "GameCommon.h"

class GameTerrain
{
public:
	GameTerrain();
	virtual ~GameTerrain();

	void draw();

private:
	GLTerrain *mTerrain;
};

#endif /* GAMETERRAIN_H_ */
