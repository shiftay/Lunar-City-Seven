#ifndef PLAYER_H

#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "console.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;


class Player
{
private:
	Console console;
	vector<string> inventory;
	int health;
	int hunger;
	int baseAtk;
	int oxygen;
	// int ammo;

public:
	Player();
	const int& playerAttacks() const;
	void ShowStats();
	bool hasItem(const string);
	void UseItem(const string);
	void AddItem(const string);
	void RemoveItem(const string);
	void Display();
	void ManageInven();				// from here to bottom are used for later implementations
	void updateHealth(const int);
	void updateHunger(const int);
//	void addAmmo(const int);

	void addO2(const int);
	void displayO2();

	void Reset();
	bool checkDead();


};

#endif