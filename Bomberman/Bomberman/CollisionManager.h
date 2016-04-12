#pragma once

#if !defined( _COLLISIONMANAGER_H_ )
#define _COLLISIONMANAGER_H_

#include "DxFramework/DxFramework.h"
#include "DxFramework/DxGameSprite.h"
#include "DxFramework/DxGameSprite.h"
#include "DxFramework/DxImage.h"
#include "Bomberman/TiledBackground.h"

class CollisionManager
{
public:
   CollisionManager();
   ~CollisionManager();
   void init();
   void update();
   void shutdown();
   
   bool CollisionCalc( DxGameSprite sprite, int numColum );
   bool worldCollisions( DxGameSprite sprite1, TiledBackground&  myLevelRef );
   bool exploisionCollisions( DxGameSprite sprite, TiledBackground&  LevelRef );
   bool spriteCollsions( DxGameSprite sprite1, DxGameSprite sprite2 );

private:
   bool loadAnimation();

private:
   bool myFirstTimeFlag;
   DxAnimation myGrassAnim;
   DxAnimation myBoomBrickAnim;


};

#endif 
