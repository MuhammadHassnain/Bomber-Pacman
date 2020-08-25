/*
 * GamePlay.cpp
 *
 *  Created on: May 20, 2017
 *      Author: muhammadhassnain
 */

#include "GamePlay.h"
#include<iostream>

GamePlay::GamePlay(int gt):score(0),gameMode(0) {
	gametime=gt;
	isClydeAdded=false;
	isInkyAdded=false;
}
void GamePlay::setScore(int s){
	score=s;
}
void GamePlay::setBreakableBricks(int bb){
	totalBreakableBricks=bb;
}
void GamePlay::setRemainingBreakableBricks(int rbb){
	remainingBreakableBricks=rbb;
}
int GamePlay::getGameTime(){
	return gametime;
}
int GamePlay::getRemainingBreakableBricks(){
	return remainingBreakableBricks;
}
int GamePlay::getTotalBreakableBricks(){
	return totalBreakableBricks;
}
float GamePlay::getBreakableBricksPercent(){
	return (((float)remainingBreakableBricks)/((float)totalBreakableBricks))*100;
}
bool GamePlay::IsClydeAdded(){
	return isClydeAdded;
}
bool GamePlay::IsInkyAdded(){
	return isInkyAdded;
}
void GamePlay::setIsClydeAdded(){
	isClydeAdded=true;
}
void GamePlay::setIsInkyAdded(){
	isInkyAdded=true;
}
void GamePlay::setGameTime(int gt){
	gametime=gt;
}
int GamePlay::getScore(){
	return score;
}
bool GamePlay::isPlay(){
	if(gametime>=0){
		return true;
	}
	return false;
}

int GamePlay::getChaseTime(){
	return chaseTime;
}
int GamePlay::getScatterTime(){
	return scatterTime;
}
void GamePlay::setChaseTime(int t){
	chaseTime=t;
}
void GamePlay::setScatterTime(int t){
	scatterTime=t;
}
void GamePlay::setGameMode(int m){
	gameMode=m;
}
int GamePlay::getGameMode(){
	return gameMode;
}
void GamePlay::setGhostMode(int m){
	ghostMode=m;
}
int GamePlay::getGhostMode(){
	return ghostMode;
}
