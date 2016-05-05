// Bomberman.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Bomberman/Bomberman.h"
#include "Bomberman/TiledBackground.h"
#include "WinApplFramework/GameMessages.h"


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
   if ( GameMessages::startNewGame )
   {
      GameMessages::startNewGame = false;
      myGameTitle = _T("");
   }

   bool result = true;
   myGameTitle.append("Underground Squirrel Brawl");
   winSetTitle ( myGameTitle );

   //sets Background Color
   bgColor = D3DCOLOR_XRGB( 255, 200, 250 );

   //Misc init
   //to use the assetsManager it must be initialized via the following:
   DxAssetManager::getInstance().init( "animations.txt" );
   myKeyboard.keyboardInit( hWnd() );
   myMouse.mouseInit( hWnd(), device() );
   myCollisionManager.init();

   //sound init

   mySoundInterface = DxSound::getInterface( DxSound::fmod );
   mySoundInterface->init( hWnd() );
   mySoundInterface->load( _T("Assets\\HamsterDance.wav"), mySound );
   mySoundInterface->loop( mySound );


   //Level init
   result &= myLevelBgnds.init( device(), _T("level_one.config") );

   //Game UI init
   myTurnCount = 1;
   myGameUI.init( fontInterface(), 732, 32, D3DCOLOR_XRGB( 0, 0, 0 ), myTurnCount );

   //Character inits
   // myUnits.init( "ACORN-BROWN", 64,64);
   // myUnits2.gameInit( 68, 36);

   //TESTING PURPOSES. COMMENT OUT WHEN NOT NEEDED
   myTurnCount = 1;
   myButtonCheck = true;

   //Creates out two custom players, and passes them to the player manager
   myPlayer1.init(true, 256, 64, Unit::mediumGrey );
   myPlayer2.init(false, 256, 512, Unit::mediumBrown );
   myManager.init(true, &myPlayer1, &myPlayer2);

   return true;
}

//=======================================================================
bool Game::checkForNewGame()
{
   if( GameMessages::startNewGame )
      gameInit();
   return false;
}

//=======================================================================
void Game::gameRun ( )
{
   // check if the player is done with their turn.
   if ( myKeyboard.keyDown(VK_RETURN) ) 
   {
      myManager.endCurrentTurn();
   }

   checkForNewGame();

   // pre-render
   const int minMove = 2;
   TiledBackground&  levelRef = myLevelBgnds;

   // clear the backbuffer
   device()->ColorFill( backBuffer(), NULL, bgColor );

   // Objects update...
   myLevelBgnds.update();
   myGameUI.update();
   myManager.update();
   myMouse.mouseUpdate();

   // start rendering

   if ( SUCCEEDED(device()->BeginScene()) )
   {
      //non-sprite rendering....

      if ( SUCCEEDED(spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {  
         if(myMouse.mouseButton(0))
         {
            myPlayer1.unitClick( myMouse.getPoint() );
         }

         myGameUI.setCurrentUnit( myPlayer1.getSelectedUnit() );
         myGameUI.setTurnCounter( myTurnCount );

         // sprite rendering...       
         myLevelBgnds.drawMySpriteMap( spriteInterface() );
         
         myManager.draw( spriteInterface() );
         myGameUI.draw( spriteInterface() );

         int keyCount = 0;       

         if(myKeyboard.keyDown(VK_DOWN))
         {
            myPlayer1.down();
            keyCount++;

         }
         else if(myKeyboard.keyDown(VK_LEFT))
         {
            keyCount++;
            myPlayer1.left();

         }
         else if(myKeyboard.keyDown(VK_RIGHT))
         {
            keyCount++;
            myPlayer1.right();

         }
         else if(myKeyboard.keyDown(VK_UP))
         {
            keyCount++;
            myPlayer1.up();

         }
         else
         {
            keyCount = 0;
         }

         //TESTING IF
         if(myKeyboard.keyPressed(VK_SHIFT))
         {
            myLevelBgnds.waterRising( myTurnCount );
            myTurnCount++;
         }

         // Stop all motion first, then check keyboard
         if( keyCount == 0 )
         {
            myPlayer1.stopAllUnits();
         }
 
         myPlayer1.checkWaterCollisions( myCollisionManager, levelRef );
         myPlayer2.checkWaterCollisions( myCollisionManager, levelRef );

         if( myCollisionManager.worldCollisions( myPlayer1.getSelectedUnit().getSprite(), levelRef ) )
         {
            myPlayer1.stopAllUnits();
            myPlayer1.singleUnitCollision();
         }

         if ( myManager.currentlyActingPlayer->isAttacking )
         {
            if( myKeyboard.keyPressed(VK_RETURN) )
            {
               Unit& pUnit = myManager.currentlyActingPlayer->findUnitReceivingDamage(myManager.currentlyActingPlayer->myAttackCursor);
               if ( myManager.currentlyActingPlayer->mySelectedUnit )
               {
                  pUnit.takingDamage(myManager.currentlyActingPlayer->mySelectedUnit.getDamage());
               }

               myManager.currentlyActingPlayer->isAttacking = false;
            }
            
         }

         //make attacking collision check
         //have a receiving unit and a giving unit stored/passed
         //have rUnit take damage from gUnit
         //endTurn or switch active player

         /*                                      make currentPlayer variable               make inactivePlayer variable
         if( myCollisionManager.attackCollisions( myPlayer1.getSelectedUnit().getSprite(), levelRef ) )
         {

         }
         */
         

         //for(int i = 0; i < 4; i++)
         //{
         //   if( myCollisionManager.spriteCollsions( myPlayer1.getSelectedUnit().getSprite(), myPlayer1.getArrayUnits().at(i).getSprite() ) )
         //   {
         //      myPlayer1.stopAllUnits();
         //      myPlayer1.unitCollision();
         //   }
         //}

         



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
      onDestroy();
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
