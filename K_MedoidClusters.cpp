/*Name: Yen Pham
*/
#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include "K_MedoidClusters.h"

using namespace std;

KMedoid:: KMedoid()
{}

void KMedoid:: set_numOfClusters(int num)
{
	numOfClusters = num;
}

int KMedoid:: get_numOfClusters()
{
	return numOfClusters;
}

void KMedoid:: set_vctAllPoints(vector <Point> vector_points)
{
	vctAllPoints.clear();
	vctAllPoints = vector_points;
}

vector <Point> KMedoid:: get_vctAllPoints()
{
	return vctAllPoints;
}


void KMedoid:: set_vctCMedoids(vector <Point> vector_medoids)
{
	vctCMedoids.clear();
	vctCMedoids = vector_medoids;
}

vector <Point> KMedoid:: get_vctCMedoids()
{
	return vctCMedoids;
}

void KMedoid:: set_vctClusters(vector <vector <Point> > vector_clusters)
{
	vctClusters.clear();
	vctClusters = vector_clusters;
}

vector <vector <Point> > KMedoid:: get_vctClusters()
{
	return vctClusters;
}

void KMedoid:: set_dunnIndex(float dunn_index)
{
	dunnIndex = dunn_index;
}

float KMedoid:: get_dunnIndex()
{
	return dunnIndex;
}

void KMedoid:: kMedoid_Clustering()
{
        int numOfPoints = vctAllPoints.size();
        int membership[numOfPoints];
        int prevMembership[numOfPoints];
        float pToCDistance;
        float minPToCDistance; // min distance from member point to centroid


        for (int i = 0; i < numOfPoints; i++)
        // fill initial membership, = respective point's id
        // prev membership = 0
        // note: remember that Point IDs start from 1, array's indices start from 0
        // 
        {
		membership[i] = i;
		prevMembership[i] = -1;
        }

        bool finished = false;
        while (!finished)
        {
		// compute distances and manage membership
		float curDistance;
		float minDistance;
		for( int i = 0; i < numOfPoints; i++ )
		{
			minDistance = numeric_limits<float>::infinity(); // reset minDistance to INFINITY for each point
			for ( int j = 0; j < vctCMedoids.size(); j++ )
			{
				// Euclidian distance
				curDistance = sqrt( pow( (vctAllPoints[i].getX() - vctCMedoids[j].getX() ), 2 ) + pow ( (vctAllPoints[i].getY() - vctCMedoids[j].getY() ), 2 ) );
				if (curDistance < minDistance)
				// in case curDistance == minDistance, no change, since priority is given to the cluster with smaller index
				{
					minDistance = curDistance;
					// set membership
					membership[i] = j; // Note: j is index, which starts from 0. As per requirement, we may want to give clusters IDs starting from 1, but don't do that here
				}
			}
                
		} // end for-loop for membership


		// checking if membership changed, membership unchanged == finished
		finished = true; // temporarily set this flag to true only to check
		for (int i = 0; i < numOfPoints; i++)
		// loop to check current and previous membership
		{
			if ( membership[i] != prevMembership[i] )
			{
				finished = false; // membership changed
				prevMembership[i] = membership[i]; // update membership
			}
		} // end for-loop for finished check


		if (!finished)
		// not finished, need to update cluster centroids
		// if finished, no need to update, since they should be the same as previous round
		{
			float centroidsXY[numOfClusters][2]; // store the new X, Y coords for the new centroids temporarily
			int numOfMembers = 0; // counter for number of members for each cluster
             
			vector<Point> vctCCentroids;
                
			for( int i = 0; i < numOfClusters; i++ ) // for each cluster
			{
				numOfMembers = 0; // reset number of members
				centroidsXY[i][0] = 0; // initiate X, Y to 0
				centroidsXY[i][1] = 0;
				for( int j = 0; j < numOfPoints; j++ ) // for each point
				{
					if ( membership[j] == i)
					//membership == index of current cluster
					{
						centroidsXY[i][0] += vctAllPoints[j].getX();
						centroidsXY[i][1] += vctAllPoints[j].getY();
						numOfMembers++;
					}
				}
				centroidsXY[i][0] = centroidsXY[i][0]/ (float) (numOfMembers); // X
				centroidsXY[i][1] = centroidsXY[i][1]/ (float) (numOfMembers); // Y

				Point tempCentroid; // create temporary point
				tempCentroid.setID(-1);
				tempCentroid.setX(centroidsXY[i][0]);
				tempCentroid.setY(centroidsXY[i][1]);

				vctCCentroids.push_back(tempCentroid); // push new centroid to vector  

			} // end for-loop for each cluster
			
			vctCMedoids.clear(); // clear medoids vector
			for ( int i = 0; i < numOfClusters; i++)  // for each cluster, again
			{
				Point tempMedoid;
				minPToCDistance = numeric_limits<float>::infinity();

				for( int j = 0; j < numOfPoints; j++ ) // for each point
				{
					if ( membership[j] == i)
					//membership == index of current cluster
					{
						pToCDistance = sqrt(pow( (vctAllPoints[j].getX() - vctCCentroids[i].getX() ), 2 ) + 
								pow ( (vctAllPoints[j].getY() - vctCCentroids[i].getY() ), 2 ) );
						if ( pToCDistance < minPToCDistance )
						{
							minPToCDistance = pToCDistance;
							tempMedoid.setID(vctAllPoints[j].getID());
							tempMedoid.setX(vctAllPoints[j].getX());
							tempMedoid.setY(vctAllPoints[j].getY());
						}
					}
				}// end for-loop for each member point
				vctCMedoids.push_back(tempMedoid);
			} // end for each cluster

		} // end if for updating cluster centroids

		else // finished, update the actual clusters with Points
		{
			vctClusters.clear();
			vector<Point> tempCluster;

			// not the best way to do this, but well, probably the simplest way
			for( int i = 0; i < numOfClusters; i++ ) // for each cluster
			{
				tempCluster.clear();
				for( int j = 0; j < numOfPoints; j++ ) // for each point
				{
					if ( membership[j] == i) //membership == index of current cluster
					{
						tempCluster.push_back(vctAllPoints[j]);
					}
				}
 				vctClusters.push_back(tempCluster);
			} // end for-loop for each cluster
		} // end if-else for updating clusters   
	} // end while-loop

	//Calculate Dunn index
	
	// for the Dunn Index
        // first, compute min inter-cluster distance (1 value for all clusters in this set)
        float minInterClusterDistance = numeric_limits<float>::infinity();
        float interClusterDistance = 0;

        for( int i = 0; i < numOfClusters; i++ ) {
        // for each cluster
		if (vctClusters[i].size() > 1) {
			for ( int j = i + 1; j < numOfClusters; j++ ) {
			// for each remaining cluster 
				if(vctClusters[j].size() > 1) {
					for(int k = 0; k < vctClusters[i].size(); k++) {
					// for each point in cluster i
						for (int l = 0; l < vctClusters[j].size(); l++) {
						// for each point in cluster j
							interClusterDistance = sqrt( pow( (vctClusters[i][k].getX() - vctClusters[j][l].getX() ), 2 ) 
										+ pow ((vctClusters[i][k].getY() - vctClusters[j][l].getY() ), 2 ) );
							if (interClusterDistance < minInterClusterDistance) {
								minInterClusterDistance = interClusterDistance;
							}
						}
					}
				}
			}
		}
	} // end for-loop for each cluster
	

	// then, compute max intra cluster distance, or max cluster diameter (also 1 value for the entire set)
	// also find the ID of the point closest to each centroid

        float intraDistance;
        float maxIntraDistance = 0;

        for ( int i = 0; i < numOfClusters; i++ ) // for each cluster
        {
		// reset the variables
		minPToCDistance = numeric_limits<float>::infinity();

		int numOfMembers = vctClusters[i].size();
		for ( int j = 0; j < numOfMembers ; j++ ) // for each member point
		{
			for ( int k = j + 1; k < numOfMembers; k++ ) // for each remaining member point
			{
				intraDistance = sqrt(pow( (vctClusters[i][j].getX() - vctClusters[i][k].getX() ), 2 ) + pow ( (vctClusters[i][j].getY() - vctClusters[i][k].getY() ), 2 ) );
				if ( intraDistance > maxIntraDistance )
				{
					maxIntraDistance = intraDistance;
				}
			} // end for-loop for each remaining member point
		}
	} // end for-loop for each cluster
	
	dunnIndex = minInterClusterDistance / maxIntraDistance;

        return;
} // end method kMedoid

void KMedoid:: printOutput()
{
	cout << "For a K value of " << numOfClusters << ", here is the information regarding its clustering: " << endl;
        for ( int i = 0; i< numOfClusters; i++ )
        {
            cout << "Cluster " << (i+1) << " contains " << vctClusters[i].size() << " points, and the point " << vctCMedoids[i].getID() << " is its medoid." << endl;
        }   
	cout << "The Dunn Index for a K value of " << numOfClusters << " is: " << dunnIndex << endl << endl;
} // end method printOutput()

