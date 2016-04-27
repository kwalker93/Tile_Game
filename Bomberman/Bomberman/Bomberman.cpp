// Bomberman.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Bomberman/Bomberman.h"
#include "Bomberman/TiledBackground.h"


//=======================================================================
int APIENTRY _tWinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                        LPTSTR    lpCmdLine, int       nCmdShow)
{
   Game app;
   return app.winMain( hInstance, hPrevInstance, lpCmdLine, nCmdShow );
}

//=======================================================================
Game::Game ( )
{
}

//=======================================================================
Game::~Game ( )
{
}

//=======================================================================
bool Game::gameInit ( )
{
   bool result = true;
   myGameTitle.append("Underground Squirrel Brawl");
   winSetTitle ( myGameTitle );

   //sets Background Color
   bgColor = D3DCOLOR_XRGB( 255, 200, 250 );

   //Misc init
   //to use the assetsManager it must be initialized via the following:
   DxAssetManager::getInstance().init( "animations.txt" );
   myKeyboard.keyboardInit( hWnd() );
   myCollsionManager.init();

   //sound init
   mySoundInterface = DxSound::getInterface( DxSound::fmod );
   mySoundInterface->init( hWnd() );
   mySoundInterface->load( _T("Assets\\HamsterDance.wav"), mySound );
   mySoundInterface->loop( mySound );

   //Level init
   result &= myLevelBgnds.init( device(), _T("level_one.config") );

   //Character inits
   myUnits.gameInit( 36,36);

   //TESTING PURPOSES. COMMENT OUT WHEN NOT NEEDED
   myTurnCount = 0;
   myButtonCheck = true;

   return true;
}

//=======================================================================
void Game::gameRun ( )
{
   // pre-render
   const int minMove = 2;
   TiledBackground&  levelRef = myLevelBgnds;

   // clear the backbuffer
   device()->ColorFill( backBuffer(), NULL, bgColor );

   // Objects update...
   myLevelBgnds.update();
   myUnits.update();

   // play sound
   mySoundInterface->play( mySound );

   // start rendering

   if ( SUCCEEDED(device()->BeginScene()) )
   {
      //non-sprite rendering....

      if ( SUCCEEDED(spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
         // sprite rendering...       
         myLevelBgnds.drawMySpriteMap( spriteInterface() );

         myUnits.draw( spriteInterface() );

         int keyCount = 0;       //TODO: KLUDGE
         if(myKeyboard.keyDown(VK_DOWN) && myButtonCheck == true )
            //&& myCurrentPlayer.getSelectedUnit() != NULL )
         {
            myUnits.down();
            keyCount++;
            myButtonCheck = false;
         }
         else if(myKeyboard.keyDown(VK_LEFT)&& myButtonCheck == true)
         {
            keyCount++;
            myUnits.left();
            myButtonCheck = false;
         }
         else if(myKeyboard.keyDown(VK_RIGHT)&& myButtonCheck == true)
         {
            keyCount++;
            myUnits.right();
            myButtonCheck = false;
         }
         else if(myKeyboard.keyDown(VK_UP)&& myButtonCheck == true)
         {
            keyCount++;
            myUnits.up();
            myButtonCheck = false;
         }
         else
         {
            keyCount = 0;
            myButtonCheck = true;
         }

         // Stop all kitty motion first, then check keyboard
         if( keyCount == 0 )
         {
            myUnits.stop();
         }

         if( myCollsionManager.worldCollisions( myUnits.getSprite(), levelRef ) )
         {
            myUnits.stop();
            D3DXVECTOR3 snPos = myUnits.getLastPosition();
            myUnits.setMyPosition(snPos);
         }

         // stop rendering
         spriteInterface()->End();
      }

      // End rendering:
      device()->EndScene();
      device()->Present( NULL, NULL, NULL, NULL );
   }

   //if the escape key is pressed, destroy
   if ( DxKeyboard::keyDown( VK_ESCAPE ) )
   {
      if( controlsMessageBox() == 9) //checkIfQuitting() == 6 )
      {
         onDestroy();
      }
   }
}

//=======================================================================
void Game::gameExit ( )
{
}

//=======================================================================
int Game::checkIfQuitting()
{
   return MessageBox(NULL, "Are you sure you want to quit?\n", "Quit?", MB_YESNO | MB_ICONEXCLAMATION );
}

//=======================================================================
int Game::checkIfReseting()
{
   return MessageBox(NULL, "Are you sure you want to reset the map?\n", "Reset Map?", MB_YESNO | MB_ICONEXCLAMATION );
}

//=======================================================================
int Game::aboutMessageBox()
{
   return MessageBox(NULL, "", "About", MB_YESNO | MB_ICONEXCLAMATION );
}

//=======================================================================
int Game::controlsMessageBox()
{
   string line0 = "Winter's coming, and there's only enough acorns in the forest for one family of squirrels!\n";
   string line1 = "In Underground Squirrel Brawl, players take turns controlling their squirrels and wipe the other player's units.\n\n";

   string line2 = "How to Play: \n";

   string line3 = "1. Click on one of your squirrels to select them.\n";
   string line4 = "2. Use the arrow keys to move the selected unit on the board. Be mindful of the Info page, since each squirrel has a limited movement range.\n";
   string line5 = "3. When your selected squirrel is within attacking range of the other player's  squirrel, you can damage them.\n";
   string line6 = "4. Once a squirrel's health goes to 0, they're toast, so be careful!\n";

   string line7 = "P.S.: Oh, by the way...\n\n\n You better win quickly, or else the nearby river my engulf you with its yearly water rising!\n";
   
   
   string concatString = line0 + line1 + line2 + line3 + line4 + line5 + line6 + line7;



   return MessageBox(NULL, concatString.c_str(), "Controls", MB_OK | MB_ICONEXCLAMATION );
}



//=======================================================================
//=======================================================================
//=======================================================================
//This is just psuedo code for the Game Logic

/*
Start game---------------------

Set up the board/map----------------------------
This includes Players with Unit on the board
Units.init should be in Player.init

Always check if 10 turns has passed. If so, call waterRising()

***( Game should have a myCurrentPlayer variable )***
Start Player1's turn

Player1 selects a Unit with the Mouse cursor position
Unit is then assigned to Player1's mySelectedUnit variable

All of Player's functions involving a Unit only apply to the mySelectedUnit

Player1 can move the select Unit
Player1 can attack with selected Unit
( change attackable tiles' colors???? )

Player2's relevant Units take damage
if Unit dies, remove/turn off that Unit from the relevant Player's array

Make a check to see if any Players' Unit are all gone

It now becomes Player2's turn

***Repeat the previous steps, but now with Player2***


What we need from this logic:

Player Player1;
Player Player2;
Player myCurrentPlayer;

Player1.init();
Player2.init();

myCurrentPlayer = &Player1;
myCurrentPlayer = &Player2;



user can use mouse to click on a unit

bool belongsToPlayerOne()

check if the clicked on unit "contains" the mouse position
check if the clicked on unit belongs to the current player
if(  )
{
assign the clicked on unit to currentPlayer's mySelectedUnit
}

Unit mySelectedUnit;

Player.left()

void left()
{
mySelectedUnit.left();
}

moving function 
mySelectedUnit.left();

now that selected unit is the only one that's movable by the currentPlayer

myCurrentPlayer







*/
