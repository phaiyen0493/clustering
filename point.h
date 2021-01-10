/*Name: Alexis Phu
*/

#ifndef POINT_H_
#define POINT_H_

class Point{

	public:
		//Point();
		//Point(float x, float y, int ID);

		float getX(){ return x;}
		void setX(float x){ this->x = x;}

		float getY(){ return y;}
		void setY(float y){ this->y = y;}

		int getID(){ return ID;}
		void setID(int ID){ this->ID = ID;}
		

	private: 
		float x;
		float y;
		int ID;
		




};

#endif

