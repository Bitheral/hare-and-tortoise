#include <iostream>
#include "console.h"
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

void drawLineH(int, int, int, char);
void drawAnimal(int, int, char);

class AnimalAction
{
public:
	string name, chance;
	int move;

	AnimalAction(string entry) {
		stringstream ss(entry);
		vector<string> result;
		
		string substr, strMove;
		getline(ss, substr) >> name;
		getline(ss, substr, ',') >> chance;
		getline(ss, substr, ',') >> strMove;
		//while (ss.good())
		//{
		//	string substr;
		//	getline(ss, substr, ',');
		//	//result.push_back(substr);
		//	cout << substr;
		//}
		cout << name << chance << strMove;
	}
};

class Animal {
private:
	int position;
	char character;
	vector<AnimalAction> actions;

public:
	Animal(int positionIn, char characterIn, string actionsFilename) {
		position = positionIn;
		character = characterIn;
		ifstream inFile(actionsFilename);
		
		string line;
		while (getline(inFile, line))
		{
			actions.push_back(AnimalAction(line));
		}

		inFile.close();
	}

	void getRandomAction() {
		int randomPercent = (rand() % 100);
		for (int i = 0; i < actions.size(); i++) {
			cout << actions[i].chance;
			//int possibility = randomPercent / actions[i].chance;
			//cout << possibility;
		}
	}

	int getPosition() {
		return position;
	}

	int getCharacter() {
		return character;
	}

	void setPosition(int positionIn) {
		position = positionIn;
	}
};


int main()
{
	const int TRACK_LENGTH = 50;
	const int TRACK_X = 10;
	const int TRACK_Y = 5;

	Animal hare = Animal(0, 'H', "hare_actions.txt"); // Hare is when turn is 0
	Animal tortoise = Animal(0, 'T', "tortoise_actions.txt"); // Tortoise is when turn is 1
	Console::setWindowTitle("Hare and Tortoise");

	srand(static_cast<unsigned int>(time(0)));

	int turn = 0;
	while (tortoise.getPosition() != TRACK_LENGTH || hare.getPosition() != TRACK_LENGTH) {
		drawLineH(TRACK_X, TRACK_Y, TRACK_LENGTH, '.');

		if (!turn) {
			hare.getRandomAction();
			//hare.setPosition(hare.getPosition())
		}

		/*if (GetKeyState('T') & 0x8000)
		{
			tortoise.setPosition(tortoise.getPosition() + 1);
			

		}

		if (GetKeyState('H') & 0x8000)
		{
			hare.setPosition(hare.getPosition() + 1);

		}*/



		if (tortoise.getPosition() != hare.getPosition()) {
			drawAnimal(TRACK_X + tortoise.getPosition(), TRACK_Y, tortoise.getCharacter());
			drawAnimal(TRACK_X + hare.getPosition(), TRACK_Y, hare.getCharacter());
			drawLineH(TRACK_X, TRACK_Y + 1, TRACK_LENGTH, ' ');
		}
		else {
			drawAnimal(TRACK_X + hare.getPosition(), TRACK_Y, 'B');
			Console::setCursorPosition(TRACK_Y + 1, TRACK_X);
			cout << "The Hare and Tortoise are in the same position.";
		}

		Sleep(200);
	}

	// Output game result

	return 0;
}

void drawLineH(int x, int y, int length, char character) {
	Console::setCursorPosition(y, x);
	for (int i = 0; i < length; i++) {
		cout << character;
	}
}

void drawAnimal(int x, int y, char character) {
	Console::setCursorPosition(y, x);
	cout << character;
}


