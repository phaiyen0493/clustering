/*Name: Yen Pham
*/
#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include <utility>
#include "HierarchicalClusters.h"

using namespace std;

HierarchicalClusters:: HierarchicalClusters()
{
	float highestDunn = 0;
	int highest_level = 0;

}

void HierarchicalClusters:: set_vctAllPoints(vector<Point> vector_all_points)
{
	vctAllPoints = vector_all_points;
}

vector <Point> HierarchicalClusters:: get_vctAllPoints()
{
	return vctAllPoints;
}

void HierarchicalClusters:: set_vctDunnIndices(vector< pair<int,float> > vector_dunn_indices)
{
	vctDunnIndices = vector_dunn_indices;
}

vector< pair<int,float> > HierarchicalClusters:: get_vctDunnIndices()
{
	return vctDunnIndices;
}

void HierarchicalClusters:: hierarchicalClustering()
{
	int numOfPoints = vctAllPoints.size();
        int numOfClusters = vctAllPoints.size(); // initially, num of clusters = num of points
        int numOfMulClusters = 0; // counting cluster with more than 1 point
        
        vector<Point> vctCCentroids;
        vector< vector<Point> > vctClusters;

        // initiate variables pre-clustering
        for ( int i = 0; i < numOfPoints; i++ )
        {
            vector<Point> vctTempCluster;
            vctTempCluster.push_back(vctAllPoints[i]);
            vctClusters.push_back(vctTempCluster);
            
            vctCCentroids.push_back(vctAllPoints[i]);
            vctCCentroids[i].setID(-1);
        }

	cout << "Hierarchy level 0 with " << numOfClusters << " clusters inside" << endl;;
        
	for ( int level = 1; level < numOfPoints; level++ ) { 
	// loop (numOfPoints - 1) times, i.e. 100 points will take 99 steps to finish clustering
        
	
	Link minLink;
        float minDistance = numeric_limits<float>::infinity(); // reset minDistance to INFINITY for each round
	
        for ( int j = 0; j < numOfClusters-1; j++ )
        // for each cluster, till n-1
        {
            for ( int k = j+1; k < numOfClusters; k++ )
            // for each remaining cluster, i.e. 2nd to nth 
            {
                Link tempLink;
                tempLink.cluster_Idx1 = j;
                tempLink.cluster_Idx2 = k;
                tempLink.distance = sqrt(pow( (vctCCentroids[j].getX() - vctCCentroids[k].getX() ), 2 ) 
					+ pow ( (vctCCentroids[j].getY() - vctCCentroids[k].getY() ), 2 ) );
                
		if ( tempLink.distance < minDistance ) 
		{
			minDistance = tempLink.distance;
			minLink = tempLink;
		}
            }
        } // end for-loop for computing links, should have found minLink also

            // make change to reflect the new clusters
            // vctClusters // actually clusters
            // vctCCentroids // centroids of clusters
            // note: 
            
            // first, update the actual cluster
            for ( int i = 0; i < vctClusters[ minLink.cluster_Idx2 ].size(); i++ )
            {
                // push each point in cluster 2 to cluster 1
                vctClusters[ minLink.cluster_Idx1 ].push_back( vctClusters[ minLink.cluster_Idx2 ][i] );
            }
            // next, erase cluster 2, i.e. a vector, from the vector of all clusters
            vctClusters.erase(vctClusters.begin() + minLink.cluster_Idx2);
            // also erase the centroid of cluster 2
            vctCCentroids.erase(vctCCentroids.begin() + minLink.cluster_Idx2);

            // second, update the centroids vector
            float tempCCX = 0; 
	    float tempCCY = 0;
            int numOfCMembers = 0;
            for ( int i = 0; i < vctClusters[ minLink.cluster_Idx1 ].size(); i++ )
            {
                tempCCX += vctClusters[ minLink.cluster_Idx1 ][i].getX();
                tempCCY += vctClusters[ minLink.cluster_Idx1 ][i].getY();
                numOfCMembers++;
            }

            tempCCX = tempCCX / (float) (numOfCMembers);
            tempCCY = tempCCY / (float) (numOfCMembers);
            vctCCentroids[ minLink.cluster_Idx1 ].setX(tempCCX);
            vctCCentroids[ minLink.cluster_Idx1 ].setY(tempCCY);


            // finally, update numberOfClusters
            //numOfClusters--; // decrement number of clusters
	    numOfClusters = vctClusters.size();


            // check to see how many clusters are non-single
            numOfMulClusters = 0;
            for ( int i = 0; i < numOfClusters; i++ )
            {
                if(vctClusters[i].size() > 1)
                {
                    numOfMulClusters++;
                }
            }


            // if more than 1 non-single cluster, can compute the Dunn Index
            pair<int,float> dunnIndexPair;
            dunnIndexPair.first = numOfClusters; 
	    dunnIndexPair.second = 0;
            if (numOfMulClusters < 2)
            {
                vctDunnIndices.push_back(dunnIndexPair);
            } // end if
            else // more than 1 non-single cluster
            {

                float minInterClusterDistance = numeric_limits<float>::infinity();
                float interClusterDistance = 0;
                float intraDistance;
                float maxIntraDistance = 0;
                for( int i = 0; i < numOfClusters; i++ )
                // for each cluster
                {
                    numOfCMembers = vctClusters[i].size();
                    if (vctClusters[i].size() > 1)
                    {
                        // compute min inter-cluster distance
                        for ( int j = i + 1; j < numOfClusters; j++ )
                        // for each remaining cluster
                        {
                            if(vctClusters[j].size() > 1)
                            {
                                for(int k = 0; k < vctClusters[i].size(); k++) 
				{
				// for each point in cluster i
					for (int l = 0; l < vctClusters[j].size(); l++) 
					{
					// for each point in cluster j
						interClusterDistance = sqrt( (float) pow( (vctClusters[i][k].getX() - vctClusters[j][l].getX() ), 2 ) 
									+ (float) pow ((vctClusters[i][k].getY() - vctClusters[j][l].getY() ), 2 ) );
						if (interClusterDistance < minInterClusterDistance) {
							minInterClusterDistance = interClusterDistance;
						}
					}
				}

                            } // end if size j > 1
                        }

                        // compute max intra cluster distance, or max cluster diameter 
                        for ( int j = 0; j < (numOfCMembers - 1) ; j++ )
                        {
                            for ( int k = j + 1; k < numOfCMembers; k++ )
                            // for each remaining member point
                            {
                                intraDistance = sqrt(pow( (vctClusters[i][j].getX() - vctClusters[i][k].getX() ), 2 ) + pow ( (vctClusters[i][j].getY() - vctClusters[i][k].getY() ), 2 ) );
                                if ( intraDistance > maxIntraDistance )
                                {
                                    maxIntraDistance = intraDistance;
                                }
                            } // end for-loop for each remaining member point
                        }
                    } // end if size i > 1

                } // end for-loop for each cluster

                // then, compute the Dunn Index for this set of clusters
                
                dunnIndexPair.second = (float) minInterClusterDistance / (float) maxIntraDistance;
                vctDunnIndices.push_back(dunnIndexPair);

            } // end if-else for computing Dunn Index
            
            // print output section
		if ( (level % 10) == 0)
		{
			printOutput( level, dunnIndexPair );
		} 
		else if (dunnIndexPair.first == 1)
		{
			printOutput( level, dunnIndexPair );
		}
        } // end the (n-1) for-loop
	cout << endl;
        return;
// end method hierarchical clustering
}

void HierarchicalClusters::printOutput(int level, pair<int, float> dunnIndexPair )
{
	if (level < (vctAllPoints.size()/2) || (dunnIndexPair.first == 1 && level > (vctAllPoints.size()/2)))
	{
		cout << "Hierarchy level " << level << " with " << dunnIndexPair.first << " clusters inside" << endl;
	}

	if ( dunnIndexPair.first > 1 && level > (vctAllPoints.size()/2) ) 
	{
		if (highestDunn < dunnIndexPair.second)
		{
			highest_level = dunnIndexPair.first;
			highestDunn = dunnIndexPair.second;
		}
		cout << "Hierarchy level " << level << " with " << dunnIndexPair.first << " clusters inside" << " and a Dunn index of " << dunnIndexPair.second << endl;
	}
}

void HierarchicalClusters::getHighestDunn()
{
	cout << "For centroid-linkage clustering, " << highest_level << " clusters had the highest Dunn index of " << highestDunn << endl;
}

