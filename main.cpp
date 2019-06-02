#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <ctime>

using namespace std;

#include "file.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Error wrong usage: " << argv[0] << " <option> <filename>" << endl;
	}
	else
	{
		file file(argv[2]);
		int iNumberOfPoints, i, j;

		iNumberOfPoints = file.iNumberOfPoints();
		//cout << "Number of Points: " << iNumberOfPoints << endl;
		//cout << "------------------" << endl;

		double **dAdjazenz = file.fMatrix(iNumberOfPoints);

		/*
		for (i = 0; i < iNumberOfPoints; i++)
		{
			for (j = 0; j < iNumberOfPoints; j++)
			{
				cout << i << " to " << j << ": ";
				cout << dAdjazenz[i][j] << endl;
			}
		}
		cout << "-------------------------------" << endl;
		*/

		// Enumeration
		if (string(argv[1]) == "-e")
		{
			cout << "Enumeration" << endl;
		}
		// Nearest Neighbour Heuristic
		else if (string(argv[1]) == "-n")
		{
			cout << "Nearest Neighbour Heuristic" << endl;

			int x, h, iCurrentPoint, iStartPoint, iVisitedPoints[iNumberOfPoints], iVisited, iShortestPointSequenceLengthIndex;
			double dLength[iNumberOfPoints], dShortest, dTemp, dTotalLength[iNumberOfPoints];
			string sPointSequence[iNumberOfPoints];
			bool bPointExists = false;
			clock_t start = clock();

			// Initialize Arrays
			for (i = 0; i < iNumberOfPoints; i++)
			{
				iVisitedPoints[i] = iNumberOfPoints;
				dTotalLength[i] = 0;
				sPointSequence[i] = "";
			}

			// set the distance from one point to himself to 999999 (infinte) to prevent endless loop
			for (i = 0; i < iNumberOfPoints; i++)
			{
				for (j = 0; j < iNumberOfPoints; j++)
				{
					if (dAdjazenz[i][j] == 0)
					{
						dAdjazenz[i][j] = 999999;
					}
				}
			}

			// algorithm to choose the shortest tour
			// go trough all starting point always choose shortest distance between points and finally go back to starting point
			for (h = 0; h < iNumberOfPoints; h++)
			{
				// reset the visited points
				for (i = 0; i < iNumberOfPoints; i++)
				{
					iVisitedPoints[i] = iNumberOfPoints;
				}

				iCurrentPoint = h;
				iVisitedPoints[0] = h;
				sPointSequence[h] = to_string(iCurrentPoint);

				for (x = 0; x < iNumberOfPoints; x++)
				{
					dShortest = 999999;
					iStartPoint = iCurrentPoint;

					for (i = 0; i < iNumberOfPoints; i++)
					{
						// check if the point was allready visited
						for (j = 0; j < iNumberOfPoints; j++)
						{
							if (iVisitedPoints[j] == i)
							{
								bPointExists = true;
							}
						}

						// if point wasn't allready visited get the point with the shortest distance
						if (!bPointExists)
						{
							if (dShortest > dAdjazenz[iStartPoint][i])
							{
								dShortest = dAdjazenz[iStartPoint][i];
								iCurrentPoint = i;
							}
						}
						// reset
						bPointExists = false;
					}

					// save visited point in array
					iVisited = x + 1;
					iVisitedPoints[iVisited] = iCurrentPoint;

					// in the second last iteration make the inital starting point available
					if (x == iNumberOfPoints - 2)
					{
						iVisitedPoints[0] = iNumberOfPoints;
					}

					//cout << "From Point " << iStartPoint << " to Point " << iCurrentPoint << " is shortest: " << setprecision(50) << dShortest << endl;
					dTotalLength[h] += dShortest;
					sPointSequence[h] += to_string(iCurrentPoint);
				}

				//cout << "Total Length: " << setprecision(50) << dTotalLength[h] << endl;
				//cout << "Sequence: " << sPointSequence[h] << endl;
				//cout << "--------------------------" << endl;
			}

			// get the shortest total lenght of all the lengths
			dShortest = 999999;
			for (i = 0; i < iNumberOfPoints; i++)
			{
				if (dShortest > dTotalLength[i])
				{
					dShortest = dTotalLength[i];
					iShortestPointSequenceLengthIndex = i;
				}
			}

			cout << "Shortest Length: " << dTotalLength[iShortestPointSequenceLengthIndex] << endl;
			cout << "Sequence: " << sPointSequence[iShortestPointSequenceLengthIndex] << endl;
			cout << "Time elapsed: " << (clock() - start) * 1000000 / (double)CLOCKS_PER_SEC << "ns" << endl;
		}
		else
		{
			cout << "Error wrong parameter use -e or -n" << endl;
		}
	}

	return 0;
}