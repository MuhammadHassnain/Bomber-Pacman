/*
 * Clyde.h
 *
 *  Created on: May 20, 2017
 *      Author: muhammadhassnain
 */

#ifndef CLYDE_H_
#define CLYDE_H_

#include "Enemy.h"

class Clyde: public Enemy {
protected:
	int position_x;
	int position_y;
	int pacX,pacY;
	Point target;
	int enemyNumber;
public:
	Clyde(int [14][17],int=-1,int=-1);
	int getEnemyNumber();
	void setEnemyPosition(int=0,int=0);
	void getEnemyPosition(int&,int&);
	void setTargetPostion(int,int);
	void BFS();
	void move();
	virtual ~Clyde(){}
};

#endif /* CLYDE_H_ */
