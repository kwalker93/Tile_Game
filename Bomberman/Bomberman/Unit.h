
#pragma once
#if !defined(__UNIT_H__)
#define __UNIT_H__


//#include "DXFramework/DxGameSprite.h"
#include "Utilities/TTypes.h"
#include "DxFramework/DxImage.h"
#include "DxFramework/DxGameSprite.h"
using namespace std;

class Unit
{

public:

   operator bool ( void ) { return myHealth != 0; }


   Unit();
  ~Unit();
   Unit(int maxPower, int lowPower, int maxHealth, int positionY, int positionX );


   //direction and enemy type enums
   enum Direction{ UP, DOWN, LEFT, RIGHT };
   enum Type { 
      blank = 0,
      acornBrown = 1, largeBrown, mediumBrown, smallBrown,
      acornGrey = 5, largeGrey, mediumGrey, smallGrey,
      acornOrange = 9, largeOrange, mediumOrange, smallOrange
   };

   vector<tstring> myUnitStrings;

public:

   //setup functions
   bool init(Type unitType, int xPos, int yPos);
   bool initUnitStrings();
   void update();
   void destroy();
   void resetUnit();
   bool draw (IDXSPRITE spriteObj);

   void setMyPosition ( D3DXVECTOR3 pos );
   DxGameSprite getSprite();
   D3DXVECTOR3 getLastPosition();

   //Move functions
   bool stop();
   bool right();
   bool up();
   bool down();
   bool left();

   //getters
   int getHealth();
   int getMovementPoints(); 
   int getDamage();
   DxGameSprite& getImage() { return myImage; }

   //move bool functions
   bool getCanMove();
   void setMove();

   //health functions
   int takingDamage(int effect);
   int healHealth(int effect);
   void killUnit();
   bool checkIfDead();
   int calculateDamage();

   //position functions
   int getY();
   int getX();
   void setY(float newY);
   void setX(float newX);

   bool getHitWaterFlag( );
   void setHitWaterFlag( bool newFlag );

   //Movement functions
   void resetMovePoints() { myMovementPoints = 4; }
   void decMovePoints() { if( myMovementPoints > 0 ) { myMovementPoints--; } }
   void incMovePoints() { if( myMovementPoints < myStartingMovePoints ) { myMovementPoints++; } }
   

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
   bool           hitWater;

   //Pixel position;
   int            myPositionY;
   int            myPositionX;
   DxGameSprite   myImage;
};


#endif