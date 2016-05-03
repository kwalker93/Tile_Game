#include "stdafx.h"
#include "Utilities/Point.h"
#include "Utilities/Rect.h"
#include "Utilities/ConfigParser.h"
#include "Bomberman/TiledBackground.h"
#include "Bomberman/TileDescParser.h"

//===================================================================================================>
//
TiledBackground::TiledBackground()
{
   myNumTilesVert = 
   myNumTilesHoriz = 0;
   myDevice = NULL;
}

//===================================================================================================>
//
TiledBackground::~TiledBackground()
{
   shutdown();
}

//===================================================================================================>
//
bool TiledBackground::init ( IDXDEVICE device, const tstring& configFilename )
{
   myDevice = device;
   device->AddRef();

   DxAssetManager& assetManager = DxAssetManager::getInstance();

   bool b = buildBackground( configFilename );


   //TODO:    FIX FOR WIN 8 and 10
      // The RENDER_TARGET mechanism is not working.
      // The test below proves it, it uses NO render target, and draws perfectly.
      // however, if changed to .create( dev, fn, rect, RENDER_TARGET ) version, it creates a render target
      //    AND DOES NOT WORK IN WIN8
 



   //RECT junk = { 0,0, 800,576 };
   //HRESULT result = myTestTexture.create( myDevice, 
   //                                        DxAssetManager::getInstance().getConfigAssetPath(_T("SCOTTS_TEST.png")), 
   //                                        D3DCOLOR_XRGB( 243,242,241), NULL );



   return b;
}


//===================================================================================================>
//
bool TiledBackground::buildBackground ( const tstring& configFilename )
{
   TileDescParser fileInfo;
   bool result = true;

   if ( !fileInfo.init( myDevice, configFilename ) )
   {
      assert(false);
      return false;
   }

   myNumTilesVert = fileInfo.numTileRows();
   myNumTilesHoriz = fileInfo.numTileCols();

   mySpriteMap.resize( myNumTilesVert * myNumTilesHoriz );

   int index = 0;

   int tilePixWidth  = fileInfo.getTilePixWidth();
   int tilePixHeight = fileInfo.getTilePixHeight();

   for (int row = 0; row < fileInfo.numTileRows(); row++)
   {
      for (int col = 0; col < fileInfo.numTileCols(); col++)
      {
         //RECT dstRect = { xPos, yPos, tilePixWidth+xPos, tilePixHeight+yPos };

         //DxTexture& srcTileTexture = fileInfo.getTileTexture(row,col);

         //srcTileTexture.stretchRect( myDevice, NULL, myTiledBgTexture, &dstRect );

         int xPos = col*tilePixWidth;
         int yPos = row*tilePixHeight; 

         mySpriteMap[index].setScale( .5, .5 );

         if(  fileInfo.getTileType( row, col ) == _T("WATER") )
         {
            mySpriteMap[index].setScale(.5f, .5f);
            mySpriteMap[index].create( "WATER" );
            
            //Point pos( (LONG)xPos, (LONG)yPos );
           // mySpriteMap[index].setCollisionArea(Rect( pos, tilePixWidth, tilePixHeight ) );
            //mySpriteMap[index].collidable(false);
         }
         else if ( fileInfo.getTileType( row, col ) == _T("FOREST") )
         {
            mySpriteMap[index].setScale(.5f, .5f);
            mySpriteMap[index].create( "FOREST" );
            

            //Point pos( (LONG)xPos, (LONG)yPos );
            //mySpriteMap[index].setCollisionArea(Rect( pos, tilePixWidth, tilePixHeight ) );
            mySpriteMap[index].setDestroyable ( false );
         }
         else if(  fileInfo.getTileType( row, col ) == _T("BLANK") )
         {
            mySpriteMap[index].setScale(.5f, .5f);
            mySpriteMap[index].create( "BLANK" );
            
            //Point pos( (LONG)xPos, (LONG)yPos );
           // mySpriteMap[index].setCollisionArea(Rect( pos, tilePixWidth, tilePixHeight ) );
            //mySpriteMap[index].collidable(false);
         }
         else
         {
            mySpriteMap[index].setScale(.5f, .5f);
            mySpriteMap[index].create( "GRASS" );
            mySpriteMap[index].collidable(false);
         }
         
         mySpriteMap[index].setPosition( float(xPos), float(yPos) );

         index++;
      }
   }

   return true;
}

//===================================================================================================>
//
void TiledBackground::waterRising( int numOfTurns )
{
	//remove number of turns by 10 to set the right tiles to water tiles
	int offset = numOfTurns - 10;	
   if( offset < 0 )
   {
      return;
   }

   int topRow = 0 + offset;
   int bottomRow = myNumTilesVert - ( offset + 1 );
   int leftCol = 0 + offset;
   int rightCol = myNumTilesHoriz - ( offset + 1 );

   int index = 0;
   int i = 0;
      
   for( i = 0; ( i + topRow ) < myNumTilesVert; i++ )
   {
      index = ( topRow + i ) * myNumTilesHoriz + leftCol;
      if( mySpriteMap[index].getAnimation().name() != "BLANK" )
      {
         mySpriteMap[index].changeAnimation( "WATER", 10 ); 
         mySpriteMap[index].collidable(true);
      }

      index = ( topRow + i ) * myNumTilesHoriz + rightCol - 4;
      if( mySpriteMap[index].getAnimation().name() != "BLANK" )
      {
         mySpriteMap[index].changeAnimation( "WATER", 10 ); 
         mySpriteMap[index].collidable(true);
      }
   }

   for( i = 0; ( i + leftCol ) < myNumTilesHoriz; i++ )
   {
      index = topRow * myNumTilesHoriz + ( leftCol + i );      
      if( mySpriteMap[index].getAnimation().name() != "BLANK" )
      {
         mySpriteMap[index].changeAnimation( "WATER", 10 ); 
         mySpriteMap[index].collidable(true);
      }

      index = bottomRow * myNumTilesHoriz + ( rightCol - i );
      if( mySpriteMap[index].getAnimation().name() != "BLANK" )
      {
         mySpriteMap[index].changeAnimation( "WATER", 10 ); 
         mySpriteMap[index].collidable(true);
      }
   }
}

//===================================================================================================>
//
TiledBackground::TileType TiledBackground::getTileEnumType( const tstring& label )
{
   if( label == "GRASS")
   {
      return GRASS;
   }

   if( label == "WATER" )
   {
      return WATER;
   }

   if( label == "FOREST" )
   {
      return FOREST;
   }

   assert(false);
   return TileType(-1);
}


//===================================================================================================>
//
bool TiledBackground::tileIsCollidable( TiledBackground::TileType tileEnumType )
{
   switch( tileEnumType )
   {
      //List non collidable tile names here
   case GRASS:
      return false;     
      break;
      //List colidable tile names here
   case WATER:
   case FOREST:
      return true;
   default:
      return true;
      break;
   }
   return true;
}



//===================================================================================================>
//
bool TiledBackground::update ( )
{
   return true;
}



//===================================================================================================>
//
void TiledBackground::shutdown ( )
{
   if ( myDevice )
   {
      myDevice->Release();    // Utilities::ifRelease( myDevice );
      myDevice = NULL;
   }
}


//===================================================================================================>
//
bool TiledBackground::draw( IDXSURFACE dstSurface, const RECT* dstRect )
{

   //todo sas - not quite right, just yet.  This should NOT stretch to the dstSurface's full size
   //           so... if dstRect isn't given... fool it into drawing in same aspect as srcSurface
   
   RECT srcRect = { 0, 0, myTiledBgTexture.width(), myTiledBgTexture.height() };

   if (dstRect == NULL) 
      dstRect = &srcRect;

   RECT dRect = *dstRect;

   //todo: this isn't right.  limit to min's.
   dRect.bottom = min( dRect.bottom, srcRect.bottom );
   dRect.right  = min( dRect.right, srcRect.right);


   HRESULT hr = -1;  //myDevice->StretchRect( myTiledBgSurface, NULL, dstSurface, &dRect, D3DTEXF_NONE );


   return SUCCEEDED( hr );  //TODO
}
//===================================================================================================>
//
bool TiledBackground::draw ( IDXSPRITE spriteobj, const RECT* dstRect )
{

   //todo sas - not quite right, just yet.  This should NOT stretch to the dstSurface's full size
   //           so... if dstRect isn't given... fool it into drawing in same aspect as srcSurface
   
   RECT srcRect = { 0, 0, myTiledBgTexture.width(), myTiledBgTexture.height() };

   if (dstRect == NULL) 
      dstRect = &srcRect;

   RECT dRect = *dstRect;

   //todo: this isn't right.  limit to min's.
   dRect.bottom = min( dRect.bottom, srcRect.bottom );
   dRect.right  = min( dRect.right, srcRect.right);


   //HRESULT hr = myDevice->StretchRect( myTiledBgSurface, NULL, dstSurface, &dRect, D3DTEXF_NONE );
   //HRESULT hr = spriteobj->Draw( myTiledBgTexture, NULL, NULL );
   
   
   
   //TODO: Need to change locations
   D3DXVECTOR3 vPos( 0, 0, 0 );
   HRESULT hr = myTiledBgTexture.draw( spriteobj, vPos.x, vPos.y, D3DCOLOR_XRGB(255,255,255));
   
   //drawMySpriteMap( spriteobj );

   return SUCCEEDED( hr );  //TODO
}

//===================================================================================================>
//
bool TiledBackground::drawMySpriteMap( IDXSPRITE spriteobj )
{
   for( size_t i = 0; i < mySpriteMap.size(); i++ )
   {
      mySpriteMap[i].draw( spriteobj );
   }

   return true;
}

