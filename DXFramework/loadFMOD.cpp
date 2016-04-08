#include "stdafx.h"
#include "loadFMOD.h"


using namespace std;


loadFMOD::loadFMOD ()
{
}

loadFMOD::~loadFMOD ()
{
}


bool loadFMOD::checkDllPtr ( void* p, const TCHAR* name )
{
   if ( p == NULL )
   {
      printf( "Unable to GetProcAddress for %s\n", name );
      return false;
   }
   return true;
}


bool loadFMOD::loadAllProcAddresses ( )
{
   bool b = false;
   fmodInst = LoadLibrary( _T("lib\\fmodL.dll") );
   DWORD gle = ::GetLastError();

   if (fmodInst != NULL) 
   { 
      dllPtrSystem_Create              = (TypeFMOD_System_Create                *) GetProcAddress(fmodInst, _T("FMOD_System_Create"));
      dllPtrSystem_Init                = (TypeFMOD_System_Init                  *) GetProcAddress(fmodInst, _T("FMOD_System_Init"));
      dllPtrSystem_Close               = (TypeFMOD_System_Close                 *) GetProcAddress(fmodInst, _T("FMOD_System_Close"));
      dllPtrSystem_Update              = (TypeFMOD_System_Update                *) GetProcAddress(fmodInst, _T("FMOD_System_Update"));
      dllPtrSystem_GetVersion          = (TypeFMOD_System_GetVersion            *) GetProcAddress(fmodInst, _T("FMOD_System_GetVersion"));
      dllPtrSystem_CreateSound         = (TypeFMOD_System_CreateSound           *) GetProcAddress(fmodInst, _T("FMOD_System_CreateSound"));
      dllPtrSystem_PlaySound           = (TypeFMOD_System_PlaySound             *) GetProcAddress(fmodInst, _T("FMOD_System_PlaySound"));
      dllPtrSound_Release              = (TypeFMOD_Sound_Release                *) GetProcAddress(fmodInst, _T("FMOD_Sound_Release"));
      dllPtrSystem_CreateChannelGroup  = (TypeFMOD_System_CreateChannelGroup    *) GetProcAddress(fmodInst, _T("FMOD_System_CreateChannelGroup"));
      dllPtrSound_SetMode              = (TypeFMOD_Sound_SetMode                *) GetProcAddress(fmodInst, _T("FMOD_Sound_SetMode"));
      dllPtrSound_GetMode              = (TypeFMOD_Sound_GetMode                *) GetProcAddress(fmodInst, _T("FMOD_Sound_GetMode"));
      dllPtrSound_SetLoopCount         = (TypeFMOD_Sound_SetLoopCount           *) GetProcAddress(fmodInst, _T("FMOD_Sound_SetLoopCount"));
      dllPtrSound_GetLoopCount         = (TypeFMOD_Sound_GetLoopCount           *) GetProcAddress(fmodInst, _T("FMOD_Sound_GetLoopCount"));
      dllPtrSound_SetLoopPoints        = (TypeFMOD_Sound_SetLoopPoints          *) GetProcAddress(fmodInst, _T("FMOD_Sound_SetLoopPoints"));
      dllPtrSound_GetLoopPoints        = (TypeFMOD_Sound_GetLoopPoints          *) GetProcAddress(fmodInst, _T("FMOD_Sound_GetLoopPoints"));
      dllPtrSound_GetName              = (TypeFMOD_Sound_GetName                *) GetProcAddress(fmodInst, _T("FMOD_Sound_GetName"));
      dllPtrSound_GetLength            = (TypeFMOD_Sound_GetLength              *) GetProcAddress(fmodInst, _T("FMOD_Sound_GetLength"));
      dllPtrChannel_Stop               = (TypeFMOD_Channel_Stop                 *) GetProcAddress(fmodInst, _T("FMOD_Channel_Stop"));
      dllPtrChannel_SetPaused          = (TypeFMOD_Channel_SetPaused            *) GetProcAddress(fmodInst, _T("FMOD_Channel_SetPaused"));
      dllPtrChannel_GetPaused          = (TypeFMOD_Channel_GetPaused            *) GetProcAddress(fmodInst, _T("FMOD_Channel_GetPaused"));
      dllPtrChannel_SetVolume          = (TypeFMOD_Channel_SetVolume            *) GetProcAddress(fmodInst, _T("FMOD_Channel_SetVolume"));
      dllPtrChannel_GetVolume          = (TypeFMOD_Channel_GetVolume            *) GetProcAddress(fmodInst, _T("FMOD_Channel_GetVolume"));
      dllPtrChannel_SetMode            = (TypeFMOD_Channel_SetMode              *) GetProcAddress(fmodInst, _T("FMOD_Channel_SetMode"));
      dllPtrChannel_GetMode            = (TypeFMOD_Channel_GetMode              *) GetProcAddress(fmodInst, _T("FMOD_Channel_GetMode"));
      dllPtrChannel_SetLoopCount       = (TypeFMOD_Channel_SetLoopCount         *) GetProcAddress(fmodInst, _T("FMOD_Channel_SetLoopCount"));
      dllPtrChannel_GetLoopCount       = (TypeFMOD_Channel_GetLoopCount         *) GetProcAddress(fmodInst, _T("FMOD_Channel_GetLoopCount"));
      dllPtrChannel_SetLoopPoints      = (TypeFMOD_Channel_SetLoopPoints        *) GetProcAddress(fmodInst, _T("FMOD_Channel_SetLoopPoints"));
      dllPtrChannel_GetLoopPoints      = (TypeFMOD_Channel_GetLoopPoints        *) GetProcAddress(fmodInst, _T("FMOD_Channel_GetLoopPoints"));
                                                                                   
      b = true;
      b &= checkDllPtr( dllPtrSystem_Create              , _T("FMOD_System_Create"));
      b &= checkDllPtr( dllPtrSystem_Init                , _T("FMOD_System_Init"));
      b &= checkDllPtr( dllPtrSystem_Close               , _T("FMOD_System_Close"));
      b &= checkDllPtr( dllPtrSystem_Update              , _T("FMOD_System_Update"));
      b &= checkDllPtr( dllPtrSystem_GetVersion          , _T("FMOD_System_GetVersion"));
      b &= checkDllPtr( dllPtrSystem_CreateSound         , _T("FMOD_System_CreateSound"));
      b &= checkDllPtr( dllPtrSystem_PlaySound           , _T("FMOD_System_PlaySound"));
      b &= checkDllPtr( dllPtrSound_Release              , _T("FMOD_Sound_Release"));
      b &= checkDllPtr( dllPtrSystem_CreateChannelGroup  , _T("FMOD_System_CreateChannelGroup"));
      b &= checkDllPtr( dllPtrSound_SetMode              , _T("FMOD_Sound_SetMode"));
      b &= checkDllPtr( dllPtrSound_GetMode              , _T("FMOD_Sound_GetMode"));
      b &= checkDllPtr( dllPtrSound_SetLoopCount         , _T("FMOD_Sound_SetLoopCount"));
      b &= checkDllPtr( dllPtrSound_GetLoopCount         , _T("FMOD_Sound_GetLoopCount"));
      b &= checkDllPtr( dllPtrSound_SetLoopPoints        , _T("FMOD_Sound_SetLoopPoints"));
      b &= checkDllPtr( dllPtrSound_GetLoopPoints        , _T("FMOD_Sound_GetLoopPoints"));
      b &= checkDllPtr( dllPtrSound_GetName              , _T("FMOD_Sound_GetName"));
      b &= checkDllPtr( dllPtrSound_GetLength            , _T("FMOD_Sound_GetLength"));
      b &= checkDllPtr( dllPtrChannel_Stop               , _T("FMOD_Channel_Stop"));
      b &= checkDllPtr( dllPtrChannel_SetPaused          , _T("FMOD_Channel_SetPaused"));
      b &= checkDllPtr( dllPtrChannel_GetPaused          , _T("FMOD_Channel_GetPaused"));
      b &= checkDllPtr( dllPtrChannel_SetVolume          , _T("FMOD_Channel_SetVolume"));
      b &= checkDllPtr( dllPtrChannel_GetVolume          , _T("FMOD_Channel_GetVolume"));
      b &= checkDllPtr( dllPtrChannel_SetMode            , _T("FMOD_Channel_SetMode"));
      b &= checkDllPtr( dllPtrChannel_GetMode            , _T("FMOD_Channel_GetMode"));
      b &= checkDllPtr( dllPtrChannel_SetLoopCount       , _T("FMOD_Channel_SetLoopCount"));
      b &= checkDllPtr( dllPtrChannel_GetLoopCount       , _T("FMOD_Channel_GetLoopCount"));
      b &= checkDllPtr( dllPtrChannel_SetLoopPoints      , _T("FMOD_Channel_SetLoopPoints"));
      b &= checkDllPtr( dllPtrChannel_GetLoopPoints      , _T("FMOD_Channel_GetLoopPoints"));
      
   }


   return b;

}

//----------------------------------------------------------------------------------------
//
tstring loadFMOD::assetFile ( const tstring& filename )
{
   return "..\\ExampleData\\" + filename;
}


//----------------------------------------------------------------------------------------
//
void loadFMOD::ERRCHECK(FMOD_RESULT result)
{
   if (result != FMOD_OK)
   {
      printf("FMOD error %d - %s", result, "[TODO:Error String Here]" ); // , FMOD_ErrorString(result));
      exit(1);
   }
}