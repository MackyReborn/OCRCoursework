#pragma once

#include <string>
#include <vector>

using std::vector;
using std::string;

template <class T>
void appendVec(std::vector<T>* vecName, T data); // Function to automatically push contents into a vector.

class Authentication // Class Dedicated to Authentication
{
public:
	Authentication(); // Constructor adds our username and password list
	bool validate(std::string* username, std::string* password); // Checks an entered username and password compared with the entries in the vectors in the class.
	string* getUsername(); // Returns the current username that has been logged in.
private:
	// These will be defined in the constructor. Created on the heap so that the lifetime will be extended.
	vector<string>* Usernames = new vector<string>(); // All possible usernames will be stored here
	vector<string>* Passwords = new vector<string>(); // All possible passwords will be stored here

	string* currentUser = new string();
};
extern Authentication* Auth; // Extern it so it's defined with the linker. This allows us to use this object in multiple cpp files if we include this header.