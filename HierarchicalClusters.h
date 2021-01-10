/*Name: Yen Pham
*/
#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include <utility>
#include "point.h"

using namespace std;


struct Link
{
	int cluster_Idx1;
	int cluster_Idx2;
	float distance;

	//Link(int, int, float); // constructor
};

class HierarchicalClusters
{
	private:
	vector<Point> vctAllPoints;
	vector< pair<int,float> > vctDunnIndices;
	
	float highestDunn;
	int highest_level;

	public:
	HierarchicalClusters(); // constructor
	void set_vctAllPoints(vector<Point> vector_all_points);
	vector <Point> get_vctAllPoints();
	void set_vctDunnIndices(vector< pair<int,float> > vector_dunn_indices);
	vector< pair<int,float> > get_vctDunnIndices();
	void getHighestDunn(); //get highest Dunn index
		
	void hierarchicalClustering();
	void printOutput(int level, pair<int,float> dunnIndexPair );
};