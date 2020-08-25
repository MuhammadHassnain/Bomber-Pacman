/*
 * Point.h
 *
 *  Created on: May 17, 2017
 *      Author: muhammadhassnain
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
	int x;
	int y;
public:
	Point(int=-1,int=-1);
	int getX();
	int getY();
	float distance(Point);
	void setPoint(int,int);
	bool operator==(Point);
};

#endif /* POINT_H_ */
