#include "AIE.h"
#include <iostream>

int main( int argc, char* argv[] )
{	
    Initialise(800, 600, false, "My Awesome Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

    int myTextureHandle = CreateSprite("./images/crate_sideup.png", 64, 64, true);
    float xPos = 100;
    float yPos = 100;

    //Game Loop
    do
    {
        MoveSprite(myTextureHandle, xPos, yPos);
        DrawSprite(myTextureHandle);

        ClearScreen();

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
