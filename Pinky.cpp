/*
 * Pinky.cpp
 *
 *  Created on: May 19, 2017
 *      Author: muhammadhassnain
 */

#include "Pinky.h"

enum Direction{
	UP,DOWN,LEFT,RIGHT
};
Pinky::Pinky(int arr[14][17],int a,int b):Enemy(arr,"chase") {
	position_x=a;
	position_y=b;
	enemyNumber=1;
}
void Pinky::setEnemyPosition(int a,int b){
	position_x=a;
	position_y=b;
}
void Pinky::getEnemyPosition(int& a,int& b){
	a=position_x;
	b=position_y;
}
void Pinky::setTargetPostion(int a,int b){
	targetX=a;
	targetY=b;
}
void Pinky::BFS(){
	initializeCopyArray();
	deque<Point> d;
	float minDistance=9999.9;
	Point PacmanPosition(targetX,targetY);
	if(behaviour=="scatter"){
			PacmanPosition.setPoint(15,11);
		}
	Point EnemyPosition(position_x,position_y);
	Point minDistancePoint(targetX,targetY);
	if(copy_array[12-(EnemyPosition.getY()+1)][EnemyPosition.getX()]==4){
		Point enemyUpPos(EnemyPosition.getX(),EnemyPosition.getY()+1);
		copy_array[12-(EnemyPosition.getY()+1)][EnemyPosition.getX()]=Direction(UP);
		d.push_back(enemyUpPos);
	}
	if(copy_array[12-(EnemyPosition.getY()-1)][EnemyPosition.getX()]==4){
		Point enemyUpPos(EnemyPosition.getX(),EnemyPosition.getY()-1);
		copy_array[12-(EnemyPosition.getY()-1)][EnemyPosition.getX()]=Direction(DOWN);
		d.push_back(enemyUpPos);
	}
	if(copy_array[12-(EnemyPosition.getY())][EnemyPosition.getX()-1]==4){
		Point enemyUpPos(EnemyPosition.getX()-1,EnemyPosition.getY());
		copy_array[12-(EnemyPosition.getY())][(EnemyPosition.getX()-1)]=Direction(LEFT);
		d.push_back(enemyUpPos);
	}
	if(copy_array[12-(EnemyPosition.getY())][EnemyPosition.getX()+1]==4){
		Point enemyUpPos(EnemyPosition.getX()+1,EnemyPosition.getY());
		copy_array[12-(EnemyPosition.getY()+0)][EnemyPosition.getX()+1]=Direction(RIGHT);
		d.push_back(enemyUpPos);
	}
	while(!d.empty()){
		Point temp=d[0];
		if(copy_array[12-(temp.getY()+1)][temp.getX()]==4){
			Point enemyNextPos(temp.getX(),temp.getY()+1);
			copy_array[12-(temp.getY()+1)][temp.getX()]=copy_array[12-(temp.getY())][temp.getX()];
			d.push_back(enemyNextPos);
			if(minDistance>temp.distance(PacmanPosition)){
				minDistance=temp.distance(PacmanPosition);
				minDistancePoint=temp;
//				cout<<12-minDistancePoint.getY()<<"  "<<minDistancePoint.getX()<<endl;
			}
		}

		if(copy_array[12-(temp.getY()-1)][temp.getX()]==4){
			Point enemyNextPos(temp.getX(),temp.getY()-1);
			copy_array[12-(temp.getY()-1)][temp.getX()]=copy_array[12-(temp.getY())][temp.getX()];
			d.push_back(enemyNextPos);
			if(minDistance>temp.distance(PacmanPosition)){
				minDistance=temp.distance(PacmanPosition);
				minDistancePoint=temp;
//				cout<<12-minDistancePoint.getY()<<"  "<<minDistancePoint.getX()<<endl;
			}
		}
		if(copy_array[12-(temp.getY())][temp.getX()+1]==4){
			Point enemyNextPos(temp.getX()+1,temp.getY());
			copy_array[12-(temp.getY())][temp.getX()+1]=copy_array[12-(temp.getY())][temp.getX()];
			d.push_back(enemyNextPos);
			if(minDistance>temp.distance(PacmanPosition)){
				minDistance=temp.distance(PacmanPosition);
				minDistancePoint=temp;
//				cout<<12-minDistancePoint.getY()<<"  "<<minDistancePoint.getX()<<endl;
			}
		}
		if(copy_array[12-(temp.getY())][temp.getX()-1]==4){
			Point enemyNextPos(temp.getX()-1,temp.getY());
			copy_array[12-(temp.getY())][temp.getX()-1]=copy_array[12-(temp.getY())][temp.getX()];
			d.push_back(enemyNextPos);
			if(minDistance>temp.distance(PacmanPosition)){
				minDistance=temp.distance(PacmanPosition);
				minDistancePoint=temp;
//				cout<<12-minDistancePoint.getY()<<"  "<<minDistancePoint.getX()<<endl;
			}
		}
		d.pop_front();
	}
//	for (int i = 0; i < 14; ++i) {
//		for (int j = 0; j < 17; ++j) {
//			cout<<copy_array[i][j]<<"  ";
//		}
//		cout<<endl;
//	}

	direction=copy_array[12-minDistancePoint.getY()][minDistancePoint.getX()];
	target=minDistancePoint;

}
void Pinky::move(){

	float minDistance=9999.99;
	deque<Point> d;
	Point EnemyPosition(position_x,position_y);
	Point minDistancePoint(position_x,position_y);
	if(copy_array[12-(EnemyPosition.getY()-1)][EnemyPosition.getX()]==direction){
		Point nextPostion(EnemyPosition.getX(),EnemyPosition.getY()-1);
		d.push_back(nextPostion);
	}
	if(copy_array[12-(EnemyPosition.getY()+1)][EnemyPosition.getX()]==direction){
			Point nextPostion(EnemyPosition.getX(),EnemyPosition.getY()+1);
			d.push_back(nextPostion);
		}
	if(copy_array[12-(EnemyPosition.getY())][EnemyPosition.getX()+1]==direction){
		Point nextPostion(EnemyPosition.getX()+1,EnemyPosition.getY());
		d.push_back(nextPostion);
	}
	if(copy_array[12-(EnemyPosition.getY())][EnemyPosition.getX()-1]==direction){
		Point nextPostion(EnemyPosition.getX()-1,EnemyPosition.getY());
		d.push_back(nextPostion);
	}

	while(!d.empty()){
		Point temp=d[0];
		if(minDistance>temp.distance(target)){
			minDistancePoint=temp;
			minDistance=temp.distance(target);
		}
		d.pop_front();
	}
	this->setEnemyPosition(minDistancePoint.getX(),minDistancePoint.getY());
	copy_array[12-minDistancePoint.getY()][minDistancePoint.getX()]=5;
}
int Pinky::getEnemyNumber(){
	return enemyNumber;
}

