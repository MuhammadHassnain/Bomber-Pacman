/*
 * Enemy.cpp
 *
 *  Created on: May 17, 2017
 *      Author: muhammadhassnain
 */

#include "Enemy.h"
#include<iostream>
using namespace std;
Enemy::Enemy(int arr[][17],string beh) {
	behaviour=beh;
	direction=-10;
}
void Enemy::setBehaviour(string beh){
	behaviour=beh;
}
string Enemy::getBehaviour(){
	return behaviour;
}
void Enemy::initializeCopyArray(){
	for(int i=0;i<14;++i){
		for (int j = 0; j < 17; ++j) {
			copy_array[i][j]=array[i][j];
		}
	}
}
void Enemy::initializeArray(int arr[][17]){
	for (int i = 0; i < 14; ++i) {
		for (int j = 0; j < 17; ++j) {
			array[i][j]=arr[i][j];
		}
	}
}


