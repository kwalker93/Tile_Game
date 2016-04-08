#include "stdafx.h"
#include "DxFramework\DxFramework.h"
#include "Bomb.h"


//========================================================================================
//
Bomb::Bomb()
{
   myFirstTimeFlag = true;
   myIsBombSet = false;
   myBombState = UNSET;
	myPosition.x = myPosition.y = myPosition.z = 0;
	myLastPosition.x = myLastPosition.y = myLastPosition.z = 0;
}
//========================================================================================
//
Bomb::~Bomb(){}
//========================================================================================
//
bool Bomb::init( IDXDEVICE device )
{
   loadCharacterAnimations();
   bool result = mySprite.create( "BBOMB-STATIC" );
   mySprite.setScale( 0.2f, 0.2f );

   assert(result);
   
   return result;
}
//========================================================================================
//
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
        myTimer.stop();
        myIsBombSet = false;
        selectAnimation( UNSET );
        break;
     default:
        //selectAnimation( SET );
        break;
     }
     //}
     //if( myTimer.isRunning() && time == 1 )
     //{
     //   selectAnimation( SET );
     //}     
     //if( myTimer.isRunning() && time == 5 )
     //{
     //   selectAnimation( LIGHT );
     //}
     //  
     //if( myTimer.isRunning() && time == 10 )
     //{
     //   selectAnimation( FLASH );
     //}

     //if( myTimer.isRunning() && time >= 15 )
     //{
     //   myTimer.stop();
     //   myIsBombSet = false;
     //   selectAnimation( UNSET );
     //}
  }

}
//========================================================================================
//
void Bomb::shutdown()
{

}
//========================================================================================
//
bool Bomb::loadCharacterAnimations()
{
   if( myFirstTimeFlag )
   {
      myFirstTimeFlag = false;
      myBombSetAnim = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-STATIC", 10, D3DCOLOR_XRGB( 170, 181, 129 ) ); 
      myBombLightAnim = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-START", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myBombFlashAnim = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-MID", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myBombWickAnime = DxAssetManager::getInstance().getAnimationCopy( "BBOMB-WICK", 10, D3DCOLOR_XRGB( 170, 181, 129 ) ); 
      //myBombExplodeAnim.init( DxFramework::device(), "BBOMB-EXPLODE", 10, D3DCOLOR_XRGB( 170, 181, 129 ) ); //not Added to animation.txt yet
   }

   return true;
}
//========================================================================================
//
void Bomb::place( int xPos, int yPos )
{
  if( !myIsBombSet )
  { 
     mySprite.setPosition( float(xPos), float(yPos) );
     myIsBombSet = true;
  }
}
//========================================================================================
//
bool Bomb::draw ( IDXSPRITE spriteObj )
{  
   if( myIsBombSet )
   {
      mySprite.draw( spriteObj );

   }

   return true;
}
//========================================================================================
//
bool Bomb::selectAnimation( BombState state )
{
   if( state != myBombState )
   {

      switch ( state )
      {
      case SET:
         mySprite.changeAnimation( myBombSetAnim );
         myBombState = SET;
         break;
      case LIGHT:
         mySprite.changeAnimation( myBombLightAnim );
         myBombState = LIGHT;
         break;
      case FLASH:
         mySprite.changeAnimation( myBombWickAnime );
         myBombState = FLASH;
         break;
      case EXPLODE:
         //mySprite.changeAnimation( myBombExplodeAnim );
         myBombState = EXPLODE;
         break;
      default:
         myBombState = UNSET;
         mySprite.changeAnimation( myBombSetAnim );
         break;

      }
   }

   return true;
}
