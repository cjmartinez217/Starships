#include <iostream>
#include <climits>
#include <fstream>
#include <vector>
using namespace std;

struct StarShip
{
	struct Weapon
	{
		string weaponName;
		int powerRating;
		float powerConsumption;

		Weapon(string weaponName, int powerRating, float powerConsumption);
	};

	int firePower;
	string shipName;
	string shipClass;
	short length;
	int shield;
	float warpSpeed;
	vector<Weapon> weapons;
	StarShip(string shipName, string shipClass, short length, int shield, float warpSpeed, vector<Weapon>& weapons, int firePower);
};

void loadFile(string fileName, vector<StarShip>& starships);
void printShips(vector<StarShip>& starships);
void printMostPowerfulOverall(vector<StarShip>& starships);
void printMostPowerfulWeapon(vector<StarShip>& starships);
void printLeastPowerful(vector<StarShip>& starships);
void printUnarmedShips(vector<StarShip>& starships);


int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

	/* Load files here */
	vector<StarShip> starships;
	switch (option)
	{
	case 1:
		loadFile("friendlyships.shp", starships);
		break;
	case 2:
		loadFile("enemyships.shp", starships);
		break;
	case 3:
		loadFile("friendlyships.shp", starships);
		loadFile("enemyships.shp", starships);
		break;
	}


	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;

	cin >> option;

	/* Work your magic here */
	switch (option)
	{
	case 1:
		printShips(starships);
		break;
	case 2:
		printMostPowerfulWeapon(starships);
		break;
	case 3:
		printMostPowerfulOverall(starships);
		break;
	case 4:
		printLeastPowerful(starships);
		break;
	case 5:
		printUnarmedShips(starships);
		break;
	}

	return 0;
}


StarShip::StarShip(string shipName, string shipClass, short length, int shield, float warpSpeed, vector<Weapon>& weapons, int firePower)
{
	this->shipName = shipName;
	this->shipClass = shipClass;
	this->length = length;
	this->shield = shield;
	this->warpSpeed = warpSpeed;
	this->weapons = weapons;
	this->firePower = firePower;
}

StarShip::Weapon::Weapon(string weaponName, int powerRating, float powerConsumption)
{
	this->weaponName = weaponName;
	this->powerRating = powerRating;
	this->powerConsumption = powerConsumption;
}

void loadFile(string fileName, vector<StarShip>& starships)
{
	ifstream inFile(fileName, ios_base::binary);
	if (!inFile.is_open())
	{
		throw invalid_argument(fileName + " could not be opened!\n");
	}
	unsigned int count;
	inFile.read((char*)&count, sizeof(count));
	for (unsigned int i = 0; i < count; i++)
	{
		//get name
		unsigned int length;
		inFile.read((char*)&length, sizeof(length));
		char* tempName = new char[length];
		inFile.read(tempName, length);
		string shipName = tempName;
		delete[] tempName;

		//get class
		inFile.read((char*)&length, sizeof(length));
		char* tempClass = new char[length];
		inFile.read(tempClass, length);
		string shipClass = tempClass;
		delete[] tempClass;

		//get length
		short shipLength;
		inFile.read((char*)&shipLength, sizeof(shipLength));

		//get sheild capacity
		int shield;
		inFile.read((char*)&shield, sizeof(shield));

		//get warpSpeed;
		float warpSpeed;
		inFile.read((char*)&warpSpeed, sizeof(warpSpeed));

		//get weapons on ship
		unsigned int weaponCount;
		inFile.read((char*)&weaponCount, sizeof(weaponCount));
		vector<StarShip::Weapon> weapons;
		int firePower = 0;
		for (unsigned int j = 0; j < weaponCount; j++)
		{
			//get weapon name
			inFile.read((char*)&length, sizeof(length));
			char* tempName = new char[length];
			inFile.read(tempName, length);
			string weaponName = tempName;
			delete[] tempName;

			//get power rating
			int powerRating;
			inFile.read((char*)&powerRating, sizeof(powerRating));
			firePower += powerRating;

			//get power consumption
			float powerConsumption;
			inFile.read((char*)&powerConsumption, sizeof(powerConsumption));

			weapons.push_back(StarShip::Weapon(weaponName, powerRating, powerConsumption));
		}
		starships.push_back(StarShip(shipName, shipClass, shipLength, shield, warpSpeed, weapons, firePower));
	}


}

void printShips(vector<StarShip>& starships)
{
	for (unsigned int i = 0; i < starships.size(); i++)
	{
		cout << "Name: " << starships[i].shipName << endl;
		cout << "Class: " << starships[i].shipClass << endl;
		cout << "Length: " << starships[i].length << endl;
		cout << "Shield capacity: " << starships[i].shield << endl;
		cout << "Maximum Warp: " << starships[i].warpSpeed << endl;
		cout << "Armaments: " << endl;
		if (starships[i].weapons.size() == 0)
			cout << "Unarmed\n\n";
		else
		{
			for (unsigned int j = 0; j < starships[i].weapons.size(); j++)
			{
				cout << starships[i].weapons[j].weaponName << ", " << starships[i].weapons[j].powerRating << ", " << starships[i].weapons[j].powerConsumption << endl;
			}
			cout << "Total firepower: " << starships[i].firePower << endl << endl;
		}
	}
}

void printMostPowerfulOverall(vector<StarShip>& starships)
{
	StarShip mostPowerful = starships[0];
	for (unsigned int i = 0; i < starships.size(); i++)
	{
		if (starships[i].firePower > mostPowerful.firePower)
			mostPowerful = starships[i];
	}
	cout << "Name: " << mostPowerful.shipName << endl;
	cout << "Class: " << mostPowerful.shipClass << endl;
	cout << "Length: " << mostPowerful.length << endl;
	cout << "Shield capacity: " << mostPowerful.shield << endl;
	cout << "Maximum Warp: " << mostPowerful.warpSpeed << endl;
	cout << "Armaments: " << endl;
	if (mostPowerful.weapons.size() == 0)
		cout << "Unarmed\n\n";
	else
	{
		for (unsigned int j = 0; j < mostPowerful.weapons.size(); j++)
		{
			cout << mostPowerful.weapons[j].weaponName << ", " << mostPowerful.weapons[j].powerRating << ", " << mostPowerful.weapons[j].powerConsumption << endl;
		}
		cout << "Total firepower: " << mostPowerful.firePower << endl << endl;
	}
}

void printMostPowerfulWeapon(vector<StarShip>& starships)
{
	StarShip mostPowerful = starships[0];
	int biggestWeapon = INT_MIN;
	for (unsigned int i = 0; i < starships.size(); i++)
	{
		if (starships[i].weapons.size() > 0)
		{
			for (unsigned int j = 0; j < starships[i].weapons.size(); j++)
			{
				if (starships[i].weapons[j].powerRating > biggestWeapon)
				{
					mostPowerful = starships[i];
					biggestWeapon = starships[i].weapons[j].powerRating;
				}
			}
		}
	}
	cout << "Name: " << mostPowerful.shipName << endl;
	cout << "Class: " << mostPowerful.shipClass << endl;
	cout << "Length: " << mostPowerful.length << endl;
	cout << "Shield capacity: " << mostPowerful.shield << endl;
	cout << "Maximum Warp: " << mostPowerful.warpSpeed << endl;
	cout << "Armaments: " << endl;
	if (mostPowerful.weapons.size() == 0)
		cout << "Unarmed\n\n";
	else
	{
		for (unsigned int j = 0; j < mostPowerful.weapons.size(); j++)
		{
			cout << mostPowerful.weapons[j].weaponName << ", " << mostPowerful.weapons[j].powerRating << ", " << mostPowerful.weapons[j].powerConsumption << endl;
		}
		cout << "Total firepower: " << mostPowerful.firePower << endl << endl;
	}
}

void printLeastPowerful(vector<StarShip>& starships)
{
	StarShip leastPowerful = starships[0];
	int count = 1;
	while (leastPowerful.firePower == 0)
	{
		leastPowerful = starships[count];
		count++;
	}
	for (unsigned int i = 0; i < starships.size(); i++)
	{
		if (starships[i].weapons.size() > 0)
		{
			for (unsigned int j = 0; j < starships.size(); j++)
			{
				if (starships[i].firePower < leastPowerful.firePower)
					leastPowerful = starships[i];
			}
		}
	}
	cout << "Name: " << leastPowerful.shipName << endl;
	cout << "Class: " << leastPowerful.shipClass << endl;
	cout << "Length: " << leastPowerful.length << endl;
	cout << "Shield capacity: " << leastPowerful.shield << endl;
	cout << "Maximum Warp: " << leastPowerful.warpSpeed << endl;
	cout << "Armaments: " << endl;
	if (leastPowerful.weapons.size() == 0)
		cout << "Unarmed\n\n";
	else
	{
		for (unsigned int j = 0; j < leastPowerful.weapons.size(); j++)
		{
			cout << leastPowerful.weapons[j].weaponName << ", " << leastPowerful.weapons[j].powerRating << ", " << leastPowerful.weapons[j].powerConsumption << endl;
		}
		cout << "Total firepower: " << leastPowerful.firePower << endl << endl;
	}
}

void printUnarmedShips(vector<StarShip>& starships)
{
	for (unsigned int i = 0; i < starships.size(); i++)
	{
		if (starships[i].weapons.size() == 0)
		{
			cout << "Name: " << starships[i].shipName << endl;
			cout << "Class: " << starships[i].shipClass << endl;
			cout << "Length: " << starships[i].length << endl;
			cout << "Shield capacity: " << starships[i].shield << endl;
			cout << "Maximum Warp: " << starships[i].warpSpeed << endl;
			cout << "Armaments: " << endl;
			cout << "Unarmed\n\n";
		}
	}
}
