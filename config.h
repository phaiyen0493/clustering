/*Name: Alexis Phu
*/
#include <string>
#include <vector>
#include "point.h"

using namespace std;

class config
{
	private:
		string pointsFile; //name of the points file
		int kMin, kMax, kNum, numPoints;
		vector<int> centroidIDs; //stores centroid ID's to use in search
		
	public:
		//Modifiers
		void setPointsFile(string file) {pointsFile = file;}
		void setKMin(int num) {kMin = num;}
		void setKMax(int num) {kMax = num;}
		void setKNum(int num) {kNum = num;}
		void setNumPoints(int num) {numPoints = num;}
		void setCentroidIDs(int c) {centroidIDs.push_back(c);}

		//Accessors
		string getPointsFile() {return pointsFile;}
		int getKMin() {return kMin;}
		int getKMax() {return kMax;}
		int getKNum() {return kNum;}
		int getNumPoints() {return numPoints;}
		//int getCentroid(int i) {return centroids.at(i);

		//Methods
		void readConfig(string file); //reads in config class info
		void readPoints(vector<Point> &points, vector<Point> &centroids, vector<vector<Point>> &centroidList); //reads from points file and populates passed in vectors, points and centroids

		//FOR TESTING ONLY
		void outputData();
};
