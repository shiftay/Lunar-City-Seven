#include "alien.h"


Alien::Alien()
{
	srand(static_cast<unsigned int>(time(0)));


	health = rand() % 10 + 1;
	if (health < MIN)
		health += MIN;

	damage = rand() % 5 + 1;
	

	name = alienTypes[rand() % 3];


}
//Accessors
const int& Alien::showHealth() const
{
	return health;
}

const string& Alien::dispName() const
{
	return name;
}

const int Alien::Attack() const
{
	return damage;
}

// Mutator
void Alien::isDamaged(const int dmgVal)
{
	health -= dmgVal;
}

bool Alien::isDead()
{
	if (health > 0)
		return false;
	else
		return true;
}

void Alien::onDeath(Player& player)
{
	int item = rand() % 2;
	int choice;
	
	int randVal = rand() % 5 + 1;

	switch (item)
	{
	case 0:
		console.output( "\nYou found a medkit on the alien's body\n");
		console.output( "Would you like to pick it up? (1) Yes (2) No\n");
		cin >> choice;
		if (choice == 1)
			player.AddItem("MedKit");
		else
			console.output( "You leave the medkit and walk away.\n");
		break;
	case 1:
		console.output( "\nYou found a Ration on the alien's body\n");
		console.output("Would you like to pick it up? (1) Yes (2) No\n");
		cin >> choice;
		if (choice == 1)
			player.AddItem("Food");
		else
			console.output( "You leave the ration and walk away.\n");
		break;
	//case 2:
	//	console.output( "You found " << randVal << " ammo on the alien's body\n");
	//	console.output( "Would you like to pick it up? (1) Yes (2) No");
	//	cin >> choice;
	//	if (choice == 1)
	//		player.addAmmo(randVal);
	//	else
	//		console.output( "You leave the ammo and walk away.\n");
	//	break;
	}

}


void Alien::fight(Player& player)
{
	int choice;

	console.output("\nYou have encountered a " + dispName() + ". You have no choice, you must fight!\n");

	do
	{
		console.output("\n");
		player.ShowStats();
		console.output("\n" + dispName() + " Health: " + console.toString(showHealth()));


		console.output("\n\n1. Fight.\n");
		console.output("2. Use item\n");
		console.output("Enter your choice: ");
		cin >> choice;


		switch (choice)
		{
		case 1:
			console.output("You swing and do " + console.toString(player.playerAttacks()) + " points of damage.\n");
			isDamaged(player.playerAttacks());
			console.output("The " + dispName() + " lunges at you dealing " + console.toString(Attack()) + " points of damage.\n");
			player.updateHealth(-Attack());
			break;
		case 2:
			player.ManageInven();
			break;
		default:
			console.output("***invalid choice***\n");
			break;
		}

		if (isDead())
		{
			console.output("\nYou have defeated " + dispName() + "\n");
			onDeath(player);
		}

	} while (!isDead());




}

