/*
 * Blinky.h
 *
 *  Created on: May 17, 2017
 *      Author: muhammadhassnain
 */

#ifndef BLINKY_H_
#define BLINKY_H_

#include "Enemy.h"

class Blinky: public Enemy {
protected:
	int position_x;
	int position_y;
	int pacX,pacY;
	Point target;
	int enemyNumber;
public:
	Blinky(int [14][17],int=-1,int=-1);
	int getEnemyNumber();
	void setEnemyPosition(int=0,int=0);
	void getEnemyPosition(int&,int&);
	void setTargetPostion(int,int);
	void BFS();
	void move();
	virtual ~Blinky(){}

};

#endif /* BLINKY_H_ */
