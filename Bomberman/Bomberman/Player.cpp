
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
bool Player::init( bool playerOne, int x, int y, Unit::Type unitType, int numUnits )
{
   myUnitCount = myMaxUnits = numUnits;

   myArrayUnits.resize(numUnits);

   //this.myArrayUnits.at(0).gameInit(x, y);
   for(unsigned index = 0; index < myArrayUnits.size(); index++)
   {
      myArrayUnits[index].init(unitType, x, y);
      myArrayUnits[index].getSprite().collidable(true);
      x += 64; 
   }

   myArrayUnits[0].setMove();

   return true;
}



//==========Determines what Unit was Clicked=============================================================
void Player::unitClick( Point mousePos )
{
   for( unsigned i = 0; i < myArrayUnits.size(); i++ )
   {
      if( myArrayUnits[i].getImage().getCollisionArea().contains( mousePos ) )
      {
         resetUnitMove();
         myArrayUnits[i].setMove();
         mySelectedUnit = myArrayUnits[i];
      }
   }
}
//========Unit Collision===============================================================
void Player::unitCollision()
{	
   for(unsigned index = 0; index < myArrayUnits.size(); index++)
   {
      D3DXVECTOR3 snPos = myArrayUnits[index].getLastPosition();
      myArrayUnits[index].setMyPosition(snPos);
      myArrayUnits[index].incMovePoints();
   }
}

//=====Resets All Units CanMove to false==================================================================
void Player::resetUnitMove()
{
   for(unsigned index = 0; index < myArrayUnits.size(); index++)
   {
      if(myArrayUnits[index].getCanMove() == true)
      {
         myArrayUnits[index].setMove();
      }
   }
}
//========Unit Drawing===============================================================
bool Player::unitDraw(IDXSPRITE spriteInterface)
{
   for(unsigned index = 0; index < myArrayUnits.size(); index++)
   {
      myArrayUnits[index].draw(spriteInterface);
   }

   return true;
}
//=======Unit Updates=======================================================================
Unit Player::getUnit(int num)
{
   return myArrayUnits[num];
}
//========================================================================
bool Player::update()
{
   checkUnitHealths();
   for ( int i = 0; i < myArrayUnits.size(); i++ )
   {
      myArrayUnits[i].update();
   }
   return true;
}

//========================================================================
bool Player::shutdown()
{
   delete[] myUnits;

   return true;
}

//========================================================================
Unit* Player::getMyUnitArr()
{
   return myUnits;
}

//========================================================================
int Player::getMyUnitCount()
{
   return myUnitCount;
}

//========================================================================
bool Player::getPlayerOneStatus()
{
   return isPlayerOne;
}

//========================================================================
bool Player::unitKilled()
{
   myUnitCount--;
   return true;
}

//========================================================================
void Player::checkUnitHealths()
{
   for(unsigned index = 0; index < myArrayUnits.size(); index++)
	{
      if( myArrayUnits[index].checkIfDead() )
      {
         myArrayUnits[index].getImage().destroy();
      }
   }
}

//==========Untested::Gets the Current selected Units or returns the Previous Selected==============================================================
Unit Player::getSelectedUnit()
{
	for(unsigned index = 0; index < myArrayUnits.size(); index++)
	{
		if(myArrayUnits[index].getCanMove() == true)
		{
			myPreviousSelectedUnit = myArrayUnits[index];
			return myArrayUnits[index];
		}	
	}
	return myPreviousSelectedUnit;
}

//========================================================================
void Player::setSelectedUnit( Unit& selectedUnit )
{
   mySelectedUnit = selectedUnit;
}

////========Moves the Unit to the left================================================================
//void Player::left()
//{
//   mySelectedUnit.left();
//}
////========Stops all the Units===============================================================
//void Player::stopAllUnits()
//{
//   for(int index = 0; index < myArrayUnits.size(); index++)
//   {
//      myArrayUnits[index].stop();
//   }
//}
//
////============Moves the Unit to the down============================================================
//void Player::down()
//{
//   mySelectedUnit.down();
//}
//
////===========Moves the Unit to the up=============================================================
//void Player::up()
//{
//   mySelectedUnit.up();
//}
////===========Moves the Unit to the right=============================================================
//void Player::right()
//{
//   mySelectedUnit.right();
//}

//========Moves the Unit to the left================================================================
void Player::left()
{
	for(unsigned index = 0; index < myArrayUnits.size(); index++)
	{
		if(myArrayUnits[index].getCanMove() == true &&
         myArrayUnits[index].getMovementPoints() > 0 )
		{
			myArrayUnits[index].left();
         myArrayUnits[index].decMovePoints();
		}
	}
}
//========Stops all the Units===============================================================
void Player::stopAllUnits()
{
	for(unsigned index = 0; index < myArrayUnits.size(); index++)
	{
		myArrayUnits[index].stop();
	}
}

//============Moves the Unit to the down============================================================
void Player::down()
{
  for(unsigned index = 0; index < myArrayUnits.size(); index++)
	{
		if(myArrayUnits[index].getCanMove() == true &&
         myArrayUnits[index].getMovementPoints() > 0)
		{
			myArrayUnits[index].down();
         myArrayUnits[index].decMovePoints();
		}
	}
}

//===========Moves the Unit to the up=============================================================
void Player::up()
{
	for(unsigned index = 0; index < myArrayUnits.size(); index++)
	{
		if(myArrayUnits[index].getCanMove() == true &&
         myArrayUnits[index].getMovementPoints() > 0)
		{
			myArrayUnits[index].up();
         myArrayUnits[index].decMovePoints();
		}
	}
}
//===========Moves the Unit to the right=============================================================
void Player::right()
{
	for(unsigned index = 0; index < myArrayUnits.size(); index++)
	{
		if(myArrayUnits[index].getCanMove() == true &&
         myArrayUnits[index].getMovementPoints() > 0)
		{
			myArrayUnits[index].right();
         myArrayUnits[index].decMovePoints();         
		}
	}
}