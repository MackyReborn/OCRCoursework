#include <fstream>
#include <iostream>
#include <algorithm>
#include <Windows.h>

#include "Files.h" // Access to the Files class that we have already defined.
#include "Auth.h" // Access to the username
#include "Game.h" // Access to the score

using std::fstream;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

// Creating 2 fstream objects to files we can read or write from
fstream* theFile = new fstream(); // Gamedata
fstream* saveFile = new fstream(); // Savedata

void File::init()
{
	fstream temp("gamedata.txt"); // Tries to locate and open the file.
	
	if (!temp) // If the file doesn't exist.
	{
		cout << "\nCould not locate song file. Program will now terminate" << endl;

		// Deallocate all the heap memory if it exists to avoid memory leaks.
		if (Auth) delete Auth;
		if (songObject) delete songObject;
		if (theFile) delete theFile;
		if (score) delete score;

		cin.get(); // Await user confirmation to exit.

		ExitProcess(EXIT_FAILURE); // Exit the process.
	}
}

void File::read()
{
	// Temporary stack objects so we can store the information before it goes into our vector.
	string songName;
	string artist;

	theFile->open("gamedata.txt"); // First open the gamedata.txt file so it's ready to be read from

	if (!theFile->is_open()) // If theFile could not be opened
		return; // Exit the function.

	while (*theFile >> songName >> artist) // Whilever there's an input to be stored in these variables, do it and also. . .
	{
		this->songNames->push_back(songName); // . . . copy the songname to this vector. . .
		this->artists->push_back(artist); // and also copy the artist to this vector . . .
	}
}

void File::save()
{
	saveFile->open("savedata.txt", std::ios::app); // Append mode
	*saveFile << *Auth->getUsername() << " " << *score; // Save the username and score.
	saveFile->close(); // Close the file because the next time we want to use it will be when reading it and we will not want it in append mode.
}

bool wayToSort(int i, int j) { return i > j; } // Simple function that allows us to reverse the sort function so biggest is first.

void leaderboards()
{
	vector<string> usernames;
	vector<int> scores;

	if (!saveFile->is_open()) // If the save file is not open
	{
		saveFile->open("savedata.txt");
	}
	string tempUsername;
	int tempScore;

	while (*saveFile >> tempUsername >> tempScore) // While-ever there is an entry
	{
		// Add them to the vectors for later when we need to compare them.
		usernames.push_back(tempUsername);
		scores.push_back(tempScore);
	}
	std::sort(scores.begin(), scores.end(), wayToSort); // Sort the vector with the biggest number first. The function at the end doesn't need () as we are passing a function pointer.
	
	cout << "Leaderboards: " << endl; // Title.
	for (int i = 0; i < scores.size() && i < 6; i++) // Iterate through the size of the array until it reaches 5 instances.
	{
		cout << usernames.at(i) << " "; // User.
		cout << scores.at(i) << endl;  // Their score.
	}
}