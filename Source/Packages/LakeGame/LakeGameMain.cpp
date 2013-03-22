/*
 * LakeGameMain.cpp
 *
 *  Created on: 22.03.2013.
 *      Author: idjukic
 */

#include "LakeGameClient.h"

int main(int argc, char **argv)
{
	AppServer *server = new AppServer("settings.ini");
	LakeGameClient *game = new LakeGameClient(server);

	server->run(game);

	delete game;
	delete server;
}
