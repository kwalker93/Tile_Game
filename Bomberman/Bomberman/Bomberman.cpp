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


        /* int keyCount = 0;       //TODO: KLUDGE
	      if(myKeyboard.keyPressed(VK_DOWN))
	      {
            myKitty.goDown();
            keyCount++;
         }
         else if(myKeyboard.keyPressed(VK_LEFT))
	      {
            keyCount++;
            myKitty.goLeft();
         }
         else if(myKeyboard.keyPressed(VK_RIGHT))
	      {
            keyCount++;
            myKitty.goRight();
         }
         else if(myKeyboard.keyPressed(VK_UP))
	      {
            keyCount++;
            myKitty.goUp();
                     }
  


         if( myKeyboard.keyPressed( VK_SPACE) )
         {
            levelRef.waterRising( myTurnCount );
            myTurnCount++;
         }

         // Stop all kitty motion first, then check keyboard
         if( keyCount == 0 )
            myKitty.goStop();*/


         if( myCollsionManager.worldCollisions( myKitty.getSprite(), levelRef ) )
         {
            myKitty.goStop();
            D3DXVECTOR3 snPos = myKitty.getLastPosition();
            myKitty.setMyPosition( snPos );
         }


            





         // stop rendering
	      spriteInterface()->End();
      }

      // End rendering:
      device()->EndScene();
      device()->Present( NULL, NULL, NULL, NULL );
   }
   
   //if the escape key is pressed, destroy
   if ( DxKeyboard::keyPressed( VK_ESCAPE ) )
	   {
		   onDestroy();
	   }

}

//=======================================================================
void Game::gameExit ( )
{
}


