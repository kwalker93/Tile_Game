#include "stdafx.h"

#include "Utilities/Point.h"
#include "Utilities/Rect.h"
#include "DxFramework/DxFramework.h"
#include "Bomberman/Kitty.h"

//Check on device
//=======================================================================
//
Kitty::Kitty ( )
{
   myFirstTimeFlag = true;
   myDirection = STILLDOWN;
   mySpeed = 0.0F;
	myPosition.x = myPosition.y = myPosition.z = 0;
	myLastPosition.x = myLastPosition.y = myLastPosition.z = 0;

}
//=======================================================================
//
Kitty::~Kitty ( )
{

}
//=======================================================================
//
bool Kitty::init( IDXDEVICE device, int xPos, int yPos )
{
   myDirection = STILLDOWN;
   loadCharacterAnimations();
   mySprite.setScale( .25f, .25f );
   mySoundInterface = DxSound::getInterface( DxSound::fmod );
   mySoundInterface->load( _T("Assets\\Cat_Steps.mp3"), mySound );
   mySoundInterface->load( _T("Assets\\Cat_Death.mp3"), myDeath );
   
   bool result = mySprite.create( "BCAT-STILL" );

   mySprite.setPosition( float(xPos), float(yPos) );
   myPosition.x = mySprite.getXPosition();
   myPosition.y = mySprite.getYPosition();

   mySpeed = 1.3f;

   assert(result);
   
   return true;
}
//=======================================================================
//
void Kitty::update()
{
   myLastPosition.x = myPosition.x;
   myLastPosition.y = myPosition.y;
   mySprite.update();
   myPosition.x = mySprite.getXPosition();
   myPosition.y = mySprite.getYPosition();
   mySoundInterface->update();

}
//=======================================================================
//
bool Kitty::draw ( IDXSPRITE spriteObj )
{ 
   mySprite.draw( spriteObj );

   return true;
}
//=======================================================================
//
bool Kitty::loadCharacterAnimations ()
{
   if( myFirstTimeFlag )
   {
      myFirstTimeFlag = false;
      myCatStillAnim = DxAssetManager::getInstance().getAnimationCopy( "BCAT-STILL", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );

      myCatWalkDownAnim = DxAssetManager::getInstance().getAnimationCopy( "BCAT-DOWN", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myCatWalkLeftAnim = DxAssetManager::getInstance().getAnimationCopy( "BCAT-LEFT", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myCatWalkRightAnim = DxAssetManager::getInstance().getAnimationCopy( "BCAT-RIGHT", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myCatWalkUpAnim = DxAssetManager::getInstance().getAnimationCopy( "BCAT-UP", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      
      myCatStillDownAnim = DxAssetManager::getInstance().getAnimationCopy( "BCAT-STILLDOWN", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myCatStillLeftAnim = DxAssetManager::getInstance().getAnimationCopy( "BCAT-STILLLEFT", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myCatStillRightAnim = DxAssetManager::getInstance().getAnimationCopy( "BCAT-STILLRIGHT", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myCatStillUpAnim = DxAssetManager::getInstance().getAnimationCopy( "BCAT-STILLUP", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      
      myCatBlowUpAnim = DxAssetManager::getInstance().getAnimationCopy( "BCAT-BLOWUP", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );   
   }
   return true;
}
//=======================================================================
// TURNS OFF ALL KITTY DIRECTIONAL MOTION!!!@
bool Kitty::goStop ( )
{
   Direction prevDirection = myDirection;

   // Stop actual sprite motion.
   mySprite.setXVel(0.0f);
   mySprite.setYVel(0.0f);

   // Set next state based on Current state.
   switch ( myDirection )
   {
   case Direction::UP:
   case Direction::STILLUP:
      myDirection = Direction::STILLUP;
      break;
   case Direction::DOWN:
   case Direction::STILLDOWN:
      myDirection = Direction::STILLDOWN;
      break;
   case Direction::LEFT:
   case Direction::STILLLEFT:
      myDirection = Direction::STILLLEFT;
      break;
   case Direction::RIGHT:
   case Direction::STILLRIGHT:
      myDirection = Direction::STILLRIGHT;
      break;
   default:
      myDirection = Direction::STILL;
      break;
   }


   if ( prevDirection != myDirection )
        stillDirection( prevDirection );

   return true;
}
//=======================================================================
//TODO: Consider actual motion...
//  If current move state == up, nothing to do.
// otherwise....
//    kitty state == UP : Immediate change
   // if kitty is ANY OTHER STILL, change to STILLUP state
//    ??? Change from any to STILL UP on first keypress????
//    if kitty is ANY STILL or STILLUP, change to UP state.
//For Kitty walking
//    Added sound->play and sound->stop to all go methods works good/ok.
//    When kitty collides with a wall she moves then stops making the sound
//    play and stop within frames
bool Kitty::goUp ( )
{
   mySoundInterface->play( mySound ); 
   Direction temp = myDirection;
   myDirection = Direction::UP;
   mySprite.setXVel( mySpeed - mySpeed );
   mySprite.setYVel(-mySpeed);
   //mySprite.changeAnimation( "BCAT-UP" );

   if(myDirection != temp)
      mySprite.changeAnimation( myCatWalkUpAnim );

   return true;
}
//=======================================================================
//
bool Kitty::goDown ( )
{
   mySoundInterface->play( mySound ); 
   Direction temp = myDirection;
   myDirection = Direction::DOWN;
   mySprite.setXVel(mySpeed - mySpeed);
   mySprite.setYVel(+mySpeed);   //TODO :  Constant somewhere for kitty speed
   //mySprite.changeAnimation( "BCAT-UP" );
   if(myDirection != temp)
      mySprite.changeAnimation( myCatWalkDownAnim );

   return true;
}
//=======================================================================
//
bool Kitty::goLeft()
{
   mySoundInterface->play( mySound ); 
   Direction temp = myDirection;
   myDirection = Direction::LEFT;
   mySprite.setXVel(-mySpeed);
   mySprite.setYVel(mySpeed - mySpeed);
   //mySprite.changeAnimation( "BCAT-UP" );
   if(myDirection != temp)
      mySprite.changeAnimation( myCatWalkLeftAnim );

   return true;
}
//=======================================================================
//
bool Kitty::goRight()
{
   mySoundInterface->play( mySound ); 
   Direction temp = myDirection;
   myDirection = Direction::RIGHT;
   mySprite.setXVel(+mySpeed);
   mySprite.setYVel( mySpeed - mySpeed ); //TODO :  Constant somewhere for kitty speed
   if(myDirection != temp)
      mySprite.changeAnimation( myCatWalkRightAnim );

   return true;
}
//=======================================================================
//
bool Kitty::goReverse()
{
   mySprite.setXVel( -mySprite.getXVel() );
   mySprite.setYVel( -mySprite.getYVel() );
   return true;
}

//=======================================================================
//
bool Kitty::goStillUp()
{
   mySoundInterface->stop( mySound );
   mySprite.changeAnimation( myCatStillUpAnim );
   return true;
}

//=======================================================================
//
bool Kitty::goStillDown()
{
   mySoundInterface->stop( mySound );
   mySprite.changeAnimation( myCatStillDownAnim );
   return true;
}

//=======================================================================
//
bool Kitty::goStillLeft()
{
   mySoundInterface->stop( mySound );
   mySprite.changeAnimation( myCatStillLeftAnim );
   return true;
}

//=======================================================================
//
bool Kitty::goStillRight()
{
   mySoundInterface->stop( mySound );
   mySprite.changeAnimation( myCatStillRightAnim );
   return true;
}
//=======================================================================
//Test Method
void Kitty::die()
{
    mySoundInterface->play( myDeath );
    mySprite.changeAnimation( myCatBlowUpAnim );
}

//=======================================================================
//
bool Kitty::stillDirection( Direction prevDirection )
{
   switch( prevDirection )
   {
      case UP:
         myDirection = STILLUP;
         goStillUp();
         break;
      case DOWN:
         myDirection = STILLDOWN;
         goStillDown();
         break;
      case LEFT:
         myDirection = STILLLEFT;
         goStillLeft();
         break;
      case RIGHT:
         myDirection = STILLRIGHT;
         goStillRight();
         break;
      default:
         myDirection = STILL;
         assert( false );
         break;
   }
   return true;
}
