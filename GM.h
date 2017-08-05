#pragma once
#include "rooms.h"

class GM
{
private:
	Player player1;
	Rooms rooms;
	int sceneCounter;
	int previousScene;
	bool gameOver;
public:
	GM();
	void Run();


};
