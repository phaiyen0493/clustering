/*Name: Alexis Phu
*/
#include "point.h"
#include "config.h"
#include <fstream>
#include <cctype>
#include <stdlib.h>
#include <iostream>

void config::readConfig(string file)
{
	//temp vars
	string temp;
	string pFile;
	int kmin, kmax, c, it;
	string ignore; //ignored values

	//open file
	ifstream readIn;
	readIn.open(file);

	//error message and quit if file can't open
	if (readIn.fail())
	{
		cout << "Could not open file." << endl;
		exit(0);
	}

	//Read in points file
	getline(readIn, temp);
	pFile = temp.substr(6);
	setPointsFile(pFile);

	//read in kmin and kmax
	getline(readIn, temp, ':');
	readIn >> kmin;
	setKMin(kmin);

	getline(readIn, temp, ':');
	readIn >> kmax;
	setKMax(kmax);

	//number of k = kmax-kmin+1
	setKNum(kmax-kmin+1);

	//Read in the centroid id's
	for (int it = kmin; it <= kmax; it++)
	{
		readIn >> ignore; //ignore the k value

		//will read in as many id's as the currrent k-value
		for (int i = 0; i < it; i++)
		{
			readIn >> c;
			setCentroidIDs(c);
		}
		
	}

	//close file
	readIn.close();
	return;
}

void config::readPoints(vector<Point> &points, vector<Point> &centroids, vector<vector<Point>> &centroidList)
{
	//temp vars
	int id;
	int count = 0;
	float x, y;
	Point tempPoint;
	bool isRepeat = false;

	//open the points file
	ifstream readIn;
	readIn.open(pointsFile);

	//error message and exit if file can't open
	if (readIn.fail())
	{
		cout << "Could not open the file." << endl;
		exit(0);
	}
	//for whole file
	while (readIn >> id)
	{
		//read id, x, and y
		tempPoint.setID(id);

		readIn >> x;
		tempPoint.setX(x);

		readIn >> y;
		tempPoint.setY(y);
		
		//Point tempPoint(x, y, id);

		//add new point to points vector
		points.push_back(tempPoint);

		count++;
	}

	//close file
	readIn.close();

	//set count
	setNumPoints(count);

	//find and assign centroids
	for (int i = 0; i < centroidIDs.size(); i++)
	{
		for (int j = 0; j < points.size(); j++)
		{
			isRepeat = false;
			//look for the id of the centroid point
			if (points.at(j).getID() == centroidIDs.at(i))
			{
				x = points.at(j).getX();
				y = points.at(j).getY();
				id = points.at(j).getID();

				tempPoint.setX(x);
				tempPoint.setY(y);
				tempPoint.setID(id);

				//Check for repeats
				if (centroids.size() > 0)
				{
					for (int k = 0; k < centroids.size(); k++)
					{
						if (centroids.at(k).getID() == tempPoint.getID())
						{
							isRepeat = true;
						}
					}
				}
				if (!isRepeat)
				{
					//add point to centroid vector
					centroids.push_back(tempPoint);
				}
			}
		}
	}

	//Store centroid list as 2D vector
	vector<vector<Point>> out;
	for (int i = kMin; i <= kMax; i++)
	{
		vector<Point> in; 
		for (int j = 0; j < i; j++)
		{
			in.push_back(centroids.at(j));
		}

		out.push_back(in);
	}

	centroidList = out;

	return;
}

void config::outputData() //USED ONLY FOR TESTING
{
	cout << "Points file: " << getPointsFile() << endl;
	cout << "K-Min: " << getKMin() << endl;
	cout << "K-Max: " << getKMax() << endl;
	cout << "Centroids IDs: ";
	for (int i = 0; i < centroidIDs.size(); i++)
	{
		cout << centroidIDs.at(i) << "  ";
	}
	cout << endl;
	return;
}
