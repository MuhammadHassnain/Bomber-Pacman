/*
 * Bomb.h
 *
 *  Created on: May 19, 2017
 *      Author: muhammadhassnain
 */

#ifndef BOMB_H_
#define BOMB_H_

class Bomb {
	bool status;
	int position_x;
	int position_y;
	int radius;
	int bombtime;
public:
	Bomb(int=0,int=0);
	void getBombPosition(int&,int&);
	void setBombPosition(int,int);
	void setBombRadius(int);
	int getBombRadius();
	bool getBombStatus();
	void setBombStatus(bool);
	void setBombTime(int=2);
	int getBombTime();
	~Bomb();
};

#endif /* BOMB_H_ */
