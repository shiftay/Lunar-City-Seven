#ifndef ALIEN_H

#define ALIEN_H

#include "player.h"
#include "console.h"

#include <ctime>
#include <cstdlib>

const int MIN = 5;
const string alienTypes[3] = { "Blob", "Fenix", "Devourer" };



class Alien
{
private:
	Console console;
	enum drops { MedKit, Ration };
	string name;
	int health;
	int damage;
	string drop;
	// accessors
	const int Attack() const;
	const string& dispName() const;
	const int& showHealth() const;
	// updater
	void isDamaged(const int);
	bool isDead();
	void onDeath(Player&);


public:
	Alien();
	void fight(Player&);
};







#endif