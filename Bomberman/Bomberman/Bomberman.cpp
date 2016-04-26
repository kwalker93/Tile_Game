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
         if(myKeyboard.keyDown(VK_DOWN) && myButtonCheck == true)
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
      if( checkIfQuitting() == 6 )
      {
         onDestroy();
      }
   }

}

//=======================================================================
void Game::gameExit ( )
{
}


int Game::checkIfQuitting()
{
   return MessageBox(NULL, "Are you sure you want to quit?\n", "Quit?", MB_YESNO | MB_ICONEXCLAMATION );
}


int Game::checkIfReseting()
{
   return MessageBox(NULL, "Are you sure you want to reset the map?\n", "Reset Map?", MB_YESNO | MB_ICONEXCLAMATION );
}

