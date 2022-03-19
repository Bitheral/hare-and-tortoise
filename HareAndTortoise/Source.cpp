#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "console.h"

using namespace std;

class Track {
private:
	int position[2] = { 0,0 }, width = 0;
	double speed = 0;

public:
	Track(string filename) {

		// Open Track config file
		ifstream inFile(filename);


		// Check if the file exists
		if (inFile) {

			// File exists - Extract data
			string line;
			int lineCount = 1;
			while (getline(inFile, line))
			{
				/* Set data depending on line number
				* 
				* 1. X Position
				* 2. Y Position
				* 3. Track width
				* 4. Simulation speed
				*
				*/

				position[lineCount - 1] = stoi(line);
				switch (lineCount) {
				case 3:
					width = stoi(line);
					break;
				case 4:
					speed = stod(line);
					break;
				}
				lineCount++;
			}
		}
		else {

			// File doesn't exist - Throw an error with red text
			// then quit the program after 5 seconds.
			Console::setColour(Console::RED, Console::WHITE);
			Console::setCursorPosition(2,0);
			cout << "Error trying to read file." << endl;
			Console::setCursorPosition(3, 0);
			cout << "File `" << filename << "` may not exist" << endl;
			Console::setCursorPosition(5, 0);
			Console::setColour(Console::WHITE, Console::BLACK);
			cout << "`" << filename << "` requires the following format:" << endl;
			cout << "X Position - How far along the X Axis the Track is in the console window" << endl;
			cout << "Y Position - How far along the Y Axis the Track is in the console window" << endl;
			cout << "Width - How wide the track is along the X Axis" << endl;
			cout << "Simulation speed - How long it takes for each turn (in seconds)" << endl << endl;
			cout << "Example:" << endl;
			cout << "10" << endl;
			cout << "5" << endl;
			cout << "25" << endl;
			cout << "1.5" << endl;
			Console::setCursorPosition(26, 0);
			inFile.close();
			Sleep(5000);
			exit(1);
		}
	}


	// Get position on X Axis
	int getXPosition() {
		return position[0];
	}

	// Get position on Y Axis
	int getYPosition() {
		return position[1];
	}

	// Get width of track
	int getWidth() {
		return width;
	}

	// Get simulation speed
	int getSpeed() {
		return speed;
	}
};

class AnimalAction
{
public:
	string name;
	int chance, move;

	string sections[3];


	// Default class when no lines are entered
	AnimalAction() {
		name = "null";
	}

	AnimalAction(string entry) {
		char delimiter = ',';
		string acc = "";
		int currentSection = 0;
		for (int i = 0; i < entry.size(); i++)
		{
			// Go through each character of the string
			if (entry[i] == delimiter)
			{
				// If the chracter is a comma (,) add the
				// last set of chracters to a String array and
				// clear string and proceed to next section index
				sections[currentSection] = acc;
				acc = "";
				currentSection += 1;
			}
			else if (entry[i] == '_') {

				// If character is an underscore (_), replace with whitespace.
				acc += ' ';
			} else {

				// Add character to set of characters
				acc += entry[i];
			}

		}

		// Set name of action to zero-th index of sections
		name = sections[0];

		// Set chance of action to first index of sections
		chance = stoi(sections[1]);

		// Set move of action to second index of sections
		if (sections[2][0] == '-') {
			// If move is negative, remove minus (-)
			// from string and turn string to int
			// and turn int to negative
			sections[2].erase(sections[2].begin());
			move = -stoi(sections[2]);
		}
		else {
			// Convert string to int
			move = stoi(sections[2]);
		}
	}
};

class Animal {
private:
	string name;
	int position = 0;
	char character = 'A';
	vector<AnimalAction> actions;

public:
	Animal() {}

	Animal(string nameIn, int positionIn, char characterIn, string actionsFilename) {


		name = nameIn;
		position = positionIn;
		character = characterIn;
		ifstream inFile(actionsFilename);
		
		// Check if the actions file exists
		if (inFile) {
			// Action file exists
			string line;
			while (getline(inFile, line))
			{
				// Add a new AnimalAction with the line to actions vector
				actions.push_back(AnimalAction(line));
			}
		}
		else {
			// Actions file doesn't exist - Throw an error with red text
			// then quit the program after 5 seconds.
			Console::setColour(Console::RED, Console::WHITE);
			Console::setCursorPosition(2, 0);
			cout << "Error trying to read file." << endl;
			Console::setCursorPosition(3, 0);
			cout << "File `" << actionsFilename << "` may not exist" << endl;
			Console::setCursorPosition(5, 0);
			Console::setColour(Console::WHITE, Console::BLACK);
			cout << "`" << actionsFilename << "` requires the following format:" << endl;
			cout << "Name,Chance,Moves" << endl;
			cout << "Name - Name of action" << endl;
			cout << "Chance - Chance out of 100% of happening" << endl;
			cout << "Moves - Number of moves to go (can be negative or positive)" << endl << endl;
			cout << "Example:" << endl;
			cout << "Sleep,5,0" << endl;
			cout << "Trip,10,-5" << endl;
			cout << "Run,40,5" << endl;
			Console::setCursorPosition(26, 0);
			inFile.close();
			Sleep(5000);
			exit(1);
		}

		inFile.close();
	}

	AnimalAction getRandomAction() {
		int randomPercent, randomActionIndex;
		AnimalAction selectedAction;
		
		// Generate a random number from 1 to 100
		randomPercent = (rand() % 100) + 1;

		// Check if the selected action name is null
		while (selectedAction.name == "null") {
			// Name is null, thefore empty selected action.

			// Generate random number based on action vector
			randomActionIndex = (rand() % actions.size());

			// Checks if the random percentage is higher than the action's chance
			if (randomPercent < actions[randomActionIndex].chance) {
				// Set selected action to the action where the random
				// percentage is higher than the action's chance variable.
				selectedAction = actions[randomActionIndex];
				break;
			}
			else {
				// Generate a new random percentage and
				// new AnimalAction with name of null
				randomPercent = (rand() % 100) + 1;
				selectedAction = AnimalAction();
			}

		}

		return selectedAction;
	}

	// Get name
	string getName() {
		return name;
	}

	// Get position
	int getPosition() {
		return position;
	}


	// Get character
	char getCharacter() {
		return character;
	}

	// Set position
	void setPosition(int positionIn) {
		position = positionIn;
	}

	// set character
	void setCharacter(char characterIn) {
		character = characterIn;
	}
};

void drawLineH(int, int, int, char);
void drawCharacter(int, int, char);
void drawTrack(int, int, int, Animal, Animal, AnimalAction);


int main()
{
	// Set random seed to current time
	srand(time(0));

	// Old track configuration
	/*
	const int TRACK_LENGTH = 25;
	const int TRACK_X = 10;
	const int TRACK_Y = 5;
	const double TRACK_SPEED = 1.5;
	*/

	// New track configuration
	Track track = Track("track_config.txt");

	// Tracks moves for Hare and Tortoise
	// respectively
	int moves[2] = { 0, 0 };

	// Create new Animal instances with the following parameters
	Animal hare = Animal("Hare", 0, 'H', "hare_actions.txt");
	Animal tortoise = Animal("Tortoise", 0, 'T', "tortoise_actions.txt");

	// Set Console Window title
	Console::setWindowTitle("Hare and Tortoise");

	// Set Game Over to false
	bool gameOver = false;

	// Set turns to 0
	int turn = 0;

	// Create variables for current animal and other animal
	Animal currentAnimal, otherAnimal;

	// Check if game is not over
	while (!gameOver) {

		// Check turn
		if (!turn) {
			// If turn is 0
			// Set current animal to hare
			// and other animal to tortoise
			currentAnimal = hare;
			otherAnimal = tortoise;
		} else {
			// If turn is 1
			// and current animal to tortoise
			// Set other animal to hare
			currentAnimal = tortoise;
			otherAnimal = hare;

		}

		// Get an action from current animal
		AnimalAction action = currentAnimal.getRandomAction();

		// Checks if the current animal position
		// + the action moves is less or equal to 0
		if (currentAnimal.getPosition() + action.move < 0) {

			// Set current animal position to 0
			currentAnimal.setPosition(0);

			// Checks if the current animal position
			// + the action moves is more than track width
		} else if (currentAnimal.getPosition() + action.move >= track.getWidth()) {

			// Set current animal position
			// to track width and end game
			currentAnimal.setPosition(track.getWidth());
			gameOver = true;
		} else {

			// Add action move the the current animal's position
			currentAnimal.setPosition(currentAnimal.getPosition() + action.move);
		}

		// Draw the track with both animals, depending on their position
		drawTrack(track.getXPosition(), track.getYPosition(), track.getWidth(), currentAnimal, otherAnimal, action);

		// Resets cursor position to 0,0
		Console::setCursorPosition(0, 0);

		// Old speed method
		//Sleep(1500);

		// New speed method
		// Checks if track speed is 0
		if (!track.getSpeed()) {
			// Disable delay between each turn
			Sleep(0);
		}
		else {
			// Wait number of seconds before next turn
			// depending on track config
			Sleep(1000 * track.getSpeed());
		}

		// Applies currentAnimal and otherAnimal
		// instances back to their original instances
		// depending on the turn
		if (!turn) {
			hare = currentAnimal;
			tortoise = otherAnimal;
			
			// Add 1 move to hare
			moves[0] += 1;
		}
		else {
			tortoise = currentAnimal;
			hare = otherAnimal;

			// Add 1 move to tortoise
			moves[1] += 1;
		}

		// Set turn to opposite of current turn
		// e.g, 1 = 0, 0 = 1
		turn = !turn;
	}

	// Output game result
	ofstream gameResult("result.txt");

	// Checks if currentAnimal's name is Hare
	// If so, set winnerMoves to Hare's moves
	// otherwise, tortoise's moves
	int winnerMoves = currentAnimal.getName() == "Hare" ? moves[0] : moves[1];

	// Output game result to file
	// and close file
	gameResult << "The winner is the " << currentAnimal.getName() << ", it took " << winnerMoves << " moves to win.";
	gameResult.close();


	// Set cursor further down in
	// console and end the program
	Console::setCursorPosition(30, 0);
	return 0;
}

void drawLineH(int x, int y, int length, char character) {

	// For number is less than the length
	// Draw a character at x + i, y and the character

	for (int i = 0; i < length; i++) {
		drawCharacter(x + i, y, character);
	}

}

void drawCharacter(int x, int y, char character) {
	// Output character at specific x and y
	Console::setCursorPosition(y, x);
	cout << character;
}

void drawTrack(int x, int y, int length, Animal current, Animal other, AnimalAction action) {

	// Reset base track
	drawLineH(x, y, length, '.');
	drawLineH(x, y + 1, length * 10, ' ');
	drawLineH(x, y + 2, length * 10, ' ');

	// Checks if both animals are
	// in the same location
	if (current.getPosition() != other.getPosition()) {
		// Current animal and Other animal
		// are not in the same location

		// Draw animal's character at animal's
		// location
		drawCharacter(x + current.getPosition(), y, current.getCharacter());
		drawCharacter(x + other.getPosition(), y, other.getCharacter());

		// Set console cursor to x and y + 1
		// and output action of current animal
		Console::setCursorPosition(y + 1, x);
		cout << "The " << current.getName() << " used " << action.name << ", moving them " << action.move << " spaces";
	}
	else {
		// Current animal and Other animal
		// are in the same location

		// Draw 'B' (for both animals) at either
		// current or other's position
		drawCharacter(x + current.getPosition(), y, 'B');

		// Set console cursor position to x, y + 1
		// and output that both animals are in the same location.
		Console::setCursorPosition(y + 1, x);
		cout << "The Hare and Tortoise are in the same position.";

		// Set console cursor position to x, y + 2
		// and output action of current animal
		Console::setCursorPosition(y + 2, x);
		cout << "The " << current.getName() << " used " << action.name << ", moving them " << action.move << " spaces";
	}
}