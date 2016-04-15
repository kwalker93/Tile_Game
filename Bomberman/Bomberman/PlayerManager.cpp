
#include <stdafx.h>
#include "Bomberman\PlayerManager.h"
#include "Bomberman\Player.h"
#include "Bomberman\Unit.h"

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
   if ( this->isPlayerOneActing )
   {
      this->playerOnePtr->update();
   }
   else
   {
      this->playerTwoPtr->update();
   }

   return true;
}

//========================================================================
bool PlayerManager::shutdown()
{
   delete[] playerOnePtr;
   delete[] playerTwoPtr;

   return true;
}

//========================================================================
bool PlayerManager::switchTurnToNextPlayer()
{
   if ( this->isPlayerOneActing )
      this->isPlayerOneActing = false;
   else
      this->isPlayerOneActing = true;

   return true;
}