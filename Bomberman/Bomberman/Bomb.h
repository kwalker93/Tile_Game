#pragma once
#if !defined(_BOMB_H_)
#define _BOMB_H_

#include "Utilities/Timer.h"
#include "DxFramework/DxGameSprite.h"
#include "DxFramework/DxImage.h"
#include "DxFramework/DxSound.h"
#include "DxFramework/DxSoundIdentifier.h"

class Bomb
{
//constructers
public:
   Bomb();
   ~Bomb();
   enum BombState{ UNSET, SET, LIGHT, FLASH, EXPLODE };

//Methods used outside of bomb
public:
   bool init( IDXDEVICE device, int xPos, int yPos  );
   void update();
   void shutdown();
   void place( D3DXVECTOR3& position, float kittyWidth, float kittyHeight );  
   bool draw( IDXSPRITE spriteObj );
   DxGameSprite getSprite() { return mySprite; };
   DxGameSprite getSprite( int num ) { return myExplosions[num]; };
   bool getIsExploding(){ return myBombExploding; };

//methods used only by bomb itself
private:
   bool loadCharacterAnimations();
   bool selectAnimation( BombState State );
   bool explode();

//member variables
private:
   bool         myBombExploding;
   bool         myFirstTimeFlag;
   bool         myIsBombSet;
   BombState    myBombState;
   DxGameSprite mySprite;
   std::vector<DxGameSprite> myExplosions;
   Timer        myTimer;
	D3DXVECTOR3  myPosition;
	D3DXVECTOR3  myLastPosition;
   DxAnimation  myBombSetBmAnim;
   DxAnimation  myBombLightAnim;
   DxAnimation  myBombFlashAnim;
   DxAnimation  myBombExplodeAnim;
   
   DxAnimation  myBombExplCentAnime;
   
   DxAnimation  myBombExplAnime;
   DxAnimation  myBombExplUpAnime;
   DxAnimation  myBombExplDownAnime; 
   DxAnimation  myBombExplLeftAnime;
   DxAnimation  myBombExplRightAnime;

   DxSound* mySoundInterface;
   DxSoundIdentifier mySound;
};

#endif