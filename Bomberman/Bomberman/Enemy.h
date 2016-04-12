#pragma once
#if !defined(_ENEMY_H_)
#define _ENEMY_H_

#include "DxFramework/DxImage.h"
#include "DxFramework/DxGameSprite.h"
#include "DxFramework/DxAnimation.h"
#include "Utilities/TTypes.h"

class Enemy
{
public:
    Enemy ( );
    ~Enemy ( );
            
    bool init ( IDXDEVICE device, int xPos, int yPos, int eType );
    void update ();
    void shutdown ();
    bool draw ( IDXSPRITE spriteobj );
    void enemyType();
    void changeDirection();

    // Disables ALL motion
    bool Stop();
    
    bool collidesWith ( const DxGameSprite& other){ return mySprite.collidesWith( other ); };

    void setMyPosition( D3DXVECTOR3 pos ){ myPosition = pos; mySprite.setPosition( myPosition.x, myPosition.y ); }

    D3DXVECTOR3 getMyPosition() { return myPosition; }
    D3DXVECTOR3 getLastPosition() { return myLastPosition; }
    DxGameSprite getSprite() { return mySprite; }

    
private:
    bool loadCharacterAnimations( int eType );
    
private:
    DxAnimation    myEnemyWalkUpAnim;
    DxAnimation    myEnemyWalkDownAnim;
    DxAnimation    myEnemyWalkLeftAnim;
    DxAnimation    myEnemyWalkRightAnim;
    DxAnimation    myEnemyBlowUpAnim;
    
    //Vectors for currentPosition, lastPosition, scale, center, color, velocity
    D3DXVECTOR3    myPosition;
    D3DXVECTOR3    myLastPosition;
    
    DxGameSprite   mySprite;
    float          mySpeed;
    
    bool           myFirstTimeFlag;
    bool           myIsAliveFlag;
    
};
#endif //_TESTAPP_H_