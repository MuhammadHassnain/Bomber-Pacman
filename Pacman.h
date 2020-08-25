/*
 * Pacman.h
 *
 *  Created on: May 17, 2017
 *      Author: muhammadhassnain
 */

#ifndef PACMAN_H_
#define PACMAN_H_

class Pacman {
	int position_x;
	int position_y;
	int lives;
public:
	Pacman(int=1,int=1);
	void setPacmanPosition(int,int);
	void getPacmanPosition(int&,int&);
	int getPacmanX();
	int getPacmanY();
	int getLives();
	void setLives(int);
	~Pacman();
};

#endif /* PACMAN_H_ */
