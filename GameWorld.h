#pragma once
#include "player.h"
#include "alien.h"
#include "console.h"

class GameWorld
{
private:
	Console console;
	Player player1;
	// controlling variables
	int sceneCounter;
	int previousScene;
	bool gameOver;
	// chapter 2
	bool coolingCompltd;
	bool valveCompltd;
	bool generatorCompltd;
	int genRefills;
	bool coolingAlien;
	bool cRoomAlien;


	// Chapter 1
	void Prologue();
	int startingScene();
	int ControlRoom(Player&);
	int SectorZero(Player&);
	int EVAC(Player&);
	int Cafeteria(Player&);
	int Barracks(Player&);
	int airLockB10(Player&);
	int MainHall(Player&);
	void SurvivorInteraction();
	void endScene(Player&, const int);
	// Chapter 2
	void chapter2Prologue();
	int chapter2start();
	void chapter2finale(Player&);
	void chapter2cutscene();
	int PPgenerator(Player&);
	int PPSafety(Player&);
	int PPCooling(Player&);
	int PPCRoom(Player&);
	bool coolingMG();
	bool safetyMG();
	bool PPcomputer(Player&);
	void refillStation(Player&);
	void GAMEOVER(Player&);


public:
	GameWorld();
	void begin();

};