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
   {
      myManager.playerOnePtr->resetUnits();
      myManager.playerTwoPtr->resetUnits();
      gameInit();
   }

   return false;
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
   myGameUI.update();
   myManager.update();
   myMouse.mouseUpdate();

   // start rendering

   if ( SUCCEEDED(device()->BeginScene()) )
   {
      //non-sprite rendering....

      if ( SUCCEEDED(spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {  

         myGameUI.setCurrentUnit( myManager.currentlyActingPlayer->getSelectedUnit() );
         myGameUI.setTurnCounter( myTurnCount );

         // sprite rendering...       
         myLevelBgnds.drawMySpriteMap( spriteInterface() );

         myManager.draw( spriteInterface() );
         myGameUI.draw( spriteInterface() );

         myPlayer1.checkWaterCollisions( myCollisionManager, levelRef );
         myPlayer2.checkWaterCollisions( myCollisionManager, levelRef );

         if( myCollisionManager.worldCollisions( myManager.currentlyActingPlayer->getSelectedUnit().getSprite(), levelRef ) )
         {
            myManager.currentlyActingPlayer->stopAllUnits();
            myManager.currentlyActingPlayer->singleUnitCollision();
         }

         if( myManager.currentlyActingPlayer->isAttacking == false )
         {
            if(myMouse.mouseButton(0))
            {
               myManager.currentlyActingPlayer->unitClick( myMouse.getPoint() );
            }

            int keyCount = 0;       

            if(myKeyboard.keyDown(VK_DOWN))
            {
               myManager.currentlyActingPlayer->down();
               keyCount++;

            }
            else if(myKeyboard.keyDown(VK_LEFT))
            {
               keyCount++;
               myManager.currentlyActingPlayer->left();

            }
            else if(myKeyboard.keyDown(VK_RIGHT))
            {
               keyCount++;
               myManager.currentlyActingPlayer->right();

            }
            else if(myKeyboard.keyDown(VK_UP))
            {
               keyCount++;
               myManager.currentlyActingPlayer->up();
            }
            else
            {
               keyCount = 0;
            }

            // Stop all motion first, then check keyboard
            if( keyCount == 0 )
            {
               myManager.currentlyActingPlayer->stopAllUnits();
            }

            if(myKeyboard.keyDown(VK_RETURN))
            {
               myManager.getCurrentActivePlayer().toggleAttackState();
               myManager.getCurrentActivePlayer().resetUnitMoves( );
            }
         }
         else if ( myManager.currentlyActingPlayer->isAttacking == true)
         {
            if(myKeyboard.keyDown(VK_DOWN))
            {
               myManager.currentlyActingPlayer->setAttackCursorDown();
            }
            else if(myKeyboard.keyDown(VK_LEFT))
            {
               myManager.currentlyActingPlayer->setAttackCursorLeft();
            }
            else if(myKeyboard.keyDown(VK_RIGHT))
            {
               myManager.currentlyActingPlayer->setAttackCursorRight();
            }
            else if(myKeyboard.keyDown(VK_UP))
            {
               myManager.currentlyActingPlayer->setAttackCursorUp();
            }

            if( myKeyboard.keyPressed(VK_SHIFT) )
            {
               Unit& pUnit = myManager.getCurrentInactivePlayer().findUnitReceivingDamage(myManager.currentlyActingPlayer->myAttackCursor);
               if ( pUnit.getHealth() > 0 )
               {
                  pUnit.takingDamage(myManager.currentlyActingPlayer->mySelectedUnit.getDamage());
               }

               myManager.getCurrentActivePlayer().toggleAttackState();
               myManager.getCurrentActivePlayer().resetUnitMoves();
               myManager.endCurrentTurn();
  
               if ( myManager.getNumElapsedTurns() % 2 == 0 )
               {
                  myTurnCount++;
               }
               else
               {
                  myTurnCount = myManager.getNumElapsedTurns() / 2;
               }

               myLevelBgnds.waterRising( myTurnCount );
               
            }

         }

         // stop rendering
         spriteInterface()->End();
      }

      // End rendering:
      device()->EndScene();
      device()->Present( NULL, NULL, NULL, NULL );
   }

   checkForNewGame();

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


