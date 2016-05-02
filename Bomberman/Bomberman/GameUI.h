#pragma once

#if !defined(_GAMEUI_H_)
#define _GAMEUI_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities/NonCopyable.h"
#include "Utilities/TTypes.h"
#include "Utilities/Rect.h"
#include "Utilities/Point.h"
#include "DxFramework/DxTexture.h"
#include "DxFramework/DxTypes.h"
#include "DxFramework/DxGameSprite.h"
#include "DxFramework/DxText.h"
#include "Utilities/Timer.h"
#include "DxFramework/DxAssetManager.h"
#include "Bomberman/Unit.h"



class GameUI
{
public:
   GameUI ( void );
   ~GameUI ( void );

public:
   bool init( IDXFONT font, int xPos, int yPos, D3DCOLOR color, int turnCounter );
   bool update( );
   bool destroy();

   bool draw( IDXSPRITE spriteObj );

   void updateTurnCounterText( );

   void setCurrentUnit( Unit& newUnit );
   void updateCurrentUnitImage();


   void updateSelectedUnitPowerText();
   void updateSelectedUnitMovementPointsText();
   void updateSelectedUnitHealthText( );




private:
   
   int            myTurnCounter; 

   DxText         myTurnCounterText;  
   DxText         myPowerText;
   DxText         myMovePointsText;
   DxText         myHealthText;

   D3DCOLOR       myTextColor; 

   Unit           myCurrentUnit;
   DxGameSprite   myCurrentUnitImage;
   
};

#endif 



	











