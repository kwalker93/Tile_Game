#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "Unit.h"
#include <time.h>






// Constructor
Unit::Unit()
{
	this->MY_MAX_HEALTH = 100;
	this->MY_MAX_POWER = 10; 
	this->myLowPowerLevel = 3;
	this->myHealth= 75;
	this->myMovementPoints = 4; // Movement points
	this->myPositionY = 0;
	this->myPositionX = 0;
	this->calculateDamage();
	//this->myImage;
}

Unit::~Unit()
{

}

Unit::Unit(int maxPower, int lowPower, int maxHealth, int positionY, int positionX )
{
	
	// Max health for this unit.
	this->MY_MAX_HEALTH = maxHealth;
	// Max Power for this unit.
	this->MY_MAX_POWER = maxPower; 

	this->myLowPowerLevel = lowPower;
	this->myHealth= maxHealth;
	this->myMovementPoints = 4; // Movement points

	this->myPositionY = positionY;
	this->myPositionX = positionX;
	this->calculateDamage();

}

bool Unit::gameInit(int xPos, int yPos)
{
	this->myImage.setScale(.25, .25);
	bool result = this->myImage.create("ESQUID-DOWN");

	this->myImage.setPosition(float(xPos), float(yPos));

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
bool Unit::draw ( IDXSPRITE spriteObj )
{ 
   myImage.draw( spriteObj );

   return true;
}

//Gets Health
int Unit::getHealth()
{
	return this->myHealth;
}

//Gets Action Points
int Unit::getMovementPoints()
{
	return this->myMovementPoints;
}

// Gets Damage power
int Unit::getDamage()
{
	
	return this->myAttackPower;

}

//resets the turn for the unit
void Unit::resetTurn()
{
	this->myMovementPoints = 4;
}
// Health affected by attacked
int Unit::healthEffect(int effect)
{

	return (this->myHealth += effect);
	
}

// Actions points used in the move, takes in parameter.
void Unit::reduceMovementPoints()
{
	if(this->myMovementPoints == 0)
	{
		// return error message stating no movement points or error checking in the game layer.

	}else
	{
		this->myMovementPoints--;
	}
}

// Calculates random damage power
int Unit::calculateDamage()
{
	int parameter = (rand() % this->myLowPowerLevel) +this->MY_MAX_POWER; // for now We can change how much to mess with the damage.
	this->myAttackPower = parameter;
	return myAttackPower;
}

//gets the int y coordinate value
int Unit::getY()
{
	return this->myPositionY;
}

//gets the int x coordinate value
int Unit::getX()
{
	return this->myPositionX;
}

