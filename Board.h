/*
 * Board.h
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <GL/glut.h>
#include <iostream>
#include<iterator>
#include<vector>
#include<algorithm>
#include "util.h"
#include "Pacman.h"
#include "Enemy.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Bomb.h"
#include "GamePlay.h"
#include "Clyde.h"
#include "Inky.h"
#include<deque>
#include<utility>
//#define WITH_TEXTURES
using namespace std;
class Board {
private:

	int xcellsize, ycellsize;
	int width, height;
	ColorNames pcolor, bcolor, gcolor;
	Pacman pacman;
	vector<Enemy*> enemy;
	Bomb bomb;
	int breakablebricks;
	GamePlay gamePlay;
	vector<Point> redBrickVector;
	vector<int> redBrickTime;
public:
	static const int BOARD_X;
	static const int BOARD_Y;
	Board(int xsize = 8, int ysize = 8);

	~Board(void);
	void InitalizeBoard(int, int);
	void initializeEnengizerBoard();
	void Draw1();
	//draw the board
	void Draw();

	static int GetBoardX() {
		return BOARD_X;
	}
	static int GetBoardY() {
		return BOARD_Y;
	}
	int GetMidX() {
		return BOARD_X * xcellsize / 2.0;
	}
	int GetMidY() {
		return BOARD_Y * ycellsize / 2.0;
	}
	int GetCellSize() {
		return xcellsize;
	}
	void GetInitBombermanPosition(int &x, int &y) {
		x = xcellsize + xcellsize / 2;
		y = ycellsize + ycellsize / 2;
	}
	int atEnergizerBoard(int,int);
	void setEnergizerBoardAt(int,int);
	void GetInitTextPosition(int &x, int &y);
	void GetInitPinkyPosition(int &x, int &y);
	void getPacmanPosition(int& a,int &b);
	void setPacmanPosition(int a,int b);
	int atboard(int,int);
	void getBlickyPosition(int&,int&);
	void getPinkyPosition(int&,int&);
	void initializeCopyBoard();
	void bfsBlinky();
	void moveBlinky();
	void checkSamePosition();
	void getEnemyPosition(int&,int&,int);
	int getPacmanLives(){
		return pacman.getLives();
	}
	void setEnemyBehaviour(string);
	string getEnemyBehaviour();
	//Function for Bomb Class
	void setBomb();
	void getBombPosition(int&,int&);
	bool getBombStatus();
	void setBombStatus(bool);
	int getBombTime();
	void setBombTime(int=1);
	void blast();
	vector<Enemy*> getEnemyVector(){
		return enemy;
	}
	//GamePlay Function
	bool getIsInkyAdded();
	bool getIsClydeAdded();
	float remainingBreakAbleBricksPercent();
	void addClyde();
	void addInky();
	int getGameTime();
	void setGameTime();
	int getScore();
	void setScore(int);
	bool isPlay();
	void setChaseTime(int=20);
	void setScatterTime(int=7);
	int getChaseTime();
	int getScatterTime();
	void setGameMode(int);
	int getGameMode();
	void setGhostMode(int);
	int getGhostMode();
	vector<Point> getRedBricksDeque();
	vector<int> getRedBrickTime();
	void destoryRedBrick(int i);
	void setRedBrickTime(int i);
	bool isNoEnergizer();
	//	int GetMidx
};

#ifdef WITH_TEXTURES
void RegisterTextures();
#endif

#endif
