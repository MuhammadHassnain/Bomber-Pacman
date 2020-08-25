/*
 * GamePlay.h
 *
 *  Created on: May 20, 2017
 *      Author: muhammadhassnain
 */

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_
class GamePlay {
	int score;
	int gametime;
	int totalBreakableBricks;
	int remainingBreakableBricks;
	bool isClydeAdded;
	bool isInkyAdded;
	int chaseTime;
	int scatterTime;
	int gameMode;
	int ghostMode;
public:
	GamePlay(int=120);
	void setScore(int);
	int getScore();
	void setBreakableBricks(int);
	void setRemainingBreakableBricks(int);
	int getGameTime();
	int getTotalBreakableBricks();
	int getRemainingBreakableBricks();
	float getBreakableBricksPercent();
	bool IsClydeAdded();
	bool IsInkyAdded();
	void setIsClydeAdded();
	void setIsInkyAdded();
	void setGameTime(int);
	bool isPlay();
	void setChaseTime(int=20);
	void setScatterTime(int=7);
	int getChaseTime();
	int getScatterTime();
	void setGameMode(int);
	int getGameMode();
	void setGhostMode(int);
	int getGhostMode();
};

#endif /* GAMEPLAY_H_ */
