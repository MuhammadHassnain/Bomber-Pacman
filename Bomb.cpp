/*
 * Bomb.cpp
 *
 *  Created on: May 19, 2017
 *      Author: muhammadhassnain
 */

#include "Bomb.h"

Bomb::Bomb(int x,int y):radius(1),status(false),bombtime(2) {
	position_x=x;
	position_y=y;
}
void Bomb::setBombPosition(int x,int y){
	position_x=x;
	position_y=y;
}
void Bomb::getBombPosition(int& x,int& y){
	x=position_x;
	y=position_y;
}
int Bomb::getBombRadius(){
	return radius;
}
void Bomb::setBombRadius(int r){
	radius=r;
}
bool Bomb::getBombStatus(){
	return status;
}
void Bomb::setBombStatus(bool s){
	status=s;
}
int Bomb::getBombTime(){
	return bombtime;
}
void Bomb::setBombTime(int t){
	bombtime=t;
}
Bomb::~Bomb(){}

