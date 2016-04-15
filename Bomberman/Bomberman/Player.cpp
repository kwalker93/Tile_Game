
#include <stdafx.h>
#include "Bomberman\Player.h"
#include "Bomberman\Unit.h"
#include "Bomberman\GameStates.h"

//========================================================================
Player::Player()
{
}

//========================================================================
Player::~Player()
{
}

//========================================================================
bool Player::init( bool playerOne, int numUnits )
{
   this->myUnitCount = this->myMaxUnits = numUnits;
   myUnits = new Unit[this->myUnitCount];

   for ( int ix = 0; ix < this->myMaxUnits; ix++ )
   {
      // TODO: 
      // this->myUnits[ix].init(); 
   }
   
   return true;
}

//========================================================================
bool Player::update()
{
   return true;

   for ( int ix = 0; ix < this->myMaxUnits; ix++ )
   {
      if ( /*Unit exists*/ true )
      {
         ;
         // TODO:
         // this->myUnits[ix].update();
      }
   }
}

//========================================================================
bool Player::shutdown()
{
   delete[] this->myUnits;

   return true;
}

//========================================================================
Unit* Player::getMyUnitArr()
{
   return this->myUnits;
}

//========================================================================
int Player::getMyUnitCount()
{
   return this->myUnitCount;
}

//========================================================================
bool Player::getPlayerOneStatus()
{
   return this->isPlayerOne;
}

//========================================================================
bool Player::unitKilled()
{
   this->myUnitCount--;
   return true;
}
