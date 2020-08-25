/*
 * Enemy.h
 *
 *  Created on: May 17, 2017
 *      Author: muhammadhassnain
 */

#ifndef ENEMY_H_
#define ENEMY_H_
#include<string>
#include "Point.h"
#include<deque>
#include<iterator>
#include<algorithm>
using namespace std;
class Enemy {
protected:
	string behaviour;
	int direction;
	int array[14][17];
	int copy_array[14][17];
public:
	Enemy(int arr[][17],string="chase");
	void setBehaviour(string);
	string getBehaviour();
	void initializeArray(int[][17]);
	void initializeCopyArray();
	virtual void setEnemyPosition(int=0,int=0)=0;
	virtual void getEnemyPosition(int&,int&)=0;
	virtual void BFS()=0;
	virtual void move()=0;
	virtual void setTargetPostion(int,int)=0;
	virtual ~Enemy(){}
	virtual int getEnemyNumber()=0;

};

#endif /* ENEMY_H_ */
