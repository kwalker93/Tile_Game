
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
   this->myUnitCount = numUnits;
   myUnits = new Unit[this->myUnitCount];

   for ( int ix = 0; ix < this->myUnitCount; ix++ )
   {
      // TODO: 
      // myUnits[ix].init(); 
   }
   
   return true;
}

//========================================================================
bool Player::update()
{
   return true;
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
