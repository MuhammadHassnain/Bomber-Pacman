/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */

#include "Board.h"
#include <stdlib.h>
#include <cstdio>

const int Board::BOARD_X = 17;
const int Board::BOARD_Y = 14;
//here's Bomberman's crazy board

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL=0, and so on
// and these numbers are represented in the board array...
enum BoardParts {
	NILL, S_BRICK, G_BRICK, R_BRICK
};
enum GiftAndEnergizer{
	GIFT,ENERGIZER
};
// defining some utility functions...

static int board_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } };
static int copy_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } };
static int energizer_array[Board::BOARD_Y][Board::BOARD_X]={{0}};
void Board::initializeEnengizerBoard() {
	srand(time(NULL));
	for (int i = 0; i < BOARD_Y - 1; ++i) {
		for (int j = 0; j < BOARD_X; ++j) {
			if (board_array[i][j] == NILL) {
				energizer_array[i][j] = GiftAndEnergizer(ENERGIZER);
			} else if (board_array[i][j] == BoardParts(G_BRICK)
					|| board_array[i][j] == BoardParts(R_BRICK)) {
				if(GetRandInRange(0,10)<5){
					energizer_array[i][j] =GiftAndEnergizer(GIFT);
				}
				else{
					energizer_array[i][j] =2;
				}
			}
		}
	}
}
void Board::Draw1(){
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
			for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
				//			cout <<      " " << board_array[i][j] << " " << flush;
				switch (energizer_array[i][j]) {
				case 2:
					break;
				case GIFT:
					DrawRectangle(x - 10, y, ycellsize, xcellsize,
							colors[WHITE]);
					DrawString(x,y+25,"Gift",colors[BLACK]);
					//DrawLine(x - 10, y, x - 10 + ycellsize, y, 4, colors[BLACK]);
					break;
				case ENERGIZER:
					DrawCircle(x+20,y+30,10,colors[WHITE]);
					break;
				}
			}
		}
}

#ifdef WITH_TEXTURES
const int nbricks = 3;

GLuint texture[nbricks];
GLuint tid[nbricks];
string tnames[] = {"solid.png", "brick.png", "brick-green.png"};
GLuint mtid[nbricks];
int cwidth = 60, cheight = 60; // 60x60 pixels bricks...
void RegisterTextures()
/*Function is used to load the textures from the
 * files and display*/
{
	// allocate a texture name
	glGenTextures(nbricks, tid);

	vector<unsigned char> data;
	//ofstream ofile("image-data.bin", ios::binary | ios::out);
	// now load each bricks data...

	for (int i = 0; i < nbricks; ++i) {

		// Read current brick

		ReadImage(tnames[i], data);
		if (i == 0) {
			int length = data.size();
			//ofile.write((char*) &length, sizeof(int));
		}
		//ofile.write((char*) &data[0], sizeof(char) * data.size());

		cout << " Texture Id=" << tid[i] << endl;
		mtid[i] = tid[i];
		// select our current texture
		glBindTexture(GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
				wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
				wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, cwidth, cheight, GL_RGB,
				GL_UNSIGNED_BYTE, &data[0]);
	}
	//ofile.close();

}
void Drawbrick(const BoardParts &cname, float fx, float fy, float fwidth,
		float fheight)
/*Draws a specfic brick at given position coordinate
 * sx = position of x-axis from left-bottom
 * sy = position of y-axis from left-bottom
 * cwidth= width of displayed brick in pixels
 * cheight= height of displayed bricki pixels.
 * */
{

	glPushMatrix();
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mtid[cname - 1]);
//	glTranslatef(0, 0, 0);
//	glRotatef(-M_PI / 2, 0, 0, 1);
	glBegin (GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();
	glColor4f(1, 1, 1, 1);

//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}
#endif
// Destructor
Board::~Board(void) {
}
void Board::InitalizeBoard(int w, int h) {
	width = w;
	height = h;
	for (int i = 0; i < BOARD_Y - 1; ++i) {
		for (int j = 0; j < BOARD_X; ++j) {
			if (i == 0 || i == BOARD_Y - 2 || j == 0 || j == BOARD_X - 1)
				board_array[i][j] = S_BRICK;
			else if (i % 2 == 0 && j % 2 == 0)
				board_array[i][j] = S_BRICK;
			else
				board_array[i][j] =
						(GetRandInRange(0, 10)) < 8 ? NILL :
						(GetRandInRange(0, 10)) < 8 ? G_BRICK : R_BRICK;
			if (board_array[i][j] == 2 || board_array[i][j] == 3) {
				breakablebricks += 1;
			}
		}
	}
	gamePlay.setBreakableBricks(breakablebricks);
	gamePlay.setRemainingBreakableBricks(breakablebricks);
}


void Board::initializeCopyBoard(){
	for (int i = 0; i < BOARD_Y-1; ++i) {
		for (int j = 0; j < BOARD_X; ++j) {
			if(board_array[i][j]==0){
				copy_array[i][j]=4;
			}
			else{
				copy_array[i][j]=5;
			}
		}
	}
}
//Constructor
Board::Board(int xsize, int ysize):breakablebricks(0) {
	xcellsize = xsize;
	ycellsize = ysize;
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED;
	gcolor = PINK;
	enemy.push_back(new Blinky(copy_array,pacman.getPacmanX(),(pacman.getPacmanY()+1)));
	enemy.push_back(new Pinky(copy_array,pacman.getPacmanX(),(pacman.getPacmanY()+3)));
//set up board
}

void Board::Draw() {
	glColor3f(0, 0, 1);
	glPushMatrix();

#ifdef WITH_TEXTURES
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
				case NILL:
				// Empty space
				break;
				case S_BRICK:
				case G_BRICK:
				case R_BRICK:
				float fwidth = (float) (xcellsize) / width * 2, fheight =
				(float) ycellsize / height * 2;
				float fx = (float) (x - 10) / width * 2 - 1, fy = (float) y
				/ height * 2 - 1;

				/*Drawbrick((BoardParts) board_array[i][j], fx, fy, fwidth,
				 fheight);*/
				Drawbrick((BoardParts) board_array[i][j], (float)x/width-1, (float)y/height-1, fwidth,
						fheight);
				break;
			}
		}
	}
#else
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout <<      " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
			case NILL:
				// Empty space
				break;
			case S_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize,
						colors[SLATE_GRAY]);
				//DrawLine(x - 10, y, x - 10 + ycellsize, y, 4, colors[BLACK]);
				break;
			case G_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize,
						colors[LIGHT_GREEN]);
				break;
			case R_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize, colors[RED]);
				break;
			}
		}
	}
#endif
	glPopMatrix();
}

void Board::GetInitPinkyPosition(int &x, int &y) {
	x = xcellsize * 3;
	y = (BOARD_Y - 3) * ycellsize;
}
void Board::GetInitTextPosition(int &x, int &y) {
	x = xcellsize;
	y = (BOARD_Y - 1) * ycellsize + ycellsize / 2;
}

void Board::setPacmanPosition(int a,int b){
	pacman.setPacmanPosition(a,b);
}
void Board::getPacmanPosition(int& a,int &b){
	pacman.getPacmanPosition(a,b);
}
int Board::atboard(int a,int b){
	return board_array[a][b];
}
void Board::getBlickyPosition(int& a,int &b){
	enemy[0]->getEnemyPosition(a,b);
}
void Board::getEnemyPosition(int& a, int& b, int n) {
	for (unsigned int i = 0; i < enemy.size(); ++i) {
		if (enemy[i]->getEnemyNumber() == n) {
			enemy[i]->getEnemyPosition(a, b);
			return;
		}
		if(enemy[i]->getEnemyNumber()==n){
			enemy[i]->getEnemyPosition(a,b);
			return;
		}
	}
}

void Board::bfsBlinky(){
	for(unsigned int i=0;i<enemy.size();++i){
		if(enemy[i]->getEnemyNumber()==0){
			enemy[i]->setTargetPostion(pacman.getPacmanX(),pacman.getPacmanY());
			enemy[i]->initializeArray(copy_array);
			enemy[i]->initializeCopyArray();
			enemy[i]->BFS();
		}
		if(enemy[i]->getEnemyNumber()==1){
			srand(time(NULL));
			do {
				int x = GetRandInRange(0, 14), y = GetRandInRange(0, 17);
				if (board_array[x][y] == 0) {
					enemy[i]->setTargetPostion(x, y);
					break;
				}
			} while (true);
			enemy[i]->initializeArray(copy_array);
			enemy[i]->initializeCopyArray();
			enemy[i]->BFS();
		}
		if(enemy[i]->getEnemyNumber()==2){
			enemy[i]->setTargetPostion(pacman.getPacmanX(),pacman.getPacmanY());
			enemy[i]->initializeArray(copy_array);
			enemy[i]->initializeCopyArray();
			enemy[i]->BFS();
		}
		if(enemy[i]->getEnemyNumber()==3){
			enemy[i]->setTargetPostion(pacman.getPacmanX(),pacman.getPacmanY());
			enemy[i]->initializeArray(copy_array);
			enemy[i]->initializeCopyArray();
			enemy[i]->BFS();
		}
	}
}
void Board::moveBlinky(){
	for(unsigned int i=0;i<enemy.size();++i){
		enemy[i]->move();
	}
	checkSamePosition();


}
void Board::getPinkyPosition(int& a,int& b){
	enemy[1]->getEnemyPosition(a,b);
}
void Board::checkSamePosition(){
	int px, py, ex, ey;
	getPacmanPosition(px, py);
	for (unsigned int i = 0; i < enemy.size(); ++i) {
		if (gamePlay.getGhostMode() == 0) {
			enemy[i]->getEnemyPosition(ex, ey);
			if (px == ex && py == ey) {
				pacman.setLives(pacman.getLives() - 1);
				pacman.setPacmanPosition(1, 1);
			}
		}
		else if(gamePlay.getGhostMode()==1){
			enemy[i]->getEnemyPosition(ex, ey);
			if (px == ex && py == ey) {
				vector<Enemy*>::iterator remove=enemy.begin()+i;
				enemy.erase(remove);
				gamePlay.setScore(gamePlay.getScore()+200);
			}
		}
	}
}
///Bomb function
bool Board::getBombStatus(){
	return bomb.getBombStatus();
}
void Board::setBombStatus(bool s){
	bomb.setBombStatus(s);
}
void Board::setBomb(){
	if(!bomb.getBombStatus()){
		bomb.setBombPosition(pacman.getPacmanX(),pacman.getPacmanY());
	}
}
void Board::getBombPosition(int& x,int& y){
	bomb.getBombPosition(x,y);
}
void Board::setBombTime(int t){
	bomb.setBombTime(t);
}
int Board::getBombTime(){
	return bomb.getBombTime();
}
void Board::blast(){
	int bomb_x,bomb_y;
	bomb.getBombPosition(bomb_x,bomb_y);
	int pac_x,pac_y;
	pacman.getPacmanPosition(pac_x,pac_y);
	if ((bomb_x == pac_x && bomb_y == pac_y)
			|| (pac_x == bomb_x - 1 && pac_y == bomb_y)
			|| (pac_x == bomb_x + 1 && pac_y == bomb_y)
			|| (pac_x == bomb_x && pac_y == bomb_y - 1)
			|| (pac_x == bomb_x && pac_y == bomb_y + 1)) {
		pacman.setLives(pacman.getLives() - 1);
		pacman.setPacmanPosition(1, 1);
	}
	int enemy_x,enemy_y;
	for(unsigned int i=0;i<enemy.size();){
		enemy[i]->getEnemyPosition(enemy_x,enemy_y);
		if ((bomb_x == enemy_x && bomb_y == enemy_y)
					|| (enemy_x == bomb_x - 1 && enemy_y == bomb_y)
					|| (enemy_x == bomb_x + 1 && enemy_y == bomb_y)
					|| (enemy_x == bomb_x && enemy_y == bomb_y - 1)
					|| (enemy_x == bomb_x && enemy_y == bomb_y + 1)){
			vector<Enemy*>::iterator remove=enemy.begin()+i;
			enemy.erase(remove);
			gamePlay.setScore(gamePlay.getScore()+200);
		}
		else{
			++i;
		}
	}
	if (board_array[12 - (bomb_y)][bomb_x - 1] == 2) {
		board_array[12 - (bomb_y)][bomb_x - 1] = 0;
		gamePlay.setRemainingBreakableBricks(gamePlay.getRemainingBreakableBricks()-1);
		initializeCopyBoard();
		gamePlay.setScore(gamePlay.getScore()+50);

	}
	if (board_array[12 - (bomb_y)][bomb_x + 1] == 2) {
		board_array[12 - (bomb_y)][bomb_x + 1] = 0;
		gamePlay.setRemainingBreakableBricks(gamePlay.getRemainingBreakableBricks()-1);
		initializeCopyBoard();
		gamePlay.setScore(gamePlay.getScore()+50);

	}
	if (board_array[12 - (bomb_y + 1)][bomb_x] == 2) {
		board_array[12 - (bomb_y + 1)][bomb_x] = 0;
		gamePlay.setRemainingBreakableBricks(gamePlay.getRemainingBreakableBricks()-1);
		initializeCopyBoard();
		gamePlay.setScore(gamePlay.getScore()+50);
	}
	if (board_array[12 - (bomb_y - 1)][bomb_x] == 2) {
		board_array[12 - (bomb_y - 1)][bomb_x] = 0;
		gamePlay.setRemainingBreakableBricks(gamePlay.getRemainingBreakableBricks()-1);
		initializeCopyBoard();
		gamePlay.setScore(gamePlay.getScore()+50);
	}

	/////
	if (board_array[12 - (bomb_y)][bomb_x - 1] == 3) {
		Point temp(bomb_x-1,bomb_y);
		redBrickVector.push_back(temp);
		redBrickTime.push_back(10);

	}
	if (board_array[12 - (bomb_y)][bomb_x + 1] == 3) {
		Point temp(bomb_x+1,bomb_y);
		redBrickVector.push_back(temp);
		redBrickTime.push_back(10);
	}
	if (board_array[12 - (bomb_y + 1)][bomb_x] == 3) {
		Point temp(bomb_x,bomb_y+1);
		redBrickVector.push_back(temp);
		redBrickTime.push_back(10);
	}
	if (board_array[12 - (bomb_y - 1)][bomb_x] == 3) {
		Point temp(bomb_x,bomb_y-1);
		redBrickVector.push_back(temp);
		redBrickTime.push_back(10);
	}
}
void Board::setEnemyBehaviour(string behaviour){
	for(unsigned int i=0;i<enemy.size();++i){
		enemy[i]->setBehaviour(behaviour);
	}
}
bool Board::getIsClydeAdded(){
	return gamePlay.IsClydeAdded();
}
bool Board::getIsInkyAdded(){
	return gamePlay.IsInkyAdded();
}
float Board::remainingBreakAbleBricksPercent(){
	cout<<gamePlay.getRemainingBreakableBricks()<<endl;
	return gamePlay.getBreakableBricksPercent();
}
void Board::addClyde(){
	int px,py;
	pacman.getPacmanPosition(px,py);
	if(board_array[12-(py+1)][px]==0){
		enemy.push_back(new Clyde(copy_array,pacman.getPacmanX(),(pacman.getPacmanY()+1)));
	}
	else if(board_array[12-(py-1)][px]==0){
		enemy.push_back(new Clyde(copy_array,pacman.getPacmanX(),(pacman.getPacmanY()-1)));
	}
	else if(board_array[12-(py)][px+1]==0){
		enemy.push_back(new Clyde(copy_array,pacman.getPacmanX()+1,(pacman.getPacmanY())));
	}
	else if(board_array[12-(py)][px-1]==0){
		enemy.push_back(new Clyde(copy_array,pacman.getPacmanX()-1,(pacman.getPacmanY()+1)));
	}
	gamePlay.setIsClydeAdded();

}
void Board::addInky(){
	int px,py;
	pacman.getPacmanPosition(px,py);
	pacman.getPacmanPosition(px,py);
		if(board_array[12-(py+1)][px]==0){
			enemy.push_back(new Inky(copy_array,pacman.getPacmanX(),(pacman.getPacmanY()+1)));
		}
		else if(board_array[12-(py-1)][px]==0){
			enemy.push_back(new Inky(copy_array,pacman.getPacmanX(),(pacman.getPacmanY()-1)));
		}
		else if(board_array[12-(py)][px+1]==0){
			enemy.push_back(new Inky(copy_array,pacman.getPacmanX()+1,(pacman.getPacmanY())));
		}
		else if(board_array[12-(py)][px-1]==0){
			enemy.push_back(new Inky(copy_array,pacman.getPacmanX()-1,(pacman.getPacmanY()+1)));
		}
gamePlay.setIsInkyAdded();
}
int Board::getGameTime(){
	return gamePlay.getGameTime();
}
void Board::setGameTime(){
	gamePlay.setGameTime(gamePlay.getGameTime()-1);
}
void Board::setScore(int score){
	gamePlay.setScore(score);
}
int Board::getScore(){
	return gamePlay.getScore();
}
bool Board::isPlay(){
	return ((!enemy.empty())||(!isNoEnergizer())||(gamePlay.getRemainingBreakableBricks()>0)) && gamePlay.isPlay();
}
string Board::getEnemyBehaviour(){
	return enemy[0]->getBehaviour();
}
void Board::setChaseTime(int t){
	gamePlay.setChaseTime(t);
}
void Board::setScatterTime(int t){
	gamePlay.setScatterTime(t);
}
int Board::getChaseTime(){
	return gamePlay.getChaseTime();
}
int Board::getScatterTime(){
	return gamePlay.getScatterTime();
}
void Board::setGameMode(int m){
	gamePlay.setGameMode(m);
}
int Board::getGameMode(){
	return gamePlay.getGameMode();
}
int Board::getGhostMode(){
	return gamePlay.getGhostMode();
}
void Board::setGhostMode(int m){
	gamePlay.setGhostMode(m);
}
int Board::atEnergizerBoard(int a,int b){
	return energizer_array[a][b];
}
void Board::setEnergizerBoardAt(int i,int j){
	energizer_array[i][j]=2;
}
vector<Point> Board::getRedBricksDeque(){
	return redBrickVector;
}
void Board::destoryRedBrick(int i){
	vector<Point>::iterator it=redBrickVector.begin()+i;
	Point temp=redBrickVector[i];
	board_array[12-temp.getY()][temp.getX()]=0;
	gamePlay.setRemainingBreakableBricks(gamePlay.getRemainingBreakableBricks()-1);
	int bomb_y=temp.getY(),bomb_x=temp.getX();
	if (board_array[12 - (bomb_y)][bomb_x - 1] == 2) {
			board_array[12 - (bomb_y)][bomb_x - 1] = 0;
			gamePlay.setRemainingBreakableBricks(gamePlay.getRemainingBreakableBricks()-1);
			initializeCopyBoard();
			gamePlay.setScore(gamePlay.getScore()+50);

		}
		if (board_array[12 - (bomb_y)][bomb_x + 1] == 2) {
			board_array[12 - (bomb_y)][bomb_x + 1] = 0;
			gamePlay.setRemainingBreakableBricks(gamePlay.getRemainingBreakableBricks()-1);
			initializeCopyBoard();
			gamePlay.setScore(gamePlay.getScore()+50);

		}
		if (board_array[12 - (bomb_y + 1)][bomb_x] == 2) {
			board_array[12 - (bomb_y + 1)][bomb_x] = 0;
			gamePlay.setRemainingBreakableBricks(gamePlay.getRemainingBreakableBricks()-1);
			initializeCopyBoard();
			gamePlay.setScore(gamePlay.getScore()+50);
		}
		if (board_array[12 - (bomb_y - 1)][bomb_x] == 2) {
			board_array[12 - (bomb_y - 1)][bomb_x] = 0;
			gamePlay.setRemainingBreakableBricks(gamePlay.getRemainingBreakableBricks()-1);
			initializeCopyBoard();
			gamePlay.setScore(gamePlay.getScore()+50);
		}

	redBrickVector.erase(it);
	vector<int>::iterator it1=redBrickTime.begin()+i;
	redBrickTime.erase(it1);
	gamePlay.setScore(gamePlay.getScore()+200);
	initializeCopyBoard();
}
void Board::setRedBrickTime(int i){
	redBrickTime[i]=redBrickTime[i]-1;
}
vector<int> Board:: getRedBrickTime(){
	return redBrickTime;
}
bool Board::isNoEnergizer(){
	for(int i=0;i<14;++i){
		for(int j=0;j<17;++j){
			if(energizer_array[i][j]==1){
				return false;
			}
		}
	}
	return true;
}
