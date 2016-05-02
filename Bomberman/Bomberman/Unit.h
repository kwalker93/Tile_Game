
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
   enum Direction{ UP, DOWN, LEFT, RIGHT };

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
   bool init(tstring spriteName, int xPos, int yPos);
   void destroy();
   bool draw (IDXSPRITE spriteObj);

   DxGameSprite& getImage() { return myImage; }

   // functions
   int takingDamage(int effect);
   int healHealth(int effect);
   
   
   
   //void setPosition(int x, int y);
   void reduceMovementPoints();
   int calculateDamage();
   void resetTurn();
   void update();
   void setMyPosition ( D3DXVECTOR3 pos );
   DxGameSprite getSprite();
   D3DXVECTOR3 getLastPosition();

   void setY(float newY);
   void setX(float newX);

   bool stop();
   bool right();
   bool left();
   bool down();
   bool up();
   void setMove();
   bool getCanMove();

   void resetMovePoints() { myMovementPoints = myStartingMovePoints; }
   void decMovePoints() { if( myMovementPoints > 0 ) { myMovementPoints--; } }
   void incMovePoints() { if( myMovementPoints < myStartingMovePoints ) { myMovementPoints++; } }
   
   bool checkIfDead();

   /*
      Units damage other Units
      waterRising water tile kill
      message box for winner
      
      game logic
         attack other unit, then end turn
         only select one unit
   */

   enum{ solider1, solider2, solider3 };


private:
   DxAnimation	   myUnitImage;
   D3DXVECTOR3    myPosition;
   D3DXVECTOR3    myLastPosition;   
   Direction      myDirection;
   float			   mySpeed;

   int            MY_MAX_HEALTH;
   int            MY_MAX_POWER;
   int            myHealth;
   int            myMovementPoints;
   int            myStartingMovePoints;
   int            myAttackPower;
   int            myLowPowerLevel;
   bool           myCanMove;

   //Pixel position;
   int            myPositionY;
   int            myPositionX;
   DxGameSprite   myImage;
};


#endif