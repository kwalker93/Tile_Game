
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
   this->elapsedTurns = 0;
   this->isPlayerOneActing = isPlayerOneMovingFirst;
   
   if ( ptrPOne == NULL ) // if default game is desired
   {
      this->playerOnePtr->init(true);
   }
   else // create custom players
   {
      this->playerOnePtr = ptrPOne;
   }

   if ( ptrPTwo == NULL ) // if default game is desired
   {
      this->playerTwoPtr->init(false);
   }
   else // else create custom players
   {
      this->playerTwoPtr = ptrPTwo;
   }

   return true;
}

//========================================================================
bool PlayerManager::update()
{
   return ( this->playerOnePtr->update() && this->playerTwoPtr->update() );
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
   this->elapsedTurns++;

   if ( this->isPlayerOneActing )
      this->isPlayerOneActing = false;
   else
      this->isPlayerOneActing = true;

   return true;
}

//========================================================================
int PlayerManager::getNumElapsedTurns()
{
   return this->elapsedTurns;
}

//========================================================================
int PlayerManager::checkUnitTotals()
{
   if ( this->playerOnePtr->getMyUnitCount() <= 0 &&
        this->playerTwoPtr->getMyUnitCount() <= 0 )
   {   
      return GameStates::GS_DRAW;
   }
   else if ( this->playerOnePtr->getMyUnitCount() != 0 &&
             this->playerTwoPtr->getMyUnitCount() <= 0 )
   {
      return GameStates::GS_P1_WINS;
   }
   else if ( this->playerOnePtr->getMyUnitCount() <= 0 &&
             this->playerTwoPtr->getMyUnitCount() != 0 )
   {
      return GameStates::GS_P2_WINS;
   }
   else
   {
      return GameStates::GS_INPROG;
   }

}
