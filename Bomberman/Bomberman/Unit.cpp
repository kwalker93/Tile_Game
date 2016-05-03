#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "Unit.h"
#include <time.h>


//========================================================================================
//
Unit::Unit()
{
	MY_MAX_HEALTH = 100;
	MY_MAX_POWER = 10; 
	myLowPowerLevel = 3;
	myHealth= 75;
	myMovementPoints = 4; // Movement points
	myPositionY = 0;
	myPositionX = 0;
	calculateDamage();
	myCanMove = false;
   hitWater = false;
}

//========================================================================================
//
Unit::~Unit()
{

}

//========================================================================================
//
Unit::Unit(int maxPower, int lowPower, int maxHealth, int positionY, int positionX )
{
	myCanMove = false;
	// Max health for this unit.
	MY_MAX_HEALTH = maxHealth;
	// Max Power for this unit.
	MY_MAX_POWER = maxPower; 

	myLowPowerLevel = lowPower;
	myHealth= maxHealth;
	myStartingMovePoints = myMovementPoints = 4; // Movement points

	myPositionY = positionY;
	myPositionX = positionX;
	calculateDamage();
}

//========================================================================================
//
bool Unit::init( Unit::Type unitType, int xPos, int yPos)
{
   initUnitStrings();
	this->myImage.setScale(.5, .5);
	this->myImage.create(myUnitStrings.at(unitType));

	myImage.setPosition(float(xPos), float(yPos));
    tstring unitStr = myUnitStrings.at(unitType);
	myUnitImage = DxAssetManager::getInstance().getAnimationCopy( unitStr, 10 );

	myPosition.x = myImage.getXPosition();
	myPosition.y = myImage.getYPosition();

	mySpeed = 64;

	return true;
}

//========================================================================================
//
bool Unit::initUnitStrings()
{
   myUnitStrings.push_back("BLANK");

   myUnitStrings.push_back("ACORN-BROWN");
   myUnitStrings.push_back("LARGE-BROWN");
   myUnitStrings.push_back("MEDIUM-BROWN");
   myUnitStrings.push_back("SMALL-BROWN");

   myUnitStrings.push_back("ACORN-GREY");
   myUnitStrings.push_back("LARGE-GREY");
   myUnitStrings.push_back("MEDIUM-GREY");
   myUnitStrings.push_back("SMALL-GREY");

   myUnitStrings.push_back("ACORN-ORANGE");
   myUnitStrings.push_back("LARGE-ORANGE");
   myUnitStrings.push_back("MEDIUM-ORANGE");
   myUnitStrings.push_back("SMALL-ORANGE");

   return true;
}

//========================================================================================
//
void Unit::update()
{
   if( checkIfDead() || hitWater == true )
   {
      killUnit();
   }
   myLastPosition.x = myPosition.x;
   myLastPosition.y = myPosition.y;
   myImage.update();
   myPosition.x = myImage.getXPosition();
   myPosition.y = myImage.getYPosition();
}

//========================================================================================
//
void Unit::destroy()
{
   myUnitImage.shutdown();
   myPosition = D3DXVECTOR3(0, 0, 0);
   myLastPosition = D3DXVECTOR3(0, 0, 0);
   mySpeed = 0;
   MY_MAX_HEALTH = 0;
   MY_MAX_POWER = 0;
   myHealth = 0;
   myMovementPoints = 0;
   myStartingMovePoints = 0;
   myAttackPower = 0;
   myLowPowerLevel = 0;
   myCanMove = false;
   myPositionY = 0;
   myPositionX = 0;
   myImage.destroy();
}

//========================================================================================
//
bool Unit::draw ( IDXSPRITE spriteObj )
{ 
   myImage.draw( spriteObj );

   return true;
}

//========================================================================================
//
void Unit::setMyPosition( D3DXVECTOR3 pos )
{
	myPosition = pos; myImage.setPosition(myPosition.x, myPosition.y );
}

//========================================================================================
//
DxGameSprite Unit::getSprite() 
{ 
	return myImage; 
}

//========================================================================================
//
D3DXVECTOR3 Unit::getLastPosition()
{
	return myLastPosition;
}

//========================================================================================
//
bool Unit::stop()
{
	myImage.setXVel(0.0f);
	myImage.setYVel(0.0f);
	return true;
}

//========================================================================================
//
bool Unit::right()
{
	myImage.setXVel(+mySpeed);
	myImage.setYVel( mySpeed - mySpeed );
	myDirection = Direction::RIGHT;
	return true;
}

//========================================================================================
//
bool Unit::up()
{
	myImage.setXVel( mySpeed - mySpeed);
	myImage.setYVel(-mySpeed);
	myDirection = Direction::UP;
	return true;
}

//========================================================================================
//
bool Unit::down()
{
	myImage.setXVel( mySpeed - mySpeed);
	myImage.setYVel(+mySpeed);
	myDirection = Direction::DOWN;
	return true;
}

//========================================================================================
//
bool Unit::left()
{
	myImage.setXVel(-mySpeed);
	myImage.setYVel(mySpeed - mySpeed);
	myDirection = Direction::LEFT;
	return true;
}

//========================================================================================
//
int Unit::getHealth()
{
	return myHealth;
}


//========================================================================================
//
int Unit::getMovementPoints()
{
	return myMovementPoints;
}

//========================================================================================
//
int Unit::getDamage()
{
	return myAttackPower;
}

//========================================================================================
//
bool Unit::getCanMove()
{
	return myCanMove;
}

//========================================================================================
//
void Unit::setMove()
{
	if(myCanMove == false)
	{
		myCanMove = true;
	}
   else if( myCanMove == true)
	{
		myCanMove = false;
	}
}

//========================================================================================
//
int Unit::takingDamage(int effect)
{
	return (myHealth -= effect);
}

//========================================================================================
//
int Unit::healHealth(int effect)
{
	return (myHealth += effect);
}

//========================================================================================
//
void Unit::killUnit()
{
   myHealth = 0;
   myImage.changeAnimation("BLANK", 0);
   myImage.collidable(false);
}

//========================================================================================
//
bool Unit::checkIfDead()
{
   if(myHealth <= 0)
   {
      return true;
   }
   return false;
}

//========================================================================================
//
int Unit::calculateDamage()
{
	int parameter = (rand() % myLowPowerLevel) +MY_MAX_POWER; // for now We can change how much to mess with the damage.
	myAttackPower = parameter;
	return myAttackPower;
}

//========================================================================================
//
int Unit::getY()
{
	return myPosition.y;
}		  

//========================================================================================
//
int Unit::getX()
{
	return myPosition.x;
}

//========================================================================================
//
void Unit::setY(float newY)
{
	myImage.setYPosition(newY);
}

//========================================================================================
//
void Unit::setX(float newX)
{
	myImage.setXPosition(newX);
}


//========================================================================================
//
bool Unit::getHitWaterFlag( )
{
   return hitWater;
}


//========================================================================================
//
void Unit::setHitWaterFlag( bool newFlag )
{
   hitWater = newFlag;
}
