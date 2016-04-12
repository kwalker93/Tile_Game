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
   myKitty.init( device(), 36, 36 );   
   myBomb.init( device(), int(myKitty.getMyPosition().x), int(myKitty.getMyPosition().y) );
   myEnemy.init( device(), 132, 100, 3);

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
   myKitty.update();
   myEnemy.update();
   myBomb.update();

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

         myBomb.draw( spriteInterface() );       
         myKitty.draw( spriteInterface() );
         myEnemy.draw( spriteInterface() );
         


         int keyCount = 0;       //TODO: KLUDGE
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

         // Stop all kitty motion first, then check keyboard
         if( keyCount == 0 )
            myKitty.goStop();


         // Separate keyboard checks so MULTIPLE KEYS can be tested...
         if( myKeyboard.keyPressed(VK_SPACE))
         {
            myBomb.place( myKitty.getMyPosition(), myKitty.getSprite().getWidth(), myKitty.getSprite().getHeight() );
         }


         if( myCollsionManager.worldCollisions( myEnemy.getSprite(), levelRef ) )
         {
            myEnemy.Stop();          
            D3DXVECTOR3 snEPos = myEnemy.getLastPosition();
            myEnemy.setMyPosition( snEPos );
            myEnemy.changeDirection();
         }  

         if( myCollsionManager.worldCollisions( myKitty.getSprite(), levelRef ) )
         {
            myKitty.goStop();
            D3DXVECTOR3 snPos = myKitty.getLastPosition();
            myKitty.setMyPosition( snPos );
         }

         if( myBomb.getIsExploding() )
         {
            for( int i = 0; i < 4; i++)
            {
               myCollsionManager.exploisionCollisions( myBomb.getSprite(i), levelRef );
            }
         }

         //not working correctly collision area too big
         /*if( myCollsionManager.spriteCollsions( myKitty.getSprite(), myEnemy.getSprite() ) )
         {
            myKitty.goStop();
            D3DXVECTOR3 snPos = myKitty.getLastPosition();
            myKitty.setMyPosition( snPos );

            myEnemy.goStop();          
            D3DXVECTOR3 snEPos = myEnemy.getLastPosition();
            myEnemy.setMyPosition( snEPos );
            myEnemy.changeDirection();
         } */        





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


