/*
Group: 31
Project 2

Name:
Alexis Phu
Thong Nguyen
Yen Pham
Rylan Abraham
*/

#include <iostream>
#include <string>
#include <vector>
#include "point.h"
#include "config.h"
#include "KMCluster.h"
#include "HierarchicalClusters.h"
#include "K_MedoidClusters.h"

using namespace std;

int main(){

	float k_mean_highest_dunn = 0;
	int k_mean_highest_k = 0;
	float hierarchical_highest_dunn = 0;
	int hierarchical_highest_clusters_count = 0;
	float k_medoid_highest_dunn = 0;
	int k_medoid_highest_k = 0;

	vector<Point> Points;
	vector<Point> centroids;
	vector<vector<Point>> centroidList;

	config setUp;
	KMCluster Kcluster;
	HierarchicalClusters Hcluster;
	KMedoid medoid_cluster;
	string file;

	//Prompt user to enter config file
	cout << "Please enter the name of the configuration file: ";
	cin >> file;

	setUp.readConfig(file); //call function to read file config
	setUp.readPoints(Points, centroids, centroidList); //call function to read file Points

	cout << "The total number of k values to be tested is: ";
	cout << setUp.getKNum() << endl;

	cout << "The total number of points in this file is: ";
	cout << setUp.getNumPoints() << endl;
	
	//set vector of Points for each function
	Kcluster.set_vctAllPoints(Points);	
	Hcluster.set_vctAllPoints(Points);
	medoid_cluster.set_vctAllPoints(Points);

	cout << "\nFor K-Means Clustering: " << endl;
	for (int i = 0; i < centroidList.size(); i++)
	{
		//K-mean clustering function call
		Kcluster.set_numOfClusters(centroidList[i].size());
		Kcluster.set_vctCCentroids(centroidList[i]);
		Kcluster.kMClustering();
		Kcluster.printOutput();

		if (k_mean_highest_dunn < Kcluster.get_dunnIndex())
		{
			k_mean_highest_dunn = Kcluster.get_dunnIndex();
			k_mean_highest_k = i + setUp.getKMin();
		}
	}

	cout << "\nFor Centroid-Linkage Clustering:" << endl;
	Hcluster.hierarchicalClustering(); //Hierarchical clustering function call

	cout << "\nFor K-Medoids Clustering: " << endl;
	for (int i = 0; i < centroidList.size(); i++)
	{
		//Medoid clustering function call (extra credit)
		medoid_cluster.set_numOfClusters(centroidList[i].size());
		medoid_cluster.set_vctCMedoids(centroidList[i]);
		medoid_cluster.kMedoid_Clustering();
		medoid_cluster.printOutput();

		if (k_medoid_highest_dunn < medoid_cluster.get_dunnIndex())
		{
			k_medoid_highest_dunn = medoid_cluster.get_dunnIndex();
			k_medoid_highest_k = i + setUp.getKMin();
		}
	}
	cout << endl;

	//Report
	cout << "The final analysis shows that: " << endl;
	cout << "For k-means, a k value of " << k_mean_highest_k << " had the highest Dunn index of " << k_mean_highest_dunn << endl;
	Hcluster.getHighestDunn(); 
	cout << "For k-medoid, a k value of " << k_medoid_highest_k << " had the highest Dunn index of " << k_medoid_highest_dunn << endl;
	
	cout << "Complete!" << endl;
	
	return 0;
}
