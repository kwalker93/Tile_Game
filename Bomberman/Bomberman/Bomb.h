#pragma once
#if !defined(_BOMB_H_)
#define _BOMB_H_

#include "DxFramework\DxGameSprite.h"
#include "DxFramework\DxImage.h"
#include "Utilities\Timer.h"

class Bomb
{
public:
   Bomb();
   ~Bomb();
   enum BombState{ UNSET, SET, LIGHT, FLASH, EXPLODE };

   bool init( IDXDEVICE device );
   void update();
   void shutdown();
   
   void place( int xPos, int yPos );
   bool draw( IDXSPRITE spriteObj );
   bool selectAnimation( BombState State );

protected:


private:
   bool loadCharacterAnimations();


private:
   bool         myFirstTimeFlag;
   bool         myIsBombSet;
   BombState    myBombState;
   DxGameSprite mySprite;

   DxAnimation  myBombSetAnim;
   DxAnimation  myBombLightAnim;
   DxAnimation  myBombFlashAnim;
   DxAnimation  myBombExplodeAnim;
   DxAnimation  myBombWickAnime;

   Timer        myTimer;
	D3DXVECTOR3  myPosition;
	D3DXVECTOR3  myLastPosition;
};

#endif