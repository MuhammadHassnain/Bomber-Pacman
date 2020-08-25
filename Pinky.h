/*
 * Pinky.h
 *
 *  Created on: May 19, 2017
 *      Author: muhammadhassnain
 */

#ifndef PINKY_H_
#define PINKY_H_

#include "Enemy.h"
#include<iostream>
using namespace std;
class Pinky: public Enemy {
	int position_x;
	int position_y;
	int targetX,targetY;
	int enemyNumber;
	Point target;
public:
	Pinky(int [][17],int=-1,int=-1);
	void setEnemyPosition(int=0,int=0);
	void getEnemyPosition(int&,int&);
	void setTargetPostion(int,int);
	void BFS();
	void move();
	int getEnemyNumber();
	virtual ~Pinky(){}
};

#endif /* PINKY_H_ */
