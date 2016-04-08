#pragma once

#if !defined( _TILEDBACKGROUND_H_ )
#define _TILEDBACKGROUND_H_


#include "DxFramework\DxFramework.h"
#include "DxFramework/DxCommon.h"
#include "Utilities\Logger.h"
#include "WinApplFramework/WinApplFramework.h"
#include "DxFramework\DxSurface.h"
#include "DxFramework\DxTexture.h"
#include "DxFramework/DxAnimationInfo.h"
#include "DxFramework/DxAssetManager.h"
#include "DxFramework/DxAnimation.h"
#include "DxFramework/DxGameSprite.h"
#include "Utilities/Point.h"



//===================================================================================================
// This things purpose...
//    Opens a spriteSheet (by name?)
//    Loads a description of tile distribution (by name?)
//    Generates a tiled background, as a texture 
//    Provides access to the tiled background for use by gameRun
//    OR draws the background...
class TiledBackground
{
public:
   TiledBackground();
  ~TiledBackground();

   enum TileType
   {
      GRASS,
      BRICKS,
      BLOCKS
   };

   bool init ( IDXDEVICE dev, const tstring& bgConfigFilename );
   bool update ();
   void shutdown ();

   bool draw ( IDXSURFACE dstSurface, const RECT* dstRect = NULL );
   bool draw ( IDXSPRITE spriteobj, const RECT* dstRect = NULL );

   bool drawMySpriteMap( IDXSPRITE spriteObj );

   bool tileIsCollidable( TileType tileEnumType );
   TileType getTileEnumType( const tstring& label );

   RECT getMyBgSrcRect();
   int numColumns () const { return myNumTilesHoriz; }
   int numRows () const { return myNumTilesVert; }

   std::vector<DxGameSprite> mySpriteMap;
   
private:
   void scrollScreen( IDXSURFACE backBuf );
   bool buildBackground ( const tstring& configFilename );

private:
   IDXDEVICE      myDevice;            //todo  need means to get this from framework...
   DxTexture      mySpriteSheet;
   DxTexture      myTiledBgTexture, myTestTexture;
   tstring        myFilePath;
   tstring        myImageFilePath;
   DxGameSprite   mySprite;

   int         myTileWidth, myTileHeight;    // Actual size rqrd in the tiled bg, NOT image width/height
   int         myNumTilesHoriz, myNumTilesVert;

   RECT        myBgSrcRect;
   int         myBgWidth, myBgHeight;

   struct TileDescr 
   {
      tstring     label;
      int         idNum;
      int         xPos, yPos, pixWidth, pixHeight;
   };

   

   



private:

};


#endif //_TILEDBACKGROUND_H_