#include <stdafx.h>
#include <cassert>
#include "DxFramework/DxCommon.h"
#include "DxFramework/DxTypes.h"
#include "Bomberman/GameUI.h"

//=======================================================================
GameUI::GameUI()
{
}

//=======================================================================
GameUI::~GameUI()
{
}

//=======================================================================
bool GameUI::init( IDXFONT font, int xPos, int yPos, D3DCOLOR color, int turnCounter )
{
   myTextColor = color;
   myTurnCounter = turnCounter;

   myXPos = xPos;
   myYPos = yPos;


   //set turn counter 
   myTurnCounterText.create( font, "Turns Counter: ", float(xPos), float(yPos), 192, 64 );  

   myCurrentUnit.getSprite().setScale( 1.0f, 1.0f );

   myCurrentUnit.init( Unit::blank, float(xPos), float(yPos) + 128 );
   //set unit image

   //myCurrentUnitImage.setScale(1.0f, 1.0f);
   //myCurrentUnitImage.create("BLANK", 0);
   myCurrentUnitImage.setPosition( float(xPos), float(yPos) + 128 );

   //set health text
   myHealthText.create( font, "Current Health: ", float(xPos), float(yPos) + 256, 192, 64 );  
   
   //set power text
   myPowerText.create( font, "Attack Power: ", float(xPos), float(yPos) + 320, 192, 64 );  
   
   //set move point text
   myMovePointsText.create( font, "Movement Points: ", float(xPos), float(yPos) + 384, 192, 64 );  

   return true;
}
//=======================================================================
bool GameUI::update( )
{
   updateTurnCounterText( );
   updateCurrentUnitImage( );
   updateSelectedUnitPowerText( );
   updateSelectedUnitMovementPointsText( );
   updateSelectedUnitHealthText( );

   return true;
}

//=======================================================================
bool GameUI::destroy()
{
   return true;
}

//=======================================================================
bool GameUI::draw( IDXSPRITE spriteObj )
{
   //image
   myCurrentUnitImage.draw( spriteObj );
   
   //turn counter
   myTurnCounterText.draw( spriteObj );
   
   //power text
   myPowerText.draw( spriteObj );
   
   //move points text
   myMovePointsText.draw( spriteObj );
   
   //health text
   myHealthText.draw( spriteObj );
   
   return true;
}

//=======================================================================
void GameUI::setCurrentUnit( Unit& newUnit )
{
   myCurrentUnit = newUnit;
}

//=======================================================================
void GameUI::updateCurrentUnitImage()
{
   myCurrentUnitImage = myCurrentUnit.getSprite();
   myCurrentUnitImage.setScale(1.0f, 1.0f);
   myCurrentUnitImage.setPosition( myXPos + 100, myYPos + 100);
}

//=======================================================================
void GameUI::updateSelectedUnitPowerText()
{
   tstringstream converter;
   converter << myCurrentUnit.getDamage();
   tstring temp = _T( converter.str() );

   myPowerText.setText( "Attack Power: " + temp );
}

//=======================================================================
void GameUI::updateSelectedUnitMovementPointsText()
{
   tstringstream converter;
   converter << myCurrentUnit.getMovementPoints();
   tstring temp = _T( converter.str() );

   myMovePointsText.setText( "Movement Points: " + temp );
}

//=======================================================================
void GameUI::updateTurnCounterText( )
{
   tstringstream converter;
   converter << myTurnCounter;
   tstring temp = _T( converter.str() );

   myTurnCounterText.setText( "Turn Counter: " + temp );
}

//=======================================================================
void GameUI::updateSelectedUnitHealthText( )
{
   tstringstream converter;
   converter << myCurrentUnit.getHealth();
   tstring temp = _T( converter.str() );

   myHealthText.setText( "Current Health: " + temp );
}










