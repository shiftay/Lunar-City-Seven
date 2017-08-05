#include "GameWorld.h"

GameWorld::GameWorld()
{
	sceneCounter = 0;
	gameOver = false;
	//chapter 2 bools
	coolingCompltd = false;
	valveCompltd = false;
	generatorCompltd = false;
	genRefills = 2;
	coolingAlien = true;
	cRoomAlien = true;

}


void GameWorld::begin()
{
	Prologue();

	do
	{
		switch (sceneCounter)
		{
		case 0:
			sceneCounter = startingScene();
			break;
		case 1:
			sceneCounter = ControlRoom(player1);
			break;
		case 2:
			sceneCounter = Cafeteria(player1);
			break;
		case 3:
			sceneCounter = SectorZero(player1);
			break;
		case 4:
			sceneCounter = Barracks(player1);
			break;
		case 5:
			sceneCounter = MainHall(player1);
			break;
		case 6:
			previousScene = sceneCounter;
			sceneCounter = airLockB10(player1);
			break;
		case 7:
			previousScene = sceneCounter;
			sceneCounter = EVAC(player1);
			break;
		case 8:
			endScene(player1, previousScene);
			chapter2Prologue();
			sceneCounter = chapter2start();
			break;
		case 9:
			sceneCounter = PPCooling(player1);
			break;
		case 10:
			sceneCounter = PPSafety(player1);
			break;
		case 11:
			sceneCounter = PPgenerator(player1);
			break;
		case 12:
			sceneCounter = PPCRoom(player1);
			break;
		case 13:
			chapter2cutscene();
			chapter2finale(player1);
			gameOver = true;
			break;
		case 20:
			GAMEOVER(player1);
			break;
		}
	} while (!gameOver);


	console.output("\n\nThank you for playing Chapter 1 and 2 of LC-7\n");
}

// Chapter 1

void GameWorld::Prologue()
{
	console.output(	"The year is 2042, the Earth's population is growing at an unexpected rate.\n");
	console.output(	"Resources are starting to become sparce and so the only thing that we could\n");
	console.output(	"do is to start developing meaningful life out in space. With the easiest spot\n");
	console.output(	"being the Moon, we colonized and started to develop sustainable life on the\n");
	console.output(	"surface of the Moon itself.\n\n"); 

	console.output(	"Lunar City Seven is where this tale takes you, the most sophisticated colony\n");
	console.output(	"to date on the Moon. LC-7 houses a mining colony with rich output of both\n");
	console.output(	"Iron and Silicone, and is powered by it's four gigantic Helium-3 Power Plants.\n\n");

	console.output(	"You assume the role of Commander Alexis Freyja Tereshkova, as she attempts to\n");
	console.output(	"find out what is plagueing the great colony of Lunar City Seven.\n\n");

	system("pause"); // do not use on release;
}

int GameWorld::startingScene()
{
	int choice;
	console.output("August 17, 2042\t\t0407hours");

	console.output( "\n\nLess than hour after completing your shift, \nyou suddenly wake up from all sorts of alarms on LCS-7 sounding loud.");
	console.output( "\nYou quickly go outside your dorm to see what has happened, \nbut you don't see anyone except for yourself. \nThe lights slowly start turning off one by one. \nYou are shaking in fear.\n");
	
	console.output( "\nInfront of you there is a sign: \n");
	console.output( "-----------------------------------------\n");
	console.output( "|        <----------- Control Room      |\n");
	console.output( "|        Cafeteria------------->        |\n");
	console.output( "-----------------------------------------\n");

	console.output( "\n1. Control Room\n");
	console.output( "2. Cafeteria\n\n");
	do{
		console.output("You Decide to go: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		default:
			console.output( "***Invalid choice***\n");
			break;
		}
	} while (true);

}

int GameWorld::Cafeteria(Player& player)
{
	int choice;
	bool itemAcquired = false;
	bool leftCafe = false;

	console.output( "\nYou stumble through the door, knocking over a chair in the process.\n");
	console.output( "Looking up you see the same scene you've seen in the hallway, disarray.\n");
	console.output( "The Cafeteria you would go to for your sustenance is now a mess\nof flashing lights and scurrying rodents.\n");


	do
	{

		console.output( "\n1. Look out through the glass wall.\n");
		if (!itemAcquired)
			console.output( "2. Scavenge through the mess for item(s)\n");
		console.output( "3. Leave the cafeteria\n");
		console.output( "\nYou decide to: ");
		cin >> choice;


		switch (choice)
		{
		case 1:
			console.output( "\nThrough the glass you see the entire colony slowly being enveloped by darkness.\n");
			console.output( "The metal creaks with strain from the slow drain of power, as you look around\nthe world seems so small and fragile.");
			console.output( " Flickering lights nearby show the\nbarracks still semi-operational\n");
			break;
		case 2:
			if (!itemAcquired)
			{
				player.AddItem("Food");
				console.output( "\nYou find a can of Star Cola Lime!\n");
				itemAcquired = true;
			}
			else
			{
				console.output( "\nYou find nothing useful on the ground.\n");
			}
			break;
		case 3:
			leftCafe = true;
			break;
		default:
			console.output( "\n***Invalid Selection***\n");
			break;
		}
	} while (choice != 3);

	if (leftCafe)
	{
		// ADD CHOICE FOR WHICH WAY TO GO AND RETURN AS SUCH
		console.output( "\nWhen leaving the cafeteria you see a sign: \n");
		console.output( "-----------------------------------------\n");
		console.output( "|        <----------- Barracks          |\n");
		console.output( "|        Main Hall------------->        |\n");
		console.output( "-----------------------------------------\n");

		console.output( "\n1. Barracks\n");
		console.output( "2. Main Hall\n");
		do{
			console.output( "\nYou Decide to go: ");
			cin >> choice;

			switch (choice)
			{
			case 1:
				return 4;
				break;
			case 2:
				return 5;
				break;
			default:
				console.output( "***Invalid choice***\n");
				break;
			}
		} while (true);
	}

}

int GameWorld::Barracks(Player& player)
{
	Alien alien;
	int choice;
	bool itemAcquired = false;
	bool leftBX = false;
	bool barPower = true;
	bool keycardAcquired = false;

	console.output( "\nAs you skulk through the hallway into the barracks, you immediately notice the\nlights flickering wildly.");
	console.output( "Ammo crates are strewn accross the floor, gun racks\nare empty, no one is around.");
	console.output( " The silence is broken as a rat pushes out of\nsome items and runs across the floor through your legs and out through the door you just opened.\n");

	alien.fight(player);

	do{

		console.output( "\n1. Check the computer for Inventory logs\n");
		if (!keycardAcquired)
			console.output( "2. Search the main desk for anything important\n");
		if (!itemAcquired)
			console.output( "3. Rummage through the floor\n");
		console.output( "4. Leave the barracks.\n\n");
		console.output( "You survey the area and decide to: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			if(barPower)
			{
				if(player.hasItem("KeyCard_B"))
				{
					console.output( "\nThe screen flickers on and the supplies count for the barracks boots up.\n");
					console.output( "\n---------------------------------------------\n");
					console.output( "|           Barracks Inventory              |\n");
					console.output( "|       Plasma Grenade:    NULL             |\n");
					console.output( "|       Plasma Grenade:    NULL             |\n");
					console.output( "|       Plasma Grenade:    NULL             |\n");
					console.output( "^&@ADS!#!%S(%)DL%(LS(!L)$@$!^&**DSAW#$^\n");
					console.output( "The screen goes dark and power turns off in the barracks\n");
					barPower = false;
				}
				else
				{
					console.output( "\nYou do not have access for this computer.\n");
				}
			}
			else
			{
				console.output( "\nThe power is out in this sector, the computer doesn't respond.\n");
			}
			break;
		case 2:
			if (!keycardAcquired)
			{
				player.AddItem("KeyCard_B");
				console.output( "\nYou acquire the Barracks KeyCard\n");
				keycardAcquired = true;
			}
			else
			{
				console.output( "\nYou find nothing useful in the desk.\n");
			}
			break;
		case 3:
			if (!itemAcquired)
			{
				player.AddItem("Grenade");
				console.output( "\nAmong the rubble you find a Plasma Grenade still intact\n");
				itemAcquired = true;
			}
			else
			{
				console.output( "\nYou find nothing of use in the rubble.\n");
			}
			break;
		case 4:
			leftBX = true;
			break;
		default:
			console.output( "\n***Invalid choice***\n");
			break;
		}



	} while (choice != 4);


	if (leftBX)
	{
		// ADD CHOICE FOR WHICH WAY TO GO AND RETURN AS SUCH
		console.output( "When leaving the Barracks you see a sign: \n");
		console.output( "-----------------------------------------\n");
		console.output( "|       <----------- AIRLOCK B10         |\n");
		console.output( "-----------------------------------------\n");

		console.output( "\n1. AIRLOCK B10\n");
		do{
			console.output( "You Decide to go: ");
			cin >> choice;

			switch (choice)
			{
			case 1:
				return 6;
				break;
			default:
				console.output( "***Invalid choice***\n");
				break;
			}
		} while (true);
	}

}

int GameWorld::airLockB10(Player& player)
{
	int choice;
	bool itemAcquired = false;
	bool leftAB10 = false;


	if(player.hasItem("survivor"))
	{
		console.output(	"Josef, the new discovered survivor, and you make it safely to Air Lock B10.\n");
		console.output(	"Suddenly, Josef collapses, his skin is pale, lips turning blue, and he is\n");
		console.output(	"grasping for air. You try your best to help him, but he says: \n");
		console.output(	"'Go on without m. . . There's no tim. . .Save yoursel. . .' \n");
		console.output( "and he dies. . .\n");
		console.output(	"\nWhile tears are running down your cheeks, you pull yourself together.\n\n");
		player.RemoveItem("survivor");
	}

	console.output( "As you stumble into the partially destroyed airlock you survey your area\n");
	console.output( "The walls are wavering in the loss of power, the city is crumbling behind you\n");
	console.output( "You can hear screeching of metal collapsing upon itself in the distance behind\nyou.\n\n");


	do
	{
		console.output( "1. Look out through the airlock door.\n");
		if (!itemAcquired)
			console.output( "2. Grab the remaining EVA suit\n");
		console.output( "3. Check your inventory\n");
		console.output( "4. Leave the Airlock\n\n");
		console.output( "Enter your choice: ");
		cin >> choice;


		switch (choice)
		{
		case 1:
			console.output( "\nThrough the Airlock's window you see a slight glow in the distance. \nYou think back to"); 
			console.output( "your patrols in the past and remember the glow from\nPower Plant 3. Before it felt");
			console.output( "welcoming, now it feels almost haunting\nas LC-7 loses all power.\n\n");
			break;
		case 2:
			if (!itemAcquired)
			{
				player.AddItem("EVA_Suit");
				console.output( "\nYou equipped the EVA Suit.\n");
				itemAcquired = true;
			}
			else
			{
				console.output( "\nYou equipped the last remaining EVA Suit.\n");
			}
			break;
		case 3:
			player.Display();
			break;
		case 4:
			if(player.hasItem("EVA_Suit"))
			{	
				leftAB10 = true;
				break;
			}
			console.output( "\t\tPERMISSION DENIED\nYou can not leave without a functioning EVA Suit.\n");
			break;
		default:
			console.output( "\n***Invalid Selection***\n");
			break;
		}
	} while (!leftAB10);

	if (leftAB10)
	{

		console.output( "As the airlock depressurizes around you the darkness starts to envelop\nyour world");
		console.output( "you step forward into the emptiness.\n\n");
		return 8;
	}
}

int GameWorld::ControlRoom(Player& player)
{
	int choice;
	bool pickedup = false;
	bool leftCR = false;

	console.output( "\nYou arrive to the control room. \nYou carefully open the door and walk inside. \nYou look around and see flashing lights from the control panel signaling \ninbound communications and items are scattered across the ground.\n\n");
	do
	{
		console.output( "\n1. Check power plant status\n");
		if (!pickedup)
		{
			console.output( "2. Look for something useful\n");
		}
		console.output( "3. Listen to the inbound communications\n");
		console.output( "4. Leave the control room\n\n");

		console.output( "Enter your choice: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			console.output( "\nPower Plant 1 -- OFFLINE\t Sector 420\n");
			console.output( "Power Plant 2 -- OFFLINE\t Sector 421\n");
			console.output( "Power Plant 3 -- OFFLINE\t Sector 422\n");
			console.output( "Power Plant 4 -- OFFLINE\t Sector 423\n");
			break;
		case 2:
			if (!pickedup)
			{
				player.AddItem("Key Card_0");
				console.output( "\nKey Card to Sector 0 has been acquired.\n");
				pickedup = true;
			}
			else
			{
				console.output( "\nYou find nothing useful on the ground\n");
			}
			break;
		case 3:
			console.output( "\nYou see the following on the screen: ");
			console.output( "\n---------------------------------------------");
			console.output( "\n|&#$$#^*#$%-anyon-%%#$$#$#-hear u-%%#%$#-s. |\n| &%$%^#$-we ne-#$@^*%^&-ed help-%&%#%-Sect-|\n|&^&$#@$-or Zer-$*#*&#$@-o-&#@&%\t    |\n");
			console.output( "---------------------------------------------\n");
			break;
		case 4:
			leftCR = true;
			break;
		default:
			console.output( "\n***Invalid Selection***\n");
		}
	} while (choice != 4);

	if (leftCR)
	{
		// ADD CHOICE FOR WHICH WAY TO GO AND RETURN AS SUCH
		console.output( "\nWhen leaving the Control Room you see a sign: \n");
		console.output( "-----------------------------------------\n");
		console.output( "|        <----------- Sector 0          |\n");
		console.output( "|        Main Hall------------->        |\n");
		console.output( "-----------------------------------------\n");

		console.output( "\n1. Sector 0\n");
		console.output( "2. Main Hall\n");
		do{
			console.output( "You Decide to go: ");
			cin >> choice;

			switch (choice)
			{
			case 1:
				if(player.hasItem("Key Card_0"))
				{
					player.RemoveItem("Key Card_0");
					return 3;
				}
				else
				{
					console.output( "\nYou don't have access to Sector 0\n");
				}
				break;
			case 2:
				return 5;
				break;
			default:
				console.output( "\n***Invalid choice***\n");
				break;
			}
		} while (true);

	}
	return true;
}

int GameWorld::SectorZero(Player& player)
{
	Alien alien;
	int choice;
	bool pickedup = false;
	bool enteredroom = false;
	bool leftSZ;
	console.output( "\nAfter figuring out where you will use the key card, \nyou make your way to sector zero. \nOn arrival, you stumble upon a big entrance way with a \nslot to insert the key card. \nYou use the key card and the big metal door creaks open. \nYou cautiously go through the door, and see SECTOR ZERO on the wall \nunder a very dimming light.\n");

	do
	{
		console.output( "\n1. Check the evacuation logs\n");
		if (!enteredroom)
		{
			console.output( "2. Check room for supplies\n");
		}

		if (!pickedup)
		{
			console.output( "3. Look for something useful\n");
		}
		console.output( "4. Leave sector zero\n\n");
		console.output( "Enter your choice: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			console.output( "\nYou see the following on the screen: ");
			console.output( "\n---------------------------------------------\n");
			console.output( "|        Total Population: 5,349            |\n");
			console.output( "|        Current Population: 0              |\n");
			console.output( "---------------------------------------------\n");
			break;
		case 2:
			if (!enteredroom)
			{
				enteredroom = true;
				alien.fight(player);

			}
			else
			{
				console.output( "\nYou have already been inside this room.\n");
			}
			break;
		case 3:
			if (!pickedup)
			{
				player.AddItem("Food");
				console.output( "\nA space cookie has been acquired\n");
				pickedup = true;
			}
			else
			{
				console.output( "\nYou find nothing useful on the ground\n");
			}
			break;
		case 4:
			leftSZ = true;
			break;
		default:
			console.output( "\n***Invalid Selection***\n");
		}
	} while (choice != 4);

	if (leftSZ)
	{
		// ADD CHOICE FOR WHICH WAY TO GO AND RETURN AS SUCH
		console.output( "\nWhen leaving Sector Zero you see a sign: \n");
		console.output( "-----------------------------------------\n");
		console.output( "|        Emergency EVAC------------->   |\n");
		console.output( "-----------------------------------------\n");

		console.output( "1. Emergency EVAC\n");
		do{
			console.output( "You Decide to go: ");
			cin >> choice;

			switch (choice)
			{
			case 1:
				return 7;
				break;
			default:
				console.output( "***Invalid choice***\n");
				break;
			}

		} while (true);
	}
}

int GameWorld::EVAC(Player& player)
{
	int choice;
	bool pickedup = false;
	bool leftEVAC = false;

	if(player.hasItem("survivor"))
	{
		console.output(	"Josef, the new discovered survivor, and you make it safely to Air Lock B10.\n");
		console.output(	"Suddenly, Josef collapses, his skin is pale, lips turning blue, and he is\n");
		console.output(	"grasping for air. You try your best to help him, but he says: \n");
		console.output(	"'Go on without m. . . There's no tim. . .Save yoursel. . .' \n");
		console.output( "and he dies. . .\n");
		console.output(	"\nWhile tears are running down your cheeks, you pull yourself together.\n");
		player.RemoveItem("survivor");
	}

	console.output( "\nYou manage to make it to Emergency Evacuation District.\n");

	do
	{
		console.output( "\n1. Get Final Status Log\n");
		if (!pickedup)
		{
			console.output( "2. Look for EVA suit\n");
		}
		console.output( "3. Check your inventory\n");
		console.output( "4. Leave Emergency EVAC\n\n");
		console.output( "Enter your choice: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			console.output( "-----------------------------------------\n");
			console.output( "|        Total Population: 23,420        |\n");
			console.output( "|        Current Population: 1           |\n");
			console.output( "|        Power Level: 4%                 |\n");
			console.output( "|        Oxygen Level: 1%                |\n");
			console.output( "|        Communication Status: NULL      |\n");
			console.output( "-----------------------------------------\n");
			break;

		case 2:
			if (!pickedup)
			{
				player.AddItem("EVA_Suit");
				console.output( "\nYou equipped the EVA Suit.\n");
				pickedup = true;
			}
			else
			{
				console.output( "\nYou grabbed the last remaining EVA Suit.\n");
			}
			break;
		case 3:
			player.Display();
			break;
		case 4:
			if(player.hasItem("EVA_Suit"))
			{	
				leftEVAC = true;
				break;
			}
			console.output( "\n\t\tPERMISSION DENIED\nYou can not leave without a functioning EVA Suit.\n");
			break;
		default:
			console.output( "***Invalid Selection***\n");
		}
	} while (!leftEVAC);

	if (leftEVAC)
	{
		console.output( "You get into an emergency pod and get launched outside.\n");
		return 8;
	}

}

int GameWorld::MainHall(Player& player)
{
	int choice;
	bool itemAcquired = false;
	bool personFound = false;
	bool leftMH = false;


	console.output( "\nYou see a long hallway with flickering lights and wires hanging loose from the\n");
	console.output( "ceiling. You walk down the hallway and arrive at the main hall.\n\n");


	do{

		console.output( "\n1. Check the Shipping Manifest\n");
		if (!personFound)
			console.output( "2. Investigate strange sound in the rubble\n");
		if (!itemAcquired)
			console.output( "3. Rummage through the floor\n");
		if(player.hasItem("survivor"))
		{
			console.output( "4. Interact with the survivor\n");
		}
		console.output( "5. Survey the Area.\n");
		console.output( "6. Leave the Main Hall.\n\n");
		console.output( "You survey the area and decide to: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			console.output( "\n-----------------------------------------\n");
			console.output( "|         LC-7 Production Chart          |\n");
			console.output( "|                                        |\n");
			console.output( "|        Iron: 23,000 Tonnes             |\n");
			console.output( "|        Silicone: 12,000 Tonnes         |\n");
			console.output( "-----------------------------------------\n");
			break;
		case 2:
			if (!personFound)
			{
				player.AddItem("survivor");
				console.output( "\nAfter believing yourself to be the sole survivor, your whole world gets flipped\n");
				console.output( "upside down when you see another survivor in the rumble of the Main Hall.\n");
				console.output( "You manage to pull the survivor out of the rubble and sit him up.\n");
				personFound = true;
			}
			else
			{
				console.output( "\nYou find nothing else in the rubble.\n");
			}
			break;
		case 3:
			if (!itemAcquired)
			{
				player.AddItem("Food");
				console.output( "Among the rubble you find an intact military grade Ration.\n");
				itemAcquired = true;
			}
			else
			{
				console.output( "You find nothing of use in the rubble.\n");
			}
			break;
		case 4:
			if(player.hasItem("survivor"))
			{
				SurvivorInteraction();
			}
			else
			{
				console.output( "\n***Invalid choice***\n");
			}
			break;
		case 5:
			console.output( "\nYou look around the main hub of LC-7, the city you used to protect.\n");
			console.output( "You remember the vibrant scenes of people scuffling around trying to\n");
			console.output( "get to their jobs, of the cheery interactions of the people as they got on\n");
			console.output( "with their lives. Now it is nothing but destruction. Steel beams lay strewn\n");
			console.output( "accross the main foyer. Wires spark with what remaining electricity is left,\n");
			console.output( "and darkness starts enveloping the entire area.\n\n");
			break;
		case 6:
			leftMH = true;
			break;
		default:
			console.output( "***Invalid choice***\n");
			break;
		}



	} while (choice != 6);


	if (leftMH)
	{
		// ADD CHOICE FOR WHICH WAY TO GO AND RETURN AS SUCH
		console.output( "When leaving the Barracks you see a sign: \n");
		console.output( "-----------------------------------------\n");
		console.output( "|       <-----------EMERGENCY EVAC      |\n");
		console.output( "|        AIRLOCK B10 ---------->        |\n");
		console.output( "-----------------------------------------\n");

		console.output( "\n1. Emegency Evacuation\n");
		console.output( "2. Airlock B10\n");
		do{
			console.output( "You Decide to go: ");
			cin >> choice;

			switch (choice)
			{
			case 1:
				return 7;
				break;
			case 2:
				return 6;
				break;
			default:
				console.output( "***Invalid choice***\n");
				break;
			}
		} while (true);
	}



}

void GameWorld::SurvivorInteraction()
{
    int choice;

    do
    {
		console.output( "1. What is your name?\n");
        console.output( "2. How did you get stuck here? Are you okay?\n");
        console.output( "3. Do you know how to get out of this sector?\n");
        console.output( "4. Let's get out of here.\n\n");

        console.output( "Enter your choice: ");

        cin >> choice;

        switch(choice)
        {
            case 1:
                console.output( "\nHello, my name is Josef Ivanov. Thank you so much for saving my life!\n\n");
                break;
            case 2:
                console.output( "\nIt all happened so fast, I didn't know how to react. \nI'm not feeling so good, but don't worry I will not hold you back.\n\n");
                break;
            case 3:
                console.output( "\nYes, there is an EED(Emergency Evacuation District) if you go to the left\nat the end of main hall.\n\n");
                break;
            case 4:
                console.output( "\nYeah, we don't have time to chat, we need to get out of here.\n\n");
                break;
        }
    }while(choice != 4);
}

void GameWorld::endScene(Player& player, const int prevScene)
{

	if(prevScene == 7)
	{
		console.output(	"\nShortly after the pod launches the system begins to shutdown to a\nlack of power and fuel.");
		console.output(	"The world starts spiraling out of control and you watch\nas you come hurling back towards");
		console.output(	"the surface of the Moon. The pod bounces\na few times and comes to a rest in a crater.\n\n");

		console.output(	"You crawl out of the cracked, and deformed pod and are lucky\nto be wearing your EVA");
		console.output(	"suit. As you climb out of the crater you notice the\nHelium-3 Power Plants glowing slightly");
		console.output(	"in the distance.\n\n");
	}
	else
	{
		console.output(	"\nThe darkness begins to eat away at you, you start pushing your way\nthrough the tattered mess");
		console.output(	"of metal that is part of the Lunar City Seven\nused for containing it's Rovers. As you push");
		console.output(	"through the mess,\nyou start catching glimpses of the surface and craters of the moon.\n\n");

		console.output(	"After getting through the ragged pieces of the hangar you glimpse\nback at the City you");
		console.output(	"called home, to only realize it was\nbeginning to collapse under the pressure of having no");
		console.output(	"power. In the\ndistance you notice the Helium-3 Power Plants that seem to be the downfall\n");
		console.output(	"of Lunar City Seven.\n\n");
	}

	system("pause"); // do not use on release

	console.output(	"\nYou push towards the Power Plant, the slight glow in the Power Plant\nmakes no sense. How could");
	console.output(	"there still be power? What happened to the other\nresidents of LC-7? Driven by a desire for");
	console.output(	"knowledge you push on,\nignoring your sensors of extreme weather, ignoring the pain in your gut");
	console.output(	"from all\nthat has happened in the past few hours. You push on, because all you\nknew and loved");
	console.output(	"in the city you\nwere sworn to protect is crumbling behind you.\n\n");

	console.output(	"As the minutes pass you slowly stumble up to the somehow still function\nAirlock entrance to");
	console.output(	"Power Plant-3. You begin to key in your access code\nto enter the Power Plant when an");
	console.output(	"it happens.\nAn all-consuming flash of light floods your peripheral vision.\n\n"); 

	console.output(	"And you black out. . .\n");

}

// Chapter 2 -- scene 8 cont
void GameWorld::chapter2Prologue()
{
	system("pause");
	console.output("\n\n\t\t\t Chapter 2 - LC-7\n\n\n\n");
	system("pause");
	console.output("August 17, 2042\t\t0407hours\n\n");
	console.output("'Where could she be?' Lt Commander George Currie thinks to himself.\n\n");

	console.output("'Send out a city-wide search' He blasts into his communicator as he\n");
	console.output("continues his walk towards the Control Room of LC-7. It just doesn't\n");
	console.output("compute to him, people don't just disappear, it doesn't work that way.\n\n");

	console.output("It wasn't more than 2 hours ago that he saw her go towards her room,\n");
	console.output("for a few hours of sleep. It was a long night, and they had been up\n");
	console.output("working over the outgoing shipments from the mining facility. \n\n");

	console.output("As Lt Cmdr Currie strolls into the Control Room, he lets out a sigh,\n");
	console.output("'Anything yet?'\n\n");

	console.output("'No sir, nothing at all. Her comms are silent, and no pickup of her\n");
	console.output("signal at all' responds a recruit striking away at his keyboard.\n\n");

	console.output("Nothing makes sense anymore, She was the reason LC-7 was running like\n");
	console.output("a well oiled machine, now all the responsibility is on him.\n\n");

	system("pause");

	console.output("August 17, 2042\t\t1807hours\n\n");

	console.output("***BEEP*** 'SIR' ***BEEP******CRITICAL LEVELS OF CHERENKOV RADITION***\n\n");
	console.output("'What kid, it's just a spike by these graphs output' mutters Acting\n");
	console.output("Commander Currie\n\n");

	console.output("'I THINK WE'VE GOT HER' yells the recruit.\n\n");

	console.output("Thank god, he thinks to himself.\n\n");

	console.output("'Sir it doesn't make sense, she... she's at the powerplant airlock.'\n\n");

	console.output("How could this be? Why would she be there. 'Send all available units\n");
	console.output("to check the area, I'm suiting up and going'\n\n");

	console.output("Minutes later, Acting Commander George Currie is standing by the\n");
	console.output("entrance to Power Plant-3 'I'm standing right where you told me,\n");
	console.output("you're telling me she is also right here?'\n\n");


	console.output("'Sir yessir, that's exactly what our sensors tell us' the recruit\n");
	console.output("chimes in.\n\n");

	console.output("What in the hell is happening...\n\n");

	system("pause");

}

int GameWorld::chapter2start()
{
	int choice;
	console.output("August 17, 2042\t\t1807hours\n\n");

	console.output("Ears ringing, you awake from the blinding light still at the foot of\n");
	console.output("power plant. The blast shook everything, your EVA suit is flashing,\n");
	console.output("you run a quick system check on your suit.\n\n");

	console.output("Power Level: 67%\n");
	console.output("Oxygen Level 20% --- CRITICAL ---\n\n");

	console.output("Your oxygen levels are depleting quickly, you're in need of some\n");
	console.output("form of sustenance and fast.\n\n");

	console.output("*********************************************************************\n");
	console.output("Until power is repaired to LC-7, you will lose oxygen on every room\n");
	console.output("you go to, and every decision you make.\n");
	console.output("*********************************************************************\n\n");


	console.output("\nWhen Entering the Power Plant you see a sign: \n");
	console.output("-----------------------------------------\n");
	console.output("|       Safety Room - Go Straight       |\n");
	console.output("|       Generator------------->         |\n");
	console.output("|       <-------------Cooling           |\n");
	console.output("-----------------------------------------\n");

	console.output("1. Safety Room\n");
	console.output("2. Generator\n");
	console.output("3. Cooling\n");

	do{
		console.output("You Decide to go: ");
		cin >> choice;
		switch (choice)
		{
		case 1:
			return 10;
			break;
		case 2:
			return 11;
			break;
		case 3:
			return 9;
			break;
		default:
			console.output("***Invalid choice***\n");
			break;
		}
	} while (true);
}
// scene 11
int GameWorld::PPgenerator(Player& player)
{
	player.addO2(-5);
	bool leftGen = false;
	bool pickedup = true;
	int choice;

	if (!generatorCompltd)
	{
		console.output("\nYou walk into the generator room, to find lights flickering\n");
		console.output("and none of the machines making any noise.\n");
	}
	else
	{
		console.output("\nYou walk into the generator room, to the clunky noises\n");
		console.output("of the generator slowly starting to flicker on.\n");
	}


	do
	{
		if (player.checkDead())
		{
			return 20;
		}

		console.output("\n1. Check Oxygen Level\n");
		console.output("2. Use the Oxygen Refill Station\n");
		console.output("3. Investigate the room\n");
		if (player.hasItem("sparkplug"))
		{
			console.output("4. Use SPARKPLUG.\n");
		}
		console.output("5. Leave the Generator\n");

		console.output("Enter your choice: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			player.displayO2();
			break;
		case 4:
			if (!generatorCompltd)
			{
				if (player.hasItem("sparkplug"))
				{
					console.output("\nYou place the sparkplug into the machine ahead of you.\n");
					console.output("Some of the machines in the room begin to roar awake,\n");
					console.output("it seems like the generator is beginning to work.\n");
					player.RemoveItem("sparkplug");
					generatorCompltd = true;
				}
				else
				{
					console.output("\nYou do not have the required item!\n");
				}
			}
			else
				console.output("The generator is beginning to hum with low intial power.\n");
			player.addO2(-1);
			break;
		case 2:
			refillStation(player);
			break;
		case 3:
			console.output("\nYou look up at the rafters, everything is so dilapidated. You\n");
			console.output("worry that even if you find a way to start the power, it is\n");
			console.output("far too late. Shaking your head, you push those fears aside\n");
			console.output("and decide you have to figure this out, LC-7 deserves better.\n");

			player.addO2(-1);
			break;
		case 5:
			leftGen = true;
			break;
		default:
			console.output("***Invalid Selection***\n");
		}
	} while (!leftGen);

	if (leftGen)
	{
		console.output("\nWhen leaving the Generator you see a sign: \n");
		console.output("-----------------------------------------\n");
		console.output("|        Safety Room------------>       |\n");
		console.output("|        <---------Control Room         |\n");
		console.output("-----------------------------------------\n");

		console.output("1. Safety Room\n");
		console.output("2. Control Room\n");
		do{
			console.output("You Decide to go: ");
			cin >> choice;

			switch (choice)
			{
			case 1:
				return 10;
				break;
			case 2:
				if (player.hasItem("Keycard_PCR"))
					return 12;
				else
					console.output("You do not have the required access to this area\n");
				break;
			default:
				console.output("***Invalid choice***\n");
				break;
			}
		} while (true);
	}

}
// scene 10
int GameWorld::PPSafety(Player& player)
{
	player.addO2(-5);
	bool pickedup = false;
	int choice;
	bool leftSR = false;
	if (!valveCompltd)
	{
		console.output("\nAs you walk into the room, you hear the blaring alarm that signals\n");
		console.output("the safety valves are misaligned.\n\n");
	}
	else
	{
		console.output("\nYou walk into the safety room.\n\n");
	}

	do
	{
		if (player.checkDead())
		{
			return 20; 
		}

		console.output("\n1. Check Oxygen Level\n");
		console.output("2. Examine the area\n");
		if (!pickedup)
		{
			console.output("3. Look for something useful\n");
		}
		if (!valveCompltd)
			console.output("4. Reinitialize Safety Valves.\n");
		console.output("5. Leave Safety Room\n\n");

		console.output("Enter your choice: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			player.displayO2();
			break;
		case 2:
			console.output("The darkness that surrounds you slowly starts to close in as the\nflashing lights start dimming. At that moment, you look around the room\nin desperation for something that will make this stop and there it is.\nYou see it. The safety valve control panel.\n");
			player.addO2(-1);
			break;
		case 3:
			if (!pickedup && !player.hasItem("Keycard_PCR"))
			{
				player.AddItem("Keycard_PCR");
				console.output("\nKey Card to Power Plant Control Room has been acquired.\n");
				pickedup = true;
			}
			else
			{
				console.output("\nYou find nothing useful on the ground\n");
			}
			player.addO2(-1);
			break;
		case 4:
			if (!valveCompltd)
			{
				if (safetyMG())
				{
					console.output("~~~SAFETY VALVE REINITIALIZATION COMPLETED~~~\n");
					valveCompltd = true;
				}
				else
					console.output("***ERROR INCOMPLETE***\n");
			}
			else
				console.output("You already have reinitialized the safety sequence.\n");
			break;
		case 5:
			leftSR = true;
			break;
		default:
			console.output("***Invalid Selection***\n");
		}
	} while (!leftSR);


	if (leftSR)
	{
		console.output("\nWhen leaving Safety Room you see a sign: \n");
		console.output("-----------------------------------------\n");
		console.output("|       Control Room - Go Straight      |\n");
		console.output("|       Generator------------->         |\n");
		console.output("|       <-------------Cooling           |\n");
		console.output("-----------------------------------------\n");

		console.output("1. Control Room\n");
		console.output("2. Generator\n");
		console.output("3. Cooling\n");

		do{
			console.output("You Decide to go: ");
			cin >> choice;

			switch (choice)
			{
			case 1:
				if (player.hasItem("Keycard_PCR"))
					return 12;
				else
					console.output("You do not have the required access to this area\n");
				break;
			case 2:
				return 11;
				break;
			case 3:
				return 9;
				break;
			default:
				console.output("***Invalid choice***\n");
				break;
			}

		} while (true);
	}
}
// scene 9
int GameWorld::PPCooling(Player& player)
{
	player.addO2(-5);
	bool pickedup = false;
	int choice;
	bool leftCool = false;
	Alien alien;
	if (!coolingCompltd)
	{
		console.output("You walk into the room and see the calm waters around the churning vats\n");
		console.output("that are used to cool the power plant.\n");
	}
	else
	{
		console.output("The rushing water is almost too loud to even hear yourself think\n");
		console.output("clearly the cooling room is doing it's job.\n");
	}

	do
	{
		if (player.checkDead())
		{
			return 20;
		}

		if (coolingAlien)
		{
			alien.fight(player);
			coolingAlien = false;
		}

		console.output("\n1. Check Oxygen Level\n");
		console.output("2. Examine the area\n");
		if (!pickedup)
		{
			console.output("3. Look for something useful\n");
		}
		if (!coolingCompltd)
			console.output("4. Turn on the Feedwater System.\n");
		console.output("5. Leave Safety Room\n\n");

		console.output("Enter your choice: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			player.displayO2();
			break;
		case 2:
			console.output("The vats and pipes of clean water almost look serene in the darkness.\n");
			console.output("The glimmer off of the water seems to dance across the floor, making\n");
			console.output("you feel almost less lonely in this world that is breaking apart in\n");
			console.output("front of you.\n");
			player.addO2(-1);
			break;
		case 3:
			if (!pickedup && !player.hasItem("sparkplug"))
			{
				player.AddItem("sparkplug");
				console.output("\nYou find a sparkplug on the ground, wonder what this is for?\n");
				pickedup = true;
			}
			else
			{
				console.output("\nYou find nothing useful on the ground\n");
			}
			player.addO2(-1);
			break;
		case 4:
			if (coolingCompltd)
			{
				console.output("You hear the water rushing through the tubes, clearly\n");
				console.output("the system has been turned on.\n");
			}
			else
			{
				coolingCompltd = coolingMG();
				if (coolingCompltd)
					console.output("You hear the water rushing through the tubes.\n");
			}

			break;
		case 5:
			leftCool = true;
			break;
		default:
			console.output("***Invalid Selection***\n");
		}
	} while (!leftCool);


	if (leftCool)
	{
		console.output("\nWhen leaving Cooling Station you see a sign: \n");
		console.output("-----------------------------------------\n");
		console.output("|       Control Room------------->      |\n");
		console.output("|       <-------------Safety            |\n");
		console.output("-----------------------------------------\n");

		console.output("1. Control Room\n");
		console.output("2. Safety\n");

		do{
			console.output("You Decide to go: ");
			cin >> choice;

			switch (choice)
			{
			case 1:
				if (player.hasItem("Keycard_PCR"))
					return 12;
				else
					console.output("You do not have the required access to this area\n");
				break;
			case 2:
				return 10;
				break;
			default:
				console.output("***Invalid choice***\n");
				break;
			}

		} while (true);
	}
}
// scene 12
int GameWorld::PPCRoom(Player& player)
{
	player.addO2(-5);
	int choice;
	bool leftPPCR = false;
	Alien alien;

	console.output("\nThe door accepts the keycard, and screeches open slowly.\n");
	console.output("You step inside the Power Plant's control room.\n\n");

	do
	{
		if (player.checkDead())
		{
			return 20; 
		}

		if (cRoomAlien)
		{
			alien.fight(player);
			cRoomAlien = false;
		}


		console.output("\n1. Check Oxygen Level\n");
		console.output("2. Boot Control Room Computer\n");
		console.output("3. Look out the window.\n");
		console.output("4. Leave Control Room\n\n");

		console.output("Enter your choice: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			player.displayO2();
			break;
		case 2:
			if (PPcomputer(player))
			{
				return 13; // send to cutscene;
			}
			player.addO2(-1);
			break;
		case 3:
			console.output("Outside everything is so dark... You can see the remenants\n");
			console.output("of LC-7. It looks so small and yet it was the pride of\n");
			console.output("the colonies on the Moon. You have to fix this, even if\n");
			console.output("it is the last thing you do.\n");
			break;
		case 4:
			leftPPCR = true;
			break;
		default:
			console.output("***Invalid Selection***\n");
		}
	} while (!leftPPCR);


	if (leftPPCR)
	{
		console.output("\nWhen leaving Control Room you see a sign: \n");
		console.output("-----------------------------------------\n");
		console.output("|       Saefty Room - Go Straight       |\n");
		console.output("|       Generator------------->         |\n");
		console.output("|       <-------------Cooling           |\n");
		console.output("-----------------------------------------\n");

		console.output("1. Safety Room\n");
		console.output("2. Generator\n");
		console.output("3. Cooling\n");

		do{
			console.output("You Decide to go: ");
			cin >> choice;

			switch (choice)
			{
			case 1:
				return 10;
				break;
			case 2:
				return 11;
				break;
			case 3:
				return 9;
				break;
			default:
				console.output("***Invalid choice***\n");
				break;
			}

		} while (true);
	}
}

void GameWorld::chapter2cutscene()
{
	console.output("\n\nAugust 17, 2042\t\t2207hours");

	console.output("\n\n'WHERE THE HELL IS SHE?' barks Lt Cmdr Currie shouts into his\n");
	console.output("communicator. He had been walking around the Helium-3 Power\n");
	console.output("Plant for the past few hours following a ghost apparently.\n\n");

	console.output("'sssssir, it sssays she is right on your position' the \n");
	console.output("recruit shyly responds.\n\n");

	console.output("'Listen to me kid, I'm too old for this right now. Either\n");
	console.output("you're calling me mentally unstable, or your systems are\n");
	console.output("wrong. Fix it!' yells the Lt Commander. \n\n");

	console.output("God damnit Alexis, what have you done.. he thinks to\n");
	console.output("himself. It has been almost 24hours since Commander\n");
	console.output("Tereshkova had disappeared and yet this ghost trail only\n");
	console.output("just recently had begun.\n\n");

	console.output("'Sir we've rebooted all of our systems, it is still\n");
	console.output("telling us she is there...' the recruit chimes in.\n\n");

	console.output("'God damnit kid, I'm coming back to the control room\n");
	console.output("and it's not going to be pretty for you'....\n");

	system("pause");
}

void GameWorld::chapter2finale(Player& player)
{
	int choice;
	bool surveyed = false;
	bool pickedup = false;
	bool leftEED = false;

	console.output("\n\nAugust 17, 2042\t\t2207hours\n");

	console.output("\nYou've walked across the surface of the moon, towards the\n");
	console.output("looming giant colony LC-7 and are just now beginning to\n");
	console.output("close in on the Emergency Evacuation Hub for civilians\n\n");

	console.output("You use your newly created access from the Powerplant to\n");
	console.output("reenter through an extra Airlock.\n\n");

	console.output("However since the systems in LC-7 are just beginning\n");
	console.output("to reboot you are unsure of how to proceed through the\n");
	console.output("area.\n\n");

	do{
		console.output("1. Look around the area\n");
		console.output("2. Scavenge the ground\n");
		if (surveyed)
			console.output("3. Enter the vents\n");
		console.output("Enter your choice: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			console.output("You glance around the Emergency Evacuation district, seeing a lot\n");
			console.output("of metal collapsed across the floor. A piece of wiring swings across\n");
			console.output("infront of your face and you turn out of the way and see a vent up\n");
			console.output("in the corner of the room.\n\n");
			surveyed = true;
			break;
		case 2:
			if (!pickedup)
			{
				player.AddItem("Food");
				console.output("\nA space cookie has been acquired\n");
				pickedup = true;
			}
			else
			{
				console.output("\nYou find nothing useful on the ground\n");
			}
			break;
		case 3:
			if (surveyed)
				leftEED = true;
			else
				console.output("You require more information.\n");
			break;
		default:
			console.output("***INVALID SELECTION***\n");
		}
	} while (!leftEED);

	if (leftEED)
	{
		choice = 0;
		console.output("You crawl through the vents towards the end, in hopes that it'll get\n");
		console.output("you as close to your personal quarters as possible. As you emerge\n");
		console.output("from the vents you find that you've come out in the Main Control Room\n");
		console.output("of LC-7\n\n");

		console.output("You wander over to the main console, with your new access you\n");
		console.output("boot into the computer to see an odd option\n\n");

		console.output("Commander Tereshkova's Final Log\n\n");
		do{
			console.output("1. View the Log\n");
			console.output("Enter your choice: ");
			cin >> choice;

			switch (choice)
			{
			case 1:
				console.output("As you type into the computer, your head starts spinning and\n");
				console.output("everything seems to fade to black...\n");
				return;
			default:
				console.output("***INVALID CHOICE***\n");
			}
		} while (choice != 1);
	}
}

bool GameWorld::coolingMG()
{
	const string word[3] = {"helium", "iron", "silicon"};
	string sWord = word[rand() % 3];
	string mixedWord = sWord;
	int chances = 5;
	string input;

	size_t length = mixedWord.size();
	for (size_t i = 0; i < length; i++)
	{
		size_t RandomIndex = (rand() % length);
		char temp = mixedWord[i];
		mixedWord[i] = mixedWord[RandomIndex];
		mixedWord[RandomIndex] = temp;
	}


	console.output("\nThe computer turns on and on the screen blinks.\n\n");
	console.output("Please input the password: _  _ _ _ _ _ \n");
	console.output("You begin to input your access code to get harrassed by a\n");
	console.output("ACCESS DENIED screen.\n");

	console.output("You enter through a backdoor you were taught by George.\n");
	console.output("On the screen flashes please enter the keyphrase.\n\n");
	do
	{
		console.output("Chances Left: " + console.toString(chances));
		console.output("\t\t" + mixedWord + "\n");
		console.output("What does it say? ");
		cin >> input;

		if (input != sWord)
			chances--;

	} while (input != sWord && chances != 0);

	if (chances == 0)
		return false;
	else
		return true;


}

bool GameWorld::safetyMG()
{
	int chances = 5;
	int input;
	int scrtNum1, scrtNum2;

	srand(time(0));

	//***Formula = rand() % range + min;	***Range = max - min + 1
	scrtNum1 = rand() % 5 + 1; // Range from 1 to 5
	scrtNum2 = rand() % (10-6) + 5; // Range from 5 to 10 


	console.output("\nThe computer boots up to a window that says: \n\n");
	console.output("In order to reboot system please input the correct number sequence\n");
	console.output("You don't know the sequence, seeing as you're just the commander of\n");
	console.output("the entire city and don't know the inner workings for the power plant\n");
	console.output("You decide to guess...\n\n");
	do{

		console.output("Chances left: " + console.toString(chances));
		console.output("\nPLEASE REENTER FIRST NUMBER(1-5): ");
		cin >> input;

		if (input > scrtNum1)
		{
			console.output("***INVALID INPUT(too high)***\n");
			chances--;
		}
		else if (input < scrtNum1)
		{
			console.output("***INVALID INPUT(too low)***\n");
			chances--;
		}

	} while (input != scrtNum1 && chances != 0);
	
	if (input == scrtNum1)
		console.output("It accepts the first number and the computer prints: \n");
	do{

		console.output("Chances left: " + console.toString(chances));
		console.output("\nPLEASE REENTER SECOND NUMBER(5-10): ");
		cin >> input;

		if (input > scrtNum2)
		{
			console.output("***INVALID INPUT(too high)***\n");
			chances--;
		}
		else if (input < scrtNum2)
		{
			console.output("***INVALID INPUT(too low)***\n");
			chances--;
		}

	} while (input != scrtNum2 && chances != 0);



	if (chances == 0)
		return false;
	else
		return true;
}

bool GameWorld::PPcomputer(Player& player)
{
	int input;
	int tries = 0;

	if (!player.hasItem("AccessCard"))
	{
		console.output("\nThe computer screeches on slowly. You key in your password and\n");
		console.output("are confronted by the ACCESS DENIED screen. Really strange...\n");
		console.output("You boot into the backend of the system and are confronted with\n");
		console.output("a screen asking for your credentials. Confused by none of your\n");
		console.output("access codes working you attempt to reset your access.\n\n");

		do {
			console.output("To reset your access, please enter Helium's Atomic Number: ");
			cin >> input;
			if (input != 2)
			{
				console.output("***INCORRECT***\n");
				tries++;
			}

			if (tries == 2)
				console.output("Helium is the Second(2) Element\n");

		} while (input != 2);

		tries = 0;

		do {
			console.output("To finish resetting your access, please enter Silicon's Atomic Number: ");
			cin >> input;
			if (input != 14)
			{
				console.output("***INCORRECT***\n");
				tries++;
			}

			if (tries == 2)
				console.output("Silicon is the Fourteenth(14) Element\n");

		} while (input != 14);

		console.output("Your access card has been updated\n\n");
		player.AddItem("AccessCard");
	}


	console.output("\nThe computer boots into a DOS menu:");

	
	do
	{
		console.output("\n1. Plant Status\n");
		console.output("2. Reboot Powerplant\n");
		console.output("Enter your choice: ");
		cin >> input;

		switch (input)
		{
		case 1:
			console.output("GENERATOR --- " + console.toString(generatorCompltd) + "\n");
			console.output("SAFETY VALVES --- " + console.toString(valveCompltd) + "\n");
			console.output("COOLANT --- " + console.toString(coolingCompltd) + "\n");
			break;
		case 2:
			if (coolingCompltd && valveCompltd && generatorCompltd)
			{
				console.output("Engines begin to roar, system lights begin to flash on in the room\n");
				console.output("power seems to be flooding back into the area.\n");
				console.output("You see through the windows lights beginning to flicker on across the compound\n");
				return true;
			}
			else
			{
				console.output("**ERROR***ERROR***ERROR***\n\nSYSTEMS ARE IN DISREPAIR REBOOT NOT POSSIBLE\n");
				return false;
			}
			break;
		default:
			console.output("Invalid Choice");
		}


	} while (input != 2);

	return false;

}

void GameWorld::refillStation(Player& player)
{
	int choice;

	console.output("\nThere are " + console.toString(genRefills) + " Refills remaining.\n");
	console.output("1. Yes\n");
	console.output("2. No\n");
	console.output("Would you like to refill: ");
	cin >> choice;
	if (choice == 1)
	{
		if (genRefills > 0)
		{
			player.addO2(50);
			genRefills--;
		}
		else
			console.output("This Refill station is currently recharging\n");
	}
	else
		console.output("You walk away from the Refill Station\n");
}

void GameWorld::GAMEOVER(Player& player)
{
	int choice;

	console.output("\n\nAlexis' collapses to her knees, choking back tears as\n");
	console.output("everything begins to fade to black...\n\n");
	console.output("You have died... GAME OVER\n\n");
	console.output("1. Play Again!\n");
	console.output("2. Quit.\n");

	do
	{
		console.output("Enter your choice: ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			//reset everything
			player.Reset();
			sceneCounter = 0;
			gameOver = false;
			coolingCompltd = false;
			valveCompltd = false;
			generatorCompltd = false;
			genRefills = 2;
			coolingAlien = true;
			cRoomAlien = true;
			system("cls");
			return;
		case 2:
			gameOver = true;
			return;
			break;
		default:
			console.output("***INVALID CHOICE***\n");
		}
	} while (choice != 2);

}