#pragma once
#if !defined(_KITTY_H_)
#define _KITTY_H_

#include "DxFramework\DxImage.h"
#include "DxFramework\DxGameSprite.h"
//#include "DxFramework\DxTexture.h"
#include "DxFramework/DxAnimation.h"
#include "Utilities/TTypes.h"

class Kitty
{
public:
   Kitty ( );
   ~Kitty ( );

   //typedef enum 
   //{
   //   STILL,
   //   UP,
   //   DOWN,
   //   LEFT,
   //   RIGHT
   //} DIRECTION;

   enum Direction{ STILL, STILLUP, STILLDOWN, STILLLEFT, STILLRIGHT, UP, DOWN, LEFT, RIGHT };
   // enum Direction{ UP = 1, DOWN, LEFT, RIGHT, STILL = (1 << 8) };  //SAS: Idea on how STILL is a "qualifier" on the ACTUAL 4 direction STATES; if ( myState & STILL )
   // And... STATE might be more than just direction and motion....


   bool init ();
   void update ();
   void shutdown ();

   bool create ( IDXDEVICE device, int xPos, int yPos );
   bool draw ( IDXSPRITE spriteobj );
   bool collidesWith ( const DxGameSprite& other){ return mySprite.collidesWith( other ); };
   bool radialCollidesWith ( const DxGameSprite& other){ return mySprite.radialCollidesWith( other ); };
   bool goStop ( );     // Disables ALL motion
   bool goUp();         // enabled upward motion UNTIL motion changes or is stopped
   bool goDown();       // LAST motion call WINS
   bool goLeft();
   bool goRight();
   bool goReverse();

   bool goStillUp();  
   bool goStillDown();
   bool goStillLeft();
   bool goStillRight();



   void setMyPosition( D3DXVECTOR3 pos ){ myPosition = pos; mySprite.setPosition(myPosition.x, myPosition.y ); }
   D3DXVECTOR3 getMyPosition() { return myPosition; }
   D3DXVECTOR3 getLastPosition(){ return myLastPosition; }
   DxGameSprite getSprite(){ return mySprite; }

private:
   bool loadCharacterAnimations();
   bool stillDirection( Direction prevDirection );

private:
   
   //Animation may not be needed
   DxAnimation    myCatStillAnim;
   DxAnimation    myCatStillUpAnim;
   DxAnimation    myCatStillDownAnim;
   DxAnimation    myCatStillLeftAnim;
   DxAnimation    myCatStillRightAnim;

   DxAnimation    myCatWalkUpAnim;
   DxAnimation    myCatWalkDownAnim;
   DxAnimation    myCatWalkLeftAnim;
   DxAnimation    myCatWalkRightAnim;
   DxAnimation    myCatBlowUpAnim;
   
   //Vectors for currentPosition, lastPosition, scale, center, color, velocity
   // last velocity, acceleration (Need a get mypos method)
   D3DXVECTOR3    myPosition;
	D3DXVECTOR3    myLastPosition;   

	//DxTexture      myTexture;
   Direction      myDirection;
   DxGameSprite   mySprite;
   float          mySpeed;

   bool           myFirstTimeFlag;
   
   //Taken from bomb which took them from gamesprite
   // Might not be neccasary



};
#endif //_TESTAPP_H_