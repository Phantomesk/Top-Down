#include "AIE.h"
#include <iostream>
#include <fstream>
using namespace std;

const int iScreenHeight = 850;
const int iScreenWidth = 700;

char playerScore1[10];
char highScore1[64];
char playerLife[10];

int playerScore = 000000000;
int highScore = 200;
int playerLives = 3;

enum GAMESTATES
{
	MAIN_MENU,
	GAMEPLAY,
	HIGHSCORE,
	GAMEOVER,	//the different gamestates of my game
	EXIT_GAME
};
GAMESTATES eCurrentState = MAIN_MENU;

struct Collision
{
	float xMin;
	float yMin;
	float xMax;		//collision structure
	float yMax;
};

struct Fire
{
	unsigned int iBulletID;
	float x;
	float y;
	Collision Planes;
	float ySpeed = 1.f;
	float width;
	float height;

	void SetSize(float a_width, float a_height)
	{
		width = a_width;
		height = a_height;
	}

	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}

	void Movement(float a_fDeltaTime)
	{
		{
			y += ySpeed * a_fDeltaTime;
		}
		MoveSprite(iBulletID, x, y);

		y = (ySpeed + y);

		Planes.xMin = x - (width * .5f);
		Planes.yMin = y - (height * .5f);
		Planes.xMax = x + (width * .5f);
		Planes.yMax = y + (height * .5f);
	}
};
Fire fire;

struct Player
{
	unsigned int iPlaneID;
	float x;
	float y;
	Collision Planes;
	float ySpeed = 400.f;
	float xSpeed = 400.f;
	float width;
	float height;
	unsigned int iMoveUpKey;
	unsigned int iMoveDownKey;
	unsigned int iMoveRightKey;
	unsigned int iMoveLeftKey;

	void SetSize(float a_width, float a_height)
	{
		width = a_width;
		height = a_height;
	}

	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}

	void Movement(float a_fDeltaTime)
	{
		

		if (IsKeyDown(GLFW_KEY_UP))
		{
			y += ySpeed * a_fDeltaTime;;
			if (y > ((iScreenHeight - 30) -(height*.5f)))
			{
				y = ((iScreenHeight-30) - (height*.5f));
			}
		}
		if (IsKeyDown(GLFW_KEY_DOWN))
		{
			y -= ySpeed * a_fDeltaTime;
			if (y < height*.5f)
			{
				y = height*.5f;
			}
		}
		if (IsKeyDown(GLFW_KEY_LEFT))
		{
			x -= xSpeed * a_fDeltaTime;
			if (x < (0+(width*.5f)))
			{
				x = 0 + (width *.5f);
			}
		}
		if (IsKeyDown(GLFW_KEY_RIGHT))
		{
			x += xSpeed * a_fDeltaTime;
			if (x > (iScreenWidth - (width * .5f)))
			{
				x = iScreenWidth - (width*.5f);
			}
		}

		MoveSprite(iPlaneID, x, y);

		Planes.xMin = x - (width * .5f);
		Planes.yMin = y - (height * .5f);
		Planes.xMax = x + (width * .5f);
		Planes.yMax = y + (height * .5f);
	}

	void bulletFire()
	{
		if (IsKeyDown(GLFW_KEY_SPACE))
		{
			fire.x = x;
			fire.y = y + fire.ySpeed;
		}
	}
};
Player playerPlane;

struct Enemies
{
	unsigned int iPlaneID;
	float x;
	float y;
	Collision Planes;
	float ySpeed1 = -.15f;
	float xSpeed1 = -.25f;
	float xSpeed2 = .3f;
	float ySpeed2 = -.1f;
	float xSpeed3 = -.2f;
	float ySpeed3 = -.2f;
	float xSpeed4 = .25f;
	float ySpeed4 = -.25f;
	float width;
	float height;

	void SetSize(float a_width, float a_height)
	{
		width = a_width;
		height = a_height;
	}

	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}

	void Movement1(float a_fDeltaTime)
	{
		if (x < (width*.5f))
		{
			x = width*.5f;
			xSpeed1 *= -1.01f;
			ySpeed1 *= 1.01f;
		}
		if (x > iScreenWidth-(width*.5f))
		{
			x = iScreenWidth - (width*.5f);
			xSpeed1 *= -1.01f;
			ySpeed1 *= 1.01f;
		}
		if (y < (0 - (height*.5f)))
		{
			y = (iScreenHeight - height*.5f) - 30;
			x = iScreenWidth * .5f;
		}

		x = (xSpeed1 + x);
		y = (ySpeed1 + y);

		MoveSprite(iPlaneID, x, y);

		Planes.xMin = x - (width * .5f);
		Planes.yMin = y - (height * .5f);
		Planes.xMax = x + (width * .5f);
		Planes.yMax = y + (height * .5f);
	}
	void Movement2(float a_fDeltaTime)
	{
		if (x < (width*.5f))
		{
			x = width*.5f;
			xSpeed2 *= -1.01f;
			ySpeed2 *= 1.01f;
		}
		if (x > iScreenWidth - (width*.5f))
		{
			x = iScreenWidth - (width*.5f);
			xSpeed2 *= -1.01f;
			ySpeed2 *= 1.01f;
		}
		if (y < (0 - (height*.5f)))
		{
			y = (iScreenHeight - height*.5f) - 30;
			x = iScreenWidth * .4f;
		}

		x = (xSpeed2 + x);
		y = (ySpeed2 + y);

		MoveSprite(iPlaneID, x, y);

		Planes.xMin = x - (width * .5f);
		Planes.yMin = y - (height * .5f);
		Planes.xMax = x + (width * .5f);
		Planes.yMax = y + (height * .5f);
	}
	void Movement3(float a_fDeltaTime)
	{
		if (x < (width*.5f))
		{
			x = width*.5f;
			xSpeed3 *= -1.01f;
			ySpeed3 *= 1.01f;
		}
		if (x > iScreenWidth - (width*.5f))
		{
			x = iScreenWidth - (width*.5f);
			xSpeed3 *= -1.01f;
			ySpeed3 *= 1.01f;
		}
		if (y < (0 - (height*.5f)))
		{
			y = (iScreenHeight - height*.5f) - 30;
			x = iScreenWidth * .4f;
		}

		x = (xSpeed3 + x);
		y = (ySpeed3 + y);

		MoveSprite(iPlaneID, x, y);

		Planes.xMin = x - (width * .5f);
		Planes.yMin = y - (height * .5f);
		Planes.xMax = x + (width * .5f);
		Planes.yMax = y + (height * .5f);
	}
	void Movement4(float a_fDeltaTime)
	{
		if (x < (width*.5f))
		{
			x = width*.5f;
			xSpeed4 *= -1.01f;
			ySpeed4 *= 1.01f;
		}
		if (x > iScreenWidth - (width*.5f))
		{
			x = iScreenWidth - (width*.5f);
			xSpeed4 *= -1.01f;
			ySpeed4 *= 1.01f;
		}
		if (y < (0 - (height*.5f)))
		{
			y = (iScreenHeight - height*.5f) - 30;
			x = iScreenWidth * .4f;
		}

		x = (xSpeed4 + x);
		y = (ySpeed4 + y);

		MoveSprite(iPlaneID, x, y);

		Planes.xMin = x - (width * .5f);
		Planes.yMin = y - (height * .5f);
		Planes.xMax = x + (width * .5f);
		Planes.yMax = y + (height * .5f);
	}
};
Enemies enemyPlane1, enemyPlane2, enemyPlane3, enemyPlane4;

struct Background
{
	unsigned int iScreenID;
	float x;
	float y;
	float ySpeed = -.1f;
	float width;
	float height;

	void SetSize(float a_width, float a_height)
	{
		width = a_width;
		height = a_height;
	}

	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}

	void Movement(float a_fDeltaTime)
	{
		MoveSprite(iScreenID, x, y);

		y = (ySpeed + y);
	}
};
Background screen1, screen2;

bool CollisionCheck(Collision box1, Collision box2)
{
	if (box1.xMin > box2.xMin && box1.yMin > box2.yMin && box1.xMin < box2.xMax && box1.yMin < box2.yMax)
	{
		return true;
	}
	if (box1.xMax > box2.xMin && box1.yMax > box2.yMin && box1.xMax < box2.xMax && box1.yMax < box2.yMax)
	{
		return true;
	}
	if (box1.xMin > box2.xMin && box1.yMax > box2.yMin && box1.xMin < box2.xMax && box1.yMax < box2.yMax)
	{
		return true;
	}
	if (box1.xMax > box2.xMin && box1.yMin > box2.yMin && box1.xMax < box2.xMax && box1.yMin < box2.yMax)
	{
		return true;
	}
	return false;
}

bool ScrollingScreen(Background screen1, Background screen2)
{
	if (screen1.y < 0)
	{
		return true;
	}
	if (screen2.y < 0)
	{
		return true;
	}
	return false;
}

void UpdateMainMenu();
void UpdateGamePlay();
void UpdateHighScore();
void readHighScore(const char* fileName);
void writeHighScore(const char* fileName, int fileData);
void UpdateGameOverScreen();

int main( int argc, char* argv[] )
{	
    Initialise(iScreenWidth, iScreenHeight, false, "Top-Down");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	playerPlane.SetSize(75.f, 64.f);
	enemyPlane1.SetSize(75.f, 64.f);
	enemyPlane2.SetSize(75.f, 64.f);
	enemyPlane3.SetSize(75.f, 64.f);
	enemyPlane4.SetSize(75.f, 64.f);
	fire.SetSize(28.f, 28.f);
	screen1.SetSize(iScreenWidth, iScreenHeight);
	screen2.SetSize(iScreenWidth, iScreenHeight);

	playerPlane.SetPosition(iScreenWidth * .5f, 150.f);
	enemyPlane1.SetPosition(iScreenWidth*.5f, ((iScreenHeight - (enemyPlane1.height*.5f))-30));
	enemyPlane2.SetPosition(iScreenWidth*.6f, ((iScreenHeight - (enemyPlane2.height * .5f))-30));
	enemyPlane3.SetPosition(iScreenWidth*.7f, ((iScreenHeight - (enemyPlane3.height * .5f)) - 30));
	enemyPlane4.SetPosition(iScreenWidth*.4f, ((iScreenHeight - (enemyPlane4.height * .5f)) - 30));
	screen1.SetPosition(iScreenWidth*.5f, iScreenHeight*.5f);
	screen2.SetPosition(iScreenWidth*.5f, (iScreenHeight*.5f + iScreenHeight));

	playerPlane.iPlaneID = CreateSprite("./images/PlayerPlane.png", playerPlane.width, playerPlane.height, true);
	enemyPlane1.iPlaneID = CreateSprite("./images/EnemyPlane1.png", enemyPlane1.width, enemyPlane1.height, true);
	enemyPlane2.iPlaneID = CreateSprite("./images/EnemyPlane2.png", enemyPlane2.width, enemyPlane2.height, true);
	enemyPlane3.iPlaneID = CreateSprite("./images/EnemyPlane3.png", enemyPlane2.width, enemyPlane2.height, true);
	enemyPlane4.iPlaneID = CreateSprite("./images/EnemyPlane4.png", enemyPlane2.width, enemyPlane2.height, true);
	fire.iBulletID = CreateSprite("./images/Bullet.png", fire.width, fire.height, true);
	screen1.iScreenID = CreateSprite("./images/background.png", screen1.width, screen1.height, true);
	screen2.iScreenID = CreateSprite("./images/background.png", screen1.width, screen1.height, true);

    //Game Loop
    do
    {
		switch (eCurrentState)
		{
		case MAIN_MENU:
			UpdateMainMenu();
			break;

		case GAMEPLAY:
			UpdateGamePlay();
			break;

		case HIGHSCORE:
			UpdateHighScore();
			break;

		case GAMEOVER:
			UpdateGameOverScreen();
			break;

		case EXIT_GAME:
			return 0;

		default:
			break;
		}

		ClearScreen();
    }
	
	while(!FrameworkUpdate());

    Shutdown();

    return 0;
}

void UpdateMainMenu()
{
	readHighScore("HighScore.txt");

	playerPlane.SetPosition(iScreenWidth * .5f, 150.f);
	enemyPlane1.SetPosition(iScreenWidth*.5f, ((iScreenHeight - (enemyPlane1.height * .5f)) - 30));
	enemyPlane2.SetPosition(iScreenWidth*.6f, ((iScreenHeight - (enemyPlane2.height * .5f)) - 30));
	enemyPlane3.SetPosition(iScreenWidth*.7f, ((iScreenHeight - (enemyPlane3.height * .5f)) - 30));
	enemyPlane4.SetPosition(iScreenWidth*.4f, ((iScreenHeight - (enemyPlane4.height * .5f)) - 30));

	enemyPlane1.ySpeed1 = -.15f;
	enemyPlane1.xSpeed1 = -.25f;
	enemyPlane2.xSpeed2 = .3f;
	enemyPlane2.ySpeed2 = -.1f;
	enemyPlane3.xSpeed3 = -.2f;
	enemyPlane3.ySpeed3 = -.2f;
	enemyPlane4.xSpeed4 = .25f;
	enemyPlane4.ySpeed4 = -.25f;

	DrawString("Welcome to SHMUP", iScreenWidth *.35f, iScreenHeight *.7f);
	DrawString("Press Enter to start.", iScreenWidth*.35f, iScreenHeight*.6f);
	DrawString("Press H for High Score", iScreenWidth * .35f, iScreenHeight * .5f);
	DrawString("Press Esc to exit.", iScreenWidth*.35f, iScreenHeight*.4f);

	if (IsKeyDown(GLFW_KEY_ENTER))
	{
		eCurrentState = GAMEPLAY;
		ClearScreen();
	}
	if (IsKeyDown('H'))
	{
		eCurrentState = HIGHSCORE;
		ClearScreen();
	}
	if (IsKeyDown(GLFW_KEY_ESCAPE))
	{
		eCurrentState = EXIT_GAME;
	}

	ClearScreen();
}

void UpdateGamePlay()
{
	float fDeltaTime = GetDeltaTime();

	readHighScore("HighScore.txt");

	screen1.Movement(fDeltaTime);
	screen2.Movement(fDeltaTime);
	playerPlane.Movement(fDeltaTime);
	enemyPlane1.Movement1(fDeltaTime);
	enemyPlane2.Movement2(fDeltaTime);
	enemyPlane3.Movement3(fDeltaTime);
	enemyPlane4.Movement4(fDeltaTime);
	fire.Movement(fDeltaTime);
	playerPlane.bulletFire();


	/*if (CollisionCheck(enemyPlane1.Planes, playerPlane.Planes))
	{
		playerLives -= 1;
		playerPlane.x = iScreenWidth*.5f;
		playerPlane.y = 150.f;
		enemyPlane1.x = iScreenWidth*.5f;
		enemyPlane1.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane1.xSpeed1 *= .5f;
		enemyPlane1.ySpeed1 *= .5f;
		enemyPlane2.x = iScreenWidth*.6f;
		enemyPlane2.y = (iScreenHeight - (enemyPlane2.height*.5f)) - 30;
		enemyPlane2.xSpeed2 *= .5f;
		enemyPlane2.ySpeed2 *= .5f;
		enemyPlane3.x = iScreenWidth*.4f;
		enemyPlane3.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane3.xSpeed3 *= .5f;
		enemyPlane3.ySpeed3 *= .5f;
		enemyPlane4.x = iScreenWidth*.7f;
		enemyPlane4.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane4.xSpeed4 *= .5f;
		enemyPlane4.ySpeed4 *= .5f;
	}

	if (CollisionCheck(enemyPlane2.Planes, playerPlane.Planes))
	{
		playerLives -= 1;
		playerPlane.x = iScreenWidth*.5f;
		playerPlane.y = 150.f;
		enemyPlane1.x = iScreenWidth*.5f;
		enemyPlane1.y = (iScreenHeight - (enemyPlane1.height*.5f))-30;
		enemyPlane1.xSpeed1 *= .5f;
		enemyPlane1.ySpeed1 *= .5f;
		enemyPlane2.x = iScreenWidth*.6f;
		enemyPlane2.y = (iScreenHeight - (enemyPlane1.height*.5f))-30;
		enemyPlane2.xSpeed2 *= .5f;
		enemyPlane2.ySpeed2 *= .5f;
		enemyPlane3.x = iScreenWidth*.4f;
		enemyPlane3.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane3.xSpeed3 *= .5f;
		enemyPlane3.ySpeed3 *= .5f;
		enemyPlane4.x = iScreenWidth*.7f;
		enemyPlane4.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane4.xSpeed4 *= .5f;
		enemyPlane4.ySpeed4 *= .5f;
	}

	if (CollisionCheck(enemyPlane3.Planes, playerPlane.Planes))
	{
		playerLives -= 1;
		playerPlane.x = iScreenWidth*.5f;
		playerPlane.y = 150.f;
		enemyPlane1.x = iScreenWidth*.5f;
		enemyPlane1.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane1.xSpeed1 *= .5f;
		enemyPlane1.ySpeed1 *= .5f;
		enemyPlane2.x = iScreenWidth*.6f;
		enemyPlane2.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane2.xSpeed2 *= .5f;
		enemyPlane2.ySpeed2 *= .5f;
		enemyPlane3.x = iScreenWidth*.4f;
		enemyPlane3.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane3.xSpeed3 *= .5f;
		enemyPlane3.ySpeed3 *= .5f;
		enemyPlane4.x = iScreenWidth*.7f;
		enemyPlane4.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane4.xSpeed4 *= .5f;
		enemyPlane4.ySpeed4 *= .5f;
	}

	if (CollisionCheck(enemyPlane4.Planes, playerPlane.Planes))
	{
		playerLives -= 1;
		playerPlane.x = iScreenWidth*.5f;
		playerPlane.y = 150.f;
		enemyPlane1.x = iScreenWidth*.5f;
		enemyPlane1.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane1.xSpeed1 *= .5f;
		enemyPlane1.ySpeed1 *= .5f;
		enemyPlane2.x = iScreenWidth*.6f;
		enemyPlane2.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane2.xSpeed2 *= .5f;
		enemyPlane2.ySpeed2 *= .5f;
		enemyPlane3.x = iScreenWidth*.4f;
		enemyPlane3.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane3.xSpeed3 *= .5f;
		enemyPlane3.ySpeed3 *= .5f;
		enemyPlane4.x = iScreenWidth*.7f;
		enemyPlane4.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane4.xSpeed4 *= .5f;
		enemyPlane4.ySpeed4 *= .5f;
		if (playerLives == 0)
	}*/

	if (CollisionCheck(fire.Planes, enemyPlane1.Planes))
	{
		playerScore += 10;
		enemyPlane1.x = iScreenWidth*.5f;
		enemyPlane1.y = (iScreenHeight - (enemyPlane1.height*.5f)) - 30;
		enemyPlane1.xSpeed1 *= -1.05f;
		enemyPlane1.ySpeed1 *= 1.05f;
		fire.y = iScreenHeight + 200.f;
	}

	if (CollisionCheck(fire.Planes, enemyPlane2.Planes))
	{
		playerScore += 20;
		enemyPlane2.x = iScreenWidth * .6f;
		enemyPlane2.y = (iScreenHeight - (enemyPlane2.height*.5f)) - 30;
		enemyPlane2.xSpeed2 *= -1.05f;
		enemyPlane2.ySpeed2 *= 1.05f;
		fire.y = iScreenHeight + 200.f;
	}

	if (CollisionCheck(fire.Planes, enemyPlane3.Planes))
	{
		playerScore += 15;
		enemyPlane3.x = iScreenWidth*.7f;
		enemyPlane3.y = (iScreenHeight - (enemyPlane3.height*.5f)) - 30;
		enemyPlane3.xSpeed1 *= -1.05f;
		enemyPlane3.ySpeed1 *= 1.05f;
		fire.y = iScreenHeight + 200.f;
	}

	if (CollisionCheck(fire.Planes, enemyPlane4.Planes))
	{
		playerScore += 25;
		enemyPlane4.x = iScreenWidth*.4f;
		enemyPlane4.y = (iScreenHeight - (enemyPlane4.height*.5f)) - 30;
		enemyPlane4.xSpeed4 *= -1.05f;
		enemyPlane4.ySpeed4 *= 1.05f;
		fire.y = iScreenHeight + 200.f;
	}

	if (playerScore > highScore)
	{
		highScore = playerScore;
		writeHighScore("highscore.txt", highScore);
	}

	if (playerLives == 0)
	{
		eCurrentState = GAMEOVER;
	}

	if (screen1.y+425 < 0)
	{
		screen1.SetPosition(iScreenWidth*.5f, ((iScreenHeight*.5f) + iScreenHeight));
		screen1.Movement(fDeltaTime);
	}

	if (screen2.y+425 < 0)
	{
		screen1.SetPosition(iScreenWidth*.5f, ((iScreenHeight*.5f) + iScreenHeight));
		screen2.Movement(fDeltaTime);
	}

	DrawSprite(screen1.iScreenID);
	DrawSprite(screen2.iScreenID);
	DrawSprite(playerPlane.iPlaneID);
	DrawSprite(enemyPlane1.iPlaneID);
	DrawSprite(enemyPlane2.iPlaneID);
	DrawSprite(enemyPlane3.iPlaneID);
	DrawSprite(enemyPlane4.iPlaneID);
 	DrawSprite(fire.iBulletID);

	DrawString(playerScore1, iScreenWidth*.75f, iScreenHeight - 2);
	DrawString(playerLife, iScreenWidth*.15, iScreenHeight - 2);
	DrawString("Lives : ", iScreenWidth *.01f, iScreenHeight - 2);

	if (IsKeyDown('E'))
	{
		eCurrentState = MAIN_MENU;
		ClearScreen();
	}

	itoa(playerScore, playerScore1, 10);
	itoa(playerLives, playerLife, 10);
	itoa(highScore, highScore1, 10);

	ClearScreen();
}

void UpdateHighScore()
{
	readHighScore("HighScore.txt");

	playerPlane.SetPosition(iScreenWidth * .5f, 150.f);
	enemyPlane1.SetPosition(iScreenWidth*.5f, ((iScreenHeight - (enemyPlane1.height*.5f))-2));
	enemyPlane2.SetPosition(iScreenWidth*.4f, ((iScreenHeight - (enemyPlane2.height * .5f))-2));

	enemyPlane1.ySpeed1 = -.15f;
	enemyPlane1.xSpeed1 = -.25f;
	enemyPlane2.xSpeed2 = .3f;
	enemyPlane2.ySpeed2 = -.1f;
	enemyPlane3.xSpeed3 = -.2f;
	enemyPlane3.ySpeed3 = -.2f;
	enemyPlane4.xSpeed4 = .25f;
	enemyPlane4.ySpeed4 = -.25f;

	playerLives = 3;

	DrawString("High score :", iScreenWidth*.35f, iScreenHeight*.55f);
	readHighScore("HighScore.txt");
	DrawString(highScore1, iScreenWidth*.575f, iScreenHeight*.55f);
	DrawString("Press E to go to Main Menu", iScreenWidth*.025, iScreenHeight - 2);
	DrawString("Press Enter to start game", iScreenWidth* .55f, iScreenHeight - 2);

	if (IsKeyDown('E'))
	{
		eCurrentState = MAIN_MENU;

		ClearScreen();
	}
	if (IsKeyDown(GLFW_KEY_ENTER))
	{
		playerScore = 00000000;

		eCurrentState = GAMEPLAY;

		ClearScreen();
	}
	
	itoa(highScore, highScore1, 64);

	ClearScreen();
}

void UpdateGameOverScreen()
{
	readHighScore("HighScore.txt");

	float fDeltaTime = GetDeltaTime();

	playerPlane.SetPosition(iScreenWidth * .5f, 150.f);
	enemyPlane1.SetPosition(iScreenWidth*.5f, ((iScreenHeight - (enemyPlane1.height * .5f)) - 30));
	enemyPlane2.SetPosition(iScreenWidth*.6f, ((iScreenHeight - (enemyPlane2.height * .5f)) - 30));
	enemyPlane3.SetPosition(iScreenWidth*.7f, ((iScreenHeight - (enemyPlane3.height * .5f)) - 30));
	enemyPlane4.SetPosition(iScreenWidth*.4f, ((iScreenHeight - (enemyPlane4.height * .5f)) - 30));

	enemyPlane1.ySpeed1 = -.15f;
	enemyPlane1.xSpeed1 = -.25f;
	enemyPlane2.xSpeed2 = .3f;
	enemyPlane2.ySpeed2 = -.1f;
	enemyPlane3.xSpeed3 = -.2f;
	enemyPlane3.ySpeed3 = -.2f;
	enemyPlane4.xSpeed4 = .25f;
	enemyPlane4.ySpeed4 = -.25f;

	enemyPlane1.Movement1(fDeltaTime);
	enemyPlane2.Movement2(fDeltaTime);
	enemyPlane3.Movement3(fDeltaTime);
	enemyPlane4.Movement4(fDeltaTime);

	playerLives = 3;

	DrawString("You were rekt bitch", iScreenWidth*.35f, iScreenHeight * .7f);
	DrawString("Press Enter to start over", iScreenWidth*.35f, iScreenHeight*.6f);
	DrawString("Press E to go to Main Menu", iScreenWidth*.35f, iScreenHeight*.5f);
	DrawString("Press H for High Score", iScreenWidth * .35f, iScreenHeight * .4f);

	if (IsKeyDown(GLFW_KEY_ENTER))
	{
		eCurrentState = GAMEPLAY;
		playerScore = 000000000;
	}
	if (IsKeyDown('E'))
	{
		eCurrentState = MAIN_MENU;
	}
	if (IsKeyDown('H'))
	{
		eCurrentState = HIGHSCORE;
	}

	ClearScreen();
}

void readHighScore(const char* fileName)
{
	fstream fileStream;
	fileName = "HighScore.txt";
	fileStream.open(fileName, ios_base::in);
	highScore1[64];
	fileStream.getline(highScore1, 64);
	highScore = atoi(highScore1);
}

void writeHighScore(const char* fileName, int fileData)
{
	fstream fileStream;
	fileStream.open(fileName, ios_base::out);
	fileStream << fileData << endl;
	fileStream.flush();
	fileStream.close();
}