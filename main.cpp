#include <iostream>
#include <fstream>
#include "tsp.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Hello, World" << endl;

	// Enumeration (-e) or Nearest Neighbour Heuristic (-n)
	cout << argv[1] << endl;

	// Filename
	cout << argv[2] << endl;

	ifstream file;
	string line;
	file.open(argv[2]);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			cout << line << endl;
		}
		file.close();
	}

	return 0;
}