// OCR GCSE 2019 Coursework by Mackenzie Bowers
// Project Time - ~10:20:00 including debugging.

#include <iostream>
#include <string>
#include <thread> // Incase we want to add multithreading later
#include <Windows.h>

#include "Auth.h" // Contains the authentication class we need to authenticate our user
#include "Files.h" // Contains the file reading functions and class we need to get the songnames and artists from
#include "Game.h"

// Better than using (using namespace std) as we will not get confused with our referrences and own functions
using std::cout;
using std::cin;
using std::endl;
using std::string;

// Needs to be created on the heap otherwise the vectors are popped from the stack too early.
Authentication* Auth = new Authentication(); // Creating an object instance of our class so we can use it's functions and perameters - a basis for the login system.
File* songObject = new File(); // The whole filesystem.

void menu() // The main menu
{
	songObject->init(); // Makes sure the files exist to avoid runtime errors.
	songObject->read(); // Read the songs from the file.

	Game(); // Start the game
	cout << "\nYou Scored: " << *score << " Points. . ." << endl;

	songObject->save(); // Save the score when they are finished.
	cout << "Game Saved!\n" << endl;

	leaderboards();
}

int main()
{
	// 2 Variables on the stack in order to temporarily store inputs to authenticate.
	string username; 
	string password;

	cout << "Enter Username: " << endl; 
	cin >> username; // Get user input and store it in the username stack variable.

	cout << "Enter Password: " << endl;
	cin >> password; // Get the user input and store it in the password stack variable.

	if (Auth->validate(&username, &password)) // If the entered combination is correct, passing by referrence avoids copying of variables for no reason, improving performance drastically.
	{
		cout << "\nWelcome Back, " << username << "\n" << std::endl; // Welcoming message.
		menu(); // Now presents the main menu.
		cin.get(); // Let the user comprehend the information at the end of the menu.
	}
	else // Otherwise, unauthorise the access
	{
		cout << "Incorrect Combination" << std::endl;
		cin.get(); // Let the user read the message
		// We should not just end the program here as the objects we have created on the heap still need to be deleted to avoid leaks.
	}

	// Makes sure we free the memory to avoid leaks. The if statement avoids a crash which would be due to trying to delete memory which doesnt exist.
	if (Auth) delete Auth;
	if (songObject) delete songObject;
	if (theFile) delete theFile;
	if (score) delete score;

	ExitProcess(EXIT_SUCCESS); // Better than returning 0 as it handles kernel imperfections.
}