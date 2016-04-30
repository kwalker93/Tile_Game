
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
  // int x = 36;
  // int y = 36;
   for ( int ix = 0; ix < this->myMaxUnits; ix++ )
   {
      // TODO: 
	//   this->myUnits[ix].gameInit(x, y); 
	  // x +=32;
   }
   
   return true;
}


//========Init All the Units===============================================================
bool Player::unitInit(int x, int y)
 {
	 myArrayUnits.resize(4);

	
	//this.myArrayUnits.at(0).gameInit(x, y);
	 for(int index = 0; index < this->myArrayUnits.size(); index++)
	 {
			this->myArrayUnits[index].init("ACORN-BROWN",x, y);
			x += 32; 
	 }

	 return true;
	
 }
//=========Update all the Units==============================================================
bool Player::unitUpdate()
{
	for(int index = 0; index < this->myArrayUnits.size(); index++)
	{
		this->myArrayUnits.at(index).update();
	}
	return true;
}
//==========Determines what Unit was Clicked=============================================================
bool Player::unitClick(int mouseX, int mouseY)
{
	
	if( mouseX >= myArrayUnits.at(0).getX() && mouseX <= (myArrayUnits.at(0).getX() +32) 
		&& mouseY >= myArrayUnits.at(0).getY() && mouseY <= (myArrayUnits.at(0).getY() +32))
	{
		resetUnitMove();
		myArrayUnits.at(0).setMove();
		return true;
	}
	if( mouseX >= myArrayUnits.at(1).getX() && mouseX <= (myArrayUnits.at(1).getX() +32) 
		&& mouseY >= myArrayUnits.at(1).getY() && mouseY <= (myArrayUnits.at(1).getY() +32))
	{
		resetUnitMove();
		myArrayUnits.at(1).setMove();
		return true;
	}
	if( mouseX >= myArrayUnits.at(2).getX() && mouseX <= (myArrayUnits.at(2).getX() +32) 
		&& mouseY >= myArrayUnits.at(2).getY() && mouseY <= (myArrayUnits.at(2).getY() +32))
	{
		resetUnitMove();

		myArrayUnits.at(2).setMove();
		return true;
	}
	if( mouseX >= myArrayUnits.at(3).getX() && mouseX <= (myArrayUnits.at(3).getX() +32) 
		&& mouseY >= myArrayUnits.at(3).getY() && mouseY <= (myArrayUnits.at(3).getY() +32))
	{
		resetUnitMove();
		myArrayUnits.at(3).setMove();
		return true;
	}

	return false;
}
//========Unit Collision===============================================================
void Player::unitCollision()
{	
	for(int index = 0; index < this->myArrayUnits.size(); index++)
	{
			D3DXVECTOR3 snPos = myArrayUnits.at(index).getLastPosition();
           myArrayUnits.at(index).setMyPosition(snPos);
	}
}

//=====Resets All Units CanMove to false==================================================================
void Player::resetUnitMove()
{
	for(int index = 0; index < this->myArrayUnits.size(); index++)
	{
		if(myArrayUnits.at(index).getCanMove() == true)
		{
		this->myArrayUnits.at(index).setMove();
		}
	}
}
//========Unit Drawing===============================================================
bool Player::unitDraw(IDXSPRITE spriteInterface)
{
	for(int index = 0; index < this->myArrayUnits.size(); index++)
	{
		this->myArrayUnits.at(index).draw(spriteInterface);
	}

	return true;
}
//=======Unit Updates=======================================================================
Unit Player::getUnit(int num)
{
	
	return this->myArrayUnits[num];
}
//========================================================================
bool Player::update()
{
   return true;

   for ( int ix = 0; ix < this->myMaxUnits; ix++ )
   {
      if ( /*Unit exists*/ true )
      {
         
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

//==========Untested::Gets the Current selected Units or returns the Previous Selected==============================================================
Unit Player::getSelectedUnit()
{
	for(int index = 0; index < this->myArrayUnits.size(); index++)
	{
		if(this->myArrayUnits.at(index).getCanMove() == true)
		{
			myPreviousSelectedUnit = this->myArrayUnits.at(index);
			return this->myArrayUnits.at(index);
		}	
	}
	return myPreviousSelectedUnit;
}

//========================================================================
void Player::setSelectedUnit( Unit& selectedUnit )
{
   mySelectedUnit = selectedUnit;
}

//========Moves the Unit to the left================================================================
void Player::left()
{
	for(int index = 0; index < this->myArrayUnits.size(); index++)
	{
		if(myArrayUnits.at(index).getCanMove() == true)
		{
			this->myArrayUnits.at(index).left();
			resetUnitMove();
		}
	}
}
//========Stops all the Units===============================================================
void Player::stopAllUnits()
{
	for(int index = 0; index < this->myArrayUnits.size(); index++)
	{
		this->myArrayUnits.at(index).stop();
	}
}

//============Moves the Unit to the down============================================================
void Player::down()
{
  for(int index = 0; index < this->myArrayUnits.size(); index++)
	{
		if(myArrayUnits.at(index).getCanMove() == true)
		{
			this->myArrayUnits.at(index).down();
			resetUnitMove();
		}
	}
}

//===========Moves the Unit to the up=============================================================
void Player::up()
{
	for(int index = 0; index < this->myArrayUnits.size(); index++)
	{
		if(myArrayUnits.at(index).getCanMove() == true)
		{
			this->myArrayUnits.at(index).up();
			resetUnitMove();
		}
	}
}
//===========Moves the Unit to the right=============================================================
void Player::right()
{
	for(int index = 0; index < this->myArrayUnits.size(); index++)
	{
		if(myArrayUnits.at(index).getCanMove() == true)
		{
			this->myArrayUnits.at(index).right();
			resetUnitMove();
		}
	}
}
