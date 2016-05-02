#include "stdafx.h"
#include "Bomberman/CollisionManager.h"


CollisionManager::CollisionManager()
{
   myFirstTimeFlag = true;
}
//========================================================================================
//
CollisionManager::~CollisionManager(){}
//========================================================================================
//
void CollisionManager::init()
{ 
  loadAnimation();

}
//========================================================================================
//
bool CollisionManager::loadAnimation()
{
   if( myFirstTimeFlag )
   {
      myFirstTimeFlag = false;
      myGrassAnim = DxAssetManager::getInstance().getAnimationCopy( "GRASS", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
      myBoomBrickAnim = DxAssetManager::getInstance().getAnimationCopy( "BRICK-DESTROY", 10, D3DCOLOR_XRGB( 170, 181, 129 ) );
   }

   return true;
}
//========================================================================================
//
void CollisionManager::update(){}
//========================================================================================
//
void CollisionManager::shutdown(){}
//========================================================================================
//
bool CollisionManager::worldCollisions( DxGameSprite sprite, TiledBackground&  LevelRef )
{
   RECT collision = sprite.getCollisionArea();
   int indexTopLeft = ( (int)collision.left / 64 ) + 
                      ( (int)collision.top / 64 ) *  LevelRef.numColumns();

   int indexBottomLeft = ( (int)collision.left / 64 ) + 
                         ( (int)collision.bottom / 64 ) *
                         LevelRef.numColumns();

   int indexTopRight = ( (int)collision.right / 64 ) + 
                       ( (int)collision.top / 64 ) * LevelRef.numColumns();

   int indexBottomRight = ( (int)collision.right / 64 ) +
                          ( (int)collision.bottom / 64 ) * 
                          LevelRef.numColumns();

   if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexTopLeft] )&&  
         LevelRef.mySpriteMap[indexTopLeft].collidable() ) )
   {
      return true;
   }
   else if ( ( sprite.collidesWith( LevelRef.mySpriteMap[indexBottomLeft] ) &&  
              LevelRef.mySpriteMap[indexBottomLeft].collidable() ) )
   {
      return true;
   }
   else if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexTopRight] ) &&  
            LevelRef.mySpriteMap[indexTopRight].collidable() ) )
   {
      return true;
   }
   else if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexBottomRight] ) &&  
             LevelRef.mySpriteMap[indexBottomRight].collidable() ) )
   {
      return true;
   }

   return false;
}

//========================================================================================
//
bool CollisionManager::waterCollisions( DxGameSprite sprite, TiledBackground&  LevelRef )
{
   RECT collision = sprite.getCollisionArea();
   int indexTopLeft = ( (int)collision.left / 64 ) + 
                      ( (int)collision.top / 64 ) *  LevelRef.numColumns();

   int indexBottomLeft = ( (int)collision.left / 64 ) + 
                         ( (int)collision.bottom / 64 ) *
                         LevelRef.numColumns();

   int indexTopRight = ( (int)collision.right / 64 ) + 
                       ( (int)collision.top / 64 ) * LevelRef.numColumns();

   int indexBottomRight = ( (int)collision.right / 64 ) +
                          ( (int)collision.bottom / 64 ) * 
                          LevelRef.numColumns();

   if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexTopLeft] )&&  
         LevelRef.mySpriteMap[indexTopLeft].collidable() &&
         LevelRef.mySpriteMap[indexTopLeft].getAnimation().name() == "WATER" ) )
   {
      return true;
   }
   else if ( ( sprite.collidesWith( LevelRef.mySpriteMap[indexBottomLeft] ) &&  
              LevelRef.mySpriteMap[indexBottomLeft].collidable() &&
         LevelRef.mySpriteMap[indexTopLeft].getAnimation().name() == "WATER" ) )
   {
      return true;
   }
   else if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexTopRight] ) &&  
            LevelRef.mySpriteMap[indexTopRight].collidable() &&
         LevelRef.mySpriteMap[indexTopLeft].getAnimation().name() == "WATER" ) )
   {
      return true;
   }
   else if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexBottomRight] ) &&  
             LevelRef.mySpriteMap[indexBottomRight].collidable() &&
         LevelRef.mySpriteMap[indexTopLeft].getAnimation().name() == "WATER" ) )
   {
      return true;
   }

   return false;
}


//========================================================================================
//
bool CollisionManager::spriteCollsions( DxGameSprite sprite1, DxGameSprite sprite2 )
{
   if( ( sprite1.collidesWith( sprite2 ) && sprite2.collidable() ) )
   {
      return true;
   }

   return false;
}