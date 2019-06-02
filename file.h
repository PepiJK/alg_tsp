#ifndef file_H
#define file_H

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class file
{
private:
	ifstream fileInput;

public:
	file(string filename);
	int iNumberOfPoints();
	double **fMatrix(int iArraySize);
	~file();
};

#endif