#include "stdafx.h"
#include "DxFramework\DxFramework.h"
#include "Bomb.h"


//========================================================================================
//
Bomb::Bomb()
{
   myFirstTimeFlag = true;
   myBombExploding = false;
   myIsBombSet = false;
   myBombState = UNSET;
	myPosition.x = myPosition.y = myPosition.z = 0;
	myLastPosition.x = myLastPosition.y = myLastPosition.z = 0;
}
//========================================================================================
//
Bomb::~Bomb()
{ 
   
}
//========================================================================================
//
bool Bomb::init( IDXDEVICE device, int xPos, int yPos )
{
   mySoundInterface = DxSound::getInterface( DxSound::fmod );
   mySoundInterface->load( _T("Assets\\Explosion.wav"), mySound );

   loadCharacterAnimations();
   myExplosions.resize( 4 );
   bool result = mySprite.create( "BBOMB-STATIC" );
   mySprite.setScale( 0.2f, 0.2f );
   myPosition.x = float(xPos);
   myPosition.y = float(yPos);

   mySprite.setPosition( myPosition.x, myPosition.y );
   
   for( int i = 0; i < 4; i++)
   {
      bool result = myExplosions[i].create( "BBOMB-EXPOLSION" );
      myExplosions[i].setScale( 0.2f, 0.2f );
      assert(result);
   }

   assert(result);
   
   return result;
}
//========================================================================================
//updates the sprites and timer that changes the state of the bomb depending on the timer
void Bomb::update()
{

   mySprite.update();

   if( myIsBombSet )
   {   
      if( !myTimer.isRunning() )
      {
         myTimer.start();   
      }

      int time = ( int( myTimer.elapsedTime() ) / 1000 );

      switch ( time )
      {
      case  1:
         selectAnimation( SET );
         break;
      case  3:
         selectAnimation( LIGHT );
         break;
      case  6:
         selectAnimation( FLASH );
         break;
      case  9:
         selectAnimation( EXPLODE );
         myBombExploding = true;
         //TODO: explosion continues to loop with fmod
         //mySoundInterface->play( mySound );
         break;
      case  11:
         //mySoundInterface->stop( mySound );
         myTimer.stop();
         myIsBombSet = false;
         myBombExploding = false;
         selectAnimation( UNSET );
         break;
      }
      for( int i = 0; i < 4; i++)
      {
         myExplosions[i].update();
      }
   }
}
//========================================================================================
//
void Bomb::shutdown()
{

}
//========================================================================================
// loads the animations for the bomb
bool Bomb::loadCharacterAnimations()
{
   if( myFirstTimeFlag )
   {
      float bmbFSpeed = 10.0;
      float expFSpeed = 4.5;
      myFirstTimeFlag = false;
      myBombSetBmAnim = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-STATIC", bmbFSpeed, D3DCOLOR_XRGB( 170, 181, 129 ) ); 
      myBombLightAnim = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-LIGHT", bmbFSpeed, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myBombFlashAnim = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-FLASH", bmbFSpeed, D3DCOLOR_XRGB( 170, 181, 129 ) );

      myBombExplCentAnime = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-EXPLCENTER", expFSpeed, D3DCOLOR_XRGB( 170, 181, 129 ) );            
      myBombExplUpAnime = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-EXPLUP", expFSpeed, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myBombExplDownAnime = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-EXPLDOWN", expFSpeed, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myBombExplLeftAnime = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-EXPLLEFT", expFSpeed, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myBombExplRightAnime = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-EXPLRIGHT", expFSpeed, D3DCOLOR_XRGB( 170, 181, 129 ) ); 

   }

   return true;
}
//========================================================================================
// Draws a bomb if the bomb has been set also draws the four other bomb sprites when it explodes 
bool Bomb::draw ( IDXSPRITE spriteObj )
{  
   if( myIsBombSet )
   {
      mySprite.draw( spriteObj );
  
      if( myBombState == EXPLODE )
      {
          for( int i = 0; i < 4; i++)
         {
            myExplosions[i].draw( spriteObj );
         }
      }
   }
   return true;
}
//========================================================================================
// used to place the bomb and only allow you to sets a bomb if a bomb had not already been set
// also sets the position for the bomb to be placed and it four points of explosions only four so far
void Bomb::place( D3DXVECTOR3& position, float kittyWidth, float kittyHeight )
{
   if( !myIsBombSet )
   {       
      myPosition = position;
      myPosition.x = ( (int)( myPosition.x + kittyWidth/2 ) - ( (int)( myPosition.x + kittyWidth/2 ) % 32) ) + 3;
      myPosition.y = ( (int)( myPosition.y + kittyHeight/2 ) - ( (int)( myPosition.y + kittyHeight/2 ) % 32) ) + 3;

      mySprite.setPosition( myPosition.x, myPosition.y );
      myIsBombSet = true;
   }
}
//========================================================================================
// Changes the state and animation of the bamb Based on the timer 
bool Bomb::selectAnimation( BombState state )
{
   if( state != myBombState )
   {

      switch ( state )
      {
      case SET:
         mySprite.changeAnimation( myBombSetBmAnim );
         myBombState = SET;
         break;
      case LIGHT:
         mySprite.changeAnimation( myBombLightAnim );
         myBombState = LIGHT;
         break;
      case FLASH:
         mySprite.changeAnimation( myBombFlashAnim );
         myBombState = FLASH;
         break;
      case EXPLODE:
         mySprite.changeAnimation( myBombExplCentAnime );
         explode();
         myBombState = EXPLODE;
         break;
      default:
         myBombState = UNSET;
         mySprite.changeAnimation( myBombSetBmAnim );
         break;

      }
   }

   return true;
}
//========================================================================================
//
bool Bomb::explode()
{
   myExplosions[0].setPosition( myPosition.x, myPosition.y + (float)mySprite.getWidth() );
   myExplosions[1].setPosition( myPosition.x, myPosition.y - (float)mySprite.getWidth() );
   myExplosions[2].setPosition( myPosition.x + (float)mySprite.getHeight(), myPosition.y );
   myExplosions[3].setPosition( myPosition.x - (float)mySprite.getHeight(), myPosition.y );

   //for( int i = 0; i < 4; i++)
   //{
      myExplosions[0].changeAnimation( myBombExplDownAnime );
      myExplosions[1].changeAnimation( myBombExplUpAnime );
      myExplosions[2].changeAnimation( myBombExplRightAnime );
      myExplosions[3].changeAnimation( myBombExplLeftAnime );

   //}

   return true;
}
