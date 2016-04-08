
#pragma once
#if !defined(_BOMBERMAN_H_)
#define _BOMBERMAN_H_

//#include "resource.h"
#include "Utilities/Rect.h"
#include "Utilities/Logger.h"
#include "DxFramework/DxFramework.h"
#include "DxFramework/DxController.h"
#include "DxFramework/DxImage.h"
#include "DxFramework/DxTexture.h"
#include "DxFramework/DxAnimation.h"
#include "DxFramework/DxKeyboard.h"
#include "DxFramework/DxGameSprite.h"
#include "DxFramework/DxTypes.h"
#include "Bomberman/TiledBackground.h"
#include "Bomberman/Kitty.h"
#include "Bomberman/Bomb.h"
#include "Bomberman/Kitty.h"
#include "DxFramework/DxSound.h"
#include "DxFramework/DxSoundIdentifier.h"

 
class Game : public DxFramework
{
public:
   Game ();
   ~Game ();

protected:
   bool gameInit ();
   void gameRun ();
   void gameExit ();
   //LPCTSTR 


   //------------------------------------------------------------
   // Windows virtual interface
   int winScreenWidth() const { return 800; }
   int winScreenHeight() const { return 600; }
   //Below doesn't currently work...
   //LPCTSTR winAppTitleStr () const { "BomberCat"; }


private:
   D3DCOLOR bgColor;
   DxTexture  myImage;	
   
   tstring     myGameTitle;


   TiledBackground   myLevelBgnds[ 1 ];
   Bomb              myBomb;
   Kitty             myKitty;
   Kitty             otherKitty;
   DxKeyboard        myKeyboard;
   D3DXVECTOR3       myPlayerPos;
   D3DXVECTOR3       myPlayerLastPos;
   RECT              myBgRect;
   //DxGameSprite      mySprite;

   DxSound* mySoundInterface;
   DxSoundIdentifier mySound;

};

#endif //_TESTAPP_H_ //todo sas: whoops.