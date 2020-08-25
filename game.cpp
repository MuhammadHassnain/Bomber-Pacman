//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Brick Slayer...
//============================================================================

#ifndef Bomberman_CPP_
#define Bomberman_CPP_
#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
bool gamePlay=false;
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
void DrawEnemy(int x/*starting x*/, int y/*starting y*/,
		ColorNames color/*color*/, float gw = 6/*Enemy Width in Units*/,
		float gh = 7/*Enemy Height in Units*/) {
	int ogw = 6, ogh = 7;/*y-=60;*/
	glPushMatrix();
	float sx = (float) gw / ogw, sy = (float) gh / ogh;
	glTranslatef(x, y, 1);
	glScalef(sx, sy, 1);

	// Draw Enemy
	DrawRoundRect(0, 1, 6, 3, colors[color]);
	DrawCircle(3, 4, 3.01, colors[color]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[color]);
	DrawCircle(3.25, 1, 0.75, colors[color]);
	DrawCircle(5.85, 1, 0.75, colors[color]);

	glPopMatrix();
	//	glPopMatrix();

	// eyes

	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	DrawCircle(1.85, 3.95, 0.75, colors[WHITE]);
	DrawCircle(4.95, 3.95, 0.75, colors[WHITE]);
	glPopMatrix();

	// eyes
	DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
	glPopMatrix();
}

//Number of Vertices used to draw Bomberman Circle...
// x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius) {

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / 6.0;
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

void DrawBomberman(float sx/*center x*/, float sy/*center y*/,
		float radius/*Radius*/,
		const ColorNames &colorname/*Bomberman Colour*/) {

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin (GL_TRIANGLE_FAN);
	glVertex4f(sx, sy, 0, 1);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
			radius / 10, colors[BLACK]);
}
/*
 * Main Canvas drawing function.
 * */
Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	if(b->getGameMode()==0){
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
					0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
			glClear (GL_COLOR_BUFFER_BIT); //Update the colors
			DrawString(300,700,"WELCOME TO BOMBER+PACMAN",colors[WHITE]);
			DrawString(300,660,"	  VERSION 1.0",colors[WHITE]);
			DrawBomberman(380, 560, 50, YELLOW);
			DrawEnemy(460,500,WHITE,2 * b->GetCellSize(), 2 * b->GetCellSize());
			DrawString(50,440,"1.YOU CAN PLAY THE GAME WITH KEYBOARD UP-DOWN-LEFT-RIGHT BUTTON",colors[WHITE]);
			DrawString(50,400,"2.BOMBERMAN HAS ONLY 3 CHANCE TO SURVIVE AND BOMBERMAN CAN ONLY ",colors[WHITE]);
			DrawString(50,360,"  EAT ENEMY WHEN THERE's COLOR IS BLUE",colors[WHITE]);
			DrawString(50,320,"3.RED BRICK DESTORYED AFTER 10Sec WHILE GREEN BRICKS DESTORY ",colors[WHITE]);
			DrawString(50,280,"  IMMIDIATELY.",colors[WHITE]);
			DrawString(400,60,"4.Press P to Play The game!",colors[WHITE]);
		}
	else if(b->getGameMode()==1){

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//

	if(b->isPlay() && b->getPacmanLives()>0){
	b->Draw1();
	b->Draw();
	int x, y;
	string time=Num2Str(b->getGameTime());
	b->GetInitTextPosition(x,y);
	x+=180;
	DrawString(x,y,time,colors[RED]);
	vector<Enemy*> enemy=b->getEnemyVector();

	for(unsigned int i=0;i<enemy.size();++i){
		if(b->getGhostMode()==0){
		if(enemy[i]->getEnemyNumber()==0){
			//Blinky
			b->getEnemyPosition(x,y,0);
			x=x*60;y=y*60;
			DrawEnemy(x, y, ORANGE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		}
		if(enemy[i]->getEnemyNumber()==1){
			//PINKY
			b->getEnemyPosition(x,y,1);
			x=x*60;y=y*60;
			DrawEnemy(x,y,PINK,0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		}
		if(enemy[i]->getEnemyNumber()==2){
					//PINKY
					b->getEnemyPosition(x,y,2);
					x=x*60;y=y*60;
					DrawEnemy(x,y,YELLOW,0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
				}
		if(enemy[i]->getEnemyNumber()==3){
					//PINKY
					b->getEnemyPosition(x,y,3);
					x=x*60;y=y*60;
					DrawEnemy(x,y,RED,0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
				}
		}
		else if(b->getGhostMode()==1){

			if(enemy[i]->getEnemyNumber()==0){
				//Blinky
				b->getEnemyPosition(x,y,0);
				x=x*60;y=y*60;
				DrawEnemy(x, y, BLUE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
			}
			if(enemy[i]->getEnemyNumber()==1){
				//PINKY
				b->getEnemyPosition(x,y,1);
				x=x*60;y=y*60;
				DrawEnemy(x,y,BLUE,0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
			}
			if(enemy[i]->getEnemyNumber()==2){
						//PINKY
						b->getEnemyPosition(x,y,2);
						x=x*60;y=y*60;
						DrawEnemy(x,y,BLUE,0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
					}
			if(enemy[i]->getEnemyNumber()==3){
						//PINKY
						b->getEnemyPosition(x,y,3);
						x=x*60;y=y*60;
						DrawEnemy(x,y,BLUE,0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
					}
		}
	}
	b->getPacmanPosition(x,y);
	x=x*60+20;y=y*60+30;
	DrawBomberman(x, y, b->GetCellSize() / 2 - 2, YELLOW);
	b->GetInitTextPosition(x, y);
	string score=Num2Str(b->getScore());
	DrawString(x, y, "SCORE:", colors[5]);
	DrawString(x+90, y, score, colors[5]);
	x+=480;
	for(int i=0;i<b->getPacmanLives();++i,x+=20){
		DrawEnemy(x,y,WHITE,0.2 * b->GetCellSize(), 0.2 * b->GetCellSize());
	}
	//	glPopMatrix();
	if (b->getBombStatus()==true) {
		int bx,by;
		b->getBombPosition(bx,by);
		DrawCircle(bx*60+20, by*60+30, 15, colors[60]); // To Draw a bomb. You will provide your own x and y relative to Bombermans position
		if(b->getBombTime()<=0){
			DrawRectangle((bx ) * 60 - 10, by * 60, b->GetCellSize(),
								b->GetCellSize(), colors[60]);
			DrawRectangle((bx - 1) * 60 - 10, by * 60, b->GetCellSize(),
					b->GetCellSize(), colors[60]);
			DrawRectangle((bx + 1) * 60 - 10, by * 60, b->GetCellSize(),
								b->GetCellSize(), colors[60]);
			DrawRectangle((bx ) * 60 - 10, (by+1) * 60, b->GetCellSize(),
								b->GetCellSize(), colors[60]);
			DrawRectangle((bx ) * 60 - 10, (by-1) * 60, b->GetCellSize(),
								b->GetCellSize(), colors[60]);
			}
	}

	}
	else{
		DrawBomberman(380, 560, 50, YELLOW);
					DrawEnemy(460,500,WHITE,2 * b->GetCellSize(), 2 * b->GetCellSize());
		if(b->getPacmanLives()<=0){
			DrawString(300, 300, "GAME OVER", colors[WHITE]);
			DrawString(300, 260, "YOU RUN OUR OF LIVES", colors[WHITE]);
			DrawString(300, 220, "YOUR SCORE IS:", colors[WHITE]);
			DrawString(490, 220, Num2Str(b->getScore()), colors[RED]);
		}
		else if(b->getGameTime()<=0){
			DrawString(300, 300, "GAME OVER", colors[WHITE]);
			DrawString(300, 260, "YOU RUN OUR OF TIME!", colors[WHITE]);
			DrawString(300, 220, "YOUR SCORE IS:", colors[WHITE]);
			DrawString(490, 220, Num2Str(b->getScore()), colors[RED]);
		}
		else{

			DrawString(300, 300, "GAME OVER", colors[WHITE]);
			DrawString(300, 260, "CONGRAGULATION! You Win", colors[WHITE]);
			DrawString(300, 220, "YOUR SCORE IS:", colors[WHITE]);
			DrawString(490, 220, Num2Str(b->getScore()), colors[RED]);
		}
	}
	}
	else if(b->getGameMode()==2){

		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
				0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		DrawBomberman(380, 560, 50, YELLOW);
		DrawEnemy(460,500,WHITE,2 * b->GetCellSize(), 2 * b->GetCellSize());
		DrawString(430,400,"GAME PAUSE",colors[WHITE]);

	}
	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if(b->getGameMode()==1){
	if(b->isPlay()&& b->getPacmanLives()>0){
	int xx,yy;
	b->getPacmanPosition(xx,yy);
	if(b->atEnergizerBoard(12-yy,xx)!=2){
		b->setScore(b->getScore()+100);
		b->setEnergizerBoardAt(12-yy,xx);
	}
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		if (b->atboard(12 - yy, xx - 1) == 0) {
			xx -= 1;
			b->setPacmanPosition(xx, yy);
		}

	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		if (b->atboard(12 - yy, xx + 1) == 0) {
			xx += 1;
			b->setPacmanPosition(xx, yy);
		}
	} else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		if (b->atboard(12 - (yy + 1), xx) == 0) {
			yy += 1;
			b->setPacmanPosition(xx, yy);
		}
	} else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		if (b->atboard(12 - (yy - 1), xx) == 0) {
			yy -= 1;
			b->setPacmanPosition(xx, yy);
		}
	}
	b->bfsBlinky();
	b->checkSamePosition();
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	if(b->atEnergizerBoard(12-yy,xx)!=2){
			b->setScore(b->getScore()+100);
			b->setEnergizerBoardAt(12-yy,xx);
		}
	}
	glutPostRedisplay();
	}
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	if ((key == 'b' || key == 'B') && b->getGameMode()==1&&b->isPlay()) //Key for placing the bomb
	{
		b->setBomb();
		b->setBombStatus(true);

	}
	if( (key== 'p'|| key =='P')&& b->isPlay()){
		if(b->getGameMode()==0){
			b->setGameMode(1);
		}
		else if(b->getGameMode()==1){
			b->setGameMode(2);
		}
		else if(b->getGameMode()==2){
			b->setGameMode(1);
			b->bfsBlinky();
		}
	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {
	if(b->getGameMode()==1){
	if(b->isPlay()&& b->getPacmanLives()>0){
		if(b->getGhostMode()==0){
			b->setChaseTime(b->getChaseTime()-1);
			if(b->getChaseTime()==0){
				b->setGhostMode(1);
				b->setEnemyBehaviour("scatter");
				b->setChaseTime();
			}
		}
		if(b->getGhostMode()==1){
			b->setScatterTime(b->getScatterTime()-1);
			if(b->getScatterTime()==0){
				b->setGhostMode(0);
				b->setEnemyBehaviour("chase");
				b->setScatterTime();
			}
		}
	b->moveBlinky();
	if(b->getBombStatus() && b->getBombTime()>=0){
		if(b->getBombTime()==0){
			b->setBombTime();
			b->blast();
			b->setBombStatus(false);
		}
		else{
			b->setBombTime(b->getBombTime()-1);
		}
	}
	if(b->getIsClydeAdded()==false && b->remainingBreakAbleBricksPercent()<=70.0){
		b->addClyde();
	}
	if(b->getIsInkyAdded()==false && b->remainingBreakAbleBricksPercent()<=30.0){
		b->addInky();
	}
	vector<int> temp=b->getRedBrickTime();
	for(unsigned i=0;i<temp.size();++i){
		if(temp[i]==0){
			b->destoryRedBrick(i);
		}
		else{
			b->setRedBrickTime(i);
		}
	}
	b->setGameTime();
	// implement your functionality hereb/
	// once again we tell the library to call our Timer function after next 1000/FPS
		}

	}
	glutTimerFunc(1000, Timer, 0);
	glutPostRedisplay();
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	b = new Board(60, 60); // create a new board object to use in the Display Function ...
	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	b->InitalizeBoard(width, height);
	b->initializeEnengizerBoard();
	b->initializeCopyBoard();
	b->setGameMode(0);
	b->setGhostMode(0);
	b->setChaseTime();
	b->setScatterTime();
	b->setEnemyBehaviour("chase");
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Bomber Bomberman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Bomberman_CPP_ */
