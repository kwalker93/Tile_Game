
#pragma once
#if !defined(__UNIT_H__)
#define __UNIT_H__


//#include "DXFramework/DxGameSprite.h"
#include "Utilities/TTypes.h"
#include "DxFramework/DxImage.h"
#include "DxFramework/DxGameSprite.h"
using namespace std;

class Unit{



	//constructor
public:
	Unit();
	Unit(int maxPower, int lowPower, int maxHealth, int positionY, int positionX );
	~Unit();
	 enum Direction{ STILL, STILLUP, STILLDOWN, STILLLEFT, STILLRIGHT, UP, DOWN, LEFT, RIGHT };

public:
	// getters for reference to get units private variables and stats.
	//void gameinit();
	//void gameRun();
	//void gameEnd();
	int getHealth();
	int getMovementPoints(); // movement points
	int getDamage();
	void setImage(string);// might need to change// 
	int getY();
	int getX();
	bool gameInit(int, int);
	bool draw (IDXSPRITE spriteObj);


	// functions
	int healthEffect(int effect);// health decrease or powerup health increase??
	//void setPosition(int x, int y);
	void reduceMovementPoints();
	int calculateDamage();
	void resetTurn();
	void Unit::update();

	enum{ solider1, solider2, solider3 };


private:
	D3DXVECTOR3    myPosition;
	D3DXVECTOR3    myLastPosition;   
	Direction      myDirection;

	int MY_MAX_HEALTH;
	int MY_MAX_POWER;
	int myHealth;
	int myMovementPoints;
	int myAttackPower;
	int myLowPowerLevel;

	//Pixel position;
	int myPositionY;
	int myPositionX;
	DxGameSprite myImage;
};


#endif