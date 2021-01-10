/*Name: Yen Pham
*/
#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include "point.h"

using namespace std;

class KMedoid
{
	private:
	int numOfClusters; // i.e. K
	vector<Point> vctAllPoints; // store all points
	
	vector< vector<Point> > vctClusters; // store the actual clusters, each cluster is a vector of Points
	vector<Point> vctCMedoids; // store the indices of points nearest to each cluster centroid
	float dunnIndex;

	public: 
	//KMedoid (int k, vector <Point> vctPoints, vector <Point> vctCentroids);
	KMedoid();
	void set_numOfClusters(int num);
	int get_numOfClusters();
	void set_vctAllPoints(vector <Point> vector_points); 
	vector <Point> get_vctAllPoints();
	void set_vctCCentroids(vector <Point> vector_centroids);
	vector <Point> get_vctCentroids();
	void set_vctCMedoids(vector <Point> vector_medoid);
	vector <Point> get_vctCMedoids();
	void set_vctClusters(vector <vector <Point> > vector_clusters);
	vector <vector <Point> > get_vctClusters();
	void set_dunnIndex(float dunn_index);
	float get_dunnIndex(); 

	void kMedoid_Clustering();
	void printOutput();
};
    