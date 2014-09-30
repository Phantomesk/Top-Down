#include "AIE.h"
#include <iostream>

const int iScreenHeight = 850;
const int iScreenWidth = 700;

char playerScore1[10];
char highScore1[10];

int playerScore = 000000000;
int highScore = 000000000;

enum GAMESTATES
{
	MAIN_MENU,
	GAMEPLAY,
	HIGHSCORE,
	GAMEOVER,	//the different gamestates of my game
	EXIT_GAME
};
GAMESTATES eCurrentState = MAIN_MENU;

struct Player
{
	unsigned int iPlaneID;
	float x;
	float y;
	float ySpeed = 250.f;
	float xSpeed = 250.f;
	float width;
	float height;
	float upperBoundry = y + height*.5f;
	float lowerBoundry = y - height*.5f;
	float rightBoundry = x + width*.5f;
	float leftBoundry = x - width*.5f;
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
			if (y > (iScreenHeight -(height*.5f)))
			{
				y = iScreenHeight - (height*.5f);
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
	}
};
Player playerPlane;

void UpdateMainMenu();
void UpdateGamePlay();
void UpdateHighScore();
void UpdateGameOverScreen();

int main( int argc, char* argv[] )
{	
    Initialise(iScreenWidth, iScreenHeight, false, "Top-Down");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	playerPlane.SetSize(75.f, 64.f);

	playerPlane.SetPosition(iScreenWidth * .5f, 150.f);

	playerPlane.iPlaneID = CreateSprite("./images/PlayerPlane.png", playerPlane.width, playerPlane.height, true);

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

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}

void UpdateMainMenu()
{
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

	playerPlane.Movement(fDeltaTime);

	MoveSprite(playerPlane.iPlaneID, playerPlane.x, playerPlane.y);

	DrawSprite(playerPlane.iPlaneID);

	DrawString(playerScore1, iScreenWidth*.975f, iScreenHeight - 2);

	if (IsKeyDown('E'))
	{
		eCurrentState = MAIN_MENU;
		ClearScreen();
	}

	itoa(playerScore, playerScore1, 10);

	ClearScreen();
}

void UpdateHighScore()
{
	DrawString("Player :", iScreenWidth*.35f, iScreenHeight*.55f);
	DrawString(playerScore1, iScreenWidth*.5f, iScreenHeight*.55f);
	DrawString("Press E to go to Main Menu", iScreenWidth*.025, iScreenHeight - 2);
	DrawString("Press Enter to start game", iScreenWidth* .6f, iScreenHeight - 2);

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
	ClearScreen();
}

void UpdateGameOverScreen()
{
	DrawString("You were rekt bitch", iScreenWidth*.35f, iScreenHeight * .7f);
	DrawString("Press Enter to start over", iScreenWidth*.35f, iScreenHeight*.6f);
	DrawString("Press E to go to Main Menu", iScreenWidth*.35f, iScreenHeight*.5f);
	DrawString("Press H for High Score", iScreenWidth * .35f, iScreenHeight * .4f);

	if (IsKeyDown(GLFW_KEY_ENTER))
	{
		eCurrentState = GAMEPLAY;
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