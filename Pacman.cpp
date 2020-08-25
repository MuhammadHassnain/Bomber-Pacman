/*
 * Pacman.cpp
 *
 *  Created on: May 17, 2017
 *      Author: muhammadhassnain
 */

#include "Pacman.h"

Pacman::Pacman(int a,int b):lives(3) {
	position_x=a;
	position_y=b;
}
void Pacman::getPacmanPosition(int& a,int &b){
	a=position_x;
	b=position_y;
}
void Pacman::setPacmanPosition(int a,int b){
	position_x=a;
	position_y=b;
}
int Pacman::getPacmanX(){
	return position_x;
}
int Pacman::getPacmanY(){
	return position_y;
}
void Pacman::setLives(int l){
	lives=l;
}
int Pacman::getLives(){
	return lives;
}
Pacman::~Pacman(){

}

