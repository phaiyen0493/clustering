/*Name: Thong Nguyen
*/
#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include "point.h"

using namespace std;

class KMCluster
{
	private:
	int numOfClusters; // i.e. K
	vector<Point> vctAllPoints; // store all points
	vector<Point> vctCCentroids; // store the cluster centroids, each centroid is still a point, its ID can be put as -1
	vector< vector<Point> > vctClusters; // store the actual clusters, each cluster is a vector of Points
	vector<int> vctNearestPointIDs; // store the indices of points nearest to each cluster centroid
	float dunnIndex;

	public: 
	//KMCluster (int k, vector <Point> vctPoints, vector <Point> vctCentroids);
	KMCluster();
	void set_numOfClusters(int num);
	int get_numOfClusters();
	void set_vctAllPoints(vector <Point> vector_points); 
	vector <Point> get_vctAllPoints();
	void set_vctCCentroids(vector <Point> vector_centroids);
	vector <Point> get_vctCentroids();
	void set_vctClusters(vector <vector <Point> > vector_clusters);
	vector <vector <Point> > get_vctClusters();
	void set_vctNearestPointIDs(vector <int> nearest_point_IDs);
	vector <int> get_vctNearestPointIDs();
	void set_dunnIndex(float dunn_index);
	float get_dunnIndex(); 

	void kMClustering();
	void printOutput();
};
    