
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
#include "DxFramework/DxMouse.h"
#include "DxFramework/DxGameSprite.h"
#include "DxFramework/DxTypes.h"
#include "Bomberman/TiledBackground.h"
#include "Bomberman/Kitty.h"
#include "Bomberman/Kitty.h"
#include "DxFramework/DxSound.h"
#include "DxFramework/DxSoundIdentifier.h"
#include "Bomberman/CollisionManager.h"
#include "Bomberman/Unit.h" 
#include "Bomberman/GameUI.h"
#include "WinApplFramework/GameMessages.h"
#include "Bomberman/Player.h"
#include "Bomberman/PlayerManager.h"

 
class Game : public DxFramework
{
public:
   Game ();
   ~Game ();

protected:
   bool gameInit ();
   void gameRun ();
   void gameExit ();

   //Message Box methods
   int checkIfQuitting();
   int checkIfReseting();

   bool checkForNewGame();

   //------------------------------------------------------------
   // Windows virtual interface
   int winScreenWidth() const { return 1004; }
   int winScreenHeight() const { return 640; }   //Below doesn't currently work...
   //LPCTSTR winAppTitleStr () const { "BomberCat"; }

private:
	bool                 myButtonCheck;
   GameMessages         myGm;

   D3DCOLOR             bgColor;
   DxTexture            myImage;	
   
   PlayerManager        myManager;
   tstring              myGameTitle;
   Player	            myPlayer1;
   Player               myPlayer2;
   DxMouse		         myMouse;

   int                  myTurnCount;
   Unit		            myUnits;

   TiledBackground      myLevelBgnds;
   Kitty                myKitty;
   DxKeyboard           myKeyboard;
   D3DXVECTOR3          myPlayerPos;
   D3DXVECTOR3          myPlayerLastPos;
   RECT                 myBgRect;
   CollisionManager     myCollisionManager;

   DxSound*             mySoundInterface;
   DxSoundIdentifier    mySound;

   GameUI               myGameUI;

};

#endif //_TESTAPP_H_ //todo sas: whoops.