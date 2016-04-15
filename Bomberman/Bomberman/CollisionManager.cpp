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
   int indexTopLeft = ( (int)collision.left / 32 ) + 
                      ( (int)collision.top / 32 ) *  LevelRef.numColumns();

   int indexBottomLeft = ( (int)collision.left / 32 ) + 
                         ( (int)collision.bottom / 32 ) *
                         LevelRef.numColumns();

   int indexTopRight = ( (int)collision.right / 32 ) + 
                       ( (int)collision.top / 32 ) * LevelRef.numColumns();

   int indexBottomRight = ( (int)collision.right / 32 ) +
                          ( (int)collision.bottom / 32 ) * 
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
bool CollisionManager::exploisionCollisions( DxGameSprite sprite, TiledBackground&  LevelRef )
{
   RECT collision = sprite.getCollisionArea();
   int indexTopLeft = ( (int)collision.left / 32 ) + 
                      ( (int)collision.top / 32 ) *  LevelRef.numColumns();

   int indexBottomLeft = ( (int)collision.left / 32 ) + 
                         ( (int)collision.bottom / 32 ) *
                         LevelRef.numColumns();

   int indexTopRight = ( (int)collision.right / 32 ) + 
                       ( (int)collision.top / 32 ) * LevelRef.numColumns();

   int indexBottomRight = ( (int)collision.right / 32 ) +
                          ( (int)collision.bottom / 32 ) * 
                          LevelRef.numColumns();

   if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexTopLeft] )&&  
         LevelRef.mySpriteMap[indexTopLeft].collidable() ) )
   {
      if( LevelRef.mySpriteMap[indexTopLeft].getDestroyable())
      {
         LevelRef.mySpriteMap[indexTopLeft].setDestroyable( false );
         LevelRef.mySpriteMap[indexTopLeft].changeAnimation ( myBoomBrickAnim ); 
         LevelRef.mySpriteMap[indexTopLeft].collidable( false );
      }
      return true;
   }
   else if ( ( sprite.collidesWith( LevelRef.mySpriteMap[indexBottomLeft] ) &&  
              LevelRef.mySpriteMap[indexBottomLeft].collidable() ) )
   {
      if( LevelRef.mySpriteMap[indexBottomLeft].getDestroyable())
      {
         LevelRef.mySpriteMap[indexBottomLeft].setDestroyable( false );
         LevelRef.mySpriteMap[indexBottomLeft].changeAnimation ( myBoomBrickAnim );
         LevelRef.mySpriteMap[indexBottomLeft].collidable( false );
      } 
      return true;
   }
   else if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexTopRight] ) &&  
            LevelRef.mySpriteMap[indexTopRight].collidable() ) )
   {
      if( LevelRef.mySpriteMap[indexTopRight].getDestroyable())
      {
         LevelRef.mySpriteMap[indexTopRight].setDestroyable( false );
         LevelRef.mySpriteMap[indexTopRight].changeAnimation( myBoomBrickAnim );
         LevelRef.mySpriteMap[indexTopRight].collidable( false );
      }
      return true;
   }
   else if( ( sprite.collidesWith( LevelRef.mySpriteMap[indexBottomRight] ) &&  
             LevelRef.mySpriteMap[indexBottomRight].collidable() ) )
   {
      if( LevelRef.mySpriteMap[indexBottomRight].getDestroyable())
      {
         LevelRef.mySpriteMap[indexBottomRight].setDestroyable( false );
         LevelRef.mySpriteMap[indexBottomRight].changeAnimation ( myBoomBrickAnim );
         LevelRef.mySpriteMap[indexBottomRight].collidable( false );
      }
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