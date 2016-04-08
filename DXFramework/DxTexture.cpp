#include "stdafx.h"
#include <cassert>
#include "Utilities/Rect.h"
#include "Utilities/Point.h"
#include "DxFramework/DxCommon.h"
#include "DxFramework/DxTypes.h"
#include "DxFramework/DxFramework.h"
#include "DxFramework/DxTexture.h"
#include "DxFramework/DxSurface.h"

//=======================================================================
DxTexture::DxTexture ( void )
:myTexture(NULL)
{
   ZeroMemory( &myTextureInfo, sizeof(myTextureInfo) );
}

//=======================================================================
DxTexture::DxTexture ( const DxTexture& other )
:DxImage(other), myTexture(NULL)
{
   ZeroMemory( &myTextureInfo, sizeof(myTextureInfo) );
   *this = other;
}

//=======================================================================
DxTexture::~DxTexture ( void )
{
   destroy();
}

//=======================================================================
DxTexture& DxTexture::operator= ( const DxTexture& other )
{
   DxImage::operator=( other );
   if ( myTexture )
   {
      destroy();
   }
   if ( other.myTexture )
   {
      other.myTexture->AddRef();
      myTexture = other.myTexture;
      myTextureInfo = other.myTextureInfo;
   }
   return *this;
}


//=======================================================================
DxTexture::operator IDXTEXTURE ( void )
{
   return myTexture;
}

//=======================================================================
bool DxTexture::create ( IDXDEVICE device, int width, int height, DWORD usage )
{
   HRESULT result;
   result = D3DXCreateTexture( device,             //Direct3D device object
                               width,              //image width
                               height,             //image height
                               1,                  //mip-map levels (1 for no chain)
                               usage,              //D3DUSAGE: )
                               D3DFMT_UNKNOWN,     //texture format (default)
                               D3DPOOL_DEFAULT,    //memory class for the texture
                               &myTexture          //destination texture
                               );  

   if ( SUCCEEDED( result ) )
   {
      D3DSURFACE_DESC surfaceInfo;
      myTexture->GetLevelDesc( 0, &surfaceInfo );

      myTextureInfo.Width = surfaceInfo.Width;
      myTextureInfo.Height= surfaceInfo.Height;
      myTextureInfo.Format= surfaceInfo.Format;
      myTextureInfo.ResourceType = D3DRTYPE_TEXTURE;  // Guessing

      myTextureInfo.MipLevels = 1;                    // from create call, above
      myTextureInfo.Depth     = 1;                    // Guessing...
      myTextureInfo.ImageFileFormat = D3DXIFF_BMP;    // for lack of better idea here...
      
   }

   return SUCCEEDED( result );
}

//bool DxTexture::create( IDXDEVICE device, int width, int height, DWORD usage, 

//=======================================================================
bool DxTexture::create ( IDXDEVICE device, LPCVOID pData, UINT dataSize, D3DCOLOR transcolor )
{
   HRESULT result;
   assert( getInfoFromFileInMemory( pData, dataSize ) );

   result = D3DXCreateTextureFromFileInMemoryEx ( device,              //Direct3D device object
                                                  pData,               //Pointer to the file in memory
                                                  dataSize,            //the size of the file in memory height
                                                  fileInfo().Width,    //bitmap image width
                                                  fileInfo().Height,   //bitmap image height
                                                  1,                   //mip-map levels (1 for no chain)
                                                  D3DPOOL_DEFAULT,     //the type of surface (standard)
                                                  D3DFMT_UNKNOWN,      //surface format (default)
                                                  D3DPOOL_DEFAULT,     //memory class for the texture
                                                  D3DX_DEFAULT,        //image filter
                                                  D3DX_DEFAULT,        //mip filter
                                                  transcolor,          //color key for transparency
                                                  &myTextureInfo,      //bitmap file myFileInfo (from loaded file)
                                                  NULL,                //color palette
                                                  &myTexture );        //destination texture
   return SUCCEEDED( result );
}

//=======================================================================
bool DxTexture::create ( IDXDEVICE device, const tstring& filename, D3DCOLOR transcolor, POINT* srcSize )
{
   HRESULT result;
   assert( getInfoFromFile( filename ) );
   DWORD usage = 0;  // 0 (default), D3DUSAGE_RENDERTARGET, D3DUSAGE_DYNAMIC

   result = D3DXCreateTextureFromFileEx( device,                                         //Direct3D device object
						                       filename.c_str(),                               //bitmap filename
                                         (srcSize ? (srcSize->x) : fileInfo().Width),    //bitmap image width
                                         (srcSize ? (srcSize->y) : fileInfo().Height),   //bitmap image height
						                       1,                                              //mip-map levels (1 for no chain)
						                       usage,                                          //Usage (see above)
						                       D3DFMT_UNKNOWN,                                 //surface format (default)
						                       D3DPOOL_DEFAULT,                                //memory class for the texture
						                       D3DX_DEFAULT,                                   //image filter
						                       D3DX_DEFAULT,                                   //mip filter
						                       transcolor,                                     //color key for transparency
                                         &myTextureInfo,                                 //bitmap file myFileInfo (from loaded file)
						                       NULL,                                           //color palette
						                       &myTexture );                                   //destination texture
   return SUCCEEDED( result );
}

//=======================================================================
void DxTexture::destroy ( void )
{
   removeFileInfo();
   IfRelease( &myTexture );
   ZeroMemory( &myTextureInfo, sizeof(myTextureInfo) );
}


//=======================================================================
void DxTexture::stretchRect ( IDXDEVICE device, RECT* srcRect, IDXTEXTURE dstTexture, RECT* dstRect )
{
   IDXSURFACE srcSurface = NULL, dstSurface = NULL, prevTarget = NULL;
   HRESULT hr;   

   hr = myTexture->GetSurfaceLevel( 0, &srcSurface );
   assert( SUCCEEDED(hr) );

   hr = dstTexture->GetSurfaceLevel( 0, &dstSurface );
   assert( SUCCEEDED(hr) );

   D3DSURFACE_DESC srcDescr, dstDescr;
   srcSurface->GetDesc( &srcDescr );
   dstSurface->GetDesc( &dstDescr );

   if ( dstDescr.Usage & D3DUSAGE_RENDERTARGET )
   {
      hr = device->StretchRect( srcSurface, srcRect, dstSurface, dstRect, D3DTEXF_NONE );
      assert(SUCCEEDED(hr));
   }

   IfRelease(&srcSurface);
   IfRelease(&dstSurface);
   IfRelease(&prevTarget);
}


//=======================================================================
HRESULT DxTexture::draw ( IDXSPRITE spriteobj, D3DXVECTOR3* position, D3DCOLOR color, RECT* srcRect, D3DXVECTOR3* center )
{
	HRESULT result = spriteobj->Draw( myTexture, srcRect, NULL, position, color);
	assert( SUCCEEDED( result ) );
   return result;
}

//=======================================================================
HRESULT DxTexture::draw ( IDXSPRITE spriteobj, D3DXVECTOR3* position, D3DXVECTOR2* scale, 
						 float rotation, D3DXVECTOR2* center, D3DCOLOR color, RECT* srcRect )
{
	D3DXMATRIX matrix, lastMatrix;
	HRESULT result;
   D3DXVECTOR2 realCenter( (center ? center->x : 0.0f) + (position ? position->x : 0.0f), 
                           (center ? center->y : 0.0f) + (position ? position->y : 0.0f) );
	D3DXVECTOR3 center3d( (center ? center->x : 0.0f), (center ? center->y : 0.0f), 0.0f ); 

   D3DXMatrixTransformation2D( &matrix, &realCenter, 0, scale, &realCenter, rotation, NULL );
   
   result = spriteobj->GetTransform( &lastMatrix );
   assert( SUCCEEDED( result ) );

	result = spriteobj->SetTransform( &matrix );
   assert( SUCCEEDED( result ) );

   result = spriteobj->Draw( myTexture, srcRect, &center3d, position, color );
	assert( SUCCEEDED( result ) );

   result = spriteobj->SetTransform( &lastMatrix );
   assert( SUCCEEDED( result ) );

   return result;
}
