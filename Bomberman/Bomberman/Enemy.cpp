#include "stdafx.h"

#include "Utilities/Point.h"
#include "Utilities/Rect.h"
#include "DxFramework/DxFramework.h"
#include "Bomberman/Enemy.h"

//Check on device
//=======================================================================
//
Enemy::Enemy ( )
{
    myFirstTimeFlag = true;
    mySpeed = 0.0F;
    myPosition.x = myPosition.y = myPosition.z = 0;
    myLastPosition.x = myLastPosition.y = myLastPosition.z = 0;
    
}
//=======================================================================
//
Enemy::~Enemy ( )
{
    
}
//=======================================================================
//
bool Enemy::init( IDXDEVICE device, int xPos, int yPos, int eType )
{
   bool result = true;
    if( eType == 1 )
    {
       //Creates Dog Enemy
       loadCharacterAnimations( 1 );
       result = mySprite.create( "EDOG-DOWN" );
       mySprite.changeAnimation( myEnemyWalkDownAnim );    
       mySpeed = 1.0f;
    }
    else if( eType == 2 )
    {
       //creates Squid Enemy
       loadCharacterAnimations( 2 );
       result = mySprite.create( "ESQUID-DOWN" ); //Fill with enemy
       mySprite.changeAnimation( myEnemyWalkDownAnim );    
       mySpeed = 1.5f;
    }
    else if( eType == 3 )
    {
       //creates Kid Enemy
       loadCharacterAnimations( 3 );
       result = mySprite.create( "EKID-DOWN" ); //Fill with enemy
       mySprite.changeAnimation( myEnemyWalkDownAnim );    
       mySpeed = 2.0f;
    }

    mySprite.setPosition( float(xPos), float(yPos) );
    myPosition.x = mySprite.getXPosition();
    myPosition.y = mySprite.getYPosition();
    mySprite.setScale( .25f, .25f );
    mySprite.setXVel(mySpeed - mySpeed);
    mySprite.setYVel(mySpeed);
    
    assert(result);
    
    return true;
}
//=======================================================================
//
void Enemy::update()
{
    myLastPosition.x = myPosition.x;
    myLastPosition.y = myPosition.y;
    mySprite.update();
    myPosition.x = mySprite.getXPosition();
    myPosition.y = mySprite.getYPosition();
    
}
//=======================================================================
//
bool Enemy::draw ( IDXSPRITE spriteObj )
{
    mySprite.draw( spriteObj );
    
    return true;
}
//=======================================================================
//
bool Enemy::loadCharacterAnimations ( int eType )
{
    if( myFirstTimeFlag )
    {
        myFirstTimeFlag = false;
        if( eType == 1 )
        {
           myEnemyWalkDownAnim = DxAssetManager::getInstance().getAnimationCopy( "EDOG-DOWN", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
           myEnemyWalkLeftAnim = DxAssetManager::getInstance().getAnimationCopy( "EDOG-LEFT", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
           myEnemyWalkRightAnim = DxAssetManager::getInstance().getAnimationCopy( "EDOG-RIGHT", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
           myEnemyWalkUpAnim = DxAssetManager::getInstance().getAnimationCopy( "EDOG-UP", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
          
           myEnemyBlowUpAnim = DxAssetManager::getInstance().getAnimationCopy( "EDOG-DEAD", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
        }
        if( eType == 2 )
        {
           myEnemyWalkDownAnim = DxAssetManager::getInstance().getAnimationCopy( "ESQUID-DOWN", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
           myEnemyWalkLeftAnim = DxAssetManager::getInstance().getAnimationCopy( "ESQUID-LEFT", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
           myEnemyWalkRightAnim = DxAssetManager::getInstance().getAnimationCopy( "ESQUID-RIGHT", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
           myEnemyWalkUpAnim = DxAssetManager::getInstance().getAnimationCopy( "ESQUID-UP", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
          
           myEnemyBlowUpAnim = DxAssetManager::getInstance().getAnimationCopy( "ESQUID-DEAD", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
        }
        if( eType == 3 )
        {
           myEnemyWalkDownAnim = DxAssetManager::getInstance().getAnimationCopy( "EKID-DOWN", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
           myEnemyWalkLeftAnim = DxAssetManager::getInstance().getAnimationCopy( "EKID-LEFT", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
           myEnemyWalkRightAnim = DxAssetManager::getInstance().getAnimationCopy( "EKID-RIGHT", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
           myEnemyWalkUpAnim = DxAssetManager::getInstance().getAnimationCopy( "EKID-UP", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
          
           myEnemyBlowUpAnim = DxAssetManager::getInstance().getAnimationCopy( "EKID-DEAD", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
        }
    }
    return true;
}
//=======================================================================
//
bool Enemy::Stop ()
{    
    // Stop actual sprite motion.
    mySprite.setXVel(0.0f);
    mySprite.setYVel(0.0f);

    return true;
}    
void Enemy::changeDirection()
{
   int ranNum = rand() % 4 + 1;

   switch( ranNum )
   {
   case 1:
      //DOWN
      mySprite.changeAnimation( myEnemyWalkDownAnim );
      mySprite.setXVel( mySpeed - mySpeed );
      mySprite.setYVel( mySpeed );
      break;
   case 2:
      //UP
      mySprite.changeAnimation( myEnemyWalkUpAnim );
      mySprite.setXVel( mySpeed - mySpeed );
      mySprite.setYVel( -mySpeed);
      break;
   case 3:
      //Right
      mySprite.changeAnimation( myEnemyWalkRightAnim );
      mySprite.setXVel( mySpeed );
      mySprite.setYVel( mySpeed - mySpeed );
      break;
   case 4:
      //LEFT
      mySprite.changeAnimation( myEnemyWalkLeftAnim );
      mySprite.setXVel( -mySpeed );
      mySprite.setYVel( mySpeed - mySpeed );
      break;
   }
}
