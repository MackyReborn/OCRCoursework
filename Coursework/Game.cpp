#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <Windows.h>

#include "Game.h"
#include "Files.h"
#include "Auth.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int song = NULL; // Creating this to store the variable of the random number generator.
int prev = NULL; // Creating this to avoid having 2 questions the same in a row.
int* score = new int();

int randomInt()
{
	srand(time(NULL)); // Generates a random seed based on how many seconds have ellapsed from the epoch (Jan 1 1970) (Helpful for getting a true random value.)
	size_t MAX_SIZE = songObject->songNames->size();
	if (MAX_SIZE == 0)
	{
		cout << "File contains no songs!" << endl;
		if (Auth) delete Auth;
		if (songObject) delete songObject;
		if (theFile) delete theFile;
		if (score) delete score;
		cin.get();
		ExitProcess(EXIT_FAILURE);
	}
	int output = rand() % MAX_SIZE; // Random number between 0 and amount of songs
	prev = output;
	return output;
}

void Game()
{
	unsigned int guesses = NULL; // Int that can only be above 0 is given the value 0

	while (guesses < 2) // Saves compute power as we dont need to check if it's equal as well as less than if we do <= for every iteration of the loop.
	{
		song = randomInt();
		if (song == prev) song = randomInt();

		// Copies the songName from the contents of the file to the stack frame so it's in range of the function.
		string name = songObject->songNames->at(song);
		string artist = songObject->artists->at(song);

		string nameWithoutUnderscores = name;
		string artistWithoutUnderscores = artist;

		string ans = ""; // Creating a stack variable for our answer.

		// Replace the underscore with a space so it's easier to compare & cleaner to print.
		std::replace(nameWithoutUnderscores.begin(), nameWithoutUnderscores.end(), '_', ' ');
		std::replace(artistWithoutUnderscores.begin(), artistWithoutUnderscores.end(), '_', ' ');

		char firstLetter = name.at(0);
		vector<char> nextLetters;

		// Stores an initial value of 0 since that's where we want to start the search from, the first character.
		int oldLetter = NULL;

		for (int i = 0; i < name.length(); i++)
		{
			size_t next = name.find('_', oldLetter) + 1; // This returns the location of the letter right after the underscore.
			if (next == 0 || next == oldLetter) break; // Prevents the first letter from being stored multiple times.
			char nextLetter = name.at(next); // Defines the letter at the position defined previously.
			nextLetters.push_back(nextLetter); // Add the letter to the vector.
			oldLetter = next;
		}

		cout << "Artist: " << artistWithoutUnderscores << endl; // Prints the first clue - the artist name.
		cout << "Name: " << firstLetter; // Prints the second clue - the first letter to the song name.

		for (int i = 0; i < nextLetters.size(); i++) // For every entry in the vector.
		{
			cout << ' ' << nextLetters.at(i); // Print a space between the letters - make it look cleaner in the console.
		}
		cout << endl; // Clear the buffer after all the contents is printed.

		// Since getline() behaves randomly if the buffer isn't in perfect condition, we loop it if it isn't receiving input.
		while (ans.length() == 0)
		{
			getline(cin, ans);
		}

		for (int i = 0; i < ans.length(); i++) // Until we reach the string length.
			ans.at(i) = std::tolower(ans.at(i)); // Copy each character but lowercase.

		if (ans == nameWithoutUnderscores)
		{
			if (guesses == 0) *score += 3; // If they get the score correct the first time, give them 3 points.
			else *score += 1; // Otherwise just give them 1 for the correct answer.
			cout << "Correct Answer!\n" << endl;
			guesses = NULL; // Each correct iteration, it resets
		}
		else
		{
			guesses++; // Adds 1 to guesses if it isn't correct.
		}

		if (guesses > 2)
		{
			cout << "Ran out of Attempts. . .\n" << endl;
			return;
		}
	}
}