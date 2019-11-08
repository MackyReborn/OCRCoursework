#pragma once
#include <fstream>
#include <string>
#include <vector>

using std::fstream;
using std::vector;
using std::string;

extern fstream* theFile;
extern fstream* saveFile;

class File // This could be a struct as it's components are all public
{
public:
	void read(); // Read function.
	void save(); // Save function.

	void init(); // Makes sure the files exist to solve certain runtime errors.

	vector<string>* songNames = new vector<string>(); // A place to store each song name. A vector is ideal as it is a dynamic array and we can keep pushing back the contents when we need to add a new entry.
	vector<string>* artists = new vector<string>(); // A place to store each artist that corresponds with the songName when we use the same int to access it.
};

// Extern it so it's defined with the linker. This allows us to use this object in multiple cpp files if we include this header.
extern File* songObject;
extern void leaderboards();