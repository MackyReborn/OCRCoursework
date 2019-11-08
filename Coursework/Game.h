#pragma once

#include <iostream>
#include <string>

#include "Files.h"

void Game(); // Allows us to access this function from other files where we include this header. We will be using this in Coursework.cpp, in the menu() function.

// Extern them so we can use them in other cpp files without the compiler getting confused about our referrences.
extern int randomInt();
extern int* score;