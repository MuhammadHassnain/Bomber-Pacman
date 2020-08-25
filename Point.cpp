/*
 * Point.cpp
 *
 *  Created on: May 17, 2017
 *      Author: muhammadhassnain
 */

#include "Point.h"
#include<stdlib.h>
#include<math.h>
#include<iostream>

Point::Point(int a,int b) {
	x=a;
	y=b;
}
int Point::getX(){
	return x;
}
int Point::getY(){
	return y;
}
void Point::setPoint(int a,int b){
	x=a;
	y=b;
}
float Point::distance(Point temp){
	this->x=(float)(x);
	this->y=(float)(y);
	temp.x=(float)(temp.x);
	temp.y=(float)(temp.y);
	float xx=fabs(pow((x-temp.x),2.0));
	float yy=fabs(pow((y-temp.y),2.0));
	return fabs(pow((xx+yy),0.5));
}
bool Point::operator ==(Point p1){
	if(p1.getX()==this->x && p1.getY()== this->y){
		return true;
	}
	return false;
}
