#include "player.h"


Player::Player()
{
	// base inventory size
	baseAtk = 5;
	hunger = 0; // used for later implementation
	health = 25; // used for later implementation
	oxygen = 20;
}

void Player::ShowStats()
{
	console.output("Alexis' Health: " + console.toString(health));
}


bool Player::hasItem(const string itemVal)
{
	bool has = false;

	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == itemVal)
		{
			has = true;
			break;
		}
	}

	return has;
}

void Player::Display()
{
	console.output("\nAlexis' inventory: \n");

	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] != "")
		{
			console.output(console.toString(i) + "\t" + inventory[i] + "\n");
		}
	}
	console.output("\n");
}

void Player::UseItem(const string itemVal)
{
	if (itemVal == "Food")
	{
		if (health >= 25)
		{
			console.output("You are already at full health");
			return;

		}
		else
		{
			console.output("You eat the food and gain 7 health points\n");
			updateHealth(7);
			RemoveItem(itemVal);
		}
	}
	else if (itemVal == "MedKit")
	{
		if (health >= 25)
		{
			console.output("You are already at full health");
			return;
		}
		else
		{
			console.output("You use the medkit and gain 25 health points\n");
			updateHealth(25);
			RemoveItem(itemVal);
		}

	}
	else
	{
		console.output(itemVal + " has no use here.");
	}
}

void Player::ManageInven()
{
	int choice;
	bool itemUsed = false;

	if (inventory.empty())
	{
		console.output("Nothing of use in your inventory\n");
		return;
	}

	Display();

	do
	{
		console.output("Which item would you like to use: ");
		cin >> choice;

		if (choice > inventory.size() || choice < 0)
		{
			console.output("invalid choice\n");
		}
		else
		{
			UseItem(inventory[choice]);
			itemUsed = true;
		}
	} while (!itemUsed);

}

void Player::AddItem(const string itemVal)
{
	inventory.push_back(itemVal);
}

void Player::RemoveItem(const string itemVal)
{
	if (hasItem(itemVal))
	{
		for (int i = 0; i < inventory.size(); i++)
		{
			if (inventory[i] == itemVal)
			{
				inventory.erase(inventory.begin() + i);
				break;
			}
		}
	}
}

const int& Player::playerAttacks() const
{
	return baseAtk;
}


void Player::updateHealth(const int dmgVal)
{
	
	health += dmgVal;

	if (health > 25)
	{
		health = 25;
	}
	else if (health < 0)
	{
		health = 0;
	}
	// can pass negative to damage player
}

void Player::updateHunger(const int foodVal)
{
	hunger += foodVal;

	if (hunger < 0)
	{
		hunger = 0;
	}
	// can pass negative to lower hunger
}

//void Player::addAmmo(const int ammoVal)
//{
////	ammo += ammoVal;
//}

void Player::addO2(const int oxyVal)
{
	oxygen += oxyVal;

	if (oxygen > 100)
		oxygen = 100;
}

void Player::displayO2()
{
	console.output("\nAlexis' Oxygen Level: " + console.toString(oxygen) + "\n");
}

bool Player::checkDead()
{
	if (health <= 0 || oxygen <= 0)
		return true;
	else
		return false;
}

void Player::Reset()
{
	health = 25;
	oxygen = 20;
	inventory.clear();
}