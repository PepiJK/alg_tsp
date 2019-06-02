#include "file.h"

// Open File argv[2]
file::file(string filename)
{
	fileInput.open(filename);

	if (fileInput.fail())
	{
		cout << "Error could not open file" << endl;
		exit(0);
	}
}

// Return first line of input file = Number of Points in File
int file::iNumberOfPoints()
{
	string sLine;
	getline(fileInput, sLine);
	return stoi(sLine);
}

// calculate Adjazenz Matrix and return Pointer to 2d Array
// iArraySize = iNumberOfPoints
double **file::fMatrix(int iArraySize)
{
	string sPoint[iArraySize], sLine;
	int i = 0, j;
	double **dAdjazenz = 0, dX[iArraySize], dY[iArraySize], dDistance;

	dAdjazenz = new double *[iArraySize];

	// save X and Y Value of each Point in Array
	while (getline(fileInput, sLine))
	{
		dX[i] = stof(sLine.substr(0, 3));
		dY[i] = stof(sLine.substr(4, 6));
		i++;
	}

	// Calculate distance between 2 points and save in matrix -> matrix[point1][point2]=distance
	for (i = 0; i < iArraySize; i++)
	{
		dAdjazenz[i] = new double[iArraySize];

		for (j = 0; j < iArraySize; j++)
		{
			dDistance = sqrt(pow((dX[i] - dX[j]), 2) + pow((dY[i] - dY[j]), 2));
			dAdjazenz[i][j] = dDistance;
		}
	}

	return dAdjazenz;
}

// Close File
file::~file()
{
	fileInput.close();
}