#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "Unit.h"
#include <time.h>


// Constructor
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
}

Unit::~Unit()
{

}

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

void Unit::setMyPosition( D3DXVECTOR3 pos )
{
	myPosition = pos; myImage.setPosition(myPosition.x, myPosition.y );
}

DxGameSprite Unit::getSprite() 
{ 
	return myImage; 
}

D3DXVECTOR3 Unit::getLastPosition()
{
	return myLastPosition;
}

bool Unit::init( tstring animationName, int xPos, int yPos)
{
	myImage.setScale(.5, .5);
	myImage.create(animationName);

	myImage.setPosition(float(xPos), float(yPos));
	myUnitImage = DxAssetManager::getInstance().getAnimationCopy( animationName, 10 );

	myPosition.x = myImage.getXPosition();
	myPosition.y = myImage.getYPosition();

	mySpeed = 64;

	return true;

}

void Unit::update()
{
   myLastPosition.x = myPosition.x;
   myLastPosition.y = myPosition.y;
   myImage.update();
   myPosition.x = myImage.getXPosition();
   myPosition.y = myImage.getYPosition();
}


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

bool Unit::draw ( IDXSPRITE spriteObj )
{ 
   myImage.draw( spriteObj );

   return true;
}

bool Unit::stop()
{
	myImage.setXVel(0.0f);
	myImage.setYVel(0.0f);
	return true;
}

bool Unit::right()
{
	myImage.setXVel(+mySpeed);
	myImage.setYVel( mySpeed - mySpeed );
	myDirection = Direction::RIGHT;
	return true;
}

bool Unit::up()
{
	myImage.setXVel( mySpeed - mySpeed);
	myImage.setYVel(-mySpeed);
	myDirection = Direction::UP;
	return true;
}

bool Unit::down()
{
	myImage.setXVel( mySpeed - mySpeed);
	myImage.setYVel(+mySpeed);
	myDirection = Direction::DOWN;
	return true;
}

bool Unit::left()
{
	myImage.setXVel(-mySpeed);
	myImage.setYVel(mySpeed - mySpeed);
	myDirection = Direction::LEFT;
	return true;
}

//Gets Health
int Unit::getHealth()
{
	return myHealth;
}

//Gets Action Points
int Unit::getMovementPoints()
{
	return myMovementPoints;
}

// Gets Damage power
int Unit::getDamage()
{
	return myAttackPower;
}

bool Unit::getCanMove()
{
	return myCanMove;
}

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

//resets the turn for the unit
void Unit::resetTurn()
{
	myMovementPoints = 4;
}

// Health affected by attacked
int Unit::takingDamage(int effect)
{
	return (myHealth -= effect);
}

int Unit::healHealth(int effect)
{
	return (myHealth += effect);
}

void Unit::killUnit()
{
   myHealth = 0;
}

bool Unit::checkIfDead()
{
   if(myHealth <= 0)
   {
      return true;
   }
   return false;
}

// Calculates random damage power
int Unit::calculateDamage()
{
	int parameter = (rand() % myLowPowerLevel) +MY_MAX_POWER; // for now We can change how much to mess with the damage.
	myAttackPower = parameter;
	return myAttackPower;
}

//gets the int y coordinate value
int Unit::getY()
{
	return myPosition.y;
}		  

//gets the int x coordinate value
int Unit::getX()
{
	return myPosition.x;
}

void Unit::setY(float newY)
{
	myImage.setYPosition(newY);
}

void Unit::setX(float newX)
{
	myImage.setXPosition(newX);
}
