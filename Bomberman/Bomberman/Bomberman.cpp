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
   myGameTitle.append("BomberCat");
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
   //myBgRect = Rect( 0, 0, winScreenWidth(), winScreenHeight() );

   //Character inits
   // myKitty.init( device(), 36, 36 );   
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
   //myKitty.update();
   myUnits.update();

   // play sound
   mySoundInterface->play( mySound );

   // start rendering

   if ( SUCCEEDED(device()->BeginScene()) )
   {
      //non-sprite rendering....
      //myLevelBgnds[0].draw( backBuffer(), &myBgRect );


      if ( SUCCEEDED(spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
         // sprite rendering...       
         myLevelBgnds.drawMySpriteMap( spriteInterface() );

         //myKitty.draw( spriteInterface() );
         myUnits.draw( spriteInterface() );


         int keyCount = 0;       //TODO: KLUDGE
         if(myKeyboard.keyDown(VK_DOWN) && myButtonCheck == true)
         {
            //myKitty.goDown();
            myUnits.down();
            keyCount++;
            myButtonCheck = false;
         }
         else if(myKeyboard.keyDown(VK_LEFT)&& myButtonCheck == true)
         {
            keyCount++;
            // myKitty.goLeft();
            myUnits.left();
            myButtonCheck = false;
         }
         else if(myKeyboard.keyDown(VK_RIGHT)&& myButtonCheck == true)
         {
            keyCount++;
            // myKitty.goRight();
            myUnits.right();
            myButtonCheck = false;
         }
         else if(myKeyboard.keyDown(VK_UP)&& myButtonCheck == true)
         {
            keyCount++;
            //myKitty.goUp();
            myUnits.up();
            myButtonCheck = false;
         }
         else
         {
            keyCount = 0;
            myButtonCheck = true;
         }

         //test Code for waterRising()
         if( myKeyboard.keyPressed( VK_SPACE) )
         {
            levelRef.waterRising( myTurnCount );
            myTurnCount++;

         }

         // Stop all kitty motion first, then check keyboard
         if( keyCount == 0 )
         {
            // myKitty.goStop();
            myUnits.stop();
         }



         if( myCollsionManager.worldCollisions( myUnits.getSprite(), levelRef ) )
         {
            // myKitty.goStop();
            myUnits.stop();
            // D3DXVECTOR3 snPos = myKitty.getLastPosition();
            D3DXVECTOR3 snPos = myUnits.getLastPosition();
            // myKitty.setMyPosition( snPos );
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
      onDestroy();
   }

}

//=======================================================================
void Game::gameExit ( )
{
}


