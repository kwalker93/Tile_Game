
#include <stdafx.h>
#include "Bomberman\PlayerManager.h"
#include "Bomberman\Player.h"
#include "Bomberman\Unit.h"
#include "Bomberman\GameStates.h"

//========================================================================
PlayerManager::PlayerManager()
{
}

//========================================================================
PlayerManager::~PlayerManager()
{
}

//========================================================================
bool PlayerManager::init( bool isPlayerOneMovingFirst, Player* ptrPOne,
                          Player* ptrPTwo )
{
   elapsedTurns = 0;
   isPlayerOneActing = isPlayerOneMovingFirst;
   
   if ( ptrPOne == NULL ) // if default game is desired
   {
      playerOnePtr->init(true, 64, 64, Unit::largeGrey);
   }
   else // create custom players
   {
      playerOnePtr = ptrPOne;
   }

   if ( ptrPTwo == NULL ) // if default game is desired
   {
      playerTwoPtr->init(false, 256, 256, Unit::smallBrown);
   }
   else // else create custom players
   {
      playerTwoPtr = ptrPTwo;
   }

   return true;
}

//========================================================================
bool PlayerManager::update()
{
   return ( playerOnePtr->update() && playerTwoPtr->update() );
}

//========================================================================
bool PlayerManager::shutdown()
{
   delete[] playerOnePtr;
   delete[] playerTwoPtr;

   return true;
}

//========================================================================
bool PlayerManager::endCurrentTurn()
{
   elapsedTurns++;

   if ( isPlayerOneActing )
      isPlayerOneActing = false;
   else
      isPlayerOneActing = true;

   return true;
}

//========================================================================
int PlayerManager::getNumElapsedTurns()
{
   return elapsedTurns;
}

//========================================================================
int PlayerManager::checkUnitTotals()
{
   if ( playerOnePtr->getMyUnitCount() <= 0 &&
        playerTwoPtr->getMyUnitCount() <= 0 )
   {   
      return GameStates::GS_DRAW;
   }
   else if ( playerOnePtr->getMyUnitCount() != 0 &&
             playerTwoPtr->getMyUnitCount() <= 0 )
   {
      return GameStates::GS_P1_WINS;
   }
   else if ( playerOnePtr->getMyUnitCount() <= 0 &&
             playerTwoPtr->getMyUnitCount() != 0 )
   {
      return GameStates::GS_P2_WINS;
   }
   else
   {
      return GameStates::GS_INPROG;
   }

}
