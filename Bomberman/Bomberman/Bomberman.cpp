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
   
   myGameTitle.append("BomberCat");
   winSetTitle ( myGameTitle );
   bool result = true;


   //to use the assetsManager it must be initialized via the following:
   DxAssetManager::getInstance().init( "animations.txt" );

   myBgRect = Rect( 0, 0, winScreenWidth(), winScreenHeight() );

   bgColor = D3DCOLOR_XRGB( 0, 0, 100 );

   result &= myLevelBgnds[0].init( device(), _T("level_one.config") );

   myKitty.init( );   
   myKitty.create( device(), 32, 32 );
   myBomb.init( device() );
   otherKitty.init( );
   otherKitty.create( device(), 200, 200 );

   myKeyboard.keyboardInit( hWnd() );


   // init sound
   mySoundInterface = DxSound::getInterface( DxSound::directSound );
   mySoundInterface->init( hWnd() );
   mySoundInterface->load( _T( "Assets\\HamsterDance.wav" ), mySound );
   mySoundInterface->loop( mySound );

   return true;
}

//=======================================================================
void Game::gameRun ( )
{
   // pre-render
   const int minMove = 2;

   // clear the backbuffer
   device()->ColorFill( backBuffer(), NULL, bgColor );

   // Objects update...
   myLevelBgnds[0].update();
   myKitty.update();
   otherKitty.update();
   myBomb.update();

   // play sound
   //mySoundInterface->play( mySound );

   // start rendering

   if ( SUCCEEDED(device()->BeginScene()) )
   {
      //non-sprite rendering....
     //myLevelBgnds[0].draw( backBuffer(), &myBgRect );


      if ( SUCCEEDED(spriteInterface()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
         // sprite rendering...
         
         //myLevelBgnds[0].draw( spriteInterface(), &myBgRect );
         myLevelBgnds[0].drawMySpriteMap( spriteInterface() );

         myBomb.draw( spriteInterface() );       
         myKitty.draw( spriteInterface() );
        //otherKitty.draw( spriteInterface() );
         


         int keyCount = 0;       //TODO: KLUDGE
	      if(myKeyboard.keyPressed(VK_DOWN))
	      {
            myKitty.goDown();
            //myKitty.collision( myKitty.getSprite(), otherKitty.getSprite() );
            keyCount++;
         }
         else if(myKeyboard.keyPressed(VK_LEFT))
	      {
            keyCount++;
            myKitty.goLeft();
            //myKitty.collision( myKitty.getSprite(), otherKitty.getSprite() );
         }
         else if(myKeyboard.keyPressed(VK_RIGHT))
	      {
            keyCount++;
            myKitty.goRight();
            //myKitty.collision( myKitty.getSprite(), otherKitty.getSprite() );
         }
         else if(myKeyboard.keyPressed(VK_UP))
	      {
            keyCount++;
            myKitty.goUp();
            //myKitty.collision( myKitty.getSprite(), otherKitty.getSprite() );
         }

         // Stop all kitty motion first, then check keyboard
         if( keyCount == 0 )
            myKitty.goStop();


         // Separate keyboard checks so MULTIPLE KEYS can be tested...
         if( myKeyboard.keyPressed(VK_SPACE))
         {
            myBomb.place( int(myKitty.getMyPosition().x), int(myKitty.getMyPosition().y) );
         }
         else
         {
         }


         //TODO:KLUGDE
         //collisions not rally how theres supposed to work but hey it's a start
         
         int indexTopLeft = ( (int)myKitty.getMyPosition().x / 32 ) + 
                            ( (int)myKitty.getMyPosition().y / 32 ) * myLevelBgnds[0].numColumns();
         int indexBottomRight = ( (int)( myKitty.getMyPosition().x + myKitty.getSprite().getWidth() ) / 32 ) + 
                                ( (int)( myKitty.getMyPosition().y + + myKitty.getSprite().getHeight() ) / 32 ) * 
                                myLevelBgnds[0].numColumns();

         if(  ( myKitty.collidesWith( myLevelBgnds[0].mySpriteMap[indexTopLeft] ) &&  
                myLevelBgnds[0].mySpriteMap[indexTopLeft].collidable() ) ||
              ( myKitty.collidesWith( myLevelBgnds[0].mySpriteMap[indexBottomRight] ) &&  
                myLevelBgnds[0].mySpriteMap[indexBottomRight].collidable() ) )
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

}

//=======================================================================
void Game::gameExit ( )
{
}


