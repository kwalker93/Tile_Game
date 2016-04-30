
//========================================================================
// Nathan Contreras
//    Player Class
//       Player class will be in control of all of their units, and be
//       responsible for making actions with their units.
//========================================================================


#pragma once
#if !defined(__PLAYER_H__)
#define __PLAYER_H__

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "DxFramework\DXFramework.h"
#include "Bomberman\Unit.h"
#include "Bomberman\GameStates.h"

//========================================================================
class Player
{
// public methods/data
public:
   Player();   //Ctor
  ~Player();   //Dtor

   bool init( bool playerOne, int numUnits = 8 );
   bool update();
   bool shutdown();

   // Getters
   Unit* getMyUnitArr();
   int   getMyUnitCount();
   bool  getPlayerOneStatus();
   
   // Signals
   bool unitKilled();
   bool playerLoses();
   Unit getUnit(int num);
   bool unitInit(int x, int y);
   bool unitUpdate();
   bool unitDraw(IDXSPRITE spriteInterface);

   bool unitClick(int mouseX, int mouseY);


   Unit getSelectedUnit();
   void setSelectedUnit( Unit& selectedUnit );

   void left();
   void down();
   void up();
   void right();
   void resetUnitMove();
   void stopAllUnits();
   void unitCollision();

// private methods/data
private:
   Unit* myUnits;// The units that belong to this player

   int   myUnitCount;  // The current number of units that belong to this player
   int   myMaxUnits;   // The total number of units that initally belonged to this player
   bool  isPlayerOne;  // Whether or not this Player is player one
   Unit mySelectedUnit;
   Unit myPreviousSelectedUnit;

   vector<Unit> myArrayUnits;

};

#endif