#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "Auth.h"

template <class T> // Generic data type for the append function.
void addUser(std::vector<T>* vecName, T data, std::vector<T>* vecName2, T data2) // Takes a vector object to append to and specifies the generic data type for the vector and data.
{
	// Add to the Vectors, cleans the code when appending multiple times.
	vecName->push_back(data);
	vecName2->push_back(data2);
}

std::string* Authentication::getUsername()
{
	return this->currentUser;
}

bool Authentication::validate(std::string* username, std::string* password) // Accepts a username and password to be passed by reference to save cpu cycles copying.
{
	for (int i = 0; i < this->Usernames->size(); i++) // Loop through all entries of our vector.
	{
		if (*username == this->Usernames->at(i)) // If the username is true
		{
			if (*password == this->Passwords->at(i)) // If the password is true
			{
				this->currentUser = username; // Define our current user so they can be referrenced later in the program.
				return true; // Confirmation is returned.
			}
		}
	}
	return false; // Otherwise, just decline the request.
}

Authentication::Authentication()
{
	// Add our registered users here
	addUser<std::string>(this->Usernames, "Mackenzie", this->Passwords, "admin");
	addUser<std::string>(this->Usernames, "Joe", this->Passwords, "123");
}